#include "ramenerVerres.h"
#include "strategieV2.h"
#include "odometrie.h"

RamenerVerres::RamenerVerres(Position goalPos) : MediumLevelAction(goalPos)
{
    //ctor
}

RamenerVerres::~RamenerVerres()
{
    //dtor
}

int RamenerVerres::update()
{
    if (status == 0) // go to base
    {
        Position vect = goalPosition - Odometrie::odometrie->getPos().getPosition();
        if (vect.getNorme() < 20.0)
        {
            goalPosition = Odometrie::odometrie->getPos().getPosition()+Position(200,0);
            StrategieV2::setCurrentGoal(goalPosition, true); // go back
            status++;
        }
    }
    else if (status == 1) // wait to have gone b
    {
        Position vect = goalPosition - Odometrie::odometrie->getPos().getPosition();
        if (vect.getNorme() < 20.0)
            return -1;
    }
}
