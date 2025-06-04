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

#define LCD_HOST  SPI2_HOST

class Display
{
public:
    Display();
    ~Display();

    void init();

private:


    esp_lcd_panel_handle_t panel_handle = NULL;
    lv_display_t *display;


};

extern Display disp;

#endif