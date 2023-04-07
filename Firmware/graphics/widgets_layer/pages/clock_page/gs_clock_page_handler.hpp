#pragma once

#include "ih/gs_events.hpp"
#include "ih/gs_ievent_handler.hpp"

#include "widgets_layer/gs_event_handler_base.hpp"

#include "utils/TimeWrapper.hpp"

#include <memory>

namespace Graphics::Views
{

class IClockWatchPage;

class ClockPageHandler
    : public Events::EventHandler<Graphics::IEventHandler, Events::TDateTimeEvents>
{

public:
    explicit ClockPageHandler(IClockWatchPage* _clockPageView) noexcept;

    ~ClockPageHandler() override = default;

public:
    void initSubscriptions(Events::EventDispatcher& eventDispatcher) override;

    void deinitHandler() override;

protected:
    void handleEventImpl(const Events::TDateTimeEvents& _event, const std::any& _eventData) noexcept
        override;

private:
    bool shouldApplyNewDate(const TimeWrapper& _toCheck) noexcept;

    static std::string formatToFullDate(const TimeWrapper& _toFormat) noexcept;

    static std::string formatDoubleDigitsNumber(std::uint8_t _toFormat) noexcept;

private:
    bool m_forceUpdateAfterVisibilityChange;
    IClockWatchPage* m_pClockWatchView;

    TimeWrapper m_lastReceivedTime;
    std::string m_fullDateString;
};

Graphics::TEventHandlerPtr createPageWatchHandler(IClockWatchPage* _clockPage) noexcept;

}; // namespace Graphics::Views
