#include "PasswordPage.h"
#include "style.h"
#include <Arduino.h>
const char passwordPage_1[] PROGMEM = "\
<!DOCTYPE html>\
<html lang=\"en\">\
<head>\
    <meta charset=\"UTF-8\">\
    <meta name=\"viewport\" content=\"width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0\">\
    <title>Тёплый пол</title>\
    <link rel=\"stylesheet\" href=\"style-floor.css\">\
</head>\
<body>\
    <div class=\"container\">\
    <h3 class=\"heading\">Контроллер теплого пола <span class=\"nospan\">TimSim-mini</span></h3>\
    <p class=\"text\">Серийный номер ";
    
const char passwordPage_2[] PROGMEM = "    </p>\
    <form action=\"checkinputPassword\" class=\"text\">\
       Пароль  <input  type=\"password\" placeholder=\"Пароль\" name=\"devicePassword\"> \
       <button class=\"button-log\" type=\"log\">Войти</button> <br>\
      <label for=\"Запомнить это устройство и входить автоматически\">Запомнить это устройство и входить автоматически</label>\
       <input type=\"checkbox\"> \
    </form>\
    </div>\
</body>\
</html>";