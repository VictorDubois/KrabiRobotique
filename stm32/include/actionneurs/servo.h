#ifndef SERVO_H
#define SERVO_H

#ifdef ROBOTHW

#include "pwmHandler.h"
#include "angle.h"
#include "memory.h"
#include "constantes.h"

/** @brief Classe utilisant un générateur de pwm pour controler un servo. Modèle : blue bird bms-620 (http://www.blue-bird-model.com).
Le servo a besoin d'une impulsion toutes les 20 ms environ et l'impulsion doit durer entre 1 et 2ms d'après http://en.wikipedia.org/wiki/Servomechanism#RC_servos.
*/
class Servo
{
    private:

        /// @brief pwm_handler Objet gérant le pwm associé au servomoteur
        PWMHandler pwm_handler;

        /// @brief timer Timer utilisé par le servo
        Timer* m_timer;

        /// @brief frequence_timer Fréquence des PWM utilisés pour les servos
        static const unsigned int frequence_timer = FREQUENCE_SERVO;

    public:

        /// @brief Constructeur du servo
        /// on fournit le timer et le numéro du channel
        /// ne pas oublier d'initialiser la pin avec la fonction PWMHandler::initialiserPinPourPWM()
        Servo(Timer* timer, unsigned char OCx);

        /// @brief ~Servo() Destructeur du servo
        ~Servo();

        /// @brief goToAngle Fait tourner le servo vers cet angle
        void goToAngle(Angle angle);

        /// @brief shutDownServo Passe le servo en roue libre (enfin si ça fonctionne)
        void shutDownServo();
};

#endif // ROBOTHW

#endif // SERVO_H
