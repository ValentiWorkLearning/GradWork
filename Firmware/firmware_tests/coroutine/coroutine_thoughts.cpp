#include <iostream>
#include <array>
#include <chrono>
#include <thread>
#include <cstdint>
#include <vector>
#include <queue>
#include <atomic>
#include <functional>
#include <coroutine>


#include "ih/drivers/ih_display_idisplay.hpp"

#include "display/display_spi_common_coro.hpp"
#include "spi/spi_wrapper_async.hpp"
#include "logger/logger_service.hpp"
#include "display/display_coro_compact_gc9a01.hpp"


#include <spi/spi_wrapper_async_templated.hpp>
#include <backends/spi_backend_desktop.hpp>

#include "st7789_draft.hpp"


 int main()
 {
     using TSpiBus = Interface::SpiTemplated::SpiBus<Interface::SpiTemplated::SpiBusDesktopBackend>;

     using TDisplayDriver =
         DisplayDriver::GC9A01Compact<TSpiBus, 240, 240>;
     /*Display display{};
     display.fillRectangle(0, 0, 220, 220, nullptr);*/

     TDisplayDriver compactGc9A01;
     compactGc9A01.fillRectangle(0, 0, 0, 0, nullptr);
     compactGc9A01.initialize();
     //ST7789Coroutine displayCoro{
     //       Interface::Spi::createSpiBusAsync<Interface::Spi::SpiInstance::M1>()
     //    ,  240
     //    ,  240
     //};
     //displayCoro.fillRectangle(0, 0, 0, 0, nullptr);
     while(true)
     {
         using namespace std::chrono_literals;
         std::this_thread::sleep_for(100ms);
         CoroUtils::CoroQueueMainLoop::GetInstance().processQueue();
     }
     return 0;
 }

