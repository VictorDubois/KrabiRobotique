#include "recalibrerOdometrie.h"
#include "odometrie.h"
#include "strategieV2.h"
#include "asservissement.h"
#include "leds.h"
#ifndef ROBOTHW
#include <QDebug>
#endif

RecalibrerOdometrie::RecalibrerOdometrie(bool blue, Position positionDepart, int coinRecalage) : MediumLevelAction()
{
    this->isBlue = blue;
    this->positionDepart = positionDepart;//Position(700, 3000, isBlue);
    //goalPosition2 = Position(0, 1360, isBlue);
    this->candidatPositionArrete = Position(0, 0, isBlue);
    this->coinRecalage = coinRecalage;
}

RecalibrerOdometrie::~RecalibrerOdometrie()
{
    //dtor
}

int RecalibrerOdometrie::update()
{
    allumerLED();
    allumerLED2();
//#ifndef ROBOTHW
//    status = -1;
//    return -1;
//#else
    if (status == 0)
    {
#ifndef ROBOTHW
        qDebug() << "recalibrerOdometrie";
#endif
        StrategieV2::setCurrentGoal(positionDepart, false);//Position(700, 1360,isBlue), false);
        status = 1;
    }
    if (status == 1) // attend d'être replacé
    {
        Position vect = positionDepart - Odometrie::odometrie->getPos().getPosition();
        if (vect.getNorme() < 40)
        {
            if(this->coinRecalage == COTE_NOTRE_DEPART_BAS || this->coinRecalage == COTE_NOTRE_DEPART_HAUT)
            {
                StrategieV2::setCurrentGoal(Position(0, positionDepart.getY()), true, 0.5);
            }
            else
            {
                StrategieV2::setCurrentGoal(Position(3000, positionDepart.getY()), true, 0.5);
            }
            StrategieV2::setEnTrainDeRecalibrer(true);
            status = 2;
        }
    }
    if (status == 2) // attend d'avoir synchro sur X
    {
        static int timeBlockedY = 0;
        //if (abs(Odometrie::odometrie->getVitesseLineaire()) < 0.005f) //if (fdc1->getValue().b && fdc2->getValue().b) // distance parcourue la derniere seconde
        Position vect = candidatPositionArrete - Odometrie::odometrie->getPos().getPosition();
        if(abs(vect.getNorme()) < 5)//Si on a pas bougé de plus de Xmm du dernier candidat de position où le robot s'est arrêté
        {
            timeBlockedY ++;
//            allumerLED2();
        }
        else {
            timeBlockedY = 0;
            candidatPositionArrete = Odometrie::odometrie->getPos().getPosition();
            eteindreLED2();
        }
        if (timeBlockedY > 100 &&
                (((this->coinRecalage == COTE_DEPART_ADVERSAIRE_HAUT || this->coinRecalage == COTE_DEPART_ADVERSAIRE_BAS)
                  && Odometrie::odometrie->getPos().getPosition().getX() > 2850)
                || ((this->coinRecalage == COTE_NOTRE_DEPART_HAUT || this->coinRecalage == COTE_NOTRE_DEPART_BAS)
                  && Odometrie::odometrie->getPos().getPosition().getX() < 150)
                 ))// && Odometrie::odometrie->getPos().getPosition().getY() > 1500)//1850)
        {
#ifdef ROBOTHW //A adapter à la taille du robot
            if(this->coinRecalage == COTE_DEPART_ADVERSAIRE_HAUT || this->coinRecalage == COTE_DEPART_ADVERSAIRE_BAS)
                Odometrie::odometrie->setX((StrategieV2::getIsBlue() ? 95 : 2905)); // robot = 319mm de large
            else
                Odometrie::odometrie->setX((StrategieV2::getIsBlue() ? 2905 : 95)); // robot = 319mm de large
#endif
            //StrategieV2::setCurrentGoal(Position(goalPosition1.getX(), 1360), false);
            StrategieV2::setCurrentGoal(positionDepart, false);
            StrategieV2::setEnTrainDeRecalibrer(false);
            status = 3;
            timeBlockedY = 0;
        }
    }
    else if (status == 3) // attend d'être replacé
    {
        Position vect = positionDepart - Odometrie::odometrie->getPos().getPosition();
        if (vect.getNorme() < 40)
        {
            if(this->coinRecalage == COTE_NOTRE_DEPART_BAS || this->coinRecalage == COTE_DEPART_ADVERSAIRE_BAS)
            {
                StrategieV2::setCurrentGoal(Position(positionDepart.getX(), 0), true, 0.5);
            }
            else
            {
                StrategieV2::setCurrentGoal(Position(positionDepart.getX(), 2000), true, 0.5);
            }
            status  = 4;
        }
    }
    else if (status == 4) // attend d'avoir synchro sur Y
    {

        static int timeBlockedX = 0;
        //if (abs(Odometrie::odometrie->getVitesseLineaire()) < 0.005f) // if (fdc1->getValue().b && fdc2->getValue().b) // distance parcourue la derniere seconde
        Position vect = candidatPositionArrete - Odometrie::odometrie->getPos().getPosition();
        if(abs(vect.getNorme()) < 5)//Si on a pas bougé de plus de Xmm du dernier candidat de position où le robot s'est arrêté
        {
            timeBlockedX ++;
//            allumerLED2();
        }
        else
        {
            timeBlockedX = 0;
            candidatPositionArrete = Odometrie::odometrie->getPos().getPosition();
            eteindreLED2();
        }
        if (timeBlockedX > 100 &&
            (((this->coinRecalage == COTE_DEPART_ADVERSAIRE_HAUT || this->coinRecalage == COTE_NOTRE_DEPART_HAUT)
              && Odometrie::odometrie->getPos().getPosition().getY() > 1850)
            || ((this->coinRecalage == COTE_DEPART_ADVERSAIRE_BAS || this->coinRecalage == COTE_NOTRE_DEPART_BAS)
              && Odometrie::odometrie->getPos().getPosition().getY() < 150)
             ))// && (StrategieV2::getIsBlue() ? Odometrie::odometrie->getPos().getPosition().getX() < 200 : Odometrie::odometrie->getPos().getPosition().getX() > 2800))
        {
#ifdef ROBOTHW //A adapter à la taille du robot

            if(this->coinRecalage == COTE_DEPART_ADVERSAIRE_HAUT || this->coinRecalage == COTE_NOTRE_DEPART_HAUT)
                Odometrie::odometrie->setY(2000-95);
            else
                Odometrie::odometrie->setY(95);
#endif
            StrategieV2::setEnTrainDeRecalibrer(false);
            StrategieV2::setCurrentGoal(positionDepart, false);
            //StrategieV2::setCurrentGoal(Odometrie::odometrie->getPos().getPosition()+Position((StrategieV2::getIsBlue()?200:-200), 0), false, 1); // on avance  encore un peu
            //goalPosition2 = Odometrie::odometrie->getPos().getPosition()+Position((StrategieV2::getIsBlue()?200:-200), 0);
            status = 5;
            timeBlockedX = 0;
        }
    }
    else if (status == 5)
    {
        Position vect = positionDepart - Odometrie::odometrie->getPos().getPosition();//positionGoal2 -
        if (vect.getNorme() < 40)
        {
            status = -1;
        }
    }
    return status;
//#endif
}
