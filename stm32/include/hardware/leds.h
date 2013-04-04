#ifndef LEDS_H_INCLUDED
#define LEDS_H_INCLUDED

#include "stm32f10x_gpio.h"
// allume ou éteint une LED
void allumerLED();
void eteindreLED();

// 2ème LED du stm h107 (LED jaune)
#ifdef STM32F10X_CL
void allumerLED2();
void eteindreLED2();
#endif


#endif // LEDS_H_INCLUDED
