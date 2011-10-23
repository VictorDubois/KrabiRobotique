#ifndef SERVO_H_INCLUDED
#define SERVO_H_INCLUDED

#include "pwm_handler.h"
#include "Angle.h"
#include "memory.h"
#include "variable.h"

/**@brief Classe utilisant un générateur de pwm pour controler un servo. Modèle : blue bird bms-620 (http://www.blue-bird-model.com).
Le servo a besoin d'une impulsion toutes les 20 ms environ et l'impulsion doit durer entre 1 et 2ms d'après http://en.wikipedia.org/wiki/Servomechanism#RC_servos.
Attention : il faut appeler initTimer _avant_ d'appeler le constructeur !
*/
class Servo
{
	PWMHandler pwm_handler;
    static Timer *timer;
    static const uint8_t numero_timer = NUMERO_TIMER_SERVO; // Tous les servos utilisent le même timer
    static const unsigned int frequence_timer = FREQUENCE_SERVO;


public:
    Servo(unsigned char OCx);
    static void initTimer();
	void goToAngle(Angle angle);
};

#endif // SERVO_H_INCLUDED
