#include "ascenseur.h"

Ascenseur* Ascenseur::singleton = 0;

#ifdef ROBOTHW
Ascenseur::Ascenseur()
{
    this->positionAscenseurLeve = 0x00;
    this->positionAscenseurBaisse = 0x00;
    this->positionPincesAscenseurOuvertes = 0x00;
    this->positionPincesAscenseurFermees = 0x00;
    this->moteurAscenseur = 0;
    this->moteurPinceGauche = 0;
    this->moteurPinceDroite = 0;

    this->fermerPincesAscenseur();
    this->baisserAscenseur();
}

Ascenseur* Ascenseur::getSingleton()
{
    if (singleton==0)
        singleton = new Ascenseur();
    return singleton;
}

void Ascenseur::leverAscenseur()
{
    ServosNumeriques::moveTo(positionAscenseurLeve, moteurAscenseur);
}

void Ascenseur::baisserAscenseur()
{
    ServosNumeriques::moveTo(positionAscenseurBaisse, moteurAscenseur);
}

void Ascenseur::ouvrirPincesAscenseurs()
{
    ServosNumeriques::moveTo(positionPincesAscenseurOuvertes, moteurPinceDroite);
    ServosNumeriques::moveTo(positionPincesAscenseurOuvertes, moteurPinceGauche);
}

void Ascenseur::fermerPincesAscenseur()
{
    ServosNumeriques::moveTo(positionPincesAscenseurFermees, moteurPinceDroite);
    ServosNumeriques::moveTo(positionPincesAscenseurFermees, moteurPinceGauche);
}

#else

Ascenseur::Ascenseur(){}

void Ascenseur::leverAscenseur(){}

void Ascenseur::baisserAscenseur(){}

void Ascenseur::ouvrirPincesAscenseurs(){}

void Ascenseur::fermerPincesAscenseur(){}

Ascenseur *Ascenseur::getSingleton()
{
    if (singleton == 0)
        singleton = new Ascenseur();
    return singleton;
}

#endif
