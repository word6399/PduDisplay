#include "Conf.h"

Conf::Conf()
{

}

Conf::~Conf()
{

}
const char TAG[] = "Conf";

static void list_data_partitions(void)
{
    ESP_LOGI(TAG, "Listing data partitions:");
    esp_partition_iterator_t it = esp_partition_find(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_ANY, NULL);

    for (; it != NULL; it = esp_partition_next(it)) {
        const esp_partition_t *part = esp_partition_get(it);
        ESP_LOGI(TAG, "- partition '%s', subtype %d, offset 0x%" PRIx32 ", size %" PRIu32 " kB",
        part->label, part->subtype, part->address, part->size / 1024);
    }

    esp_partition_iterator_release(it);
}


void Conf::init()
{
    list_data_partitions();

    if(!FatUser.begin(false, "/fuser", 10, "fuser")){
        Serial.println("Mount field");
    } else {
        Serial.println("Mount ok");
    }

    if(!FatSite.begin(false, "/fsite", 10, "fsite")){
        Serial.println("Mount field");
        
    } else {
        Serial.println("Mount ok");
    }

    Serial.println("============ fat user ============");

    File root = FatUser.open("/","r");
    File file = root.openNextFile();

    while(file){
        String path = file.path();
        Serial.println("user file: " + path);
        
        String data = file.readString();
        Serial.println(data);

        file = root.openNextFile();
    }

    Serial.println("============ fat site ============");

    root = FatSite.open("/","r");
    file = root.openNextFile();

    while(file){
        String path = file.path();
        Serial.println("user file: " + path);
        
        //String data = file.readString();
        //Serial.println(data);

        file = root.openNextFile();
    }
    Serial.println("done");

    // while(1){
    //     delay(1);
    // }
    
    initLogAdmin();
    initLogUser();
    initNet();
    initNtp();
    initSnmp1();
    initSnmp2();
    initSnmp3();
    initSnmp4();
    initSnmp5();
    initSnmpTrapMessage();
    initSyslogConf();
    initPduName();
    initDeviseMode();

    
}

void Conf::initLogAdmin()
{
    File file = FatUser.open(logAdminFile);
    DynamicJsonDocument doc(64*1024);
    deserializeJson(doc, file);

    m_logAdmin.adminLog  = doc["adminLog"].as<String>();
    m_logAdmin.adminPass = doc["adminPass"].as<String>();

    m_logAdmin.admin = m_logAdmin.adminLog + ":" + m_logAdmin.adminPass;
    Serial.println("logAdmin" + m_logAdmin.admin);

}

void Conf::saveLogAdmin()
{
    DynamicJsonDocument doc(64*1024);

    doc["adminLog"]  = m_logAdmin.adminLog;
    doc["adminPass"] = m_logAdmin.adminPass;

    File file = FatUser.open(logAdminFile, "w");
    serializeJson(doc, file);
    file.close();
}

void Conf::initLogUser()
{
    File file = FatUser.open(logUserFile);
    DynamicJsonDocument doc(64*1024);
    deserializeJson(doc, file);

    m_logUser.adminLog  = doc["userLog"].as<String>();
    m_logUser.adminPass = doc["userPass"].as<String>();

    m_logUser.admin = m_logUser.adminLog + ":" + m_logUser.adminPass;
    
}

void Conf::saveLogUser()
{
    DynamicJsonDocument doc(64*1024);

     doc["userLog"]  = m_logAdmin.adminLog;
     doc["userPass"] = m_logAdmin.adminPass;

    File file = FatUser.open(logUserFile, "w");
    serializeJson(doc, file);
    file.close();
}

void Conf::initNet()
{
    File file = FatUser.open(netFile);
    DynamicJsonDocument doc(64*1024);
    deserializeJson(doc, file);

    m_net.dhsp = doc["dhsp"];
    m_net.ip   = doc["ip"].as<String>();
    m_net.gw   = doc["gw"].as<String>();
    m_net.sn   = doc["sn"].as<String>();
    m_net.dns  = doc["dns"].as<String>();
    m_net.dns2 = doc["dns2"].as<String>();
    m_net.port = doc["port"];
    
    Serial.println("ip: " + m_net.ip );

    
}

void Conf::saveNet()
{
    DynamicJsonDocument doc(64*1024);

    doc["dhsp"] = m_net.dhsp;
    doc["ip"]   = m_net.ip;
    doc["gw"]   = m_net.gw;  
    doc["sn"]   = m_net.sn;  
    doc["dns"]  = m_net.dns;
    doc["dns2"] = m_net.dns2;
    doc["port"] = m_net.port;

    File file = FatUser.open(netFile, "w");
    serializeJson(doc, file);
    file.close();
    file = FatUser.open(netFile);
    Serial.println(file.readString());

    
    Serial.println("net save");
}

