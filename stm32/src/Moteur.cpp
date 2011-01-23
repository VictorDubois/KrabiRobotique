#include "Moteur.h"

Moteur::Moteur(unsigned char OCx) : pwm(new Timer(4,71,20000, Timer::Div1), OCx)//pwm(&timer, OCx)
{
}

void Moteur::tourne(float rapport)
{
    pwm.setDutyCycle(rapport);
}
