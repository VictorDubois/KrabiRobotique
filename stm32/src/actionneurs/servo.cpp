#include "servo.h"

#ifdef ROBOTHW

Servo::Servo(Timer* timer, unsigned char OCx)
    : pwm_handler(timer, OCx), m_timer(timer)
{

}

void Servo::goToAngle(Angle angle)
{
	// Convertir angle en signal
	float pulseWidth = ANGLETOPULSE(angle);

    // Donner la rapport au PWM
	pwm_handler.setPulseWidth(pulseWidth);

}

void Servo::shutDownServo()
{
    pwm_handler.setPulseWidth(0);
}

Servo::~Servo()
{

}

#endif // ROBOTHW
