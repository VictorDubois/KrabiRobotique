#include "strategieV2.h"
#include "leds.h"
#include "positionPlusAngle.h"
#include "commandLookAt.h"
#include "asservissement.h"
#include "memory.h"
#include "actionGoTo.h"
#include "ramenerVerres.h"
#include "recalibrerOdometrie.h"
#include "evitement.h"
#include "commandAllerA.h"

#ifndef NULL
#define NULL 0
#endif

StrategieV2* StrategieV2::strategie = NULL;
int StrategieV2::updateCount = 0;
Command* StrategieV2::currentCommand = NULL;
MediumLevelAction* StrategieV2::currentAction = NULL;
int StrategieV2::actionsCount = 0;
MediumLevelAction* StrategieV2::actionsToDo[32];
bool StrategieV2::hasToGoBase = false;
bool StrategieV2::hasJustAvoided = false;
bool StrategieV2::mustDeleteAction = false;
int StrategieV2::glassGathered = 0;
int StrategieV2::timeSinceLastRecalibration = 0;
bool StrategieV2::somethingDetected = false;

StrategieV2::StrategieV2()
{
    /*actionsToDo[0] = new RamasserVerreV2(Position(900,550));
    actionsToDo[1] = new RamasserVerreV2(Position(1050,800));
    actionsToDo[2] = new RamasserVerreV2(Position(900,1050));
    actionsToDo[3] = new RamasserVerreV2(Position(1200,1050));
    actionsToDo[4] = new RamasserVerreV2(Position(1200,550));
    actionsToDo[5] = new RamasserVerreV2(Position(1350,800));
    actionsToDo[6] = new RamasserVerreV2(Position(1650,800));
    actionsToDo[7] = new RamasserVerreV2(Position(1800,1050));
    actionsToDo[8] = new RamasserVerreV2(Position(1800,550));
    actionsToDo[9] = new RamasserVerreV2(Position(1950,800));
    actionsToDo[10] = new RamasserVerreV2(Position(2100,550));
    actionsToDo[11] = new RamasserVerreV2(Position(2100,1050));*/

    //actionsToDo[0] = new Evitement();
    actionsToDo[0] = new ActionGoTo(Position(1000,230), false);
    //actionsToDo[0] = new RamasserVerreV2(Position(900,550));
    actionsToDo[1] = new ActionGoTo(Position(2300,230), false);
    actionsToDo[2] = new ActionGoTo(Position(2600,400), false);
    actionsToDo[3] = new ActionGoTo(Position(2600,550), false);
    actionsToDo[4] = new ActionGoTo(Position(300, 550), false);
    actionsToDo[5] = new ActionGoTo(Position(2600,550), true);
    actionsToDo[6] = new ActionGoTo(Position(2600,800), false);
    actionsToDo[7] = new ActionGoTo(Position(300, 800), false);
    actionsToDo[8] = new ActionGoTo(Position(2600,800), true);
    actionsToDo[9] = new ActionGoTo(Position(2600,1070), false);
    actionsToDo[10] = new ActionGoTo(Position(300,1070), false);

    //currentAction = new RecalibrerOdometrie(new LimitSwitchSensor(LimitSwitchSensor::BACK_LEFT, GPIO_Pin_14, GPIOD), new LimitSwitchSensor(LimitSwitchSensor::BACK_RIGHT, GPIO_Pin_1, GPIOD));
    currentAction = actionsToDo[actionsCount];
    //currentCommand = new CommandAllerA(currentAction->getGoalPosition());
    //Asservissement::setCommand(currentCommand);
    //currentAction = new RecalibrerOdometrie();
    //hasJustAvoided = true;
    currentAction->update();

    StrategieV2::strategie = this;
}

StrategieV2::~StrategieV2()
{
    //dtor
}


void StrategieV2::update()
{
    if (StrategieV2::strategie == NULL)
        return;
    if (actionsCount == 11)
        return;
    
    // check sensors:
    if (somethingDetected)
    {
        hasJustAvoided = true;
        if (true) // if (canStillDoAction)
        {
            if (currentAction)
            {
                currentAction->collisionAvoided();
                currentAction->update();
            }
        }
        hasJustAvoided = false;
        somethingDetected = false;
    }

    //std::cout << "updating action" << std::endl;
    if (currentAction->update() == -1)
    {
        //std::cout << "Changing action" << std::endl;
        Position currentPos = Odometrie::odometrie->getPos().getPosition();
        // delete the current command
        //if (currentCommand != NULL)
            //delete currentCommand;
        if (mustDeleteAction && currentAction != NULL)
            delete currentAction;

        // must go to base :
        if (hasToGoBase)
        {
            currentAction = new RamenerVerres(Position(300,currentPos.getY()));
            hasToGoBase = false;
            mustDeleteAction = true;
        }
        /*else if (timeSinceLastRecalibration % 3 == 2)
        {
            currentAction = new RecalibrerOdometrie();
            mustDeleteAction = true;
            timeSinceLastRecalibration++;
        }*/
        //else
        //{
        if (mustDeleteAction) // temporary action
            mustDeleteAction = false;

        actionsCount++;
        if (actionsCount == 11)
        {
            Asservissement::asservissement->setCommandSpeeds(NULL);
            return;
        }
        else
        {
            currentAction = actionsToDo[actionsCount];
            mustDeleteAction = false;
        }
            //timeSinceLastRecalibration++;
        //}
        //if (currentAction != NULL)
            //delete action;
        currentAction->update();

    }
    if (currentCommand)
        currentCommand->update();
    Asservissement::asservissement->setCommandSpeeds(currentCommand);
    updateCount ++;
}

void StrategieV2::setCurrentGoal(Position goal, bool goBack)
{
    if (currentCommand != NULL)
            delete currentCommand;
    currentCommand = new CommandAllerA(goal, goBack);
    Asservissement::asservissement->setCommandSpeeds(currentCommand);
}
void StrategieV2::setCurrentGoal(Position goal, Position center, float vitesse, bool goBack)
{
    if (currentCommand != NULL)
            delete currentCommand;
    currentCommand = new CommandAllerEnArcA(goal, center, vitesse*5, goBack);
    Asservissement::asservissement->setCommandSpeeds(currentCommand);
}
void StrategieV2::lookAt(Position pos)
{
    if (currentCommand != NULL)
            delete currentCommand;
    currentCommand = new CommandTournerVers(pos); // create the command
    Asservissement::asservissement->setCommandSpeeds(currentCommand); // apply it
}
void StrategieV2::addTemporaryAction(MediumLevelAction* action)
{
    currentAction = action;
    mustDeleteAction = true; // this is a temporary action that needs to be deleted
}
void StrategieV2::setJustAvoided(bool avoided)
{
    hasJustAvoided = avoided;
}
bool StrategieV2::getJustAvoided()
{
    return hasJustAvoided;
}
bool StrategieV2::willCollide()
{
    somethingDetected = true;
    Asservissement::asservissement->setCommandSpeeds(NULL); // stoppe le robot
}

void StrategieV2::gatherGlass()
{
    glassGathered++;
    if (glassGathered > 0)
    {
        glassGathered = 0;
        hasToGoBase = true;
    }
}


