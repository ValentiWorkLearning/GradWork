#pragma once

#include "ih/drivers/ih_ble_dts_service.hpp"

#include "ble_cts_c.h"

namespace Ble::DateTimeService
{

class DateTimeServiceNordic : public IDateTimeService
{

public:
    DateTimeServiceNordic(const std::any& _pGattQueue);

public:
    virtual ~DateTimeServiceNordic() override = default;

public:
    void handleDiscoveryEvent(const std::any& _pBleDbDiscoveryEvent) noexcept override;

private:
    void initService(const std::any& _pGattQueue) noexcept;

    void serviceEventHandler(ble_cts_c_t* _pCurrentTimeService, ble_cts_c_evt_t* _pEvent) noexcept;
};

} // namespace Ble::DateTimeService