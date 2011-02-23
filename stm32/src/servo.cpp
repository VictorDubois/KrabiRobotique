#include "servo.h"
#include "memory.h"

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

	float pulseWidth = (angle*500)/124 + 1500;
	pwm_handler.setPulseWidth(pulseWidth);
	//pwm_handler.setPulseWidth((unsigned int)(angle*angle2pulsewidth_slope + angle2pulsewidth_yintercept));
}

void Servo::initTimer()
{

	// frequence_impulsion = 50Hz : Une impulsion toutes les 20ms
	// frequence_timer = 1Mhz : Précision de 1us -> 1000 positions possible -> précision de 0.18°
	// timPrescaler = 72e6/(frequence_timer*valeur_timClockDivision)-1
    // timPeriod = frequence_timer/frequence_impulsion
    const Timer::ClkDivision timClockDivision = Timer::Div1;
    const uint16_t timPrescaler = 71;
    const uint16_t timPeriod = 20000;

    timer = new Timer(numero_timer, timPeriod, timPrescaler, timClockDivision);
}

Timer *Servo::timer = 0; // bizarrement NULL n'est pas défini
