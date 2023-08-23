#include <Arduino.h>
#include "style.h"

const char style[] PROGMEM = "\
<style>\
.heading{\
    font-size: 36px;\
text-align: center;\
}\
.container{\
    width: 1140px;margin: 0 auto;\
    background-color: rgb(245, 229, 209);\
    padding: 100px;\
}\
.text{font-size: 16px;\
line-height: 26px;\
color: #1F3F68;\
text-align: center;\
}\
.button-submit{background: #5A98D0;\
    box-shadow: 5px 20px 50px rgba(16, 112, 177, 0.2);\
    border-radius: 10px;\
    font-size: 16px;\
    font-weight: 500px;\
    line-height: 26px;\
    line-height: 26px;\
    text-align: center;\
    color: #FFFFFF;\
    text-transform: uppercase;\
    }\
</style>";