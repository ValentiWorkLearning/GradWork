#include "gs_bluetooth_widget_handler.hpp"

#include "ih/gs_events.hpp"

#include "gs_event_dispatcher.hpp"
#include "ih/widgets/gs_ibluetooth_widget.hpp"

#include <cassert>

namespace Graphics::Widgets
{

BluetoothWidgetHandler::BluetoothWidgetHandler(IBluetoothWidget* _bluetoothWidget) noexcept
    : m_pBluetoothWidget{_bluetoothWidget}
{
}

void BluetoothWidgetHandler::handleEventImpl(
    const Events::TBleClientEvents& _event,
    const std::any& _eventData) noexcept
{
    if (_event == Events::TBleClientEvents::DeviceConnected)
        m_pBluetoothWidget->setBluetoothStatus(IBluetoothWidget::BluetoothStatus::Connected);
    else if (_event == Events::TBleClientEvents::DeviceDisconnected)
        m_pBluetoothWidget->setBluetoothStatus(IBluetoothWidget::BluetoothStatus::Disconnected);
    else
    {
        assert(false);
    }
}

void BluetoothWidgetHandler::initSubscriptions(Events::EventDispatcher& eventDispatcher)
{
    eventDispatcher.subscribe(Events::EventGroup::BleDevice, [this](const Events::TEvent& _event) {
        handleEvent(_event);
    });
}

void BluetoothWidgetHandler::deinitHandler()
{
}

std::unique_ptr<Graphics::IEventHandler> createBluetoothWidgetHandler(
    IBluetoothWidget* _bluetoothWidget) noexcept
{
    return std::make_unique<BluetoothWidgetHandler>(_bluetoothWidget);
}

} // namespace Graphics::Widgets
