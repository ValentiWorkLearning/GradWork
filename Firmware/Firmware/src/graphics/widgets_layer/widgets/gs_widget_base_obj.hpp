#pragma once

#include "ih/gs_iwidget_object.hpp"

#include "lvgl.h"

#include "MetaUtils.hpp"

#include <string>
#include <memory>


namespace Graphics::Widgets
{

template<typename TBaseWidgetInterface>
class WidgetBaseObj
    :   public TBaseWidgetInterface
{

public:

    WidgetBaseObj( std::weak_ptr<Theme::IThemeController> _themeController );

public:

    void show() override;

    void hide() override;

    bool isVisible()const override;

public:

    std::weak_ptr<Theme::IThemeController> getThemeController() const override;

protected:

    struct ShowParams
    {
        lv_obj_t* pParent;
        const std::uint32_t DisplayWidth;
        const std::uint32_t DisplayHeight;
    };

    ShowParams getShowParams();

private:

    bool m_isWidgetVisible;

    std::weak_ptr<Theme::IThemeController> m_pThemeController;
};

}