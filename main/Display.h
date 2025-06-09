#ifndef DISPLAY_H
#define DISPLAY_H

#pragma once

#include <Arduino.h>
#include "lvgl.h"

#include "esp_lcd_panel_st7789.h"

#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"


#include "esp_lcd_touch_gt911.h"
#include "driver/i2c_master.h"


#define LCD_PIXEL_CLOCK_HZ     (60 * 1000 * 1000)
#define LCD_BK_LIGHT_ON_LEVEL  1
#define LCD_BK_LIGHT_OFF_LEVEL !LCD_BK_LIGHT_ON_LEVEL
#define PIN_NUM_SCLK           4
#define PIN_NUM_MOSI           19
#define PIN_NUM_MISO           34
#define PIN_NUM_LCD_DC         21
#define PIN_NUM_LCD_RST        22
#define PIN_NUM_LCD_CS         2
#define PIN_NUM_BK_LIGHT       23
#define PIN_NUM_TOUCH_CS       35


#define LCD_H_RES              240
#define LCD_V_RES              320

// Bit number used to represent command and parameter
#define LCD_CMD_BITS           8
#define LCD_PARAM_BITS         8

#define LVGL_DRAW_BUF_LINES    20 // number of display lines in each draw buffer
#define LVGL_TICK_PERIOD_MS    2
#define LVGL_TASK_MAX_DELAY_MS 500
#define LVGL_TASK_MIN_DELAY_MS 1
#define LVGL_TASK_STACK_SIZE   (32 * 1024)
#define LVGL_TASK_PRIORITY     2

#define LCD_HOST  SPI2_HOST

class Display
{
public:
    Display();
    ~Display();

    void init();

    void rotate180(uint8_t rotate);

    

private:

    void initDisplay();
    void initTouch();

    esp_lcd_panel_handle_t panel_handle = NULL;
    lv_display_t *display;


};

extern Display disp;

#endif