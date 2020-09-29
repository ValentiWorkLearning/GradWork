### Coroutines from C++20 on ARM Cortex-M

Подробные пояснения по сопрограммам, их особенностям реализации, преимуществами, примерами использования можно посмотреть в следующем списке статей. Ознакомление с статьями рекомендую в следующем порядке:

https://www.youtube.com/watch?v=Ts-1mWBmTNE - MUST WATCH видео от автора предложения Coroutines в стандарт С++20. Раскрыты детали реализации сопрограмм, бенчмарки в сравнении с "callback hell". Рекомендуется к просмотру в первую очередь.

https://blog.panicsoftware.com/coroutines-introduction/ - тут хорошая начальная теория. Либо, взять за основу следующую статью:

https://luncliff.github.io/posts/Exploring-MSVC-Coroutine.html - тут больше картинок и примеры кода есть под конец статьи

https://blog.panicsoftware.com/your-first-coroutine/ - следующая в цикле статей, для начального понимания происходящего

https://lewissbaker.github.io/2017/09/25/coroutine-theory - базовая теория по сопрограммам, для начала может быть сложной

https://habr.com/ru/company/yandex/blog/420861/ - полезный пример "телепортации" между различными очередями задач

https://habr.com/en/post/348602/ - как использовать сопрограммы из С++20 в связке с boost::asio

 https://habr.com/en/post/493808/ // coroutine code linearizing - Линеаризация кода с использованием сопрограмм. Показаны фрагменты реализации модели Акторов.

https://manybutfinite.com/post/anatomy-of-a-program-in-memory/ 

https://manybutfinite.com/post/journey-to-the-stack/



В свою очередь, было решено попробовать фишки из С++20 в домашнем проекте. Прежде, чем собирать все в реальном проекте -  был сделан отдельный репозиторий https://github.com/ValentiWorkLearning/CoroutineExperiments/ . В репозитории была реализована первая идея- использовать сопрограммы для переписывания драйвера для дисплея, работающего по SPI. 



### Пояснение демонстрационного примера из репозитория CoroutineExperiments

Для реализации "эмуляции" передачи данных по интерфейсу SPI  с использованием DMA необходимо реализовать следующий набор функций:

* Сигнатуру HAL(Hardware Abstraction Layer) подобную доступной в API конкретного вендора.
* Пользовательскую сигнатуру для передачи данных( например, передачи команды на дисплей)
* Функцию инициализации дисплея

API для передачи данных, в большинстве своем, имеют похожий вид-указатель на блок данных + размер передаваемого блока + void* на _pUserData -подобный "контекст". Так-же, имеется функционал для инициализации интерфейса.



В случае Nordic, например, сигнатура функции для инициализации SPI имеет вид:

```cpp
nrfx_err_t nrfx_spim_init(nrfx_spim_t  const * const p_instance,
                          nrfx_spim_config_t const * p_config,
                          nrfx_spim_evt_handler_t    handler,
                          void                     * p_context)
```

где p_context- "контекст" который будет доступен в `nrfx_spim_evt_handler_t    handler` callback-е.

Инициализация интерфейса SPI происходит вызовом nrfx_spim_init:

```cpp
APP_ERROR_CHECK(
            nrfx_spim_init(
                    &m_spiHandle
                ,   &spiConfig
                ,   spimEventHandler
                ,   this
            )
        );
```

Аргументами которой являются:

* m_spiHandle- структура-дескриптор, которая выглядит следующим образом:

  ```cpp
  typedef struct
  {
      NRF_SPIM_Type * p_reg;        ///< Pointer to a structure with SPIM registers.
      uint8_t         drv_inst_idx; ///< Index of the driver instance. For internal use only.
  } nrfx_spim_t;
  ```

