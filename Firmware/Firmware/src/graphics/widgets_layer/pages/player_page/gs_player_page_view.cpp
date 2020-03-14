#include "gs_player_page_view.hpp"

#include "ih/gs_itheme_controller.hpp"

#include "IconFont16px.hpp"
#include "IconFont35px.hpp"

namespace Graphics::Views
{

PlayerPage::PlayerPage( std::weak_ptr<Theme::IThemeController> _themeController )
	:	PageViewObject<IPlayerWatchPage>{ _themeController, IPlayerWatchPage::PlayerPageName }
{
	initStyles();
}

void PlayerPage::show()
{
	PageViewObject::show();

	auto parent = lv_disp_get_scr_act( nullptr );

	auto pThemeProvider = PageViewObject::getThemeController();
	if (!pThemeProvider )
		return;

	const std::uint32_t DisplayWidth { pThemeProvider->getDisplayWidth() };
	const std::uint32_t DisplayHeight { pThemeProvider->getDisplayHeight() };

	initPageTitle( parent, DisplayWidth, DisplayHeight );
}

void PlayerPage::hide()
{
	PageViewObject::hide();

	/*Meta::tupleApply(
			[]( auto&& _nodeToReset ){ _nodeToReset.reset(); }
		,	std::forward_as_tuple(
				m_pHealthPageLabel
			,	m_pHealthPageIcon
			,	m_pHeartBeatsLabel
			,	m_pHeartBeatsTooltip
			,	m_pPulseIcon
			,	m_pStepsLabel
			,	m_pStepsTooltip
			,	m_pStepsIcon
			,	m_pKcalLabel
			,	m_pKcalTooltip
		)
	);*/
}

void PlayerPage::setPause()
{
}

void PlayerPage::setPlaying()
{
}

void PlayerPage::initStyles()
{
}

void PlayerPage::initPageTitle(lv_obj_t* _parentObject, const std::uint32_t _displayWidth, const std::uint32_t _displayHeight)
{
}

std::shared_ptr<IPlayerWatchPage>
createPlayerWatchView( std::weak_ptr<Theme::IThemeController> _themeController )
{
	return std::make_shared<PlayerPage>( _themeController );
}

}