### Practical C++20 coroutines notes for ARM Cortex-M

Достаточно много времени прошло с предыдущей заметки на тему использования сопрограмм. Изначально было в планах продемонстрировать на чем-то концепцию и как именно их можно было применять. На тот момент вариант примера в виде мигания светодиодиком подошел отлично. Но он был слишком простой. Необходимо было придумать что-то более сложное и более полезное, что-ли. Таким образом и появилась идея переписать драйвер дисплея и SPI-FLASH в проекте-долгострое.

Небольшой план, что будет в заметке:

1. Предистория с транзакциями
2. Как это работает в общих чертах
3. Работаем с SPI интерфейсом
4. Массив команд инициализации
5. Идеи с std::tuple транзакций
6. Реализуем when_all_sequence
7. Как работает Task из cppcoro
8. Как это тестировать?
9. Добавляем параметрические тесты в GTest
10. Добавляем черновой вариант драйвера для SPI-FLASH
11. Добавляем чтение JEDEC ID
12. Добавляем чтение device id
13. Ожидание окончания выполнения сопрограммы

### 0. Перед прочтением
Заметка предполагает базовое знакомство читателя с сопрогрмаммами/ их синтаксисом. В силу наличия более подробных статей на тему деталей реализации сопрограмм и их устройства рекомендуются к прочтению следующие материалы:

https://blog.panicsoftware.com/your-first-coroutine/
https://lewissbaker.github.io/2017/09/25/coroutine-theory
https://lewissbaker.github.io/2017/11/17/understanding-operator-co-await
https://lewissbaker.github.io/2018/09/05/understanding-the-promise-type
https://lewissbaker.github.io/2020/05/11/understanding_symmetric_transfer

В заметке изложение материала может показаться непоследовательным. Предложения буду рад увидеть в виде issues или же в комментариях/сообщениях в Telegram.

Что будет рассмотрено:
* драйвер дисплея с использованием сопрограмм, с использованием таблицы инициализации на базе std::tuple и классического варианта на базе массива команд.
* фрагмент драйвера для SPI-FLASH памяти
* написание тестов на драйвер SPI с использованием параметрических тестов в GTest
* Рассмотрение работы и реализация нескольких примитивов из cppcoro библиотеки.

### 1. Предистория с транзакциями

Изначально, идея переписывания с подхода в виде транзакций появилась как только возникла необходимость расширения транзакционности read-транзакциями. Для формирования очереди отправки этот подход был достаточно удобным, но для очереди приема получалось что-то вроде callback-hell подхода.

В общих чертах, транзакционный подход представлял собой следующую идею:
```cpp
template <typename... Args> void sendCommand(std::uint8_t _command, Args... _commandArgs) noexcept
{
    sendCommand(_command);
    sendChunk(static_cast<std::uint8_t>(_commandArgs)...);
}

template <typename... Args> void sendChunk(Args... _chunkArgs) noexcept
{
    std::array chunk = {static_cast<std::uint8_t>(_chunkArgs)...};
    Interface::Spi::Transaction chunkTransaction{};

    chunkTransaction.beforeTransaction = [this] { setDcPin(); };

    chunkTransaction.transactionAction = [this, chunkToSend = std::move(chunk)] {
        m_pBusPtr->sendChunk(
            reinterpret_cast<const std::uint8_t*>(chunkToSend.data()), chunkToSend.size());
    };

    chunkTransaction.afterTransaction = [this] { resetDcPin(); };

    m_pBusPtr->addTransaction(std::move(chunkTransaction));
}
```

Т.е. у нас есть некоторое действие до транзакции, сама транзакция и действие, которое будет выполнено после нее. Использование так-же было достаточно удобным:
```cpp
sendCommand(DisplayReg::SLPOUT);
sendCommand(DisplayReg::COLMOD, 0x55);
sendCommand(DisplayReg::MADCTL, 0x08);
sendCommand(DisplayReg::CASET, 0x00, 0, 0, 240);
```
Этот подход достаточно хорошо себя показал в работе. Типовая задача для применения имела следующий вид:

1. Выставить состояние порта D/C для дисплея  для выбора типа принимаемых данных (команда или данные) 
2. Сформировать DMA- транзакцию
3. По ее окончанию выполнить следующую отправку, если блок данных был не полностью отправлен
4. Или вернуть состояние порта D/C в исходное состояние и перейти к обработке следующей транзакции

Недостатки стали проявляться при попытке реализации драйвера для SPI-FLASH которая должна была быть использована в связке с Little FS. Где-то в тот-же период времени было найдено предложение в стандарт С++20 по сопрограммам, просмотрена серия мотивирующих статей:
https://habr.com/ru/company/yandex/blog/420861/
https://habr.com/ru/post/201826/
https://habr.com/ru/company/yandex/blog/240525/
https://habr.com/ru/post/340732/

И было принято решение о переписывании на сопрограммы часть существующих драйверов.

### 2. Как это работает в общих чертах
Для разработчиков, которые имели дело с C#/Python/JS не являются чем-то новым ключевые слова `yeild`, `await`,`async`.(Да, они тут приведены в общем варианте, без принадлежности к конкретному языку). В кратце, идея сопрограмм состоит в возможности приостановки функции в любом месте исполнения с последствующим восстановлением ее работы из прерванной точки. Фактически, мы получаем легковесные потоки уровня пользователя, т.е. для переключения сопрограмм нам нет необходимости обращаться к ядру ОС/etc.

В С++20 минимальный пример сопрограммы может быть представлен в виде следущей конструкции:
```cpp
#include <coroutine>
#include <iostream>

struct Awaitable
{
    struct Promise;
    using promise_type = Promise;

    Awaitable(std::coroutine_handle<promise_type> coroHandle) : thisCoroutine{coroHandle}
    {
        std::cout << "Awaitable created\n";
    }
    ~Awaitable()
    {
        std::cout << "Awaitable destroyed\n";
        if (thisCoroutine)
            thisCoroutine.destroy();
    }
    struct Promise
    {
        auto initial_suspend() noexcept
        {
            return std::suspend_always();
        }
        auto final_suspend() noexcept
        {
            return std::suspend_always();
        }
        void unhandled_exception()
        {
            std::terminate();
        }

        Awaitable get_return_object()
        {
            return Awaitable(std::coroutine_handle<promise_type>::from_promise(*this));
        }
        void return_void() noexcept
        {
        }
    };
    bool isFinished()
    {
        if (thisCoroutine)
            return thisCoroutine.done();
        return false;
    }
    void restore()
    {
        if (thisCoroutine && !thisCoroutine.done())
            thisCoroutine.resume();
    }
    std::coroutine_handle<promise_type> thisCoroutine;
};

Awaitable callMe()
{
    std::cout << "Hello ";
    co_await std::suspend_always{};
    std::cout << "World\n";
}
int main()
{
    auto lazyHello = callMe();
    while (!lazyHello.isFinished())
        lazyHello.restore();

    return 0;
}
```
Где полезная нагрузка- ленивый вывод фразы "Hello world".
Попробуем реализовать идею использования, только на примере чего-то реальнее. Например, инициализации и работы с дисплеем. Для интереса, весь обмен должен происходить с использованием DMA микроконтроллера.

