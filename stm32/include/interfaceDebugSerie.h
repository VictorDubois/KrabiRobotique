#ifndef INTERFACE_DEBUG_SERIE_H_INCLUDED
#define INTERFACE_DEBUG_SERIE_H_INCLUDED

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

//void ServosNumeriques_sendData(int data);

namespace UartDebug
{

void initClocksAndPortsGPIO();

void init(int baudRate);

void sendData(int data);

int receiveData();

int receiveStatusPacket(int* tableau);


}


#endif
