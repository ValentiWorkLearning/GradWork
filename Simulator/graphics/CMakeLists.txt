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
    "lvgl/src/lv_gpu/"
    "lvgl/src/lv_hal/"
    "lvgl/src/lv_misc/"
    "lvgl/src/lv_themes/"
    "lvgl/src/lv_widgets/"
    

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
    "lvgl/porting/lv_port_disp_template.c"
    "lvgl/porting/lv_port_fs_template.c"
    "lvgl/porting/lv_port_indev_template.c"
    "lvgl/src/lv_core/lv_debug.c"
    "lvgl/src/lv_core/lv_disp.c"
    "lvgl/src/lv_core/lv_group.c"
    "lvgl/src/lv_core/lv_indev.c"
    "lvgl/src/lv_core/lv_obj.c"
    "lvgl/src/lv_core/lv_refr.c"
    "lvgl/src/lv_core/lv_style.c"
    "lvgl/src/lv_draw/lv_draw_arc.c"
    "lvgl/src/lv_draw/lv_draw_blend.c"
    "lvgl/src/lv_draw/lv_draw_img.c"
    "lvgl/src/lv_draw/lv_draw_label.c"
    "lvgl/src/lv_draw/lv_draw_line.c"
    "lvgl/src/lv_draw/lv_draw_mask.c"
    "lvgl/src/lv_draw/lv_draw_rect.c"
    "lvgl/src/lv_draw/lv_draw_triangle.c"
    "lvgl/src/lv_draw/lv_img_buf.c"
    "lvgl/src/lv_draw/lv_img_cache.c"
    "lvgl/src/lv_draw/lv_img_decoder.c"
    "lvgl/src/lv_font/lv_font.c"
    "lvgl/src/lv_font/lv_font_dejavu_16_persian_hebrew.c"
    "lvgl/src/lv_font/lv_font_fmt_txt.c"
    "lvgl/src/lv_font/lv_font_montserrat_12.c"
    "lvgl/src/lv_font/lv_font_montserrat_12_subpx.c"
    "lvgl/src/lv_font/lv_font_montserrat_14.c"
    "lvgl/src/lv_font/lv_font_montserrat_16.c"
    "lvgl/src/lv_font/lv_font_montserrat_18.c"
    "lvgl/src/lv_font/lv_font_montserrat_20.c"
    "lvgl/src/lv_font/lv_font_montserrat_22.c"
    "lvgl/src/lv_font/lv_font_montserrat_24.c"
    "lvgl/src/lv_font/lv_font_montserrat_26.c"
    "lvgl/src/lv_font/lv_font_montserrat_28.c"
    "lvgl/src/lv_font/lv_font_montserrat_28_compressed.c"
    "lvgl/src/lv_font/lv_font_montserrat_30.c"
    "lvgl/src/lv_font/lv_font_montserrat_32.c"
    "lvgl/src/lv_font/lv_font_montserrat_34.c"
    "lvgl/src/lv_font/lv_font_montserrat_36.c"
    "lvgl/src/lv_font/lv_font_montserrat_38.c"
    "lvgl/src/lv_font/lv_font_montserrat_40.c"
    "lvgl/src/lv_font/lv_font_montserrat_42.c"
    "lvgl/src/lv_font/lv_font_montserrat_44.c"
    "lvgl/src/lv_font/lv_font_montserrat_46.c"
    "lvgl/src/lv_font/lv_font_montserrat_48.c"
    "lvgl/src/lv_font/lv_font_simsun_16_cjk.c"
    "lvgl/src/lv_font/lv_font_unscii_8.c"
    "lvgl/src/lv_gpu/lv_gpu_stm32_dma2d.c"
    "lvgl/src/lv_hal/lv_hal_disp.c"
    "lvgl/src/lv_hal/lv_hal_indev.c"
    "lvgl/src/lv_hal/lv_hal_tick.c"
    "lvgl/src/lv_misc/lv_anim.c"
    "lvgl/src/lv_misc/lv_area.c"
    "lvgl/src/lv_misc/lv_async.c"
    "lvgl/src/lv_misc/lv_bidi.c"
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
    "lvgl/src/lv_misc/lv_txt_ap.c"
    "lvgl/src/lv_misc/lv_utils.c"
    "lvgl/src/lv_themes/lv_theme.c"
    "lvgl/src/lv_themes/lv_theme_empty.c"
    "lvgl/src/lv_themes/lv_theme_material.c"
    "lvgl/src/lv_themes/lv_theme_mono.c"
    "lvgl/src/lv_themes/lv_theme_template.c"
    "lvgl/src/lv_widgets/lv_arc.c"
    "lvgl/src/lv_widgets/lv_bar.c"
    "lvgl/src/lv_widgets/lv_btn.c"
    "lvgl/src/lv_widgets/lv_btnmatrix.c"
    "lvgl/src/lv_widgets/lv_calendar.c"
    "lvgl/src/lv_widgets/lv_canvas.c"
    "lvgl/src/lv_widgets/lv_chart.c"
    "lvgl/src/lv_widgets/lv_checkbox.c"
    "lvgl/src/lv_widgets/lv_cont.c"
    "lvgl/src/lv_widgets/lv_cpicker.c"
    "lvgl/src/lv_widgets/lv_dropdown.c"
    "lvgl/src/lv_widgets/lv_gauge.c"
    "lvgl/src/lv_widgets/lv_img.c"
    "lvgl/src/lv_widgets/lv_imgbtn.c"
    "lvgl/src/lv_widgets/lv_keyboard.c"
    "lvgl/src/lv_widgets/lv_label.c"
    "lvgl/src/lv_widgets/lv_led.c"
    "lvgl/src/lv_widgets/lv_line.c"
    "lvgl/src/lv_widgets/lv_linemeter.c"
    "lvgl/src/lv_widgets/lv_list.c"
    "lvgl/src/lv_widgets/lv_msgbox.c"
    "lvgl/src/lv_widgets/lv_objmask.c"
    "lvgl/src/lv_widgets/lv_objx_templ.c"
    "lvgl/src/lv_widgets/lv_page.c"
    "lvgl/src/lv_widgets/lv_roller.c"
    "lvgl/src/lv_widgets/lv_slider.c"
    "lvgl/src/lv_widgets/lv_spinbox.c"
    "lvgl/src/lv_widgets/lv_spinner.c"
    "lvgl/src/lv_widgets/lv_switch.c"
    "lvgl/src/lv_widgets/lv_table.c"
    "lvgl/src/lv_widgets/lv_tabview.c"
    "lvgl/src/lv_widgets/lv_textarea.c"
    "lvgl/src/lv_widgets/lv_tileview.c"
    "lvgl/src/lv_widgets/lv_win.c"

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