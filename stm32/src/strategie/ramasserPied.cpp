#include "ramasserPied.h"
#include "ascenseur.h"
#include "strategieV2.h"
#include "mediumLevelAction.h"
#include "command.h"
#include "pinces.h"

//MLA : Medium Level Action
#define MLA_RAMASSER_PIED_APPROCHE 1
#define MLA_RAMASSER_PIED_REGARDE 20
#define MLA_RAMASSER_PIED_LEVE 50
#define MLA_RAMASSER_PIED_APPROCHE_PLUS 50
#define MLA_RAMASSER_PIED_OUVRE 50
#define MLA_RAMASSER_PIED_BAISSE 50
#define MLA_RAMASSER_PIED_FERME 50
#define MLA_RAMASSER_PIED_PART 1


#ifndef ROBOTHW
#include <QDebug>
#endif

RamasserPied::RamasserPied(){}

RamasserPied::RamasserPied(Position goalposition): MediumLevelAction(goalposition){}

RamasserPied::~RamasserPied(){}

Etape::EtapeType RamasserPied::getType()
{
    return Etape::RAMASSER_PIED;
}

int RamasserPied::update()
{

    if (status == 0)
    {
    #ifndef ROBOTHW
            qDebug() << "action pied";
    #endif
        StrategieV2::setCurrentGoal(this->goalPosition, this->goBack, VITESSE_LINEAIRE_MAX, -100.0, 200.f);
        Ascenseur::getSingleton()->leverAscenseur();
        status++;
    }

    else if (status == MLA_RAMASSER_PIED_APPROCHE)
    {
        if (Command::isNear(goalPosition, 200.0f))
        {
            StrategieV2::lookAt(goalPosition);
            status++;
        }
    }

    else if (status == MLA_RAMASSER_PIED_REGARDE + MLA_RAMASSER_PIED_APPROCHE)
    {
        if (Command::isLookingAt(goalPosition))
        {
            Ascenseur::getSingleton()->ouvrirAscenseur();
            status++;
        }
    }

    else if (status == MLA_RAMASSER_PIED_OUVRE + MLA_RAMASSER_PIED_REGARDE + MLA_RAMASSER_PIED_APPROCHE)
    {
        Ascenseur::getSingleton()->baisserAscenseur();
        status++;
    }

    else if (status == MLA_RAMASSER_PIED_BAISSE + MLA_RAMASSER_PIED_OUVRE + MLA_RAMASSER_PIED_REGARDE + MLA_RAMASSER_PIED_APPROCHE)
    {
        Ascenseur::getSingleton()->fermerAscenseur();
        status++;
    }

    else if (status == MLA_RAMASSER_PIED_FERME + MLA_RAMASSER_PIED_BAISSE + MLA_RAMASSER_PIED_OUVRE + MLA_RAMASSER_PIED_REGARDE + MLA_RAMASSER_PIED_APPROCHE)
    {
        Ascenseur::getSingleton()->leverAscenseur();
        status++;
    }

    else if (status == MLA_RAMASSER_PIED_LEVE+ MLA_RAMASSER_PIED_FERME + MLA_RAMASSER_PIED_BAISSE + MLA_RAMASSER_PIED_OUVRE + MLA_RAMASSER_PIED_REGARDE + MLA_RAMASSER_PIED_APPROCHE)
    {
#ifndef ROBOTHW
        qDebug() << "Etape pied finie";
#endif
        StrategieV2::setCurrentGoal(this->goalPosition, this->goBack);

        Ascenseur::getSingleton()->addPied();
        status++;
    }

    else if (status == MLA_RAMASSER_PIED_LEVE+ MLA_RAMASSER_PIED_FERME + MLA_RAMASSER_PIED_BAISSE + MLA_RAMASSER_PIED_OUVRE + MLA_RAMASSER_PIED_REGARDE + MLA_RAMASSER_PIED_APPROCHE+MLA_RAMASSER_PIED_PART)
    {
        if (Command::isNear(goalPosition))
        {
            StrategieV2::lookAt(goalPosition);
            status = -1;
        }
    }

    else
    {
        status++;
    }

    return status;
}
