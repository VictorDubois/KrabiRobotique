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

void moveToAtSpeed(uint16_t position = 0x0000, uint16_t vitesse = 0x0000, uint8_t servo = 0xfe);
void moveTo(uint16_t position = 0x0000, uint8_t servo = 0xfe);
void moveAtSpeed(uint16_t vitesse = 0x0000, uint8_t servo = 0xfe);
void setLedState(uint8_t ledOn = 0, uint8_t servo = 0xfe);

void setMinimumAngle(uint16_t angle = 0x0000, uint8_t servo = 0xfe);

void setMaximumAngle(uint16_t angle = 0x0000, uint8_t servo = 0xfe);

void setTorqueLimite(uint16_t torque = 0x0000, uint8_t servo = 0xfe); // dans la RAM
void setMaxTorque(uint16_t torque = 0x0000, uint8_t servo = 0xfe); // EEPROM, automatiquement mis dans la RAM au démarrage


}


#endif
