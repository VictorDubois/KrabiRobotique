#include "eteindreBougie.h"
#include "strategie.h"
#include "actionnerMarteau.h"
#include "regarderCouleur.h"

#ifndef ROBOTHW
#include "table.h"
#endif

EteindreBougie::EteindreBougie(Position position, int rotation, int color, bool triggered, bool high) : MediumLevelAction(position, 0, ETEINDRE_BOUGIE)
{
    this->rotation = rotation;
    this->color = color;
    this->triggered = triggered;
    this->high = high;

}
EteindreBougie::~EteindreBougie()
{
}

int EteindreBougie::update()
{
    if (status == 0) // time to start
        status = 1;

    if (status == 1) // go to the goal position
    {
        float distance = (this->getRobotPosition() - Strategie::getInstance()->getOdometrie()->getPos().getPosition()).getNorme();
        if (distance < 20)
        {
            status = 2;

            if (high)
            {
                actionsToDo[0] = new ActionnerMarteau(0, 0, 0);
                status = 2;
            }
            else
                status = 3;
        }

    }
    if (high && status == 2) // put the checking hammer to the good position
    {
        int result = actionsToDo[0]->update();
        if (result == -1)
        {
            status = 3;
            delete actionsToDo[0];
        }
    }
    if (status == 3) // time to check the color
    {
        bool isBlue = Strategie::getInstance()->getIsBlue();
        if (color == 0) // color never checked
        {
            actionsToDo[0] = new RegarderCouleur(); // create the color checker
            status = 4;
        }
        else if ((color == 1 && !isBlue) || (color==2 && isBlue)) // nothing to do, return -1
        {
            status = -1;
            return -1;
        }
        else // have to push it
        {
            status = 5;
        }
    }
    if (status == 4) // we are checking the color
    {
        bool isBlue = Strategie::getInstance()->getIsBlue();
        int result = actionsToDo[0]->update(); // wait the sensors to detect color
        if (result > 0) // the color has been checked
        {
            color = result;
            status = 5;
            if ((color == 1 && isBlue) || (color==2 && !isBlue)) // leave if it's not our color
            {
                status = -1;
                return -1;
            }
            delete actionsToDo[0];
        }
    }
    if (status == 5) // we checked the color, time to push the ball
    {
        actionsToDo[0] = new ActionnerMarteau(0,0x01ff,0xffff); // push
        status = 6;
    }
    if (status == 6)
    {
        int result = actionsToDo[0]->update(); // wait the push to finish
        if (result)
        {
            actionsToDo[0] = new ActionnerMarteau(0,0,0); // get up
            status = -2; // we can do other stuff while finishing this
        }
    }

    if (status == -2)
    {
        int result = actionsToDo[0]->update(); // waits the hammer to get up
        if (result)
        {
            status = -1;
            return -1;
        }
    }

    if (status >= 2)
        status++;

    if (status > 20)
        return -1;

    return status;
}
