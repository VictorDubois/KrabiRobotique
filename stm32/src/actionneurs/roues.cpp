#include "roues.h"

Roues::Roues()
    : gauche(TIM4, 2, GPIOD, GPIO_Pin_3)
    , droite(TIM4, 4, GPIOD, GPIO_Pin_4)
{
}
