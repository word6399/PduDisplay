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
    
}

std::vector<lv_obj_t *> rotate_list;

void rotateWin(uint8_t rot){
    // 0 - 0 grad
    // 1 - 180 grad
    // 2 - 90 grad
    // 3 - 270 grad

    int32_t rotate = 0;
    int32_t shift = 0;
    if(rot>1){
        rotate = 900;
        shift = 240;
        
        Serial.println("Rotate 90");
        set_var_control_rot2( 2700 );
    } else {
        rotate = 0;
        shift = 0;
        Serial.println("Rotate 0");
        set_var_control_rot2( 0 );
    }

    if(rot%2){
        disp.rotate180(0); // 0
        Serial.println("Rotate 0");
    } else {
        disp.rotate180(1); // 180
        Serial.println("Rotate 180");
    }

    for(auto val : rotate_list){
        lv_obj_set_style_transform_angle(val, rotate, 0);
        lv_obj_set_x(val, shift);
    }        

    File file =FileFS.open("/conf/orientation.ini", FILE_WRITE);
    String str(rot);
    file.write((uint8_t *)str.c_str(), str.length());
    file.close();
}

void shift_up(lv_obj_t * list)
{
    uint16_t item_count = lv_obj_get_child_cnt(list);
    if(item_count > 1) {
        //
        lv_obj_t * first_item = lv_obj_get_child(list, item_count-1);
        lv_obj_move_to_index(first_item, 0);
        //lv_obj_del(first_item);
    }
}

void shift_down(lv_obj_t * list)
{
    uint16_t item_count = lv_obj_get_child_cnt(list);
    if(item_count > 1) {
        //
        lv_obj_t * first_item = lv_obj_get_child(list, 0);
        lv_obj_move_to_index(first_item, item_count-1);
        //lv_obj_del(first_item);
    }
}
void action_shift_data_up(lv_event_t *e) 
{
    shift_up(objects.data_data);
    
}

void action_shift_data_down(lv_event_t *e) 
{
    shift_down(objects.data_data);
}

void action_shift_message_up(lv_event_t *e) {
    Serial.println("up noty");
    shift_up(objects.message_list);
}

void action_shift_message_down(lv_event_t *e) {
    Serial.println("down noty");
    shift_down(objects.message_list);
}



std::vector<lv_obj_t *> switch_list;
std::vector<lv_obj_t *> switch_change_list;
void initSwithRotate()
{
    switch_list.push_back(objects.swithc_orientation_1);
    switch_list.push_back(objects.swithc_orientation_2);
    switch_list.push_back(objects.swithc_orientation_3);
    switch_list.push_back(objects.swithc_orientation_4);

    switch_change_list.push_back(objects.swithc_orientation_changed_1);
    switch_change_list.push_back(objects.swithc_orientation_changed_2);
    switch_change_list.push_back(objects.swithc_orientation_changed_3);
    switch_change_list.push_back(objects.swithc_orientation_changed_4);

    File file =FileFS.open("/conf/orientation.ini", FILE_READ);
    String str = file.readString();
    uint8_t rot = str.toInt();
    file.close();

    

    lv_obj_add_state( switch_list.at(rot), LV_STATE_CHECKED);
    lv_obj_add_state( switch_change_list.at(rot), LV_STATE_CHECKED);
    
    

    auto cb = [](lv_event_t * event){
        // Снимаем нажатие
        for(auto val: switch_change_list){
            lv_obj_clear_state(val, LV_STATE_CHECKED);
        } 
        // Устанавливаем нажатие для текущего
        lv_obj_t *obj = (lv_obj_t *)lv_event_get_target(event);
        lv_obj_add_state(obj, LV_STATE_CHECKED);

        // Поворачиваем экран
        uint8_t *data = (uint8_t *)lv_event_get_user_data(event);
        // 0 - 0, 1 - 180, 2 - 90, 3 - 270 
        rotateWin( *data );

        for(auto val: switch_list){
            lv_obj_clear_state(val, LV_STATE_CHECKED);
        } 
        lv_obj_add_state(switch_list.at(*data), LV_STATE_CHECKED);
    };

    

    for (size_t i = 0; i < switch_change_list.size(); i++)
    {
        lv_obj_add_event_cb(switch_change_list.at(i), cb ,LV_EVENT_CLICKED, new uint8_t(i));
    }

    //
    Serial.println("read rotate: " + String(rot));

    file =FileFS.open("/conf/display_orientation.ini", FILE_READ);

    rotateWin(rot);
    
    Serial.println("file size: ");
    Serial.println(file.size());
    Serial.println("file: ");
    Serial.println(str);

}

