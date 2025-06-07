/*
 * SPDX-FileCopyrightText: 2021-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

 #include <Arduino.h>
 #include "ui/ui.h"


#include "Display.h"
#include "About.h"


#include "DataList.h"
#include "ModbusControls.h"

#include "Conf.h"

static const char *TAG = "example";

// Using SPI2 in the example




void Task1code( void * pvParameters );
TaskHandle_t Task1;

#include "vars.h"

esp_lcd_panel_handle_t panel_handle = NULL;
lv_display_t *display;

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
        esp_lcd_panel_mirror(disp.panel_handle, false, false);
        lv_display_set_rotation(disp.display, LV_DISP_ROTATION_0);

        

        if (FileFS.exists("/display.ini")) {
            //FileFS
            FileFS.remove("/display.ini");
        } else {
            
        }
    } else {
        esp_lcd_panel_mirror(disp.panel_handle, true, true);
        lv_display_set_rotation(disp.display, LV_DISPLAY_ROTATION_90);
        // lv_area_t area ={
        //     .x1 = 0,
        //     .y1 = 40,
        //     .x2 = 240,        
        //     .y2 = 280
        // };

        // lv_display_rotate_area(disp.display, &area);

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

    //lv_style_set_bg_opa(btn, 0);    
}
void addElement(lv_obj_t * parent,const char* text)
{
    lv_obj_t * btn = lv_button_create( parent);
    lv_obj_set_height(btn, 40);
    lv_obj_set_width (btn, LV_PCT(100));    
    lv_obj_set_style_bg_opa(btn, 0, 0);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_t *label = lv_label_create( btn );
    lv_obj_set_align(label, LV_ALIGN_LEFT_MID);
    lv_obj_set_style_text_font(label, &ui_font_nunito_bold_18, 0);
    lv_label_set_text(label, text);      
}


void initAbout()
{
    //objects.system_about;
    lv_obj_clean(objects.system_about);


    

    String data;
    data = "MFR: " + about.companu();
    addElement(objects.system_about, data.c_str()); 
    
    data = "FW Main: " + about.versionStr();
    addElement(objects.system_about, data.c_str());
    
    data = "FW Display: " + about.versionStr();
    addElement(objects.system_about, data.c_str());

    data = "Date: " + about.date();
    addElement(objects.system_about, data.c_str());

    String str(about.serialNumber()); 
    while (str.length() < 6) {
        str = "0" + str;
    }    
    data = "SN: " + str.substring(0, 3) + " " + str.substring(3);;
    addElement(objects.system_about, data.c_str());
}

void addDataRelay(lv_obj_t * parent, const char* text, float *value)
{
    lv_obj_t * btn = lv_button_create( parent );
    lv_obj_set_size (btn, LV_PCT(100), 34);    
    
    lv_obj_set_style_bg_opa(btn, 0, 0);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_CLICKABLE);

    lv_obj_t *label = lv_label_create( btn );
    lv_obj_set_style_text_font(label, &ui_font_nunito_bold_25, 0);
    lv_obj_set_align(label, LV_ALIGN_LEFT_MID);
    lv_label_set_text(label, text);     

    lv_obj_t *swith = lv_switch_create(btn);
    lv_obj_clear_flag(swith, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_state(swith, LV_STATE_CHECKED);
    lv_obj_set_align(swith, LV_ALIGN_RIGHT_MID);
    lv_obj_set_size(swith, 50, 25);

}

typedef struct 
{
    float *value;
    lv_obj_t *label;
    int prec;
} t_watch;

std::vector<t_watch> wath;


void addDataDisplay(lv_obj_t * parent, const char* text, float *value, const char * meas, int prec =0)
{
    lv_obj_t *obj = lv_obj_create( parent );
    lv_obj_set_style_bg_opa(obj, 0, 0);
    lv_obj_set_style_pad_all(obj, 0, 0);
    lv_obj_set_style_border_width(obj, 0, 0);
    lv_obj_set_size (obj, LV_PCT(100), 68); 

    lv_obj_t *label_name = lv_label_create( obj );
    lv_label_set_text(label_name, text);
    lv_obj_set_style_text_font(label_name, &ui_font_nunito_bold_18, 0);
    lv_obj_set_align(label_name, LV_ALIGN_TOP_MID);
    {
        lv_obj_t *container = lv_obj_create( obj );
        lv_obj_set_style_bg_opa(container, 0, 0);
        lv_obj_set_style_pad_all(container, 0, 0);
        lv_obj_set_style_pad_top(container, 20, 0);
        lv_obj_set_size(container, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_set_style_border_width(container, 0, 0);
        lv_obj_set_layout(container, LV_LAYOUT_FLEX);
        lv_obj_set_align(container, LV_ALIGN_TOP_MID);

        lv_obj_t *label_value = lv_label_create( container );
        lv_obj_set_style_text_font(label_value, &ui_font_nunito_bold_46, 0);
        lv_label_set_text_fmt(label_value, String(*value, prec).c_str());

        lv_obj_t *label_meas = lv_label_create(container);
        lv_obj_set_style_text_font(label_meas, &ui_font_nunito_bold_18, 0);
        lv_label_set_text_fmt(label_meas, "\n%s", meas);

        t_watch node;
        node.label = label_value;
        node.value = value;
        node.prec = prec;

        wath.push_back(node);
    }
    
}

void initData()
{
    lv_obj_clean(objects.data_data); // Нужно потом раскоментировать
    float tmp = 219;

    auto list = dataList.displayData();

    for(auto node: *list){
        float *ptr = &dataList.getById(node.id)->dataF;
        if(node.input)
            addDataRelay(objects.data_data, node.name.c_str(), ptr);
        else 
            addDataDisplay(objects.data_data, node.name.c_str(), ptr, node.meas.c_str(), node.pric);
    }
    
    // addDataRelay(objects.data_data, "L1 Выход", &tmp);
    // dataList.getById(5)->dataF = 5;
    // addDataDisplay(objects.data_data,"Напряжение", &dataList.getById(5)->dataF , "В");
    // addDataDisplay(objects.data_data,"Ток", &dataList.getById(1)->dataF , "А", 1);
    // addDataDisplay(objects.data_data,"Мощность", &dataList.getById(8)->dataF , "кВт", 2);

    // addDataRelay(objects.data_data, "L2 Выход", &tmp);
    // addDataDisplay(objects.data_data,"Напряжение", &dataList.getById(6)->dataF , "В");
    // addDataDisplay(objects.data_data,"Ток", &dataList.getById(2)->dataF , "А", 1);
    // addDataDisplay(objects.data_data,"Мощность", &dataList.getById(9)->dataF , "кВт", 2);
    
}


void setup()
{
    Serial.begin(115200);

    dataList.init();
    conf.init();

    disp.init();
    ui_init();

    if (FileFS.exists("/display.ini")) {
        set_var_setting_orientation(1);
    } else {
        set_var_setting_orientation(0);
    }

    gpio_set_level((gpio_num_t)PIN_NUM_BK_LIGHT, LCD_BK_LIGHT_ON_LEVEL);

    modBus.init();
    initAbout();
    initData();
    

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

void update_wath()
{
    for(auto val: wath){
        
        lv_label_set_text(val.label, String(*val.value, val.prec).c_str());
    }
    //
}
void loop()
{
    ui_tick();
    lv_timer_handler();
    lv_tick_inc(1);

    update_wath();

    // set_var_volt1(dataList.getById(5)->dataF);
    // set_var_volt2(dataList.getById(6)->dataF);
    // set_var_volt3(dataList.getById(7)->dataF);

    // set_var_cur1(dataList.getById(1)->dataF);
    // set_var_cur2(dataList.getById(2)->dataF);
    // set_var_cur3(dataList.getById(3)->dataF);

    // set_var_pow1(dataList.getById(8)->dataF);
    // set_var_pow2(dataList.getById(9)->dataF);
    // set_var_pow3(dataList.getById(10)->dataF);

    // set_var_cur_all(dataList.getById(4)->dataF);
    // set_var_pow_all(dataList.getById(11)->dataF);
    // 
    counter++;
    // if(counter >1000){
    //     counter =0;
    //     Serial.println("update: " + String(millis()));
    // }
    // delay(1);
}
