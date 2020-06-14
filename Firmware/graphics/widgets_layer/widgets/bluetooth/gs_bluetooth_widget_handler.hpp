#pragma once

#include "ih/gs_ievent_handler.hpp"
#include <memory>

namespace Graphics::Widgets
{

class IBluetoothWidget;

class BluetoothWidgetHandler
    :   public Graphics::IEventHandler
{

public:

    explicit BluetoothWidgetHandler( IBluetoothWidget* _bluetoothWidget );

    ~BluetoothWidgetHandler() override = default;

public:

    void handleEvent( const Events::TEvent& _event ) override;

private:

    IBluetoothWidget* m_pBluetoothWidget;
};

std::unique_ptr<Graphics::IEventHandler>
createBluetoothWidgetHandler( IBluetoothWidget* _bluetoothWidget );

}