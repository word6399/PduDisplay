#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *window_data;
    lv_obj_t *window_notify;
    lv_obj_t *window_system;
    lv_obj_t *window_setting;
    lv_obj_t *window_setting_net;
    lv_obj_t *window_setting_display;
    lv_obj_t *window_setting_mode;
    lv_obj_t *window_setting_old;
    lv_obj_t *obj0;
    lv_obj_t *obj0__control_left;
    lv_obj_t *obj0__control_up;
    lv_obj_t *obj0__control_down;
    lv_obj_t *obj0__obj0;
    lv_obj_t *obj1;
    lv_obj_t *obj1__obj16;
    lv_obj_t *obj2;
    lv_obj_t *obj2__obj15;
    lv_obj_t *obj3;
    lv_obj_t *obj3__obj15;
    lv_obj_t *obj4;
    lv_obj_t *obj4__control_left;
    lv_obj_t *obj4__control_up;
    lv_obj_t *obj4__control_down;
    lv_obj_t *obj4__obj0;
    lv_obj_t *notification1;
    lv_obj_t *notification1__noty_clear1;
    lv_obj_t *notification1__noty_clear1__obj0;
    lv_obj_t *notification1__noty_clear1__obj1;
    lv_obj_t *notification1__noty_clear1__obj2;
    lv_obj_t *notification1__noty_clear1__obj3;
    lv_obj_t *notification1__obj13;
    lv_obj_t *notification1__obj14;
    lv_obj_t *obj5;
    lv_obj_t *obj5__control_left;
    lv_obj_t *obj5__control_up;
    lv_obj_t *obj5__control_down;
    lv_obj_t *obj5__obj0;
    lv_obj_t *obj6;
    lv_obj_t *obj6__control_left;
    lv_obj_t *obj6__control_up;
    lv_obj_t *obj6__control_down;
    lv_obj_t *obj6__obj0;
    lv_obj_t *obj7;
    lv_obj_t *obj7__obj16;
    lv_obj_t *obj8;
    lv_obj_t *obj8__control_left;
    lv_obj_t *obj8__control_up;
    lv_obj_t *obj8__control_down;
    lv_obj_t *obj8__obj0;
    lv_obj_t *obj9;
    lv_obj_t *obj9__obj16;
    lv_obj_t *obj10;
    lv_obj_t *obj10__control_left;
    lv_obj_t *obj10__control_up;
    lv_obj_t *obj10__control_down;
    lv_obj_t *obj10__obj0;
    lv_obj_t *obj11;
    lv_obj_t *obj11__obj16;
    lv_obj_t *obj12;
    lv_obj_t *obj12__control_left;
    lv_obj_t *obj12__control_up;
    lv_obj_t *obj12__control_down;
    lv_obj_t *obj12__obj0;
    lv_obj_t *obj13;
    lv_obj_t *obj13__obj16;
    lv_obj_t *obj14;
    lv_obj_t *obj14__control_left;
    lv_obj_t *obj14__control_up;
    lv_obj_t *obj14__control_down;
    lv_obj_t *obj14__obj0;
    lv_obj_t *change_ip1_1;
    lv_obj_t *change_ip1_1__obj1;
    lv_obj_t *change_ip1_1__obj2;
    lv_obj_t *change_ip1_1__obj3;
    lv_obj_t *change_ip1_1__obj4;
    lv_obj_t *change_orientation1_1;
    lv_obj_t *change_orientation1_1__obj5;
    lv_obj_t *change_orientation1_1__obj6;
    lv_obj_t *change_orientation1_1__obj7;
    lv_obj_t *change_orientation1_1__obj8;
    lv_obj_t *change_mode1_1;
    lv_obj_t *change_mode1_1__mode_slave;
    lv_obj_t *change_mode1_1__mode_slave__slave_roller;
    lv_obj_t *change_mode1_1__mode_slave__obj0;
    lv_obj_t *change_mode1_1__mode_slave__obj1;
    lv_obj_t *change_mode1_1__obj9;
    lv_obj_t *change_mode1_1__obj10;
    lv_obj_t *change_mode1_1__obj11;
    lv_obj_t *change_mode1_1__obj12;
    lv_obj_t *obj15;
    lv_obj_t *obj15__control_left;
    lv_obj_t *obj15__control_up;
    lv_obj_t *obj15__control_down;
    lv_obj_t *obj15__obj0;
    lv_obj_t *test_button;
    lv_obj_t *test_button_2;
    lv_obj_t *test_button_3;
    lv_obj_t *test_button_4;
    lv_obj_t *obj16;
    lv_obj_t *obj17;
    lv_obj_t *obj18;
    lv_obj_t *obj19;
    lv_obj_t *obj20;
    lv_obj_t *obj21;
    lv_obj_t *obj22;
    lv_obj_t *obj23;
    lv_obj_t *obj24;
    lv_obj_t *obj25;
    lv_obj_t *obj26;
    lv_obj_t *obj27;
    lv_obj_t *obj28;
    lv_obj_t *obj29;
    lv_obj_t *obj30;
    lv_obj_t *obj31;
    lv_obj_t *obj32;
    lv_obj_t *obj33;
    lv_obj_t *obj34;
    lv_obj_t *obj35;
    lv_obj_t *obj36;
    lv_obj_t *obj37;
    lv_obj_t *obj38;
    lv_obj_t *obj39;
    lv_obj_t *obj40;
    lv_obj_t *panel_lan_1;
    lv_obj_t *panel_display_1;
    lv_obj_t *panel_mode_1;
    lv_obj_t *obj41;
    lv_obj_t *obj42;
    lv_obj_t *obj43;
    lv_obj_t *obj44;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_WINDOW_DATA = 2,
    SCREEN_ID_WINDOW_NOTIFY = 3,
    SCREEN_ID_WINDOW_SYSTEM = 4,
    SCREEN_ID_WINDOW_SETTING = 5,
    SCREEN_ID_WINDOW_SETTING_NET = 6,
    SCREEN_ID_WINDOW_SETTING_DISPLAY = 7,
    SCREEN_ID_WINDOW_SETTING_MODE = 8,
    SCREEN_ID_WINDOW_SETTING_OLD = 9,
};

void create_screen_main();
void delete_screen_main();
void tick_screen_main();

void create_screen_window_data();
void delete_screen_window_data();
void tick_screen_window_data();

void create_screen_window_notify();
void delete_screen_window_notify();
void tick_screen_window_notify();

void create_screen_window_system();
void delete_screen_window_system();
void tick_screen_window_system();

void create_screen_window_setting();
void delete_screen_window_setting();
void tick_screen_window_setting();

void create_screen_window_setting_net();
void delete_screen_window_setting_net();
void tick_screen_window_setting_net();

void create_screen_window_setting_display();
void delete_screen_window_setting_display();
void tick_screen_window_setting_display();

void create_screen_window_setting_mode();
void delete_screen_window_setting_mode();
void tick_screen_window_setting_mode();

void create_screen_window_setting_old();
void delete_screen_window_setting_old();
void tick_screen_window_setting_old();

void create_user_widget_controls_bottom(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_controls_bottom(void *flowState, int startWidgetIndex);

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

void create_user_widget_controls_top(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_controls_top(void *flowState, int startWidgetIndex);

void create_screen_by_id(enum ScreensEnum screenId);
void delete_screen_by_id(enum ScreensEnum screenId);
void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/