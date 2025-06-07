#ifndef CONF_H
#define CONF_H

#pragma once

#include "vfs_api.h"
#include "ArduinoJson.h"
#include <FFat.h>
#include <esp_log.h>
#include "esp_log.h"

#define LOG_CONF_ENABLE 0

using namespace fs;
#define FileFS   FFat
#define FatUser  FFat
#define FatSite  FFat


typedef struct {
  String ip;
  String sn;
  String gw;
  String dns;
  String dns2;
  uint16_t port;
  bool dhsp;
  bool changed;
} netConf_TypeDef;

typedef struct {
  int type;
  int timezone;
  String ntp1;
  String ntp2;
  String ntp3;
  uint32_t update;
  bool changed;
} ntpConf_TypeDef;

typedef struct {
  String name;
  String id;
  String host;
  String port;
  String userName;
  String userPass;
} mqttConf_TypeDef;

typedef struct {
  bool connect;
} mqttStatus_TypeDef;


typedef struct {
  bool enable;
  int version;  
  int serverPort;
  String serverIp;
  bool changed;
} snmpConf1_typedef;

typedef struct {
  // v2
  String comunityReadV1;
  String comunityWriteV1;
  bool changed;
} snmpConf2_typedef;

typedef struct {
  String comunityReadV2;
  String comunityWriteV2;
  bool changed;
} snmpConf3_typedef;

typedef struct {
  // v3
  int securityLevel;
  bool enableWrite;
  String nameV3;
  String authProtocol;
  String authPassV3;
  String privProtocol;
  String privPassV3;
  bool changed;
} snmpConf4_typedef;

typedef struct {
  bool trapEnable;
  String trapIp;
  int trapPort;
  bool changed;
} snmpConf5_typedef;

typedef struct {
  snmpConf1_typedef card1; // Общие
  snmpConf2_typedef card2; // snmp v1
  snmpConf3_typedef card3; // snmp v2
  snmpConf4_typedef card4; // snmp v3
  snmpConf5_typedef card5; // snmp trap

  bool enable;
  bool trapEnable;
  int version;  
  String serverIp;
  int serverPort;
  String trapIp;
  int trapPort;


  // v1
  String comunityReadV1;
  String comunityWriteV1;

  // v2
  String comunityRead;
  String comunityWrite;

  // v3
  int securityLevel;
  bool enableWrite;
  String nameV3;
  String authProtocol;
  String authPassV3;
  String privProtocol;
  String privPassV3;
  
  bool changed;
  bool changed1;
  bool changed2;
  bool changed3;
  bool changed4;
  bool changed5;
} snmpConf_TypeDef;

typedef struct {
  String trapIp;
  int trapPort;
  String message;
  bool changed;
} snmpTestTrap_TypeDef;

typedef struct {
  bool enable;
  String message;
  String lowErr;
  String lowCritical;
  String normal;
  String hightCritical;
  String hightErr;
  int updateTime;
  bool changed;
  
} snmpTrapMessage_TypeDef;

typedef struct {
  bool enable;
  String server;
  int port;
  bool changed;
  
} syslogConf_TypeDef;

typedef struct {
  String ip;
  uint16_t port;
  String meaasge;
  bool changed;
  
} syslogTestMessage_TypeDef;

typedef struct {
  String adminLog;
  String adminPass;
  String admin;
  bool changed;
  
} LogAdmin_TypeDef;

typedef struct {
  String name;
} pduName_TypeDef;

typedef struct {
  bool isSlave;
  uint16_t address;
} deviceMode_TypeDef;

typedef struct modeBusTypeDef {
  uint16_t id;
  uint16_t adr;
  uint16_t reg;
  uint16_t len;
  uint16_t priority;
} modeBusTypeDef;




const char logAdminFile[]    = "/conf/log_admin.ini";
const char logUserFile[]     = "/conf/log_user.ini";
const char netFile[]         = "/conf/net.ini";
const char snmpFile1[]       = "/conf/snmpconf1.ini";
const char snmpFile2[]       = "/conf/snmpconf2.ini";
const char snmpFile3[]       = "/conf/snmpconf3.ini";
const char snmpFile4[]       = "/conf/snmpconf4.ini";
const char snmpFile5[]       = "/conf/snmpconf5.ini";
const char ntpFile[]         = "/conf/ntp_conf.ini";
const char snmpTrapFile[]    = "/conf/trap_message.ini";
const char snmpTestFile[]    = "/conf/log_admin.ini";
const char syalogFile[]      = "/conf/syslog.ini";
const char nduNameFile[]     = "/conf/pdu_name.ini";
const char deviceModeFile[]  = "/conf/deviceMode.ini";
const char dataListFile[]    = "/conf/data.ini";
const char dashboardFile[]   = "/conf/dashboard.ini";
const char modbusFile[]      = "/conf/modbus.ini";


class Conf
{
public:
    Conf();
    ~Conf();

    void init();    

    void initLogAdmin();
    void saveLogAdmin();
    void initLogUser();
    void saveLogUser();    
    void initNet();
    void saveNet();
    void initNtp();
    void saveNtp();

    void initSnmp();
    void saveSnmp();
    void initSnmp1();
    void saveSnmp1();
    void initSnmp2();
    void saveSnmp2();
    void initSnmp3();
    void saveSnmp3();
    void initSnmp4();
    void saveSnmp4();
    void initSnmp5();
    void saveSnmp5();

    void initSnmpTrapMessage();
    void saveSnmpTrapMessage();
    void initSyslogConf();
    void saveSyslogConf();
    void initPduName();
    void savePduName();
    void initDeviseMode();
    void saveDeviseMode();

    void initDisplayData();
    void saveDisplayData();
    
    LogAdmin_TypeDef          *logAdmin();          
    LogAdmin_TypeDef          *logUser();           
    netConf_TypeDef           *net();                   
    snmpConf_TypeDef          *snmp();          
    ntpConf_TypeDef           *ntp();           
    snmpTestTrap_TypeDef      *snmpTestTrap();      
    snmpTrapMessage_TypeDef   *snmpTrap();   
    syslogConf_TypeDef        *syslog();         
    syslogTestMessage_TypeDef *syslogTestMessage(); 
    pduName_TypeDef           *pduName();
    deviceMode_TypeDef        *deviceMode();

    int tstAncors;
    bool dataListChanged;
    bool isChanged;
    bool isChangedTable;
    bool isChangedSetting;
    bool modbusChanged;
    bool snmpChanged;

private:
    LogAdmin_TypeDef          m_logAdmin;    
    LogAdmin_TypeDef          m_logUser;     
    netConf_TypeDef           m_net;         
    snmpConf_TypeDef          m_snmp;        
    ntpConf_TypeDef           m_ntp;         
    snmpTestTrap_TypeDef      m_snmpTestTrap;
    snmpTrapMessage_TypeDef   m_snmpTrap;   
    syslogConf_TypeDef        m_syslog;      
    syslogTestMessage_TypeDef m_syslogTestMessage;
    pduName_TypeDef           m_pduName;
    deviceMode_TypeDef        m_deviceMode;
};

extern Conf conf;

#endif