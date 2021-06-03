#include "inc/delay/delay_provider.hpp"

#if defined(USE_DEVICE_SPECIFIC)
#include "nrf_delay.h"
#else
#include <chrono>
#include <thread>
#endif

namespace Delay
{
void waitFor(std::uint16_t _toWaitBlockingMs)
{
#if defined(USE_DEVICE_SPECIFIC)
    nrf_delay_ms(_toWaitBlockingMs);
#else
    std::this_thread::sleep_for(std::chrono::milliseconds(_toWaitBlockingMs));
#endif
}
} // namespace Delay
