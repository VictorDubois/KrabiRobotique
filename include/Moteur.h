#ifndef MOTEUR_H_INCLUDED
#define MOTEUR_H_INCLUDED

#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "timer_handler.h"
#include "pwm_handler.h"

class Moteur{
    protected:
    PWMHandler pwm;

    public:
    Moteur(unsigned char OCx);
    void tourne(float rapport);
};

#endif // MOTEUR_H_INCLUDED
