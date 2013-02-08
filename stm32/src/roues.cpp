#include "roues.h"

Roues::Roues()
#ifdef STM32F10X_MD
    : gauche(3, GPIOC, GPIO_Pin_6), droite(4, GPIOC, GPIO_Pin_7)
#endif
#ifdef STM32F10X_CL
    : gauche(3, GPIOD, GPIO_Pin_3), droite(4, GPIOD, GPIO_Pin_4)
#endif
{
}
