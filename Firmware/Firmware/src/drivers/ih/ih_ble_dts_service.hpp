#pragma once

#include "Noncopyable.hpp"
#include "TimeWrapper.hpp"
#include "SimpleSignal.hpp"


namespace Ble::DateTimeService
{

class IDateTimeService
    :   private Utils::noncopyable
{

public:

    virtual ~IDateTimeService() = default;

public:

    Simple::Signal<void(TimeWrapper)> onDateTimeDiscovered;

};

}