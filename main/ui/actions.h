#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif


enum {
    ACTION_MODE_CHANGED_PROPERTY_VALUE,
};
extern void action_mode_changed(lv_event_t * e);

extern void action_net_changed(lv_event_t * e);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/