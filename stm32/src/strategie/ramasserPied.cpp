#include "ramasserPied.h"
#include "ascenseur.h"
#include "strategieV2.h"
#include "mediumLevelAction.h"
#include "command.h"

//MLA : Medium Level Action
#define MLA_RAMASSER_PIED_APPROCHE 1
#define MLA_RAMASSER_PIED_REGARDE 1
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

int RamasserPied::update()
{

    if (status == 0)
    {
    #ifndef ROBOTHW
            qDebug() << "action pied";
    #endif
        StrategieV2::setCurrentGoal(this->goalPosition, this->goBack);
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

    else if (status == MLA_RAMASSER_PIED_APPROCHE)
    {
        if (Command::isNear(goalPosition, 175.0f))
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
    }

    else if (status == MLA_RAMASSER_PIED_FERME + MLA_RAMASSER_PIED_BAISSE + MLA_RAMASSER_PIED_OUVRE + MLA_RAMASSER_PIED_REGARDE + MLA_RAMASSER_PIED_APPROCHE)
    {
        Ascenseur::getSingleton()->leverAscenseur();
    }

    else if (status == MLA_RAMASSER_PIED_FERME + MLA_RAMASSER_PIED_BAISSE + MLA_RAMASSER_PIED_OUVRE + MLA_RAMASSER_PIED_REGARDE + MLA_RAMASSER_PIED_APPROCHE)
    {
#ifndef ROBOTHW
        qDebug() << "Etape pied finie";
#endif
        StrategieV2::setCurrentGoal(this->goalPosition, this->goBack);
        status++;
        int nouveauNbrPiedsStockes = Ascenseur::getSingleton()->getNbrPiedsStockes() + 1;
        Ascenseur::getSingleton()->setNbrPiedsStockes(nouveauNbrPiedsStockes);
    }

    else if (status == 84)
    {
        if (Command::isNear(goalPosition))
        {
            StrategieV2::lookAt(goalPosition);
            status++;
        }
    }

    else if (status == 85)
    {
        status = -1;
    }
    else
    {
        status++;
    }

    return status;
}
