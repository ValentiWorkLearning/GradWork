#pragma once

#include "ih/gs_ievent_handler.hpp"

#include "gs_event_handler_base.hpp"

#include <memory>

namespace Graphics::MainWindow
{
class IGsMainWindowModel;
}

namespace Graphics::MainWindow
{

class IBatteryWidget;

class MainWindowHandler
    : public Events::EventHandler<Graphics::IEventHandler, Events::TButtonsEvents>
{

public:
    explicit MainWindowHandler(IGsMainWindowModel* _pMainWindowModel) noexcept;

    ~MainWindowHandler() override = default;

protected:
    void handleEventImpl(const Events::TButtonsEvents& _event, const std::any& _eventData) noexcept
        override;

private:
    void navigateToNextPage() noexcept;

    void navigateToPreviousPage() noexcept;

private:
    IGsMainWindowModel* m_pMainWindowModel;
};

std::unique_ptr<Graphics::IEventHandler> createMainWindowEventHandler(IGsMainWindowModel*) noexcept;

}; // namespace Graphics::MainWindow
