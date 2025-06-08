#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_img_dsc_t img_control_down;
extern const lv_img_dsc_t img_control_left;
extern const lv_img_dsc_t img_control_up;
extern const lv_img_dsc_t img_data;
extern const lv_img_dsc_t img_notation;
extern const lv_img_dsc_t img_setting;
extern const lv_img_dsc_t img_system;
extern const lv_img_dsc_t img_data_power;
extern const lv_img_dsc_t img_logo;
extern const lv_img_dsc_t img_control_right;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[10];


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/