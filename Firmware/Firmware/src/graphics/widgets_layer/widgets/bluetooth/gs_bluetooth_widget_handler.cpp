#include "gs_bluetooth_widget_handler.hpp"

#include "ih/gs_events.hpp"

#include "gs_ibluetooth_widget.hpp"

#include <cassert>

namespace Graphics::Widgets
{

BluetoothWidgetHandler::BluetoothWidgetHandler( IBluetoothWidget* _bluetoothWidget )
    :   m_pBluetoothWidget{ _bluetoothWidget }
{

}

void
BluetoothWidgetHandler::handleEvent( const Events::TEvent& _event )
{
    Events::TBleClientEvents bleClientEvent { std::any_cast<Events::TBleClientEvents>( _event.eventType ) };
    if( bleClientEvent == Events::TBleClientEvents::DeviceConnected )
        m_pBluetoothWidget->setBluetoothStatus( IBluetoothWidget::BluetoothStatus::Connected );
    else if( bleClientEvent == Events::TBleClientEvents::DeviceDisconnected )
        m_pBluetoothWidget->setBluetoothStatus( IBluetoothWidget::BluetoothStatus::Disconnected );
    else{
        assert( false );
    }
}

std::unique_ptr<Graphics::IEventHandler>
createBluetoothWidgetHandler(IBluetoothWidget* _bluetoothWidget)
{
    return std::make_unique<BluetoothWidgetHandler>( _bluetoothWidget );
}

}