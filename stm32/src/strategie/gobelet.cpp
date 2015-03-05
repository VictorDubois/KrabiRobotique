#include "gobelet.h"
#include "strategieV2.h"
#include "mediumLevelAction.h"
#include "command.h"


Gobelet::Gobelet(){}

Gobelet::Gobelet(Position position):MediumLevelAction(position){}

Gobelet::~Gobelet(){}

int Gobelet::update()
{
    if (status == 0)
    {
        #ifndef ROBOTHW
            qDebug() << "gobelet";
        #endif
        status++;
    }

    else if (status == 1)
    {
        StrategieV2::setCurrentGoal(goalPosition, goBack);
        status++;
    }

    else if (status == 2)
    {
        if (Command::isNear(goalPosition))
        {
            StrategieV2::lookAt(goalPosition);
            status++;
        }
    }

    else if (status == 3)
    {
        if (Command::isLookingAt(goalPosition))
        {
            //recuperer le gobelet
            #ifndef ROBOTHW
            qDebug() << "On recupere le gobelet";
            #endif
            status++;
        }
    }

    else if (status <=53 && status > -1)
    {
        status++;
    }

    else if (status == 54)
    {
        status = -1;
    }

    return status;
}
