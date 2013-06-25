#include "ramasserVerreV2.h"
#include "position.h"
#include "odometrie.h"
#include "strategieV2.h"
#include "actionGoTo.h"

RamasserVerreV2::RamasserVerreV2(Position goalPos) : MediumLevelAction(goalPos)
{

}

RamasserVerreV2::~RamasserVerreV2()
{
    //dtor
}

int RamasserVerreV2::update()
{
    if (status == 0) // trying to go
    {
        StrategieV2::addTemporaryAction(new ActionGoTo(goalPosition, false, 10));
    }
    else if (status == 1)
    {
        Position vect = goalPosition - Odometrie::odometrie->getPos().getPosition();
        float distance = vect.getNorme();
        if (distance < 20.0)
        {
            StrategieV2::gatherGlass();
            return -1;
        }
    }
}