void Conf::initNtp()
{
    File file = FatUser.open(ntpFile);
    DynamicJsonDocument doc(64*1024);
    deserializeJson(doc, file);

    m_ntp.type      = doc["type"];
    m_ntp.timezone  = doc["timeZone"];
    m_ntp.ntp1      = doc["ntp1"].as<String>();
    m_ntp.ntp2      = doc["ntp2"].as<String>();
    m_ntp.ntp3      = doc["ntp3"].as<String>();
    m_ntp.update    = doc["update"];


    Serial.println(" ntp type: " + m_ntp.type );
    Serial.println(" ntp timezone: " + m_ntp.timezone );
    Serial.println(" ntp ntp1: " + m_ntp.ntp1 );
    Serial.println(" ntp ntp2: " + m_ntp.ntp2 );
    Serial.println(" ntp ntp3: " + m_ntp.ntp3 );
    Serial.println(" ntp update: " + m_ntp.update );
    

}

void Conf::saveNtp()
{
    DynamicJsonDocument doc(64*1024);

    doc["type"]     = m_ntp.type;    
    doc["timeZone"] = m_ntp.timezone;
    doc["ntp1"]     = m_ntp.ntp1;    
    doc["ntp2"]     = m_ntp.ntp2;    
    doc["ntp3"]     = m_ntp.ntp3;    
    doc["update"]   = m_ntp.update;  

    File file = FatUser.open(logAdminFile, "w");
    serializeJson(doc, file);
    file.close();
}

void Conf::initSnmp()
{
    initSnmp1();
    initSnmp2();
    initSnmp3();
    initSnmp4();
    initSnmp5();

}

void Conf::saveSnmp()
{
    saveSnmp1();
    saveSnmp2();
    saveSnmp3();
    saveSnmp4();
    saveSnmp5();
}

void Conf::initSnmp1()
{
    File file = FatUser.open(snmpFile1);
    DynamicJsonDocument doc(64*1024);
    deserializeJson(doc, file);


    m_snmp.enable       = doc["enable"];
    m_snmp.version      = doc["Version"];
    m_snmp.serverPort   = doc["ServerPort"];
    m_snmp.serverIp     = doc["ServerIp"].as<String>();
}

void Conf::saveSnmp1()
{
    DynamicJsonDocument doc(64*1024);

    doc["enable"]       = m_snmp.enable;
    doc["Version"]      = m_snmp.version;
    doc["ServerPort"]   = m_snmp.serverPort;
    doc["ServerIp"]     = m_snmp.serverIp;

    File file = FatUser.open(snmpFile1, "w");
    serializeJson(doc, file);
    file.close();
}

void Conf::initSnmp2()
{
    File file = FatUser.open(snmpFile2);
    DynamicJsonDocument doc(64*1024);
    deserializeJson(doc, file);

    m_snmp.comunityReadV1   = doc["ComunityRead1"].as<String>();
    m_snmp.comunityWriteV1  = doc["ComunityWrite1"].as<String>();
}

void Conf::saveSnmp2()
{
    DynamicJsonDocument doc(64*1024);

    doc["ComunityRead1"]    = m_snmp.comunityReadV1;
    doc["ComunityWrite1"]   = m_snmp.comunityWriteV1;

    File file = FatUser.open(snmpFile2, "w");
    serializeJson(doc, file);
    file.close();
}

void Conf::initSnmp3()
{
    File file = FatUser.open(snmpFile3);
    DynamicJsonDocument doc(64*1024);
    deserializeJson(doc, file);

    m_snmp.comunityRead  = doc["ComunityRead"].as<String>();
    m_snmp.comunityWrite = doc["ComunityWrite"].as<String>();
}

void Conf::saveSnmp3()
{
    DynamicJsonDocument doc(64*1024);

    doc["ComunityRead"]     = m_snmp.comunityRead;
    doc["ComunityWrite"]    = m_snmp.comunityWrite;

    File file = FatUser.open(snmpFile3, "w");
    serializeJson(doc, file);
    file.close();
}

void Conf::initSnmp4()
{
    File file = FatUser.open(snmpFile4);
    DynamicJsonDocument doc(64*1024);
    deserializeJson(doc, file);

    m_snmp.securityLevel  = doc["security"];
    m_snmp.enableWrite    = doc["enableWrite3"];
    m_snmp.nameV3         = doc["Name3"].as<String>();
    m_snmp.authProtocol   = doc["AuthCrypt"].as<String>();
    m_snmp.authPassV3     = doc["Auth3"].as<String>();
    m_snmp.privProtocol   = doc["KeyCrypt"].as<String>();
    m_snmp.privPassV3     = doc["Key3"].as<String>();
}

void Conf::saveSnmp4()
{
    DynamicJsonDocument doc(64*1024);

    doc["security"]     = m_snmp.securityLevel;
    doc["enableWrite3"] = m_snmp.enableWrite;
    doc["Name3"]        = m_snmp.nameV3;
    doc["AuthCrypt"]    = m_snmp.authProtocol;
    doc["Auth3"]        = m_snmp.authPassV3;
    doc["KeyCrypt"]     = m_snmp.privProtocol;
    doc["Key3"]         = m_snmp.privPassV3;

    File file = FatUser.open(snmpFile4, "w");
    serializeJson(doc, file);
    file.close();
}

