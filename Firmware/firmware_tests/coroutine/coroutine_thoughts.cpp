#include <iostream>
#include <array>
#include <chrono>
#include <thread>
#include <cstdint>
#include <vector>
#include <queue>
#include <atomic>
#include <functional>

#ifdef WIN32
#include <experimental/coroutine>
namespace stdcoro = std::experimental;
#else
#include <coroutine>
namespace stdcoro = std;
#endif // WIN32

#include "ih/drivers/ih_display_idisplay.hpp"

#include "display/display_spi_common_coro.hpp"

// https://blog.panicsoftware.com/your-first-coroutine/
// https://manybutfinite.com/post/anatomy-of-a-program-in-memory/
// https://manybutfinite.com/post/journey-to-the-stack/
// https://luncliff.github.io/posts/Exploring-MSVC-Coroutine.html
// https://habr.com/en/post/493808/ // coroutine code linearizing
// https://lewissbaker.github.io/2017/09/25/coroutine-theory
// https://lewissbaker.github.io/2018/09/05/understanding-the-promise-type
// https://devblogs.microsoft.com/oldnewthing/20191219-00/?p=103230
// https://habr.com/en/post/348602/ // boost asio with coroutines TS
// https://m.habr.com/ru/post/519464/ // C++20 coroutines
// https://mariusbancila.ro/blog/2020/06/22/a-cpp20-coroutine-example/

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

            std::cout << "TRANSMIT SOME DATA" << "THREAD:" << std::this_thread::get_id() << std::endl;
            stdcoro::coroutine_handle<>::from_address(_pUserData).resume();
        }
    );
    dmaThread.detach();
}

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

auto commandBufferFirst = std::array{ 0x00u, 0x01u, 0x02u, 0x03u };
auto commandBufferSecond = std::array{ 0x04u, 0x05u, 0x06u, 0x07u,0x08u };

struct DisplayInitializedEvent
{
    DisplayInitializedEvent() = default;

    DisplayInitializedEvent(const DisplayInitializedEvent&) = delete;
    DisplayInitializedEvent& operator = (const  DisplayInitializedEvent&) = delete;

    DisplayInitializedEvent(DisplayInitializedEvent&&) = delete;
    DisplayInitializedEvent& operator =(DisplayInitializedEvent&&) = delete;

     struct DisplayAwaiter
        {
            DisplayAwaiter(const DisplayInitializedEvent& _event)
                :   m_event{_event}
            {
            }
            bool await_ready()const
            {
                return m_event.m_isNotified;
            }

            bool await_suspend(stdcoro::coroutine_handle<> _coroHandle)noexcept
            {
                m_coroHandle = _coroHandle;
                if (m_event.m_isNotified)
                    return false;
                else
                    m_event.m_pSuspendedWaiter.store(this);
                return true;
            }
            void await_resume()
            {
            }

            friend DisplayInitializedEvent;
            private:
                const DisplayInitializedEvent& m_event;
                stdcoro::coroutine_handle<> m_coroHandle;
        };

    auto operator co_await() const noexcept
    {
        return DisplayAwaiter{ *this };
    }

    void notify()
    {
        m_isNotified = true;
        if (m_pSuspendedWaiter)
        {
            auto pDisplayWaiter = static_cast<DisplayAwaiter*>(m_pSuspendedWaiter.load());
            if(pDisplayWaiter)
            {
                pDisplayWaiter->m_coroHandle.resume();
            }
        }
    }

    mutable std::atomic<bool> m_isNotified{ false };
    mutable std::atomic<void*> m_pSuspendedWaiter;
};

struct Display
{
    Display()
    {
        initDisplay();
    }

    void fillRectangle(
        std::uint16_t _x
        , std::uint16_t _y
        , std::uint16_t _width
        , std::uint16_t _height
        , std::uint16_t* _colorToFill
    )
    {
        std::cout << "void fillRectangle(); SUSPEND"<< "THREAD:"<< std::this_thread::get_id() << std::endl;
        co_await m_initializedEvent;
        std::cout << "void fillRectangle(); RESUMED"<< "THREAD:" << std::this_thread::get_id() << std::endl;
        
        co_await spiTrasnmitCommandBufferAsync(
            reinterpret_cast<std::uint8_t*>(commandBufferFirst.data())
            , commandBufferFirst.size()
        );
    }

