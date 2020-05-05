#include "gs_health_page_view.hpp"

#include "ih/gs_itheme_controller.hpp"

#include "IconFont16px.hpp"
#include "IconFont35px.hpp"

namespace Graphics::Views
{

HealthPage::HealthPage( const Theme::IThemeController* _themeController )
	:	PageViewObject<IHealthWatchPage>{ _themeController, IHealthWatchPage::HealthPageName }
	,	m_mainLabelStyleDark{}
	,	m_healthPageIconStyle{}
    ,	m_mainFontLight{}
    ,	m_mainFontDark{}
    ,	m_tooltipsStyleDark{}
    ,	m_tooltipsStyleLight{}
    ,	m_stepsIconStyle{}
    ,	m_pulseLineStyle{}
{
	initStyles();
}

void HealthPage::show()
{
	PageViewObject::show();

	auto parent = lv_disp_get_scr_act( nullptr );

	auto pThemeProvider = PageViewObject::getThemeController();
	if (!pThemeProvider )
		return;

	const std::uint32_t DisplayWidth { pThemeProvider->getDisplayWidth() };
	const std::uint32_t DisplayHeight { pThemeProvider->getDisplayHeight() };

	initHeartrateWidgets( parent, DisplayWidth, DisplayHeight );
	initCalloriesCounter( parent, DisplayWidth, DisplayHeight );
	initStepsCounter( parent, DisplayWidth, DisplayHeight );
	initPageTitle( parent, DisplayWidth, DisplayHeight );
}

void HealthPage::hide()
{
	PageViewObject::hide();

	Meta::tupleApply(
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
	);
}

void HealthPage::reloadStyle()
{
	PageViewObject::reloadStyle();
	initStyles();
}

void HealthPage::setStepsCount(std::uint8_t _newStepsValue)
{
}

void HealthPage::setHeartrate(std::uint8_t _newHeartrateValue)
{
}

void HealthPage::setCalloriesCount(std::uint8_t _newCalloriesCount)
{
}

void HealthPage::initStyles()
{
	auto pThemeProvider = PageViewObject::getThemeController();
	if (!pThemeProvider )
		return;

	m_mainLabelStyleDark = pThemeProvider->getFontStyle(
			Theme::FontSize::large
		,	Theme::Color::MainThemeDark
	);

	m_mainFontDark = pThemeProvider->getFontStyle(
			Theme::FontSize::normal
		,	Theme::Color::MainThemeDark
	);

	m_mainFontLight = pThemeProvider->getFontStyle(
			Theme::FontSize::normal
		,	Theme::Color::MainThemeLight
	);

	m_healthPageIconStyle = pThemeProvider->getIconsFont(
			Theme::FontSize::small
		,	Theme::Color::MainThemeDark
	);

	m_stepsIconStyle = pThemeProvider->getIconsFont(
			Theme::FontSize::normal
		,	Theme::Color::MainThemeLight
	);

	m_tooltipsStyleDark = pThemeProvider->getFontStyle(
			Theme::FontSize::extra_small
		,	Theme::Color::MainThemeDark
	);

	m_tooltipsStyleLight = pThemeProvider->getFontStyle(
			Theme::FontSize::extra_small
		,	Theme::Color::MainThemeLight
	);

	auto MainThemeDark = pThemeProvider->getMainThemeColor(
		Theme::Color::MainThemeDark
	);
	
	lv_style_set_line_color(&m_pulseLineStyle, LV_STATE_DEFAULT, MainThemeDark);

	constexpr int LineWidth = 3;
	lv_style_set_line_width(&m_pulseLineStyle, LV_STATE_DEFAULT, LineWidth);
	lv_style_set_line_rounded(&m_pulseLineStyle, LV_STATE_DEFAULT, true);
}

void HealthPage::initPageTitle(
		lv_obj_t* _parentObject
	,	const std::uint32_t _displayWidth
	,	const std::uint32_t _displayHeight
)
{
	m_pHealthPageLabel.reset( lv_label_create( _parentObject, nullptr ) );

	lv_obj_add_style( m_pHealthPageLabel.get(), LV_LABEL_PART_MAIN, &m_mainLabelStyleDark );
	lv_label_set_text( m_pHealthPageLabel.get(), "HEALTH" );
	lv_obj_align(
			m_pHealthPageLabel.get()
		,	nullptr
		,	LV_ALIGN_IN_TOP_MID
		,	0
		,	_displayHeight / 15
	);

	m_pHealthPageIcon.reset( lv_label_create( _parentObject, nullptr ) );

	lv_obj_add_style( m_pHealthPageIcon.get(), LV_LABEL_PART_MAIN, &m_healthPageIconStyle );
	lv_label_set_text( m_pHealthPageIcon.get(), IconFontSymbols::Health::HeartIcon.data() );
	lv_obj_align(
			m_pHealthPageIcon.get()
		,	m_pHealthPageLabel.get()
		,	LV_ALIGN_OUT_BOTTOM_MID
		,	0
		,	0
	);

}

void HealthPage::initHeartrateWidgets(
		lv_obj_t* _parentObject
	,	const std::uint32_t _displayWidth
	,	const std::uint32_t _displayHeight
)
{
	m_pHeartBeatsLabel.reset( lv_label_create(_parentObject, nullptr) );

	lv_obj_add_style( m_pHeartBeatsLabel.get(), LV_LABEL_PART_MAIN, &m_mainFontDark );
	lv_label_set_text( m_pHeartBeatsLabel.get(), "80");

	lv_obj_align(
			m_pHeartBeatsLabel.get()
		,	nullptr
		,	LV_ALIGN_IN_LEFT_MID
		,	_displayWidth / 4  - _displayWidth / 60
		,	-static_cast<int>( _displayHeight / 24 )
	);

	m_pHeartBeatsTooltip.reset( lv_label_create(_parentObject, nullptr) );

	lv_obj_add_style( m_pHeartBeatsTooltip.get(), LV_LABEL_PART_MAIN, &m_tooltipsStyleDark);
	lv_label_set_text( m_pHeartBeatsTooltip.get(), "HEARTBEATS");

	lv_obj_align(
			m_pHeartBeatsTooltip.get()
		,	m_pHeartBeatsLabel.get()
		,	LV_ALIGN_OUT_BOTTOM_LEFT
		,	0
		,	0
	);

	m_pPulseIcon.reset( lv_line_create(_parentObject, nullptr ) );

	lv_line_set_points(
			m_pPulseIcon.get()
		,	CardioIconPoints.data()
		,	static_cast<std::uint16_t>(CardioIconPoints.size())
	);

	lv_obj_add_style( m_pPulseIcon.get(), LV_LINE_PART_MAIN, &m_pulseLineStyle );

	lv_obj_align(
			m_pPulseIcon.get()
		,	nullptr
		,	LV_ALIGN_IN_LEFT_MID
		,	0
		,	-static_cast<int>( _displayHeight / 25 )
	);
}

void HealthPage::initCalloriesCounter(
		lv_obj_t* _parentObject
	,	const std::uint32_t _displayWidth
	,	const std::uint32_t _displayHeight
)
{
	m_pKcalLabel.reset( lv_label_create(_parentObject, nullptr) );

	lv_obj_add_style( m_pKcalLabel.get(), LV_LABEL_PART_MAIN, &m_mainFontLight );
	lv_label_set_text( m_pKcalLabel.get(), "160");

	lv_obj_align(
			m_pKcalLabel.get()
		,	nullptr
		,	LV_ALIGN_CENTER
		,	_displayWidth / 6
		,	static_cast<int>( _displayHeight / 6 )
	);

	m_pKcalTooltip.reset( lv_label_create(_parentObject, nullptr) );

	lv_obj_add_style( m_pKcalTooltip.get(), LV_LABEL_PART_MAIN, &m_tooltipsStyleLight );
	lv_label_set_text( m_pKcalTooltip.get(), "KCAL");

	lv_obj_align(
			m_pKcalTooltip.get()
		,	m_pKcalLabel.get()
		,	LV_ALIGN_OUT_BOTTOM_RIGHT
		,	_displayWidth / 10
		,	0
	);
}

void HealthPage::initStepsCounter(
		lv_obj_t* _parentObject
	,	const std::uint32_t _displayWidth
	,	const std::uint32_t _displayHeight
)
{
	m_pStepsLabel.reset( lv_label_create(_parentObject, nullptr) );

	lv_obj_add_style( m_pStepsLabel.get(), LV_LABEL_PART_MAIN, &m_mainFontLight );
	lv_label_set_text( m_pStepsLabel.get(), "3600");

	lv_obj_align(
			m_pStepsLabel.get()
		,	nullptr
		,	LV_ALIGN_IN_RIGHT_MID
		,	-static_cast<int>( _displayWidth / 12 )
		,	-static_cast<int>( _displayHeight / 20 )
	);

	m_pStepsTooltip.reset( lv_label_create(_parentObject, nullptr) );

	lv_obj_add_style( m_pStepsTooltip.get(), LV_LABEL_PART_MAIN, &m_tooltipsStyleLight );
	lv_label_set_text( m_pStepsTooltip.get(), "STEPS");

	lv_obj_align(
			m_pStepsTooltip.get()
		,	m_pStepsLabel.get()
		,	LV_ALIGN_OUT_BOTTOM_RIGHT
		,	_displayWidth / 24
		,	0
	);

	m_pStepsIcon.reset( lv_label_create(_parentObject, nullptr ) );
	lv_obj_add_style( m_pStepsIcon.get(), LV_OBJ_PART_MAIN,&m_stepsIconStyle );
    lv_label_set_text( m_pStepsIcon.get(), IconFontSymbols::Steps::StepsIcon.data() );

    lv_obj_align(
			m_pStepsIcon.get()
        ,   nullptr
        ,   LV_ALIGN_CENTER
        ,   static_cast<int>( _displayWidth / 10 )
        ,	-static_cast<int>(_displayHeight / 48 )
    );
}


std::unique_ptr<IHealthWatchPage>
createHeartrateWatchView( const Theme::IThemeController* _themeController )
{
	return std::make_unique<HealthPage>( _themeController );
}

}