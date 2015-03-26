#include "roues.h"

Roues::Roues()
// Pour la v1 :
  //  : droite(TIM4, 4, GPIOB, GPIO_Pin_9, GPIOD, GPIO_Pin_4),gauche(TIM4, 2, GPIOB, GPIO_Pin_7, GPIOD, GPIO_Pin_3)
 // pour la v2 :
    //: droite(TIM5, 4, GPIOA, GPIO_Pin_3, GPIOD, GPIO_Pin_4), gauche(TIM5, 1, GPIOA, GPIO_Pin_0, GPIOD, GPIO_Pin_3)
 // pour la v3 :
#ifdef STM32F10X_MD // pour la STM32 H103 2014 v1 :
    : droite(TIM2, 2, GPIOA, GPIO_Pin_0, GPIOA, GPIO_Pin_4), gauche(TIM2, 1, GPIOA, GPIO_Pin_1, GPIOC, GPIO_Pin_4)
#endif
#ifdef STM32F10X_CL // pour la STM32 H107 2013 v2 :
    : droite(TIM5, 4, GPIOA, GPIO_Pin_3, GPIOD, GPIO_Pin_4), gauche(TIM5, 2, GPIOA, GPIO_Pin_1, GPIOD, GPIO_Pin_6)
#endif
#ifdef STM32F40_41xxx // pour la STM32 H405 2014 v1 :
    : droite(TIM2, 2, GPIOA, GPIO_Pin_0, GPIOA, GPIO_Pin_4), gauche(TIM2, 1, GPIOA, GPIO_Pin_1, GPIOC, GPIO_Pin_4)
#endif

{
}
