#include "eteindreBougies.h"
#include "strategieV2.h"
#include "actionGoTo.h"
#include "leds.h"
#include "odometrie.h"
#include "asservissement.h"
#include "marteaux.h"

EteindreBougies::EteindreBougies(bool isBlue) : MediumLevelAction()
{
    //bool isBlue = StrategieV2::getIsBlue();
    bleuVersRouge = isBlue;
    bougiesBas[0] = new EteindreBougieV2(Position(832.398, 1789.51), -1.3500,   true, true, isBlue, bleuVersRouge);
    bougiesBas[1] = new EteindreBougieV2(Position(909.626, 1623.89), -1.1781,   true, false, false, bleuVersRouge);
    bougiesBas[2] = new EteindreBougieV2(Position(1027.09, 1483.91), -0.916298, true, false, false, bleuVersRouge);
    bougiesBas[3] = new EteindreBougieV2( Position(1176.78, 1379.09), -0.654498, true, false, false, bleuVersRouge);
    
    if (StrategieV2::getIsBlue())
    {
    bougiesBas[4] = new EteindreBougieV2(Position(1290, 1320, StrategieV2::getIsBlue()), -0.50, true, true, true, bleuVersRouge);
    bougiesBas[5] = new EteindreBougieV2( Position(1470, 1285, StrategieV2::getIsBlue()), -0.1309,   true, true, true, bleuVersRouge);
    bougiesBas[6] = new EteindreBougieV2(Position(1640, 1295, StrategieV2::getIsBlue()), 0.1309,    true, true, true, bleuVersRouge);
    bougiesBas[7] = new EteindreBougieV2(Position(1820, 1365, StrategieV2::getIsBlue()), 0.50,  true, true, true, bleuVersRouge);
    }
    else
    {
    bougiesBas[4] = new EteindreBougieV2(Position(1290, 1320, StrategieV2::getIsBlue()), 0.50, true, true, true, bleuVersRouge);
    bougiesBas[5] = new EteindreBougieV2( Position(1470, 1285, StrategieV2::getIsBlue()), 0.1309,   true, true, true, bleuVersRouge);
    bougiesBas[6] = new EteindreBougieV2(Position(1640, 1295, StrategieV2::getIsBlue()), -0.1309,    true, true, true, bleuVersRouge);
    bougiesBas[7] = new EteindreBougieV2(Position(1820, 1365, StrategieV2::getIsBlue()), -0.50,  true, true, true, bleuVersRouge);
    }
    bougiesBas[8] = new EteindreBougieV2(Position(1913.96, 1460.52), 0.654498,  true, false, false, bleuVersRouge);
    bougiesBas[9] = new EteindreBougieV2(Position(2039.48, 1586.04), 0.916298,  true, false, false, bleuVersRouge);
    bougiesBas[10] = new EteindreBougieV2(Position(2128.24, 1739.78), 1.1781,   true, false, false, bleuVersRouge);
    bougiesBas[11] = new EteindreBougieV2(Position(2174.18, 1862.00), 1.4399,   true, true, !isBlue, bleuVersRouge);

    etapeBas = 4;//(bleuVersRouge?4:6); // valeur a laquelle on commence, mettre 4 ou 7 pour faire les blanches uniquements
    status = 0;
}

EteindreBougies::~EteindreBougies()
{
    //dtor
}

int EteindreBougies::update()
{
    allumerLED2();
    if (status == 0)
        status = 1;
    else if (status == 1) // mise en place du robot
    {
        StrategieV2::setCurrentGoal(Position(1000, 1360, StrategieV2::getIsBlue()), false); // positions a changer pour ne faire que les blanches
        status = 3;
    }
    else if (status == 2) // mise en place du robot
    {
        Position vect = Position(834, 1360, StrategieV2::getIsBlue()) - Odometrie::odometrie->getPos().getPosition();
        allumerLED2();
        if (vect.getNorme() < 10)
        {
            StrategieV2::setCurrentGoal(Position(841, 1792, StrategieV2::getIsBlue()), true); // positions a changer pour ne faire que les blanches
            status = 3;
        }
    }
    else if (status == 3) // choisir la bougie a faire
    {
        Position vect = Position(1000, 1360, StrategieV2::getIsBlue()) - Odometrie::odometrie->getPos().getPosition();
        if (vect.getNorme() < 20)
        {
            //Asservissement::asservissement->roues.droite.tourne(0);
            //Asservissement::asservissement->roues.gauche.tourne(0);
            StrategieV2::addTemporaryAction(bougiesBas[etapeBas]);
            status = 4;
        }
    }
    else if (status == 4) // appelé quand l'action temporaire (éteindre une bougie) est terminée.
    {
        etapeBas += 1;// (bleuVersRouge?1:-1);
        status = 5;
        if (etapeBas == 2 || etapeBas == 8) // c'est fini !!
        {
            float currentAngle = wrapAngle(Odometrie::odometrie->getPos().getAngle());
            StrategieV2::addTemporaryAction( new ActionGoTo(Odometrie::odometrie->getPos().getPosition() + Position(-300*cos(currentAngle), -300*sin(currentAngle)), true));
            status = 6;
        }
    }
    else if (status == 5)
    {
        StrategieV2::addTemporaryAction(bougiesBas[etapeBas]);
        status = 4;
    }
    else if (status == 6)
    {
        status = -1;
    }
    else if (status > 5)
        status ++;
        
    
    return status;
}