void Conf::initSnmp5()
{
    File file = FatUser.open(snmpFile5);
    DynamicJsonDocument doc(64*1024);
    deserializeJson(doc, file);

    m_snmp.trapEnable   = doc["trapEnable"];
    m_snmp.trapIp       = doc["TrapIp"].as<String>();
    m_snmp.trapPort     = doc["TrapPort"];  
}

void Conf::saveSnmp5()
{
    DynamicJsonDocument doc(64*1024);

    doc["trapEnable"] = m_snmp.trapEnable;
    doc["TrapIp"]     = m_snmp.trapIp;
    doc["TrapPort"]   = m_snmp.trapPort;  

    File file = FatUser.open(snmpFile5, "w");
    serializeJson(doc, file);
    file.close();
}

void Conf::initSnmpTrapMessage()
{
    File file = FatUser.open(snmpTrapFile);
    DynamicJsonDocument doc(64*1024);
    deserializeJson(doc, file);

    m_snmpTrap.enable        = doc["enable"];
    m_snmpTrap.lowErr        = doc["lowErr"].as<String>();
    m_snmpTrap.lowCritical   = doc["lowCritical"].as<String>();
    m_snmpTrap.normal        = doc["normal"].as<String>();
    m_snmpTrap.hightCritical = doc["hightCritical"].as<String>();
    m_snmpTrap.hightErr      = doc["hightErr"].as<String>();
    m_snmpTrap.updateTime    = doc["updateTime"];

}

void Conf::saveSnmpTrapMessage()
{
    DynamicJsonDocument doc(64*1024);

    doc["enable"]       = m_snmpTrap.enable;
    doc["lowErr"]       = m_snmpTrap.lowErr;
    doc["lowCritical"]  = m_snmpTrap.lowCritical;
    doc["normal"]       = m_snmpTrap.normal;
    doc["hightCritical"]= m_snmpTrap.hightCritical;
    doc["hightErr"]     = m_snmpTrap.hightErr;
    doc["updateTime"]   = m_snmpTrap.updateTime;

    File file = FatUser.open(snmpTrapFile, "w");
    serializeJson(doc, file);
    file.close();
}

void Conf::initSyslogConf()
{
    File file = FatUser.open(syalogFile);
    DynamicJsonDocument doc(64*1024);
    deserializeJson(doc, file);

    m_syslog.enable = doc["enable"];
    m_syslog.server = doc["server"].as<String>();
    m_syslog.port   = doc["port"];

}

void Conf::saveSyslogConf()
{
    DynamicJsonDocument doc(64*1024);

    doc["enable"]   = m_syslog.enable;
    doc["server"]   = m_syslog.server;
    doc["port"]     = m_syslog.port;

    File file = FatUser.open(syalogFile, "w");
    serializeJson(doc, file);
    file.close();
}

void Conf::initPduName()
{
    File file = FatUser.open(nduNameFile);
    DynamicJsonDocument doc(64*1024);
    deserializeJson(doc, file);

    m_pduName.name = doc["name"].as<String>();

}

void Conf::savePduName()
{
    DynamicJsonDocument doc(64*1024);

    doc["name"] = m_pduName.name;

    File file = FatUser.open(nduNameFile, "w");
    serializeJson(doc, file);
    file.close();
}

void Conf::initDeviseMode()
{
    File file = FatUser.open(deviceModeFile);
    DynamicJsonDocument doc(64*1024);
    deserializeJson(doc, file);

    m_deviceMode.isSlave = doc["isSlave"].as<bool>();
    m_deviceMode.address = doc["address"];

    Serial.println("isSlave: " + String(m_deviceMode.isSlave) );
    Serial.println("address: " + String(m_deviceMode.address) );

   
   
}

void Conf::saveDeviseMode()
{
    File file = FatUser.open(deviceModeFile, "w");
    DynamicJsonDocument doc(64*1024);

    doc["isSlave"] = m_deviceMode.isSlave;
    doc["address"] = m_deviceMode.address;

    serializeJson(doc, file);
    file.close();
}

void Conf::initDisplayData()
{
    // Перенесено в другой файл
}

void Conf::saveDisplayData()
{
    // Перенесено в другой файл
}

LogAdmin_TypeDef *Conf::logAdmin()
{
    return &m_logAdmin;
}

LogAdmin_TypeDef *Conf::logUser()
{
    return &m_logUser;
}

netConf_TypeDef *Conf::net()
{
    return &m_net;
}

snmpConf_TypeDef *Conf::snmp()
{
    return &m_snmp;
}

ntpConf_TypeDef *Conf::ntp()
{
    return &m_ntp;
}

snmpTestTrap_TypeDef *Conf::snmpTestTrap()
{
    return &m_snmpTestTrap;
}

snmpTrapMessage_TypeDef *Conf::snmpTrap()
{
    return &m_snmpTrap;
}

syslogConf_TypeDef *Conf::syslog()
{
    return &m_syslog;
}

syslogTestMessage_TypeDef *Conf::syslogTestMessage()
{
    return &m_syslogTestMessage;
}

pduName_TypeDef *Conf::pduName()
{
    return &m_pduName;
}

deviceMode_TypeDef *Conf::deviceMode()
{
    return &m_deviceMode;
}

Conf conf;