### 3. Работа с SPI интерфейсом
 Для работы с SPI интерфейсом необходимо реализовать небольшой набор Awaitable-типов, на которых может быть вызван оператор `co_await`.
Самый простой вариант имеет следующий вид:
```cpp
struct Awaiter
{
    bool resetDcPin = false;
    bool restoreInSpiCtx = false;
    const std::uint8_t* pTransmitBuffer;
    This_t* pBaseDisplay;
    std::uint16_t bufferSize;

    bool await_ready() const noexcept
    {
        // проверяем, есть ли необходимость выполнять приостановку сопрограммы
        const bool isAwaitReady = pTransmitBuffer == nullptr || bufferSize == 0;
        return isAwaitReady;
    }
    void await_resume() const noexcept
    {
        //вызов, который будет совершен при выполнении .resume() у сопрограммы
        if (resetDcPin)
            pBaseDisplay->setDcPin();
    }
    void await_suspend(std::coroutine_handle<> thisCoroutine) const
    {
        //действие на время приостановки сопрограммы. В SPI драйвер передается handle сопрограммы,
        // после чего она приостановлена.
        if (resetDcPin)
            pBaseDisplay->resetDcPin();

        pBaseDisplay->getSpiBus()->transmitBuffer(
            pTransmitBuffer, bufferSize, thisCoroutine.address(), restoreInSpiCtx);
    }
};
```

В свою очередь, на стороне SPI-драйвера по окончании передачи данных выполняется следующий код:
```cpp
void transmitCompleted() noexcept
{
    const bool isAllDmaTransactionsProceeded = m_transmitContext.fullDmaTransactionsCount == 0;
    const bool isAllChunckedTransactionsCompleted =
        m_transmitContext.chunkedTransactionBufSize == 0;

    if (!isAllDmaTransactionsProceeded)
    {
        //Если еще можем передавать транзакции размером с DMA буфер
    }
    else if (!isAllChunckedTransactionsCompleted)
    {
        // Если транзакции меньше размера DMA буфера не переданы
    }
    else
    {
        // В случае, если все DMA транзакции выполнены- проверяем, в каком контексте выполнения
        // должна быть восстановлена сопрограмма.Не забываем, что этот метод вызывается из контекта
        // прерывания и восстановление тяжелой сопрограммы может привести к трудноулавливааемым
        // ошибкам. Тут есть два варианта - либо восстанавливаемся в контекте прерывания, либо
        // передаем обработчик сопрограммы в очередь,которая обрабатывается в главном потоке. Таким
        // образом, сопрограмма будет восстановлена из main-потока.
        if (m_transmitContext.restoreInSpiCtx)
        {
            m_coroHandle.resume();
        }
        else
        {
            CoroUtils::CoroQueueMainLoop::GetInstance().pushToLater(m_coroHandle);
        }
    }
}
```
В целях уменьшения нагрузки на чтение кода- при выполнении `transmitBuffer` выполняется формирование контекста передачи данных в драйвере, после чего выполняется рассчет целого количества DMA транзакций + размер оставшегося буфера, который так-же будет передан.
Далее, по окончанию передачи DMA транзакции выполлняется вызов `transmitCompleted` где выполняется формирование новой посылки или же выполняется восстановление приостановленной сопрограммы в заданном контексте выполнения( в контексте прерывания или же в главном потоке программы).

### 4. Итерация на массиве команд инициализации
Нам будут необходимы несколько всопомогательных функций. Их больше, чем две. но в общем случае представим их так:
```cpp
auto sendCommand(const std::uint8_t* _pBuffer, std::size_t _bufferSize) noexcept
{
    const std::uint8_t* commandBuf = _pBuffer;
    const std::uint8_t* ArgBuf = _pBuffer + 1;
    const std::uint16_t ArgsBufferSize = static_cast<std::uint16_t>(_bufferSize - 1);

    return CoroUtils::when_all_sequence(
        sendCommandImpl(commandBuf),
        ArgsBufferSize > 0 ? sendChunk(ArgBuf, ArgsBufferSize) : sendChunk(nullptr, 0));
}

auto sendChunk(const std::uint8_t* _pBuffer, std::size_t _bufferSize) noexcept
{
    return Awaiter{.pTransmitBuffer = _pBuffer,
                   .pBaseDisplay = this,
                   .bufferSize = static_cast<std::uint16_t>(_bufferSize)};
}
```

Массив для инициализации дисплея представлен следующим образом:
```cpp
namespace DisplayDriver::InitializationCommands
{
// clang-format off
constexpr std::size_t CommandsSize = 328;
constexpr std::size_t CommandsTransactionsCount = 59;
static auto Commands = std::array<std::uint8_t, CommandsSize>
{
    /***Cmd****Argc****delay****argv*****************************/
        0xFE,   0,      0
    ,   0xEF,   0,      0
    ,   0xEB,   1,      0,      0x14

    ,   0xFE,   0,      0
    ,   0xEF,   0,      0
    ,   0xEB,   1,      0,      0x14
    ,   0xFE,   0,      0
    ,   0xEF,   0,      0
    ,   0xEB,   1,      0,      0x14
    .....
}
// clang-format on
} // namespace DisplayDriver::InitializationCommands
```

Собираем в полноценную картину функцию инициализации дисплея. Для каждой команды необходимо выполнить передачу команды + передачу ее аргументов, если они есть + выполнить ожидание N миллисекунд(после команды DISP_ON, например). Т.к. отправлять мы будем с использованием ранее реализованных функций - получаем следующий вид тела функции:
```cpp
void initDisplay() noexcept
{
    TBaseSpiDisplay::resetResetPin();
    Delay::waitFor(100);
    TBaseSpiDisplay::setResetPin();
    size_t CommandCount = InitializationCommands::CommandsTransactionsCount;
    const std::uint8_t* pBuffer = InitializationCommands::Commands.data();
    while (CommandCount--)
    {
        const std::uint8_t* Command = pBuffer++;
        const std::uint8_t NumArgs = *pBuffer++;
        const std::uint8_t Delay = *pBuffer++;

        co_await TBaseSpiDisplay::sendCommandImpl(Command);
        if (NumArgs)
        {
            co_await TBaseSpiDisplay::sendChunk(pBuffer++, NumArgs);
            pBuffer += (NumArgs - 1);
        }
        if (Delay)
            Delay::waitFor(Delay);
    }
    TBaseSpiDisplay::m_displayInitialized.set();
}
```
Что мы получили? Каждый вызов `sendCommandImpl` - ассинхронный "под капотом". При выполнении ` co_await TBaseSpiDisplay::sendCommandImpl` или `co_await TBaseSpiDisplay::sendChunk` - выполняется приостановка функции initDisplay, при этом управление возвращается вызывающей стороне. По окончании процедуры инициализации выполняется установка флага окончания инициализации дисплея.

