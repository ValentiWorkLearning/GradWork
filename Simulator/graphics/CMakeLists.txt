cmake_minimum_required(VERSION 3.10)

set (TARGET_NAME lvgl_lib)

add_library( ${TARGET_NAME} STATIC )


set(CMAKE_C_STANDARD 11)

target_include_directories(
    ${TARGET_NAME}
    PUBLIC
    "lvgl/"
    "lvgl/src/"
    "lvgl/src/lv_core/"
    "lvgl/src/lv_draw/"
    "lvgl/src/lv_font/"
    "lvgl/src/lv_hal/"
    "lvgl/src/lv_misc/"
    "lvgl/src/lv_objx/"
    "lvgl/src/lv_themes/"

    "lv_drivers/display/fbdev.h"
    "lv_drivers/display/monitor.h"
    "lv_drivers/display/R61581.h"
    "lv_drivers/display/SHARP_MIP.h"
    "lv_drivers/display/SSD1963.h"
    "lv_drivers/display/ST7565.h"
    "lv_drivers/display/UC1610.h"
    "lv_drivers/indev/AD_touch.h"
    "lv_drivers/indev/evdev.h"
    "lv_drivers/indev/FT5406EE8.h"
    "lv_drivers/indev/keyboard.h"
    "lv_drivers/indev/libinput_drv.h"
    "lv_drivers/indev/mouse.h"
    "lv_drivers/indev/mousewheel.h"
    "lv_drivers/indev/XPT2046.h"
    "lv_drivers/lv_drv_conf_templ.h"
    "lv_drivers/win_drv.h"

    ${CMAKE_CURRENT_LIST_DIR}
)

