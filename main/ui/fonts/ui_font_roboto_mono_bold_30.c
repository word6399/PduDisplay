/*******************************************************************************
 * Size: 30 px
 * Bpp: 4
 * Opts: --bpp 4 --size 30 --no-compress --font ..\fonts\Roboto_Mono\static\RobotoMono-Bold.ttf --range 48-57 --format lvgl
 ******************************************************************************/

#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
#else
    #include "lvgl.h"
#endif

#ifndef UI_FONT_ROBOTO_MONO_BOLD_30
#define UI_FONT_ROBOTO_MONO_BOLD_30 1
#endif

#if UI_FONT_ROBOTO_MONO_BOLD_30

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0030 "0" */
    0x0, 0x2, 0x9d, 0xff, 0xd9, 0x30, 0x0, 0x0,
    0x7f, 0xff, 0xff, 0xff, 0xf8, 0x0, 0x6, 0xff,
    0xff, 0xff, 0xff, 0xff, 0x60, 0x1f, 0xff, 0xfb,
    0x55, 0xbf, 0xff, 0xf1, 0x6f, 0xff, 0xc0, 0x0,
    0xc, 0xff, 0xf6, 0xaf, 0xff, 0x60, 0x0, 0x5,
    0xff, 0xfb, 0xdf, 0xff, 0x30, 0x0, 0x3, 0xff,
    0xfd, 0xef, 0xff, 0x20, 0x0, 0x8, 0xff, 0xff,
    0xff, 0xff, 0x20, 0x2, 0xcf, 0xff, 0xff, 0xff,
    0xff, 0x20, 0x6f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x4b, 0xff, 0xc4, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xf8, 0x2, 0xff, 0xff, 0xff, 0xff, 0xfd, 0x30,
    0x2, 0xff, 0xff, 0xef, 0xff, 0x90, 0x0, 0x2,
    0xff, 0xff, 0xdf, 0xff, 0x30, 0x0, 0x3, 0xff,
    0xfd, 0xaf, 0xff, 0x60, 0x0, 0x5, 0xff, 0xfb,
    0x6f, 0xff, 0xc0, 0x0, 0xb, 0xff, 0xf7, 0xe,
    0xff, 0xfb, 0x55, 0xaf, 0xff, 0xf1, 0x6, 0xff,
    0xff, 0xff, 0xff, 0xff, 0x70, 0x0, 0x7f, 0xff,
    0xff, 0xff, 0xf8, 0x0, 0x0, 0x2, 0x9d, 0xff,
    0xd9, 0x30, 0x0,

    /* U+0031 "1" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x4a, 0xf0, 0x0, 0x0, 0x39, 0xef, 0xff,
    0x0, 0x28, 0xdf, 0xff, 0xff, 0xf0, 0x6f, 0xff,
    0xff, 0xff, 0xff, 0x7, 0xff, 0xff, 0xef, 0xff,
    0xf0, 0x7f, 0xfa, 0x41, 0xff, 0xff, 0x4, 0x50,
    0x0, 0x1f, 0xff, 0xf0, 0x0, 0x0, 0x1, 0xff,
    0xff, 0x0, 0x0, 0x0, 0x1f, 0xff, 0xf0, 0x0,
    0x0, 0x1, 0xff, 0xff, 0x0, 0x0, 0x0, 0x1f,
    0xff, 0xf0, 0x0, 0x0, 0x1, 0xff, 0xff, 0x0,
    0x0, 0x0, 0x1f, 0xff, 0xf0, 0x0, 0x0, 0x1,
    0xff, 0xff, 0x0, 0x0, 0x0, 0x1f, 0xff, 0xf0,
    0x0, 0x0, 0x1, 0xff, 0xff, 0x0, 0x0, 0x0,
    0x1f, 0xff, 0xf0, 0x0, 0x0, 0x1, 0xff, 0xff,
    0x0, 0x0, 0x0, 0x1f, 0xff, 0xf0, 0x0, 0x0,
    0x1, 0xff, 0xff, 0x0, 0x0, 0x0, 0x1f, 0xff,
    0xf0,

    /* U+0032 "2" */
    0x0, 0x1, 0x7c, 0xef, 0xfc, 0x81, 0x0, 0x0,
    0x0, 0x5e, 0xff, 0xff, 0xff, 0xff, 0x50, 0x0,
    0x5, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf4, 0x0,
    0x1f, 0xff, 0xfd, 0x76, 0x9f, 0xff, 0xfc, 0x0,
    0x8f, 0xff, 0xc0, 0x0, 0x4, 0xff, 0xff, 0x10,
    0xdf, 0xff, 0x40, 0x0, 0x0, 0xdf, 0xff, 0x40,
    0xcc, 0xcc, 0x10, 0x0, 0x0, 0xcf, 0xff, 0x40,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0x10,
    0x0, 0x0, 0x0, 0x0, 0x8, 0xff, 0xfb, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x3f, 0xff, 0xf3, 0x0,
    0x0, 0x0, 0x0, 0x2, 0xef, 0xff, 0x80, 0x0,
    0x0, 0x0, 0x0, 0x2e, 0xff, 0xfb, 0x0, 0x0,
    0x0, 0x0, 0x1, 0xdf, 0xff, 0xb0, 0x0, 0x0,
    0x0, 0x0, 0x1d, 0xff, 0xfc, 0x0, 0x0, 0x0,
    0x0, 0x1, 0xdf, 0xff, 0xc0, 0x0, 0x0, 0x0,
    0x0, 0x1c, 0xff, 0xfc, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xcf, 0xff, 0xd1, 0x0, 0x0, 0x0, 0x0,
    0xc, 0xff, 0xff, 0x53, 0x33, 0x33, 0x33, 0x30,
    0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
    0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,
    0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0,

    /* U+0033 "3" */
    0x0, 0x1, 0x7c, 0xef, 0xfd, 0xa4, 0x0, 0x0,
    0x0, 0x5f, 0xff, 0xff, 0xff, 0xff, 0xc1, 0x0,
    0x5, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0x0,
    0xe, 0xff, 0xfd, 0x74, 0x5a, 0xff, 0xff, 0x60,
    0x4f, 0xff, 0xe1, 0x0, 0x0, 0xaf, 0xff, 0xa0,
    0x15, 0x55, 0x30, 0x0, 0x0, 0x5f, 0xff, 0xb0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x8f, 0xff, 0x80,
    0x0, 0x0, 0x0, 0x0, 0x17, 0xff, 0xff, 0x10,
    0x0, 0x0, 0xd, 0xff, 0xff, 0xff, 0xe4, 0x0,
    0x0, 0x0, 0xd, 0xff, 0xff, 0xfe, 0x20, 0x0,
    0x0, 0x0, 0xd, 0xff, 0xff, 0xff, 0xf5, 0x0,
    0x0, 0x0, 0x1, 0x22, 0x49, 0xff, 0xff, 0x30,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x8f, 0xff, 0xb0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x1f, 0xff, 0xf0,
    0x13, 0x33, 0x10, 0x0, 0x0, 0xf, 0xff, 0xf0,
    0x8f, 0xff, 0x90, 0x0, 0x0, 0x2f, 0xff, 0xf0,
    0x5f, 0xff, 0xe2, 0x0, 0x0, 0x9f, 0xff, 0xc0,
    0xe, 0xff, 0xfe, 0x74, 0x5b, 0xff, 0xff, 0x50,
    0x5, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0x0,
    0x0, 0x5f, 0xff, 0xff, 0xff, 0xff, 0xa0, 0x0,
    0x0, 0x1, 0x7c, 0xef, 0xfd, 0x93, 0x0, 0x0,

    /* U+0034 "4" */
    0x0, 0x0, 0x0, 0x0, 0x7, 0xff, 0xff, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x2, 0xff, 0xff, 0xf0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xcf, 0xff, 0xff,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x7f, 0xff, 0xff,
    0xf0, 0x0, 0x0, 0x0, 0x0, 0x2f, 0xff, 0xff,
    0xff, 0x0, 0x0, 0x0, 0x0, 0xc, 0xff, 0xdf,
    0xff, 0xf0, 0x0, 0x0, 0x0, 0x6, 0xff, 0xf4,
    0xff, 0xff, 0x0, 0x0, 0x0, 0x1, 0xff, 0xf8,
    0x1f, 0xff, 0xf0, 0x0, 0x0, 0x0, 0xbf, 0xfd,
    0x1, 0xff, 0xff, 0x0, 0x0, 0x0, 0x6f, 0xff,
    0x30, 0x1f, 0xff, 0xf0, 0x0, 0x0, 0x1e, 0xff,
    0x80, 0x1, 0xff, 0xff, 0x0, 0x0, 0xa, 0xff,
    0xd0, 0x0, 0x1f, 0xff, 0xf0, 0x0, 0x5, 0xff,
    0xf3, 0x0, 0x1, 0xff, 0xff, 0x0, 0x0, 0xef,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0x1f,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x70,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7,
    0x4, 0x44, 0x44, 0x44, 0x45, 0xff, 0xff, 0x44,
    0x10, 0x0, 0x0, 0x0, 0x0, 0x1f, 0xff, 0xf0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0xff, 0xff,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1f, 0xff,
    0xf0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0xff,
    0xff, 0x0, 0x0,

    /* U+0035 "5" */
    0x0, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x50,
    0x0, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0x50,
    0x0, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0x50,
    0x0, 0xef, 0xfe, 0x66, 0x66, 0x66, 0x66, 0x20,
    0x0, 0xff, 0xfb, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x2, 0xff, 0xf9, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x4, 0xff, 0xf7, 0x0, 0x10, 0x0, 0x0, 0x0,
    0x6, 0xff, 0xfa, 0xcf, 0xff, 0xd8, 0x0, 0x0,
    0x8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd2, 0x0,
    0xa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0x0,
    0x5, 0xae, 0xf7, 0x10, 0x29, 0xff, 0xff, 0x60,
    0x0, 0x0, 0x10, 0x0, 0x0, 0x9f, 0xff, 0xb0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x3f, 0xff, 0xe0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x1f, 0xff, 0xf0,
    0x1, 0x11, 0x10, 0x0, 0x0, 0x1f, 0xff, 0xf0,
    0x3f, 0xff, 0xd0, 0x0, 0x0, 0x4f, 0xff, 0xe0,
    0xf, 0xff, 0xf5, 0x0, 0x0, 0xbf, 0xff, 0xa0,
    0x9, 0xff, 0xff, 0x84, 0x4b, 0xff, 0xff, 0x30,
    0x1, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xf9, 0x0,
    0x0, 0x1b, 0xff, 0xff, 0xff, 0xff, 0x90, 0x0,
    0x0, 0x0, 0x4a, 0xef, 0xfd, 0xa3, 0x0, 0x0,

    /* U+0036 "6" */
    0x0, 0x0, 0x0, 0x17, 0xbe, 0xfd, 0x0, 0x0,
    0x0, 0x0, 0x8, 0xff, 0xff, 0xfe, 0x0, 0x0,
    0x0, 0x2, 0xdf, 0xff, 0xff, 0xfe, 0x0, 0x0,
    0x0, 0x1d, 0xff, 0xff, 0xd8, 0x64, 0x0, 0x0,
    0x0, 0xaf, 0xff, 0xe4, 0x0, 0x0, 0x0, 0x0,
    0x3, 0xff, 0xfe, 0x20, 0x0, 0x0, 0x0, 0x0,
    0xa, 0xff, 0xf5, 0x0, 0x33, 0x10, 0x0, 0x0,
    0xf, 0xff, 0xe1, 0x9f, 0xff, 0xfb, 0x30, 0x0,
    0x3f, 0xff, 0xde, 0xff, 0xff, 0xff, 0xf4, 0x0,
    0x5f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x10,
    0x7f, 0xff, 0xfd, 0x40, 0x18, 0xff, 0xff, 0x70,
    0x7f, 0xff, 0xe1, 0x0, 0x0, 0x9f, 0xff, 0xc0,
    0x7f, 0xff, 0xa0, 0x0, 0x0, 0x2f, 0xff, 0xf0,
    0x7f, 0xff, 0xa0, 0x0, 0x0, 0xf, 0xff, 0xf1,
    0x5f, 0xff, 0xb0, 0x0, 0x0, 0xf, 0xff, 0xf0,
    0x2f, 0xff, 0xf0, 0x0, 0x0, 0x3f, 0xff, 0xe0,
    0xc, 0xff, 0xf8, 0x0, 0x0, 0xbf, 0xff, 0xa0,
    0x4, 0xff, 0xff, 0x94, 0x5c, 0xff, 0xff, 0x30,
    0x0, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x0,
    0x0, 0x8, 0xff, 0xff, 0xff, 0xff, 0x80, 0x0,
    0x0, 0x0, 0x39, 0xdf, 0xfd, 0x92, 0x0, 0x0,

    /* U+0037 "7" */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd4, 0x44,
    0x44, 0x44, 0x44, 0x49, 0xff, 0xf7, 0x0, 0x0,
    0x0, 0x0, 0x0, 0xdf, 0xff, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x5f, 0xff, 0x80, 0x0, 0x0, 0x0,
    0x0, 0xc, 0xff, 0xf2, 0x0, 0x0, 0x0, 0x0,
    0x4, 0xff, 0xfa, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xbf, 0xff, 0x30, 0x0, 0x0, 0x0, 0x0, 0x3f,
    0xff, 0xc0, 0x0, 0x0, 0x0, 0x0, 0xa, 0xff,
    0xf5, 0x0, 0x0, 0x0, 0x0, 0x2, 0xff, 0xfe,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x9f, 0xff, 0x70,
    0x0, 0x0, 0x0, 0x0, 0x1f, 0xff, 0xf0, 0x0,
    0x0, 0x0, 0x0, 0x8, 0xff, 0xf9, 0x0, 0x0,
    0x0, 0x0, 0x1, 0xff, 0xff, 0x20, 0x0, 0x0,
    0x0, 0x0, 0x7f, 0xff, 0xa0, 0x0, 0x0, 0x0,
    0x0, 0xe, 0xff, 0xf3, 0x0, 0x0, 0x0, 0x0,
    0x6, 0xff, 0xfc, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xef, 0xff, 0x50, 0x0, 0x0, 0x0, 0x0, 0x5f,
    0xff, 0xe0, 0x0, 0x0, 0x0, 0x0,

    /* U+0038 "8" */
    0x0, 0x0, 0x7c, 0xef, 0xfd, 0x93, 0x0, 0x0,
    0x3, 0xef, 0xff, 0xff, 0xff, 0xf9, 0x0, 0x2,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0x0, 0x9f,
    0xff, 0xf8, 0x45, 0xcf, 0xff, 0xf2, 0xd, 0xff,
    0xf6, 0x0, 0x0, 0xef, 0xff, 0x60, 0xef, 0xff,
    0x20, 0x0, 0xa, 0xff, 0xf7, 0xc, 0xff, 0xf5,
    0x0, 0x0, 0xcf, 0xff, 0x40, 0x5f, 0xff, 0xe4,
    0x1, 0x8f, 0xff, 0xd0, 0x0, 0x9f, 0xff, 0xff,
    0xff, 0xff, 0xe2, 0x0, 0x0, 0x7f, 0xff, 0xff,
    0xff, 0xe1, 0x0, 0x0, 0x7f, 0xff, 0xff, 0xff,
    0xff, 0xd1, 0x0, 0x5f, 0xff, 0xf8, 0x45, 0xcf,
    0xff, 0xd0, 0xe, 0xff, 0xf4, 0x0, 0x0, 0xcf,
    0xff, 0x74, 0xff, 0xfd, 0x0, 0x0, 0x5, 0xff,
    0xfc, 0x6f, 0xff, 0xb0, 0x0, 0x0, 0x3f, 0xff,
    0xe5, 0xff, 0xfd, 0x0, 0x0, 0x4, 0xff, 0xfd,
    0x3f, 0xff, 0xf4, 0x0, 0x0, 0xbf, 0xff, 0xb0,
    0xdf, 0xff, 0xf7, 0x45, 0xcf, 0xff, 0xf5, 0x3,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0x0, 0x4,
    0xef, 0xff, 0xff, 0xff, 0xfa, 0x0, 0x0, 0x0,
    0x6b, 0xef, 0xfd, 0x93, 0x0, 0x0,

    /* U+0039 "9" */
    0x0, 0x0, 0x6b, 0xef, 0xeb, 0x50, 0x0, 0x0,
    0x2, 0xdf, 0xff, 0xff, 0xff, 0xc1, 0x0, 0x1,
    0xef, 0xff, 0xff, 0xff, 0xff, 0xd0, 0x0, 0xaf,
    0xff, 0xf7, 0x47, 0xff, 0xff, 0x80, 0x1f, 0xff,
    0xf4, 0x0, 0x3, 0xff, 0xff, 0x6, 0xff, 0xfc,
    0x0, 0x0, 0xb, 0xff, 0xf5, 0x8f, 0xff, 0x80,
    0x0, 0x0, 0x7f, 0xff, 0x89, 0xff, 0xf8, 0x0,
    0x0, 0x6, 0xff, 0xfa, 0x7f, 0xff, 0xa0, 0x0,
    0x0, 0x6f, 0xff, 0xa4, 0xff, 0xff, 0x20, 0x0,
    0xb, 0xff, 0xfb, 0xe, 0xff, 0xfe, 0x52, 0x3b,
    0xff, 0xff, 0xa0, 0x5f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xf9, 0x0, 0x7f, 0xff, 0xff, 0xff, 0xef,
    0xff, 0x70, 0x0, 0x3a, 0xef, 0xfb, 0x49, 0xff,
    0xf4, 0x0, 0x0, 0x0, 0x0, 0x0, 0xef, 0xff,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x8f, 0xff, 0x90,
    0x0, 0x0, 0x0, 0x1, 0x9f, 0xff, 0xf1, 0x0,
    0x0, 0x26, 0x7a, 0xff, 0xff, 0xf5, 0x0, 0x0,
    0x6, 0xff, 0xff, 0xff, 0xf6, 0x0, 0x0, 0x0,
    0x6f, 0xff, 0xff, 0xc3, 0x0, 0x0, 0x0, 0x6,
    0xfe, 0xc9, 0x30, 0x0, 0x0, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 288, .box_w = 14, .box_h = 21, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 147, .adv_w = 288, .box_w = 11, .box_h = 22, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 268, .adv_w = 288, .box_w = 16, .box_h = 21, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 436, .adv_w = 288, .box_w = 16, .box_h = 21, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 604, .adv_w = 288, .box_w = 17, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 783, .adv_w = 288, .box_w = 16, .box_h = 21, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 951, .adv_w = 288, .box_w = 16, .box_h = 21, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1119, .adv_w = 288, .box_w = 15, .box_h = 21, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1277, .adv_w = 288, .box_w = 15, .box_h = 21, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1435, .adv_w = 288, .box_w = 15, .box_h = 21, .ofs_x = 1, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 48, .range_length = 10, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
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
    .bpp = 4,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t ui_font_roboto_mono_bold_30 = {
#else
lv_font_t ui_font_roboto_mono_bold_30 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 22,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UI_FONT_ROBOTO_MONO_BOLD_30*/

