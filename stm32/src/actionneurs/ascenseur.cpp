#include "ascenseur.h"

Ascenseur* Ascenseur::singleton = 0;

#ifdef ROBOTHW
Ascenseur::Ascenseur()
{
    this->positionAscenseurLeve = 0x00;
    this->positionAscenseurBaisse = 0x00;
    this->positionPincesAscenseurOuvertes = 0x00;
    this->positionPincesAscenseurFermees = 0x0227;
    this->moteurAscenseur = 0;
    this->moteurPinceGauche = 15;
    this->moteurPinceDroite = 16;

    this->fermerPincesAscenseur();
    this->baisserAscenseur();
}

Ascenseur* Ascenseur::getSingleton()
{
    //TO DO  : decommenter le bout de code suivant et le debugger

    if (singleton==0)
        singleton = new Ascenseur();

/*    if (singleton->getNbrPiedsStockes==0)
        singleton->positionAscenseurLeve = 0x00;
    if (singleton->getNbrPiedsStockes==1)
        singleton->positionAscenseurLeve = 0x00;
    if (singleton->getNbrPiedsStockes==2)
        singleton->positionAscenseurLeve = 0x00;  */

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

void Ascenseur::ouvrirPincesAscenseur()
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

void Ascenseur::ouvrirPincesAscenseur(){}

void Ascenseur::fermerPincesAscenseur(){}

Ascenseur *Ascenseur::getSingleton()
{
    if (singleton == 0)
        singleton = new Ascenseur();
    return singleton;
}

#endif

int Ascenseur::getNbrPiedsStockes()
{
    return nbrPiedsStockes;
}

int Ascenseur::setNbrPiedsStockes(int nbrPiedsStockes)
{
    this->nbrPiedsStockes = nbrPiedsStockes;
}
