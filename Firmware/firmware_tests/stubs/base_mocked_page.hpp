#pragma once

#include <gmock/gmock.h>

#include "ih/gs_ipage_view_object.hpp"

#include "ih/gs_iwidget_object.hpp"
#include "ih/gs_itheme_controller.hpp"

#include <string>

template <typename PageBaseFake >
class FakeBasePage
	: public PageBaseFake
{

public:

	FakeBasePage( std::string_view _pageName )
		:	m_isVisible{ false }
		,	m_pageName{ _pageName }
	{

	}

	void addWidget( Graphics::Widgets::IWidgetObject* _pWidget )noexcept override
	{
	}

	bool isVisible() const noexcept override
	{
		return m_isVisible;
	}

	void reloadStyle()noexcept override {}

	void show()noexcept override
	{
		m_isVisible = true;
	}
	void hide()noexcept override
	{
		m_isVisible = false;
	}

	std::string_view getPageName() const noexcept override
	{
		return m_pageName;
	}

public:

	const Graphics::Theme::IThemeController* getThemeController() const noexcept override
	{
		return nullptr;
	}

private:
	bool m_isVisible;
	std::string_view m_pageName;
};

template <typename PageBaseFake >
class FakeBasePageMock
	: public PageBaseFake
{

public:

	MOCK_METHOD(void,addWidget, (Graphics::Widgets::IWidgetObject*),(noexcept));
	MOCK_METHOD(bool,isVisible, (), (const,noexcept));

	void reloadStyle()noexcept override {}

	void show()noexcept override {}
	void hide()noexcept override {}

public:

	MOCK_CONST_METHOD0(getPageName, std::string_view());
	MOCK_CONST_METHOD0(getThemeController, const Graphics::Theme::IThemeController* ());

};