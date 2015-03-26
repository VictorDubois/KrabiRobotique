#include "feuCote.h"
#include "strategieV2.h"
#include "actionGoTo.h"
#include "leds.h"
#include "odometrie.h"
#include "asservissement.h"

#ifndef ROBOTHW
#include <QDebug>
#endif

FeuCote::FeuCote(){}

FeuCote::FeuCote(bool isBlue, Position positionDepart, int bordureFeu, bool sensFeu, bool coteDuFeu, float precision) : MediumLevelAction()
{
    this->isBlue = isBlue;
    this->positionDepart = positionDepart;
    this->bordureFeu = bordureFeu;
    this->sensFeu = sensFeu;
    this->coteDuFeu = coteDuFeu;
    this->precision = precision;

    if(this->bordureFeu == NOTRE_BORDURE)
    {
        this->positionColleBordure = Position(positionDepart.getX()-75, positionDepart.getY(), isBlue);
    }
    else if(this->bordureFeu == BORDURE_MILIEU)
    {
        this->positionColleBordure = Position(positionDepart.getX(), positionDepart.getY()-75, isBlue);
    }
    else if(this->bordureFeu == BORDURE_ADVERSAIRE)
    {
        this->positionColleBordure = Position(positionDepart.getX()+75, positionDepart.getY(), isBlue);
    }

    if(this->bordureFeu == NOTRE_BORDURE)
    {
        this->positionLookAt = Position(0, positionDepart.getY(), isBlue);
    }
    else if(this->bordureFeu == BORDURE_MILIEU)
    {
        this->positionLookAt = Position(positionDepart.getX(), 0, isBlue);
    }
    else if(this->bordureFeu == BORDURE_ADVERSAIRE)
    {
        this->positionLookAt = Position(3000, positionDepart.getY(), isBlue);
    }

    status = 0;
}

FeuCote::~FeuCote()
{
    //dtor
}

int FeuCote::update()
{
    if (status == 0)
    {
#ifndef ROBOTHW
        qDebug() << "feuCote";
#endif
        status = 1;
    }

    else if (status == 1) // mise en place du robot
    {
        StrategieV2::setCurrentGoal(positionDepart, false);
        status++;
    }
    else if (status == 2) // mise en place du robot
    {
        Position vect = positionDepart - Odometrie::odometrie->getPos().getPosition();

        if(vect.getNorme() < (int) this->precision)
        {
            StrategieV2::setCurrentGoal(this->positionColleBordure, false);

            status++;
        }
    }
    else if(status == 3)
    {
        Position vect = this->positionColleBordure - Odometrie::odometrie->getPos().getPosition();
        if(vect.getNorme() < (int) this->precision)
        {

            StrategieV2::lookAt(this->positionLookAt);//On garde le même angle pour éviter que le robot ne dévie
            //Sortir le bras pour pousser de feu
            BrasLateral::getLeft()->collapse();
#ifndef ROBOTHW
            qDebug() << "Sortie du bras";
#endif
            status++;
        }
    }
    else if(status < 53)//On attend pendant (53-3) * 5ms, le temps que le bras sorte
    {
        status++;
    }
    else if(status == 53)
    {
        //Rentrer le bras
        BrasLateral::getLeft()->expand();
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
    }

    return status;
}
