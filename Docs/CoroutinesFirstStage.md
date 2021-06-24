### Practical C++20 coroutines notes for ARM Cortex-M

Появилась идея в домашнем проекте попробовать использовать сопрограммы из С++20 на маленькой железке. В качестве модуля для экспериментов был выбран E73 NRF52832. Из инструментария, который использовался в процессе разработки- arm-gcc-gnu-none-eabi 10.2, MSVC для проверки идей и прогона тестов на Windows-платформе.
Изначально было в планах продемонстрировать на чем-то концепцию и как именно их можно было применять. Была идея адаптирования примера в виде мигания светодиодиком. Но он был слишком простой. Необходимо было придумать что-то более сложное и более полезное, что ли. Таким образом и появилась идея переписать драйвер дисплея и пары фрагментов SPI-FLASH в проекте-долгострое.

Небольшой план, что будет в заметке:

1. Предыстория с транзакциями
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
Заметка предполагает базовое знакомство читателя с сопрогрмаммами / их синтаксисом. В силу наличия более подробных статей на тему деталей реализации сопрограмм и их устройства рекомендуются к прочтению следующие материалы:

* [YOUR FIRST COROUTINE,panicsoftware](https://blog.panicsoftware.com/your-first-coroutine/)

Серия статей от автора библиотеки [cppcoro](https://github.com/lewissbaker/cppcoro)
* https://lewissbaker.github.io/2017/09/25/coroutine-theory
* https://lewissbaker.github.io/2017/11/17/understanding-operator-co-await
* https://lewissbaker.github.io/2018/09/05/understanding-the-promise-type
* https://lewissbaker.github.io/2020/05/11/understanding_symmetric_transfer

В заметке изложение материала может показаться непоследовательным. Предложения буду рад увидеть в виде issues или же в комментариях/сообщениях в Telegram.

Что будет рассмотрено:
* драйвер дисплея с использованием сопрограмм, с использованием таблицы инициализации на базе std::tuple и классического варианта на базе массива команд.
* фрагмент драйвера для SPI-FLASH памяти
* написание тестов на драйвер SPI с использованием параметрических тестов в GTest
* Рассмотрение работы и реализация нескольких примитивов из cppcoro библиотеки.

### 1. Предыстория с транзакциями

Изначально, идея переписывания с подхода в виде транзакций появилась как только возникла необходимость расширения транзакционности read-транзакциями. Для формирования очереди отправки этот подход был достаточно удобным, но для очереди приема получалось что-то вроде callback-hell подхода.

В общих чертах, транзакционный подход представлял собой следующую идею:
```cpp
template <typename... Args> void sendCommand(std::uint8_t command, Args... commandArgs) noexcept
{
    sendCommand(command);
    sendChunk(static_cast<std::uint8_t>(commandArgs)...);
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

1. Выставить состояние порта D/C для дисплея для выбора типа принимаемых данных (команда или данные) 
2. Сформировать DMA- транзакцию
3. По ее окончанию выполнить следующую отправку, если блок данных был не полностью отправлен
4. Или вернуть состояние порта D/C в исходное состояние и перейти к обработке следующей транзакции

Недостатки стали проявляться при попытке реализации драйвера для SPI-FLASH которая должна была быть использована в связке с Little FS. Где-то в тот-же период времени было найдено предложение в стандарт С++20 по сопрограммам, просмотрена серия мотивирующих статей:
* [Готовимся к С++20. Coroutines TS на реальном примере](https://habr.com/ru/company/yandex/blog/420861/)

* [Асинхронность: назад в будущее](https://habr.com/ru/post/201826/)
* [Асинхронность 2: телепортация сквозь порталы](https://habr.com/ru/company/yandex/blog/240525/)
* [Асинхронность 3: Субъекторная модель](https://habr.com/ru/post/340732/)

И было принято решение о переписывании на сопрограммы части существующих драйверов.

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
auto sendCommand(const std::uint8_t* pBuffer, std::size_t bufferSize) noexcept
{
    const std::uint8_t* commandBuf = pBuffer;
    const std::uint8_t* ArgBuf = pBuffer + 1;
    const std::uint16_t ArgsBufferSize = static_cast<std::uint16_t>(bufferSize - 1);

    return CoroUtils::when_all_sequence(
        sendCommandImpl(commandBuf),
        ArgsBufferSize > 0 ? sendChunk(ArgBuf, ArgsBufferSize) : sendChunk(nullptr, 0));
}

auto sendChunk(const std::uint8_t* pBuffer, std::size_t bufferSize) noexcept
{
    return Awaiter{.pTransmitBuffer = pBuffer,
                   .pBaseDisplay = this,
                   .bufferSize = static_cast<std::uint16_t>(bufferSize)};
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

Как может выглядеть процедура отправки дисплейного буфера? Т.к. в проекте используется библиотека LVGL - фреймбуфер может быть non-screen-sized, т.е. не полностью соответствовать размеру буфера экрана, что позволяет выполнять отрисовку фрагментами.(Иногда может не быть возможности поместить полностью в память буфер дисплея)

Для реализации функции отправки нам необходимо выполнить отправку команд на установку области экрана, в которую будет осуществлена отрисовка, после чего отправить команду на запись в память дисплея и выполнить отправку дисплейного буфера.
Что-же. В синхронном варианте, данный код мог бы иметь вид:
```cpp
void fillRectangle(
    std::uint16_t x,
    std::uint16_t y,
    std::uint16_t width,
    std::uint16_t height,
    TBaseSpiDisplay::TColor* colorToFill) noexcept
{

    const std::uint16_t DisplayHeight = TBaseSpiDisplay::getHeight();
    const std::uint16_t DisplayWidth = TBaseSpiDisplay::getWidth();

    const bool isCoordsValid{!((x >= DisplayWidth) || (y >= DisplayHeight))};
    if (isCoordsValid)
    {
        //Определяем размеры буфера для отправки
        const size_t BytesSizeX = (width - x + 1);
        const size_t BytesSizeY = (height - y + 1);
        const size_t BytesSquare = BytesSizeX * BytesSizeY;
        const size_t TransferBufferSize = (BytesSquare * sizeof(typename TBaseSpiDisplay::TColor));

        //Формируем область экрана для обновления
        setAddrWindow(x, y, width, height);

        static std::uint8_t RamWriteCmd{0x2C};
        // Команда на запись в экранный буфер
        TBaseSpiDisplay::sendCommandImplFast(&RamWriteCmd);

        //Устанавликаем порт Data/Command в режим работы с данными(все что передано в дисплей
        //воспринимается, как данные, а не как команды)
        TBaseSpiDisplay::setDcPin();
        // Отправляем дисплейный буфер
        TBaseSpiDisplay::sendChunk(
            reinterpret_cast<const std::uint8_t*>(colorToFill), TransferBufferSize);
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
co_await setAddrWindow(x, y, width, height); // <=============== co_await here

static std::uint8_t RamWriteCmd{0x2C};
// Команда на запись в экранный буфер
co_await TBaseSpiDisplay::sendCommandImplFast(&RamWriteCmd); // <=============== co_await here

TBaseSpiDisplay::setDcPin();
// Отправляем дисплейный буфер
co_await TBaseSpiDisplay::sendChunk(
    reinterpret_cast<const std::uint8_t*>(colorToFill),
    TransferBufferSize); // <=============== co_await here

TBaseSpiDisplay::resetDcPin();

TBaseSpiDisplay::onRectArreaFilled.emitLater();

```

Добавлением в трех строках `co_await` мы получили ассинххронный код. Остается только дописать немного примитивов, которые будут нам необходимы, чтобы это все заработало. А именно, реализовать притивы `when_all_sequence` для запуска последовательности и `Task` для вызова `co_await` на возвращаемом результате функции `setAddrWindow`.

### 5. Для любителей посложнее - итерация на std::tuple<CommandDescriptor>
Данная идея была первой. Представляем таблицу команд инициализации диспллея в виде std::tuple который в свою очередь состоял бы из Дескрипторов команд.
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
    //Возвращаем false, т.к. вызов await_suspend долежн быть выполнен. Если
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
    // Используя fold-expression из C++17 - вызываем co_await для каждого
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

В данной реализации у нас появился возвращаемый тип `VoidTask`. Он нам необходим для приостановки выполнения `await_suspend` т.к. в ином случае при выполнении `co_await` для первого из переданных аргументов в `launchAll` будет выполнено возващение на вызывающую сторону, после чего вызов `handle.resume()` что не совсем соотвествует ожидаемому результату. Восстановление ожидающей сопрограммы должно быть выполнено только после окончания работы всех переданных задач.

Рассмотрим реализацию типа `VoidTask`.
Данный тип представляет собой "ленивую" задачу которая не выполняется до момента вызова на ней оператора `co_await`. Изначально задача приостановлена. Рассмотрим небольшой пример ее работы, прежде чем описывать детали реализации.

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

`operator co_await` должен вернуть на вызвающую сторону `task_awaitable`, который имеет возможность восстановить выполнение приостановленной сопрограммы и дополнительно установить `continuation`, т.е. сопрограмму, которая будет восстановлена после окончания работы текущей сопрограммы.
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
        auto await_suspend(std::coroutine_handle<> awaitingRoutine)
        {
            // Используем symmetric-transfer
            // Подробнее можно ознакомиться:
            // https://lewissbaker.github.io/2020/05/11/understanding_symmetric_transfer

            m_coroutine.promise().set_continuation(awaitingRoutine);
            return m_coroutine;
        }

        void await_resume()
        {
        }

        std::coroutine_handle<promise_type> m_coroutine;
    };
```
Необходимо реализовать у `promise` метод для установки `continuation` и так-же добавить возможность вызова `continuation`.

Реализация установки `continuation` представляет собой метод:
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
    auto await_suspend(std::coroutine_handle<TPromise> coroutine) noexcept
    {
        task_promise& promise = coroutine.promise();
        return promise.m_continuation;
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
            auto await_suspend(std::coroutine_handle<TPromise> coroutine) noexcept
            {
                // https://lewissbaker.github.io/2020/05/11/understanding_symmetric_transfer
                task_promise& promise = coroutine.promise();
                return promise.m_continuation;
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
        auto await_suspend(std::coroutine_handle<> awaitingRoutine)
        {
            m_coroutine.promise().set_continuation(awaitingRoutine);
            return m_coroutine;
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
    const std::uint8_t* pBuffer,
    std::uint16_t pBufferSize,
    void* pUserData,
    bool restoreInSpiCtx) noexcept
{
    // установили coroutine_handle
    m_coroHandle = std::coroutine_handle<>::from_address(pUserData);
    //установили вызов, который будет вызван по окончанию передачи в конкретной реализации SPI
    m_backendImpl.setTransactionCompletedHandler([this] { transmitCompleted(); });

    const size_t TransferBufferSize = pBufferSize;
    const size_t FullDmaTransactionsCount = TransferBufferSize / DmaBufferSize;
    const size_t ChunkedTransactionsBufSize = TransferBufferSize % DmaBufferSize;
    const bool ComputeChunkOffsetWithDma = FullDmaTransactionsCount >= 1;

    // сформировали контекст транзакции
    TransactionContext newContext{.restoreInSpiCtx = restoreInSpiCtx,
                                  .computeChunkOffsetWithDma = ComputeChunkOffsetWithDma,
                                  .pDataToTransmit = pBuffer,
                                  .fullDmaTransactionsCount = FullDmaTransactionsCount,
                                  .chunkedTransactionBufSize = ChunkedTransactionsBufSize,
                                  .completedTransactionsCount = 0};

    m_transmitContext = std::move(newContext);

    // выполнили передачу данных
    if (FullDmaTransactionsCount)
    {
        --m_transmitContext.fullDmaTransactionsCount;
        m_backendImpl.sendChunk(pBuffer, DmaBufferSize);
    }
    else
    {
        m_transmitContext.chunkedTransactionBufSize = 0;
        m_backendImpl.sendChunk(pBuffer, pBufferSize);
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

    void sendChunk(const std::uint8_t* pBuffer, const size_t bufferSize) noexcept
    {
        // формирование дескриптора на передачу данных
        nrfx_spimxfer_desc_t xferDesc = NRFX_SPIMXFER_TX(pBuffer, bufferSize);

        // выполнение транзакции
        nrfx_err_t transmissionError = nrfx_spimxfer(
            &SpiInstance::HandleStorage[PeripheralInstance::HandleIdx], &xferDesc, 0);
        APP_ERROR_CHECK(transmissionError);
    }

    void xferChunk(
        std::span<const std::uint8_t> _transmitArray,
        std::span<std::uint8_t> _receiveArray)
    {
        // формирование transmit-receive транзакции
        nrfx_spimxfer_desc_t xferDesc = NRFX_SPIMXFER_TRX(
            _transmitArray.data(),
            _transmitArray.size(),
            _receiveArray.data(),
            _receiveArray.size());

        nrfx_err_t transmissionError = nrfx_spimxfer(
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
Рассматриваемые тестовые сценарии:
* передача блока данных меньше размера DMA буфера
* передача блока данных размером с DMA буфер
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
void sendChunk(const std::uint8_t* pBuffer, const size_t bufferSize) noexcept
{
    BusTransactionsTransmit.emplace_back(pBuffer, bufferSize);
    m_completedTransaction();
}

using TDataStream = std::vector<std::byte>;
TDataStream getTransmittedData() const
{
    TDataStream stream;
    std::ranges::for_each(BusTransactionsTransmit, [&stream](const auto& _transaction) {
        const auto& [pArray, blockSize] = _transaction;
        auto arraySpan = std::span{pArray, blockSize};
        std::ranges::transform(arraySpan, std::back_inserter(stream), [](std::uint8_t _dataByte) {
            return std::byte{_dataByte};
        });
    });
    return stream;
}
```
 Для работы с параметрическими тестами необходимо добавить его определение + инстанцирование.
 На данном этапе будет опущена реализация примитива SyncWait, она будет приведена далее. Нам она необходима для ожидания окончания работы сопрограммы.

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

    CoroUtils::syncWait(sendChunk(
        reinterpret_cast<const std::uint8_t*>(ExpectedStream.data()), ExpectedStream.size()));
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

Идея с `std::forward_as_tuple` следующая - все что передано в аргументах -  в функции `prepareXferTransaction` будет рассмотрено как команда + количество dummy-bytes которые нужны для принятия команды. Все что после `forward_as_tuple` - количество dummy-bytes для вычитки данных.


Реализация фунеции `prepareXferTransaction` следующая: получаем на вход команду в виде tuple + количество пустых посылок. Далее, заполняем передащий буфер сначала командой и ее аргументами, передаем, после- пустыми посылками. Для возвращаемого значения возвращаем slice на буфер с принятыми данными

Реализация функции имеет вид:

```cpp
    template <typename TCommand, typename... Args>
    CoroUtils::Task<std::span<std::uint8_t>> prepareXferTransaction(
        TCommand&& command,
        Args&&... argList)
    {
        auto& transmitBuffer = getSpiBus()->getDmaBufferTransmit();
        auto& receiveBuffer = getSpiBus()->getDmaBufferReceive();

        getSpiBus()->setCsPinLow();

        processTransmitBuffer(transmitBuffer, std::forward<TCommand&&>(command));

        constexpr std::size_t CommandSize = std::tuple_size_v<TCommand>;

        co_await transmitChunk(std::span(transmitBuffer.data(), CommandSize));

        constexpr std::size_t DummyListSize = sizeof...(argList);

        processTransmitBuffer(transmitBuffer, std::forward_as_tuple(argList...));

        auto receivedBlockSpan = co_await xferTransaction(
            std::span(transmitBuffer.data(), DummyListSize),
            std::span(receiveBuffer.data(), DummyListSize));

        getSpiBus()->setCsPinHigh();
        co_return std::span(receiveBuffer.data(), DummyListSize);
    }
```

Где `xferTransaction` представлена в виде:
```cpp
    CoroUtils::Task<std::span<std::uint8_t>> xferTransaction(
        std::span<const std::uint8_t> pTransmitCommand,
        std::span<std::uint8_t> pReceiveBuffer) noexcept
    {
        co_await xferChunk(pTransmitCommand, pReceiveBuffer);
        co_return std::span(pReceiveBuffer.data(), pReceiveBuffer.size());
    }

    template <
        typename TTRansmitBuffer,
        typename TArgsTuple,
        typename Indexes = std::make_index_sequence<std::tuple_size_v<TArgsTuple>>>
    void processTransmitBuffer(TTRansmitBuffer&& transmitBuffer, TArgsTuple&& argsTuple)
    {
        processTransmitBufferImpl(
            std::forward<TTRansmitBuffer&&>(transmitBuffer),
            std::forward<TArgsTuple&&>(argsTuple),
            Indexes{});
    }

    template <typename TTRansmitBuffer, typename TArgsTuple, std::size_t... Index>
    void processTransmitBufferImpl(
        TTRansmitBuffer&& transmitBuffer,
        TArgsTuple&& argsTuple,
        std::index_sequence<Index...>)
    {
        ((transmitBuffer[Index] = std::get<Index>(argsTuple)), ...);
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
SyncWaitTask<TTaskResult> makeSyncWaitTask(TAwaitable&& awaitable)
{
    co_yield co_await awaitable;
}
```
Где `co_await` приостанавливает текущий вызов, а `co_yield` используется для сохранения результата выполненной сопрограммы.


При этом, необходимо учесть, что при вызове `SyncWait` на VoidTask у нас возвращаемого результата не будет. Проще всего это реализовать через специализацию шаблона для `Promise`.

Блокирование текущего потока выполнения реализовано за счет установки `BlockingEvent` в котором при вызове `.wait` происходит lock на `condition_wariable` до момента, пока не будет установлен `atomic_bool` флаг:
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
Фрагмент реализации `SyncWait` для типов с вовращаемым результетом не-void:
```cpp
template<typename TResultType>
struct SyncTaskPromise;

template <typename TResultType>
struct SyncWaitTask
{
    using promise_type = SyncTaskPromise<TResultType>;
    using TResultRef = ResultTypeRefHolder<TResultType>::Type;

    SyncWaitTask(stdcoro::coroutine_handle<SyncTaskPromise<TResultType>> suspendedRoutine)
        : m_suspendedRoutine{suspendedRoutine}
    {
    }
    ~SyncWaitTask()
    {
        if (m_suspendedRoutine)
            m_suspendedRoutine.destroy();
    }

    decltype(auto) result() noexcept
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
    stdcoro::coroutine_handle<SyncTaskPromise<TResultType>> m_suspendedRoutine;
};


template<typename TResultType>
struct SyncTaskPromise
{
    using TResultRef = TResultType&&;

    struct FinalAwaitable
    {
        bool await_ready() noexcept
        {
            return false;
        }
        template <typename TPromise>
        void await_suspend(stdcoro::coroutine_handle<TPromise> coroutine) noexcept
        {
            SyncTaskPromise& promise = coroutine.promise();
            promise.m_event->set();
        }
        void await_resume() noexcept
        {
        }
    };

    auto get_return_object() noexcept
    {
        return SyncWaitTask<TResultType>{ stdcoro::coroutine_handle<SyncTaskPromise<TResultType>>::from_promise(*this) };
    }
    void start(BlockingEvent* _pEvent) noexcept
    {
        m_event = _pEvent;
        stdcoro::coroutine_handle<SyncTaskPromise<TResultType>>::from_promise(*this).resume();
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

template <typename TAwaitable, typename TTaskResult = AwaitResultGetter<TAwaitable>::Result>
SyncWaitTask<TTaskResult> makeSyncWaitTask(TAwaitable&& awaitable)
{
    if constexpr (!std::is_same_v<TTaskResult, void>)
        coyield co_await awaitable;
    else
        co_await awaitable;
}

```


## Небольшие примеры для экспериментов
Полный пример на котором можно экспериментировать:
https://godbolt.org/z/8YoxPPYsW

Пример с использованием SPI-интерфейса для инициализации дисплея. Можно экспериментировать.
https://wandbox.org/permlink/y6s7UVqLQUBy67xK


## Полезные ссылки и материалы
* https://blog.panicsoftware.com/your-first-coroutine/
* https://lewissbaker.github.io/2017/09/25/coroutine-theory
* https://lewissbaker.github.io/2017/11/17/understanding-operator-co-await
* https://lewissbaker.github.io/2018/09/05/understanding-the-promise-type
* https://lewissbaker.github.io/2020/05/11/understanding_symmetric_transfer
* https://gist.github.com/MattPD/9b55db49537a90545a90447392ad3aeb - собрание ссылок и материалов по сопрограммам(доклады, библиотеки, примеры)
* https://github.com/lewissbaker/cppcoro - библиотека, с которой разбирался в процессе написания заметки
* https://github.com/bbelson2/coro-mc-wwl-code - репозиторий из исследования [C++20 Coroutines on Microcontrollers—What We Learned](https://ieeexplore.ieee.org/abstract/document/8995550)

P.S. В дальнейшем хотелось бы раписать про особенности работы сопрограмм, использование пользовательских аллокаторов для них, применение в связке с библиотеками.
