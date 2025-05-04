#include "DataList.h"


DataList::DataList(/* args */)
{

}

DataList::~DataList()
{
}

void DataList::init()
{
    FileFS.begin(true);  

    File file = FileFS.open("/conf/data.ini");
    DynamicJsonDocument doc(64*1024);
    deserializeJson(doc, file);

    Serial.println("Start Create List");

    // for(int i=0; i<len; i++){
    //     delete 
    // }

    len = 0;

    while(file.available()){
        char symbol = file.read();
        if( symbol == '}') len++;
    }

    //nodeList = new nodeTypeDef[len];

    file = FileFS.open("/conf/data.ini");
    len = 0;

    String data = "";

    while(file.available()){
        char symbol = file.read();
        if( symbol != '[' )
            data+= symbol;
        if( symbol == '}'){
            createNode(len, data);
            char skip = file.read();
            len++;
            data = "";
        } 
    }
    

    Serial.print("End Create List node cnt- ");
    Serial.println(len);
}

void DataList::createNode(uint16_t index, String data)
{
    DynamicJsonDocument doc(200);
    deserializeJson(doc, data);

    
    auto node = new nodeTypeDef;

    node->id = doc["UnitID"];
    String desc =  doc["Description"];
    node->desc = desc;
    String type = doc["Datatype"];
    if(type == "float"){
        node->dataType = false;
        node->dataF = doc["Value"];
    } else {
        node->dataType = true;
        node->data = doc["Value"];
    }
        
    node->priority = doc["Priority"];

    listExecute.push_back(node);
    //Serial.println(data);
    // nodeList[index].id = doc["UnitID"];
    // String desc =  doc["Description"];
    // nodeList[index].desc = desc;
    // String type = doc["Datatype"];
    // if(type == "float"){
    //     nodeList[index].dataType = false;
    //     nodeList[index].dataF = doc["Value"];
    // } else {
    //     nodeList[index].dataType = true;
    //     nodeList[index].data = doc["Value"];
    // }
        
    // nodeList[index].priority = doc["Priority"];
    

    // Serial.print("node % ");
    // Serial.print(index);
    // Serial.print(" id-");
    // Serial.print(nodeList[index].id);
    // Serial.print(" Description");
    // Serial.print(nodeList[index].desc);
    // Serial.print(" type-");
    // Serial.print(nodeList[index].dataType);
    // Serial.print(" priority-");
    // Serial.print(nodeList[index].priority);
    // Serial.print(" value-");
    // Serial.println(nodeList[index].dataF);
}

nodeTypeDef * DataList::getById(uint16_t index)
{
    return listExecute.at(index);
}

int DataList::getNodeCount()
{
    return len;
}

void DataList::pushUnitInt(uint16_t id, uint16_t data)
{
    nodeTypeDef * node = new nodeTypeDef();
    node->id = id;
    node->dataType = true;
    node->data = data;
    listExecute.push_back(node);
}

void DataList::pushUnitFloat(uint16_t id, float data)
{
}

std::vector<nodeTypeDef *> *DataList::getList()
{
    return &listExecute;
}

int DataList::displaFilesAvaliable()
{
    if(displayLock)
        return 0;
    return displayFiles.size();
}

void DataList::addDisplayFile(String fileName)
{
    displayFiles.push_back(fileName);
}

std::list<String> *DataList::getDisplayFiles()
{
    return &displayFiles;
}

void DataList::lockDisplay()
{
    Serial.println("Lock display");
    displayLock = true;
}

void DataList::unlockDisplay()
{
    Serial.println("Unclock display");
    displayLock = false;
}

bool DataList::getDisplayLock()
{
    return displayLock;
}


bool DataList::executUnitAvailable()
{
    bool available = false;

    if(listExecute.size() > 0){
        available = true;
    }
    return available;
}

void DataList::addMessage(String data)
{
    messageList.push_back(data);
}

std::vector<String> *DataList::getMessageList()
{
    return &messageList;
}

void DataList::clearMessageList()
{
    messageList.clear();
}


DataList dataList;
