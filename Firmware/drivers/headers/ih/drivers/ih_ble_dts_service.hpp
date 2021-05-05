#pragma once

#include "utils/Noncopyable.hpp"
#include "utils/TimeWrapper.hpp"
#include "utils/SimpleSignal.hpp"

#include <any>

namespace Ble::DateTimeService
{

class IDateTimeService
    :   private Utils::noncopyable
{

public:

    virtual ~IDateTimeService() = default;

public:

    virtual void handleDiscoveryEvent( const std::any& _pBleDbDiscoveryEvent )noexcept = 0;
public:

    Simple::Signal<void(TimeWrapper)> onDateTimeDiscovered;

};

}