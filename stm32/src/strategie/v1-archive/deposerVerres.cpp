#include "deposerVerres.h"
#include "actionnerPortes.h"
#include "actionnerAscenseur.h"
#include "strategie.h"

DeposerVerres::DeposerVerres(Position position) : MediumLevelAction(position, 0, DEPOSER_VERRES)
{

}

DeposerVerres::~DeposerVerres()
{

}

int DeposerVerres::update()
{
    if (status == 0) // time to start
        status = 1;

    if (status == 1) // go to the goal position
    {
        float distance = (this->getRobotPosition() - Strategie::getInstance()->getOdometrie()->getPos().getPosition()).getNorme();
        if (distance < 20)
            status = 5;
    }
    if (status == 2)  // we are at the goal pos
    {
        actionsToDo[0] = new ActionnerPortes(false); // open the bottom doors
        status = 3;
    }
    if (status == 3) // we wait the bottom doors to open
    {
        int result = actionsToDo[0]->update();
        if (result > 0) // bottom doors are open
        {
            delete actionsToDo[0];
            actionsToDo[0] = new ActionnerAscenseur(false); // open the elevator doors
            status = 4;
        }
    }
    if (status == 4) // we wait the elevator doors to be open
    {
        int result = actionsToDo[0]->update();
        if (result > 0) // the elevator doors are open, glasses should be down
        {
            delete actionsToDo[0];
#ifndef ROBOTHW
            Strategie::getInstance()->cleanGlassStorage();
#endif
            status = 5;
        }
    }
    if (status == 5) // need to go back
    {
        robotPosition = Position(robotPosition.getX()+(Strategie::getInstance()->getIsBlue()?200:-200), robotPosition.getY());
        Strategie::getInstance()->updateGoal(robotPosition, true);
        status = 6;
    }
    if (status == 6) // finish
    {
        float distance = (this->getRobotPosition() - Strategie::getInstance()->getOdometrie()->getPos().getPosition()).getNorme();
        if (distance < 20)
            status = -1;
    }
    return status;
}
