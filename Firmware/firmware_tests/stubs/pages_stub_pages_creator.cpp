#include "pages_stub_pages_creator.hpp"

#include "ih/pages/gs_iclock_page_view.hpp"
#include "ih/pages/gs_ihealth_page_view.hpp"
#include "ih/pages/gs_iplayer_page_view.hpp"

namespace Graphics::StubViews
{

StubPagesCreator::~StubPagesCreator() = default;

std::unique_ptr<Graphics::Views::IClockWatchPage>
StubPagesCreator::createClockPage(Graphics::Theme::IThemeController * _pThemeController)
{
	return nullptr;
}

std::unique_ptr<Graphics::Views::IHealthWatchPage>
StubPagesCreator::createHealthPage(Graphics::Theme::IThemeController* _pThemeController)
{
	return nullptr;
}

std::unique_ptr<Graphics::Views::IPlayerWatchPage>
StubPagesCreator::createPlayerPage(Graphics::Theme::IThemeController* _pThemeController)
{
	return nullptr;
}


Graphics::Views::IPagesCreator::Ptr createStubPagesCreator()
{
	return std::make_unique<StubPagesCreator>();
}

}