#include "gs_clock_page_view.hpp"

namespace Graphics::Views
{

void ClockWatch::show()
{
	PageViewObject::show();
	//here show for the concrete widgets
}


void ClockWatch::hide()
{
	PageViewObject::hide();
	//here hide for the concrete widgets
}

std::unique_ptr<IPageViewObject> createClockWatchView()
{
	return std::make_unique<ClockWatch>();
}

}