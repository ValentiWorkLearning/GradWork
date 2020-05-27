#pragma once

#include "Noncopyable.hpp"
#include "TimeWrapper.hpp"
#include "SimpleSignal.hpp"

#include <any>

namespace Ble::DateTimeService
{

class IDateTimeService
    :   private Utils::noncopyable
{

public:

    virtual ~IDateTimeService() = default;

public:

    virtual void handleDiscoveryEvent( const std::any& _pBleDbDiscoveryEvent ) = 0;
public:

    Simple::Signal<void(TimeWrapper)> onDateTimeDiscovered;

};

}