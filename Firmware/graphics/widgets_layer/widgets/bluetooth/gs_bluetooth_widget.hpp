#pragma once

#include "ih/widgets/gs_ibluetooth_widget.hpp"
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

class BluetoothWidget : public WidgetBaseObj<IBluetoothWidget>
{

public:
    explicit BluetoothWidget(const Theme::IThemeController* _themeController) noexcept;

    ~BluetoothWidget() override = default;

public:
    void show() noexcept override;

    void hide() noexcept override;

    void reloadStyle() noexcept override;

public:
    void setBluetoothStatus(BluetoothStatus _iconToSet) noexcept override;

private:
    void initStyles() noexcept;

    void resetStyle() noexcept;

    void initBluetoothIcon(
        lv_obj_t* _parentObject,
        const std::uint32_t _displayWidth,
        const std::uint32_t _displayHeight) noexcept;

    BluetoothStatus getCurrentStatus() const noexcept;

private:
    BluetoothStatus m_currentStatus;
    lv_style_t m_bluetoothIconStyle;
    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pBluetoothIcon;
};

std::unique_ptr<IBluetoothWidget> createBluetoothWidget(
    const Theme::IThemeController* _themeController) noexcept;

}; // namespace Graphics::Widgets
