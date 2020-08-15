#include "gs_pages_creator.hpp"

#include "widgets_layer/pages/clock_page/gs_clock_page_view.hpp"
#include "widgets_layer/pages/health_page/gs_health_page_view.hpp"
#include "widgets_layer/pages/player_page/gs_player_page_view.hpp"

namespace Graphics::Views
{
LvglPagesCreator::~LvglPagesCreator() = default;

std::unique_ptr<Graphics::Views::IClockWatchPage>
LvglPagesCreator::createClockPage(Theme::IThemeController* _pThemeController)
{
	return Views::createClockWatchView( _pThemeController );
}
std::unique_ptr<Graphics::Views::IHealthWatchPage>
LvglPagesCreator::createHealthPage(Theme::IThemeController* _pThemeController)
{
	return  Views::createHeartrateWatchView( _pThemeController );
}
std::unique_ptr<Graphics::Views::IPlayerWatchPage>
LvglPagesCreator::createPlayerPage(Theme::IThemeController* _pThemeController)
{
	return Views::createPlayerWatchView( _pThemeController );
}
IPagesCreator::Ptr createLvglPagesCreator()
{
	return std::make_unique<LvglPagesCreator>();
}
}