#include "ascenseur.h"

#ifdef ROBOTHW
//    #include <QDebug>
#endif



#define POS_ASC_OUVERT 0x0200
//#define POS_ASC_OUVERT_DEPOT 0x01D0
#define POS_ASC_FERME 0x0235
#define INDEX_SERVO_ASC 42
#define INDEX_SERVO_PORTE_DROITE 15
#define INDEX_SERVO_PORTE_GAUCHE 16

Ascenseur* Ascenseur::singleton = 0;

Ascenseur *Ascenseur::getSingleton()
{
    if (singleton == 0)
        singleton = new Ascenseur();
    return singleton;
}

#ifdef ROBOTHW
Ascenseur::Ascenseur()
{
    #ifdef STM32F10X_CL // pour la STM32 H107 2013 v2 :
        this->microSwitchBas = MicroSwitch(GPIOE, GPIO_Pin_3);
        this->microSwitchHaut = MicroSwitch(GPIOE, GPIO_Pin_2);
    #endif

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

#else

Ascenseur::Ascenseur(){}

void Ascenseur::leverAscenseur()
{
            qDebug() << "On leve l'ascenseur";
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

#endif

bool Ascenseur::estEnHaut()
{
    return this->microSwitchHaut.ferme();
}

bool Ascenseur::estEnBas()
{
    return this->microSwitchBas.ferme();
}

bool Ascenseur::estOuvert ()
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
