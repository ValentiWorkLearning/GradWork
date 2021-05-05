#include "gs_pages_switch.hpp"

#include "ih/gs_itheme_controller.hpp"

#include "ih/pages/gs_iclock_page_view.hpp"
#include "ih/pages/gs_ihealth_page_view.hpp"
#include "ih/pages/gs_iplayer_page_view.hpp"

namespace Graphics::Widgets
{

PagesSwitch::PagesSwitch( const Theme::IThemeController* _themeController )noexcept
	:	WidgetBaseObj<IPagesSwitch>{ _themeController }
    ,	m_pointStyle{}
	, m_pointStyleChecked{}
	,	m_activePageName{}
{
	initStyles();
}

void PagesSwitch::show()noexcept
{
	WidgetBaseObj::show();

	const auto [parent, DisplayWidth, DisplayHeight] = WidgetBaseObj::getShowParams();

	initCheckedPages( parent, DisplayWidth, DisplayHeight );
	initUncheckedPages( parent, DisplayWidth, DisplayHeight );
	setActivePage( m_activePageName );
}

void PagesSwitch::hide()noexcept
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

void PagesSwitch::reloadStyle()noexcept
{
	resetStyle();
	initStyles();
}

void PagesSwitch::setActivePage( std::string_view _pageName )noexcept
{
	if( _pageName == Views::IClockWatchPage::ClockPageName )
	{
		lv_obj_add_state( m_pFirstPage.get(), LV_STATE_CHECKED );
		lv_obj_clear_state( m_pSecondPage.get(), LV_STATE_CHECKED);
		lv_obj_clear_state( m_pThirdPage.get(), LV_STATE_CHECKED);
	}
	else if( _pageName == Views::IHealthWatchPage::HealthPageName ) // TODO migrate to labels/ objects
	{
		lv_obj_clear_state( m_pFirstPage.get(), LV_STATE_CHECKED);
		lv_obj_add_state( m_pSecondPage.get(), LV_STATE_CHECKED );
		lv_obj_clear_state( m_pThirdPage.get(), LV_STATE_CHECKED);
	}
	else if ( _pageName == Views::IPlayerWatchPage::PlayerPageName )
	{
		lv_obj_clear_state( m_pFirstPage.get(), LV_STATE_CHECKED);
		lv_obj_clear_state( m_pSecondPage.get(), LV_STATE_CHECKED);
		lv_obj_add_state( m_pThirdPage.get(), LV_STATE_CHECKED );
	}
	m_activePageName = _pageName;
}

void PagesSwitch::initStyles()noexcept
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

	lv_style_init(&m_pointStyle);
	lv_style_init(&m_pointStyleChecked);

	lv_style_set_bg_color( &m_pointStyleChecked, ThemeDark );
	lv_style_set_bg_color( &m_pointStyle, ThemeLight );

	lv_style_set_bg_grad_color(&m_pointStyle, ThemeLight);
	lv_style_set_bg_grad_color(&m_pointStyleChecked,ThemeDark);

	lv_style_set_bg_opa(&m_pointStyle, LV_OPA_COVER);
	lv_style_set_bg_opa(&m_pointStyleChecked, LV_OPA_COVER);

	lv_style_set_radius( &m_pointStyle, LV_RADIUS_CIRCLE );
	lv_style_set_radius( &m_pointStyleChecked, LV_RADIUS_CIRCLE );

	lv_style_set_border_color(&m_pointStyle, ThemeLight);
	lv_style_set_border_color(&m_pointStyleChecked, ThemeLight);
	
	lv_style_set_bg_opa( &m_pointStyleChecked, LV_OPA_COVER );
	lv_style_set_border_opa( &m_pointStyle, LV_OPA_COVER );

	lv_style_set_border_width( &m_pointStyleChecked, 2 );
	lv_style_set_border_width( &m_pointStyle, 2 );
}

void PagesSwitch::resetStyle()noexcept
{
	Meta::tupleApply(
		[](auto&& _nodeToReset) { 	lv_style_reset( &_nodeToReset ); }
		,   std::forward_as_tuple(
				m_pointStyle
			, m_pointStyleChecked
		)
	);
}

void PagesSwitch::initCheckedPages(
		lv_obj_t* _parentObject
	,	const std::uint32_t _displayWidth
	,	const std::uint32_t _displayHeight
)noexcept
{
	m_pFirstPage.reset( lv_obj_create(_parentObject ) );
	lv_obj_set_size( m_pFirstPage.get(), ArcSize, ArcSize );
	lv_obj_add_style(m_pFirstPage.get(), &m_pointStyle,LV_PART_MAIN|LV_STATE_DEFAULT );
	lv_obj_add_style(m_pFirstPage.get(), &m_pointStyleChecked,LV_PART_MAIN|LV_STATE_CHECKED );


	lv_obj_align(
			m_pFirstPage.get()
		,	LV_ALIGN_BOTTOM_MID
		,	-static_cast<int>( _displayWidth / 12 )
		,	-static_cast<int>( _displayHeight / 10 )
	);
}

void PagesSwitch::initUncheckedPages(
		lv_obj_t* _parentObject
	,	const std::uint32_t _displayWidth
	,	const std::uint32_t _displayHeight
)noexcept
{
	m_pSecondPage.reset( lv_obj_create(_parentObject) );
	lv_obj_set_size( m_pSecondPage.get(), ArcSize, ArcSize );
	lv_obj_add_style( m_pSecondPage.get(), &m_pointStyle ,LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_style( m_pSecondPage.get(), &m_pointStyleChecked, LV_PART_MAIN|LV_STATE_CHECKED);


	lv_obj_align(
			m_pSecondPage.get()
		,	LV_ALIGN_BOTTOM_MID
		,	0
		,	-static_cast<int>(_displayHeight / 10)
	);

	m_pThirdPage.reset( lv_obj_create( _parentObject) );

	lv_obj_set_size( m_pThirdPage.get(), ArcSize, ArcSize );
	lv_obj_add_style( m_pThirdPage.get(), &m_pointStyle,LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_style( m_pThirdPage.get(), &m_pointStyleChecked,LV_PART_MAIN|LV_STATE_CHECKED);


	lv_obj_align(
			m_pThirdPage.get()
		,	LV_ALIGN_BOTTOM_MID
		,	static_cast<int>( _displayWidth / 12)
		,	-static_cast<int>( _displayHeight / 10)
	);
}



std::unique_ptr<IPagesSwitch>
createPagesSwitch(const Theme::IThemeController* _themeController)noexcept
{
	return std::make_unique<PagesSwitch>( _themeController );
}

}