Как может выглядеть процедура отправки дисплейного буфера? Т.к. в проекте используется библиотека LVGL -  фреймбуфер может быть non-screen-sized, т.е. не полностью соответствовать размеру буфера экрана, что позволяет выполнять отрисовку фрагментами.(Иногда может не быть возможности поместить полностью в память буфер дисплея)

Для реализации функции отправки нам необходимо выполнить отправку команд на установку области экрана, в которую будет осуществлена отрисовка, после чего отправить команду на запись в память дисплея и выполнить отправку дисплейного буфера.
Что-же. В синхронном варианте, данный код мог-бы иметь вид:
```cpp
void fillRectangle(
    std::uint16_t _x,
    std::uint16_t _y,
    std::uint16_t _width,
    std::uint16_t _height,
    TBaseSpiDisplay::TColor* _colorToFill) noexcept
{

    const std::uint16_t DisplayHeight = TBaseSpiDisplay::getHeight();
    const std::uint16_t DisplayWidth = TBaseSpiDisplay::getWidth();

    const bool isCoordsValid{!((_x >= DisplayWidth) || (_y >= DisplayHeight))};
    if (isCoordsValid)
    {
        //Определяем размеры буфера для отправки
        const size_t BytesSizeX = (_width - _x + 1);
        const size_t BytesSizeY = (_height - _y + 1);
        const size_t BytesSquare = BytesSizeX * BytesSizeY;
        const size_t TransferBufferSize = (BytesSquare * sizeof(typename TBaseSpiDisplay::TColor));

        //Формируем область экрана для обновления
        setAddrWindow(_x, _y, _width, _height);

        static std::uint8_t RamWriteCmd{0x2C};
        // Команда на запись в экранный буфер
        TBaseSpiDisplay::sendCommandImplFast(&RamWriteCmd);

        //Устанавликаем порт Data/Command в режим работы с данными(все что передано в дисплей
        //воспринимается, как данные, а не как команды)
        TBaseSpiDisplay::setDcPin();
        // Отправляем дисплейный буфер
        TBaseSpiDisplay::sendChunk(
            reinterpret_cast<const std::uint8_t*>(_colorToFill), TransferBufferSize);
        // Восстанавливаем состояние порта Data/Command
        TBaseSpiDisplay::resetDcPin();
        // Сигнализируем об окончании заполнении области дисплея
        TBaseSpiDisplay::onRectArreaFilled.emitLater();
    }
}
```

А что необходимо изменить, чтобы код стал выполняться ассинхронно? Т.е. выполнили транзакцию по DMA- вернулись в точку приостановки, отправили следующую команду и/или дисплейный буфер и продолжили выполнение?
На фрагменте ниже приведены все изменения, которые необходимо выполнить(пратически все).
```cpp

//Формируем область экрана для обновления
co_await setAddrWindow(_x, _y, _width, _height); // <=============== co_await here

static std::uint8_t RamWriteCmd{0x2C};
// Команда на запись в экранный буфер
co_await TBaseSpiDisplay::sendCommandImplFast(&RamWriteCmd); // <=============== co_await here

TBaseSpiDisplay::setDcPin();
// Отправляем дисплейный буфер
co_await TBaseSpiDisplay::sendChunk(
    reinterpret_cast<const std::uint8_t*>(_colorToFill),
    TransferBufferSize); // <=============== co_await here

TBaseSpiDisplay::resetDcPin();

TBaseSpiDisplay::onRectArreaFilled.emitLater();

```

Добавлением в трех строках `co_await` мы получили ассинххронный код. Остается только дописать немного примитивов, которые будут нам необходимы, чтобы это все заработало. А именно, реализовать притивы `when_all_sequence` для запуска последовательности и `Task` для вызова `co_await` на возвращаемом результате функции `setAddrWindow`.

### 5. Для любителей посложнее - итерация на std::tuple<CommandDescriptor>
Данная идея была первой. Прдеставляем таблицу команд инициализации диспллея в виде std::tuple который в свою очередь состоял бы из Дескрипторов команд.
Преимущество- нет необходимости указывать количество аргументов у команды. Все, что задано после `DefaultDelay`- будет считаться аргументом команды.

Дескриптор команды был реализован как:
```cpp
template <std::uint8_t... Command> struct CommandDescriptor
{
};

template <std::uint8_t Command, std::uint8_t CommandDelay, std::uint8_t... CommandArgs>
struct CommandDescriptor<Command, CommandDelay, CommandArgs...>
{
    std::uint8_t commandDelay = CommandDelay;
    std::array<std::uint8_t, sizeof...(CommandArgs) + 1> command{Command, CommandArgs...};
};

template <std::uint8_t Command, std::uint8_t CommandDelay>
struct CommandDescriptor<Command, CommandDelay>
{
    std::uint8_t commandDelay = CommandDelay;
    std::array<std::uint8_t, 1> command{Command};
};

template <std::uint8_t Command> struct CommandDescriptor<Command>
{
    std::uint8_t commandDelay = 0;
    std::array<std::uint8_t, 1> command{Command};
};
```
В свою очередь, для создания таблицы команд для инициализации было необходимо их сохранить в tuple. В первой итерации, это выглядело вот так:
```cpp
static std::tuple CommandsArray = {
    CommandDescriptor<0xFE>{},
    CommandDescriptor<0xEF>{},
    CommandDescriptor<0xEB, DefaultDelay, 0x14>{},
    CommandDescriptor<0xFF, DefaultDelay, 0x60, 0x01, 0x04>{},
    CommandDescriptor<0x74, DefaultDelay, 0x10, 0x75, 0x80, 0x00, 0x00, 0x4E, 0x00>{},
    CommandDescriptor<0xC3, DefaultDelay, 0x14, 0xC4, 0x14, 0xC9, 0x25>{},
    CommandDescriptor<0x74, DefaultDelay, 0x10, 0x85, 0x80, 0x00, 0x00, 0x4e, 0x00>{},
    CommandDescriptor<0x29>{}};
```

Как распаковать подобный `std::tuple` дескрипторов?
Можно применить `std::apply`и в нем уже заниматься распаковкой команд для их отправки.
В таком случае, произойдет небольшое видоизменение функции для инициализации дисплея.

```cpp
template <typename Tuple, std::size_t... Indexes>
CoroUtils::VoidTask launchInit(
    Tuple&& commandSequence,
    std::integer_sequence<std::size_t, Indexes...>) noexcept
{
    (co_await CoroUtils::when_all_sequence(sendCommand(
         std::get<Indexes>(commandSequence).command.data(),
         std::get<Indexes>(commandSequence).command.size())),
     ...);
}
```
Перейдем к рассмотрению используемых примитивов, а именно `CoroUtils::when_all_sequence` и `CoroUtils::VoidTask`.

### 6. Реализуем when_all_sequence
Прежде всего- зачем он необходим? В общем случае- когда мы хотим вызвать `co_await` для всех переданных аргументов.

