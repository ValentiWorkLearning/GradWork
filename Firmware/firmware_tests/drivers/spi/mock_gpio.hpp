#pragma once

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace Gpio
{

class MockGpio
{
public:

    MockGpio() = default;

    ~MockGpio() = default;

public:
    MOCK_METHOD(void, setGpioHigh, ());
    MOCK_METHOD(void, setGpioLow, ());

private:
    GTEST_DISALLOW_COPY_AND_ASSIGN_(MockGpio);
};

};