* spiConfig- структура с конфигурацией SPI( скорость, используемые порты, etc). Подробнее фрагмент можно посмотреть [ссылка на листинг в репозитории](https://github.com/ValentiWorkLearning/GradWork/blob/9262f65599d58640db2a972ff668a8b065b6441c/Firmware/drivers/spi/spi_wrapper.cpp#L57)

* spimEventHandler- callback, вызываемый в момент обработки события на шине SPI, по завершению приема/передачи.

* this- контекст, который будет доступен в обработчике события, в текущей реализации-обрабатывает состояние транзакций на шине.

Callback реализован как:

```cpp
 static void spimEventHandler(
            nrfx_spim_evt_t const* _pEvent
        ,   void* _pContext
    )noexcept
    {
        Meta::UnuseVar( _pContext );
        if( _pEvent->type == NRFX_SPIM_EVENT_DONE )
        {
            auto pThis = reinterpret_cast<SpiBus::SpiBackendImpl*>( _pContext );
            pThis->m_pSpiBus->handleEvent( SpiBus::TCompletedEvent::TransactionCompleted );
        }
    }
```

Передача данных по SPI формируется созданием дескриптора транзакции + инициации передачи данных:

```cpp
nrfx_spim_xfer_desc_t xferDesc =
    NRFX_SPIM_XFER_TX(
            _pBuffer
        ,   _bufferSize
    );
nrfx_err_t transmissionError = nrfx_spim_xfer
        &m_spiHandle
    ,   &xferDesc
    ,   0
);
```

В общем случае,  можно объединить вызов в :

```cpp
void sendDataChunk(std::uint8_t* _pData, std::uint16_t _dataSize, void* _pUserContext);
```

При необходимости передачи данных блоком, например-  передачи блока команд инициализации на дисплей в неблокирующем режиме - в традиционном варианте необходимо сформировать очередь на отправку, из которой по прерыванию(событию?) доставать новый блок данных и формировать пакет на отправку.

В коде выглядит примерно как:

```cpp
    sendCommand(    DisplayReg::SLPOUT     );
    sendCommand(    DisplayReg::COLMOD     , 0x55   );
    sendCommand(    DisplayReg::MADCTL     , 0x08   );
```

Реализацию sendCommand можно посмотреть [тут](https://github.com/ValentiWorkLearning/GradWork/blob/9262f65599d58640db2a972ff668a8b065b6441c/Firmware/drivers/display/inc/display/display_spi_common.hpp#L76)

Вкратце- помещаем в очередь выполнения SPI - транзакцию с beforeTransaction, transactionAction,afterTransaction.

### CoroutineExperiments implementation

В предыдущем разделе был упомянут "объединенный" вызов для запуска передачи данных. Для эмуляции асинхронной передачи данных реализуем HAL-метод следующий образом:

- P.S. восстановление сопрограммы происходит не в потоке, откуда была инициирована передача данных, если это является проблемой- возможно использовать подход, описанный в [Готовимся к С++20. Coroutines TS на реальном примере](https://habr.com/ru/company/yandex/blog/420861/) или [Асинхронность 2: телепортация сквозь порталы](https://habr.com/ru/company/yandex/blog/240525/)

  

```cpp
void spiBackendImplTransmit(
        std::uint8_t* _pBuffer
    ,   std::uint16_t _bufferSize
    ,   void* _pUserData
)
{
    std::thread dmaThread = std::thread(
        [_pUserData]
        {
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(500ms);

            std::cout << "TRANSMIT SOME DATA" << std::endl;
            stdcoro::coroutine_handle<>::from_address(_pUserData).resume();
        }
    );
    dmaThread.detach();
}
```



Пользовательский метод передачи данных реализуем следующим образом

```cpp
auto spiTrasnmitCommandBufferAsync(
        std::uint8_t* _pBuffer
    ,   std::uint16_t _bufferSize
)
{
    std::cout << "Toggle GPIO ON" << std::endl;
    struct Awaiter
    {
        std::uint8_t* pBuffer;
        std::uint16_t bufferSize;

        bool await_ready() const noexcept
        {
            return false;
        }
        void await_resume() const noexcept
        {
            std::cout << "Toggle GPIO OFF" << std::endl;
        }
        void await_suspend(stdcoro::coroutine_handle<> thisCoroutine) const
        {
            spiBackendImplTransmit( pBuffer,bufferSize, thisCoroutine.address() );
        }
    };

    return Awaiter{
            .pBuffer = _pBuffer
        ,   .bufferSize = _bufferSize
    };
}
```

`bool await_ready() const noexcept` - возвращает всегда false, т.к. нам гарантированно надо выполнять операцию для получения результата awaitable.

`void await_resume() const noexcept` - момент "восстановления" сопрограммы

`void await_suspend(stdcoro::coroutine_handle<> thisCoroutine) const` - функция, вызываемая в момент приостановки сопрограммы

И получим следующую реализацию функции инициализации дисплея:

```cpp
auto commandBufferFirst = std::array{ 0x00u, 0x01u, 0x02u, 0x03u };
auto commandBufferSecond = std::array{ 0x04u, 0x05u, 0x06u, 0x07u,0x08u };

void initDisplay()
{

    co_await spiTrasnmitCommandBufferAsync(
            reinterpret_cast<std::uint8_t*>( commandBufferFirst.data() )
        ,   commandBufferFirst.size()
    );
    co_await spiTrasnmitCommandBufferAsync(
            reinterpret_cast<std::uint8_t*>( commandBufferSecond.data() )
        ,   commandBufferSecond.size()
    );
}
```

Подробный полный пример доступен [Ссылка на репозиторий](https://github.com/ValentiWorkLearning/CoroutineExperiments/)

### Мигаем светодиодом на NRF52832

Имея механизм сопрограмм, и исследовав пример [Exploring MSVC Coroutine](https://luncliff.github.io/posts/Exploring-MSVC-Coroutine.html)

мы можем помигать светодиодом с весьма интересным синтаксисом:

```cpp

void
Board::ledToggle()
{
    using namespace std::chrono_literals;
    while(true)
    {
        co_await 300ms;

        LOG_DEBUG_ENDL("LED TIMER EXPIRED");
        bsp_board_led_invert(0);
    }
}

```



Немного освежив в памяти API FreeRTOS - вспоминается следующий фрагмент кода:

```cpp
xTaskCreate(ledBlinkTask,"ledBlinkTask",128,NULL,2,NULL);
void ledBlinkTask(void *pvParameters)  
{
	while(true)
    {
        vTaskDelay( 300 / portTICK_PERIOD_MS );
        bsp_board_led_invert(0);
	}
}
```

Реализация `co_await 300ms` схожа с вышеупомянутой статьей с [Exploring MSVC Coroutine](https://luncliff.github.io/posts/Exploring-MSVC-Coroutine.html), а именно следующая:

```cpp
auto operator co_await( std::chrono::milliseconds _duration)
{

    class Awaitable
    {

        public:

        explicit Awaitable(std::chrono::milliseconds _duration)
            :   m_duration{_duration}
        {
        }

        bool await_ready()const
        {
            return false;
        }

        void await_suspend(std::coroutine_handle<> _coroLedHandle)
        {
            ret_code_t errorCode{};
            errorCode = app_timer_start(
                    m_ledDriverTimer
                ,   APP_TIMER_TICKS( m_duration.count() )
                ,   _coroLedHandle.address()
            );
            APP_ERROR_CHECK( errorCode );
        }

        void await_resume()
        {
            app_timer_stop(m_ledDriverTimer);
        }

        private:

        std::chrono::milliseconds m_duration;

    };
    return Awaitable{_duration};
}
```

Где на `await_suspend` сопрограммы делается запуск таймера на заданный период( `300ms`),  в обработчике таймера вызывается `coroutine_handle.resume()` , после которого таймер останавливается в `void await_resume()`. 

Полная реализация доступна [Ссылка на репозиторий,watchboard.cpp](https://github.com/ValentiWorkLearning/GradWork/blob/dev/develop/Firmware/drivers/board/watchboard.cpp)