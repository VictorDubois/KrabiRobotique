#include "leds.h"
// allume ou éteint une LED
void allumerLED()
{
#ifdef STM32F10X_MD // stm32 h103
    GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_RESET);
#endif
#ifdef STM32F10X_CL // stm32 h107
    GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_SET); // LED verte
#endif
}

void eteindreLED()
{
#ifdef STM32F10X_MD // stm32 h103
    GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_SET);
#endif
#ifdef STM32F10X_CL // stm32 h107
    GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_RESET); // LED verte
#endif
}

// 2ème LED du stm h107 (LED jaune)
#ifdef STM32F10X_CL
void allumerLED2()
{
    GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_SET);
}
void eteindreLED2()
{
    GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_RESET);
}
#endif
