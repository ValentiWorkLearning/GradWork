// This file is a "Hello, world!" in C++ language by GCC for wandbox.
#include "coroutine_utils.hpp"
#include "display_gc9a01.hpp"
#include "spi_desktop_backend.hpp"
#include "spi_driver_high_level.hpp"
#include <cstdlib>
#include <iostream>

using TSpiBus = SpiBus<SpiBusDesktopBackend>;
using TDisplayDriver = DisplayDriver::GC9A01Compact<TSpiBus, 240, 240>;

TDisplayDriver compactGc9A01;

CoroUtils::Task<int> waitForInit()
{
    compactGc9A01.initialize();
    co_await compactGc9A01.displayInitialized;
    co_return 0;
}

int main()
{
    auto waitForInitTask = waitForInit();
    int initResult = CoroUtils::syncWait(waitForInitTask);
    return initResult;
}