#pragma once

#include "base_stub_widget.hpp"

#include "ih/widgets/gs_ibattery_widget.hpp"

class BatteryWidgetStub : public FakeBaseWidget<Graphics::Widgets::IBatteryWidget>
{
public:
    void setBatteryLevelPercentage(const std::uint8_t _newBatteryLevel) override
    {
    }
    void setBatteryStatus(Graphics::Widgets::IBatteryWidget::BatteryStatus _iconToSet) override
    {
    }
};
