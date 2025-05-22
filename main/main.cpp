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
 #include "esp_lcd_panel_io.h"
 #include "esp_lcd_panel_vendor.h"
 #include "esp_lcd_panel_ops.h"
 #include "driver/gpio.h"
 #include "driver/spi_master.h"
 #include "esp_err.h"
 #include "esp_log.h"
 #include "lvgl.h"
 //#include "examp/ui.h"

 

 #include "esp_lcd_panel_st7789.h"

 
 #include "esp_lcd_touch_gt911.h"
 #include "driver/i2c_master.h"
 

static const char *TAG = "example";

// Using SPI2 in the example
#define LCD_HOST  SPI2_HOST

#include "DataList.h"
#include "ModbusControls.h"

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
        esp_lcd_panel_mirror(panel_handle, false, false);
        lv_display_set_rotation(display, LV_DISP_ROTATION_0);

        

        if (FileFS.exists("/display.ini")) {
            //FileFS
            FileFS.remove("/display.ini");
        } else {
            
        }
    } else {
        esp_lcd_panel_mirror(panel_handle, true, true);
        lv_display_set_rotation(display, LV_DISP_ROTATION_180);

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

    
    
    
    //lv_style_set_bg_opa(btn, 0);
    
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// Please update the following configuration according to your LCD spec //////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define EXAMPLE_LCD_PIXEL_CLOCK_HZ     (60 * 1000 * 1000)
#define EXAMPLE_LCD_BK_LIGHT_ON_LEVEL  1
#define EXAMPLE_LCD_BK_LIGHT_OFF_LEVEL !EXAMPLE_LCD_BK_LIGHT_ON_LEVEL
#define EXAMPLE_PIN_NUM_SCLK           4
#define EXAMPLE_PIN_NUM_MOSI           19
#define EXAMPLE_PIN_NUM_MISO           34
#define EXAMPLE_PIN_NUM_LCD_DC         21
#define EXAMPLE_PIN_NUM_LCD_RST        22
#define EXAMPLE_PIN_NUM_LCD_CS         2
#define EXAMPLE_PIN_NUM_BK_LIGHT       23
#define EXAMPLE_PIN_NUM_TOUCH_CS       35


#define EXAMPLE_LCD_H_RES              240
#define EXAMPLE_LCD_V_RES              320

// Bit number used to represent command and parameter
#define EXAMPLE_LCD_CMD_BITS           8
#define EXAMPLE_LCD_PARAM_BITS         8

#define EXAMPLE_LVGL_DRAW_BUF_LINES    20 // number of display lines in each draw buffer
#define EXAMPLE_LVGL_TICK_PERIOD_MS    2
#define EXAMPLE_LVGL_TASK_MAX_DELAY_MS 500
#define EXAMPLE_LVGL_TASK_MIN_DELAY_MS 1
#define EXAMPLE_LVGL_TASK_STACK_SIZE   (32 * 1024)
#define EXAMPLE_LVGL_TASK_PRIORITY     2

// LVGL library is not thread-safe, this example will call LVGL APIs from different tasks, so use a mutex to protect it
static _lock_t lvgl_api_lock;
extern void example_lvgl_demo_ui(lv_disp_t *disp);

static bool example_notify_lvgl_flush_ready(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx)
{
    lv_display_t *disp = (lv_display_t *)user_ctx;
    lv_display_flush_ready(disp);
    return false;
}



static void example_lvgl_flush_cb(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
    //example_lvgl_port_update_callback(disp);
    esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t)lv_display_get_user_data(disp);
    int offsetx1 = area->x1;
    int offsetx2 = area->x2;
    int offsety1 = area->y1;
    int offsety2 = area->y2;
    // because SPI LCD is big-endian, we need to swap the RGB bytes order
    lv_draw_sw_rgb565_swap(px_map, (offsetx2 + 1 - offsetx1) * (offsety2 + 1 - offsety1));
    // copy a buffer's content to a specific area of the display
    esp_lcd_panel_draw_bitmap(panel_handle, offsetx1, offsety1, offsetx2 + 1, offsety2 + 1, px_map);
}

