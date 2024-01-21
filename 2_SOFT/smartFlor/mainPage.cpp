#include "mainPage.h"
#include "style.h"
#include <Arduino.h>
const char mainPage_1[] PROGMEM = "\
<!DOCTYPE html>\
<html lang=\"en\">\
<head>\
    <meta charset=\"UTF-8\">\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
    <title>Controller</title>\
    <link rel=\"stylesheet\" href=\"style.css\">\
</head>\
<body>\
    <div class=\" container\">\
        <div class=\"top\">\
            <div class=\"block-1\">\
                <div class=\"top_card\">\
                    <div class=\"card\">\
                    <form action=\"newDataTempSensor_1\" class=\"text\" metod=\"get\">\
                        <h4 class=\"heading-mini\">Датчик №1</h4>\
                        <p class=\"text\">25 &#176;С</p>\
                        <p class=\"text\">Температура выключения</p>\
                        <input class=\"input-number\" type=\"number\" step=\"1\" min=\"-60\" max=\"100\" value=\"";
                       
                        //60
const char mainPage_2[] PROGMEM = "\"\                        
                        name=\"tempSensor_1_t_up\">\
                        <p class=\"text\">Температура включения</p>\
                        <input class=\"input-number\" type=\"number\" step=\"1\" min=\"-60\" max=\"100\" value=\"";
                        
                        //-60
const char mainPage_3[] PROGMEM = "\"\                        
                         name=\"tempSensor_1_t_dn\">\
                        <button type=\"submit\" class=\"button-submit\">Сохранить</button>\
					          </form>\
                    </div>\
                    <div class=\"card\">\
                         <form action=\"newDataTempSensor_2\" class=\"text\">\
                            <h4 disabled class=\"heading-mini\">Датчик №2</h4>\
                            <p disable dclass=\"text\">25 &#176;С </p>\
                            <p class=\"text\">Температура выключения</p>\
                            <input class=\"input-number\"type=\"number\" step=\"1\" min=\"-60\" max=\"100\" value=\"";

                           
                            //60
const char mainPage_4[] PROGMEM = "\"\                             
                             name=\"tempSensor_2_t_up\"  >\
                            <p class=\"text\">Температура включения</p>\
                            <input class=\"input-number\" type=\"number\" step=\"1\" min=\"-60\" max=\"100\" value=\"";
                            
                            //-60
const char mainPage_5[] PROGMEM = "\"\                             
                             name=\"tempSensor_2_t_dn\">\
                            <button type=\"submit\" class=\"button-submit\">Сохранить</button>\
					          </form>\                            
                    </div>\
                </div>\
            </div>\
            <div class=\"block-2\">\
              <form action=\"workRegim\" metod=\"get\">\
                    <button type=\"button \" class=\"button-rele\">Реле ВКЛ</button>\
                    <div class=\"mode_work\">\
                    <h4 class=\"heading-mini\">Режим работы</h4>\
                    <input type=\"radio\" name=\"mode\" value=\"1\" checked>Автоматический  <br>\
                    <input type=\"radio\" name=\"mode\" value=\"2\">По таймеру<br>\
                    <input type=\"radio\" name=\"mode\" value=\"3\">Ручной  <br><br>\
                    <input type=\"checkbox\" id=\"sensor_1\" name=\"sensor_1\" value=\"sens\">\
                    <label for=\"sensor_1\">Только датчик №1</label> <br>\
                    <input type=\"checkbox\" id=\"sensor_2\" name=\"sensor_2\" value=\"sound\">\  
                    <label for=\"sensor_2\">Отключить звуковую сигнализацию</label>\     
                    <button type=\"submit\" class=\"button-submit\">Сохранить</button>\       
              </form>\
            </div>\
                <button type=\"button\" class=\"button\"  > <a class=\"link\" href=\"rutine.html\">Расписание</button><br>\
                <button type=\"button\" class=\"button-submit\"> <a class=\"link\" href=\"net_setting.html\"> Настройка</a></button><br>\
                </div>\
          </div>\
        </div>\
</body>\
</html>\
";
