#include <Arduino.h>
#include "style.h"

const char style[] PROGMEM = "\
<style>\
.nospan{ white-space: nowrap} .nospan:hover { white-space: normal }\
.heading{\
font-size: 36px;\
text-align: center;\
}\
.heading-mini{text-decoration: none ;\
text-align: center;\
}\
.container{\
    width: 80%;margin: 0 auto;\
    background-color: rgb(245, 229, 209, 0.8);\
    padding: 10px;\
}\
.container_button{\
    width: 63%;margin: 0 auto;\
    display: flex;\
    justify-content: center;\
   flex-wrap: wrap;\
    max-width: 63%;\
}\
.top-button{\
    display: flex;\
    flex-wrap: wrap;\
    justify-content: space-between;\
}\
.text{font-size: 16px;\
line-height: 26px;\
text-align: center;\
}\
.button-submit{\
    background: #c9cdd1e5;\
    box-shadow: 5px 20px 50px rgba(138, 151, 160, 0.849);\
    border-radius: 6px;\
    font-size: 16px;\
    line-height: 26px;\
    text-align: center;\
    color: #000000;\
     margin-top: 35px;\
     margin-bottom: 15px;\
     margin-right: 25px; \
     padding-left: 10px;\
     padding-right: 10px;\
     min-width: 140px;\
   }\
   .button-log{\
    background: #c9cdd1e5;\
    box-shadow: 5px 20px 50px rgba(138, 151, 160, 0.849);\
    border-radius: 5px;\
    padding-left: 15px;\
    padding-right: 15px;\
   }\
   .link{\
     text-decoration:none;\
     color: #000000;\
}\
.input{\
    width: 300px;\
}\
.button{\
    max-width: 150px;\
    background: #c9cdd1e5;\
    box-shadow: 5px 20px 50px rgba(245, 229, 209, 0.76);\
    border-radius: 6px;\
    font-size: 16px;\
    color: black;\
    line-height: 20px;\
   margin-bottom: 20px;\
    text-align: center;\
    margin-top: 20px;\
}\
.button-rele{\
    margin-bottom: 10px;\
    background-color: rgb(143, 238, 99);\
    border-radius: 6px;\
    min-width: 150px;\
}\
    display: flex;\
    justify-content:center;\
    }\
    .block-1{\
    margin: 0px;\
    display: flex;\
    flex-direction: column;  \
  }\
  .block-2{\
    margin: 0px;\
     padding: none;\
  }\
   .card{\
        border: black ridge 1px;\
        margin-right: 20px;\
        margin-left: 20px;\
        line-height:normal;\
       display: flex;\
       justify-content:space-between;\
       flex-direction: column;\
    align-items: center;\
    }\
 .top_card{\
        margin: 0;\
        display: flex;\
    }\   
    .checkbox{\
        display: flex;\
        padding-left: 20px;\
    }\
    .mode_work{\
        border: black ridge 1px;\
        padding-bottom: 25px;\
        margin: 0px;\ 
    }\
   .input-number {\
    margin-bottom: 10px;\
    opacity: .8;\
}\   
.table{\
    text-align: center;\
}\
.button-schedule:hover{\
        box-shadow: 0 1px 3px rgba(0, 0, 0, 0.2);\
      }\
.button-schedule:hover {\
  background: #39a1f4;\
      }\
  .button-schedule:active {\
        box-shadow: inset 0 1px 3px rgba(0, 0, 0, 0.2);\
        text-shadow: 0 1px 3px rgba(0, 0, 0, 0.2);\
      }\
      .button_with_№{\
    display: flex;\
    line-height: 40px;\
    padding-left: 20px;\
    padding-right: 20px;\
    min-width: 110px;\
    font-size: 16px;\
    background-color: #91fafacb;\
   margin-bottom: 20px;\
    /*border: none;*/\
    outline: none;\
    display: inline-block;\
    text-align: center;\
}\
.button_with_№:active{\
background-color: #39a2c2ee;\
}\
.big_container_button{\
    width: 63%;margin: 0 auto;\
    display: flex;\
    max-width: 63%;\
flex-direction: column;\
flex-wrap: wrap;\
align-content: space-around;\
justify-content: space-around;\
</style>\
";
