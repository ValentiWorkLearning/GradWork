#include "gs_main_window_event_handler.hpp"

#include "ih/gs_imain_window.hpp"
#include "ih/gs_ipage_view_object.hpp"

#include "ih/pages/gs_iclock_page_view.hpp"
#include "ih/pages/gs_ihealth_page_view.hpp"
#include "ih/pages/gs_iplayer_page_view.hpp"

namespace Graphics::MainWindow
{

MainWindowHandler::MainWindowHandler(IGsMainWindowModel* _pMainWindowModel) noexcept
    : m_pMainWindowModel{_pMainWindowModel}
{
}

void MainWindowHandler::handleEventImpl(
    const Events::TButtonsEvents& _event,
    const std::any& _eventData) noexcept
{
    if (_event != Events::TButtonsEvents::ButtonClicked)
        return;

    Graphics::Events::HardwareButtonId buttonId =
        std::any_cast<Graphics::Events::HardwareButtonId>(_eventData);

    if (buttonId == Graphics::Events::HardwareButtonId::kLeftButtonTop)
        navigateToNextPage();
    else if (buttonId == Graphics::Events::HardwareButtonId::kLeftButtonBottom)
        navigateToPreviousPage();
}

void MainWindowHandler::navigateToNextPage() noexcept
{
    const auto& activePage = m_pMainWindowModel->getActivePage();
    auto activePageName = activePage.getPageName();

    if (activePageName == Graphics::Views::IPlayerWatchPage::PlayerPageName)
        m_pMainWindowModel->setPageActive(Graphics::Views::IClockWatchPage::ClockPageName);
    else if (activePageName == Graphics::Views::IClockWatchPage::ClockPageName)
        m_pMainWindowModel->setPageActive(Graphics::Views::IHealthWatchPage::HealthPageName);
    else if (activePageName == Graphics::Views::IHealthWatchPage::HealthPageName)
        m_pMainWindowModel->setPageActive(Graphics::Views::IPlayerWatchPage::PlayerPageName);
}

void MainWindowHandler::navigateToPreviousPage() noexcept
{
    const auto& activePage = m_pMainWindowModel->getActivePage();
    auto activePageName = activePage.getPageName();

    if (activePageName == Graphics::Views::IClockWatchPage::ClockPageName)
        m_pMainWindowModel->setPageActive(Graphics::Views::IPlayerWatchPage::PlayerPageName);
    else if (activePageName == Graphics::Views::IPlayerWatchPage::PlayerPageName)
        m_pMainWindowModel->setPageActive(Graphics::Views::IHealthWatchPage::HealthPageName);
    else if (activePageName == Graphics::Views::IHealthWatchPage::HealthPageName)
        m_pMainWindowModel->setPageActive(Graphics::Views::IClockWatchPage::ClockPageName);
}

std::unique_ptr<Graphics::IEventHandler> createMainWindowEventHandler(
    IGsMainWindowModel* _pMainWindowModel) noexcept
{
    return std::make_unique<MainWindowHandler>(_pMainWindowModel);
}

} // namespace Graphics::MainWindow