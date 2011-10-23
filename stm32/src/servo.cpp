#include "servo.h"

Servo::Servo(unsigned char OCx) : pwm_handler(timer, OCx)
{
}

void Servo::goToAngle(Angle angle)
{
	// Convertir angle en signal
	// Il reste à faire des tests pour vérifier que les valeurs d'angle correspondent effectivement

    // Variables utilisées pour convertir l'angle en largeur d'impulsion
    //static const float angle2pulsewidth_slope = frequence_timer*(angle180_timing - angle0_timing)/(180. - 0.);
    //static const float angle2pulsewidth_yintercept = angle0_timing*frequence_timer;

	float pulseWidth = ANGLETOPULSE(angle);  // l'angle est à prendre entre -150 (fermé) et +170 (grd ouvert)

	pwm_handler.setPulseWidth(pulseWidth);
	//pwm_handler.setPulseWidth((unsigned int)(angle*angle2pulsewidth_slope + angle2pulsewidth_yintercept));
}

void Servo::initTimer()
{

	// frequence_impulsion = 50Hz : Une impulsion toutes les 20ms
	// frequence_timer = 1Mhz : Précision de 1us -> 1000 positions possible -> précision de 0.18°
	// timPrescaler = 72e6/(frequence_timer*valeur_timClockDivision)-1
    // timPeriod = frequence_timer/frequence_impulsion
    timer = new Timer(numero_timer, PERIOD_TIMER_MOTEUR, PRESCALER_TIMER_MOTEUR, CLOCK_TIMER_MOTEUR);
}

Timer *Servo::timer = NULL;