Как было показано в примере выше, у нас есть необходимость распаковать `std::tuple` команд. Или же, мы не хотим писать несколько раз `co_await` друг-за другом. Например, в случае отправки команды установки экранной области, нам необходимо передать координаты по X/Y.Фрагмент отправки имеет вид:
```cpp
static std::array xAxisCommand = std::array{static_cast<std::uint8_t>(0x2a),
                                            static_cast<std::uint8_t>(xa >> 24),
                                            static_cast<std::uint8_t>(xa >> 16),
                                            static_cast<std::uint8_t>(xa >> 8),
                                            static_cast<std::uint8_t>(xa)};
static std::array yAxisCommand = std::array{static_cast<std::uint8_t>(0x2b),
                                            static_cast<std::uint8_t>(ya >> 24),
                                            static_cast<std::uint8_t>(ya >> 16),
                                            static_cast<std::uint8_t>(ya >> 8),
                                            static_cast<std::uint8_t>(ya)};
co_await sendCommand(xAxisCommand.data(), xAxisCommand.size());
co_await sendCommand(yAxisCommand.data(), yAxisCommand.size());
```

Предположим, что два подряд `co_await` это не проблема. Но что делать, если их станет больше? Например, в случае распаковки `std::tuple` с дескрипторами команд нам необходимо вызвать co_await для каждого дескриптора. Получается, для каждого элемента прийдется писать `co_await std::get<N>`? Не порядок.
Для данного варианта можно применить fold-expression из С++17, с помощью которых вызвать `co_await` для каждого переданного аргумента.
При этом, все переданные задачи мы можем сохранить в `std::tuple`.
Приведем реализацию `WhenAllSequence` с комментариями:
```cpp
template <typename... Tasks> struct WhenAllSequence {
  //  Хранилище переданных задач
  std::tuple<Tasks...> m_taskList;

  explicit WhenAllSequence(Tasks &&... tasks) noexcept
      : m_taskList(std::move(tasks)...) {}

  explicit WhenAllSequence(std::tuple<Tasks...> &&tasks) noexcept
      : m_taskList(std::move(tasks)) {}

  bool await_ready() const noexcept {
    //Возвращаем false, т.к. вызов await_suspend долежн быть выполнен. Еси
    //вернуть true- приостановка сопрограммы выполнена не будет, тело
    //await_suspend вызвано не будет.
    return false;
  }

  void await_suspend(stdcoro::coroutine_handle<> handle) noexcept {
    // при вызове co_await будет выполнен вызов launchAll, в котором компиляторм
    // для каждого элемента std::tuple был сгенериррован вызов co_await
    co_await launchAll(
        std::make_integer_sequence<std::size_t, sizeof...(Tasks)>{});
    handle.resume();
  }

  template <std::size_t... Indexes>
  VoidTask launchAll(std::integer_sequence<std::size_t, Indexes...>) {
    // ИСпользуя fold-expression из C++17 - вызываем co_await для каждого
    // элемента tuple
    (co_await std::get<Indexes>(m_taskList), ...);
  }

  void await_resume() noexcept {}
};

template <typename... Args> auto when_all_sequence(Args &&... args) noexcept {
  // конструируем WhenAllSequence от переданных аргументов, при этом из
  // аргументов формируем tuple.
  return WhenAllSequence{std::make_tuple(std::move(args)...)};
}

} // namespace CoroUtils
```

Таким образом, получаем возможность не дублировать написание `co_await` для последовательно выполняемых сопрограмм. 

В данной реализации у нас появился возвращаемый тип `VoidTask`. Он нам необходим для приостановки выполнения `await_suspend` т.к. в ином случае при выполнении `co_await` для первого из переданных аргумнетов в `launchAll` будет выполнено возващение на вызывающую сторону, после чего вызов `handle.resume()` что не совсем соотвествует ожидаемому результату.Восстановление ожидающей сопрограммы должно быть выполнено только после окончания работы всех переданных.

Рассмотрим реализацию типа `VoidTask`.
Данный тип представляет собой "ленивую" задачу которая не выполняется до момента вызова на ней оператора `co_await`. Изначально задача приостановлена. Рассмотрим небольшой пример ее работы прежде чем описывать детали реализации.

```cpp

VoidTask lazyTask()
{
    std::cout<<"I was called\n";
    co_return;
}
int main()
{
    auto lazy = lazyTask();

    return 0;
}
```
Если запустить на wandbox - получим следующий вывод:
```
Start
0
Finish
```
Т.е. тело сопрограммы не было выполнено.
Для того, чтобы выполнить тело сопрограммы - необходимо добавить вызов `co_await` и добавить реализацию `promise_type` для сопрограммы, в которой будет выполнен `co_await`:

```cpp
struct Promise
{
    auto initial_suspend() noexcept
    {
        return std::suspend_never{};
    }
    auto final_suspend() noexcept
    {
        return std::suspend_never{};
    }

    void get_return_object()
    {
    }
    void return_void()
    {
    }

    void unhandled_exception()
    {
        while (1)
        {
        }
    }
};

template <typename... Args> struct std::coroutine_traits<void, Args...>
{
    using promise_type = Promise;
};

void taskEval()
{
    auto lazy = lazyTask();
    co_await lazy;
}
int main()
{   
    taskEval();
    return 0;
}
```

Таким образом, мы получили "ленивую" сопрограмму.

### 7. Как работает Task из cppcoro

`VoidTask` будет частичным примером из библиотеки cppcoro, т.к. в ее реализации `VoidTask` это специализация шаблонного класса `Task` вида `Task<void>`. Разберемся, как он устроен и как он работает.

Прежде всего, для сопрограммы необходимо реализовать `promise_type`.  В нашем случае, т.к. сопрограмма приостанавливает свое выполнение после создания- у `promise_type` вызов `initial_suspend` должен вернуть `std::suspend_always`. Отметим, что так-же `promise_type` должен реализовать обработку поведения в случае выброса необработанного исключения(в нашем случае можем уйти в `std::terminate`), и определить тип возвращаемого объекта наружу, т.е. реализовать метод `get_return_object`.
```cpp
struct task_promise
    {
        task_promise() noexcept = default;
        void return_void() noexcept
        {
        }
        void unhandled_exception() noexcept
        {
            std::terminate();
        }
        VoidTask get_return_object() noexcept
        {
            return VoidTask{std::coroutine_handle<task_promise>::from_promise(*this)};
        }

        auto initial_suspend() noexcept
        {
            return std::suspend_always{};
        }
    };
```

В свою очередь, VoidTask должен определить у себя оператор `co_await` для возможности его вызова.

