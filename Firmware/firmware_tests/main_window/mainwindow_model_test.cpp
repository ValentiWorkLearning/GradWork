#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "mainwindow_fakes.hpp"
#include "mainwindow_fixture.hpp"

#include "ih/pages/gs_iclock_page_view.hpp"

TEST_F(MainWindowTest, InitialSetupMainWindow)
{
    m_pMainWindow->setPageActive(
        Graphics::Views::IClockWatchPage::ClockPageName
    );
    ASSERT_EQ( m_pMainWindow->getActivePage().getPageName(), Graphics::Views::IClockWatchPage::ClockPageName );
}
