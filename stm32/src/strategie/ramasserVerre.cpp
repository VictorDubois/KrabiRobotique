#include "ramasserVerre.h"
#include "strategie.h"
#include "actionnerPortes.h"
#include "actionnerAscenseur.h"
#include "lancerAscenseur.h"
#include "asservissement.h"
#include "commandGoTo.h"

RamasserVerre::RamasserVerre(Position position) : MediumLevelAction(position, 0, RAMASSER_VERRE)
{

}
RamasserVerre::~RamasserVerre()
{
}

int RamasserVerre::update() {
    if (status == 0)
        status = 1;
    if (status == 1) // go 150mm (center of the robot) far to the right location
    {
        float distance = (this->getRobotPosition() - Strategie::getInstance()->getOdometrie()->getPos().getPosition()).getNorme();
        if (distance < 20)
        {
            //actionsToDo[0] = new ActionnerPortes(false); // open the doors
            status = -1;
            Strategie::getInstance()->updateGoal(Strategie::getInstance()->getOdometrie()->getPos().getPosition()); // stop moving
            return -1;
        }
    }
    if (status == 2) // waiting the doors to open
    {
        int result = actionsToDo[0]->update();
        if (result > 0) // dors are open
        {
            status = 3;
            Strategie::getInstance()->updateGoal(robotPosition); // go to the exact location of the glass
            delete actionsToDo[0];
        }
    }
    if (status == 3) // waiting the robot to take the glass
    {
        float distance = (this->getRobotPosition() - Strategie::getInstance()->getOdometrie()->getPos().getPosition()).getNorme();
        if (distance < 15) // 1mm5 far from the glass initial pos
        {
            status = 4;
            actionsToDo[0] = new ActionnerPortes(true); // close the doors
        }
    }
    if (status == 4) // wait the doors to close
    {
        int result = actionsToDo[0]->update();
        if (result > 0) // dors are now closed
        {
            status = 5;
            delete actionsToDo[0];
            actionsToDo[0] = new ActionnerAscenseur(false); // open the elevator doors
        }
    }
    if (status == 5) // wait the elevator doors to open
    {
        int result = actionsToDo[0]->update();
        if (result > 0) // elevator doors are open
        {
            status = 6;
            delete actionsToDo[0];
            actionsToDo[0] = new LancerAscenseur(-100); // elevator goes down
        }
    }
    if (status == 6) // wait the elevator to go down
    {
        int result = actionsToDo[0]->update();
        if (result > 0) // elevator is now down
        {
            status = 7;
            delete actionsToDo[0];
            actionsToDo[0] = new ActionnerAscenseur(true); // elevator doors close
        }
    }
    if (status == 7) // wait the elevator to close doors
    {
        int result = actionsToDo[0]->update();
        if (result > 0) // elevator doors are closed
        {
            status = 8;
            delete actionsToDo[0];
            actionsToDo[0] = new LancerAscenseur(100); // elevator goes up
        }
    }
    if (status == 8) // wait the elevator to go up
    {
        int result = actionsToDo[0]->update();
        if (result > 0) // elevator is up, it's the end
        {
            status = -1;
            Strategie::getInstance()->storeGlass();
            delete actionsToDo[0];
            return -1;
        }
    }

    return status;
}



