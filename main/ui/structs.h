#ifndef EEZ_LVGL_UI_STRUCTS_H
#define EEZ_LVGL_UI_STRUCTS_H

#include "eez-flow.h"


#if defined(EEZ_FOR_LVGL)

#include <stdint.h>
#include <stdbool.h>

#include "vars.h"

using namespace eez;

typedef struct
{
    const char *name;
    const lv_img_dsc_t *icon;
    lv_color_t bg_color;
    lv_color_t text_color;
    const lv_font_t *font;
} dsgnMainButton_def;





#endif

#endif /*EEZ_LVGL_UI_STRUCTS_H*/