`operator co_await` должен вернуть на вызвающую сторону `task_promise`, который имеет возможность восстановить выполнение приостановленной сопрограммы и дополнительно установить `continuation`, т.е. сопрограмму, которая будет восстановлена после окончания работы текущей сопрограммы.
```cpp
    struct task_awaitable
    {
        task_awaitable(std::coroutine_handle<promise_type> coroutine) : m_coroutine{coroutine}
        {
        }
        bool await_ready() const noexcept
        {
            return !m_coroutine || m_coroutine.done();
        }
        void await_suspend(std::coroutine_handle<> awaitingRoutine)
        {
            // Подробное описание, почему выполняется сначала resume и только поле этого установка continuation :
            // https://github.com/lewissbaker/cppcoro/blob/a87e97fe5b6091ca9f6de4637736b8e0d8b109cf/include/cppcoro/task.hpp#L314

            m_coroutine.resume();
            m_coroutine.promise().set_continuation(awaitingRoutine);
        }

        void await_resume()
        {
        }

        std::coroutine_handle<promise_type> m_coroutine;
    };
```
Необходимо реализовать у `promise` метод для установки `continuation` и так-же добавить возможность вызова `continuation`.

Реализация установки `continuation` представляет собой дин метод:
```cpp
void set_continuation(std::coroutine_handle<> continuation)
{
    m_continuation = continuation;
}
```
Для вызова установленного `continuation` необходимо реализовать у promise метод `final_suspend`. В методе `final_suspend` вместо `std::suspend_always/std::suspend_never` можно вернуть пользовательский Awaitable-тип, для которого будет сгенерирован вызов `co_await`.

```cpp
struct final_awaitable
{
    bool await_ready() noexcept
    {
        return false;
    }
    template <typename TPromise>
    void await_suspend(std::coroutine_handle<TPromise> coroutine) noexcept
    {
        task_promise& promise = coroutine.promise();
        if (promise.m_continuation)
        {
            promise.m_continuation.resume();
        }
    }

    void await_resume() noexcept
    {
    }
};
```

Рассмотрим полную реализацию с комментариями для основных моментов:

```cpp
#include <coroutine>
#include <iostream>

struct VoidTask
{
    struct task_promise;
    using promise_type = task_promise;

    struct task_promise
    {
        task_promise() noexcept = default;
        //Сопрограмма ничего не возвращает. return_void
        void return_void() noexcept
        {
        }
        // При перехвате необработанного исключения - std::terminate
        void unhandled_exception() noexcept
        {
            std::terminate();
        }
        //Возвращаемый на вызывающую сторону объект - VoidTask с переданным в конструктор
        //coroutine_handle
        VoidTask get_return_object() noexcept
        {
            return VoidTask{std::coroutine_handle<task_promise>::from_promise(*this)};
        }

        // Изначально сопрограмма приостановлена
        auto initial_suspend() noexcept
        {
            return std::suspend_always{};
        }

        struct final_awaitable
        {
            bool await_ready() noexcept
            {
                // await_ready - false, вызов тела await_suspend является необходимым
                return false;
            }
            template <typename TPromise>
            void await_suspend(std::coroutine_handle<TPromise> coroutine) noexcept
            {
                //получаем promise из сопрограммы. если у него установлен continuation, т.е.
                //сопрограмма в которой было приостанолвено выполнение- восстанавливаем ее работу.
                task_promise& promise = coroutine.promise();
                if (promise.m_continuation)
                {
                    promise.m_continuation.resume();
                }
            }

            void await_resume() noexcept
            {
            }
        };

        void set_continuation(std::coroutine_handle<> continuation)
        {
            m_continuation = continuation;
        }

        auto final_suspend() noexcept
        {
            return final_awaitable{};
        }

        std::coroutine_handle<> m_continuation;
    };

    struct task_awaitable
    {
        task_awaitable(std::coroutine_handle<promise_type> coroutine) : m_coroutine{coroutine}
        {
        }
        bool await_ready() const noexcept
        {
            return !m_coroutine || m_coroutine.done();
        }
        void await_suspend(std::coroutine_handle<> awaitingRoutine)
        {
            m_coroutine.resume();
            m_coroutine.promise().set_continuation(awaitingRoutine);
        }

        void await_resume()
        {
        }

        std::coroutine_handle<promise_type> m_coroutine;
    };

    VoidTask(std::coroutine_handle<task_promise> suspendedCoroutine)
        : m_coroutine{suspendedCoroutine}
    {
    }

    ~VoidTask()
    {
        // т.к. мы возвращали для initial_suspend у promise_type std::suspend_always -
        // ответственность за удаление coroutine handle остается на нас.
        if (m_coroutine)
            m_coroutine.destroy();
    }

    bool await_ready() const noexcept
    {
        return !m_coroutine || m_coroutine.done();
    }

    auto operator co_await() noexcept
    {
        return task_awaitable{m_coroutine};
    }

    void await_resume()
    {
    }

    std::coroutine_handle<promise_type> m_coroutine;
};
```

### 8. Как это тестировать?
Реализация SPI-драйвера представляет собой шаблонный класс, в который можно передать backend, который будет использоваться для передачи. Решение было принято с целью повышения тестопригодности модуля. В целом, пользователь работает в основном с несколькими методами:

```cpp
void transmitBuffer(
    const std::uint8_t* _pBuffer,
    std::uint16_t _pBufferSize,
    void* _pUserData,
    bool _restoreInSpiCtx) noexcept
{
    // установили coroutine_handle
    m_coroHandle = std::coroutine_handle<>::from_address(_pUserData);
    //установили вызов, который будет вызван по окончанию передачи в конкретной реализации SPI
    m_backendImpl.setTransactionCompletedHandler([this] { transmitCompleted(); });

    const size_t TransferBufferSize = _pBufferSize;
    const size_t FullDmaTransactionsCount = TransferBufferSize / DmaBufferSize;
    const size_t ChunkedTransactionsBufSize = TransferBufferSize % DmaBufferSize;
    const bool ComputeChunkOffsetWithDma = FullDmaTransactionsCount >= 1;

    // сформировали контекст транзакции
    TransactionContext newContext{.restoreInSpiCtx = _restoreInSpiCtx,
                                  .computeChunkOffsetWithDma = ComputeChunkOffsetWithDma,
                                  .pDataToTransmit = _pBuffer,
                                  .fullDmaTransactionsCount = FullDmaTransactionsCount,
                                  .chunkedTransactionBufSize = ChunkedTransactionsBufSize,
                                  .completedTransactionsCount = 0};

    m_transmitContext = std::move(newContext);

    // выполнили передачу данных
    if (FullDmaTransactionsCount)
    {
        --m_transmitContext.fullDmaTransactionsCount;
        m_backendImpl.sendChunk(_pBuffer, DmaBufferSize);
    }
    else
    {
        m_transmitContext.chunkedTransactionBufSize = 0;
        m_backendImpl.sendChunk(_pBuffer, _pBufferSize);
    }
}
```

