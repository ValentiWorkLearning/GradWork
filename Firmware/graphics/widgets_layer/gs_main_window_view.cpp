#include "gs_main_window_view.hpp"

#include "gs_theme_controller.hpp"

namespace Graphics::MainWindow
{

MainWindowView::MainWindowView()
    :   m_pThemeController{ Theme::createThemeController(
                Theme::ColorTheme::Night
            ,   Width
            ,   Height
        )
        }
    ,   m_iniStyle{}
    ,   m_yanStyle{}
    ,   m_iniCircleStyle{}
    ,   m_yanCircleStyle{}
    ,   maskArea{ 0,0,240,240 }
    ,   radiusParam{}
{
    initMask();
    initBackground();
}

void
MainWindowView::initBackground()
{

    auto createAlignedRect = [this]( auto _aligmentType, lv_style_t* _style )
    {
        lv_obj_t* pObject{ nullptr };
        auto parent = m_pObjMask.get();

        pObject = lv_obj_create( parent, nullptr );
        lv_obj_set_size(
                pObject
            ,   MainWindowView::Width
            ,   MainWindowView::Height / 2
        );

        lv_obj_add_style( pObject,LV_PART_MAIN, LV_STATE_DEFAULT, _style );
        lv_obj_align( pObject, nullptr, _aligmentType, 0, 0 );

        return pObject;
    };


    const auto MainThemeDark = m_pThemeController->getMainThemeColor(
            Graphics::Theme::Color::MainThemeDark
        );
    const auto MainThemeLight = m_pThemeController->getMainThemeColor(
            Graphics::Theme::Color::MainThemeLight
        );

    lv_style_set_bg_opa( &m_iniStyle, LV_OPA_COVER );
    lv_style_set_bg_color( &m_iniStyle, MainThemeDark );
    lv_style_set_bg_grad_color( &m_iniStyle,MainThemeDark );

    lv_style_set_bg_color( &m_yanStyle, MainThemeLight );
    lv_style_set_bg_grad_color( &m_yanStyle, MainThemeLight );
    lv_style_set_bg_opa( &m_yanStyle, LV_OPA_COVER );

    m_pIny.reset( createAlignedRect(LV_ALIGN_IN_BOTTOM_MID, &m_iniStyle) );
    m_pYan.reset( createAlignedRect( LV_ALIGN_IN_TOP_MID, &m_yanStyle ) );

    auto createAlignedCircle = [this](auto _aligmentType, lv_style_t* _style)
    {
        auto parent = m_pObjMask.get();
        lv_obj_t* pCircle = lv_obj_create( parent, nullptr );

        lv_obj_set_size(
                pCircle
            ,   MainWindowView::Width / 2
            ,   MainWindowView::Height / 2
        );

        lv_obj_add_style( pCircle, LV_PART_MAIN, LV_STATE_DEFAULT,_style );
        lv_obj_align( pCircle, nullptr, _aligmentType, 0, 0);

        return pCircle;
    };

    lv_style_set_bg_opa( &m_iniCircleStyle, LV_OPA_COVER );
    lv_style_set_bg_color( &m_iniCircleStyle,MainThemeDark );
    lv_style_set_border_color( &m_iniCircleStyle, MainThemeDark );
    lv_style_set_bg_grad_color( &m_iniCircleStyle, MainThemeDark );
    lv_style_set_radius( &m_iniCircleStyle, LV_RADIUS_CIRCLE );

    lv_style_set_bg_opa( &m_yanCircleStyle, LV_OPA_COVER );
    lv_style_set_bg_color( &m_yanCircleStyle,MainThemeLight );
    lv_style_set_border_color( &m_yanCircleStyle, MainThemeLight );
    lv_style_set_bg_grad_color( &m_yanCircleStyle, MainThemeLight );
    lv_style_set_radius(&m_yanCircleStyle, LV_RADIUS_CIRCLE);

    m_pInyCircle.reset( createAlignedCircle( LV_ALIGN_IN_RIGHT_MID, &m_iniCircleStyle ) );
    m_pYanCircle.reset( createAlignedCircle( LV_ALIGN_IN_LEFT_MID, &m_yanCircleStyle ) );
}

void
MainWindowView::resetBackgroundStyle()
{
    Meta::tupleApply(
        [](auto&& _nodeToReset) { 	lv_style_reset( &_nodeToReset ); }
        , std::forward_as_tuple(
                 m_iniStyle
            ,    m_yanStyle
            ,    m_iniCircleStyle
            ,    m_yanCircleStyle
        )
    );
}

void
MainWindowView::initMask()
{
    
    lv_draw_mask_radius_init(&radiusParam, &maskArea, LV_RADIUS_CIRCLE, false);
    m_maskId = lv_draw_mask_add(&radiusParam, 0);

    //m_pObjMask.reset( lv_objmask_create( lv_disp_get_scr_act( nullptr ), nullptr ) );

    //const std::uint8_t RoundedArea = 240;
    //lv_obj_set_size( m_pObjMask.get(), RoundedArea, RoundedArea );
    //lv_obj_align( m_pObjMask.get(), nullptr, LV_ALIGN_CENTER, 0, 0 );

    //lv_objmask_add_mask( m_pObjMask.get(), &radiusParam );
}

const Theme::IThemeController*
MainWindowView::getThemeController() const
{
    return m_pThemeController.get();
}

Theme::IThemeController*
MainWindowView::getThemeController()
{
    return m_pThemeController.get();
}

std::unique_ptr<IMainWindowView> createMainWindowView()
{
    return std::make_unique<MainWindowView>();
}

}
