//#include "stdint.h"
//
////#include <WiFi.h>
////#include <WiFiUdp.h>
//
///* WiFi network name and password 
//const char * ssid = "Vikonik";
//const char * pwd = "88115221421";
//*/
//// IP address to send UDP data to.
//// it can be ip address of the server or 
//// a network broadcast address
//// here is broadcast address
//const char * udpAddress = "192.168.0.104";
//const int udpPort = 44444;
//
////create UDP instance
//
//void TaskUDP(void *pvParameters) {
//    (void) pvParameters;
//    
//    WiFiUDP udp;
////Раньше здесь была настройка WiFi
//
//
//while(1){
//  //data will be sent to server
//  uint8_t buffer[50] = "hello world";
//  //This initializes udp and transfer buffer
// // udp.beginPacket(udpAddress, udpPort);
// // udp.write(buffer, 11);
// // udp.endPacket();
//  memset(buffer, 0, 50);
//  //processing incoming packet, must be called before reading the buffer
//  udp.parsePacket();
//  //receive response from server, it will be HELLO WORLD
//  if(udp.read(buffer, 50) > 0){
//    Serial.print("Server to client: ");
//    Serial.println((char *)buffer);
//  }
//  //Wait for 1 second
////  delay(1000);
////Serial.println("UDP");
//  vTaskDelay(10); 
//}
//}
//