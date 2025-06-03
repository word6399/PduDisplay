/*
 * SPDX-FileCopyrightText: 2021-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <Arduino.h>

#include "ui/ui.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/lock.h>
#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"

#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_err.h"
#include "esp_log.h"
#include "lvgl.h"

#include "Display.h"
 


 

static const char *TAG = "example";

// Using SPI2 in the example


#include "DataList.h"
#include "ModbusControls.h"

void Task1code( void * pvParameters );
TaskHandle_t Task1;

#include "vars.h"


//lv_display_t *display;

//ArrayOfdata_typeValue
#include "structs.h"

void action_tst_act(lv_event_t *e) {
    //ArrayOfdata_typeValue;//[0].
}


char setting_net_ip[100] = { 0 };

const char *get_var_setting_net_ip() {
    return setting_net_ip;
}

void set_var_setting_net_ip(const char *value) {
    strncpy(setting_net_ip, value, sizeof(setting_net_ip) / sizeof(char));
    setting_net_ip[sizeof(setting_net_ip) / sizeof(char) - 1] = 0;
}

char setting_net_mask[100] = { 0 };

const char *get_var_setting_net_mask() {
    return setting_net_mask;
}

void set_var_setting_net_mask(const char *value) {
    strncpy(setting_net_mask, value, sizeof(setting_net_mask) / sizeof(char));
    setting_net_mask[sizeof(setting_net_mask) / sizeof(char) - 1] = 0;
}

char setting_net_gw[100] = { 0 };

const char *get_var_setting_net_gw() {
    return setting_net_gw;
}

void set_var_setting_net_gw(const char *value) {
    strncpy(setting_net_gw, value, sizeof(setting_net_gw) / sizeof(char));
    setting_net_gw[sizeof(setting_net_gw) / sizeof(char) - 1] = 0;
}

int32_t setting_mode;

int32_t get_var_setting_mode() {
    return setting_mode;
}

void set_var_setting_mode(int32_t value) {
    setting_mode = value;
}

int32_t setting_orientation;

int32_t get_var_setting_orientation() {
    return setting_orientation;
}

void set_var_setting_orientation(int32_t value) {
    setting_orientation = value;

    if(setting_orientation == 0){
        esp_lcd_panel_mirror(display.panel_handle, false, false);
        lv_display_set_rotation(display.display, LV_DISP_ROTATION_0);

        

        if (FileFS.exists("/display.ini")) {
            //FileFS
            FileFS.remove("/display.ini");
        } else {
            
        }
    } else {
        esp_lcd_panel_mirror(display.panel_handle, true, true);
        //lv_display_set_rotation(display.display, LV_DISP_ROTATION_180);

        if (FileFS.exists("/display.ini")) {
            //FileFS
        } else {
            File file =FileFS.open("/display.ini", FILE_WRITE);
            uint8_t buf[] = "123";
            file.write(buf,1);
            file.close();
        }

    }

    set_var_setting_orientation_not(!value);

    Serial.println("go to rotate " + String(value));

    
}

int32_t setting_orientation_not;

int32_t get_var_setting_orientation_not() {
    return setting_orientation_not;
}

void set_var_setting_orientation_not(int32_t value) {
    Serial.println("go to rotate not " + String(value));
    setting_orientation_not = value;

    // if(setting_orientation != 0){
    //     esp_lcd_panel_mirror(panel_handle, false, false);
    //     lv_display_set_rotation(display, LV_DISP_ROTATION_0);

        

    //     if (FileFS.exists("/display.ini")) {
    //         //FileFS
    //         FileFS.remove("/display.ini");
    //     } else {
            
    //     }
    // } else {
    //     esp_lcd_panel_mirror(panel_handle, true, true);
    //     lv_display_set_rotation(display, LV_DISP_ROTATION_180);

    //     if (FileFS.exists("/display.ini")) {
    //         //FileFS
    //     } else {
    //         File file =FileFS.open("/display.ini", FILE_WRITE);
    //         uint8_t buf[] = "123";
    //         file.write(buf,1);
    //         file.close();
    //     }

    // }
}


char notify_message[100] = { 0 };

const char *get_var_notify_message() {
    return notify_message;
}

void set_var_notify_message(const char *value) {
    strncpy(notify_message, value, sizeof(notify_message) / sizeof(char));
    notify_message[sizeof(notify_message) / sizeof(char) - 1] = 0;
}

#include "ui/fonts.h"
#include "screens.h"
extern objects_t objects;

void action_add_message(lv_event_t *e) {
    //eez_flow_init_object_names();

    lv_obj_t * btn = lv_button_create( objects.message_list );
    lv_obj_t *label = lv_label_create( btn );
    //lv_obj_get_style_text_font(label, )
    lv_obj_set_style_text_font(label, &ui_font_nunito_bold_18, 0);

    lv_obj_set_height(btn, 40);
    lv_obj_set_width (btn, LV_PCT(100));    
    lv_obj_set_style_bg_opa(btn, 0, 0);
    lv_color_t bg_color;
    bg_color.red    = 0x15;
    bg_color.green  = 0x14;
    bg_color.blue   = 0x19;
    lv_obj_set_style_border_color(btn, bg_color, 0);
    lv_obj_set_style_border_width(btn, 2, 0);
    
}





// LVGL library is not thread-safe, this example will call LVGL APIs from different tasks, so use a mutex to protect it
static _lock_t lvgl_api_lock;
extern void example_lvgl_demo_ui(lv_disp_t *disp);







void setup()
{
    
    Serial.begin(115200);

    dataList.init();
    
 

    display.init();
    

    
    // Lock the mutex due to the LVGL APIs are not thread-safe
    //_lock_acquire(&lvgl_api_lock);
    Serial.println("after");
    //CONFIG_LV_THEME_DEFAULT_DARK;

    if (FileFS.exists("/display.ini")) {
        set_var_setting_orientation(1);
    } else {
        set_var_setting_orientation(0);
    }

    

    ui_init();
    //example_lvgl_demo_ui(display);
    //_lock_release(&lvgl_api_lock);

    

    gpio_set_level((gpio_num_t)EXAMPLE_PIN_NUM_BK_LIGHT, EXAMPLE_LCD_BK_LIGHT_ON_LEVEL);

    modBus.init();


    set_var_current_date(__DATE__);

    
    

    xTaskCreatePinnedToCore(
        Task1code,   // Функция задачи. 
        "Task1",     // Ее имя. 
        16*1024,       // Размер стека функции 
        NULL,        // Параметры 
        1,           // Приоритет 
        &Task1,      // Дескриптор задачи для отслеживания 
        0);          // Указываем пин для данного ядра  

    Serial.println("start [rogram]");
}

void Task1code( void * pvParameters ){
    //
    Serial.print("Task1 running on core ");
    Serial.println( xPortGetCoreID() ); 
  
    while(1){  
      modBus.tick();  
    }
    
  }

int counter =0;
void loop()
{
    ui_tick();
    lv_timer_handler();
    lv_tick_inc(1);

    set_var_volt1(dataList.getById(5)->dataF);
    set_var_volt2(dataList.getById(6)->dataF);
    set_var_volt3(dataList.getById(7)->dataF);

    set_var_cur1(dataList.getById(1)->dataF);
    set_var_cur2(dataList.getById(2)->dataF);
    set_var_cur3(dataList.getById(3)->dataF);

    set_var_pow1(dataList.getById(8)->dataF);
    set_var_pow2(dataList.getById(9)->dataF);
    set_var_pow3(dataList.getById(10)->dataF);

    set_var_cur_all(dataList.getById(4)->dataF);
    set_var_pow_all(dataList.getById(11)->dataF);
    // 
    // counter++;
    // if(counter >1000){
    //     counter =0;
    //     Serial.println("update: " + String(millis()));
    // }
    // delay(1);
}
