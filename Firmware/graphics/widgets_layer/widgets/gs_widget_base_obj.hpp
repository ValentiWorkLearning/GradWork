#pragma once

#include "ih/gs_iwidget_object.hpp"

#include "lvgl.h"

#include "utils/MetaUtils.hpp"

#include <string>
#include <memory>


namespace Graphics::Widgets
{

template<typename TBaseWidgetInterface>
class WidgetBaseObj
    :   public TBaseWidgetInterface
{

public:

    explicit WidgetBaseObj( const Theme::IThemeController* _themeController )noexcept;

public:

    void show()noexcept override;

    void hide()noexcept override;

    bool isVisible()const noexcept override;

public:

    const Theme::IThemeController* getThemeController() const noexcept override;

protected:

    struct ShowParams
    {
        lv_obj_t* pParent;
        const std::uint32_t DisplayWidth;
        const std::uint32_t DisplayHeight;
    };

    ShowParams getShowParams() noexcept;

private:

    bool m_isWidgetVisible;

    const Theme::IThemeController* m_pThemeController;
};

}