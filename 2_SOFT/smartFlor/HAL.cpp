#include <ArduinoJson.h>
StaticJsonDocument<200> tempSens1_j;

void initTempSens1_j(){
tempSens1_j["SENSOR_1"] = "1";
tempSens1_j["TAMP_ON"] = 22;
tempSens1_j["TAMP_OFF"] = 28;
}


StaticJsonDocument<200> TempSens2_j;
void initTempSens2_j(){
TempSens2_j["SENSOR_2"] = "1";
TempSens2_j["TAMP_ON"] = 22;
TempSens2_j["TAMP_OFF"] = 28;
}

StaticJsonDocument <200>WorkMode_j;
void initWorkMode_j(){
WorkMode_j["WORK_MODE"] = "auto";
WorkMode_j["USE_ONLY_SENSOR_1"] = "true";
WorkMode_j["SOUND_STATUS"] = "off";
}


StaticJsonDocument <200>DayliRutine_j;
JsonArray monday = DayliRutine_j.createNestedArray("MONDAY");
JsonArray tusde = DayliRutine_j.createNestedArray("TUSDE");
JsonArray wensday = DayliRutine_j.createNestedArray("WENSDAY");
JsonArray ferstay = DayliRutine_j.createNestedArray("FERSDAY");
JsonArray friday = DayliRutine_j.createNestedArray("FRAIDAY");
JsonArray setaday = DayliRutine_j.createNestedArray("SETADY");
JsonArray sunday = DayliRutine_j.createNestedArray("SUNDAY");

/**/
void initDayliRutineArr_j(JsonArray *arr){
  for(int i = 0; i < 24; i++)
    arr->add("0");
}

/**/
void initDayliRutine_j(){
  initDayliRutineArr_j(&monday);
  initDayliRutineArr_j(&tusde);
  initDayliRutineArr_j(&wensday);
  initDayliRutineArr_j(&ferstay);
  initDayliRutineArr_j(&friday);
  initDayliRutineArr_j(&setaday);
  initDayliRutineArr_j(&sunday);
}



StaticJsonDocument <200>NetSetting_j;
void initNetSetting_j(){
NetSetting_j["ROUTER_ID"] = "";
NetSetting_j["ROUTER_PASS"] = "";
NetSetting_j["USE_DHCP"] = "false";
NetSetting_j["IP"] = "192.168.0.1",
NetSetting_j["MASK"] = "255.255.255.0";
NetSetting_j["GEAT_WAY"] = "192.168.0.1";
}


StaticJsonDocument <200>Time_j;
void initTime_j(){
Time_j["YEAR"]="";
Time_j["MANS"]="";
Time_j["DAY"]="",
Time_j["HH"]="";
Time_j["MM"]="";
Time_j["SS"]="";
}

StaticJsonDocument <200>BrokerSetting_j;
void initBrokerSetting_j(){
BrokerSetting_j["BROKER_ADDRES"] = "";
BrokerSetting_j["DEV_ID"] = "";
BrokerSetting_j["BROKER_LOGIN"] = "";
BrokerSetting_j["BROKER_PASS"] = "";
BrokerSetting_j["TOPIK_SEND"] = "";
BrokerSetting_j["TOPIK_RCV"] = "";
}



StaticJsonDocument <200>SecuritySetting_j;
void initSecuritySetting_j(){
SecuritySetting_j["NEW_PASSWORD"] = "";
SecuritySetting_j["SET_DEFAULT"] = "false";
SecuritySetting_j["CLEER"] = "false";
}

/**/
void jsonInit(){
 initTempSens1_j();
 initTempSens2_j();
 initWorkMode_j();
 initDayliRutine_j();
 initNetSetting_j();
 initTime_j();
 initBrokerSetting_j();
 initSecuritySetting_j();
  
}

/**/
