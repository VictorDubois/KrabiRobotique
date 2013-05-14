#include "leds.h"
// allume ou éteint une LED
void allumerLED()
{
#ifdef ROBOTHW
    GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_SET); // LED verte
    #endif
}

void eteindreLED()
{
#ifdef ROBOTHW
    GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_RESET); // LED verte
#endif
}

void allumerLED2()
{
#ifdef ROBOTHW
    GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_SET);
#endif
}
void eteindreLED2()
{
#ifdef ROBOTHW
    GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_RESET);
#endif
}