set ( TARGET_SOURCE_LIST
    "lvgl/src/lv_core/lv_debug.c"
    "lvgl/src/lv_core/lv_disp.c"
    "lvgl/src/lv_core/lv_group.c"
    "lvgl/src/lv_core/lv_indev.c"
    "lvgl/src/lv_core/lv_obj.c"
    "lvgl/src/lv_core/lv_refr.c"
    "lvgl/src/lv_core/lv_style.c"
    "lvgl/src/lv_draw/lv_draw.c"
    "lvgl/src/lv_draw/lv_draw_arc.c"
    "lvgl/src/lv_draw/lv_draw_basic.c"
    "lvgl/src/lv_draw/lv_draw_img.c"
    "lvgl/src/lv_draw/lv_draw_label.c"
    "lvgl/src/lv_draw/lv_draw_line.c"
    "lvgl/src/lv_draw/lv_draw_rect.c"
    "lvgl/src/lv_draw/lv_draw_triangle.c"
    "lvgl/src/lv_draw/lv_img_cache.c"
    "lvgl/src/lv_draw/lv_img_decoder.c"
    "lvgl/src/lv_font/lv_font.c"
    "lvgl/src/lv_font/lv_font_fmt_txt.c"
    "lvgl/src/lv_font/lv_font_roboto_12.c"
    "lvgl/src/lv_font/lv_font_roboto_12_subpx.c"
    "lvgl/src/lv_font/lv_font_roboto_16.c"
    "lvgl/src/lv_font/lv_font_roboto_22.c"
    "lvgl/src/lv_font/lv_font_roboto_28.c"
    "lvgl/src/lv_font/lv_font_roboto_28_compressed.c"
    "lvgl/src/lv_font/lv_font_unscii_8.c"
    "lvgl/src/lv_hal/lv_hal_disp.c"
    "lvgl/src/lv_hal/lv_hal_indev.c"
    "lvgl/src/lv_hal/lv_hal_tick.c"
    "lvgl/src/lv_misc/lv_anim.c"
    "lvgl/src/lv_misc/lv_area.c"
    "lvgl/src/lv_misc/lv_async.c"
    "lvgl/src/lv_misc/lv_bidi.c"
    "lvgl/src/lv_misc/lv_circ.c"
    "lvgl/src/lv_misc/lv_color.c"
    "lvgl/src/lv_misc/lv_fs.c"
    "lvgl/src/lv_misc/lv_gc.c"
    "lvgl/src/lv_misc/lv_ll.c"
    "lvgl/src/lv_misc/lv_log.c"
    "lvgl/src/lv_misc/lv_math.c"
    "lvgl/src/lv_misc/lv_mem.c"
    "lvgl/src/lv_misc/lv_printf.c"
    "lvgl/src/lv_misc/lv_task.c"
    "lvgl/src/lv_misc/lv_templ.c"
    "lvgl/src/lv_misc/lv_txt.c"
    "lvgl/src/lv_misc/lv_utils.c"
    "lvgl/src/lv_objx/lv_arc.c"
    "lvgl/src/lv_objx/lv_bar.c"
    "lvgl/src/lv_objx/lv_btn.c"
    "lvgl/src/lv_objx/lv_btnm.c"
    "lvgl/src/lv_objx/lv_calendar.c"
    "lvgl/src/lv_objx/lv_canvas.c"
    "lvgl/src/lv_objx/lv_cb.c"
    "lvgl/src/lv_objx/lv_chart.c"
    "lvgl/src/lv_objx/lv_cont.c"
    "lvgl/src/lv_objx/lv_cpicker.c"
    "lvgl/src/lv_objx/lv_ddlist.c"
    "lvgl/src/lv_objx/lv_gauge.c"
    "lvgl/src/lv_objx/lv_img.c"
    "lvgl/src/lv_objx/lv_imgbtn.c"
    "lvgl/src/lv_objx/lv_kb.c"
    "lvgl/src/lv_objx/lv_label.c"
    "lvgl/src/lv_objx/lv_led.c"
    "lvgl/src/lv_objx/lv_line.c"
    "lvgl/src/lv_objx/lv_list.c"
    "lvgl/src/lv_objx/lv_lmeter.c"
    "lvgl/src/lv_objx/lv_mbox.c"
    "lvgl/src/lv_objx/lv_objx_templ.c"
    "lvgl/src/lv_objx/lv_page.c"
    "lvgl/src/lv_objx/lv_preload.c"
    "lvgl/src/lv_objx/lv_roller.c"
    "lvgl/src/lv_objx/lv_slider.c"
    "lvgl/src/lv_objx/lv_spinbox.c"
    "lvgl/src/lv_objx/lv_sw.c"
    "lvgl/src/lv_objx/lv_ta.c"
    "lvgl/src/lv_objx/lv_table.c"
    "lvgl/src/lv_objx/lv_tabview.c"
    "lvgl/src/lv_objx/lv_tileview.c"
    "lvgl/src/lv_objx/lv_win.c"
    "lvgl/src/lv_themes/lv_theme.c"
    "lvgl/src/lv_themes/lv_theme_alien.c"
    "lvgl/src/lv_themes/lv_theme_default.c"
    "lvgl/src/lv_themes/lv_theme_material.c"
    "lvgl/src/lv_themes/lv_theme_mono.c"
    "lvgl/src/lv_themes/lv_theme_nemo.c"
    "lvgl/src/lv_themes/lv_theme_night.c"
    "lvgl/src/lv_themes/lv_theme_templ.c"
    "lvgl/src/lv_themes/lv_theme_zen.c"

    "lv_drivers/display/fbdev.c"
    "lv_drivers/display/monitor.c"
    "lv_drivers/display/R61581.c"
    "lv_drivers/display/SHARP_MIP.c"
    "lv_drivers/display/SSD1963.c"
    "lv_drivers/display/ST7565.c"
    "lv_drivers/display/UC1610.c"
    "lv_drivers/indev/AD_touch.c"
    "lv_drivers/indev/evdev.c"
    "lv_drivers/indev/FT5406EE8.c"
    "lv_drivers/indev/keyboard.c"
    "lv_drivers/indev/libinput.c"
    "lv_drivers/indev/mouse.c"
    "lv_drivers/indev/mousewheel.c"
    "lv_drivers/indev/XPT2046.c"
    "lv_drivers/win_drv.c"
)

target_sources(
    ${TARGET_NAME}
    PRIVATE
    ${TARGET_SOURCE_LIST}
)

set_source_files_properties(
    ${TARGET_SOURCE_LIST}
    PROPERTIES LANGUAGE C
)

target_include_directories(
    ${TARGET_NAME}
    PUBLIC
    "SDL-mirror/include"
)