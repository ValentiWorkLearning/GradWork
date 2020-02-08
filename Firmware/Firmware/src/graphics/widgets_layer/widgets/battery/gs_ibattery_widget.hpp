#pragma once

#include "gs_iwidget_object.hpp"

#include <cstdint>

namespace Graphics::Widgets
{

class IBatteryWidget
    :   public IWidgetObject
{

public:

    enum class BatteryStatus
    {
            QuaterCharge
        ,   HalfCharged
        ,   Charge75Percents
        ,   Charged90Percents
        ,   FullCharged
    };

    virtual void setBatteryLevelPercentage( const std::uint8_t _newBatteryLevel ) = 0;

    virtual void setBatteryStatus( BatteryStatus _iconToSet ) = 0;
};

};
