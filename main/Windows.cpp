#include "Windows.h"

Windows::Windows()
{

}

Windows::~Windows()
{

}

void Windows::initData()
{
    lv_obj_clean(objects.data_data); // Нужно потом раскоментировать
    float tmp = 219;

    wath.clear();

    auto list = dataList.displayData();

    for(auto node: *list){
        float *ptr = &dataList.getById(node.id)->dataF;
        if(node.input)
            addDataRelay(objects.data_data, node.name.c_str(), ptr);
        else 
            addDataDisplay(objects.data_data, node.name.c_str(), ptr, node.meas.c_str(), node.pric);
    }
}

void Windows::tickData()
{
    for(auto val: wath){        
        lv_label_set_text(val.label, String(*val.value, val.prec).c_str());
    }
}

void Windows::addDataRelay(lv_obj_t * parent, const char * text, float * value)
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

void Windows::addDataDisplay(lv_obj_t * parent, const char * text, float * value, const char * meas, int prec)
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


Windows win;