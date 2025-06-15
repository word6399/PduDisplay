#ifndef  _MODBUSCONTROLS_H
#define  _MODBUSCONTROLS_H

#include <Arduino.h>
#include "DataList.h"
#include "ModbusSlave/ModbusSlave.h"
#include "Update.h"
#include "vars.h"
#include "actions.h"
#include "Windows.h"

#define RS485N1_UARTPORT        UART_NUM_1
#define RS485N1_RXD             39
#define RS485N1_TXD             17
#define RS485N1_RTS             5
#define RS485N1_CTS             -1
#define RS485N1_BUFSIZE         128
#define RS485N1_BAUDRATE        115200


void fileRemove(uint16_t *data, uint16_t length);
void fileWrite(uint16_t *data, uint16_t length);
void fileAppeng(uint16_t *data, uint16_t length);

void mbWorckMode(uint16_t *data, uint16_t length);

void updateFsBegin(uint16_t *data, uint16_t length);
void updateFsAppend(uint16_t *data, uint16_t length);
void updateFsEnd(uint16_t *data, uint16_t length); // Заканчивает обновление файловой системы начинает обновление Основной программы
void updateSourceEnd(uint16_t *data, uint16_t length);

void updateNet(uint16_t *data, uint16_t length);
void updateMessage(uint16_t *data, uint16_t length);

void updateDisplay(uint16_t *data, uint16_t length);


class ModbusControls
{

public:
    ModbusControls(/* args */);
    ~ModbusControls();

    void setModBus(ModbusLib * mb);


    void init();
    void tick();


private:


};

extern ModbusControls modBus;

#endif
