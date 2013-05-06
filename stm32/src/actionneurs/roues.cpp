#include "roues.h"

Roues::Roues()
// Pour la v1 :
  //  : droite(TIM4, 4, GPIOB, GPIO_Pin_9, GPIOD, GPIO_Pin_4),gauche(TIM4, 2, GPIOB, GPIO_Pin_7, GPIOD, GPIO_Pin_3)
 // pour la v2 :
    : droite(TIM5, 4, GPIOA, GPIO_Pin_3, GPIOD, GPIO_Pin_4), gauche(TIM5, 1, GPIOA, GPIO_Pin_0, GPIOD, GPIO_Pin_3)
{
}
