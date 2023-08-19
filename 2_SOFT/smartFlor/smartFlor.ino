
//https://github.com/Rightech/ric-examples/blob/master/mqtt/arduino/103-json.ino
//https://www.iotsharing.com/2017/06/how-to-use-udpip-with-arduino-esp32.html
/* https://github.com/plapointe6/EspMQTTClient */

#include "my_wifi.h"
#include "deviceInfo.h"
#include "setStartRegim.h"

/*Выбираем на каком ядре будем работать*/
#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

void setup() {
  Serial.begin(115200);
  delay(3000);
  Serial.println("Power ON1");
  checkFerstStartInit();  //Проверка на первый старт

// initResetButton() ;
 initSwitchToAPButton();
/*Для FreeRtos*/
//Задача для WiFi
  xTaskCreatePinnedToCore(
    TaskWifiAp
    ,  "TaskWifiAp"
    ,  4096*2 // Stack size
    ,  NULL//Передаем состояние кнопки в качестве аргумента
    ,  1  // Priority
    ,  NULL
    ,  ARDUINO_RUNNING_CORE);


 Serial.println("init complite");

}

void loop()
{

}




