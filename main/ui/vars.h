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
    FLOW_GLOBAL_VARIABLE_COLOR_SETTING = 0
};

// Native global variables

extern const char *get_var_setting_net_ip();
extern void set_var_setting_net_ip(const char *value);
extern const char *get_var_setting_net_mask();
extern void set_var_setting_net_mask(const char *value);
extern const char *get_var_setting_net_gw();
extern void set_var_setting_net_gw(const char *value);
extern const char *get_var_setting_mode();
extern void set_var_setting_mode(const char *value);
extern int32_t get_var_notify_count();
extern void set_var_notify_count(int32_t value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/