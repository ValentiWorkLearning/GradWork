#include "gs_pages_switch.hpp"

#include "ih/gs_itheme_controller.hpp"

#include "pages/clock_page/gs_iclock_page_view.hpp"
#include "pages/health_page/gs_ihealth_page_view.hpp"
#include "pages/player_page/gs_iplayer_page_view.hpp"

namespace Graphics::Widgets
{

PagesSwitch::PagesSwitch( const Theme::IThemeController* _themeController )
	:	WidgetBaseObj<IPagesSwitch>{ _themeController }
	,	m_activePageName{}
	,	m_pointStyle{}
{
	initStyles();
}

void PagesSwitch::show()
{
	WidgetBaseObj::show();

	const auto [parent, DisplayWidth, DisplayHeight] = WidgetBaseObj::getShowParams();

	initCheckedPages( parent, DisplayWidth, DisplayHeight );
	initUncheckedPages( parent, DisplayWidth, DisplayHeight );
	setActivePage( m_activePageName );
}

void PagesSwitch::hide()
{
	WidgetBaseObj::hide();

	Meta::tupleApply(
		[]( auto&& _nodeToReset ){ _nodeToReset.reset(); }
		,   std::forward_as_tuple(
				m_pFirstPage
			,	m_pSecondPage
			,	m_pThirdPage
		)
	);
}

void PagesSwitch::reloadStyle()
{
	resetStyle();
	initStyles();
}

void PagesSwitch::setActivePage( std::string_view _pageName )
{
	if( _pageName == Views::IClockWatchPage::ClockPageName )
	{
		lv_obj_set_state( m_pFirstPage.get(), LV_STATE_CHECKED );
		lv_obj_set_state( m_pSecondPage.get(), LV_STATE_DEFAULT );
		lv_obj_set_state( m_pThirdPage.get(), LV_STATE_DEFAULT );
	}
	else if( _pageName == Views::IHealthWatchPage::HealthPageName ) // TODO migrate to labels/ objects
	{
		lv_obj_set_state( m_pFirstPage.get(), LV_STATE_DEFAULT );
		lv_obj_set_state( m_pSecondPage.get(), LV_STATE_CHECKED );
		lv_obj_set_state( m_pThirdPage.get(), LV_STATE_DEFAULT );
	}
	else if ( _pageName == Views::IPlayerWatchPage::PlayerPageName )
	{
		lv_obj_set_state( m_pFirstPage.get(), LV_STATE_DEFAULT );
		lv_obj_set_state( m_pSecondPage.get(), LV_STATE_DEFAULT );
		lv_obj_set_state( m_pThirdPage.get(), LV_STATE_CHECKED );
	}
	m_activePageName = _pageName;
}

void PagesSwitch::initStyles()
{
	auto pThemeProvider = WidgetBaseObj::getThemeController();
	if (!pThemeProvider)
		return;

	const auto ThemeDark = pThemeProvider->getMainThemeColor(
			Theme::Color::MainThemeDark
		);
	const auto ThemeLight = pThemeProvider->getMainThemeColor(
			Theme::Color::MainThemeLight
		);

	
	lv_style_set_bg_color( &m_pointStyle, LV_STATE_CHECKED, ThemeDark );
	lv_style_set_bg_color( &m_pointStyle, LV_STATE_DEFAULT, ThemeLight );

	lv_style_set_bg_grad_color(&m_pointStyle, LV_STATE_DEFAULT, ThemeLight);
	lv_style_set_bg_grad_color(&m_pointStyle, LV_STATE_CHECKED, ThemeDark);

	lv_style_set_bg_opa(&m_pointStyle, LV_STATE_DEFAULT, LV_OPA_COVER);

	lv_style_set_radius( &m_pointStyle, LV_STATE_DEFAULT, LV_RADIUS_CIRCLE );
	lv_style_set_radius( &m_pointStyle, LV_STATE_CHECKED, LV_RADIUS_CIRCLE );

	lv_style_set_border_color(&m_pointStyle, LV_STATE_DEFAULT, ThemeLight);
	lv_style_set_border_color(&m_pointStyle, LV_STATE_CHECKED, ThemeLight);
	
	lv_style_set_bg_opa( &m_pointStyle, LV_STATE_CHECKED, LV_OPA_COVER );
	lv_style_set_border_opa( &m_pointStyle, LV_STATE_DEFAULT, LV_OPA_COVER );

	lv_style_set_border_width( &m_pointStyle, LV_STATE_CHECKED, 2 );
}

void PagesSwitch::resetStyle()
{
	Meta::tupleApply(
		[](auto&& _nodeToReset) { 	lv_style_reset( &_nodeToReset ); }
		,   std::forward_as_tuple(
				m_pointStyle
		)
	);
}

void PagesSwitch::initCheckedPages(
		lv_obj_t* _parentObject
	,	const std::uint32_t _displayWidth
	,	const std::uint32_t _displayHeight
)
{
	m_pFirstPage.reset( lv_obj_create(_parentObject, nullptr ) );
	lv_obj_set_size( m_pFirstPage.get(), ArcSize, ArcSize );
	lv_obj_add_style(m_pFirstPage.get(), LV_OBJ_PART_MAIN, &m_pointStyle);


	lv_obj_align(
			m_pFirstPage.get()
		,	nullptr
		,	LV_ALIGN_IN_BOTTOM_MID
		,	-static_cast<int>( _displayWidth / 12 )
		,	-static_cast<int>( _displayHeight / 10 )
	);
}

void PagesSwitch::initUncheckedPages(
		lv_obj_t* _parentObject
	,	const std::uint32_t _displayWidth
	,	const std::uint32_t _displayHeight
)
{
	m_pSecondPage.reset( lv_obj_create(_parentObject, nullptr ) );
	lv_obj_set_size( m_pSecondPage.get(), ArcSize, ArcSize );
	lv_obj_add_style( m_pSecondPage.get(), LV_OBJ_PART_MAIN, &m_pointStyle);


	lv_obj_align(
			m_pSecondPage.get()
		,	nullptr
		,	LV_ALIGN_IN_BOTTOM_MID
		,	0
		,	-static_cast<int>(_displayHeight / 10)
	);

	m_pThirdPage.reset( lv_obj_create( _parentObject, nullptr) );

	lv_obj_set_size( m_pThirdPage.get(), ArcSize, ArcSize );
	lv_obj_add_style( m_pThirdPage.get(), LV_OBJ_PART_MAIN, &m_pointStyle);


	lv_obj_align(
			m_pThirdPage.get()
		,	nullptr
		,	LV_ALIGN_IN_BOTTOM_MID
		,	static_cast<int>( _displayWidth / 12)
		,	-static_cast<int>( _displayHeight / 10)
	);
}



std::unique_ptr<IPagesSwitch>
createPagesSwitch(const Theme::IThemeController* _themeController)
{
	return std::make_unique<PagesSwitch>( _themeController );
}

}