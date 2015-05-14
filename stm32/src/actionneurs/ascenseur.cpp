#include "ascenseur.h"

#define POS_ASC_OUVERT 0x0200
//#define POS_ASC_OUVERT_DEPOT 0x01D0
#define POS_ASC_FERME 0x0235

#define INDEX_SERVO_ASC 42
#define INDEX_SERVO_PORTE_DROITE 15
#define INDEX_SERVO_PORTE_GAUCHE 16

#ifndef ROBOTHW
    #include <QDebug>
    #include "table.h"
#endif

Ascenseur* Ascenseur::singleton = 0;

Ascenseur *Ascenseur::getSingleton()
{
    if (singleton == 0)
        singleton = new Ascenseur();
    return singleton;
}

    Ascenseur::Ascenseur()
#ifdef ROBOTHW
       : microSwitchBas(MicroSwitch(GPIOE, GPIO_Pin_3)), microSwitchHaut(MicroSwitch(GPIOE, GPIO_Pin_2))
#endif
{
    this->fermerAscenseur();
    this->leverAscenseur();
    this->nbrPiedsStockes = 0;
#ifdef ROBOTHW
    ServosNumeriques::changeContinuousRotationMode(INDEX_SERVO_ASC, true);
#endif

}

void Ascenseur::update()
{
    switch(status)
    {
        case UP:
            if(estEnHaut())
                arreterAscenseur();
        case DOWN:
            if(estEnBas())
                arreterAscenseur();
    }
}

void Ascenseur::leverAscenseur()
{
#ifdef ROBOTHW
        ServosNumeriques::moveAtSpeed(0x01ff, INDEX_SERVO_ASC, false);
#else
    qDebug() << "On leve l'ascenseur";

    // supprime le pied qui est dans l'ascenseur de la table
//    PositionPlusAngle ppa = Table::getMainInstance()->getMainRobot()->getPos();
//    Position pElevator = ppa.getPosition() + Position(140. * cos(ppa.getAngle()), 140. * sin(ppa.getAngle()));
//    std::vector<Objet*> objects = Table::getMainInstance()->findObjectsNear(pElevator, 50., Objet::STAND);

//    for(std::vector<Objet*>::iterator it = objects.begin(); it != objects.end(); ++it)
//        (*it)->moveOutOfField();
#endif
    status = UP;
}

void Ascenseur::baisserAscenseur()
{
#ifdef ROBOTHW
    ServosNumeriques::moveAtSpeed(0x01ff, INDEX_SERVO_ASC, true);
#else
    qDebug() << "On baisse l'ascenseur";
#endif
    status = DOWN;
}

void Ascenseur::arreterAscenseur()
{
#ifdef ROBOTHW
    ServosNumeriques::moveAtSpeed(0x0000, INDEX_SERVO_ASC);
#else
    qDebug() << "On arrete l'ascenseur";
#endif
    status = STOP;
}

void Ascenseur::ouvrirAscenseur()
{
#ifdef ROBOTHW
    ServosNumeriques::moveTo(POS_ASC_OUVERT, INDEX_SERVO_PORTE_DROITE);
    ServosNumeriques::moveTo(POS_ASC_OUVERT, INDEX_SERVO_PORTE_GAUCHE);
#else
    qDebug() << "On ouvre l'ascenseur";
#endif
    ouvert = true;
}

void Ascenseur::fermerAscenseur()
{
#ifdef ROBOTHW
    ServosNumeriques::moveTo(POS_ASC_FERME, INDEX_SERVO_PORTE_DROITE);
    ServosNumeriques::moveTo(POS_ASC_FERME, INDEX_SERVO_PORTE_GAUCHE);
#else
    qDebug() << "On ferme l'ascenseur";
#endif
    ouvert = false;
}

bool Ascenseur::estEnHaut()
{
#ifdef ROBOTHW
    return this->microSwitchHaut.ferme();
#else
    return true;
#endif
}

bool Ascenseur::estEnBas()
{
#ifdef ROBOTHW
    return this->microSwitchBas.ferme();
#else
    return true;
#endif
}

bool Ascenseur::estOuvert()
{
    return ouvert;
}

int Ascenseur::getNbrPiedsStockes()
{
    return nbrPiedsStockes;
}

void Ascenseur::setNbrPiedsStockes(int nbrPiedsStockes)
{
    this->nbrPiedsStockes = nbrPiedsStockes;
}

void Ascenseur::addPied()
{
    this->nbrPiedsStockes++;
}

void Ascenseur::resetNbrPiedsStockes()
{
    this->nbrPiedsStockes = 0;
}
