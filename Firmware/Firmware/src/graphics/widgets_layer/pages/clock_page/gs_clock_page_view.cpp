#include "gs_clock_page_view.hpp"
#include "ih/gs_itheme_controller.hpp"

namespace Graphics::Views
{

ClockWatch::ClockWatch( const Theme::IThemeController* _themeController )
	:	PageViewObject<IClockWatchPage>{ _themeController, IClockWatchPage::ClockPageName }
	,	m_hoursLabelStyle{}
	,	m_minutesLabelStyle{}
	,	m_secondsLabelStyle{}
	,	m_fullDateStyle{}
	,	m_weekDayStyle{}
	,	m_hoursValue{ "00" }
	,	m_minutesValue{ "00" }
	,	m_secondsValue{ ":00" }
	,	m_weekdayValue{ "........." }
	,	m_fulldateValue{ "../../...." }
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

	restoreLabelsText();
}

void ClockWatch::hide()
{
	PageViewObject::hide();

	Meta::tupleApply(
			[]( auto&& _nodeToReset ){ _nodeToReset.reset(); }
		,	std::forward_as_tuple(
				m_pHoursLabel
			,	m_pMinutesLabel
			,	m_pSecondsLabel
			,	m_pFullDateLabel
			,	m_pWeekDayLabel
		)
	);
}

void ClockWatch::reloadStyle()
{
	PageViewObject::reloadStyle();
	initStyles();
}


void ClockWatch::setHours( const std::string& _newHoursValue )
{
	m_hoursValue = _newHoursValue;
	lv_label_set_text( m_pHoursLabel.get(), m_hoursValue.c_str() );
}

void ClockWatch::setMinutes( const std::string& _newMinutesValue )
{
	m_minutesValue = _newMinutesValue;
	lv_label_set_text( m_pMinutesLabel.get(), m_minutesValue.c_str() );
}

void ClockWatch::setSeconds( const std::string& _newSecondsValue )
{
	m_secondsValue = _newSecondsValue;
	lv_label_set_text( m_pSecondsLabel.get(), m_secondsValue.c_str() );
}

void ClockWatch::setWeekday( std::string_view _newWeekDay )
{
	m_weekdayValue = _newWeekDay;
	lv_label_set_text( m_pWeekDayLabel.get(), m_weekdayValue.c_str() );
}

void ClockWatch::setFullDate( const std::string& _fullDate )
{
	m_fulldateValue = _fullDate;
	lv_label_set_text( m_pFullDateLabel.get(), m_fulldateValue.c_str() );
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
	lv_obj_add_style(
			m_pHoursLabel.get()
		, 	LV_LABEL_PART_MAIN
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
	lv_obj_add_style(
			m_pMinutesLabel.get()
		,	LV_LABEL_PART_MAIN
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
	lv_obj_add_style(
			m_pSecondsLabel.get()
		,	LV_LABEL_PART_MAIN
		,	&m_secondsLabelStyle
	);

	lv_obj_align(
			m_pSecondsLabel.get()
		,	nullptr
		,	LV_ALIGN_IN_TOP_RIGHT
		,	0
		,	DisplayHeight / 3 + DisplayHeight / 20
	);
}

void ClockWatch::initFullDateLabel(
		lv_obj_t* _parentObject
	,	const std::uint32_t _displayWidth
	,	const std::uint32_t _displayHeight
)
{

	m_pFullDateLabel.reset( lv_label_create( _parentObject, nullptr ) );
	lv_obj_add_style(
			m_pFullDateLabel.get()
		, 	LV_LABEL_PART_MAIN
		, 	&m_fullDateStyle
	);

	lv_obj_align(
			m_pFullDateLabel.get()
		,	nullptr
		,	LV_ALIGN_IN_RIGHT_MID
		,	- static_cast<int>( _displayWidth / 3 )
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
	lv_obj_add_style(
			m_pWeekDayLabel.get()
		, 	LV_LABEL_PART_MAIN
		, 	&m_weekDayStyle
	);

	lv_obj_align(
			m_pWeekDayLabel.get()
		,	nullptr
		,	LV_ALIGN_IN_TOP_MID
		,	static_cast<int>( _displayWidth / 24 )
		,	_displayHeight / 15
	);
}

void ClockWatch::restoreLabelsText()
{
	lv_label_set_text( m_pHoursLabel.get(), m_hoursValue.c_str() );
	lv_label_set_text( m_pMinutesLabel.get(), m_minutesValue.c_str() );
	lv_label_set_text( m_pSecondsLabel.get(), m_secondsValue.c_str() );
	lv_label_set_text( m_pFullDateLabel.get(), m_fulldateValue.c_str() );
	lv_label_set_text( m_pWeekDayLabel.get(), m_weekdayValue.c_str() );
}


std::unique_ptr<IClockWatchPage> createClockWatchView(
	const Theme::IThemeController* _themeController
)
{
	return std::make_unique<ClockWatch>( _themeController );
}

}