По окончанию передачи данных, в реализации backend вызвается `TransactionCompletedHandler`. Рассмотрим фрагмент реализации для Nordic:
```cpp
template <typename PeripheralInstance> class NordicSpi
{

public:
    using This_t = NordicSpi<PeripheralInstance>;
    NordicSpi() noexcept
    {

        nrfx_spim_config_t spiConfig{};

        // конфигурация SPI пропущена .... //
        //инициализация модуля SPIM. если вместо spimEventHandlerThisOne и this передать nullptr и
        //nullptr - передача будет выполнена без использования EasyDMA, т.е. в блокирующем режиме
        APP_ERROR_CHECK(nrfx_spim_init(
            &SpiInstance::HandleStorage[PeripheralInstance::HandleIdx],
            &spiConfig,
            spimEventHandlerThisOne,
            this));
    }

    void sendChunk(const std::uint8_t* _pBuffer, const size_t _bufferSize) noexcept
    {
        // формирование дескриптора на передачу данных
        nrfx_spim_xfer_desc_t xferDesc = NRFX_SPIM_XFER_TX(_pBuffer, _bufferSize);

        // выполнение транзакции
        nrfx_err_t transmissionError = nrfx_spim_xfer(
            &SpiInstance::HandleStorage[PeripheralInstance::HandleIdx], &xferDesc, 0);
        APP_ERROR_CHECK(transmissionError);
    }

    void xferChunk(
        std::span<const std::uint8_t> _transmitArray,
        std::span<std::uint8_t> _receiveArray)
    {
        // формирование transmit-receive транзакции
        nrfx_spim_xfer_desc_t xferDesc = NRFX_SPIM_XFER_TRX(
            _transmitArray.data(),
            _transmitArray.size(),
            _receiveArray.data(),
            _receiveArray.size());

        nrfx_err_t transmissionError = nrfx_spim_xfer(
            &SpiInstance::HandleStorage[PeripheralInstance::HandleIdx], &xferDesc, 0);
        APP_ERROR_CHECK(transmissionError);
    }

    using TTransactionCompletedHandler = std::function<void()>;
    void setTransactionCompletedHandler(const TTransactionCompletedHandler& _handler) noexcept
    {
        m_transactionCompleted = _handler;
    }

private:
    static void spimEventHandlerThisOne(nrfx_spim_evt_t const* _pEvent, void* _pContext) noexcept
    {
        // данный обработчик вызывается по окончании передачи данных при помощи EasyDMA
        if (_pEvent->type == NRFX_SPIM_EVENT_DONE)
        {
            // вызываем ранее установленный callback на драйвере верхнего уровня.
            auto pThis = reinterpret_cast<This_t*>(_pContext);
            pThis->m_transactionCompleted();
        }
    }

public:
    TTransactionCompletedHandler m_transactionCompleted;
};

```

В свою очередь, для тестирования драйвера верхнего уровня необходимо релизовать соответствующий `stub-backend` + реализовать тесты.
Рассматривамеые тестовые сценарии:
* передача блока данных меньше размера DMA буфера
* передача блока данных рамзером с DMA буфер
* передача нескольких блоков данных размером с DMA буфер
* передача нескольких блоков размером с DMA буфер и неполного блока

### 9. Добавляем параметрические тесты в GTest

Тестирование будем производить с использованием GTest фреймворка. С целью избегания copy-paste для тестов с вышеупомянутыми сценариями- воспользуемся функционалом, позволяющим инстанцировать параметрические тесты.

Для поддержки параметрических тестов в фикстуре необходимо добавить еще однин класс, от которого идет наследование помимо базового `::testing::Test`. Для поддержки параметрических тестов необходимо добавить наследование от `::testing::WithParamInterface`.

В нашем случае это будет `std::tuple` вида:
```cpp
public ::testing::WithParamInterface<std::tuple<std::uint16_t, std::string_view>>
```

Где `std::string_view` будет соответствовать названию теста, а `std::uint16_t` - использоваться для задавания размера тестового буфера данных для отправки.

Реализация stub-backend для SPI драйвера представляет собой хранилище spi-транзакций, которые добавляются при каждом вызове `sendChunk`. После чего, по окончании передачи данных может быть выполнено преобразование из отправленных транзакций в полноценный буфер с целью сравнения данных, которые были поставлены на отправку и данных, которы были переданы в драйвер низкого уровня.

Реализация данных функций представлена ниже:

```cpp
void sendChunk(const std::uint8_t* _pBuffer, const size_t _bufferSize) noexcept
{
    BusTransactionsTransmit.emplace_back(_pBuffer, _bufferSize);
    m_completedTransaction();
}
using TDataStream = std::vector<std::byte>;
TDataStream getTransmittedData() const
{
    TDataStream stream;
    std::for_each(
        BusTransactionsTransmit.cbegin(),
        BusTransactionsTransmit.cend(),
        [&stream](const auto& _transaction) {
            const auto& [pArray, blockSize] = _transaction;
            auto arraySpan = std::span{pArray, blockSize};
            std::transform(
                arraySpan.begin(),
                arraySpan.end(),
                std::back_inserter(stream),
                [](std::uint8_t _dataByte) { return std::byte{_dataByte}; });
        });
    return stream;
}
```
 Для работы с параметрическими тестами необходимо добавить его определение + инстанцирование.

Определение параметрического теста будет иметь вид:

```cpp
TEST_P(SpiDriverTest, CheckRandomSequenceWithLengthTransmissionCorrect)
{
    // получаем размер последовательности
    const std::uint16_t TransactionLength{std::get<0>(GetParam())};
    TDataStream ExpectedStream{TransactionLength};

    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<> distribution(0x00, 0xFF);
    // формируем случайную посылку
    std::ranges::generate(ExpectedStream, [&distribution, generator]() mutable {
        return std::byte(distribution(generator));
    });

    co_await sendChunk(
        reinterpret_cast<const std::uint8_t*>(ExpectedStream.data()), ExpectedStream.size());
    // проверяем соответствие данных, которые должны были быть переданы данным, которые были отправлены в spi-backend
    EXPECT_EQ(TransactionsToDataStream(), ExpectedStream);
}

```

Инстанцирование параметрического теста представлено на фрагменте ниже:

```cpp
INSTANTIATE_TEST_SUITE_P(
    SpiDriverTesting,
    SpiDriverTest,
    ::testing::Values(
        std::make_tuple(Null, "Null"),
        std::make_tuple(SmallerThanSingleDmaTransaction, "SmallerThanSingleDmaTransaction"),
        std::make_tuple(EqualsToSingleDmaTransaction, "EqualsToSingleDmaTransaction"),
        std::make_tuple(ThreeDmaTransactions, "ThreeDmaTransactions"),
        std::make_tuple(SingleDmaAndChunk, "SingleDmaAndChunk"),
        std::make_tuple(ThreeDmaAndChunk, "ThreeDmaAndChunk"),
        std::make_tuple(StressChunked, "StressChunked")),
    [](const auto& testParam) {
        const auto& suiteName = std::get<1>(testParam.param);
        return std::string(suiteName.data());
    });
```

Переданная лямбда позволяет отформатировать название теста, который выполняется.


### 10. Добавляем черновой вариант драйвера для SPI-FLASH
Рассмотрим добавление драйвера для SPI-FLASH памяти. На первом этапе, рассмотрм получение JEDEC ID и device ID. Условия те-же самые, использовать DMA, ассинхронно, не блокироваться на ожидании событий.

