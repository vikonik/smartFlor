
//https://github.com/Rightech/ric-examples/blob/master/mqtt/arduino/103-json.ino
//https://www.iotsharing.com/2017/06/how-to-use-udpip-with-arduino-esp32.html
/* https://github.com/plapointe6/EspMQTTClient */
#include "wifi.h"

#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif

// define two tasks for Blink & AnalogRead
void TaskBlink( void *pvParameters );
void TaskAnalogReadA3( void *pvParameters );
void TaskTestPrint(void *pvParameters) ;
// the setup function runs once when you press reset or power the board
void setup() {
  
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
delay(3000)  ;
 
  xTaskCreatePinnedToCore(
    TaskTestPrint
    ,  "TaskTestPrint"
    ,  1024  // Stack size
    ,  NULL
    ,  2  // Priority
    ,  NULL 
    ,  ARDUINO_RUNNING_CORE);  


  xTaskCreatePinnedToCore(
    TaskWifiAp
    ,  "TaskWifiAp"
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
  (void) pvParameters;
  
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
    vTaskDelay(1000);  // one tick delay (15ms) in between reads for stability
  }
}