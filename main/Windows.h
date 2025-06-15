#ifndef WINDOWS_H
#define WINDOWS_H

#pragma once

#include <Arduino.h>
#include "ui/ui.h"
#include "lvgl.h"

#include "ui/fonts.h"
#include "screens.h"

#include "DataList.h"

typedef struct 
{
    float *value;
    lv_obj_t *label;
    int prec;
} t_watch;

class Windows
{
public:
    Windows();
    ~Windows();

    void initData();
    void tickData();

private:

    void addDataRelay(lv_obj_t * parent, const char* text, float *value);
    void addDataDisplay(lv_obj_t * parent, const char* text, float *value, const char * meas, int prec =0);

    std::vector<t_watch> wath;
};

extern Windows win;


#endif