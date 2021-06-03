#pragma once

#include "ih/widgets/gs_ibattery_widget.hpp"
#include "widgets_layer/widgets/gs_widget_base_obj.hpp"

#include "lvgl.h"

#include "utils/MetaUtils.hpp"

#include <memory>
#include <string>

namespace Graphics::Theme
{
class IThemeController;
}

namespace Graphics::Widgets
{

class IWidgetEventHandler;

class BatteryWidget : public WidgetBaseObj<IBatteryWidget>
{

public:
    explicit BatteryWidget(const Theme::IThemeController* _themeController) noexcept;

    ~BatteryWidget() override = default;

public:
    void show() noexcept override;

    void hide() noexcept override;

    void reloadStyle() noexcept override;

public:
    void setBatteryLevelPercentage(const std::uint8_t _newBatteryLevel) noexcept override;

    void setBatteryStatus(BatteryStatus _iconToSet) noexcept override;

private:
    void initStyles() noexcept;

    void resetStyle() noexcept;

    void initBatteryPercentageLabel(
        lv_obj_t* _parentObject,
        const std::uint32_t _displayWidth,
        const std::uint32_t _displayHeight) noexcept;

    void initBatteryIcon(
        lv_obj_t* _parentObject,
        const std::uint32_t _displayWidth,
        const std::uint32_t _displayHeight) noexcept;

private:
    lv_style_t m_bateryIconStyle;
    lv_style_t m_batteryLabelStyle;

    std::string m_labelText;

    BatteryStatus m_currentStatus;

    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pBatteryIcon;
    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pBatteryLabel;
};

std::unique_ptr<IBatteryWidget> createBatteryWidget(
    const Theme::IThemeController* _themeController) noexcept;

}; // namespace Graphics::Widgets
