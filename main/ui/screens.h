#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _groups_t {
    lv_group_t *notify_messages;
} groups_t;

extern groups_t groups;

void ui_create_groups();

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *window_data;
    lv_obj_t *window_notify;
    lv_obj_t *window_notify_mesagge;
    lv_obj_t *window_system;
    lv_obj_t *window_setting;
    lv_obj_t *window_setting_net;
    lv_obj_t *window_setting_net_change;
    lv_obj_t *window_setting_display;
    lv_obj_t *window_setting_display_change;
    lv_obj_t *window_setting_mode;
    lv_obj_t *window_setting_mode_change;
    lv_obj_t *tst;
    lv_obj_t *window_data_custom;
    lv_obj_t *obj0;
    lv_obj_t *obj0__obj16;
    lv_obj_t *obj1;
    lv_obj_t *obj1__obj19;
    lv_obj_t *obj2;
    lv_obj_t *obj2__control_left;
    lv_obj_t *obj2__control_up;
    lv_obj_t *obj2__control_down;
    lv_obj_t *obj2__obj0;
    lv_obj_t *obj3;
    lv_obj_t *obj3__control_left_1;
    lv_obj_t *obj3__control_up_1;
    lv_obj_t *obj3__control_down_1;
    lv_obj_t *obj3__obj18;
    lv_obj_t *obj4;
    lv_obj_t *obj4__control_left;
    lv_obj_t *obj4__control_up;
    lv_obj_t *obj4__control_down;
    lv_obj_t *obj4__obj0;
    lv_obj_t *obj5;
    lv_obj_t *obj5__control_left;
    lv_obj_t *obj5__control_up;
    lv_obj_t *obj5__control_down;
    lv_obj_t *obj5__obj0;
    lv_obj_t *notification_clear;
    lv_obj_t *notification_clear__obj0;
    lv_obj_t *notification_clear__obj1;
    lv_obj_t *notification_clear__obj2;
    lv_obj_t *notification_clear__obj3;
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
    lv_obj_t *obj8;
    lv_obj_t *obj8__control_left;
    lv_obj_t *obj8__control_up;
    lv_obj_t *obj8__control_down;
    lv_obj_t *obj8__obj0;
    lv_obj_t *obj9;
    lv_obj_t *obj9__control_left;
    lv_obj_t *obj9__control_up;
    lv_obj_t *obj9__control_down;
    lv_obj_t *obj9__obj0;
    lv_obj_t *obj10;
    lv_obj_t *obj10__control_left;
    lv_obj_t *obj10__control_up;
    lv_obj_t *obj10__control_down;
    lv_obj_t *obj10__obj0;
    lv_obj_t *obj11;
    lv_obj_t *obj12;
    lv_obj_t *obj12__control_left;
    lv_obj_t *obj12__control_up;
    lv_obj_t *obj12__control_down;
    lv_obj_t *obj12__obj0;
    lv_obj_t *obj13;
    lv_obj_t *obj14;
    lv_obj_t *obj14__control_left;
    lv_obj_t *obj14__control_up;
    lv_obj_t *obj14__control_down;
    lv_obj_t *obj14__obj0;
    lv_obj_t *obj15;
    lv_obj_t *obj16;
    lv_obj_t *obj16__control_left;
    lv_obj_t *obj16__control_up;
    lv_obj_t *obj16__control_down;
    lv_obj_t *obj16__obj0;
    lv_obj_t *obj17;
    lv_obj_t *obj18;
    lv_obj_t *obj18__control_left;
    lv_obj_t *obj18__control_up;
    lv_obj_t *obj18__control_down;
    lv_obj_t *obj18__obj0;
    lv_obj_t *obj19;
    lv_obj_t *obj19__obj17;
    lv_obj_t *obj20;
    lv_obj_t *obj20__control_left;
    lv_obj_t *obj20__control_up;
    lv_obj_t *obj20__control_down;
    lv_obj_t *obj20__obj0;
    lv_obj_t *test_button;
    lv_obj_t *test_button_2;
    lv_obj_t *test_button_3;
    lv_obj_t *test_button_4;
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
    lv_obj_t *swithc_orientation0;
    lv_obj_t *swithc_orientation180;
    lv_obj_t *obj34;
    lv_obj_t *obj35;
    lv_obj_t *obj36;
    lv_obj_t *obj37;
    lv_obj_t *obj38;
    lv_obj_t *obj39;
    lv_obj_t *switch_master;
    lv_obj_t *switch_slave1;
    lv_obj_t *switch_slave2;
    lv_obj_t *switch_slave3;
    lv_obj_t *obj40;
    lv_obj_t *obj41;
    lv_obj_t *obj42;
    lv_obj_t *obj43;
    lv_obj_t *obj44;
    lv_obj_t *obj45;
    lv_obj_t *obj46;
    lv_obj_t *obj47;
    lv_obj_t *obj48;
    lv_obj_t *obj49;
    lv_obj_t *obj50;
    lv_obj_t *obj51;
    lv_obj_t *obj52;
    lv_obj_t *obj53;
    lv_obj_t *obj54;
    lv_obj_t *obj55;
    lv_obj_t *obj56;
    lv_obj_t *obj57;
    lv_obj_t *obj58;
    lv_obj_t *obj59;
    lv_obj_t *obj60;
    lv_obj_t *obj61;
    lv_obj_t *obj62;
    lv_obj_t *obj63;
    lv_obj_t *obj64;
    lv_obj_t *obj65;
    lv_obj_t *obj66;
    lv_obj_t *obj67;
    lv_obj_t *obj68;
    lv_obj_t *obj69;
    lv_obj_t *obj70;
    lv_obj_t *obj71;
    lv_obj_t *message_list;
    lv_obj_t *obj72;
    lv_obj_t *obj73;
    lv_obj_t *obj74;
    lv_obj_t *obj75;
    lv_obj_t *obj76;
    lv_obj_t *obj77;
    lv_obj_t *obj78;
    lv_obj_t *system_about;
    lv_obj_t *obj79;
    lv_obj_t *obj80;
    lv_obj_t *obj81;
    lv_obj_t *obj82;
    lv_obj_t *obj83;
    lv_obj_t *obj84;
    lv_obj_t *obj85;
    lv_obj_t *obj86;
    lv_obj_t *obj87;
    lv_obj_t *obj88;
    lv_obj_t *obj89;
    lv_obj_t *obj90;
    lv_obj_t *obj91;
    lv_obj_t *obj92;
    lv_obj_t *obj93;
    lv_obj_t *obj94;
    lv_obj_t *obj95;
    lv_obj_t *obj96;
    lv_obj_t *obj97;
    lv_obj_t *obj98;
    lv_obj_t *obj99;
    lv_obj_t *obj100;
    lv_obj_t *obj101;
    lv_obj_t *obj102;
    lv_obj_t *obj103;
    lv_obj_t *obj104;
    lv_obj_t *obj105;
    lv_obj_t *obj106;
    lv_obj_t *obj107;
    lv_obj_t *obj108;
    lv_obj_t *obj109;
    lv_obj_t *obj110;
    lv_obj_t *data_data;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_WINDOW_DATA = 2,
    SCREEN_ID_WINDOW_NOTIFY = 3,
    SCREEN_ID_WINDOW_NOTIFY_MESAGGE = 4,
    SCREEN_ID_WINDOW_SYSTEM = 5,
    SCREEN_ID_WINDOW_SETTING = 6,
    SCREEN_ID_WINDOW_SETTING_NET = 7,
    SCREEN_ID_WINDOW_SETTING_NET_CHANGE = 8,
    SCREEN_ID_WINDOW_SETTING_DISPLAY = 9,
    SCREEN_ID_WINDOW_SETTING_DISPLAY_CHANGE = 10,
    SCREEN_ID_WINDOW_SETTING_MODE = 11,
    SCREEN_ID_WINDOW_SETTING_MODE_CHANGE = 12,
    SCREEN_ID_TST = 13,
    SCREEN_ID_WINDOW_DATA_CUSTOM = 14,
};

