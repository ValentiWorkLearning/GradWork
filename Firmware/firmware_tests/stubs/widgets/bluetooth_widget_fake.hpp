#pragma once

#include "base_stub_widget.hpp"

#include "ih/widgets/gs_ibluetooth_widget.hpp"

class BluetoothWidgetStub : public FakeBaseWidget<Graphics::Widgets::IBluetoothWidget>
{
public:
    void setBluetoothStatus(
        Graphics::Widgets::IBluetoothWidget::BluetoothStatus _iconToSet) override
    {
    }
};