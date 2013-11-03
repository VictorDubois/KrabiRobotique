#include "leds.h"
// allume ou éteint une LED
void allumerLED()
{
#ifdef ROBOTHW
    GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_SET); // LED verte
#endif
#ifndef ROBOTHW

    turnLed(0, 1);
#endif
}

void eteindreLED()
{
#ifdef ROBOTHW
    GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_RESET); // LED verte
#endif
#ifndef ROBOTHW
    turnLed(0, 0);
#endif
}

void allumerLED2()
{
#ifdef ROBOTHW
    GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_SET);
#endif
#ifndef ROBOTHW
    turnLed(1, 1);
#endif
}
void eteindreLED2()
{
#ifdef ROBOTHW
    GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_RESET);
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
