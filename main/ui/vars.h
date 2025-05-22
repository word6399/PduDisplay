#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations



// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_COLOR_SETTING = 0,
    FLOW_GLOBAL_VARIABLE_GROUP_TEST = 1,
    FLOW_GLOBAL_VARIABLE_DATA = 2
};

// Native global variables

extern const char *get_var_setting_net_ip();
extern void set_var_setting_net_ip(const char *value);
extern const char *get_var_setting_net_mask();
extern void set_var_setting_net_mask(const char *value);
extern const char *get_var_setting_net_gw();
extern void set_var_setting_net_gw(const char *value);
extern int32_t get_var_setting_mode();
extern void set_var_setting_mode(int32_t value);
extern int32_t get_var_notify_count();
extern void set_var_notify_count(int32_t value);
extern bool get_var_net_dhcp();
extern void set_var_net_dhcp(bool value);
extern int32_t get_var_set_net_mode();
extern void set_var_set_net_mode(int32_t value);
extern int32_t get_var_net_mode();
extern void set_var_net_mode(int32_t value);
extern int32_t get_var_setting_orientation();
extern void set_var_setting_orientation(int32_t value);
extern const char *get_var_notify_message();
extern void set_var_notify_message(const char *value);
extern float get_var_volt1();
extern void set_var_volt1(float value);
extern float get_var_volt2();
extern void set_var_volt2(float value);
extern float get_var_volt3();
extern void set_var_volt3(float value);
extern float get_var_cur1();
extern void set_var_cur1(float value);
extern float get_var_cur2();
extern void set_var_cur2(float value);
extern float get_var_cur3();
extern void set_var_cur3(float value);
extern float get_var_pow1();
extern void set_var_pow1(float value);
extern float get_var_pow2();
extern void set_var_pow2(float value);
extern float get_var_pow3();
extern void set_var_pow3(float value);
extern float get_var_cur_all();
extern void set_var_cur_all(float value);
extern float get_var_pow_all();
extern void set_var_pow_all(float value);
extern const char *get_var_current_date();
extern void set_var_current_date(const char *value);
extern int32_t get_var_setting_orientation_not();
extern void set_var_setting_orientation_not(int32_t value);
extern bool get_var_set_net_dhcp();
extern void set_var_set_net_dhcp(bool value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/