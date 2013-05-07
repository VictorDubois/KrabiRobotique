#include "recalibrerOdometrie.h"
#include "odometrie.h"
#include "strategieV2.h"

RecalibrerOdometrie::RecalibrerOdometrie(LimitSwitchSensor* _fdc1, LimitSwitchSensor* _fdc2) : MediumLevelAction()
{
    goalPosition1 = Position(700, 1950);
    goalPosition2 = Position(50, 1000);
    fdc1 = _fdc1;
    fdc2 = _fdc1;
}

RecalibrerOdometrie::~RecalibrerOdometrie()
{
    //dtor
}

int RecalibrerOdometrie::update()
{
#ifndef ROBOTHW
    status = -1;
    return -1;
#else
    if (status == 0)
    {
        StrategieV2::setCurrentGoal(Position(700, 1000), false);
        status = 1;
    }
    if (status == 1) // attend d'avoir synchro sur Y
    {
        Position vect = Position(700, 1000) - Odometrie::odometrie->getPos().getPosition();
        if (vect.getNorme() < 20) // distance parcourue la derniere seconde
        {
            StrategieV2::setCurrentGoal(goalPosition1, true);
            status = 4;
        }
    }
    if (status == 2) // attend d'avoir synchro sur Y
    {
        fdc1->updateValue();
        fdc2->updateValue();
        if (fdc1->getValue().b && fdc2->getValue().b) // distance parcourue la derniere seconde
        {
            Odometrie::odometrie->setY(2000-95);
            StrategieV2::setCurrentGoal(Position(700, 1000), false);
            status = 3;
        }
    }
    if (status == 3) // attend d'avoir synchro sur Y
    {
        Position vect = Position(700, 1000) - Odometrie::odometrie->getPos().getPosition();
        if (vect.getNorme() < 20) // distance parcourue la derniere seconde
        {
            StrategieV2::setCurrentGoal(goalPosition2, true);
            status = 4;
        }
    }
    else if (status == 4) // attend d'avoir synchro sur Y
    {
        fdc1->updateValue();
        fdc2->updateValue();
        if (fdc1->getValue().b && fdc2->getValue().b) // distance parcourue la derniere seconde
        {
            Odometrie::odometrie->setX(95); // robot = 319mm de large
            status = -1;
        }
    }
    return status;
#endif
}