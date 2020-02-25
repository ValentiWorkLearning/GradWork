#pragma once

#include "lvgl.h"

#include "MetaUtils.hpp"

#include <string>
#include <memory>


template<typename TBaseWidgetInterface>
class BaseWidgetImpl
    :   public TBaseWidgetInterface
{

public:

    BaseWidgetImpl( std::weak_ptr<Theme::IThemeController> _themeController )

protected:

private:

    bool m_isVisible;

    std::weak_ptr<Theme::IThemeController> m_pThemeController;
}