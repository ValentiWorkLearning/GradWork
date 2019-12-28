#include "lvgl_ui.hpp"

extern "C"
{
    #include "lvgl.h"
}

namespace LvglUi
{

void createWidgetsDemo()
{

   //lv_theme_t* pTheme = lv_theme_mono_init(0, NULL);
    lv_theme_t* pTheme = lv_theme_material_init(0, NULL);
    lv_theme_set_current(pTheme);

    lv_obj_t * scr = lv_disp_get_scr_act(NULL);     /*Get the current screen*/

    lv_obj_t * preload = lv_preload_create(lv_scr_act(), NULL);
    lv_preload_set_spin_time(preload, 10000);
    lv_obj_set_size(preload, 240, 240);
    lv_obj_align(preload, NULL, LV_ALIGN_CENTER, 0, 0);


     static lv_style_t styleMainLabel;
     lv_style_copy(&styleMainLabel, &lv_style_transp_tight);         /*Copy a built-in style as a starting point*/

     lv_obj_t* label1 = lv_label_create(scr, NULL);
    styleMainLabel.text.font = &lv_font_roboto_28;
    lv_label_set_style( label1 ,LV_LABEL_STYLE_MAIN, &styleMainLabel );
    lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(label1, "12:23");


// Line with clockwatch
    // static lv_point_t line_points[] = { {5, 5}, {70, 70}, {120, 10}, {180, 60}, {220, 10} };
    // static lv_style_t style_line;
    // lv_style_copy(&style_line, &lv_style_plain);
    // style_line.line.color = LV_COLOR_MAKE(0x00, 0x3b, 0x75);
    // style_line.line.width = 3;
    // style_line.line.rounded = 1;

    // /*Copy the previous line and apply the new style*/
    // lv_obj_t* line1;
    // line1 = lv_line_create(lv_scr_act(), NULL);
    // lv_line_set_points(line1, line_points, 5);     /*Set the points*/
    // lv_line_set_style(line1, LV_LINE_STYLE_MAIN, &style_line);
    // lv_obj_align(line1, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);

    lv_obj_t* label2 = lv_label_create(scr, NULL);
    styleMainLabel.text.font = &lv_font_roboto_28;
    lv_label_set_style( label2 ,LV_LABEL_STYLE_MAIN, &styleMainLabel );

    lv_label_set_text(label2, "28/12/19");

    lv_obj_align(label2, NULL, LV_ALIGN_CENTER, 0, 30);

}

}