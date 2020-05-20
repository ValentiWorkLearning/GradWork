#pragma once

#include "ih/ih_ble_dts_service.hpp"

namespace Ble::DateTimeService
{

class DateTimeServiceNordic
    :   public IDateTimeService
{

public:

    virtual ~DateTimeServiceNordic()override = default;
};

}