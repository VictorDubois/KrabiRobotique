#include "commandTest.h"
#include "odometrie.h"
#include "strategieV2.h"
#include "leds.h"
#include "angle.h"

#ifndef abs
#define abs(x) fabs(x)
#endif

    ////////////////////////////////
    //      CommandAttendre       //
    ////////////////////////////////

CommandAttendre::CommandAttendre(int nbUpdates)
    : Command(), compte(nbUpdates)
{
}

void CommandAttendre::update()
{
    compte--;
}

Vitesse CommandAttendre::getLinearSpeed()
{
    return 0.0f;
}

Angle CommandAttendre::getAngularSpeed()
{
    return 0.0f;
}

bool CommandAttendre::fini() const
{
    return (compte <= 0);
}


    ////////////////////////////////
    //      CommandTestAvancer    //
    ////////////////////////////////

CommandTestAvancer::CommandTestAvancer()
    : Command()
{
}

void CommandTestAvancer::update()
{
}

Vitesse CommandTestAvancer::getLinearSpeed()
{
    return VITESSE_LINEAIRE_MAX;
}

Angle CommandTestAvancer::getAngularSpeed()
{
    return 0.0f;
}

    ////////////////////////////////
    //  CommandTestTournerGauche  //
    ////////////////////////////////


CommandTestTournerGauche::CommandTestTournerGauche()
    : Command()
{
}

void CommandTestTournerGauche::update()
{
}

Vitesse CommandTestTournerGauche::getLinearSpeed()
{
    return 0.0f;
}

Angle CommandTestTournerGauche::getAngularSpeed()
{
    return VITESSE_ANGULAIRE_MAX;
}
