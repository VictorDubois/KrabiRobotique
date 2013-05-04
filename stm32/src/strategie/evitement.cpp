#include "evitement.h"
#include "strategieV2.h"

Evitement::Evitement()
{
    //ctor
}

Evitement::~Evitement()
{
    //dtor
}

int Evitement::update()
{
    if (status == 0)
    {
        Position currentPos = Odometrie::odometrie->getPos().getPosition();
        // d'abord on recule :
        Position recul(-200*cos(Odometrie::odometrie->getPos().angle), -200*sin(Odometrie::odometrie->getPos().angle));
        goalPosition = currentPos + recul;
        StrategieV2::setCurrentGoal(goalPosition, true); // go back
        StrategieV2::setJustAvoided(true);
        status = 1;
        //std::cout << "EVITEMENT HAS BEEN CALLED" << std::endl;
    }
    else if (status == 1)
    {
        Position vect = goalPosition - Odometrie::odometrie->getPos().getPosition();
        if (vect.getNorme() < 20.0)
            status = -1;
    }
    return status;
}