void listDir(fs::FS &fs, const char *dirname, uint8_t levels) {
  Serial.printf("Listing directory: %s\r\n", dirname);

  File root = fs.open(dirname);
  if (!root) {
    Serial.println("- failed to open directory");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println(" - not a directory");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if (levels) {
        listDir(fs, file.path(), levels - 1);
      }
    } else {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("\tSIZE: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}

void setup()
{
    Serial.begin(115200);

    dataList.init();
    conf.init();

    listDir(FileFS, "/", 2);
    
    File file =FileFS.open("/conf/orientation.ini", FILE_READ);
    Serial.println("=============================");
    Serial.println("file: " + file.readString());
    Serial.println(file.readString());
    Serial.println("=============================");
    file.close();

    disp.init();
    ui_init();

    // if (FileFS.exists("/display.ini")) {
    //     set_var_setting_orientation(1);
    // } else {
    //     set_var_setting_orientation(0);
    // }

    gpio_set_level((gpio_num_t)PIN_NUM_BK_LIGHT, LCD_BK_LIGHT_ON_LEVEL);

    modBus.init();
    initAbout();
    initData();

    rotate_list.push_back( objects.data_data );
    rotate_list.push_back( objects.panel_main );
    rotate_list.push_back( objects.system_about );
    rotate_list.push_back( objects.message_list );
    rotate_list.push_back( objects.message_current );
    rotate_list.push_back( objects.message_container );
    rotate_list.push_back( objects.panel_setting );
    rotate_list.push_back( objects.panel_setting_net );
    rotate_list.push_back( objects.panel_setting_net_change );
    rotate_list.push_back( objects.panel_setting_display );
    rotate_list.push_back( objects.panel_setting_display_changed );
    rotate_list.push_back( objects.panel_setting_mode );
    rotate_list.push_back( objects.panel_setting_mode_changed );

    //lv_obj_set_style_opa(objects.message_container, 0, 0);

    //message_container

    
    //objects.con

    //rotateWin(1);
    initSwithRotate();


    //ui_create_groups();
    // uint32_t count = lv_group_get_obj_count(groups.win_rot90);

    // for (uint32_t i = 0; i < count; i++)
    // {
    //     lv_obj_t *obj = lv_group_get_obj_by_index(groups.win_rot90, i);
    //     lv_obj_set_style_transform_angle(obj, 900, 0);
    //     lv_obj_set_x(obj, 240);
    // }

    
    



    xTaskCreatePinnedToCore(
        Task1code,   // Функция задачи. 
        "Task1",     // Ее имя. 
        16*1024,       // Размер стека функции 
        NULL,        // Параметры 
        1,           // Приоритет 
        &Task1,      // Дескриптор задачи для отслеживания 
        0);          // Указываем пин для данного ядра  

    Serial.println("start [rogram]");

    //ui_tick();
    //lv_timer_handler();
    //lv_obj_set_x(lv_scr_act(), -40);

    
    //
    
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
    //lv_obj_set_x(lv_scr_act(), 0);

    update_wath();

    //set_var_control_rot2( get_var_control_rot2() + 1);

    // counter++;
    // if(counter >1000){
    //     counter =0;
    //     //Serial.printf("width: %d, height: %d\n", (int)lv_obj_get_width(lv_scr_act()), (int)lv_obj_get_height(lv_scr_act()));
    //     uint32_t count = lv_group_get_obj_count(groups.setting_rotate);
    //     Serial.printf("Group size: %d\n", (int)count);
    // }
    // delay(1);
}
