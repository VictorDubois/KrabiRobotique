#include "DepotFeu.h"

DepotFeu::DepotFeu(bool isBlue, Position posFoyer, float precision)
{
    this->isBlue = isBlue;
    this->precision = precision;
    this->posFoyer = posFoyer;

    Brak* bras = Brak::getSingleton();

    status = 0;
}

DepotFeu::~DepotFeu()
{
    //dtor
}

int DepotFeu::update()
{
    if (status == 0)
        status = 1;

    else if (status == 1) // mise en place du robot
    {
        StrategieV2::setCurrentGoal(posFoyer, false);

#ifndef ROBOTHW
            qDebug() << "deplacement vers le foyer";
#endif
        status++;
    }
    else if (status == 2)
    {
        Position vect = posFoyer - Odometrie::odometrie->getPos().getPosition();

        if(vect.getNorme() < (int) this->precision)
        {
            StrategieV2::setCurrentGoal(this->posFoyer, false, 1);
#ifndef ROBOTHW
            qDebug() << "arrivé au foyer";
#endif
            status++;
        }
    }
    else if (status == 3)
    {
        bras->positionBasse();
#ifndef ROBOTHW
            qDebug() << "abaissage du bras";
#endif
            status++;
    }
    else if (status < 200)
    {
        status++;
    }
    else if (status == 200)
    {
#ifndef ROBOTHW
            qDebug() << "le bras est en position basse. On relache le feu";
#endif
        bras->relacherFeu();
        status++;
    }
    else if (status < 225)
    {
        status++;
    }
    else if (status == 226)
    {
#ifndef ROBOTHW
            qDebug() << "le feu est relache. On remonte le bras";
#endif
        bras->positionHaute();
        status++;
    }
    else if (status == 224)
    {
#ifndef ROBOTHW
            qDebug() << "le bras est en train de remonter. Fin";
#endif
    }
     return status;
}

