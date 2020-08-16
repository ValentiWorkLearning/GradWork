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

	void addWidget( Graphics::Widgets::IWidgetObject* _pWidget ) override
	{
	}

	bool isVisible() const override
	{
		return m_isVisible;
	}

	void reloadStyle() override {}

	void show() override
	{
		m_isVisible = true;
	}
	void hide() override
	{
		m_isVisible = false;
	}

	std::string_view getPageName() const override
	{
		return m_pageName;
	}

public:

	const Graphics::Theme::IThemeController* getThemeController() const override
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

	MOCK_METHOD1(addWidget, void(Graphics::Widgets::IWidgetObject* _pWidget));
	MOCK_CONST_METHOD0(isVisible, bool());

	void reloadStyle() override {}

	void show() override {}
	void hide() override {}

public:

	MOCK_CONST_METHOD0(getPageName, std::string_view());
	MOCK_CONST_METHOD0(getThemeController, const Graphics::Theme::IThemeController* ());

};