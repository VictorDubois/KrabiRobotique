#ifndef MOTEUR_H_INCLUDED
#define MOTEUR_H_INCLUDED

#include "variable.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "timer_handler.h"
#include "pwm_handler.h"

/**@brief Classe utilisé pour gérer les moteurs (Souvent pas héritage). */
class Moteur{
    protected:
        PWMHandler pwm;

    public:
        Moteur(unsigned char OCx);
        /**@brief Fonction permettant de faire tourner le moteur.
         *@param rapport est l'angle de rotation du moteur pour le servoMoteur */
        void tourne(float rapport);
};

#endif // MOTEUR_H_INCLUDED
