#include "gs_page_view_object.hpp"

#include "widgets/gs_battery_widget.hpp"

#include <algorithm>

namespace Graphics::Views
{

void PageViewObject::addWidget(
    const std::shared_ptr<Graphics::Widgets::IWidgetObject>& _pWidget
)
{
    m_pWidgetsStorage.push_back( _pWidget );
}

void PageViewObject::handleEvent( const EventDispatcher::Events::Event& _tEvent )
{
    executeForEachWidget(
        [&_tEvent]( std::shared_ptr<Graphics::Widgets::IWidgetObject>& _pWidget )
        {
                _pWidget->handleEvent( _tEvent );
        }
    );
}

void PageViewObject::show()
{
    executeForEachWidget(
        []( std::shared_ptr<Graphics::Widgets::IWidgetObject>& _pWidget )
        {
                _pWidget->show();
        }
    );
}

void PageViewObject::hide()
{

}

void PageViewObject::executeForEachWidget(
    std::function<void(std::shared_ptr<Graphics::Widgets::IWidgetObject>&)> _toCall
)
{
    std::for_each(
            m_pWidgetsStorage.begin()
        ,   m_pWidgetsStorage.end()
        ,   _toCall
    );
}

};
