#pragma once
#include "inc/delay/delay_provider.hpp"

#include "nrf_delay.h"

namespace Delay
{
    void waitFor(std::uint16_t _toWaitBlockingMs )
    {
        nrf_delay_ms( _toWaitBlockingMs );
    }
} // namespace Delay
