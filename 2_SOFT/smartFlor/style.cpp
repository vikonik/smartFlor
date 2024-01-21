#include "style.h"
#include "style.h"
#include <Arduino.h>
const char style[] PROGMEM = "\
<style>\
html{\
  background-repeat: no-repeat;\
  background-position: center center;\
  background-attachment: fixed;\
  -webkit-background-size: cover;\
  -moz-background-size: cover;\
  -o-background-size: cover;\
  background-size: cover;\
}\
\
.nospan{ white-space: nowrap}\
.nospan:hover { white-space: normal }\
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
.container-button{\
    width: 90%;margin: 0 auto;\
    display: flex;\
    justify-content: center;\
    max-width: 90%;\
}\
.table-rutine{\
width: 600px;\
margin: auto;\
}\
.top-button{\
    display: flex;\
    flex-wrap: wrap;\
    justify-content: space-between;\
}\
.text{\
	font-size: 16px;\
	line-height: 26px;\
	text-align: center;\
}\
.disable-text{\
	font-size: 16px;\
	line-height: 26px;\
	text-align: center;\
	color: gray;\
}\
.button-submit{\
    background: #c9cdd1e5;\
    box-shadow: 5px 20px 50px rgba(138, 151, 160, 0.849);\
    border-radius: 6px;\
    font-size: 16px;\
    line-height: 26px;\
    text-align: center;\
    color: #000000;\
    margin-top: 10px;\
    margin-bottom: 10px;\
    margin-right: 1px; \
    padding-left: 10px;\
    padding-right: 10px;\
    width: 100%;\
	height:50px;\
   }\
.button-log{\
    background: #c9cdd1e5;\
    box-shadow: 5px 20px 50px rgba(138, 151, 160, 0.849);\
    border-radius: 5px;\
    padding-left: 15px;\
    padding-right: 15px;\
\
   }\
    \
.link{\
     text-decoration:none;\
     color: #000000;\
}\
.input{\
    width:100%;\
}\
.button{\
    width: 100%;\
	height:50px;\
    background: #c9cdd1e5;\
    box-shadow: 5px 20px 50px rgba(245, 229, 209, 0.76);\
    border-radius: 6px;\
    font-size: 16px;\
    color: black;\
    line-height: 20px;\
    margin-bottom: 5px;\
    text-align: center;\
    margin-top: 5px;\
\
\
}\
.button-rele{\
    margin-bottom: 10px;\
    background-color: rgb(143, 238, 99);\
    border-radius: 6px;\
    width: 100%;\
	min-height: 50px;\
}\
\
@media screen and (min-width: 750px) and (max-width: 800px){ \
.top{\
justify-content:center;     }\
}\
@media screen and (min-width: 800px) { \
.top{  \
display: flex;\
justify-content:center;     \
	}\
}\
.block-1{\
\
	\
     margin: 0px;\
    display: flex;\
    flex-direction: column; \
  }\
.block-2{\
    margin: 0px;\
       \
     padding: none;\
  }\
\
\
		@media screen and (max-width: 400px) {\
			.card{\
					width: 90%;\
					margin-bottom: 10px;\
				margin-left: auto;\
			margin-right:auto;	\
			}\
}\
\
@media screen and (min-width: 400px) {\
.card{\
		width: 45%;\
        margin-right: 20px;\
        margin-left: 20px;\
        line-height:normal;\
    }\
}	\
\
.card{\
border: black ridge 1px;	\
align-items: center;\
        display: flex;\
        justify-content:space-between;\
        flex-direction: column;\
}\
\
\
\
@media screen and (min-width: 400px) {\
.top_card{	\
		\
        margin: 0;\
        display: flex;\
    }   \
}	\
.checkbox{\
        display: flex;\
        padding-left: 20px;\
    }\
.mode_work{\
        border: black ridge 1px;\
        padding-bottom: 1px;\
        margin: 0px;\
        \
    }\
.input-number {\
    margin-bottom: 10px;\
    opacity: .8;\
	width: 90%;\
\
}\
\
\
.button-schedule:{\
	height:30px;\
	\
}\
/*\
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
	  */\
\
	  \
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
}\
</style>\
";