static void example_lvgl_touch_cb(lv_indev_t * indev, lv_indev_data_t * data)
{
    uint16_t touchpad_x[1] = {0};
    uint16_t touchpad_y[1] = {0};
    uint8_t touchpad_cnt = 0;

    

    esp_lcd_touch_handle_t touch_pad = (esp_lcd_touch_handle_t)lv_indev_get_user_data(indev);
    esp_lcd_touch_read_data(touch_pad);
    /* Get coordinates */
    bool touchpad_pressed = esp_lcd_touch_get_coordinates(touch_pad, touchpad_x, touchpad_y, NULL, &touchpad_cnt, 1);

    if (touchpad_pressed && touchpad_cnt > 0) {
        //ESP_LOGI("TOUCH: ", "%d, %d", touchpad_x[0], touchpad_y[0]);
        data->point.x = touchpad_x[0];
        data->point.y = touchpad_y[0];
        data->state = LV_INDEV_STATE_PRESSED;
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

static void example_increase_lvgl_tick(void *arg)
{
    /* Tell LVGL how many milliseconds has elapsed */
    lv_tick_inc(EXAMPLE_LVGL_TICK_PERIOD_MS);
}

static void example_lvgl_port_task(void *arg)
{
    ESP_LOGI(TAG, "Starting LVGL task");
    uint32_t time_till_next_ms = 0;
    uint32_t time_threshold_ms = 1000 / CONFIG_FREERTOS_HZ;
    while (1) {
        //_lock_acquire(&lvgl_api_lock);
        time_till_next_ms = lv_timer_handler();
        //_lock_release(&lvgl_api_lock);
        // in case of triggering a task watch dog time out
        time_till_next_ms = MAX(time_till_next_ms, time_threshold_ms);
        usleep(1000 * time_till_next_ms);
    }
}

void setup()
{
    ESP_LOGI(TAG, "Turn off LCD backlight");
    gpio_config_t bk_gpio_config = {
        .pin_bit_mask = 1ULL << EXAMPLE_PIN_NUM_BK_LIGHT,
        .mode = GPIO_MODE_OUTPUT,
        
    };
    ESP_ERROR_CHECK(gpio_config(&bk_gpio_config));
    gpio_set_level((gpio_num_t)EXAMPLE_PIN_NUM_BK_LIGHT, EXAMPLE_LCD_BK_LIGHT_OFF_LEVEL);

    Serial.begin(115200);

    dataList.init();
    
 

    ESP_LOGI(TAG, "Initialize SPI bus");
    spi_bus_config_t buscfg = {
        .mosi_io_num = EXAMPLE_PIN_NUM_MOSI,
        .miso_io_num = EXAMPLE_PIN_NUM_MISO,
        .sclk_io_num = EXAMPLE_PIN_NUM_SCLK,
        
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = EXAMPLE_LCD_H_RES * 80 * sizeof(uint16_t),
    };
    ESP_ERROR_CHECK(spi_bus_initialize(LCD_HOST, &buscfg, SPI_DMA_CH_AUTO));

    ESP_LOGI(TAG, "Install panel IO");
    esp_lcd_panel_io_handle_t io_handle = NULL;
    esp_lcd_panel_io_spi_config_t io_config = {
        .cs_gpio_num = EXAMPLE_PIN_NUM_LCD_CS,
        .dc_gpio_num = EXAMPLE_PIN_NUM_LCD_DC,
        .spi_mode = 0,
        .pclk_hz = EXAMPLE_LCD_PIXEL_CLOCK_HZ,
        .trans_queue_depth = 10,
        .lcd_cmd_bits = EXAMPLE_LCD_CMD_BITS,
        .lcd_param_bits = EXAMPLE_LCD_PARAM_BITS,
        
    };
    // Attach the LCD to the SPI bus
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)LCD_HOST, &io_config, &io_handle));

    
    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = EXAMPLE_PIN_NUM_LCD_RST,
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB,
        .bits_per_pixel = 16,
    };

    esp_lcd_new_panel_st7789(io_handle, &panel_config, &panel_handle);

    
    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel_handle, false));
    ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel_handle, false, false));
    ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panel_handle, true));

    //panel_handle->mirror(panel_handle, true, false));    
    //esp_lcd_panel_invert_color(panel_handle, true);
    //esp_lcd_panel_mirror(panel_handle, false, true);

    // user can flush pre-defined pattern to the screen before we turn on the screen or backlight
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));

    ESP_LOGI(TAG, "Turn on LCD backlight");
    

    ESP_LOGI(TAG, "Initialize LVGL library");
    lv_init();

    // create a lvgl display
    display = lv_display_create(EXAMPLE_LCD_H_RES, EXAMPLE_LCD_V_RES);

    // alloc draw buffers used by LVGL
    // it's recommended to choose the size of the draw buffer(s) to be at least 1/10 screen sized
    size_t draw_buffer_sz = EXAMPLE_LCD_H_RES * EXAMPLE_LVGL_DRAW_BUF_LINES * sizeof(lv_color16_t);

    void *buf1 = spi_bus_dma_memory_alloc(LCD_HOST, draw_buffer_sz, 0);
    assert(buf1);
    void *buf2 = spi_bus_dma_memory_alloc(LCD_HOST, draw_buffer_sz, 0);
    assert(buf2);
    // initialize LVGL draw buffers
    lv_display_set_buffers(display, buf1, buf2, draw_buffer_sz, LV_DISPLAY_RENDER_MODE_PARTIAL);
    // associate the mipi panel handle to the display
    lv_display_set_user_data(display, panel_handle);
    // set color depth
    lv_display_set_color_format(display, LV_COLOR_FORMAT_RGB565);
    // set the callback which can copy the rendered image to an area of the display
    lv_display_set_flush_cb(display, example_lvgl_flush_cb);

    //esp_lcd_panel_mirror(panel_handle, true, true);

    //ESP_LOGI(TAG, "Install LVGL tick timer");
    // Tick interface for LVGL (using esp_timer to generate 2ms periodic event)
    // const esp_timer_create_args_t lvgl_tick_timer_args = {
    //     .callback = &example_increase_lvgl_tick,
    //     .name = "lvgl_tick"
    // };
    // esp_timer_handle_t lvgl_tick_timer = NULL;
    // (esp_timer_create(&lvgl_tick_timer_args, &lvgl_tick_timer));
    // ESP_ERROR_CHECK(esp_timer_start_periodic(lvgl_tick_timer, EXAMPLE_LVGL_TICK_PERIOD_MS * 1000));

    ESP_LOGI(TAG, "Register io panel event callback for LVGL flush ready notification");
    const esp_lcd_panel_io_callbacks_t cbs = {
        .on_color_trans_done = example_notify_lvgl_flush_ready,
    };
    /* Register done callback */
    ESP_ERROR_CHECK(esp_lcd_panel_io_register_event_callbacks(io_handle, &cbs, display));


    i2c_master_bus_handle_t i2c_bus = NULL;
    i2c_master_bus_config_t bus_config = {
        .i2c_port = (i2c_port_num_t)0,
        .sda_io_num = (gpio_num_t)33,
        .scl_io_num = (gpio_num_t)32,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        
        .flags = {
            .enable_internal_pullup = true,
            .allow_pd = false,
        }
    };

    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, &i2c_bus));   
    
    

    esp_lcd_panel_io_i2c_config_t tp_io_config = ESP_LCD_TOUCH_IO_I2C_GT911_CONFIG();
    tp_io_config.scl_speed_hz = 400*1000;

    esp_lcd_touch_io_gt911_config_t tp_gt911_config = {
        .dev_addr = (uint8_t)tp_io_config.dev_addr,
    };

    esp_lcd_panel_io_handle_t tp_io_handle = NULL;

    ESP_ERROR_CHECK(esp_lcd_new_panel_io_i2c(i2c_bus, &tp_io_config, &tp_io_handle));

    esp_lcd_touch_config_t tp_cfg = {
        .x_max = EXAMPLE_LCD_H_RES,
        .y_max = EXAMPLE_LCD_V_RES,
        //.rst_gpio_num = (gpio_num_t)-1,
        //.int_gpio_num = (gpio_num_t)35,
        .levels = {
            .reset = 0,
            .interrupt = 0,
        },
        .flags = {
            .swap_xy = 0,
            .mirror_x = 0,
            .mirror_y = 0,
        },
        .driver_data = &tp_gt911_config,
    };
        
    esp_lcd_touch_handle_t tp;    
    esp_lcd_touch_new_i2c_gt911(tp_io_handle, &tp_cfg, &tp);

    static lv_indev_t *indev;
    indev = lv_indev_create();  // Input device driver (Touch)
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_display(indev, display);
    lv_indev_set_user_data(indev, tp);
    lv_indev_set_read_cb(indev, example_lvgl_touch_cb);


    ESP_LOGI(TAG, "Create LVGL task");
    //xTaskCreate(example_lvgl_port_task, "LVGL", EXAMPLE_LVGL_TASK_STACK_SIZE, NULL, EXAMPLE_LVGL_TASK_PRIORITY, NULL);

    ESP_LOGI(TAG, "Display LVGL Meter Widget");
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
