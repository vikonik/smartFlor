#pragma once

#define BUTTON_MASTER_MODE 4
#define RELAY_PIN 2   // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED
typedef struct{
  IPAddress *local_ip;
  IPAddress *gateway;
  IPAddress *subnet;

}NetSetting_t;

extern NetSetting_t netSetting;


