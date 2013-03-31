#include "commandTest.h"


CommandTestAvancer::CommandTestAvancer()
    : Command()
{
}

void CommandTestAvancer::update()
{
}

// Avance à la vitesse maximale
Vitesse CommandTestAvancer::getLinearSpeed()
{
    return VITESSE_LINEAIRE_MAX;
}

// renvoit 0
Angle CommandTestAvancer::getAngularSpeed()
{
    return 0.0f;
}



CommandTestTournerGauche::CommandTestTournerGauche()
    : Command()
{
}

void CommandTestTournerGauche::update()
{
}

// renvoit 0
Vitesse CommandTestTournerGauche::getLinearSpeed()
{
    return 0.0f;
}

// tourne à la vitesse maximale (vers la gauche)
Angle CommandTestTournerGauche::getAngularSpeed()
{
    return VITESSE_ANGULAIRE_MAX;
}
