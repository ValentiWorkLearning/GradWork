#pragma once

#include "ih/gs_ievent_handler.hpp"

#include "widgets_layer/gs_event_handler_base.hpp"

#include <memory>

namespace Graphics::Widgets
{

class IBluetoothWidget;

class BluetoothWidgetHandler
    : public Events::EventHandler<Graphics::IEventHandler, Events::TBleClientEvents>
{

public:
    explicit BluetoothWidgetHandler(IBluetoothWidget* _bluetoothWidget) noexcept;

    ~BluetoothWidgetHandler() override = default;

protected:
    void handleEventImpl(
        const Events::TBleClientEvents& _event,
        const std::any& _eventData) noexcept override;

private:
    IBluetoothWidget* m_pBluetoothWidget;
};

std::unique_ptr<Graphics::IEventHandler> createBluetoothWidgetHandler(
    IBluetoothWidget* _bluetoothWidget) noexcept;

} // namespace Graphics::Widgets