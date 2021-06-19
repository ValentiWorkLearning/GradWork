#pragma once

#include "ih/gs_ipage_view_object.hpp"

#include <etl/vector.h>
#include <vector>

#include <functional>
#include <lvgl.h>

namespace Graphics::Events
{
struct TEvent;
}

namespace Graphics::Views
{

template <typename ConcretePageView> class PageViewObject : public ConcretePageView
{

public:
    explicit PageViewObject(
        const Theme::IThemeController* _themeController,
        std::string_view _pageName) noexcept;

    ~PageViewObject() override = default;

public:
    void addWidget(Graphics::Widgets::IWidgetObject* _pWidget) noexcept override;

    void show() noexcept override;

    void hide() noexcept override;

    void reloadStyle() noexcept override;

public:
    std::string_view getPageName() const noexcept override;

    bool isVisible() const noexcept override;

    const Theme::IThemeController* getThemeController() const noexcept override;

protected:
    virtual void resetStyle() noexcept = 0;

    virtual void initStyles() noexcept = 0;

    virtual void initPageWidgets(
        lv_obj_t* _parent,
        const std::uint32_t _displayWidth,
        const std::uint32_t _displayHeight) noexcept = 0;

    virtual void unloadWidgets() noexcept = 0;

private:
    void executeForEachWidget(
        std::function<void(Graphics::Widgets::IWidgetObject*)> _toCall) noexcept;

    static constexpr int WidgetsQuantity = 3;
    using TWidgetsStorage = etl::vector<Graphics::Widgets::IWidgetObject*, WidgetsQuantity>;
    TWidgetsStorage m_pWidgetsStorage;

private:
    bool m_isPageVisible;
    std::string_view m_pageName;
    const Theme::IThemeController* m_pThemeController;
};

}; // namespace Graphics::Views
