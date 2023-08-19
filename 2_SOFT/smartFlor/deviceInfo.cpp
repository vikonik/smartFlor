/*
Данные об устройстве
addr - адрес начала
dataкуда положить данные
  EEPROM.get(addr,data);
  EEPROM.put(addr,data);
  EEPROM.commit();  
  EEPROM.end();
*/
#if defined(ESP8266)
#pragma message "deviceinfo.cpp ESP8266 stuff happening!"
#include <ESP8266WiFi.h>

#elif defined(ESP32)
#pragma message "deviceinfo.cpp ESP32 stuff happening!"
#include <WiFi.h>

#else
#error "deviceinfo.cpp This ain't a ESP8266 or ESP32, dumbo!"
#endif

#include <Arduino.h>
#include <EEPROM.h>
#include "deviceInfo.h"

DeviceInfo_t deviceInfo;

const char* masterLogin = "masterLogin";//backDor
const char* masterPass = "masterPassword";

//Это для страницы входа на устройство
const char* defaultUserLogin = "user";//
const char* defaultUserPass = "pass";

const char* defaultSsidAP = "WormFlor";
const char* defaultPasswordAP = "00000000";

const char* defaultSsidSTA = "Vikonik";//"ava-1314";
const char* defaultPasswordSTA = "_88115221421";

uint32_t addrDeviceID = ADDR_deviceID;
uint32_t addrMac = addrDeviceID + sizeof(addrDeviceID);
uint32_t addApSSID  = addrMac + sizeof(addrMac);
uint32_t addApPass = addApSSID + sizeof(addApSSID);
uint32_t addrUserlogin = addApPass + sizeof(addApPass);
uint32_t addrUserPass = addrUserlogin + sizeof(addrUserlogin);
uint32_t addrSsid = addrUserPass + sizeof(addrUserPass);
uint32_t addrRouterPass = addrSsid + sizeof(addrSsid);
uint32_t addrBrockerAddr = addrRouterPass + sizeof(addrRouterPass);
uint32_t addrBrockerID = addrBrockerAddr + sizeof(addrBrockerAddr);
uint32_t addrBrockerLogin = addrBrockerID + sizeof(addrBrockerID);
uint32_t addrBrockerPass = addrBrockerLogin + sizeof(addrBrockerLogin);
uint32_t addrBrockerTopickOut = addrBrockerPass + sizeof(addrBrockerPass);
uint32_t addrKeyUseUserData = addrBrockerTopickOut + sizeof(addrBrockerTopickOut);//Ключ показывает, что импользубтся логин и пароль введенный пользователем
uint32_t addrKeyUseUserSetting = addrKeyUseUserData + sizeof(addrKeyUseUserData);//Ключ показывает, что импользубтся настройки сети введенные пользователем
uint32_t addrkeyFerstStart = addrKeyUseUserSetting + sizeof(addrKeyUseUserSetting);

const char* mqtt_server = "dev.rightech.io";//Брокер
const int mqtt_port = 1883;//Порт
const char*  mqtt_user = "user";//Логин для MQTT
const char*  mqtt_pass = "pass";//Пароль для MQTT
const char * mqtt_client_DI = "mqtt-smartFun";//ID объекта. При старте пустая строка. Идентификацию делаем по MAC
const char* inTopic = "alik";//Топик на который подписываемся для получеия команд управления
const char* outTopic = "alik";//Топик который отправляем 
/*
Инициализация структуры при первом включении
*/
void checkFerstStartInit(){
    const char* notInstaled = "Not instaled";
    uint32_t  stryctSize = sizeof(DeviceInfo_t);
    EEPROM.begin(sizeof(deviceInfo));
    EEPROM.get(addrDeviceID,deviceInfo);
    Serial.printf("Key %X\n",deviceInfo.keyFerstStart);
    if(deviceInfo.keyFerstStart != 0xDEADBEEE){//Если это действительно первый старт
      Serial.println("Ferst start");
      deviceInfo.keyFerstStart = 0xDEADBEEF; 
      setDefaultSetting();      
   }

   printDeviceSetting();
}

/*
Грузим сведения об устройства из алэша
*/
void getDeviceSetting(){
 EEPROM.get(addrDeviceID,deviceInfo);
}

/*
выводимв консоль сведения о настройках устройства
*/
void printDeviceSetting(){
  int i = 0;  
  char tmp[64];
  getDeviceSetting();//Получили данные из флаш
  getDeviceInfo();//Получили данные об устройстве
  Serial.printf("Device ID: 0x%04X%08X\n", (uint16_t)(deviceInfo.deviceID >>32), (uint32_t)deviceInfo.deviceID);
  Serial.printf("Device MAC: %X:%X:%X:%X:%X:%X\n", deviceInfo.mac[0],deviceInfo.mac[1],deviceInfo.mac[2],deviceInfo.mac[3],deviceInfo.mac[4],deviceInfo.mac[5]);
  Serial.printf("Device userLogin: %S\n", deviceInfo.userLogin);
  Serial.printf("Device userPass: %S\n", deviceInfo.userPass);
  Serial.printf("Device keyUseUserData: 0x%X\n", deviceInfo.keyUseUserData);
  Serial.printf("Device apSSID: %S\n", deviceInfo.apSSID);
  Serial.printf("Device apPass: %S\n", deviceInfo.apPass);
  Serial.printf("Device routerSSID: %S\n", deviceInfo.routerSSID);
  Serial.printf("Device routerPass: %S\n", deviceInfo.routerPass);
  Serial.printf("Device brockerAddr: %S\n", deviceInfo.brockerAddr);
  Serial.printf("Device brockerID: %S\n", deviceInfo.brockerID);
  Serial.printf("Device brockerLogin: %S\n", deviceInfo.brockerLogin);
  Serial.printf("Device brockerPass: %S\n", deviceInfo.brockerPass);
  Serial.printf("Device brockerTopickOut: %S\n", deviceInfo.brockerTopickOut);
  Serial.printf("Device brockerTopikIn: %S\n", deviceInfo.brockerTopikIn);
  Serial.printf("Device keyUseUserSetting: 0x%X\n", deviceInfo.keyUseUserSetting);
  Serial.printf("Device keyFerstStart: 0x%X\n", deviceInfo.keyFerstStart);

}


