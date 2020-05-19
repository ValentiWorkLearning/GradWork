#pragma once

#include "gs_ibluetooth_widget.hpp"
#include "gs_widget_base_obj.hpp"

#include "lvgl.h"

#include "MetaUtils.hpp"

#include <string>
#include <memory>

namespace Graphics::Theme
{
    class IThemeController;
}

namespace Graphics::Widgets
{

class IWidgetEventHandler;

class BluetoothWidget
    :   public WidgetBaseObj<IBluetoothWidget>
{

public:

    explicit BluetoothWidget( const Theme::IThemeController* _themeController );

    ~BluetoothWidget() override = default;

public:

    void show() override;

    void hide() override;

    void reloadStyle() override;

public:

    void setBluetoothStatus( BluetoothStatus _iconToSet ) override;

private:

    void initStyles();

    void resetStyle();

    void initBluetoothIcon(
            lv_obj_t* _parentObject
        ,   const std::uint32_t _displayWidth
        ,   const std::uint32_t _displayHeight
    );

    BluetoothStatus getCurrentStatus() const;

private:

    BluetoothStatus m_currentStatus;
    lv_style_t m_bluetoothIconStyle;
    Meta::PointerWrapper<lv_obj_t,lv_obj_del> m_pBluetoothIcon;

};

std::unique_ptr<IBluetoothWidget> createBluetoothWidget(
    const Theme::IThemeController* _themeController
);

};
