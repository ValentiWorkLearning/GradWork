#include "lvgl/lvgl.h"

/*******************************************************************************
 * Size: 24 px
 * Bpp: 2
 * Opts: 
 ******************************************************************************/

#ifndef ICONFONT24PX
#define ICONFONT24PX 1
#endif

#if ICONFONT24PX

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t gylph_bitmap[] = {
    /* U+E801 "" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x1a, 0x0, 0x0,
    0x0, 0x0, 0x5b, 0xff, 0xf0, 0x0, 0x0, 0x6b,
    0xff, 0xe4, 0x2c, 0x0, 0x0, 0xbf, 0x94, 0x0,
    0xb, 0x0, 0x0, 0x38, 0x0, 0x0, 0x6b, 0xc0,
    0x0, 0xe, 0x1, 0x6f, 0xff, 0xf0, 0x0, 0x3,
    0xff, 0xfe, 0x90, 0x2c, 0x0, 0x0, 0xfe, 0x50,
    0x0, 0xb, 0x0, 0x0, 0x38, 0x0, 0x0, 0x2,
    0xc0, 0x0, 0xe, 0x0, 0x0, 0x0, 0xb0, 0x0,
    0x3, 0x80, 0x0, 0x0, 0x2c, 0x0, 0x0, 0xe0,
    0x0, 0x0, 0xb, 0x0, 0x0, 0x38, 0x0, 0x0,
    0x2, 0xc0, 0x0, 0xe, 0x0, 0x0, 0x0, 0xb0,
    0x0, 0x3, 0x80, 0x0, 0xbf, 0xac, 0x0, 0x0,
    0xe0, 0x1, 0xfe, 0xff, 0x0, 0xbe, 0x78, 0x1,
    0xf0, 0x3, 0xc2, 0xff, 0xfe, 0x0, 0xb0, 0x0,
    0xb1, 0xf4, 0xb, 0x80, 0x3c, 0x0, 0x2c, 0xf0,
    0x0, 0xe0, 0xb, 0x0, 0x1d, 0x38, 0x0, 0x38,
    0x0, 0xf4, 0x6e, 0xe, 0x0, 0x1c, 0x0, 0xb,
    0xfd, 0x2, 0xd0, 0x2d, 0x0, 0x0, 0x0, 0x0,
    0x2f, 0xfd, 0x0, 0x0, 0x0, 0x0, 0x0, 0x50,
    0x0, 0x0, 0x0, 0x0, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 384, .box_w = 25, .box_h = 25, .ofs_x = -1, .ofs_y = -4}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 59393, .range_length = 1, .glyph_id_start = 1,
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
    .bpp = 2,
    .kern_classes = 0,
    .bitmap_format = 0
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
const lv_font_t IconFont24px = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 25,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};

#endif /*#if ICONFONT24PX*/

