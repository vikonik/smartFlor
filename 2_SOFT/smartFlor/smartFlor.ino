
//https://github.com/Rightech/ric-examples/blob/master/mqtt/arduino/103-json.ino
//https://www.iotsharing.com/2017/06/how-to-use-udpip-with-arduino-esp32.html
/* https://github.com/plapointe6/EspMQTTClient */
#include "wifi.h"
#include "allDefenition.h"
#include "HAL.h"
#include <ArduinoJson.h>



#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif





// define two tasks for Blink & AnalogRead
void TaskBlink( void *pvParameters );
void TaskAnalogReadA3( void *pvParameters );
void TaskTestPrint(void *pvParameters) ;
void TaskButton1( void *pvParameters );
void TaskUDP(void *pvParameters);


 
NetSetting_t netSetting;

bool state_btn  = true;

char str[]="qwe";
// the setup function runs once when you press reset or power the board
void setup() {
  
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
 pinMode(BUTTON_MASTER_MODE,INPUT_PULLUP);  
 pinMode(RELAY_PIN,OUTPUT);   
delay(3000)  ;


 jsonInit();

netSetting.local_ip = new IPAddress(192,168,0,1);
netSetting.subnet = new IPAddress(255,255,255,0);
netSetting.gateway = new IPAddress(192,168,0,1);
 
  Serial.println();

Serial.printf("Button status %d",digitalRead(BUTTON_MASTER_MODE) );
 if(!digitalRead(BUTTON_MASTER_MODE)){
  initWiFi_AP();
   }
 else{
  initWiFi_STA();
 }

 /*
  xTaskCreatePinnedToCore(
    TaskTestPrint
    ,  "TaskTestPrint"
    ,  1024  // Stack size
    ,  (void*)&str
    ,  2  // Priority
    ,  NULL 
    ,  ARDUINO_RUNNING_CORE);  
*/

//Усли нажата кнопка, то загружаемся в режима точки доступа

  xTaskCreatePinnedToCore(
    TaskWifiAp
    ,  "TaskWifiAp"
    ,  4096 // Stack size
    ,  NULL//Передаем состояние кнопки в качестве аргумента
    ,  1  // Priority
    ,  NULL 
    ,  ARDUINO_RUNNING_CORE);  


    
      xTaskCreatePinnedToCore(
    TaskButton1
    ,  "TaskButton1"
    ,  512 // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL 
    ,  ARDUINO_RUNNING_CORE); 

 
      xTaskCreatePinnedToCore(
    TaskUDP
    ,  "TaskUDP"
    ,  4096 // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL 
    ,  ARDUINO_RUNNING_CORE); 

}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/




/**/
void TaskTestPrint(void *pvParameters)  // This is a task.
{
//  (void) pvParameters;
  
/*
  AnalogReadSerial
  Reads an analog input on pin A3, prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A3, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/

  for (;;)
  {

    Serial.println("Hello World");
    Serial.println((char*)pvParameters);
    vTaskDelay(1000);  // one tick delay (15ms) in between reads for stability
  }
}

void TaskButton1( void *pvParameters ){
// Определяем режим работы GPIO с кнопкой   
  
   while( true ){
      bool st = digitalRead(BUTTON_MASTER_MODE);
   
// Проверка изменения состояния кнопки      
      if( st != state_btn ){
          state_btn = st;
          if( st == LOW ){
               Serial.println("Button pressed");
          }
          else {
               Serial.println("Button released");            
          }
      }
// Задержка, во время которой выполняются задачи с меньшим приоритетом      
      vTaskDelay(100);    
   }  
}