void create_screen_main();
void tick_screen_main();

void create_screen_window_data();
void tick_screen_window_data();

void create_screen_window_notify();
void tick_screen_window_notify();

void create_screen_window_notify_mesagge();
void tick_screen_window_notify_mesagge();

void create_screen_window_system();
void tick_screen_window_system();

void create_screen_window_setting();
void tick_screen_window_setting();

void create_screen_window_setting_net();
void tick_screen_window_setting_net();

void create_screen_window_setting_net_change();
void tick_screen_window_setting_net_change();

void create_screen_window_setting_display();
void tick_screen_window_setting_display();

void create_screen_window_setting_display_change();
void tick_screen_window_setting_display_change();

void create_screen_window_setting_mode();
void tick_screen_window_setting_mode();

void create_screen_window_setting_mode_change();
void tick_screen_window_setting_mode_change();

void create_screen_tst();
void tick_screen_tst();

void create_screen_window_data_custom();
void tick_screen_window_data_custom();

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

void create_user_widget_spacer(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_spacer(void *flowState, int startWidgetIndex);

void create_user_widget_data_custom(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_data_custom(void *flowState, int startWidgetIndex);

void create_user_widget_controls_right(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_controls_right(void *flowState, int startWidgetIndex);

void create_user_widget_controls_left(lv_obj_t *parent_obj, void *flowState, int startWidgetIndex);
void tick_user_widget_controls_left(void *flowState, int startWidgetIndex);

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/