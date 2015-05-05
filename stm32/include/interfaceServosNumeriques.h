#ifndef INTERFACE_SERVOS_NUMERIQUES_H_INCLUDED
#define INTERFACE_SERVOS_NUMERIQUES_H_INCLUDED

#ifdef STM32F40_41xxx
    #include "stm32f4xx_rcc.h"
    #include "stm32f4xx_gpio.h"
    #include "stm32f4xx_usart.h"
#elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
    #include "stm32f10x_rcc.h"
    #include "stm32f10x_gpio.h"
    #include "stm32f10x_usart.h"
#endif

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

void moveToAtSpeed(uint16_t position, uint16_t vitesse, uint8_t servo); // vitesse min : 0x0000 (stupide), vitesse max : 0x07ff
void moveTo(uint16_t position, uint8_t servo); // position min : 0x0000, position max : 0x03ff
//void moveAtSpeed(uint16_t vitesse, uint8_t servo); // définie la vitesse des prochains mouvements
void moveAtSpeed(uint16_t vitesse, uint8_t servo, bool sensTrigoSiContinue = false); // définie la vitesse des prochains mouvements. Si rotation continue : de 0 à 1023 dans un sens, de 1024 à 2047 dans l'autre
void setLedState(uint8_t ledOn, uint8_t servo);

void setMinimumAngle(uint16_t angle, uint8_t servo);
void setMaximumAngle(uint16_t angle, uint8_t servo);
void setBaudRate(uint8_t baudRate, uint8_t servo);

void setTorqueLimite(uint16_t torque, uint8_t servo); // dans la RAM
void setMaxTorque(uint16_t torque, uint8_t servo); // EEPROM, automatiquement mis dans la RAM au démarrage

void changeContinuousRotationMode(uint8_t servo, bool continuous = true, uint8_t step = 0);//Rotation continue/angle précis. step sert à n'envoyer qu'un packet à la fois

int getPosition(uint8_t servo);
}


#endif
