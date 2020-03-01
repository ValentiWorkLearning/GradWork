#include "gs_pages_switch.hpp"

#include "ih/gs_itheme_controller.hpp"

#include "pages/clock_page/gs_iclock_page_view.hpp"
#include "pages/health_page/gs_ihealth_page_view.hpp"

namespace Graphics::Widgets
{

PagesSwitch::PagesSwitch( std::weak_ptr<Theme::IThemeController> _themeController )
	:	WidgetBaseObj<IPagesSwitch>{ _themeController }
{
	initStyles();
}

void PagesSwitch::show()
{
	WidgetBaseObj::show();

	const auto [parent, DisplayWidth, DisplayHeight] = WidgetBaseObj::getShowParams();

	initCheckedPages( parent, DisplayWidth, DisplayHeight );
	initUncheckedPages( parent, DisplayWidth, DisplayHeight );
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

void PagesSwitch::setActivePage( std::string_view _pageName )
{

	if( _pageName == Views::IClockWatchPage::ClockPageName )
	{
		lv_arc_set_style( m_pFirstPage.get(), LV_ARC_STYLE_MAIN, &m_checkedPointStyle );
		lv_arc_set_style( m_pSecondPage.get(), LV_ARC_STYLE_MAIN, &m_uncheckedPointStyle );
		lv_arc_set_style( m_pThirdPage.get(), LV_ARC_STYLE_MAIN, &m_uncheckedPointStyle );
	}
	else if( _pageName == Views::IHealthWatchPage::HealthPageName ) // TODO migrate to labels/ objects
	{
		lv_arc_set_style( m_pFirstPage.get(), LV_ARC_STYLE_MAIN, &m_uncheckedPointStyle );
		lv_arc_set_style( m_pSecondPage.get(), LV_ARC_STYLE_MAIN, &m_checkedPointStyle );
		lv_arc_set_style( m_pThirdPage.get(), LV_ARC_STYLE_MAIN, &m_uncheckedPointStyle );
	}
	else if ( _pageName == "NONENONE" )
	{
		lv_arc_set_style( m_pFirstPage.get(), LV_ARC_STYLE_MAIN, &m_uncheckedPointStyle );
		lv_arc_set_style( m_pSecondPage.get(), LV_ARC_STYLE_MAIN, &m_uncheckedPointStyle );
		lv_arc_set_style( m_pThirdPage.get(), LV_ARC_STYLE_MAIN, &m_checkedPointStyle);
	}
}

void PagesSwitch::initStyles()
{
	auto pThemeProvider = WidgetBaseObj::getThemeController().lock();
	if (!pThemeProvider)
		return;

	lv_style_copy( &m_checkedPointStyle, &lv_style_plain );

	m_checkedPointStyle.line.color = pThemeProvider->getMainThemeColor(
		Theme::Color::MainThemeLight
	);
	m_checkedPointStyle.line.width = 2;
	m_checkedPointStyle.body.radius = LV_RADIUS_CIRCLE;

	lv_style_copy( &m_uncheckedPointStyle, &lv_style_plain );

	m_uncheckedPointStyle.line.color= pThemeProvider->getMainThemeColor(
		Theme::Color::MainThemeLight
	);

	m_uncheckedPointStyle.line.width = 10;
	m_checkedPointStyle.body.radius = LV_RADIUS_CIRCLE;
}

void PagesSwitch::initCheckedPages(
		lv_obj_t* _parentObject
	,	const std::uint32_t _displayWidth
	,	const std::uint32_t _displayHeight
)
{
	m_pFirstPage.reset( lv_arc_create(_parentObject, nullptr ) );
	lv_arc_set_style( m_pFirstPage.get(), LV_ARC_STYLE_MAIN, &m_checkedPointStyle);

	lv_arc_set_angles( m_pFirstPage.get(), 0, 360 );
	lv_obj_set_size( m_pFirstPage.get(), ArcSize, ArcSize );
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
	m_pSecondPage.reset( lv_arc_create(_parentObject, nullptr ) );
	lv_arc_set_style( m_pSecondPage.get(), LV_ARC_STYLE_MAIN, &m_uncheckedPointStyle );

	lv_arc_set_angles( m_pSecondPage.get(), 0, 360 );
	lv_obj_set_size( m_pSecondPage.get(), ArcSize, ArcSize );
	lv_obj_align(
			m_pSecondPage.get()
		,	nullptr
		,	LV_ALIGN_IN_BOTTOM_MID
		,	0
		,	-static_cast<int>(_displayHeight / 10)
	);

	m_pThirdPage.reset( lv_arc_create( _parentObject, nullptr) );

	lv_arc_set_style( m_pThirdPage.get(), LV_ARC_STYLE_MAIN, &m_uncheckedPointStyle);

	lv_arc_set_angles( m_pThirdPage.get(), 0, 360);
	lv_obj_set_size( m_pThirdPage.get(), ArcSize, ArcSize);
	lv_obj_set_style( m_pThirdPage.get(), &m_uncheckedPointStyle );
	lv_obj_align(
			m_pThirdPage.get()
		,	nullptr
		,	LV_ALIGN_IN_BOTTOM_MID
		,	static_cast<int>( _displayWidth / 12)
		,	-static_cast<int>( _displayHeight / 10)
	);
}



std::shared_ptr<IPagesSwitch>
createPagesSwitch(std::weak_ptr<Theme::IThemeController> _themeController)
{
	return std::make_shared<PagesSwitch>( _themeController );
}

}