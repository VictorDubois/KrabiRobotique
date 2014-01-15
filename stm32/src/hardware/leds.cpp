#include "leds.h"
// allume ou éteint une LED
void allumerLED()
{
#ifdef ROBOTHW
    #ifdef STM32F10X_MD // pour la STM32 H103 2014 v1 :
        GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_SET); // LED verte
    #endif
    #ifdef STM32F10X_CL // pour la STM32 H107 2013 v2 :
        GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_SET); // LED verte
    #endif

#endif
#ifndef ROBOTHW

    turnLed(0, 1);
#endif
}

void eteindreLED()
{
#ifdef ROBOTHW
    #ifdef STM32F10X_MD // pour la STM32 H103 2014 v1 :
        GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_RESET); // LED verte
    #endif
    #ifdef STM32F10X_CL // pour la STM32 H107 2013 v2 :
        GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_RESET); // LED verte
    #endif
#endif
#ifndef ROBOTHW
    turnLed(0, 0);
#endif
}

void allumerLED2()
{
#ifdef ROBOTHW
    #ifdef STM32F10X_MD // pour la STM32 H103 2014 v1 :
       // Pas de LED jaune sur le H103 :'(
    #endif
    #ifdef STM32F10X_CL // pour la STM32 H107 2013 v2 :
        GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_SET); // LED jaune
    #endif

#endif
#ifndef ROBOTHW
    turnLed(1, 1);
#endif
}
void eteindreLED2()
{
#ifdef ROBOTHW
        #ifdef STM32F10X_CL // pour la STM32 H107 2013 v2 :
        GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_RESET); // LED jaune
    #endif
#endif
#ifndef ROBOTHW
    turnLed(1, 0);
#endif
}

#ifndef ROBOTHW
void turnLed(int led, bool turnOn)
{
    if(led>=NB_LED)
    {
        //ERREUR!!!
        return;
    }
    ledIsOn[led] = turnOn;
}

bool isLedOn(int led)
{
    if(led>=NB_LED)
    {
        //ERREUR!!!
    }
    return ledIsOn[led];
}

#endif
