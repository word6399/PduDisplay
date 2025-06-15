#include "ModbusControls.h"
#include "eez-flow.h"
#include "ui/fonts.h"
#include "screens.h"
extern objects_t objects;


ModbusLib slave(Serial1, 0xF0);
uint16_t ethernetReset = 0;
uint16_t setWorckMode = 0;
uint16_t worckMode = 0;
int messageCount = 0;

uint16_t net[16];
char fileName[100];

bool uploadState = false;
size_t remainingFs;
size_t remainingFirmware;
int total = 0;

int32_t notify_count;

bool net_dhcp;

bool get_var_net_dhcp() {
    return net_dhcp;
}

void set_var_net_dhcp(bool value) {
    net_dhcp = value;
}

bool set_net_dhcp;

bool get_var_set_net_dhcp() {
    return set_net_dhcp;
}

void set_var_set_net_dhcp(bool value) {
    set_net_dhcp = value;
    set_var_net_dhcp(value);
}


int32_t get_var_notify_count() {
    return notify_count;
}

void set_var_notify_count(int32_t value) {
    notify_count = value;
}

void action_notify_clear(lv_event_t *e) {
    dataList.clearMessageList();
    lv_obj_clean(objects.message_list);
    set_var_notify_count(0);
}

int32_t set_net_mode;

int32_t get_var_set_net_mode() {
    return set_net_mode;
}

void set_var_set_net_mode(int32_t value) {
    set_net_mode = value;
    Serial.println("set net mode: " + String(value));
    
}

int32_t net_mode;

int32_t get_var_net_mode() {
    return net_mode;
}

void set_var_net_mode(int32_t value) {
    net_mode = value;
}

#include "ui/vars.h"


void addMessage(String message){
  lv_obj_t * btn = lv_button_create( objects.message_list );
  lv_obj_t *label = lv_label_create( btn );

  lv_obj_set_style_text_font(label, &ui_font_nunito_bold_18, 0);
  lv_label_set_text(label, message.c_str());

  lv_obj_set_height(btn, 40);
  lv_obj_set_width (btn, LV_PCT(100));    
  lv_obj_set_style_bg_opa(btn, 0, 0);
  lv_color_t bg_color;
  bg_color.red    = 0x15;
  bg_color.green  = 0x14;
  bg_color.blue   = 0x19;
  lv_obj_set_style_border_color(btn, bg_color, 0);
  lv_obj_set_style_border_width(btn, 2, 0);
  lv_obj_set_user_data(btn, (void*)(""));

  //eez_flow_set_screen();

  lv_event_cb_t handler =  [](lv_event_t * e){

    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED){
        //loadScreen();
        //message.c_str();
        char * message = (char *)lv_event_get_user_data(e);
        lv_obj_t * obj = lv_event_get_target_obj(e);
        lv_label_t * label = (lv_label_t *)lv_obj_get_child(obj, 0);
        
        set_var_notify_message( lv_label_get_text((lv_obj_t *)label));
        Serial.println(lv_label_get_text((lv_obj_t *)label));

        eez_flow_set_screen( SCREEN_ID_WINDOW_NOTIFY_MESAGGE, LV_SCR_LOAD_ANIM_NONE, 0, 0);
    }
  };

  lv_obj_add_event_cb(btn, handler, LV_EVENT_CLICKED, (void*)(message.c_str()));
}

String fileContent="";

extern bool removeFlag;

void fileRemove(uint16_t *data, uint16_t length)
{
  for(int i=0; i<length; i++)
    fileName[i] = data[i];

  removeFlag = true;
  
  //Serial.println("go to file update: ");
  //Serial.println(fileName);
  fileContent="";
}

extern bool updateDataFlag;
void fileWrite(uint16_t *data, uint16_t length)
{
  File file = FileFS.open(fileName, "a");
  file.write((uint8_t *) fileContent.c_str(), fileContent.length());
  file.close();
  
  //Serial.println("file write true");
}



void fileAppeng(uint16_t *data, uint16_t length)
{

  //File file = FileFS.open(fileName, "a");
  //file.write((uint8_t *)data, length*2);
  //file.close();
  fileContent += String((char *)data, length*2);

  //Serial.write((char *)data, length*2);

}

void mbWorckMode(uint16_t *data, uint16_t length)
{
   worckMode = data[0];

  String wrocktext;
  switch (worckMode)
  {
      case 0:
          wrocktext = "Master";
          break;
      case 1:
          wrocktext = "Slave 1";
          break;
      case 2:
          wrocktext = "Slave 2";
          break;
      case 3:
          wrocktext = "Slave 3";
          break;
  }
  set_var_net_mode(worckMode);
  //Serial.println("Mode: " + String(worckMode));

  set_var_setting_mode(worckMode);
}

