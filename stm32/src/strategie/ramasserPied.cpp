#include "ramasserPied.h"
#include "ascenseur.h"
#include "pinces.h"
#include "strategieV2.h"
#include "mediumLevelAction.h"
#include "command.h"
#include "pinces.h"

//MLA : Medium Level Action
#define MLA_RAMASSER_PIED_APPROCHE 1
#define MLA_RAMASSER_PIED_REGARDE 1
#define MLA_RAMASSER_PIED_OUVRIR_PINCES 200
#define MLA_RAMASSER_PIED_APPROCHE_PLUS 1
#define MLA_RAMASSER_PIED_SAISIR 200
#define MLA_RAMASSER_PIED_OUVRE_ASC 200
#define MLA_RAMASSER_PIED_BAISSER_ASC 200
#define MLA_RAMASSER_PIED_FERME 200
#define MLA_RAMASSER_PIED_LEVE 200
#define MLA_RAMASSER_PIED_FERMER_PINCES 200
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

    /*if (status == 0)
    {
    #ifndef ROBOTHW
            qDebug() << "action pied";
    #endif
        StrategieV2::setCurrentGoal(this->goalPosition, this->goBack, VITESSE_LINEAIRE_MAX, -100.0, 500.f);
        Ascenseur::getSingleton()->leverAscenseur();
        status++;
    }

    else if (status == MLA_RAMASSER_PIED_APPROCHE)
    {
        if (Command::isNear(goalPosition, 100.0f))
        {
            StrategieV2::lookAt(goalPosition);
            status++;
        }
    }
    */
    if(status == 0)
    {
        StrategieV2::lookAt(goalPosition);
        status = MLA_RAMASSER_PIED_REGARDE + MLA_RAMASSER_PIED_APPROCHE;
    }

    else if (status == MLA_RAMASSER_PIED_REGARDE + MLA_RAMASSER_PIED_APPROCHE)
    {
        if (Command::isLookingAt(goalPosition))
        {
            Pinces::getSingleton()->ouvrirPinces();
            status++;
            //status = MLA_RAMASSER_PIED_APPROCHE_PLUS + MLA_RAMASSER_PIED_OUVRIR_PINCES + MLA_RAMASSER_PIED_REGARDE + MLA_RAMASSER_PIED_APPROCHE;
        }
    }

    else if (status == MLA_RAMASSER_PIED_OUVRIR_PINCES + MLA_RAMASSER_PIED_REGARDE + MLA_RAMASSER_PIED_APPROCHE)
    {
        StrategieV2::setCurrentGoal(this->goalPosition, this->goBack, VITESSE_LINEAIRE_MAX, -100.0, 140.f);
        qDebug() << "Deplacement";
        status++;
        //qDebug() << status;
    }

    else if (status == MLA_RAMASSER_PIED_APPROCHE_PLUS + MLA_RAMASSER_PIED_OUVRIR_PINCES + MLA_RAMASSER_PIED_REGARDE + MLA_RAMASSER_PIED_APPROCHE)
    {
        if(Command::isNear(goalPosition, 140.f))
        {
            StrategieV2::stop();
            Pinces::getSingleton()->saisirPied();
            status++;
        }
    }

    else if (status == MLA_RAMASSER_PIED_SAISIR + MLA_RAMASSER_PIED_APPROCHE_PLUS
                        + MLA_RAMASSER_PIED_REGARDE + MLA_RAMASSER_PIED_APPROCHE + MLA_RAMASSER_PIED_OUVRIR_PINCES)
    {
            Ascenseur::getSingleton()->ouvrirAscenseur();
            status++;
    }


    else if (status == MLA_RAMASSER_PIED_OUVRE_ASC + MLA_RAMASSER_PIED_SAISIR + MLA_RAMASSER_PIED_APPROCHE_PLUS
             + MLA_RAMASSER_PIED_REGARDE + MLA_RAMASSER_PIED_APPROCHE + MLA_RAMASSER_PIED_OUVRIR_PINCES)
    {
        Ascenseur::getSingleton()->baisserAscenseur();
        status++;
    }

    else if (status == MLA_RAMASSER_PIED_BAISSER_ASC + MLA_RAMASSER_PIED_OUVRE_ASC + MLA_RAMASSER_PIED_SAISIR + MLA_RAMASSER_PIED_APPROCHE_PLUS
             + MLA_RAMASSER_PIED_REGARDE + MLA_RAMASSER_PIED_APPROCHE + MLA_RAMASSER_PIED_OUVRIR_PINCES)
    {
        Ascenseur::getSingleton()->fermerAscenseur();
        status++;
    }

    else if (status == MLA_RAMASSER_PIED_FERME + MLA_RAMASSER_PIED_BAISSER_ASC + MLA_RAMASSER_PIED_OUVRE_ASC
             + MLA_RAMASSER_PIED_SAISIR + MLA_RAMASSER_PIED_APPROCHE_PLUS + MLA_RAMASSER_PIED_REGARDE + MLA_RAMASSER_PIED_APPROCHE + MLA_RAMASSER_PIED_OUVRIR_PINCES)
    {
        Ascenseur::getSingleton()->leverAscenseur();
        status++;
    }

    else if (status == MLA_RAMASSER_PIED_LEVE+ MLA_RAMASSER_PIED_FERME + MLA_RAMASSER_PIED_BAISSER_ASC + MLA_RAMASSER_PIED_OUVRE_ASC
             + MLA_RAMASSER_PIED_SAISIR + MLA_RAMASSER_PIED_APPROCHE_PLUS + MLA_RAMASSER_PIED_REGARDE + MLA_RAMASSER_PIED_APPROCHE + MLA_RAMASSER_PIED_OUVRIR_PINCES)
    {

        StrategieV2::setCurrentGoal(this->goalPosition, this->goBack);
        qDebug() << "Deplacement 2";
        Pinces::getSingleton()->fermerPinces();
        Ascenseur::getSingleton()->addPied();
        status++;
    }

    else if (status == MLA_RAMASSER_PIED_FERMER_PINCES + MLA_RAMASSER_PIED_LEVE + MLA_RAMASSER_PIED_FERME + MLA_RAMASSER_PIED_BAISSER_ASC + MLA_RAMASSER_PIED_OUVRE_ASC
             + MLA_RAMASSER_PIED_SAISIR + MLA_RAMASSER_PIED_APPROCHE_PLUS + MLA_RAMASSER_PIED_REGARDE + MLA_RAMASSER_PIED_APPROCHE + MLA_RAMASSER_PIED_OUVRIR_PINCES)
    {
        if (Command::isNear(goalPosition))
        {
#ifndef ROBOTHW
        qDebug() << "Etape pied finie";
#endif
            status = -1;
        }
    }

    else
    {
        status++;
    }

    return status;
}
