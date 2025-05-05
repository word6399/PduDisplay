#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *window_data;
    lv_obj_t *window_setting;
    lv_obj_t *window_notify;
    lv_obj_t *window_system;
    lv_obj_t *obj0;
    lv_obj_t *obj0__control_left;
    lv_obj_t *obj0__control_up;
    lv_obj_t *obj0__control_down;
    lv_obj_t *obj0__obj0;
    lv_obj_t *obj1;
    lv_obj_t *obj1__obj15;
    lv_obj_t *obj2;
    lv_obj_t *obj2__obj15;
    lv_obj_t *obj3;
    lv_obj_t *obj3__obj15;
    lv_obj_t *obj4;
    lv_obj_t *obj4__control_left;
    lv_obj_t *obj4__control_up;
    lv_obj_t *obj4__control_down;
    lv_obj_t *obj4__obj0;
    lv_obj_t *change_ip1;
    lv_obj_t *change_ip1__obj1;
    lv_obj_t *change_ip1__obj2;
    lv_obj_t *change_ip1__obj3;
    lv_obj_t *change_ip1__obj4;
    lv_obj_t *change_orientation1;
    lv_obj_t *change_orientation1__obj5;
    lv_obj_t *change_orientation1__obj6;
    lv_obj_t *change_orientation1__obj7;
    lv_obj_t *change_orientation1__obj8;
    lv_obj_t *change_mode1;
    lv_obj_t *change_mode1__mode_slave;
    lv_obj_t *change_mode1__mode_slave__slave_roller;
    lv_obj_t *change_mode1__mode_slave__obj0;
    lv_obj_t *change_mode1__mode_slave__obj1;
    lv_obj_t *change_mode1__obj9;
    lv_obj_t *change_mode1__obj10;
    lv_obj_t *change_mode1__obj11;
    lv_obj_t *change_mode1__obj12;
    lv_obj_t *obj5;
    lv_obj_t *obj5__control_left;
    lv_obj_t *obj5__control_up;
    lv_obj_t *obj5__control_down;
    lv_obj_t *obj5__obj0;
    lv_obj_t *notification1;
    lv_obj_t *notification1__noty_clear1;
    lv_obj_t *notification1__noty_clear1__obj0;
    lv_obj_t *notification1__noty_clear1__obj1;
    lv_obj_t *notification1__noty_clear1__obj2;
    lv_obj_t *notification1__noty_clear1__obj3;
    lv_obj_t *notification1__obj13;
    lv_obj_t *notification1__obj14;
    lv_obj_t *obj6;
    lv_obj_t *obj6__control_left;
    lv_obj_t *obj6__control_up;
    lv_obj_t *obj6__control_down;
    lv_obj_t *obj6__obj0;
    lv_obj_t *obj7;
    lv_obj_t *obj7__control_left;
    lv_obj_t *obj7__control_up;
    lv_obj_t *obj7__control_down;
    lv_obj_t *obj7__obj0;
    lv_obj_t *test_button;
    lv_obj_t *test_button_2;
    lv_obj_t *test_button_3;
    lv_obj_t *test_button_4;
    lv_obj_t *obj8;
    lv_obj_t *obj9;
    lv_obj_t *obj10;
    lv_obj_t *obj11;
    lv_obj_t *obj12;
    lv_obj_t *obj13;
    lv_obj_t *panel_lan;
    lv_obj_t *panel_display;
    lv_obj_t *panel_mode;
    lv_obj_t *obj14;
    lv_obj_t *obj15;
    lv_obj_t *obj16;
    lv_obj_t *obj17;
    lv_obj_t *obj18;
    lv_obj_t *obj19;
    lv_obj_t *obj20;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_WINDOW_DATA = 2,
    SCREEN_ID_WINDOW_SETTING = 3,
    SCREEN_ID_WINDOW_NOTIFY = 4,
    SCREEN_ID_WINDOW_SYSTEM = 5,
};

void create_screen_main();
void tick_screen_main();

void create_screen_window_data();
void tick_screen_window_data();

void create_screen_window_setting();
void tick_screen_window_setting();

void create_screen_window_notify();
void tick_screen_window_notify();

void create_screen_window_system();
void tick_screen_window_system();

void create_user_widget_controls(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_controls(void *flowState, int startWidgetIndex);

void create_user_widget_change_ip(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_change_ip(void *flowState, int startWidgetIndex);

void create_user_widget_change_orientation(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_change_orientation(void *flowState, int startWidgetIndex);

void create_user_widget_change_mode(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_change_mode(void *flowState, int startWidgetIndex);

void create_user_widget_change_mode_slave(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_change_mode_slave(void *flowState, int startWidgetIndex);

void create_user_widget_notification(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_notification(void *flowState, int startWidgetIndex);

void create_user_widget_notification_clear(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_notification_clear(void *flowState, int startWidgetIndex);

void create_user_widget_data_default(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_data_default(void *flowState, int startWidgetIndex);

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/