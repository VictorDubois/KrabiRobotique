#ifndef MOTEUR_H
#define MOTEUR_H

#include "pwmHandler.h"

/**@brief Classe utilisé pour gérer les moteurs (Souvent par héritage). */
class Moteur
{
    protected:

        PWMHandler pwm;

    public:

        Moteur(unsigned char OCx);

        /**@brief Fonction permettant de faire tourner le moteur.
         *@param rapport est l'angle de rotation du moteur pour le servoMoteur */
        void tourne(float rapport);
};

#endif // MOTEUR_H
