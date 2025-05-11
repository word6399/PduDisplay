#ifndef EEZ_LVGL_UI_STRUCTS_H
#define EEZ_LVGL_UI_STRUCTS_H

#include "eez-flow.h"


#if defined(EEZ_FOR_LVGL)

#include <stdint.h>
#include <stdbool.h>

#include "vars.h"

using namespace eez;

typedef struct
{
    const char *name;
    const lv_img_dsc_t *icon;
    lv_color_t bg_color;
    lv_color_t text_color;
    const lv_font_t *font;
} dsgnMainButton_def;

enum FlowStructures {
    FLOW_STRUCTURE_DATA_TYPE = 16384
};

enum FlowArrayOfStructures {
    FLOW_ARRAY_OF_STRUCTURE_DATA_TYPE = 81920
};

enum data_typeFlowStructureFields {
    FLOW_STRUCTURE_DATA_TYPE_FIELD_RELEY = 0,
    FLOW_STRUCTURE_DATA_TYPE_FIELD_VOLTAGE = 1,
    FLOW_STRUCTURE_DATA_TYPE_FIELD_CURENT = 2,
    FLOW_STRUCTURE_DATA_TYPE_FIELD_POWER = 3,
    FLOW_STRUCTURE_DATA_TYPE_NUM_FIELDS
};

struct data_typeValue {
    Value value;
    
    data_typeValue() {
        value = Value::makeArrayRef(FLOW_STRUCTURE_DATA_TYPE_NUM_FIELDS, FLOW_STRUCTURE_DATA_TYPE, 0);
    }
    
    data_typeValue(Value value) : value(value) {}
    
    operator Value() const { return value; }
    
    operator bool() const { return value.isArray(); }
    
    bool reley() {
        return value.getArray()->values[FLOW_STRUCTURE_DATA_TYPE_FIELD_RELEY].getBoolean();
    }
    void reley(bool reley) {
        value.getArray()->values[FLOW_STRUCTURE_DATA_TYPE_FIELD_RELEY] = BooleanValue(reley);
    }
    
    float voltage() {
        return value.getArray()->values[FLOW_STRUCTURE_DATA_TYPE_FIELD_VOLTAGE].getFloat();
    }
    void voltage(float voltage) {
        value.getArray()->values[FLOW_STRUCTURE_DATA_TYPE_FIELD_VOLTAGE] = FloatValue(voltage);
    }
    
    float curent() {
        return value.getArray()->values[FLOW_STRUCTURE_DATA_TYPE_FIELD_CURENT].getFloat();
    }
    void curent(float curent) {
        value.getArray()->values[FLOW_STRUCTURE_DATA_TYPE_FIELD_CURENT] = FloatValue(curent);
    }
    
    float power() {
        return value.getArray()->values[FLOW_STRUCTURE_DATA_TYPE_FIELD_POWER].getFloat();
    }
    void power(float power) {
        value.getArray()->values[FLOW_STRUCTURE_DATA_TYPE_FIELD_POWER] = FloatValue(power);
    }
};

typedef ArrayOf<data_typeValue, FLOW_ARRAY_OF_STRUCTURE_DATA_TYPE> ArrayOfdata_typeValue;


#endif

#endif /*EEZ_LVGL_UI_STRUCTS_H*/
