#pragma once
#include "ih/gs_imain_window.hpp"
#include "ih/gs_itheme_controller.hpp"

#include <utils/MetaUtils.hpp>

namespace Graphics::MainWindow
{

class MainWindowView : public IMainWindowView
{

public:
    MainWindowView() noexcept;

    virtual ~MainWindowView() = default;

public:
    void initBackground() noexcept override;

    void resetBackgroundStyle() noexcept override;

public:
    const Theme::IThemeController* getThemeController() const noexcept override;

    Theme::IThemeController* getThemeController() noexcept override;

private:
    static constexpr inline std::uint32_t Width = LV_HOR_RES_MAX;
    static constexpr inline std::uint32_t Height = LV_VER_RES_MAX;

private:
    void initMask() noexcept;

private:
    std::unique_ptr<Theme::IThemeController> m_pThemeController;

private:
    lv_style_t m_iniStyle;
    lv_style_t m_yanStyle;
    lv_style_t m_iniCircleStyle;
    lv_style_t m_yanCircleStyle;
    lv_area_t maskArea;
    std::uint16_t m_maskId;

    lv_draw_mask_radius_param_t radiusParam;
    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pWindowRoot;
    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pIny;
    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pInyCircle;
    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pYan;
    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pYanCircle;
    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pObjMask;
};

std::unique_ptr<IMainWindowView> createMainWindowView() noexcept;

} // namespace Graphics::MainWindow
