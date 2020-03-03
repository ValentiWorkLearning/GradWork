#pragma once

#include "gs_iwidget_object.hpp"

#include <cstdint>

namespace Graphics::Widgets
{

class IBluetoothWidget
    :   public IWidgetObject
{

public:

    enum class BluetoothStatus
    {
            Connected
        ,   Disconnected
    };

    virtual void setBluetoothStatus( BluetoothStatus _iconToSet ) = 0;
};

};
