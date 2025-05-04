#include "images.h"

const ext_img_desc_t images[8] = {
    { "control_down", &img_control_down },
    { "control_left", &img_control_left },
    { "control_up", &img_control_up },
    { "data", &img_data },
    { "notation", &img_notation },
    { "setting", &img_setting },
    { "system", &img_system },
    { "data_power", &img_data_power },
};
