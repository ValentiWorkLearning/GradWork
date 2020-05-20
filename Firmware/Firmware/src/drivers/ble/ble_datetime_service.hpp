#pragma once

#include "ih/ih_ble_dts_service.hpp"

#include "ble_cts_c.h"

namespace Ble::DateTimeService
{

class DateTimeServiceNordic
    :   public IDateTimeService
{

public:

    DateTimeServiceNordic();

public:

    virtual ~DateTimeServiceNordic()override = default;

private:

    void initService();

    void serviceEventHandler( ble_cts_c_t* _pCurrentTimeService, ble_cts_c_evt_t* _pEvent );
};

}