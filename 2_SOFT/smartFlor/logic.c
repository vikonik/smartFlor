/*
Осноавная логика работы
*/
#include "stdint.h"
#include "logic.h"


#define RELAY_PIN

StatusDevice_t statusDevice;
MachineState_t machineState;
/*
Подача звукового сигнала
*/
void sound(uint16_t uSec){
	
	
}

/*
Инициализация
*/
void initLogick(void){
	statusDevice.currentRegim = AUTO;
	
}

/**/
void relayOn(void){
	
}

/**/
void relayOff(void){
	
	
}

/*
Читаем состояние реле
*/
uint8_t readRelaystate(void){
	
	return 0;
}

/**/
double getTemperatureSensor_1(void){
	
		return 0;
}

/**/
double getTemperatureSensor_2(void){
		return 0;
	
}

/*
Проверяем рассписание
0-если сейчас не работаем
1-усли настало время поработать
*/
uint8_t checkSheduller(void){
	return 0;	
	
}


/*
Конечный автомат работы терморегулятора
*/
uint8_t logic(void){
	
	switch(machineState){
		case STATE_CHECK_DEVICE_STATE:
			if(statusDevice.deviceState == DEVICE_OFF)
			{
				machineState = STATE_RELAY_OFF;
				break;
			}
			machineState = STATE_CHECK_REGIM;
		break;

		case STATE_CHECK_REGIM://Проверяем режим работы
			if(statusDevice.deviceState == AUTO){
				machineState = STATE_CHECK_TEMERATURE_SENSOR_1;
			}
			
			if(statusDevice.deviceState == SCHEDULED_WORK){
				machineState = STATE_CHECK_SCHEDULER;
			}		
		break;		
		
		case STATE_CHECK_SCHEDULER://Режим работы по рассписанию?
			if(statusDevice.deviceState == MANUAL_WORK){
				machineState = STATE_MANUAL_WORK;
				break;
			}				

			if(checkSheduller()){//Если наступило время в рассписании
				machineState = STATE_CHECK_TEMERATURE_SENSOR_1;
			}
			else{
				statusDevice.relayState = readRelaystate();
				if(statusDevice.relayState = relayOff)
					machineState = STATE_CHECK_DEVICE_STATE;
				else
					machineState = STATE_RELAY_OFF;
			}
			

		break;			
		
		case STATE_MANUAL_WORK:
			//Проверить на получение команды и уйти на вкл или выкл
		break;

		case STATE_CHECK_TEMERATURE_SENSOR_1:
			if(statusDevice.temperaturePorog_1 < getTemperatureSensor_1())
				machineState = STATE_CHECK_TEMERATURE_SENSOR_2;
		
		break;
		
		case STATE_CHECK_TEMERATURE_SENSOR_2:
			if(statusDevice.temperaturePorog_2 > getTemperatureSensor_2())
				machineState = STATE_RELAY_ON;
			else
				machineState = STATE_RELAY_OFF;
		break;
		
		case STATE_RELAY_ON:
			relayOn();
			machineState = STATE_CHECK_DEVICE_STATE;
		break;
		
		case STATE_RELAY_OFF:
			relayOff();
			machineState = STATE_CHECK_DEVICE_STATE;
		break;
		
		
		default: 
			machineState = STATE_CHECK_DEVICE_STATE;
		break;
	}
}