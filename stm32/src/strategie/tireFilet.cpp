                                     //#ifdef PASENCORECOMPILABLE
#include "tireFilet.h"
#include "tireLances.h"
#include "strategieV2.h"
#include "actionGoTo.h"
#include "leds.h"
#include "odometrie.h"
#include "asservissement.h"
#include "positionPlusAngle.h"

#ifndef ROBOTHW
#include <QDebug>
#endif

TireFilet::TireFilet(){}

TireFilet::TireFilet(bool isBlue, Position positionDepart, bool coteDuMammouth, float precisionPosition, float precisionAngle) : MediumLevelAction()
{
    this->isBlue = isBlue;
    this->positionDepart = positionDepart;
    //this->coteDuMammouth = coteDuMammouth;
//    this->bordureFeu = bordureFeu;
//    this->sensFeu = sensFeu;
//    this->coteDuFeu = coteDuFeu;
    //this->precision = precision;
    this->precisionPosition = precisionPosition;
    this->precisionAngle = precisionAngle;
    if(coteDuMammouth == COTE_NOTRE_DEPART)
    {
        this->positionTir = Position(500, 0);
    }
    else
    {
        this->positionTir = Position(1500, 0);
    }

/*
    if(coteDuMammouth == COTE_NOTRE_DEPART)
    {
        positionsTire[0] = Position(1000, 500, isBlue);
        directionsTire[0] = Position(1000, 500, isBlue);

        positionsTire[1] = Position(1000, 500, isBlue);
        directionsTire[1] = Position(1000, 500, isBlue);

        positionsTire[2] = Position(1000, 500, isBlue);
        directionsTire[2] = Position(1000, 500, isBlue);

        positionsTire[3] = Position(1000, 500, isBlue);
        directionsTire[3] = Position(1000, 500, isBlue);

        positionsTire[4] = Position(1000, 500, isBlue);
        directionsTire[4] = Position(1000, 500, isBlue);

        positionsTire[5] = Position(1000, 500, isBlue);
        directionsTire[5] = Position(1000, 500, isBlue);
    }
    else if(coteDuMammouth == COTE_DEPART_ADVERSAIRE)
    {
        positionsTire[0] = Position(1000, 500, isBlue);
        directionsTire[0] = Position(1000, 500, isBlue);

        positionsTire[1] = Position(1000, 500, isBlue);
        directionsTire[1] = Position(1000, 500, isBlue);

        positionsTire[2] = Position(1000, 500, isBlue);
        directionsTire[2] = Position(1000, 500, isBlue);

        positionsTire[3] = Position(1000, 500, isBlue);
        directionsTire[3] = Position(1000, 500, isBlue);

        positionsTire[4] = Position(1000, 500, isBlue);
        directionsTire[4] = Position(1000, 500, isBlue);

        positionsTire[5] = Position(1000, 500, isBlue);
        directionsTire[5] = Position(1000, 500, isBlue);
    }*/
    status = 0;
}

TireFilet::~TireFilet()
{
    //dtor
}

int TireFilet::update()
{

    if (status == 0)
    {
        status = 1;
    }

    else if (status == 1) // mise en place du robot
    {
        StrategieV2::setCurrentGoal(positionDepart, false);
        status++;
    }
    else if (status == 2) // position tir 1
    {
        Position vect = positionDepart - Odometrie::odometrie->getPos().getPosition();

        if(vect.getNorme() < (int) this->precisionPosition)
        {
            //StrategieV2::setCurrentGoal((this->positionTir), false);
            StrategieV2::lookAt(this->positionTir);
            status++;
        }
    }
    /*
    else if(status == 3)
    {
        Position vect = this->positionsTire[0] - Odometrie::odometrie->getPos().getPosition();
        if(vect.getNorme() < (int) this->precisionPosition)
        {
            StrategieV2::lookAt(this->directionsTire[0]);//On aligne le tir en direction du mammouth
            status++;
        }
    }
    else if(status == 4)
    {
        Position vect = this->directionsTire[0] - Odometrie::odometrie->getPos().getPosition();
        if(arcsin(vect.getX(), vect.getY()) < (int) this->precisionAngle)
        {
            // OPEN FIRE!
#ifndef ROBOTHW
            qDebug() << "Feu !";
#endif
            status++;
        }
    }
    else if(status < 53)//On attend pendant (53-4) * 5ms, le temps que le tire parte
    {
        status++;
    }











    else if(status == 53)
    {
        //Rentrer le bras
#ifndef ROBOTHW
        qDebug() << "Rentrée du bras";
#endif
        status++;
    }
    else if(status < 103)//On attend pendant, le temps que le bras rentre
    {
        status++;
    }
    else if(status == 103)//On revient au départ de l'étape, en marche arrière
    {
        StrategieV2::setCurrentGoal(positionDepart, true);
        status++;
    }
    else if(status == 104)//On passe à l'étape suivante
    {
        Position vect = positionDepart - Odometrie::odometrie->getPos().getPosition();

        if(vect.getNorme() < (int) this->precision)
        {
            status = -1;
        }
    }*/

    return status;
}
//#endif //PASENCORECOMPILABLE
