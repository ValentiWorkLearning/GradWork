#pragma once

#include "ih/gs_iwidget_object.hpp"
#include "ih/gs_itheme_controller.hpp"

#include <string>

template <typename BaseWidgetStub>
class FakeBaseWidget
	:	public BaseWidgetStub
{

public:

	void reloadStyle() override {}

	void show() override
	{
		m_isVisible = true;
	}
	void hide() override
	{
		m_isVisible = false;
	}

	bool isVisible() const override
	{
		return m_isVisible;
	}

	const Graphics::Theme::IThemeController* getThemeController() const override
	{
		return nullptr;
	}

private:

	bool m_isVisible = false;
};