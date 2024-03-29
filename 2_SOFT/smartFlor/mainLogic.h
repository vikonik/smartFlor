#ifndef _LOGUC__H
#define _LOGUC__H

/*
Режим работы
	- автоматический
	- по рассписанию
*/
typedef enum{
	AUTO,
	SCHEDULED_WORK,
	MANUAL_WORK
}Regim_t;

/*
Состояние устройства
	- вкл
	- выкл
*/
typedef enum{
	DEVICE_OFF,
	DEVICE_ON
}DeviceState_t;
 
/*
Состояние реле
	-Вкл
	-Выкл
*/ 
typedef enum{
	RELAY_OFF,
	RELAY_ONN
}RelayState_t;

typedef struct{
	DeviceState_t 	deviceState;//DeviceState_t
	Regim_t 		currentRegim;//Regim_t
	RelayState_t	relayState;//RelayState_t
	double 			temperaturePorog_1;
	double			temperaturePorog_2;
	
}StatusDevice_t;

/*
Состояния конечного автомата
*/
typedef enum{
	STATE_CHECK_DEVICE_STATE,
	STATE_CHECK_REGIM,
	STATE_CHECK_TEMERATURE_SENSOR_1,
	STATE_CHECK_TEMERATURE_SENSOR_2,
	STATE_CHECK_SCHEDULER,
	STATE_MANUAL_WORK,
	STATE_RELAY_ON,
	STATE_RELAY_OFF
	
}MachineState_t;

void sound(uint16_t uSec) ;
void initLogick(void) ;

/**/
void relayOn(void);
void relayOff(void) ;
uint8_t readRelaystate(void) ;
/**/
double getTemperatureSensor_1(void) ;

/**/
double getTemperatureSensor_2(void) ;

/*
  Проверяем рассписание
  0-если сейчас не работаем
  1-усли настало время поработать
*/
uint8_t checkSheduller(void) ;
void TaskMain( void *pvParameters );

#endif
