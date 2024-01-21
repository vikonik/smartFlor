#pragma once
#ifndef _DEVICEINFO_H
#define _DEVICEINFO_H

#define ADDR_deviceID 0
#define DEFAULT_DATA 0//Ключ. используем данные по умолчанию
#define USER_DATA 1//Ключ. используем пользовательские данные 

//Режим работы устройства
//Точка доступа или клиент
typedef enum{
  MODE_AP,
  MODE_STA
}WorkMode_t;

//Режим работы устройства
typedef enum{
  DEVICE_WORK_MODE_FUTO,
  DEVICE_WORK_MODE_TIMRT,
  DEVICE_WORK_MODE_MANUAL
}DeviceWorkMode_t;

//Дни недели
typedef enum{
  SUDAY,
  MONDAY,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY
}WeekDay_t;


//Информация об устройстве
typedef struct{
	uint64_t deviceID;
	uint8_t mac[6];//Биилиотечная функция возвращает String
	char userLogin[16];
	char userPass[16];//пароль для входа на устройство
	uint32_t keyUseUserData;//Если были изменены данные по умолчанию, то здесь 1
	char apSSID[16];//SSID точки доступа
	char apPass[16];
	char routerSSID[16];//SSID роутера
	char routerPass[16] ;
	char brockerAddr[64];//адрес брокера
	char brockerID[64];//ID устройства у брокера
	char brockerLogin[64];//логин для подключения к брокеру
	char brockerPass[32];//пароль для подключения к брокеру
	char brockerTopickOut[64];//топик для отправки сообщения к брокеру
	char brockerTopikIn[64];//топик для получеиня сообщения от брокера
	uint32_t keyUseUserSetting;//Если были изменены данные по умолчанию, то здесь 1
  uint32_t keyFerstStart;//Ключ показывает что это первый старт или продолжение работы 0xDEADBEEF
  WorkMode_t workMode;
  //Дописываем переменные для работы устройства
  DeviceWorkMode_t deviceWorkMode;//Режим работы
  uint8_t useOnluSensor_1;//Использовать только датчик температуры №1
  uint8_t useSound;//Звуковая сигнализация Вклд/Выкл
  int8_t tempH_sensor_1;
  int8_t tempL_sensor_1;
  int8_t tempH_sensor_2;
  int8_t tempL_sensor_2;
  uint8_t rutine[7][24];
}DeviceInfo_t;

extern DeviceInfo_t deviceInfo;

void checkFerstStartInit();
void getDeviceInfo();
void getDeviceInfoData();
void getDeviceSetting();
void printDeviceSetting();
void setDefaultSetting();

#endif
