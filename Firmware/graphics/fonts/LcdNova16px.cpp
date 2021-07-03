/*******************************************************************************
 * Size: 16 px
 * Bpp: 2
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef LCDNOVA16PX
#define LCDNOVA16PX 1
#endif

#if LCDNOVA16PX

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0021 "!" */
    0x21, 0xc7, 0x1c, 0x70, 0x82, 0x1c, 0x70, 0x83,
    0x8,

    /* U+0022 "\"" */
    0x21, 0x9c, 0xb7, 0x2c, 0x86,

    /* U+0023 "#" */
    0x0, 0x4, 0x0, 0xa, 0x34, 0x0, 0x28, 0xd0,
    0x0, 0xa3, 0x40, 0xbf, 0xfb, 0xf4, 0x5a, 0x75,
    0x40, 0x28, 0xd0, 0x0, 0xa3, 0x40, 0xbf, 0xfb,
    0xf4, 0x5a, 0x75, 0x40, 0x28, 0xd0, 0x0, 0xa3,
    0x40, 0x1, 0x44, 0x0,

    /* U+0024 "$" */
    0x0, 0x80, 0x2, 0xc0, 0xf, 0xb8, 0x35, 0x1e,
    0x70, 0xa, 0x70, 0x0, 0x70, 0x0, 0x1f, 0xf8,
    0x5, 0x5a, 0x0, 0xe, 0x10, 0xe, 0x70, 0xe,
    0x35, 0x1a, 0xf, 0xb8, 0x2, 0xc0, 0x0, 0x80,

    /* U+0025 "%" */
    0xf, 0xd0, 0x0, 0x3, 0x57, 0x40, 0x40, 0x70,
    0x34, 0x2c, 0x7, 0x3, 0x4b, 0x40, 0x70, 0x36,
    0xe0, 0x1, 0xfe, 0xbf, 0xf0, 0x5, 0x6f, 0xd5,
    0xc0, 0xb, 0x6c, 0x1c, 0x2, 0xd2, 0xc1, 0xc0,
    0x74, 0x2c, 0x1c, 0x1, 0x1, 0xd6, 0xc0, 0x0,
    0xb, 0xf0,

    /* U+0026 "&" */
    0xf, 0xe0, 0x3, 0x54, 0x0, 0x70, 0x0, 0x7,
    0x0, 0xa0, 0x70, 0xe, 0x1, 0xff, 0xfc, 0x35,
    0x5a, 0x47, 0x0, 0xe0, 0x70, 0xe, 0x7, 0x0,
    0xe0, 0x35, 0x5a, 0x0, 0xff, 0x80,

    /* U+0027 "'" */
    0x21, 0xc7, 0x8,

    /* U+0028 "(" */
    0xf, 0xd, 0x47, 0x1, 0xc0, 0x70, 0x8, 0x2,
    0x1, 0xc0, 0x70, 0x1c, 0x3, 0x50, 0x3c,

    /* U+0029 ")" */
    0x3c, 0x6, 0xc0, 0x70, 0x1c, 0x7, 0x0, 0x80,
    0x20, 0x1c, 0x7, 0x1, 0xc1, 0xb0, 0xf0,

    /* U+002A "*" */
    0x0, 0x0, 0x22, 0x24, 0x3c, 0xb0, 0x4f, 0xd4,
    0x8a, 0xc8, 0x2d, 0xf0, 0x75, 0x34, 0x1, 0x0,

    /* U+002B "+" */
    0x0, 0x0, 0x0, 0xb0, 0x0, 0x2c, 0x0, 0xb,
    0x0, 0xbf, 0xbf, 0x5, 0xb5, 0x0, 0x2c, 0x0,
    0xb, 0x0, 0x0, 0x40, 0x0,

    /* U+002C "," */
    0x0, 0xc7, 0x0,

    /* U+002D "-" */
    0x0, 0xb, 0xfc, 0x15, 0x40,

    /* U+002E "." */
    0x21, 0xc1, 0x0,

    /* U+002F "/" */
    0x0, 0xa0, 0xd, 0x1, 0xc0, 0x38, 0x3, 0x0,
    0xb0, 0xd, 0x1, 0xc0, 0x28, 0x3, 0x40, 0xb0,
    0x9, 0x0,

    /* U+0030 "0" */
    0xf, 0xf8, 0x35, 0x7e, 0x70, 0x7e, 0x70, 0xbe,
    0x70, 0xde, 0x21, 0xc9, 0x22, 0x89, 0x73, 0x4e,
    0x7b, 0xe, 0x7e, 0xe, 0x3a, 0x5e, 0xf, 0xf8,

    /* U+0031 "1" */
    0xf, 0x80, 0x1, 0xb0, 0x0, 0x1c, 0x0, 0x7,
    0x0, 0x1, 0xc0, 0x0, 0x60, 0x0, 0x18, 0x0,
    0x7, 0x0, 0x1, 0xc0, 0x0, 0x70, 0x1, 0x6d,
    0x51, 0xfd, 0xfc,

    /* U+0032 "2" */
    0xf, 0xf8, 0x5, 0x5e, 0x0, 0xe, 0x0, 0xe,
    0x0, 0xe, 0x1f, 0xf8, 0x35, 0x50, 0x70, 0x0,
    0x70, 0x0, 0x70, 0x0, 0x75, 0x54, 0x3f, 0xfd,

    /* U+0033 "3" */
    0x3f, 0xfd, 0x15, 0xb8, 0x0, 0xe0, 0x7, 0x80,
    0xa, 0x0, 0xf, 0xf8, 0x5, 0x5a, 0x0, 0xe,
    0x0, 0xe, 0x0, 0xe, 0x15, 0x5a, 0x3f, 0xf8,

    /* U+0034 "4" */
    0x0, 0xba, 0x2, 0xcb, 0xf, 0xb, 0x3c, 0xb,
    0x30, 0xa, 0xbf, 0xfc, 0x15, 0x5a, 0x0, 0xb,
    0x0, 0xb, 0x0, 0xb, 0x0, 0xb, 0x0, 0x0,

    /* U+0035 "5" */
    0x3f, 0xfc, 0x75, 0x50, 0x70, 0x0, 0x70, 0x0,
    0x70, 0x0, 0x1f, 0xf8, 0x5, 0x5a, 0x0, 0xe,
    0x0, 0xe, 0x0, 0xe, 0x15, 0x5a, 0x3f, 0xf8,

    /* U+0036 "6" */
    0xf, 0xf8, 0x35, 0x50, 0x70, 0x0, 0x70, 0x0,
    0x70, 0x0, 0x1f, 0xf8, 0x35, 0x5a, 0x70, 0xe,
    0x70, 0xe, 0x70, 0xe, 0x35, 0x5a, 0xf, 0xf8,

    /* U+0037 "7" */
    0x3f, 0xfd, 0x15, 0x5e, 0x0, 0xe, 0x0, 0xe,
    0x0, 0xe, 0x0, 0xb8, 0x2, 0xd0, 0x2, 0xc0,
    0x2, 0xc0, 0x2, 0xc0, 0x2, 0xc0, 0x0, 0x0,

    /* U+0038 "8" */
    0xf, 0xf8, 0x35, 0x5e, 0x70, 0xe, 0x70, 0xe,
    0x70, 0xe, 0x1f, 0xfc, 0x35, 0x5a, 0x70, 0xe,
    0x70, 0xe, 0x70, 0xe, 0x35, 0x5a, 0xf, 0xf8,

    /* U+0039 "9" */
    0xf, 0xf8, 0x35, 0x5e, 0x70, 0xe, 0x70, 0xe,
    0x70, 0xe, 0x1f, 0xfc, 0x5, 0x5a, 0x0, 0xe,
    0x0, 0xe, 0x0, 0xe, 0x5, 0x5a, 0xf, 0xf8,

    /* U+003A ":" */
    0x0, 0xc3, 0x0, 0x0, 0x3, 0x8,

    /* U+003B ";" */
    0x0, 0xc3, 0x0, 0x0, 0x3, 0x1c, 0x0,

    /* U+003C "<" */
    0x0, 0x0, 0xe0, 0xf0, 0xb0, 0x2d, 0x2, 0xd0,
    0x2c,

    /* U+003D "=" */
    0x0, 0x3, 0xfe, 0x5, 0x40, 0x0, 0x3f, 0xe0,
    0x54,

    /* U+003E ">" */
    0x0, 0x1d, 0x2, 0xd0, 0x2d, 0xf, 0x4f, 0x47,
    0x40,

    /* U+003F "?" */
    0xbf, 0xe0, 0x55, 0xa0, 0x2, 0xc0, 0xb, 0x0,
    0x2c, 0x7, 0xc0, 0x74, 0x1, 0xc0, 0x3, 0x0,
    0x8, 0x0, 0x70, 0x0, 0x40,

    /* U+0040 "@" */
    0xf, 0xfb, 0xff, 0xd, 0x54, 0x55, 0xb7, 0x0,
    0x0, 0x2d, 0xc0, 0xbd, 0xb, 0x70, 0xa5, 0xc2,
    0xc8, 0x28, 0x34, 0xb3, 0xa, 0xd, 0x2d, 0xc0,
    0xbe, 0xfc, 0x70, 0x5, 0x4, 0x1c, 0x0, 0x0,
    0x3, 0x55, 0x0, 0x0, 0x3f, 0xe0, 0x0,

    /* U+0041 "A" */
    0xf, 0xfe, 0x35, 0x5e, 0x70, 0xe, 0x70, 0xe,
    0x70, 0xe, 0x1f, 0xfc, 0x35, 0x5e, 0x70, 0xe,
    0x70, 0xe, 0x70, 0xe, 0x70, 0xe, 0x10, 0x0,

    /* U+0042 "B" */
    0x3f, 0xf8, 0x75, 0x5e, 0x70, 0xe, 0x70, 0xe,
    0x70, 0xe, 0x1f, 0xfc, 0x35, 0x5a, 0x70, 0xe,
    0x70, 0xe, 0x70, 0xe, 0x75, 0x5a, 0x3f, 0xf8,

    /* U+0043 "C" */
    0xf, 0xf8, 0x35, 0x5e, 0x70, 0xe, 0x70, 0x4,
    0x70, 0x0, 0x20, 0x0, 0x20, 0x0, 0x70, 0x0,
    0x70, 0x4, 0x70, 0xe, 0x35, 0x5e, 0xf, 0xf8,

    /* U+0044 "D" */
    0x3f, 0xf8, 0x75, 0x5e, 0x70, 0xe, 0x70, 0xe,
    0x70, 0xe, 0x20, 0x9, 0x20, 0x9, 0x70, 0xe,
    0x70, 0xe, 0x70, 0xe, 0x75, 0x5e, 0x3f, 0xf8,

    /* U+0045 "E" */
    0x3f, 0xf9, 0xd5, 0x47, 0x0, 0x1c, 0x0, 0x70,
    0x0, 0x7f, 0xe3, 0x55, 0x1c, 0x0, 0x70, 0x1,
    0xc0, 0x7, 0x55, 0xf, 0xfe,

    /* U+0046 "F" */
    0x3f, 0xf9, 0xd5, 0x47, 0x0, 0x1c, 0x0, 0x70,
    0x0, 0x7f, 0xe3, 0x55, 0x1c, 0x0, 0x70, 0x1,
    0xc0, 0x7, 0x0, 0x4, 0x0,

    /* U+0047 "G" */
    0xf, 0xf8, 0x35, 0x5e, 0x70, 0xa, 0x70, 0x0,
    0x70, 0x0, 0x20, 0xfe, 0x30, 0x1a, 0x70, 0xe,
    0x70, 0xe, 0x70, 0xe, 0x35, 0x5a, 0xf, 0xf8,

    /* U+0048 "H" */
    0x0, 0x0, 0x30, 0xa, 0x70, 0xe, 0x70, 0xe,
    0x70, 0xe, 0x70, 0xe, 0x1f, 0xfc, 0x35, 0x5e,
    0x70, 0xe, 0x70, 0xe, 0x70, 0xe, 0x70, 0xe,
    0x10, 0x0,

    /* U+0049 "I" */
    0x3f, 0x7d, 0x16, 0xd4, 0x2, 0xc0, 0x2, 0xc0,
    0x2, 0xc0, 0x1, 0x80, 0x1, 0x80, 0x2, 0xc0,
    0x2, 0xc0, 0x2, 0xc0, 0x16, 0xd4, 0x3f, 0x7d,

    /* U+004A "J" */
    0x0, 0x9, 0x0, 0xe, 0x0, 0xe, 0x0, 0xe,
    0x0, 0xe, 0x0, 0x5, 0x20, 0x5, 0x70, 0xe,
    0x70, 0xe, 0x70, 0xe, 0x35, 0x5e, 0xf, 0xf8,

    /* U+004B "K" */
    0x30, 0x1c, 0x70, 0x74, 0x71, 0xd0, 0x77, 0x40,
    0x7a, 0x0, 0x1f, 0xf8, 0x35, 0x5e, 0x70, 0xe,
    0x70, 0xe, 0x70, 0xe, 0x70, 0xe, 0x10, 0x0,

    /* U+004C "L" */
    0x20, 0x1, 0xc0, 0x7, 0x0, 0x1c, 0x0, 0x70,
    0x0, 0x80, 0x2, 0x0, 0x1c, 0x0, 0x70, 0x1,
    0xc0, 0x7, 0x55, 0xf, 0xfe,

    /* U+004D "M" */
    0x10, 0x0, 0x11, 0xf8, 0x7, 0xd7, 0x74, 0x37,
    0x5c, 0xb3, 0x8d, 0x70, 0xfc, 0x34, 0xc0, 0x90,
    0xd2, 0x0, 0x1, 0x1c, 0x0, 0xd, 0x70, 0x0,
    0x35, 0xc0, 0x0, 0xd7, 0x0, 0x3, 0x4c, 0x0,
    0xd, 0x0, 0x0, 0x0,

    /* U+004E "N" */
    0x0, 0x0, 0x35, 0xa, 0x7b, 0xe, 0x73, 0xce,
    0x70, 0xee, 0x70, 0x7e, 0x20, 0x5, 0x30, 0xa,
    0x70, 0xe, 0x70, 0xe, 0x70, 0xe, 0x70, 0xe,
    0x10, 0x4,

    /* U+004F "O" */
    0xf, 0xf8, 0x35, 0x5e, 0x70, 0xe, 0x70, 0xe,
    0x70, 0xe, 0x20, 0x9, 0x20, 0x9, 0x70, 0xe,
    0x70, 0xe, 0x70, 0xe, 0x35, 0x5e, 0xf, 0xf8,

    /* U+0050 "P" */
    0x3f, 0xf8, 0x75, 0x5a, 0x70, 0xb, 0x70, 0xb,
    0x70, 0xb, 0x1f, 0xfc, 0x35, 0x50, 0x70, 0x0,
    0x70, 0x0, 0x70, 0x0, 0x70, 0x0, 0x10, 0x0,

    /* U+0051 "Q" */
    0xf, 0xf8, 0x35, 0x5e, 0x70, 0xe, 0x70, 0xe,
    0x70, 0xe, 0x20, 0x9, 0x20, 0x9, 0x70, 0xe,
    0x70, 0xe, 0x71, 0xce, 0x36, 0xde, 0xf, 0xb8,
    0x2, 0xc0, 0x1, 0xc0, 0x0, 0xb8, 0x0, 0x10,

    /* U+0052 "R" */
    0x3f, 0xf8, 0x75, 0x5e, 0x70, 0xe, 0x70, 0xe,
    0x70, 0xe, 0x1f, 0xf8, 0x3a, 0x50, 0x7b, 0x40,
    0x72, 0xc0, 0x70, 0xf0, 0x70, 0x3c, 0x20, 0xd,

    /* U+0053 "S" */
    0xf, 0xf8, 0x35, 0x5e, 0x70, 0xa, 0x70, 0x0,
    0x70, 0x0, 0x1f, 0xf8, 0x5, 0x5a, 0x0, 0xe,
    0x10, 0xe, 0x70, 0xe, 0x35, 0x5a, 0xf, 0xf8,

    /* U+0054 "T" */
    0xbf, 0x7f, 0x85, 0xb5, 0x40, 0x1c, 0x0, 0x7,
    0x0, 0x1, 0xc0, 0x0, 0x20, 0x0, 0x8, 0x0,
    0x7, 0x0, 0x1, 0xc0, 0x0, 0x70, 0x0, 0x1c,
    0x0, 0x2, 0x0,

    /* U+0055 "U" */
    0x20, 0x9, 0x70, 0xe, 0x70, 0xe, 0x70, 0xe,
    0x70, 0xe, 0x20, 0x9, 0x20, 0x9, 0x70, 0xe,
    0x70, 0xe, 0x70, 0xe, 0x35, 0x5e, 0xf, 0xf8,

    /* U+0056 "V" */
    0x20, 0x8, 0x70, 0xd, 0x70, 0xd, 0x70, 0xd,
    0x70, 0xd, 0x20, 0xc, 0x20, 0x34, 0x70, 0xf0,
    0x77, 0xc0, 0x7f, 0x0, 0x78, 0x0, 0x20, 0x0,

    /* U+0057 "W" */
    0x0, 0x0, 0x0, 0xc0, 0x0, 0xd7, 0x0, 0x3,
    0x5c, 0x0, 0xd, 0x70, 0x0, 0x35, 0xc0, 0x0,
    0xd2, 0x0, 0x1, 0xc, 0x9, 0xd, 0x70, 0xfc,
    0x35, 0xcb, 0x38, 0xd7, 0x74, 0x37, 0x5f, 0x80,
    0x7d, 0x10, 0x0, 0x10,

    /* U+0058 "X" */
    0x70, 0x3, 0xe, 0x2, 0xc1, 0xc0, 0xd0, 0x38,
    0xb0, 0x7, 0x74, 0x0, 0xf8, 0x0, 0x3e, 0x0,
    0x1d, 0xd0, 0xe, 0x2c, 0x7, 0x3, 0x43, 0x80,
    0xb1, 0xc0, 0xc,

    /* U+0059 "Y" */
    0x0, 0x0, 0x30, 0xa, 0x70, 0xe, 0x70, 0xe,
    0x70, 0xe, 0x70, 0xe, 0x1f, 0xfc, 0x5, 0x5a,
    0x0, 0xe, 0x0, 0xe, 0x0, 0xe, 0x15, 0x5a,
    0x3f, 0xf8,

    /* U+005A "Z" */
    0xbf, 0xfd, 0x15, 0x5c, 0x0, 0x2c, 0x0, 0x34,
    0x0, 0xf0, 0x0, 0xc0, 0x3, 0x0, 0xf, 0x0,
    0x2c, 0x0, 0x38, 0x0, 0x35, 0x54, 0xbf, 0xfd,

    /* U+005B "[" */
    0x3f, 0x1d, 0x47, 0x1, 0xc0, 0x70, 0x8, 0x2,
    0x1, 0xc0, 0x70, 0x1c, 0x7, 0x50, 0xfc,

    /* U+005C "\\" */
    0x90, 0xb, 0x0, 0x34, 0x2, 0x80, 0x1c, 0x0,
    0xd0, 0xb, 0x0, 0x30, 0x3, 0x80, 0x1c, 0x0,
    0xd0, 0xa,

    /* U+005D "]" */
    0xbd, 0x1e, 0xe, 0xe, 0xe, 0x9, 0x9, 0xe,
    0xe, 0xe, 0x1e, 0xbd,

    /* U+005E "^" */
    0x0, 0x0, 0x18, 0x1, 0xfc, 0x1e, 0x3c, 0xe0,
    0x34,

    /* U+005F "_" */
    0x0, 0x0, 0x0, 0x2f, 0xff, 0xff, 0xc1, 0x55,
    0x55, 0x40,

    /* U+0060 "`" */
    0xe0, 0x78, 0x1c,

    /* U+0061 "a" */
    0xf, 0xfe, 0x35, 0x5e, 0x70, 0xe, 0x70, 0xe,
    0x70, 0xe, 0x1f, 0xfc, 0x35, 0x5e, 0x70, 0xe,
    0x70, 0xe, 0x70, 0xe, 0x70, 0xe, 0x10, 0x0,

    /* U+0062 "b" */
    0x3f, 0xf8, 0x75, 0x5e, 0x70, 0xe, 0x70, 0xe,
    0x70, 0xe, 0x1f, 0xfc, 0x35, 0x5a, 0x70, 0xe,
    0x70, 0xe, 0x70, 0xe, 0x75, 0x5a, 0x3f, 0xf8,

    /* U+0063 "c" */
    0xf, 0xf8, 0x35, 0x5e, 0x70, 0xe, 0x70, 0x4,
    0x70, 0x0, 0x20, 0x0, 0x20, 0x0, 0x70, 0x0,
    0x70, 0x4, 0x70, 0xe, 0x35, 0x5e, 0xf, 0xf8,

    /* U+0064 "d" */
    0x3f, 0xf8, 0x75, 0x5e, 0x70, 0xe, 0x70, 0xe,
    0x70, 0xe, 0x20, 0x9, 0x20, 0x9, 0x70, 0xe,
    0x70, 0xe, 0x70, 0xe, 0x75, 0x5e, 0x3f, 0xf8,

    /* U+0065 "e" */
    0x3f, 0xf9, 0xd5, 0x47, 0x0, 0x1c, 0x0, 0x70,
    0x0, 0x7f, 0xe3, 0x55, 0x1c, 0x0, 0x70, 0x1,
    0xc0, 0x7, 0x55, 0xf, 0xfe,

    /* U+0066 "f" */
    0x3f, 0xf9, 0xd5, 0x47, 0x0, 0x1c, 0x0, 0x70,
    0x0, 0x7f, 0xe3, 0x55, 0x1c, 0x0, 0x70, 0x1,
    0xc0, 0x7, 0x0, 0x4, 0x0,

    /* U+0067 "g" */
    0xf, 0xf8, 0x35, 0x5e, 0x70, 0xa, 0x70, 0x0,
    0x70, 0x0, 0x20, 0xfe, 0x30, 0x1a, 0x70, 0xe,
    0x70, 0xe, 0x70, 0xe, 0x35, 0x5a, 0xf, 0xf8,

    /* U+0068 "h" */
    0x0, 0x0, 0x30, 0xa, 0x70, 0xe, 0x70, 0xe,
    0x70, 0xe, 0x70, 0xe, 0x1f, 0xfc, 0x35, 0x5e,
    0x70, 0xe, 0x70, 0xe, 0x70, 0xe, 0x70, 0xe,
    0x10, 0x0,

    /* U+0069 "i" */
    0x3f, 0x7d, 0x16, 0xd4, 0x2, 0xc0, 0x2, 0xc0,
    0x2, 0xc0, 0x1, 0x80, 0x1, 0x80, 0x2, 0xc0,
    0x2, 0xc0, 0x2, 0xc0, 0x16, 0xd4, 0x3f, 0x7d,

    /* U+006A "j" */
    0x0, 0x9, 0x0, 0xe, 0x0, 0xe, 0x0, 0xe,
    0x0, 0xe, 0x0, 0x5, 0x20, 0x5, 0x70, 0xe,
    0x70, 0xe, 0x70, 0xe, 0x35, 0x5e, 0xf, 0xf8,

    /* U+006B "k" */
    0x30, 0x1c, 0x70, 0x74, 0x71, 0xd0, 0x77, 0x40,
    0x7a, 0x0, 0x1f, 0xf8, 0x35, 0x5e, 0x70, 0xe,
    0x70, 0xe, 0x70, 0xe, 0x70, 0xe, 0x10, 0x0,

    /* U+006C "l" */
    0x20, 0x1, 0xc0, 0x7, 0x0, 0x1c, 0x0, 0x70,
    0x0, 0x80, 0x2, 0x0, 0x1c, 0x0, 0x70, 0x1,
    0xc0, 0x7, 0x55, 0xf, 0xfe,

    /* U+006D "m" */
    0x10, 0x0, 0x11, 0xf8, 0x7, 0xd7, 0x74, 0x37,
    0x5c, 0xb3, 0x8d, 0x70, 0xfc, 0x34, 0xc0, 0x90,
    0xd2, 0x0, 0x1, 0x1c, 0x0, 0xd, 0x70, 0x0,
    0x35, 0xc0, 0x0, 0xd7, 0x0, 0x3, 0x4c, 0x0,
    0xd, 0x0, 0x0, 0x0,

    /* U+006E "n" */
    0x0, 0x0, 0x35, 0xa, 0x7b, 0xe, 0x73, 0xce,
    0x70, 0xee, 0x70, 0x7e, 0x20, 0x5, 0x30, 0xa,
    0x70, 0xe, 0x70, 0xe, 0x70, 0xe, 0x70, 0xe,
    0x10, 0x4,

    /* U+006F "o" */
    0xf, 0xf8, 0x35, 0x5e, 0x70, 0xe, 0x70, 0xe,
    0x70, 0xe, 0x20, 0x9, 0x20, 0x9, 0x70, 0xe,
    0x70, 0xe, 0x70, 0xe, 0x35, 0x5e, 0xf, 0xf8,

    /* U+0070 "p" */
    0x3f, 0xf8, 0x75, 0x5a, 0x70, 0xb, 0x70, 0xb,
    0x70, 0xb, 0x1f, 0xfc, 0x35, 0x50, 0x70, 0x0,
    0x70, 0x0, 0x70, 0x0, 0x70, 0x0, 0x10, 0x0,

    /* U+0071 "q" */
    0xf, 0xf8, 0x35, 0x5e, 0x70, 0xe, 0x70, 0xe,
    0x70, 0xe, 0x20, 0x9, 0x20, 0x9, 0x70, 0xe,
    0x70, 0xe, 0x71, 0xce, 0x36, 0xde, 0xf, 0xb8,
    0x2, 0xc0, 0x1, 0xc0, 0x0, 0xb8, 0x0, 0x10,

    /* U+0072 "r" */
    0x3f, 0xf8, 0x75, 0x5e, 0x70, 0xe, 0x70, 0xe,
    0x70, 0xe, 0x1f, 0xf8, 0x3a, 0x50, 0x7b, 0x40,
    0x72, 0xc0, 0x70, 0xf0, 0x70, 0x3c, 0x20, 0xd,

    /* U+0073 "s" */
    0xf, 0xf8, 0x35, 0x5e, 0x70, 0xa, 0x70, 0x0,
    0x70, 0x0, 0x1f, 0xf8, 0x5, 0x5a, 0x0, 0xe,
    0x10, 0xe, 0x70, 0xe, 0x35, 0x5a, 0xf, 0xf8,

    /* U+0074 "t" */
    0xbf, 0x7f, 0x85, 0xb5, 0x40, 0x1c, 0x0, 0x7,
    0x0, 0x1, 0xc0, 0x0, 0x20, 0x0, 0x8, 0x0,
    0x7, 0x0, 0x1, 0xc0, 0x0, 0x70, 0x0, 0x1c,
    0x0, 0x2, 0x0,

    /* U+0075 "u" */
    0x20, 0x9, 0x70, 0xe, 0x70, 0xe, 0x70, 0xe,
    0x70, 0xe, 0x20, 0x9, 0x20, 0x9, 0x70, 0xe,
    0x70, 0xe, 0x70, 0xe, 0x35, 0x5e, 0xf, 0xf8,

    /* U+0076 "v" */
    0x20, 0x8, 0x70, 0xd, 0x70, 0xd, 0x70, 0xd,
    0x70, 0xd, 0x20, 0xc, 0x20, 0x34, 0x70, 0xf0,
    0x77, 0xc0, 0x7f, 0x0, 0x78, 0x0, 0x20, 0x0,

    /* U+0077 "w" */
    0x0, 0x0, 0x0, 0xc0, 0x0, 0xd7, 0x0, 0x3,
    0x5c, 0x0, 0xd, 0x70, 0x0, 0x35, 0xc0, 0x0,
    0xd2, 0x0, 0x1, 0xc, 0x9, 0xd, 0x70, 0xfc,
    0x35, 0xcb, 0x38, 0xd7, 0x74, 0x37, 0x5f, 0x80,
    0x7d, 0x10, 0x0, 0x10,

    /* U+0078 "x" */
    0x70, 0x3, 0xe, 0x2, 0xc1, 0xc0, 0xd0, 0x38,
    0xb0, 0x7, 0x74, 0x0, 0xf8, 0x0, 0x3e, 0x0,
    0x1d, 0xd0, 0xe, 0x2c, 0x7, 0x3, 0x43, 0x80,
    0xb1, 0xc0, 0xc,

    /* U+0079 "y" */
    0x0, 0x0, 0x30, 0xa, 0x70, 0xe, 0x70, 0xe,
    0x70, 0xe, 0x70, 0xe, 0x1f, 0xfc, 0x5, 0x5a,
    0x0, 0xe, 0x0, 0xe, 0x0, 0xe, 0x15, 0x5a,
    0x3f, 0xf8,

    /* U+007A "z" */
    0xbf, 0xfd, 0x15, 0x5c, 0x0, 0x2c, 0x0, 0x34,
    0x0, 0xf0, 0x0, 0xc0, 0x3, 0x0, 0xf, 0x0,
    0x2c, 0x0, 0x38, 0x0, 0x35, 0x54, 0xbf, 0xfd,

    /* U+007B "{" */
    0x3, 0xc0, 0xe4, 0xd, 0x0, 0xd0, 0xd, 0xb,
    0x80, 0x1d, 0x0, 0xd0, 0xd, 0x0, 0xd0, 0xe,
    0x40, 0x3c,

    /* U+007C "|" */
    0x21, 0xc7, 0x1c, 0x70, 0x82, 0x1c, 0x71, 0xc7,
    0x8,

    /* U+007D "}" */
    0xb4, 0x1, 0xd0, 0xe, 0x0, 0xe0, 0xe, 0x0,
    0x7c, 0xe, 0x0, 0xe0, 0xe, 0x0, 0xe0, 0x1d,
    0xb, 0x40,

    /* U+007E "~" */
    0x1f, 0xc0, 0xe7, 0x8f, 0x3c, 0xe0, 0x3f, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 66, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 46, .box_w = 3, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 9, .adv_w = 88, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 14, .adv_w = 170, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 50, .adv_w = 134, .box_w = 8, .box_h = 16, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 82, .adv_w = 222, .box_w = 14, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 124, .adv_w = 152, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 154, .adv_w = 46, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 157, .adv_w = 77, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 172, .adv_w = 77, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 187, .adv_w = 115, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 203, .adv_w = 131, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 224, .adv_w = 46, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 227, .adv_w = 90, .box_w = 6, .box_h = 3, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 232, .adv_w = 46, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 235, .adv_w = 94, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 253, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 277, .adv_w = 134, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 304, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 328, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 352, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 376, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 400, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 424, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 448, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 472, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 496, .adv_w = 46, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 502, .adv_w = 46, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 509, .adv_w = 88, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 518, .adv_w = 107, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 527, .adv_w = 88, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 536, .adv_w = 122, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 557, .adv_w = 219, .box_w = 13, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 596, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 620, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 644, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 668, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 692, .adv_w = 114, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 713, .adv_w = 114, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 734, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 758, .adv_w = 134, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 784, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 808, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 832, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 856, .adv_w = 111, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 877, .adv_w = 179, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 913, .adv_w = 134, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 939, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 963, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 987, .adv_w = 134, .box_w = 8, .box_h = 16, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1019, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1043, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1067, .adv_w = 142, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1094, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1118, .adv_w = 128, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1142, .adv_w = 179, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1178, .adv_w = 143, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1205, .adv_w = 134, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1231, .adv_w = 127, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1255, .adv_w = 68, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1270, .adv_w = 94, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1288, .adv_w = 68, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1300, .adv_w = 106, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 1309, .adv_w = 193, .box_w = 13, .box_h = 3, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1319, .adv_w = 54, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 9},
    {.bitmap_index = 1322, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1346, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1370, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1394, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1418, .adv_w = 114, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1439, .adv_w = 114, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1460, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1484, .adv_w = 134, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1510, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1534, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1558, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1582, .adv_w = 111, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1603, .adv_w = 179, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1639, .adv_w = 134, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1665, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1689, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1713, .adv_w = 134, .box_w = 8, .box_h = 16, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1745, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1769, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1793, .adv_w = 142, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1820, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1844, .adv_w = 128, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1868, .adv_w = 179, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1904, .adv_w = 143, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1931, .adv_w = 134, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1957, .adv_w = 127, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1981, .adv_w = 89, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1999, .adv_w = 46, .box_w = 3, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2008, .adv_w = 89, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2026, .adv_w = 157, .box_w = 10, .box_h = 3, .ofs_x = 0, .ofs_y = 5}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 2,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t LcdNova16px = {
#else
lv_font_t LcdNova16px = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 18,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0)
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if LCDNOVA16PX*/
