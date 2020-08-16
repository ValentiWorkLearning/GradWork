#include "pages_stub_pages_creator.hpp"

#include "pages/clock_watch_fake_view.hpp"
#include "pages/health_watch_fake_view.hpp"
#include "pages/player_watch_fake_view.hpp"

namespace Graphics::StubViews
{

StubPagesCreator::~StubPagesCreator() = default;

std::unique_ptr<Graphics::Views::IClockWatchPage>
StubPagesCreator::createClockPage(Graphics::Theme::IThemeController * _pThemeController)
{
	return std::make_unique<FakeClockPage>( Graphics::Views::IClockWatchPage::ClockPageName );
}

std::unique_ptr<Graphics::Views::IHealthWatchPage>
StubPagesCreator::createHealthPage(Graphics::Theme::IThemeController* _pThemeController)
{
	return std::make_unique<FakeHealthPage>( Graphics::Views::IHealthWatchPage::HealthPageName );
}

std::unique_ptr<Graphics::Views::IPlayerWatchPage>
StubPagesCreator::createPlayerPage(Graphics::Theme::IThemeController* _pThemeController)
{
	return std::make_unique<FakePlayerPage>( Graphics::Views::IPlayerWatchPage::PlayerPageName );
}


Graphics::Views::IPagesCreator::Ptr createStubPagesCreator()
{
	return std::make_unique<StubPagesCreator>();
}

}