    void initDisplay()
    {

        co_await spiTrasnmitCommandBufferAsync(
            reinterpret_cast<std::uint8_t*>(commandBufferFirst.data())
            , commandBufferFirst.size()
        );
        co_await spiTrasnmitCommandBufferAsync(
            reinterpret_cast<std::uint8_t*>(commandBufferSecond.data())
            , commandBufferSecond.size()
        );
        m_initializedEvent.notify();
    }

    DisplayInitializedEvent m_initializedEvent;
};




class ST7789Coroutine
    : public DisplayDriver::BaseSpiDisplayCoroutine
{
    using BaseDisplay_t = DisplayDriver::BaseSpiDisplayCoroutine;
public:

    explicit ST7789Coroutine(
            std::unique_ptr<Interface::Spi::SpiBusAsync>&& _busPtr
        ,   std::uint16_t _width
        ,   std::uint16_t _height
    )   :     DisplayDriver::BaseSpiDisplayCoroutine(
            std::move(_busPtr)
        ,   _width
        ,   _height
    )
    {
        initDisplay();
        initColumnRow(_width, _height);
    }

    ~ST7789Coroutine()noexcept override
    {
    }

    void turnOn()noexcept override
    {
    }

    void turnOff()noexcept override
    {
    }

    void fillRectangle(
        std::uint16_t _x
        , std::uint16_t _y
        , std::uint16_t _width
        , std::uint16_t _height
        , IDisplayDriver::TColor* _color
    )noexcept override
    {
    }

private:

    void initDisplay()noexcept
    {
        BaseDisplay_t::resetResetPin();
        Delay::waitFor(100);
        BaseDisplay_t::setResetPin();

        co_await sendCommand(0x01);
        Delay::waitFor(150);
        co_await sendCommand(0x02);
        co_await sendCommand(0x03, 0x31);
        co_await sendCommand(0x04, 0x41);
        co_await sendCommand(0x05, 0x51, 0x52, 0x53, 0x54);
        co_await sendCommand(0x06, 0x61, 0x62, 0x63, 0x64);
        co_await sendCommand(0x07, 0x71);
        co_await sendCommand(0x08);
        co_await sendCommand(0x09);
        co_await sendCommand(0x10, 0x11);

    }

    void initColumnRow(
        std::uint16_t _width
        , std::uint16_t _height
    )noexcept
    {
    }

    void setAddrWindow(
        std::uint16_t _x
        , std::uint16_t _y
        , std::uint16_t _width
        , std::uint16_t _height
    )noexcept
    {
    }
};


 // TODO what is the compiler-generated code?
 int main()
 {
     /*Display display{};
     display.fillRectangle(0, 0, 220, 220, nullptr);*/

     using namespace std::chrono_literals;
     std::this_thread::sleep_for(5000ms);
     return 0;
 }


// We have to define the 'resumable' class for the way
// of communicating between the coroutine and usual function
class resumable
{
public:

    // Here we declare the promise type with necessary functions 
    struct promise_type
    {
        // //declaration of the coroutine handle alias- basic type for operating with coroutine;
        using coro_handle = stdcoro::coroutine_handle<promise_type>;

        resumable get_return_object()
        {
            return coro_handle::from_promise(*this);
        }
        auto initial_suspend()
        {
            return stdcoro::suspend_always();
        }
        auto final_suspend()noexcept
        {
            return stdcoro::suspend_always();
        }

        void unhandled_exception()
        {
            std::terminate();
        }

        void return_void() {}
    };

    //declaration of the coroutine handle alias- basic type for operating with coroutine;
    using coro_handle = stdcoro::coroutine_handle<promise_type>;

public:

    resumable(coro_handle handle)
        : m_coroutineHandle{ handle }
    {
    }

    resumable(resumable&) = delete;
    resumable(resumable&&) = delete;

    bool resume()
    {
        if (!m_coroutineHandle.done())
            m_coroutineHandle.resume();

        return !m_coroutineHandle.done();
    }
private:
    coro_handle m_coroutineHandle;
};

resumable foo()
{
    std::cout << "Hello" << std::endl;
    // Without resumable return type we cant't use our coroutine
    // or without overriding the co_await operator also

    co_await stdcoro::suspend_always();
    std::cout << "from coroutine" << std::endl;
}

////For using co_await operator we have to use the concept of 'awaitable entity'
////the main idea is quite simple - to provide the implementation for the customization_point of the coroutine

//int main()
//{
//    auto resumableObject = foo();
//    resumableObject.resume();
//    resumableObject.resume();
//
//    return 0;
//}