Результат, который мы хотим получить, выглядит следующим образом:
```cpp
void Board::initBoardSpiFlash() noexcept
{
    m_pFlashDriver = std::make_unique<Hal::TFlashDriver>();
    if (m_pFlashDriver)
    {
        const std::uint32_t JedecId = co_await m_pFlashDriver->requestJEDEDCId();
        LOG_DEBUG("Jedec Id is:");
        LOG_DEBUG_ENDL(fmt::format("{:#04x}", JedecId));

        const std::span<std::uint8_t> DeviceId = co_await m_pFlashDriver->requestDeviceId();
        LOG_DEBUG_ENDL(fmt::format("{:02X}", fmt::join(DeviceId, "")));
    }
}
```
Для этого нам необходимо реализовать примитив, с помощью которого мы сможем вернуть значение на вызвающую сторону. Рассмотрим расширенный интерфейс `Task`, а именно необходимые измненения для добавления поддержки возврата значения.
1. Необходимо изменить тип `await_resume` у `task_awaitable`:
```cpp
decltype(auto) await_resume()
{
    return m_coroutine.promise().result();
}
```
2. Добавить метод `.result()` у `promise`:
```cpp
TResult& result()
{
    return m_coroutineResult;
}
```
3. Добавить у `promise` метод `return_value`:
```cpp
void return_value(const TResult& _value)noexcept
{
    m_coroutineResult = _value;
}
```
4. Сделать `Task` шаблонным:
```cpp
template <typename TResult> struct Task
```
5. Добавить member в `promise` для сохранения результата.

Полная реализация измененного `Promise`:
```cpp
struct ResultTaskPromise
{
    ResultTaskPromise() noexcept = default;

    void unhandled_exception() noexcept
    {
        std::terminate();
    }
    Task<TResult> get_return_object() noexcept
    {
        // Изменили тип возвращаемого объекта, теперь это шаблонный Task<Result>
        return Task<TResult>{std::coroutine_handle<ResultTaskPromise>::from_promise(*this)};
    }
    auto initial_suspend() noexcept
    {
        return std::suspend_always{};
    }

    void return_value(const TResult& _value) noexcept
    {
        // добавили метод return value
        m_coroutineResult = _value;
    }

    void set_continuation(std::coroutine_handle<> continuation)
    {
        m_continuation = continuation;
    }

    TResult& result()
    {
        // добавили метод result для возвращения результата
        return m_coroutineResult;
    }

    struct final_awaitable
    {
        bool await_ready() noexcept
        {
            return false;
        }
        template <typename TPromise>
        void await_suspend(std::coroutine_handle<TPromise> coroutine) noexcept
        {
            ResultTaskPromise& promise = coroutine.promise();
            if (promise.m_continuation)
            {
                promise.m_continuation.resume();
            }
        }

        void await_resume() noexcept
        {
        }
    };

    auto final_suspend() noexcept
    {
        return final_awaitable{};
    }

    // добавили поле класса для хранения результата
    TResult m_coroutineResult;
    std::coroutine_handle<> m_continuation;
};
```

### 11. Добавляем чтение JEDEC ID
Для чтения JEDEC ID, который представляет собой std::uint32 необходимо добавить в API spi-flash драйвера метод `requestJedecId`:
```cpp
CoroUtils::Task<std::uint32_t> requestJEDEDCId() noexcept
{
    auto receivedData = co_await prepareXferTransaction(
        std::forward_as_tuple(WindbondCommandSet::ReadJedecId),
        WindbondCommandSet::DummyByte,
        WindbondCommandSet::DummyByte,
        WindbondCommandSet::DummyByte);

    std::uint32_t JedecDeviceId{};
    for (std::size_t i{}; i < WindbondCommandSet::JedecIdLength; ++i)
    {
        JedecDeviceId |= (receivedData[i] << (16 - i * 8));
    }

    co_return JedecDeviceId;
}
```

Идея с std::forward_as_tuple следующая - все что передано в аргументах -  в функции `prepareXferTransaction` будет рассмотрено как команда + количество dummy-bytes которые нужны для принятия команды. Все что после `forward_as_tuple` - количество dummy-bytes для вычитки данных.


Реализация фунеции `prepareXferTransaction` следующая: получаем на вод команду  виде tuple + количество пустых посылок. Далеее, заполняем передащий буфер сначала командой и ее аргументами, после- пустыми посылками. Для возвращаемого значения рассчитываем размер смещения в принмающем буфере, чтобы на сторону клиента драйвера вернулся slice на буфер, где в 0-м элементе лежат необходимые данные.
// TODO, может, есть способ удобнее?
Реализация функции имеет вид:

```cpp
template <typename TCommand, typename... Args>
auto prepareXferTransaction(TCommand&& _command, Args&&... _argList)
{
    auto& transmitBuffer = getSpiBus()->getDmaBufferTransmit();
    auto& receiveBuffer = getSpiBus()->getDmaBufferReceive();
    processTransmitBuffer(transmitBuffer, std::forward<TCommand&&>(_command));

    processTransmitBuffer(
        std::span(
            transmitBuffer.data() + std::tuple_size_v<TCommand>, TSpiBusInstance::DmaBufferSize),
        std::forward_as_tuple(_argList...));

    constexpr std::size_t TransmitSize = std::tuple_size_v<TCommand> + sizeof...(_argList);
    constexpr std::size_t ReceiveSize = TransmitSize;
    constexpr std::size_t Skip = std::tuple_size_v<TCommand>;
    return xferTransaction(
        std::span(transmitBuffer.data(), TransmitSize),
        std::span(receiveBuffer.data(), TransmitSize),
        Skip);
}
```

Где `xferTransaction` представлена в виде:
```cpp
CoroUtils::Task<std::span<std::uint8_t>> xferTransaction(
    std::span<const std::uint8_t> _pTransmitCommand,
    std::span<std::uint8_t> _pReceiveBuffer,
    std::size_t _skipBytes) noexcept
{
    co_await xferChunk(_pTransmitCommand, _pReceiveBuffer);
    co_return std::span(_pReceiveBuffer.data() + _skipBytes, _pReceiveBuffer.size() - _skipBytes);
}

template <
    typename TTRansmitBuffer,
    typename TArgsTuple,
    typename Indexes = std::make_index_sequence<std::tuple_size_v<TArgsTuple>>>
void processTransmitBuffer(TTRansmitBuffer&& _transmitBuffer, TArgsTuple&& _argsTuple)
{
    processTransmitBufferImpl(
        std::forward<TTRansmitBuffer&&>(_transmitBuffer),
        std::forward<TArgsTuple&&>(_argsTuple),
        Indexes{});
}

template <typename TTRansmitBuffer, typename TArgsTuple, std::size_t... Index>
void processTransmitBufferImpl(
    TTRansmitBuffer&& _transmitBuffer,
    TArgsTuple&& _argsTuple,
    std::index_sequence<Index...>)
{
    ((_transmitBuffer[Index] = std::get<Index>(_argsTuple)), ...);
}
```
### 12. Добавляем чтение device id
Для поддержки чтения device-id необходимо добавить в API драйвера следующую функцию:
```cpp
CoroUtils::Task<std::span<std::uint8_t>> requestDeviceId() noexcept
{
    auto receivedData = co_await prepareXferTransaction(
        std::forward_as_tuple(
            WindbondCommandSet::ReadUniqueId,
            WindbondCommandSet::DummyByte,
            WindbondCommandSet::DummyByte,
            WindbondCommandSet::DummyByte,
            WindbondCommandSet::DummyByte),

        WindbondCommandSet::DummyByte,
        WindbondCommandSet::DummyByte,
        WindbondCommandSet::DummyByte,
        WindbondCommandSet::DummyByte,
        WindbondCommandSet::DummyByte,
        WindbondCommandSet::DummyByte);
    co_return std::span(receivedData.data(), receivedData.size());
}
```
На сторону пользователя, в данном случае вернется slice на принимающий DMA-буфер SPI. А далее его можно отформатировать с использованием `fmtlib` или же `std::format`, в зависимости от поддерживаемого компилятора. 

