#include "ascenseur.h"

#include <QDebug>

#define POS_ASC_LEVE 0x00
#define POS_ASC_BAISSE 0x00
#define POS_ASC_OUVERT 0x0210
//#define POS_ASC_OUVERT_DEPOT 0x01D0
#define POS_ASC_FERME 0x0230
#define INDEX_SERVO_ASC 0
#define INDEX_SERVO_PORTE_DROITE 16
#define INDEX_SERVO_PORTE_GAUCHE 15

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
    this->fermerPincesAscenseur();
    this->baisserAscenseur();
}

Ascenseur* Ascenseur::getSingleton()
{
    //TO DO  : decommenter le bout de code suivant et le debugger

    if (singleton==0)
        singleton = new Ascenseur();

/*    if (singleton->getNbrPiedsStockes==0)
        singleton->POS_ASC_LEVE = 0x00;
    if (singleton->getNbrPiedsStockes==1)
        singleton->POS_ASC_LEVE = 0x00;
    if (singleton->getNbrPiedsStockes==2)
        singleton->POS_ASC_LEVE = 0x00;  */

    return singleton;
}

void Ascenseur::leverAscenseur()
{
    ServosNumeriques::moveTo(POS_ASC_LEVE, INDEX_SERVO_ASC);
    leve = true;
}

void Ascenseur::baisserAscenseur()
{
    ServosNumeriques::moveTo(POS_ASC_BAISSE, INDEX_SERVO_ASC);
    leve = false;
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

bool Ascenseur::estLeve ()
{
    return leve;
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
