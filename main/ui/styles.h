#ifndef EEZ_LVGL_UI_STYLES_H
#define EEZ_LVGL_UI_STYLES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Style: label_font
lv_style_t *get_style_label_font_MAIN_DEFAULT();
void add_style_label_font(lv_obj_t *obj);
void remove_style_label_font(lv_obj_t *obj);

// Style: setting buttons
lv_style_t *get_style_setting_buttons_MAIN_DEFAULT();
void add_style_setting_buttons(lv_obj_t *obj);
void remove_style_setting_buttons(lv_obj_t *obj);

// Style: setting_panel
void add_style_setting_panel(lv_obj_t *obj);
void remove_style_setting_panel(lv_obj_t *obj);



#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_STYLES_H*/