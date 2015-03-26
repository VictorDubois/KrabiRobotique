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

    if (StrategieV2::getIsBlue())
    {
    bougiesBas[0] = new EteindreBougieV2(Position(850.00,   1793, StrategieV2::getIsBlue()), -1.2200,   true,   true, isBlue,   bleuVersRouge);
    bougiesBas[1] = new EteindreBougieV2(Position(850.00,   1793, StrategieV2::getIsBlue()), -1.2200,   false,  true, isBlue,   bleuVersRouge);
    bougiesBas[2] = new EteindreBougieV2(Position(909.626,  1623, StrategieV2::getIsBlue()), -1.0000,   true,   true, isBlue,   bleuVersRouge);
    bougiesBas[3] = new EteindreBougieV2(Position(941.00,   1580, StrategieV2::getIsBlue()), -0.9100,   false,  true, !isBlue,  bleuVersRouge);
    bougiesBas[4] = new EteindreBougieV2(Position(1027.09,  1483, StrategieV2::getIsBlue()), -0.916298, true,   true, isBlue,   bleuVersRouge);
    bougiesBas[5] = new EteindreBougieV2(Position(1176.00,  1370, StrategieV2::getIsBlue()), -0.4000,   false,  true, isBlue,   bleuVersRouge);
    bougiesBas[6] = new EteindreBougieV2(Position(1176.78,  1379, StrategieV2::getIsBlue()), -0.654498, true,   true, !isBlue,  bleuVersRouge);
    bougiesBas[7] = new EteindreBougieV2(Position(1290,     1320, StrategieV2::getIsBlue()), -0.50,     true,   true, isBlue,   bleuVersRouge);
    bougiesBas[8] = new EteindreBougieV2(Position(1430,     1300, StrategieV2::getIsBlue()), 0.0000,    false,  true, !isBlue,  bleuVersRouge);
    bougiesBas[9] = new EteindreBougieV2(Position(1485,     1260, StrategieV2::getIsBlue()), -0.0500,   true,   true, isBlue,   bleuVersRouge);
    bougiesBas[10] = new EteindreBougieV2(Position(1665,    1300, StrategieV2::getIsBlue()), 0.1309,    true,   true, isBlue,   bleuVersRouge);
    bougiesBas[11] = new EteindreBougieV2(Position(1665,    1300, StrategieV2::getIsBlue()), 0.2500,    false,  true, isBlue,   bleuVersRouge);
    bougiesBas[12] = new EteindreBougieV2(Position(1860,    1355, StrategieV2::getIsBlue()), 0.50,      true,   true, isBlue,   bleuVersRouge);
    bougiesBas[13] = new EteindreBougieV2(Position(1920,    1420, StrategieV2::getIsBlue()), 0.50,      false,  true, !isBlue,  bleuVersRouge);
    bougiesBas[14] = new EteindreBougieV2(Position(2010,    1510, StrategieV2::getIsBlue()), 0.654498,  true,   true, isBlue,   bleuVersRouge);
    bougiesBas[15] = new EteindreBougieV2(Position(2060,    1600, StrategieV2::getIsBlue()), 0.80,      false,  true, isBlue,   bleuVersRouge);
    bougiesBas[16] = new EteindreBougieV2(Position(2120.00, 1620, StrategieV2::getIsBlue()), 0.916298,  true,   true, !isBlue,  bleuVersRouge);
    bougiesBas[17] = new EteindreBougieV2(Position(2160.00, 1780, StrategieV2::getIsBlue()), 1.1781,    true,   true, !isBlue,  bleuVersRouge);
    bougiesBas[18] = new EteindreBougieV2(Position(2174.18, 1890, StrategieV2::getIsBlue()), 1.4399,    true,   true, !isBlue,  bleuVersRouge);

    //bougiesBas[7] = new EteindreBougieV2(Position(2150, 1895, StrategieV2::getIsBlue()), 1.10,  false, true, true, bleuVersRouge);

    }
    else
    {
    bougiesBas[4] = new EteindreBougieV2(Position(1290, 1320, StrategieV2::getIsBlue()), 0.50, true, true, true, bleuVersRouge);
    bougiesBas[5] = new EteindreBougieV2(Position(1470, 1285, StrategieV2::getIsBlue()), 0.1309,   true, true, true, bleuVersRouge);
    bougiesBas[6] = new EteindreBougieV2(Position(1640, 1295, StrategieV2::getIsBlue()), -0.1309,    true, true, true, bleuVersRouge);
    bougiesBas[7] = new EteindreBougieV2(Position(1820, 1365, StrategieV2::getIsBlue()), -0.50,  true, true, true, bleuVersRouge);
    }

    etapeBas = 0;//(bleuVersRouge?4:6); // valeur a laquelle on commence, mettre 4 ou 7 pour faire les blanches uniquements
    status = 0;
}

EteindreBougies::~EteindreBougies()
{
    //dtor
}

int EteindreBougies::update()
{
    //allumerLED2();
    if (status == 0)
        status = 1;
    else if (status == 1) // mise en place du robot
    {
        StrategieV2::setCurrentGoal(Position(1000, 1360, StrategieV2::getIsBlue()), false); // positions a changer pour ne faire que les blanches
        status = 2;
    }
    else if (status == 2) // mise en place du robot
    {
        Position vect = Position(1000, 1360, StrategieV2::getIsBlue()) - Odometrie::odometrie->getPos().getPosition();
      //  allumerLED2();
        if (vect.getNorme() < 10)
        {
            StrategieV2::setCurrentGoal(Position(850, 1793, StrategieV2::getIsBlue()), true); // positions a changer pour ne faire que les blanches
            Marteaux::releverHautGauche();
            status = 3;
        }
    }
    else if (status == 3) // choisir la bougie a faire
    {
        Position vect = Position(850, 1793, StrategieV2::getIsBlue()) - Odometrie::odometrie->getPos().getPosition();
        if (vect.getNorme() < 10)
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
        if (etapeBas == -1 || etapeBas == 18) // c'est fini !!
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
        StrategieV2::lookAt(Position(2100, 1250));
        status = 7;
    }
    else if (status == 200)
    {
        Marteaux::rangerHautGauche();
        status = -1;
    }
    else if (status > 6)
        status ++;


    return status;
}
