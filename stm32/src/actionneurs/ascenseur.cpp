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

#ifdef ROBOTHW

#ifdef STM32F10X_CL // pour la STM32 H107 2013 v2 :
    Ascenseur::Ascenseur() : microSwitchBas(MicroSwitch(GPIOE, GPIO_Pin_3)), microSwitchHaut(MicroSwitch(GPIOE, GPIO_Pin_2))
#else
    #error Should not be used with KJ
#endif
{
//    this->fermerAscenseur();
//    this->baisserAscenseur();
    ServosNumeriques::changeContinuousRotationMode(INDEX_SERVO_ASC, true);
}

void Ascenseur::leverAscenseur()
{
    ServosNumeriques::moveAtSpeed(0x01ff, INDEX_SERVO_ASC, false);
}

void Ascenseur::baisserAscenseur()
{
    ServosNumeriques::moveAtSpeed(0x01ff, INDEX_SERVO_ASC, true);
}

void Ascenseur::arreterAscenseur()
{
    ServosNumeriques::moveAtSpeed(0x0000, INDEX_SERVO_ASC);
}

void Ascenseur::ouvrirAscenseur()
{
    ServosNumeriques::moveTo(POS_ASC_OUVERT, INDEX_SERVO_PORTE_DROITE);
    ServosNumeriques::moveTo(POS_ASC_OUVERT, INDEX_SERVO_PORTE_GAUCHE);
    ouvert = true;
}

void Ascenseur::fermerAscenseur()
{
    ServosNumeriques::moveTo(POS_ASC_FERME, INDEX_SERVO_PORTE_DROITE);
    ServosNumeriques::moveTo(POS_ASC_FERME, INDEX_SERVO_PORTE_GAUCHE);
    ouvert = false;
}

bool Ascenseur::estEnHaut()
{
    return this->microSwitchHaut.ferme();
}

bool Ascenseur::estEnBas()
{
    return this->microSwitchBas.ferme();
}

#else

Ascenseur::Ascenseur(){}

void Ascenseur::leverAscenseur()
{
    qDebug() << "On leve l'ascenseur";

    // supprime le pied qui est dans l'ascenseur de la table
    PositionPlusAngle ppa = Table::getMainInstance()->getMainRobot()->getPos();
    Position pElevator = ppa.getPosition() + Position(140. * cos(ppa.getAngle()), 140. * sin(ppa.getAngle()));
    std::vector<Objet*> objects = Table::getMainInstance()->findObjectsNear(pElevator, 50., Objet::STAND);

    for(std::vector<Objet*>::iterator it = objects.begin(); it != objects.end(); ++it)
        (*it)->moveOutOfField();
}

void Ascenseur::baisserAscenseur()
{
    qDebug() << "On baisse l'ascenseur";
}

void Ascenseur::ouvrirAscenseur()
{
    qDebug() << "On ouvre l'ascenseur";
}

void Ascenseur::fermerAscenseur()
{
    qDebug() << "On ferme l'ascenseur";
}

bool Ascenseur::estEnHaut()
{
    return true;
}

bool Ascenseur::estEnBas()
{
    return true;
}

#endif

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
