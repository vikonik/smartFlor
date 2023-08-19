/*
  WiFiAccessPoint.ino creates a WiFi access point and provides a web server on it.

  Steps:
  1. Connect to the access point "yourAp"
  2. Point your web browser to http://192.168.4.1/H to turn the LED on or http://192.168.4.1/L to turn it off
     OR
     Run raw TCP "GET /H" and "GET /L" on PuTTY terminal with 192.168.4.1 as IP address and 80 as port

  Created for arduino-esp32 on 04 July, 2018
  by Elochukwu Ifediora (fedy0)
*/

#if defined(ESP8266)
#pragma message "MyWiFi.cpp ESP8266 stuff happening!"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#elif defined(ESP32)
#pragma message "MyWiFi.cpp ESP32 stuff happening!"
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiAP.h>
#else
#error "MyWiFi.cpp This ain't a ESP8266 or ESP32, dumbo!"
#endif


#include <Arduino.h>
#include <WiFiClient.h>

#include "my_wifi.h"
#include "deviceInfo.h"
#include "setStartRegim.h"  //отсюда берем кнопку переключения в режим AP
//#include "allDefenition.h"

void initWiFi_AP();
void initWiFi_STA();


IPAddress local_ip(192,168,0,1);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);


WiFiServer server(80);

void TaskWifiAp(void *pvParameters) {
  (void)pvParameters;

  initWiFi();

  server.begin();
  Serial.println("Server started");
  // Add service to MDNS-SD
  MDNS.addService("http", "tcp", 80);

  while (1) {

    Serial.print("Stations connected: ");
    Serial.println(WiFi.softAPgetStationNum());
    WiFiClient client = server.available();  // listen for incoming clients
    /**/
    if (client) {                     // if you get a client,
      Serial.println("New Client.");  // print a message out the serial port
      String currentLine = "";        // make a String to hold incoming data from the client
      while (client.connected()) {    // loop while the client's connected
        if (client.available()) {     // if there's bytes to read from the client,
          char c = client.read();     // read a byte, then
          Serial.write(c);            // print it out the serial monitor
          if (c == '\n') {            // if the byte is a newline character

            // if the current line is blank, you got two newline characters in a row.
            // that's the end of the client HTTP request, so send a response:
            if (currentLine.length() == 0) {
              // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
              // and a content-type so the client knows what's coming, then a blank line:
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println();

              // the content of the HTTP response follows the header:
              client.print("Click <a href=\"/H\">here</a> to turn ON the LED.<br>");
              client.print("Click <a href=\"/L\">here</a> to turn OFF the LED.<br>");

              // The HTTP response ends with another blank line:
              client.println();
              // break out of the while loop:
              break;
            } else {  // if you got a newline, then clear currentLine:
              currentLine = "";
            }
          } else if (c != '\r') {  // if you got anything else but a carriage return character,
            currentLine += c;      // add it to the end of the currentLine
          }

          // Check to see if the client request was "GET /H" or "GET /L":
          /*
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(RELAY_PIN, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(RELAY_PIN, LOW);                // GET /L turns the LED off
        }
        */
        }
      }
      // close the connection:
      client.stop();
      Serial.println("Client Disconnected.");
    }

    vTaskDelay(5000);
  }
}


/*********************************************************************************************************************************************************************/
/*
Эту функцию добавить в setup
*/
void initWiFi() {
  Serial.println("Try to WiFi init");
  //Если нажата кнопка перехода в режим AP то переходим
  //Если указан SSID роутера, то пытаемя подключится к нем, если не получается переключаемся на работу в режиме точки доступа
  //Если название WiFi сети установлено и не пустая строка
  if (digitalRead(SWITCH_TO_AP_BUTTON) == LOW) {
    Serial.println("TestPoint\n");
    if ((strcmp(deviceInfo.routerSSID, "Not instaled") != 0) && (strcmp(deviceInfo.routerSSID, "") != 0)) {
      Serial.println("TestPoint 2\n");
      if (setupWifiStandartWork() == 255) {
        Serial.println("Can not connect to router, start as AP\n");
        setupWifiApMode();
        deviceInfo.workMode = MODE_AP;
      }
      //initMQTT(); Пока без неё
      //serwerStart();//Пока без нее, надо для работы с web страницей

      deviceInfo.workMode = MODE_STA;
    } else {
      Serial.println("Can not find router SSID, start as AP\n");
      setupWifiApMode();
      deviceInfo.workMode = MODE_AP;
    }

  } else {
    Serial.println("Prees button SWITCH_TO_AP_BUTTON, start as AP\n");
    setupWifiApMode();
    deviceInfo.workMode = MODE_AP;
  }
  if (deviceInfo.workMode == MODE_AP) Serial.printf("workMode AP");
  if (deviceInfo.workMode == MODE_STA) Serial.printf("workMode STA");
Serial.println("WiFi init complite\n");
  //serwerStart(); Пока без неё
}
/*
Настраиваем как точку доступа
*/
void setupWifiApMode() {
  delay(1000);


  Serial.println("Configuring access point...");
    
   Serial.println(local_ip); 

  WiFi.hostname(deviceInfo.apSSID);  //Устанавливаем имя устройства чтобы оно отображалось на роутере
  WiFi.mode(WIFI_AP);
 	Serial.print("Setting soft-AP configuration ... ");
 	Serial.println(WiFi.softAPConfig(local_ip, gateway, subnet) ? "Ready" : "Failed!");
 	Serial.print("Setting soft-AP ... ");
 	Serial.println(WiFi.softAP(deviceInfo.apSSID, deviceInfo.apPass) ? "Ready" : "Failed!");

  delay(1000);
  String str(deviceInfo.apSSID);
  if (!MDNS.begin(str)) {  //Назначаем сетевое имя, задаем такое же как и имя точки доступа
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.print("Soft-AP IP address: ");
 	Serial.println(WiFi.softAPIP());
  Serial.print("ESP Board MAC Address:  ");
  Serial.println(WiFi.macAddress());
  
  delay(100);
}

/*
Настроить режим работы как клиент
если в течении минуты нет подключения, то настраиваем на точку доступа
*/
uint8_t setupWifiStandartWork() {
  uint8_t tryConnectCNT = 0;
  delay(5000);
  Serial.println("Connecting as STA");
  Serial.printf("SSID: %S Password: %S", deviceInfo.routerSSID, deviceInfo.routerPass);

  WiFi.hostname(deviceInfo.apSSID);  //Устанавливаем имя устройства чтобы оно отображалось на роутере
  WiFi.mode(WIFI_STA);

  //Serial.print("Host Name: ");
  //Serial.println(WiFi.hostname());


  WiFi.begin(deviceInfo.routerSSID, deviceInfo.routerPass);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED && tryConnectCNT < 120) {
    delay(500);
    Serial.print(".");
    tryConnectCNT++;

    //	digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
  if (tryConnectCNT >= 120)  //Если не получилось подключиться выходим с ошибкой
    return 255;

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(deviceInfo.routerSSID);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  String str(deviceInfo.apSSID);
  if (!MDNS.begin(str)) {  //Назначаем сетевое имя, задаем такое же как и имя точки доступа
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("MDNS responder started");
  //  connectLedOn();
  return 0;
}

const char pageStyle[] PROGMEM = "варпврирапиаот";