void updateFsBegin(uint16_t *data, uint16_t length)
{
   size_t size = 0;
      
      uint16_t size16[length];
      for(int i = 0; i < length; i++){
        size16[i] = data[i];
      }  

      uint32_t *buf32 = (uint32_t *)size16;

    
      remainingFs = buf32[1];
      remainingFirmware = buf32[2];

      //size = ( size16[0] ) | ( size16[1] <<16 );
      uploadState = true;
      Update.begin(remainingFs, U_SPIFFS );   
      //Serial1.setTimeout(1);
      //Serial1.begin(115200);

      net[3] = 0x00100010;
      //uart_set_baudrate(UART_NUM_1, 921600);
      //Serial1.begin(921600);
}

void updateFsAppend(uint16_t *data, uint16_t length)
{
  uint16_t size16[length];
  //Update.write((uint8_t *)buf, length*2);

  for(int i = 0; i < length; i++){
    size16[i] = data[i];
  }  
  total+=length*2;
  //Serial.println(" update fs: " + String(total));

  Update.write((uint8_t *)size16, length*2);
}

void updateFsEnd(uint16_t *data, uint16_t length)
{
  if (Update.end()) {
      Serial.println("File FS OTA done!");
      if (Update.isFinished()) {
        Serial.println("Update FileFS successfully completed. Rebooting.");
        //ESP.restart();
      } else {
        Serial.println("Update not finished? Something went wrong!");
      }
    } else {
      Serial.println("Error Occurred. Error #: " + String(Update.getError()));
    }

    Update.begin(remainingFirmware, U_FLASH); 
}

void updateSourceEnd(uint16_t *data, uint16_t length)
{
  if (Update.end()) {
      Serial.println("File FS OTA done!");
      if (Update.isFinished()) {
        Serial.println("Update FileFS successfully completed. Rebooting.");
        ESP.restart();
      } else {
        Serial.println("Update not finished? Something went wrong!");
      }
    } else {
      Serial.println("Error Occurred. Error #: " + String(Update.getError()));
    }
}

void updateNet(uint16_t *data, uint16_t length)
{
  for(int i = 0; i < length; i++){
    uint16_t adr = data[i];
    net[i] = adr;//slave.readRegisterFromBuffer(i);

  } 

  uint8_t *ptr8;
  ptr8 = (uint8_t *)net;
  char ip[100];
  char mask[100];
  char gw[100];
  sprintf(ip,"%d.%d.%d.%d", ptr8[0], ptr8[1], ptr8[2], ptr8[3]);
  sprintf(mask,"%d.%d.%d.%d", ptr8[4], ptr8[5], ptr8[6], ptr8[7]);
  sprintf(gw,"%d.%d.%d.%d", ptr8[8], ptr8[9], ptr8[10], ptr8[11]);

  if(net[6] == 1){
    if( get_var_net_dhcp() != true){
      //set_var_set_net_mode(true);
      set_var_net_dhcp(true); 
    }
          
  } else if(net[6] == 2) {      
    if( get_var_net_dhcp() != false){
      //set_var_set_net_mode(false);
      set_var_net_dhcp(false);
    }  
    
  }
  
  set_var_setting_net_ip(ip);
  set_var_setting_net_mask(mask);
  set_var_setting_net_gw(gw);
}

void updateMessage(uint16_t *data, uint16_t length)
{

  uint8_t *data8 = (uint8_t *)data;
  String str(data8, length*2);
  
  dataList.addMessage(str);
  addMessage(str);

  set_var_notify_count(dataList.getMessageList()->size());
  
  messageCount++;
}

void updateDisplay(uint16_t *data, uint16_t length)
{
  //fileWrite(data, length);
  updateDataFlag = true;

}

