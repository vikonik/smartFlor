#include "webinterface.h"
#include <EEPROM.h>



#if defined(ESP8266)
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
//ESP8266WebServer server(80);

#elif defined(ESP32)



#else
#error "MyWiFi.cpp This ain't a ESP8266 or ESP32, dumbo!"
#endif
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#include <Arduino.h>
#include "deviceInfo.h"


/********************Web страницы***************************/
#include "style.h"
#include "PasswordPage.h"


/****************/
void sendPasswordPage();
void handle_OnConnect() ;
/***************/


  WebServer server(80);
void TaskWebInterface(void *pvParameters) {
 (void)pvParameters;
  server.begin();
  Serial.println("Server started");
  // Add service to MDNS-SD
  MDNS.addService("http", "tcp", 80);
serwerStart();
 
while(1){
  

  if (deviceInfo.workMode == MODE_AP) {
    checkSerwerConnect();
  } else {
    checkSerwerConnect();
//    checkClientConnected();//Это для MQTT
  }
    vTaskDelay(1000);
}
}

/*
Дергаем сервер
*/
void checkSerwerConnect() {
  server.handleClient();
 // MDNS.update();
}

/*
Здесь всё про настройку WEB страниц
*/
void serwerStart() {
   server.on("/", handle_OnConnect);    //Страница загрузки
  // server.onNotFound(handle_NotFound);  //страница отдается на несуществующую ссылку
  // server.on("/setSpeed_1", handle_setSpeed_1);
  // server.on("/setSpeed_2", handle_setSpeed_2);
  // server.on("/setSpeed_3", handle_setSpeed_3);
  // server.on("/funStop", handle_stop);
  // server.on("/toSetting", handle_sendPageSetting);

  // //кнопки на странице с настройками
  // //server.on("/get_page", sendPageSetting);  // /get?funStatus=funspeed_2
  // server.on("/get_routerSetting", handle_getRouterSetting);  //Настройка для подключению к роутеру
  // server.on("/get_mqttSetting", handle_getMQTTSetting);      //Настройка для подключению к брокеру


  // server.on("/toMainPage", handle_goToMainPage);  //Возврат на страницу управления вентилятором

  // //Ввод пароля для доступа на устройство
  server.on("/checkinputPassword", handle_checkinputPassword);

  server.begin();
  Serial.println("HTTP server started");
}

/**/
void handle_OnConnect() {
  Serial.println("send connection page");
  sendPasswordPage();
  //sendPage(BUTTON_OFF,  BUTTON_OFF, BUTTON_OFF, BUTTON_ON);
}

/**/
void handle_NotFound() {
  server.send(404, "text/plain", "Not found facking gavnishen vestrn");
}


/*
Страница ввода пароля
*/
void handle_checkinputPassword() {
  Serial.println("Press paswordSetting");
  Serial.printf("%s",server.arg("devicePassword"));
  
  if ( (server.arg("devicePassword") == deviceInfo.userPass)) {
    //sendPage(BUTTON_OFF, BUTTON_OFF, BUTTON_OFF, BUTTON_ON);
Serial.println("God password");
sendPasswordPage();
  } 
  else {
    Serial.println("Bad password");
    sendPasswordPage();
  }
  
}


/**/
void sendPasswordPage() {
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);  //CONTENT_LENGTH_UNKNOWN
  server.send(200, "text/html", "");
  server.sendContent_P(passwordPage, strlen(passwordPage));
    server.sendContent_P(style, strlen(style));
}
