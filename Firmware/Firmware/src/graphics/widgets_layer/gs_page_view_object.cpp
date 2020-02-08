#include "gs_page_view_object.hpp"

#include "ih/gs_events.hpp"

#include "widgets/battery/gs_battery_widget.hpp"
#include "widgets/battery/gs_battery_handler.hpp"

#include <algorithm>

namespace Graphics::Views
{

void PageViewObject::addWidget(
    const std::shared_ptr<Graphics::Widgets::IWidgetObject>& _pWidget
)
{
    m_pWidgetsStorage.push_back( _pWidget );
}

//void PageViewObject::handleEvent( const Events::TEvent& _tEvent )
//{
//    executeForEachWidget(
//        [&_tEvent]( std::shared_ptr<Graphics::Widgets::IWidgetObject>& _pWidget )
//        {
//                _pWidget->getEventHandler().handleEvent( _tEvent );
//        }
//    );
//}

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
    executeForEachWidget(
        []( std::shared_ptr<Graphics::Widgets::IWidgetObject>& _pWidget )
        {
                _pWidget->hide();
        }
    );
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
