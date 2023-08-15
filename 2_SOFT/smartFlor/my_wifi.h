#pragma once
#include "WiFi.h"
//Сетевые настройки
//typedef struct{
//  IPAddress *local_ip;
//  IPAddress *gateway;
//  IPAddress *subnet;
//
//}NetSetting_t;
//extern NetSetting_t netSetting;

//void TaskWifiAp(void *pvParameters);
void initWiFi_AP();
void initWiFi_STA();
