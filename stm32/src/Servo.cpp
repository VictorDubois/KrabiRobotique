#include "Servo.h"

#ifdef ROBOTHW

Servo::Servo(unsigned char OCx) : pwm_handler(timer, OCx)
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

void Servo::initTimer()
{

	// frequence_impulsion = 50Hz : Une impulsion toutes les 20ms
	// frequence_timer = 1Mhz : Précision de 1us -> 1000 positions possible -> précision de 0.18°
	// timPrescaler = 72e6/(frequence_timer*valeur_timClockDivision)-1
    // timPeriod = frequence_timer/frequence_impulsion
    timer = new Timer(numero_timer, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
}

Timer *Servo::timer = NULL;

Servo::~Servo()
{

}

#endif // ROBOTHW
