#pragma once

#include "base_stub_widget.hpp"

#include "ih/widgets/gs_ipages_switch.hpp"

class PagesSwitchWidgetStub : public FakeBaseWidget<Graphics::Widgets::IPagesSwitch>
{
public:
    void setActivePage(std::string_view _pageName) override
    {
    }
};