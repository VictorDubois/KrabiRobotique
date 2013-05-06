#ifndef MOTEUR_H
#define MOTEUR_H

#include "pwmHandler.h"

/// @brief Classe utilisé pour gérer les moteurs (Souvent par héritage).
class Moteur
{
    protected:

        PWMHandler pwm;

    public:

        /// @brief constructeur pour initialiser les moteurs
        /// @param TIMx est le timer du moteur
        /// @param OCx est le numéro du channel
        /// GPIOx_pwm et GPIO_Pin_pwm pour définir la pin du pwm
        Moteur(TIM_TypeDef* TIMx, unsigned char OCx, GPIO_TypeDef* GPIOx_pwm, uint16_t GPIO_Pin_pwm);

        /// @brief Fonction permettant de faire tourner le moteur.
        /// @param rapport est l'angle de rotation du moteur pour le servoMoteur
        void tourne(float rapport);
};

#endif // MOTEUR_H
