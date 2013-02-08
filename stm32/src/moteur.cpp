#include "moteur.h"

#include "constantes.h"
#include "timerHandler.h"

Moteur::Moteur(unsigned char OCx)
    : pwm(new Timer(NUM_TIMER_MOTEUR,PERIOD_TIMER_MOTEUR,PRESCALER_TIMER_MOTEUR, CLOCK_TIMER_MOTEUR), OCx)
{
}

void Moteur::tourne(float rapport)
{
    pwm.setDutyCycle(rapport);
}
