#include "brasTapis.h"


BrasTapis* BrasTapis::singleton = 0;

#ifdef ROBOTHW
BrasTapis::BrasTapis(COTE cote)
{
    if (cote == DROIT)
    {
        this->positionBrasOuvert = 0x00;
        this->positionBrasFerme = 0x00;
        this->positionPinceOuverte = 0x00;
        this->positionPinceFermee = 0x00;
        this->moteurBras = 0;
        this->moteurPinceHaut = 0;
        this->moteurPinceBas = 0;
    }

    else if (cote == GAUCHE)
    {
        this->positionBrasOuvert = 0x00;
        this->positionBrasFerme = 0x00;
        this->positionPinceOuverte = 0x00;
        this->positionPinceFermee = 0x00;
        this->moteurBras = 0;
        this->moteurPinceHaut = 0;
        this->moteurPinceBas = 0;
    }
    this->fermerBras();
}

//TODO trouver une solution : comment discerner dans le singleton que l'on veut le bras droit ou le bras gauche? (2 getSingleton?)

BrasTapis* BrasTapis::getSingleton(COTE cote)
{
    singleton = new BrasTapis(cote);
    return singleton;
}


void BrasTapis::ouvrirBras()
{
    ServosNumeriques::moveTo(positionBrasOuvert, moteurBras);
}

void BrasTapis::fermerBras()
{
    ServosNumeriques::moveTo(positionBrasFerme, moteurBras);
}

void BrasTapis::ouvrirPince()
{
    ServosNumeriques::moveTo(positionPinceOuverte, moteurPinceHaut);
    ServosNumeriques::moveTo(positionPinceOuverte, moteurPinceBas);
}

void BrasTapis::fermerPince()
{
    ServosNumeriques::moveTo(positionPinceFermee, moteurPinceHaut);
    ServosNumeriques::moveTo(positionPinceFermee, moteurPinceBas);
}


#else


BrasTapis::BrasTapis(){}

void BrasTapis::ouvrirBras(){}

void BrasTapis::fermerBras(){}

void BrasTapis::ouvrirPince(){}

void BrasTapis::fermerPince(){}

BrasTapis *BrasTapis::getSingleton(COTE cote)
{
    return singleton;
}


#endif
