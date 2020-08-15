#pragma once
#include <gtest/gtest.h>

#include "ih/drivers/ih_button_driver.hpp"

#include "ih/gs_events.hpp"
#include "ih/gs_ievent_handler.hpp"

#include "ih/gs_imain_window.hpp"

#include "gs_event_dispatcher.hpp"

#include "widgets_stub_pages_creator.hpp"
#include "pages_stub_pages_creator.hpp"

#include "widgets_layer/gs_main_window.hpp"
#include "mainwindow_fakes.hpp"

#include <memory>

class MainWindowTest
	: public ::testing::Test
{

protected:

	void SetUp() override
	{
		auto pMainWindowView = Graphics::StubMainWindow::createFakeMainWindowView();
		auto pStubWidgetsCreator = Graphics::StubWidgets::createStubWidgetsCreator();
		auto pStubPagesCreator = Graphics::StubViews::createStubPagesCreator();

		m_pMainWindow = Graphics::MainWindow::createMainWindow(
				std::move( pMainWindowView )
			,	std::move( pStubWidgetsCreator )
			,	std::move( pStubPagesCreator )
		);
	}

protected:

	std::unique_ptr<Graphics::MainWindow::IGsMainWindowModel> m_pMainWindow;
};