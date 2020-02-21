#include "gs_clock_page_view.hpp"
#include "ih/gs_itheme_controller.hpp"

namespace Graphics::Views
{

ClockWatch::ClockWatch( std::weak_ptr<Theme::IThemeController> _themeController )
	:	PageViewObject{ _themeController }
{
	initStyles();
}

void ClockWatch::show()
{
	PageViewObject::show();

	auto parent = lv_disp_get_scr_act( nullptr );

	auto pThemeProvider = PageViewObject::getThemeController();
	if (!pThemeProvider )
		return;

	const std::uint32_t DisplayWidth { pThemeProvider->getDisplayWidth() };
	const std::uint32_t DisplayHeight { pThemeProvider->getDisplayHeight() };

	initClockLabels( parent, DisplayWidth, DisplayHeight );
	initFullDateLabel( parent, DisplayWidth, DisplayHeight );
	initWeekDayLabel( parent, DisplayWidth, DisplayHeight );

	lv_label_set_text(m_pHoursLabel.get(), "22");
	lv_label_set_text(m_pMinutesLabel.get(), "18");
	lv_label_set_text(m_pSecondsLabel.get(), ":27");
	lv_label_set_text(m_pFullDateLabel.get(), "JAN/20/2020");
	lv_label_set_text(m_pWeekDayLabel.get(), "MONDAY");
}

void ClockWatch::hide()
{
	PageViewObject::hide();

	m_pHoursLabel.reset();
	m_pMinutesLabel.reset();
	m_pSecondsLabel.reset();
	m_pFullDateLabel.reset();
	m_pWeekDayLabel.reset();
}

void ClockWatch::initStyles()
{
	auto pThemeProvider = PageViewObject::getThemeController();
	if (!pThemeProvider )
		return;

	m_hoursLabelStyle = pThemeProvider->getFontStyle(
			Theme::FontSize::x_large
		,	Theme::Color::MainThemeDark
	);

	m_minutesLabelStyle = pThemeProvider->getFontStyle(
			Theme::FontSize::x_large
		,	Theme::Color::MainThemeLight
	);

	m_secondsLabelStyle = pThemeProvider->getFontStyle(
			Theme::FontSize::small
		,	Theme::Color::MainThemeLight
	);

	m_fullDateStyle = m_secondsLabelStyle;

	m_weekDayStyle = pThemeProvider->getFontStyle(
			Theme::FontSize::large
		,	Theme::Color::MainThemeDark
	);
}

void ClockWatch::initClockLabels(
		lv_obj_t* _parentObject
	,	const std::uint32_t _displayWidth
	,	const std::uint32_t _displayHeight
)
{
	auto parent = _parentObject;
	const std::uint32_t DisplayWidth { _displayWidth };
	const std::uint32_t DisplayHeight { _displayHeight };

	m_pHoursLabel.reset( lv_label_create( parent, nullptr ) );
	lv_label_set_style(
			m_pHoursLabel.get()
		, 	LV_LABEL_STYLE_MAIN
		, 	&m_hoursLabelStyle
	);

	lv_obj_align(
			m_pHoursLabel.get()
		,	nullptr
		,	LV_ALIGN_IN_LEFT_MID
		,	DisplayWidth / 7
		,	DisplayHeight / 30
	);

	m_pMinutesLabel.reset( lv_label_create( parent, nullptr ) );
	lv_label_set_style(
			m_pMinutesLabel.get()
		,	LV_LABEL_STYLE_MAIN
		,	&m_minutesLabelStyle
	);

	lv_obj_align(
			m_pMinutesLabel.get()
		,	nullptr
		,	LV_ALIGN_CENTER
		,	DisplayWidth / 20
		,	DisplayHeight / 30
	);

	m_pSecondsLabel.reset( lv_label_create( parent, nullptr ) );
	lv_label_set_style(
			m_pSecondsLabel.get()
		,	LV_LABEL_STYLE_MAIN
		,	&m_secondsLabelStyle
	);
}

void ClockWatch::initFullDateLabel(
		lv_obj_t* _parentObject
	,	const std::uint32_t _displayWidth
	,	const std::uint32_t _displayHeight
)
{

	m_pFullDateLabel.reset( lv_label_create( _parentObject, nullptr ) );
	lv_label_set_style(
			m_pFullDateLabel.get()
		, 	LV_LABEL_STYLE_MAIN
		, 	&m_fullDateStyle
	);

	lv_obj_align(
			m_pFullDateLabel.get()
		,	nullptr
		,	LV_ALIGN_IN_RIGHT_MID
		,	- static_cast<int>( _displayWidth / 8 )
		,	static_cast<int>( _displayHeight / 4.5f )
	);
}

void ClockWatch::initWeekDayLabel(
		lv_obj_t* _parentObject
	,	const std::uint32_t _displayWidth
	,	const std::uint32_t _displayHeight
)
{
	m_pWeekDayLabel.reset( lv_label_create( _parentObject, nullptr ) );
	lv_label_set_style(
			m_pWeekDayLabel.get()
		, 	LV_LABEL_STYLE_MAIN
		, 	&m_weekDayStyle
	);

	lv_obj_align(
			m_pWeekDayLabel.get()
		,	nullptr
		,	LV_ALIGN_IN_TOP_MID
		,	0
		,	_displayHeight / 15
	);
}


std::unique_ptr<IPageViewObject> createClockWatchView(
	std::weak_ptr<Theme::IThemeController> _themeController
)
{
	return std::make_unique<ClockWatch>( _themeController );
}

}