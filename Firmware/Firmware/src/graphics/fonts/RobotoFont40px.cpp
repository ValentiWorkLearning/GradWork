#include "lvgl/lvgl.h"

/*******************************************************************************
 * Size: 40 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifndef ROBOTOFONT40PX
#define ROBOTOFONT40PX 1
#endif

#if ROBOTOFONT40PX

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t gylph_bitmap[] = {
    /* U+30 "0" */
    0x3, 0xf8, 0x1, 0xff, 0xc0, 0x7f, 0xfc, 0x1f,
    0xff, 0xc7, 0xe0, 0xfc, 0xf8, 0xf, 0x9f, 0x1,
    0xf7, 0xc0, 0x1f, 0xf8, 0x3, 0xff, 0x0, 0x7f,
    0xe0, 0xf, 0xfc, 0x1, 0xff, 0x80, 0x3f, 0xf0,
    0x7, 0xfe, 0x0, 0xff, 0xc0, 0x1f, 0xf8, 0x3,
    0xff, 0x0, 0x7f, 0xe0, 0xf, 0xfc, 0x1, 0xff,
    0x80, 0x3f, 0xf0, 0x7, 0xdf, 0x1, 0xf3, 0xe0,
    0x3e, 0x7e, 0xf, 0xc7, 0xff, 0xf0, 0x7f, 0xfc,
    0x7, 0xff, 0x0, 0x3f, 0x80,

    /* U+31 "1" */
    0x0, 0x30, 0x1f, 0x7, 0xf3, 0xff, 0xff, 0xff,
    0xff, 0xf9, 0xfc, 0x1f, 0x1, 0xf0, 0x1f, 0x1,
    0xf0, 0x1f, 0x1, 0xf0, 0x1f, 0x1, 0xf0, 0x1f,
    0x1, 0xf0, 0x1f, 0x1, 0xf0, 0x1f, 0x1, 0xf0,
    0x1f, 0x1, 0xf0, 0x1f, 0x1, 0xf0, 0x1f, 0x1,
    0xf0, 0x1f, 0x1, 0xf0,

    /* U+32 "2" */
    0x3, 0xf8, 0x0, 0xff, 0xf0, 0x1f, 0xff, 0x83,
    0xff, 0xfc, 0x7e, 0xf, 0xc7, 0xc0, 0x7e, 0xfc,
    0x3, 0xef, 0x80, 0x3e, 0xf8, 0x3, 0xe0, 0x0,
    0x3e, 0x0, 0x3, 0xe0, 0x0, 0x7c, 0x0, 0x7,
    0xc0, 0x0, 0xf8, 0x0, 0x1f, 0x0, 0x3, 0xf0,
    0x0, 0x7e, 0x0, 0xf, 0xc0, 0x1, 0xf8, 0x0,
    0x3f, 0x0, 0x3, 0xe0, 0x0, 0x7c, 0x0, 0xf,
    0x80, 0x1, 0xf0, 0x0, 0x3e, 0x0, 0x7, 0xff,
    0xff, 0x7f, 0xff, 0xf7, 0xff, 0xff, 0x7f, 0xff,
    0xf0,

    /* U+33 "3" */
    0x3, 0xf8, 0x1, 0xff, 0xe0, 0xff, 0xfe, 0x3f,
    0xff, 0xe7, 0xe0, 0xfd, 0xf8, 0xf, 0xfe, 0x0,
    0xff, 0xc0, 0x1f, 0x0, 0x3, 0xe0, 0x0, 0x7c,
    0x0, 0x1f, 0x0, 0x7, 0xe0, 0x3f, 0xf0, 0x7,
    0xfc, 0x0, 0xff, 0x80, 0x1f, 0xfc, 0x0, 0xf,
    0xc0, 0x0, 0xf8, 0x0, 0xf, 0x80, 0x1, 0xf0,
    0x0, 0x3f, 0xf0, 0x7, 0xfe, 0x0, 0xff, 0xe0,
    0x3f, 0x7e, 0xf, 0xcf, 0xff, 0xf0, 0xff, 0xfe,
    0x7, 0xff, 0x0, 0x3f, 0x80,

    /* U+34 "4" */
    0x0, 0xf, 0x80, 0x0, 0xfc, 0x0, 0xf, 0xe0,
    0x0, 0x7f, 0x0, 0x7, 0xf8, 0x0, 0x3f, 0xc0,
    0x3, 0xfe, 0x0, 0x3f, 0xf0, 0x1, 0xef, 0x80,
    0x1e, 0x7c, 0x0, 0xf3, 0xe0, 0xf, 0x1f, 0x0,
    0xf8, 0xf8, 0x7, 0x87, 0xc0, 0x78, 0x3e, 0x3,
    0xc1, 0xf0, 0x3c, 0xf, 0x83, 0xe0, 0x7c, 0x1e,
    0x3, 0xe1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xe0, 0x1, 0xf0, 0x0,
    0xf, 0x80, 0x0, 0x7c, 0x0, 0x3, 0xe0, 0x0,
    0x1f, 0x0, 0x0, 0xf8, 0x0,

    /* U+35 "5" */
    0x3f, 0xff, 0xc7, 0xff, 0xf8, 0xff, 0xff, 0x1f,
    0xff, 0xe3, 0xc0, 0x0, 0x78, 0x0, 0xf, 0x0,
    0x1, 0xe0, 0x0, 0x7c, 0x0, 0xf, 0xbf, 0x1,
    0xff, 0xf8, 0x3f, 0xff, 0x87, 0xff, 0xf8, 0xf8,
    0x3f, 0x82, 0x1, 0xf0, 0x0, 0x3f, 0x0, 0x3,
    0xe0, 0x0, 0x7c, 0x0, 0xf, 0x80, 0x1, 0xf0,
    0x0, 0x3f, 0xf0, 0x7, 0xfe, 0x1, 0xff, 0xe0,
    0x3e, 0x7e, 0x1f, 0xc7, 0xff, 0xf0, 0x7f, 0xfc,
    0x7, 0xff, 0x0, 0x3f, 0x80,

    /* U+36 "6" */
    0x0, 0x3e, 0x0, 0x3f, 0xc0, 0x1f, 0xf8, 0x7,
    0xff, 0x1, 0xfe, 0x0, 0x3e, 0x0, 0xf, 0x80,
    0x1, 0xe0, 0x0, 0x7c, 0x0, 0xf, 0x9f, 0x81,
    0xef, 0xfc, 0x7f, 0xff, 0xcf, 0xff, 0xf9, 0xfe,
    0x1f, 0xbf, 0x1, 0xf7, 0xc0, 0x3f, 0xf8, 0x3,
    0xff, 0x0, 0x7f, 0xe0, 0xf, 0xfc, 0x1, 0xff,
    0x80, 0x3f, 0xf8, 0x7, 0xdf, 0x1, 0xf3, 0xf0,
    0x3e, 0x3f, 0xf, 0xc7, 0xff, 0xf0, 0x7f, 0xfc,
    0x7, 0xff, 0x0, 0x3f, 0x80,

    /* U+37 "7" */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0x0, 0x1, 0xe0, 0x0, 0x3e, 0x0,
    0x3, 0xc0, 0x0, 0x7c, 0x0, 0x7, 0x80, 0x0,
    0xf8, 0x0, 0xf, 0x80, 0x1, 0xf0, 0x0, 0x1f,
    0x0, 0x1, 0xe0, 0x0, 0x3e, 0x0, 0x3, 0xc0,
    0x0, 0x7c, 0x0, 0x7, 0xc0, 0x0, 0xf8, 0x0,
    0xf, 0x80, 0x1, 0xf0, 0x0, 0x1f, 0x0, 0x3,
    0xe0, 0x0, 0x3e, 0x0, 0x7, 0xc0, 0x0, 0x7c,
    0x0, 0x7, 0xc0, 0x0, 0xf8, 0x0, 0xf, 0x80,
    0x0,

    /* U+38 "8" */
    0x3, 0xf8, 0x1, 0xff, 0xc0, 0x7f, 0xfc, 0x1f,
    0xff, 0xc3, 0xf1, 0xf8, 0xfc, 0x1f, 0x9f, 0x1,
    0xf3, 0xe0, 0x3e, 0x7c, 0x7, 0xcf, 0x80, 0xf8,
    0xf8, 0x3e, 0x1f, 0x8f, 0xc1, 0xff, 0xf0, 0x1f,
    0xfc, 0x3, 0xff, 0x81, 0xff, 0xfc, 0x7e, 0xf,
    0xcf, 0x80, 0xfb, 0xe0, 0xf, 0xfc, 0x1, 0xff,
    0x80, 0x3f, 0xf0, 0x7, 0xfe, 0x0, 0xff, 0xe0,
    0x3f, 0x7e, 0xf, 0xcf, 0xff, 0xf8, 0xff, 0xfe,
    0x7, 0xff, 0x0, 0x3f, 0x80,

    /* U+39 "9" */
    0x3, 0xf8, 0x1, 0xff, 0xc0, 0x7f, 0xfc, 0x1f,
    0xff, 0xc7, 0xe1, 0xf8, 0xf8, 0xf, 0xbf, 0x1,
    0xf7, 0xc0, 0x1e, 0xf8, 0x3, 0xff, 0x0, 0x7f,
    0xe0, 0xf, 0xfc, 0x1, 0xff, 0xc0, 0x3e, 0xf8,
    0xf, 0xdf, 0x83, 0xf9, 0xff, 0xff, 0x3f, 0xff,
    0xe3, 0xff, 0x7c, 0x1f, 0x8f, 0x0, 0x1, 0xe0,
    0x0, 0x7c, 0x0, 0xf, 0x80, 0x3, 0xe0, 0x0,
    0xf8, 0x0, 0x7f, 0x1, 0xff, 0xc0, 0x3f, 0xf0,
    0x7, 0xf8, 0x0, 0xf8, 0x0,

    /* U+3A ":" */
    0x77, 0xff, 0xf7, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x3, 0xbf, 0xff, 0xb8
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 364, .box_w = 19, .box_h = 29, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 69, .adv_w = 364, .box_w = 12, .box_h = 29, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 113, .adv_w = 364, .box_w = 20, .box_h = 29, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 186, .adv_w = 364, .box_w = 19, .box_h = 29, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 255, .adv_w = 364, .box_w = 21, .box_h = 29, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 332, .adv_w = 364, .box_w = 19, .box_h = 29, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 401, .adv_w = 363, .box_w = 19, .box_h = 29, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 470, .adv_w = 364, .box_w = 20, .box_h = 29, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 543, .adv_w = 364, .box_w = 19, .box_h = 29, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 612, .adv_w = 364, .box_w = 19, .box_h = 29, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 681, .adv_w = 170, .box_w = 5, .box_h = 22, .ofs_x = 3, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 48, .range_length = 11, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

/*Store all the custom data of the font*/
static lv_font_fmt_txt_dsc_t font_dsc = {
    .glyph_bitmap = gylph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
lv_font_t RobotoFont40px = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 29,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
    .subpx = LV_FONT_SUBPX_NONE,
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};

#endif /*#if ROBOTOFONT40PX*/