uint8_t writeHolders(uint8_t fc, uint16_t address, uint16_t length)
{

  String data;
  
  //Serial.printf("adress %d, length %d\n", address, length);

  
  if(address < dataList.getNodeCount()){         
    int i=0;
    for(auto node : *dataList.getList()){
      uint16_t *ptr;
      ptr = (uint16_t*) &node->dataF;
      
      ptr[0] = slave.readRegisterFromBuffer(i*2);
      ptr[1] = slave.readRegisterFromBuffer(i*2+1);
      i++;

      //Serial.printf("%f ", node->dataF);
    }
    //Serial.printf("\n");
      // uint16_t data16[50];
      // for(int i=0; i<dataList.getNodeCount(); i++){
      //   data16[i] = slave.readRegisterFromBuffer(i);
      // }

      // float req =0;
      // uint32_t *pReq;
      // pReq = (uint32_t *) &req;

      // for(int i=0; i<length/2; i++){
      //   if(i >= dataList.getNodeCount())
      //     break;

      //   auto tmp = dataList.getById(i);
        
      //   tmp->dataF = i;
      //   *pReq = data16[i*2+0];
      //   *pReq |= ( data16[i*2+1] << 16 );
      //   tmp->dataF = req;
        
      // }

    return 0;
  }

  uint16_t buf[length];
  for(uint16_t i = 0; i < length; i++){
    buf[i] = slave.readRegisterFromBuffer(i);
  }  

  switch(address){
    case 200: fileRemove(buf, length); break;
    case 201: fileAppeng(buf, length); break;
    case 202: ESP.restart(); break;
    case 205: updateDisplay(buf, length); break;
    case 207: mbWorckMode(buf, length); break;

    // Update Source
    case 210: updateFsBegin(buf, length); break;
    case 211: updateFsAppend(buf, length); break; 
    case 212: updateFsEnd(buf, length); break; 
    case 214: updateSourceEnd(buf, length); break; 

    case 240: updateNet(buf, length); break; 
    case 241: updateMessage(buf, length); break; 

    default: break;
  }    

  return 0;
}

void action_mode_changed(lv_event_t *e) {
  
  bool data = (bool)lv_event_get_user_data(e);
  lv_obj_t *slider = (lv_obj_t *)lv_event_get_target(e);
  data = lv_obj_has_state(slider, LV_STATE_CHECKED);
  if(data == false)  ethernetReset = 1;
  Serial.println("action dhcp" + String(data));
  
}

void action_net_changed(lv_event_t *e) {
  // TODO: Implement action net_changed here
  lv_obj_t *slider = (lv_obj_t *)lv_event_get_target(e);
  net_dhcp = lv_obj_has_state(slider, LV_STATE_CHECKED);
  if(net_dhcp == true)  ethernetReset = 1;
  else ethernetReset = 2;
  Serial.println("action dhcp" + String(net_dhcp));
}


uint8_t readHolders(uint8_t fc, uint16_t address, uint16_t length)
{
    //Serial.println("address: " + String(address) + " length: " + String(length));

    if(address == 6){
      slave.writeRegisterToBuffer(0, ethernetReset);
      ethernetReset = 0;
    }
    if(address == 7){
      slave.writeRegisterToBuffer(0, set_net_mode);
      setWorckMode = 0;
    }
    return 0;

}

ModbusControls::ModbusControls(/* args */)
{
    Serial1.begin(115200);
}

ModbusControls::~ModbusControls()
{
}

void ModbusControls::setModBus(ModbusLib *mb)
{
    //m_slave = mb;

    //void * ptr = (void *)readHolders;
    //m_slave->cbVector[CB_READ_HOLDING_REGISTERS]  = (ModbusCallback*)(readHolders);
   

    // m_slave->begin(460000);
    // Serial1.setTimeout(1);
    //Serial1.setRxFIFOFull(255);
}

void ModbusControls::init()
{

  // Serial1.begin(115200);
  // Serial1.setTimeout(0);
  //Serial1.setPins(RS485N1_RXD, RS485N1_TXD, RS485N1_CTS, RS485N1_RTS );
  // Serial1.setMode(UART_MODE_RS485_HALF_DUPLEX);
  uart_config_t uart_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity    = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    .rx_flow_ctrl_thresh = 122,
    .source_clk = UART_SCLK_DEFAULT,
    
  };
  int intr_alloc_flags = 0;
  uart_driver_install((uart_port_t)1, 1024 * 2, 1024 * 2, 0, NULL, intr_alloc_flags);
  uart_param_config((uart_port_t)1, &uart_config);
  uart_set_pin((uart_port_t)1, 17, 39, 5, -1);
  uart_set_mode((uart_port_t)1, UART_MODE_RS485_HALF_DUPLEX);

  //slave.begin(115200);
  slave.cbVector[CB_READ_HOLDING_REGISTERS]  = readHolders;
  slave.cbVector[CB_WRITE_HOLDING_REGISTERS] = writeHolders;
    
}

void ModbusControls::tick()
{    
  if( slave.poll() == 0){
    delay(1);
  };
}

ModbusControls modBus;


