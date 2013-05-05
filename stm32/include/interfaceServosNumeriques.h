#ifndef INTERFACE_SERVOS_NUMERIQUES_H_INCLUDED
#define INTERFACE_SERVOS_NUMERIQUES_H_INCLUDED

#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "ax12api.h"

void ServosNumeriques_sendData(int data);

namespace ServosNumeriques
{

void initClocksAndPortsGPIO();

void initUART(int baudRate);

void sendMode();
void receiveMode();

void sendData(int data);

int receiveData();

int receiveStatusPacket(int* tableau);

void moveToAtSpeed(uint16_t position, uint16_t vitesse, uint8_t servo);
void moveTo(uint16_t position, uint8_t servo);
void moveAtSpeed(uint16_t vitesse, uint8_t servo);
void setLedState(uint8_t ledOn, uint8_t servo);

void setMinimumAngle(uint16_t angle, uint8_t servo);
void setMaximumAngle(uint16_t angle, uint8_t servo);
void setBaudRate(uint8_t baudRate, uint8_t servo);

void setTorqueLimite(uint16_t torque, uint8_t servo); // dans la RAM
void setMaxTorque(uint16_t torque, uint8_t servo); // EEPROM, automatiquement mis dans la RAM au démarrage


}


#endif