/*
brockerTopikInполучаем сведения о сотоянии устройства
*/
void getDeviceInfo(){
  #if defined(ESP8266)
#pragma message "deviceinfo.cpp ESP8266 stuff happening!"
deviceInfo.deviceID = ESP.getChipId();

#elif defined(ESP32)
#pragma message "deviceinfo.cpp ESP32 stuff happening!"
deviceInfo.deviceID = ESP.getEfuseMac();
#else
#error "deviceinfo.cpp This ain't a ESP8266 or ESP32, dumbo!"
#endif


uint8_t buf[6];
WiFi.macAddress(deviceInfo.mac); 

    Serial.printf("_Device MAC: %X\n", deviceInfo.mac);
    Serial.println(WiFi.macAddress());
//  getDeviceInfoData();
}

/*
Заполняем структуру со сведениями и настройками устройства
*/
void getDeviceInfoData(){



// 	int keyUseUserData = EEPROM.read(addrKeyUseUserData);
// 	uint32_t i = 0;
//   uint8_t readTmp = 0;

// // имя пользователя и пароль  
// if(keyUseUserData == USER_DATA){
//     //читаем логин
//     readTmp = EEPROM.read(addrUserlogin);
// 		while(readTmp!= 0){
// 			deviceInfo.userLogin[i] += EEPROM.read(addrUserlogin + i);	
//       i++;      
//       readTmp = EEPROM.read(addrUserlogin + i);      
// 		}
//     //читаем пароль
//     readTmp = EEPROM.read(addrUserPass);
// 		while(readTmp!= 0){
// 			deviceInfo.userPass[i] += EEPROM.read(addrUserPass + i);	
//       i++;      
//       readTmp = EEPROM.read(addrUserPass + i);      
// 		}
// 	}
}


/*
Установка значеий поумолчанию
*/
void setDefaultSetting(){

  //Сначали почистили мусор    
      memset(deviceInfo.apSSID,0, sizeof(deviceInfo.apSSID));  
      memset(deviceInfo.apPass,0, sizeof(deviceInfo.apPass));  
      memset(deviceInfo.userLogin,0, sizeof(deviceInfo.userLogin));
      memset(deviceInfo.userPass,0, sizeof(deviceInfo.userPass));
      deviceInfo.keyUseUserData = 0;
      memset(deviceInfo.routerSSID,0, sizeof(deviceInfo.routerSSID));    
      memset(deviceInfo.routerPass,0, sizeof(deviceInfo.routerPass));    
      memset(deviceInfo.brockerAddr,0, sizeof(deviceInfo.brockerAddr));    
      memset(deviceInfo.brockerID,0, sizeof(deviceInfo.brockerID));    
      memset(deviceInfo.brockerLogin,0, sizeof(deviceInfo.brockerLogin));    
      memset(deviceInfo.brockerPass,0, sizeof(deviceInfo.brockerPass)); 
      memset(deviceInfo.brockerTopickOut,0, sizeof(deviceInfo.brockerTopickOut)); 
      memset(deviceInfo.brockerTopikIn,0, sizeof(deviceInfo.brockerTopikIn)); 
      deviceInfo.keyUseUserSetting = 0;

	
  // /*******Дописать настройки роутера по умолчанию***************************/
      //deviceInfo.deviceID = ESP.getChipId();
      memcpy(deviceInfo.userLogin,defaultUserLogin, strlen(defaultUserLogin));
      memcpy(deviceInfo.userPass,defaultUserPass, strlen(defaultUserPass));
      memcpy(deviceInfo.apSSID, defaultSsidAP,strlen(defaultSsidAP));    
      memcpy(deviceInfo.apPass, defaultPasswordAP, strlen(defaultPasswordAP));
      memcpy(deviceInfo.routerSSID,defaultSsidSTA, strlen(defaultSsidSTA));    
      memcpy(deviceInfo.routerPass,defaultPasswordSTA, strlen(defaultPasswordSTA)); 
      memcpy(deviceInfo.brockerAddr,mqtt_server, strlen(mqtt_server));    
      memcpy(deviceInfo.brockerID,mqtt_client_DI, strlen(mqtt_client_DI));    
      memcpy(deviceInfo.brockerLogin,mqtt_user, strlen(mqtt_user));    
      memcpy(deviceInfo.brockerPass,mqtt_pass, strlen(mqtt_pass)); 
      memcpy(deviceInfo.brockerTopickOut,outTopic, strlen(outTopic)); 
      memcpy(deviceInfo.brockerTopikIn,inTopic, strlen(inTopic)); 
    
  // /*************************************************************************/

      EEPROM.put(addrDeviceID,deviceInfo);
      EEPROM.commit();    
}
