#include "PasswordPage.h"
#include "style.h"
#include <Arduino.h>
const char passwordPage[] PROGMEM = "\
<!DOCTYPE html>\
<html lang=\"en\">\
<head>\
    <meta charset=\"UTF-8\">\
    <meta name=\"viewport\" content=\"width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0\">\
    <title>Document</title>\
    <link rel=\"stylesheet\" href=\"style-floor.css\">\
</head>\
<body>\
    <div class=\"container\">\
    <h3 class=\"heading\">Контролёр теплого пола TimSim-mini</h3>\
    <p class=\"text\">Серийный номер №*****</p>\
    <form action=\"#\" class=\"text\">\
       Пароль  <input  type=\"password\" placeholder=\"Пароль\"> \
       <button class=\"button-log\" type=\"log\">Войти</button> <br>\
      <label for=\"Запомнить это устройство и входить автоматически\">Запомнить это устройство и входить автоматически</label>\
       <input type=\"checkbox\"> \
    </form>\
    </div>\
</body>\
</html>";