### 13. Ожидание окончания выполнения сопрограммы

Иногда может возникнуть необходимость подождать выполнения сопрограммы, т.е. заблокировать выполнение текущего потока до момента, пока не будет завершена сопрограмма. Для этого можно реализовать примитив SyncWait.

Рассмотрим построение этого примитива( в cppcoro он так-же реализован, данный параграф скорее рассмотрение того, как он работает)

Мы хотим получить интерфейс вида:
```cpp
TEST_F(FlashDriverTest, RequestJedecId)
{
    auto jedecId = CoroUtils::syncWait(flashDriver.requestJEDEDCId());
    constexpr std::uint32_t MagicTrashFromRawMemory = 13487565; //  For fun;
    EXPECT_EQ(jedecId, MagicTrashFromRawMemory);
}
```
Т.е. по вызову `CoroUtils::syncWait` заблокироваться до получения результата.

1. Реализуем `syncWait`
необходимо получить тип возвращаемого значения из сопрограммы. Для этого необходимо написать небольшую обертку, которая позволит это выполнить. В нашем случае, возвращаемые типы представляют собой Awaitable-примтивы с доступным `operator co_await`.

Примерный интерфейс `syncWait`:
```cpp
template <typename TCoroutine>
auto syncWait(TCoroutine&& _coroutineTask)->//Необходимо получить возвращаемый тип
```
Для получения возвращаемого типа реализуем структуру `AwaitResultGetter`:
```cpp
template <typename TAwaiter> auto awaiterGetter(TAwaiter&& _awaiter)
{
    return static_cast<TAwaiter&&>(_awaiter).operator co_await();
}

template <typename TAwaitable> struct AwaitResultGetter
{
    using Type = decltype(awaiterGetter(std::declval<TAwaitable>()));
    using Result = decltype(std::declval<Type>().await_resume());
};
```
Где возвращаемый тип может быть получен с помощью вызова `.await_resume` на результате `declval` от awaitable-типа

Вызов `makeSyncWaitTask` представляет собой последовательность вызовов `co_yield co_await`:
```cpp
template <typename TAwaitable, typename TTaskResult = AwaitResultGetter<TAwaitable>::Result>
SyncWaitTask<TTaskResult> makeSyncWaitTask(TAwaitable&& _awaitable)
{
    co_yield co_await _awaitable;
}
```
Где `co_await` приостанавливает текущий вызов, а `co_yield` используется для сохранения результата выполненной сопрограммы.

Блокирование текущего потока выполнения реализовано за счет установки `BlockingEvent` в котором при вызове `.wait` происходит lockна `condition_wariable` до момента, пока не будет установлен `atomic_bool` флаг:
```cpp
class BlockingEvent
{
public:
    void wait()
    {
        std::unique_lock<std::mutex> lock(mutex);
        condEvent.wait(lock, [this] { return m_isSet.load(std::memory_order_acquire); });
    }

    void set()
    {
        m_isSet.store(true, std::memory_order_release);
        condEvent.notify_all();
    }

private:
    std::atomic_bool m_isSet = false;
    std::mutex mutex;
    std::condition_variable condEvent;
};
```
Полная реализация `SyncWait`:
```cpp
template <typename TResultType> struct SyncWaitTask
{
    struct SyncTaskPromise;
    using promise_type = SyncTaskPromise;
    using TResultRef = TResultType&&;

    SyncWaitTask(std::coroutine_handle<SyncTaskPromise> _suspendedRoutine)
        : m_suspendedRoutine{_suspendedRoutine}
    {
    }
    ~SyncWaitTask()
    {
        if (m_suspendedRoutine)
            m_suspendedRoutine.destroy();
    }

    struct FinalAwaitable
    {
        bool await_ready() noexcept
        {
            return false;
        }
        template <typename TPromise>
        void await_suspend(std::coroutine_handle<TPromise> coroutine) noexcept
        {
            // по окончанию работы сопрограммы устанавливаем  blockingEvent  в set, тем самым
            // восстанавливая текущий поток выполнения
            SyncTaskPromise& promise = coroutine.promise();
            promise.m_event->set();
        }
        void await_resume() noexcept
        {
        }
    };

    struct SyncTaskPromise
    {

        auto get_return_object() noexcept
        {
            return SyncWaitTask{std::coroutine_handle<SyncTaskPromise>::from_promise(*this)};
        }
        void start(BlockingEvent* _pEvent) noexcept
        {
            m_event = _pEvent;
            std::coroutine_handle<SyncTaskPromise>::from_promise(*this).resume();
        }
        auto initial_suspend() noexcept
        {
            return std::suspend_always{};
        }

        auto final_suspend() noexcept
        {
            return FinalAwaitable{};
        }

        auto yield_value(TResultRef result) noexcept
        {
            // для поддержки operator co_yield
            m_value = std::addressof(result);
            return final_suspend();
        }

        decltype(auto) value() noexcept
        {
            return static_cast<TResultRef>(*m_value);
        }

        void return_void() noexcept
        {
        }

        void unhandled_exception()
        {
            std::terminate();
        }

        BlockingEvent* m_event;
        std::remove_reference_t<TResultType>* m_value;
    };

    TResultType&& result() noexcept
    {
        return m_suspendedRoutine.promise().value();
    }

    void await_resume()
    {
    }

    void start(BlockingEvent& _event)
    {
        m_suspendedRoutine.promise().start(&_event);
    }
    std::coroutine_handle<SyncTaskPromise> m_suspendedRoutine;
};

template <typename TAwaitable, typename TTaskResult = AwaitResultGetter<TAwaitable>::Result>
SyncWaitTask<TTaskResult> makeSyncWaitTask(TAwaitable&& _awaitable)
{
    co_yield co_await _awaitable;
}

Полный пример на котором можно экспериментировать:
https://godbolt.org/z/8YoxPPYsW

Пример с использованием SPI-интерфейса для инициализации дисплея. Можно экспериментировать.
https://wandbox.org/permlink/dsL64oCgPxEEph81

```