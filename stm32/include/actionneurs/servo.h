#ifndef SERVO_H
#define SERVO_H

#ifdef ROBOTHW

#include "pwmHandler.h"
#include "angle.h"
#include "memory.h"
#include "constantes.h"

/** @brief Classe utilisant un générateur de pwm pour controler un servo. Modèle : blue bird bms-620 (http://www.blue-bird-model.com).
Le servo a besoin d'une impulsion toutes les 20 ms environ et l'impulsion doit durer entre 1 et 2ms d'après http://en.wikipedia.org/wiki/Servomechanism#RC_servos.
Attention : il faut appeler initTimer _avant_ d'appeler le constructeur !
*/
class Servo
{
    private:

        /// @brief pwm_handler Objet gérant le pwm associé au servomoteur
        PWMHandler pwm_handler;

        /// @brief timer Timer utilisé par le servo
        Timer* m_timer;

        // rapport cyclique minimal
        float m_RC0degre;

        // m_coefRC = (RC180degres - RC0degre)/180
        // permet d'obtenir le rapport cyclique pour un angle grace à la formule m_coefRC*(angle en degrés)+m_RC0degre
        float m_coefRC;

    public:

        /// @brief Servo(numéro channel) Constructeur du servo
        // on donne le rapport cyclique de l'angle minimal (0 degré) et celui de l'angle maximal (180 degrés)
        Servo(Timer* timer, unsigned char OCx, float RC0degre, float RC180degres);

        /// @brief ~Servo() Destructeur du servo
        ~Servo();

        /// @brief initTimer Pour initialiser le timer et créer les PWM
        // fonction obsolete vu que plusieurs timers utilisent des pwm
  //      static void initTimer();

        // initialise la pin du servo
        static void initPin(GPIO_TypeDef* GPIOx, uint16_t pinX);

        /// @brief goToAngle Fait tourner le servo vers cet angle
        void goToAngle(Angle angle);

        /// @brief shutDownServo Passe le servo en roue libre (enfin si ça fonctionne)
        void shutDownServo();
};

#endif // ROBOTHW

#endif // SERVO_H
