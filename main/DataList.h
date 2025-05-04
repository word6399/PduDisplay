#ifndef DATALIST_H
#define DATALIST_H


#include <SPI.h>
#include <SPIFFS.h>
#include "ArduinoJson.h"
#include "Arduino.h"
#include <FFat.h>
#include <list>
#include <vector>


#define FileFS        FFat

typedef struct nodeTypeDef {
  uint16_t id;
  String desc;
  bool dataType; // 0 - float 1 - uint
  bool valid;
  float dataF;
  int data;
  int priority;

  //struct nodeTypeDef * nextNode;
} nodeTypeDef;


class DataList
{

    /* data */
public:
    DataList(/* args */);
    ~DataList();

    void init();

    void createNode(uint16_t index, String data);

    nodeTypeDef * getById( uint16_t index);
    int getNodeCount();

    void pushUnitInt(uint16_t id, uint16_t data);
    void pushUnitFloat(uint16_t id, float data);

    std::vector<nodeTypeDef*> * getList();
    int displaFilesAvaliable();
    void addDisplayFile(String fileName);
    std::list<String> * getDisplayFiles();

    void lockDisplay();
    void unlockDisplay();
    bool getDisplayLock();

    bool executUnitAvailable();
    void addMessage(String data);
    std::vector<String> *getMessageList();
    void clearMessageList();


private:
    uint16_t len;
    nodeTypeDef * nodeList;

    std::vector<nodeTypeDef*> listExecute;
    std::list<String> displayFiles;
    std::vector<String> messageList;
    bool displayLock = false;


};


extern DataList dataList;

#endif