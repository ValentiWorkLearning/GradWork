#include "gs_bluetooth_widget_handler.hpp"

#include "ih/gs_events.hpp"

#include "ih/widgets/gs_ibluetooth_widget.hpp"

#include <cassert>

namespace Graphics::Widgets
{

BluetoothWidgetHandler::BluetoothWidgetHandler( IBluetoothWidget* _bluetoothWidget )
    :   m_pBluetoothWidget{ _bluetoothWidget }
{

}

void
BluetoothWidgetHandler::handleEventImpl( const Events::TBleClientEvents& _event, const std::any& _eventData )
{
    if( _event == Events::TBleClientEvents::DeviceConnected )
        m_pBluetoothWidget->setBluetoothStatus( IBluetoothWidget::BluetoothStatus::Connected );
    else if( _event == Events::TBleClientEvents::DeviceDisconnected )
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
