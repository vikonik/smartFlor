#include "webinterface.h"
#include <EEPROM.h>
#include "stdlib.h"


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
#include "PasswordPage.h"//Первая страница ввода пароля
#include "mainPage.h"//Основная страница с установками

char buf[32];
/****************/
void handle_OnConnect();
void sendPasswordPage();
void sendMainPage();
void handle_newDataTempSensor_1();
void handle_newDataTempSensor_2();
void handle_workRegim();
/***************/


WebServer server(80);
void TaskWebInterface(void *pvParameters) {
  (void)pvParameters;
  server.begin();
  Serial.println("Server started");
  // Add service to MDNS-SD
  MDNS.addService("http", "tcp", 80);
  serwerStart();

  while (1) {


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
  server.on("/", handle_OnConnect);  //Страница загрузки
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
  //Обрабатываем нажатие кнопки для сохранения температуры датчика 1
  server.on("/newDataTempSensor_1", handle_newDataTempSensor_1);
  server.on("/newDataTempSensor_2", handle_newDataTempSensor_2);
  server.on("/workRegim", handle_workRegim);
  server.begin();
  Serial.println("HTTP server started");
}

/**/
void handle_OnConnect() {
  Serial.println("send connection page");
 // sendPasswordPage();
  //sendPage(BUTTON_OFF,  BUTTON_OFF, BUTTON_OFF, BUTTON_ON);
  sendMainPage();
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
  Serial.printf("Пароль %s \r\n", deviceInfo.userPass);
  Serial.printf("Введенный пароль %s\r\n", server.arg("devicePassword"));

  if ((server.arg("devicePassword") == deviceInfo.userPass)) {
    //sendPage(BUTTON_OFF, BUTTON_OFF, BUTTON_OFF, BUTTON_ON);
    Serial.println("God password");
    sendMainPage();
  } else {
    Serial.println("Bad password");
    sendPasswordPage();
  }
}

/*************************Обработка команд ввода новых уставок*****************************/
/**/
void handle_newDataTempSensor_1(){

Serial.println("New setting fot sensor_1");
Serial.printf("T1h %S \r\n", server.arg("tempSensor_1_t_up"));
Serial.printf("T1l %s \r\n", server.arg("tempSensor_1_t_dn"));

sprintf(buf,"%s", server.arg("tempSensor_1_t_up"));
deviceInfo.tempH_sensor_1 =  atoi(buf);
sprintf(buf,"%s", server.arg("tempSensor_1_t_dn"));
deviceInfo.tempL_sensor_1 =  atoi(buf);
sendMainPage();
}
/**/
void handle_newDataTempSensor_2(){
Serial.println("New setting fot sensor_2");

Serial.printf("T2h %S \r\n", server.arg("tempSensor_2_t_up"));
Serial.printf("T2l %s \r\n", server.arg("tempSensor_2_t_dn"));
sprintf(buf,"%s", server.arg("tempSensor_2_t_up"));
deviceInfo.tempH_sensor_2 =  atoi(buf);
sprintf(buf,"%s", server.arg("tempSensor_2_t_dn"));
deviceInfo.tempL_sensor_2 =  atoi(buf);

sendMainPage();
}

/**/
void handle_workRegim(){
Serial.println("handle_workRegim");
Serial.printf("workRegim %S \r\n", server.arg("mode"));
Serial.printf("sensor_1 %S \r\n", server.arg("sensor_1"));
Serial.printf("sensor_2 %S \r\n", server.arg("sensor_2"));
sendMainPage();
}
/****************************Отображение страниц******************************************/
/**/
void sendPasswordPage() {
 // char tmp[64];
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);  //CONTENT_LENGTH_UNKNOWN
  server.send(200, "text/html", "");

  server.sendContent_P(passwordPage_1, strlen(passwordPage_1));
  sprintf(buf, "%04X%08X\n", (uint16_t)(deviceInfo.deviceID >> 32), (uint32_t)deviceInfo.deviceID);
  server.sendContent(buf);
  server.sendContent_P(passwordPage_2, strlen(passwordPage_2));
  server.sendContent_P(style, strlen(style));
}

/**/
void sendMainPage(){
  Serial.println("sendMainPage");
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);  //CONTENT_LENGTH_UNKNOWN
  server.send(200, "text/html", "");

  server.sendContent_P(mainPage_1, strlen(mainPage_1));

  sprintf(buf, "%d", deviceInfo.tempH_sensor_1);
  server.sendContent(buf);

  server.sendContent_P(mainPage_2, strlen(mainPage_2));

  sprintf(buf, "%d", deviceInfo.tempL_sensor_1);
  server.sendContent(buf);

  server.sendContent_P(mainPage_3, strlen(mainPage_3));

  sprintf(buf, "%d", deviceInfo.tempH_sensor_2);
  server.sendContent(buf);

  server.sendContent_P(mainPage_4, strlen(mainPage_4));

  sprintf(buf, "%d", deviceInfo.tempL_sensor_2);
  server.sendContent(buf);

  server.sendContent_P(mainPage_5, strlen(mainPage_5));



  server.sendContent_P(style, strlen(style));
}
