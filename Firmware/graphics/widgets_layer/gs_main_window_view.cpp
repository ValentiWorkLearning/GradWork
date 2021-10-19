#include "gs_main_window_view.hpp"

#include "gs_theme_controller.hpp"

namespace Graphics::MainWindow
{

MainWindowView::MainWindowView() noexcept
    : m_pThemeController{Theme::createThemeController(Theme::ColorTheme::Night, Width, Height)}
    , m_iniStyle{}
    , m_yanStyle{}
    , m_iniCircleStyle{}
    , m_yanCircleStyle{}
    , maskArea{0, 0, 240, 240}
    , radiusParam{}
{
    initMask();
    initBackground();
}

void MainWindowView::initBackground() noexcept
{

    auto createAlignedRect = [this](auto _aligmentType, lv_style_t* _style) {
        lv_obj_t* pObject{nullptr};
        auto parent = m_pWindowRoot.get();

        pObject = lv_obj_create(parent);
        lv_obj_set_size(pObject, MainWindowView::Width, MainWindowView::Height / 2);

        lv_obj_add_style(pObject, _style, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_align(pObject, _aligmentType, 0, 0);

        return pObject;
    };

    const auto MainThemeDark =
        m_pThemeController->getMainThemeColor(Graphics::Theme::Color::MainThemeDark);
    const auto MainThemeLight =
        m_pThemeController->getMainThemeColor(Graphics::Theme::Color::MainThemeLight);

    lv_style_init(&m_iniStyle);
    lv_style_set_bg_opa(&m_iniStyle, LV_OPA_COVER);
    lv_style_set_bg_color(&m_iniStyle, MainThemeDark);
    lv_style_set_bg_grad_color(&m_iniStyle, MainThemeDark);
    lv_style_set_border_width(&m_iniStyle, 0);

    lv_style_init(&m_yanStyle);
    lv_style_set_bg_color(&m_yanStyle, MainThemeLight);
    lv_style_set_bg_grad_color(&m_yanStyle, MainThemeLight);
    lv_style_set_bg_opa(&m_yanStyle, LV_OPA_COVER);
    lv_style_set_border_width(&m_yanStyle, 0);

    m_pIny.reset(createAlignedRect(LV_ALIGN_BOTTOM_MID, &m_iniStyle));
    m_pYan.reset(createAlignedRect(LV_ALIGN_TOP_MID, &m_yanStyle));

    auto createAlignedCircle = [this](auto _aligmentType, lv_style_t* _style) {
        auto parent = m_pWindowRoot.get();
        lv_obj_t* pCircle = lv_obj_create(parent);

        lv_obj_set_size(pCircle, MainWindowView::Width / 2, MainWindowView::Height / 2);

        lv_obj_add_style(pCircle, _style, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_align(pCircle, _aligmentType, 0, 0);

        return pCircle;
    };

    lv_style_init(&m_iniCircleStyle);
    lv_style_set_bg_opa(&m_iniCircleStyle, LV_OPA_COVER);
    lv_style_set_bg_color(&m_iniCircleStyle, MainThemeDark);
    lv_style_set_border_color(&m_iniCircleStyle, MainThemeDark);
    lv_style_set_bg_grad_color(&m_iniCircleStyle, MainThemeDark);
    lv_style_set_radius(&m_iniCircleStyle, LV_RADIUS_CIRCLE);
    lv_style_set_border_width(&m_iniCircleStyle, 0);

    lv_style_init(&m_yanCircleStyle);
    lv_style_set_bg_opa(&m_yanCircleStyle, LV_OPA_COVER);
    lv_style_set_bg_color(&m_yanCircleStyle, MainThemeLight);
    lv_style_set_border_color(&m_yanCircleStyle, MainThemeLight);
    lv_style_set_bg_grad_color(&m_yanCircleStyle, MainThemeLight);
    lv_style_set_radius(&m_yanCircleStyle, LV_RADIUS_CIRCLE);
    lv_style_set_border_width(&m_yanCircleStyle, 0);

    m_pInyCircle.reset(createAlignedCircle(LV_ALIGN_RIGHT_MID, &m_iniCircleStyle));
    m_pYanCircle.reset(createAlignedCircle(LV_ALIGN_LEFT_MID, &m_yanCircleStyle));
}

void MainWindowView::resetBackgroundStyle() noexcept
{
    Meta::tupleApply(
        [](auto&& _nodeToReset) { lv_style_reset(&_nodeToReset); },
        std::forward_as_tuple(m_iniStyle, m_yanStyle, m_iniCircleStyle, m_yanCircleStyle));
}

void MainWindowView::initMask() noexcept
{
    m_pWindowRoot.reset(lv_obj_create(lv_scr_act()));
    auto container = m_pWindowRoot.get();
    lv_obj_set_size(container,  MainWindowView::Width,  MainWindowView::Height);
    lv_obj_center(container);
    lv_obj_set_style_radius(container, LV_RADIUS_CIRCLE, LV_PART_MAIN);
    lv_obj_set_scrollbar_mode(container,LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_pad_all(container,0,LV_PART_MAIN);
    lv_obj_set_style_clip_corner(container,true,LV_PART_MAIN);
    lv_obj_set_style_border_width(container,0,LV_PART_MAIN);

// The drawing mask implementation causes the crash with the access violation.
// For the current LVGL 8.0 latest version the solution hasn't been found
// The best we can do now is an attempt to use the container for all of the widgtes with the given set of styles

//    constexpr std::uint8_t RoundedArea = 240;
//    lv_draw_mask_radius_init(&radiusParam, &maskArea, RoundedArea, false);
//    m_maskId = lv_draw_mask_add(&radiusParam, nullptr);

    // m_pObjMask.reset( lv_objmask_create( lv_disp_get_scr_act( nullptr ), nullptr ) );

    // const std::uint8_t RoundedArea = 240;
    // lv_obj_set_size( m_pObjMask.get(), RoundedArea, RoundedArea );
    // lv_obj_align( m_pObjMask.get(), nullptr, LV_ALIGN_CENTER, 0, 0 );

    // lv_objmask_add_mask( m_pObjMask.get(), &radiusParam );
}

const Theme::IThemeController* MainWindowView::getThemeController() const noexcept
{
    return m_pThemeController.get();
}

Theme::IThemeController* MainWindowView::getThemeController() noexcept
{
    return m_pThemeController.get();
}

std::unique_ptr<IMainWindowView> createMainWindowView() noexcept
{
    return std::make_unique<MainWindowView>();
}

} // namespace Graphics::MainWindow
