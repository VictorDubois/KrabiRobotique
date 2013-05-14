#include "recalibrerOdometrie.h"
#include "odometrie.h"
#include "strategieV2.h"
#include "asservissement.h"
#include "leds.h"

RecalibrerOdometrie::RecalibrerOdometrie(bool blue) : MediumLevelAction()
{
    isBlue = blue;
    goalPosition1 = Position(700, 3000, isBlue);
    goalPosition2 = Position(0, 1360, isBlue);
}

RecalibrerOdometrie::~RecalibrerOdometrie()
{
    //dtor
}

int RecalibrerOdometrie::update()
{
    allumerLED();
    allumerLED2();
#ifndef ROBOTHW
    status = -1;
    return -1;
#else
    if (status == 0)
    {
        StrategieV2::setCurrentGoal(Position(700, 1360,isBlue), false);
        status = 1;
    }
    if (status == 1) // attend d'être replacé
    {
        Position vect = Position(700, 1360, isBlue) - Odometrie::odometrie->getPos().getPosition();
        if (vect.getNorme() < 40) // distance parcourue la derniere seconde
        {
            StrategieV2::setCurrentGoal(goalPosition1, true, 0.5);
            StrategieV2::setEnTrainDeRecalibrer(true);
            status = 2;
        }
    }
    if (status == 2) // attend d'avoir synchro sur Y
    {
        static int timeBlockedY = 0;
        if (abs(Odometrie::odometrie->getVitesseLineaire()) < 0.005f) //if (fdc1->getValue().b && fdc2->getValue().b) // distance parcourue la derniere seconde
        {
            timeBlockedY ++;
            allumerLED2();
        }
        else {
            timeBlockedY = 0;
            eteindreLED2();
        }
        if (timeBlockedY > 100 && Odometrie::odometrie->getPos().getPosition().getY() > 1850)
        {
            Odometrie::odometrie->setY(2000-95);
            StrategieV2::setCurrentGoal(Position(goalPosition1.getX(), 1360), false);
            StrategieV2::setEnTrainDeRecalibrer(false);
            status = 3;
            timeBlockedY = 0;
        }
    }
    else if (status == 3) // attend d'être replacé
    {
        Position vect = Position(goalPosition1.getX(), 1360) - Odometrie::odometrie->getPos().getPosition();
        if (vect.getNorme() < 40) // distance parcourue la derniere seconde
        {
            StrategieV2::setCurrentGoal(goalPosition2, true, 0.5);
            StrategieV2::setEnTrainDeRecalibrer(true);
            status = 4;
        }
    }
    else if (status == 4) // attend d'avoir synchro sur X
    {
        static int timeBlockedX = 0;
        if (abs(Odometrie::odometrie->getVitesseLineaire()) < 0.005f) // if (fdc1->getValue().b && fdc2->getValue().b) // distance parcourue la derniere seconde
        {
            timeBlockedX ++;
            allumerLED2();
        }
        else
        {
            timeBlockedX = 0;
            eteindreLED2();
        }
        if (timeBlockedX > 100 && (StrategieV2::getIsBlue() ? Odometrie::odometrie->getPos().getPosition().getX() < 200 : Odometrie::odometrie->getPos().getPosition().getX() > 2800))
        {
            Odometrie::odometrie->setX((StrategieV2::getIsBlue() ? 95 : 2905)); // robot = 319mm de large
            StrategieV2::setEnTrainDeRecalibrer(false);
            StrategieV2::setCurrentGoal(Odometrie::odometrie->getPos().getPosition()+Position((StrategieV2::getIsBlue()?200:-200), 0), false, 1); // on avance  encore un peu
            goalPosition2 = Odometrie::odometrie->getPos().getPosition()+Position((StrategieV2::getIsBlue()?200:-200), 0);
            status = 5;
            timeBlockedX = 0;
        }
    }
    else if (status == 5)
    {
        Position vect = goalPosition2 - Odometrie::odometrie->getPos().getPosition();
        if (vect.getNorme() < 40) // distance parcourue la derniere seconde
        {
            status = -1;
        }
    }
    return status;
#endif
}
