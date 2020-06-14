#pragma once

#include "ih/gs_ievent_handler.hpp"

#include "utils/TimeWrapper.hpp"

#include <memory>

namespace Graphics::Views
{

class IClockWatchPage;

class ClockPageHandler
    :   public Graphics::IEventHandler
{

public:

    explicit ClockPageHandler( IClockWatchPage* _clockPageView );

    ~ClockPageHandler() override = default;

public:

    void handleEvent( const Events::TEvent& _event ) override;

private:

    bool shouldApplyNewDate( const TimeWrapper& _toCheck );

    static std::string formatToFullDate( const TimeWrapper& _toFormat );

    static std::string formatDoubleDigitsNumber( std::uint8_t _toFormat );

private:

    bool forceUpdateAfterVisibilityChange;
    IClockWatchPage* m_pClockWatchView;

    TimeWrapper m_lastReceivedTime;
    std::string m_fullDateString;
};

std::unique_ptr<Graphics::IEventHandler>
createPageWatchHandler( IClockWatchPage* _clockPage);

};
