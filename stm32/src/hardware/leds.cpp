#include "leds.h"

// allume ou éteint une LED
void allumerLED()
{
    Led::setOn(0);
}

void eteindreLED()
{
    Led::setOff(0);
}

void allumerLED2()
{
    Led::setOn(1);
}

void eteindreLED2()
{
    Led::setOff(1);
}

bool Led::ledOn[LED_NUMBER] = {0};

void Led::toggle(int index)
{
    if (index>=0 and index<LED_NUMBER)
    {
        if (ledOn[index])
            setOff(index);
        else
            setOn(index);
    }
}

void Led::setOn(int index)
{
    if (index>=0 and index<LED_NUMBER)
        ledOn[index] = true;

    switch(index)
    {
        case 0:
        #ifdef ROBOTHW
            #ifdef STM32F10X_MD // pour la STM32 H103 2014 v1 :
                GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_RESET); // LED verte
            #endif
            #ifdef STM32F10X_CL // pour la STM32 H107 2013 v2 :
                GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_SET); // LED verte
            #endif
            #ifdef STM32F40_41xxx // pour la STM32 H405 2014 v1 :
                GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_RESET); // LED verte
            #endif
        #endif
        #ifndef ROBOTHW
            turnLed(0, 1);
        #endif
            break;

        case 1:
        #ifdef ROBOTHW
            #ifdef STM32F10X_MD // pour la STM32 H103 2014 v1 :
               // Pas de LED jaune sur le H103 :'(
            #endif
            #ifdef STM32F10X_CL // pour la STM32 H107 2013 v2 :
                GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_SET); // LED jaune
            #endif

        #else
            turnLed(1, 1);
        #endif
            break;

        default:
            break;
    }
}

void Led::setOff(int index)
{
    if (index>=0 and index<LED_NUMBER)
        ledOn[index] = false;

    switch(index)
    {
        case 0:
        #ifdef ROBOTHW
            #ifdef STM32F10X_MD // pour la STM32 H103 2014 v1 :
                GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_SET); // LED verte
            #endif
            #ifdef STM32F10X_CL // pour la STM32 H107 2013 v2 :
                GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_RESET); // LED verte
            #endif
            #ifdef STM32F40_41xxx // pour la STM32 H405 2014 v1 :
                GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_SET); // LED verte
            #endif
        #else
            turnLed(0, 0);
        #endif
            break;

        case 1:
        #ifdef ROBOTHW
            #ifdef STM32F10X_CL // pour la STM32 H107 2013 v2 :
                GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_RESET); // LED jaune
            #endif
        #else
            turnLed(1, 0);
        #endif
            break;
        default:
            break;
    }
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
