#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "mainwindow_fakes.hpp"
#include "mainwindow_fixture.hpp"

#include "ih/pages/gs_iclock_page_view.hpp"
#include "ih/pages/gs_ihealth_page_view.hpp"
#include "ih/pages/gs_iplayer_page_view.hpp"

TEST_F(MainWindowTest, InitialSetupMainWindow)
{
    ASSERT_EQ(
            m_pMainWindow->getActivePage().getPageName()
        ,   Graphics::Views::IClockWatchPage::ClockPageName
    );
}

TEST_F(MainWindowTest, ChangeActivePage)
{
    m_pMainWindow->setPageActive(
        Graphics::Views::IHealthWatchPage::HealthPageName
    );

    ASSERT_EQ(
            m_pMainWindow->getActivePage().getPageName()
        ,   Graphics::Views::IHealthWatchPage::HealthPageName
    );
}

TEST_F( MainWindowTest, HandleNavigateToNextPage_ButtonClickEvent )
{
    m_pMainWindow->getEventDispatcher().postEvent(
        {
                Graphics::Events::EventGroup::Buttons
            ,   Graphics::Events::TButtonsEvents::ButtonClicked
            ,   Graphics::Events::HardwareButtonId::kLeftButtonTop
        }
    );

    m_pMainWindow->getEventDispatcher().processEventQueue();

    ASSERT_EQ (
            m_pMainWindow->getActivePage().getPageName()
        ,   Graphics::Views::IHealthWatchPage::HealthPageName
    );
}


TEST_F(MainWindowTest, HandleNavigateNextFromLastPage_ButtonClickEvent)
{
    m_pMainWindow->setPageActive(
        Graphics::Views::IPlayerWatchPage::PlayerPageName
    );

    m_pMainWindow->getEventDispatcher().postEvent(
        {
                Graphics::Events::EventGroup::Buttons
            ,   Graphics::Events::TButtonsEvents::ButtonClicked
            ,   Graphics::Events::HardwareButtonId::kLeftButtonTop
        }
    );

    m_pMainWindow->getEventDispatcher().processEventQueue();

    ASSERT_EQ(
            m_pMainWindow->getActivePage().getPageName()
        ,   Graphics::Views::IClockWatchPage::ClockPageName
    );
}

TEST_F(MainWindowTest, HandleNavigateToPreviousPageFromInitialState_ButtonClickEvent)
{
    m_pMainWindow->getEventDispatcher().postEvent(
        {
                Graphics::Events::EventGroup::Buttons
            ,   Graphics::Events::TButtonsEvents::ButtonClicked
            ,   Graphics::Events::HardwareButtonId::kLeftButtonBottom
        }
    );

    m_pMainWindow->getEventDispatcher().processEventQueue();

    ASSERT_EQ(
            m_pMainWindow->getActivePage().getPageName()
        ,   Graphics::Views::IPlayerWatchPage::PlayerPageName
    );
}