#include "brasTapis.h"


BrasTapis* BrasTapis::singletonGauche = 0;
BrasTapis* BrasTapis::singletonDroit = 0;

#ifdef ROBOTHW
BrasTapis::BrasTapis(COTE cote)
{
    this->positionBrasOuvert = 0x0133;
    this->positionBrasFerme = 0x01f0;
    if(cote == DROIT)
        this->moteurBras = 20;
    else if (cote == GAUCHE)
        this->moteurBras = 13;
    this->fermerBras();
}

BrasTapis* BrasTapis::getSingleton(COTE cote)
{
    if(cote == GAUCHE)
    {
        if(singletonGauche == 0)
            singletonGauche = new BrasTapis(GAUCHE);
        return singletonGauche;
    }
    else if(cote == DROIT)
    {
        if(singletonDroit == 0)
            singletonDroit = new BrasTapis(DROIT);
        return singletonDroit;
    }
}

void BrasTapis::ouvrirBras()
{
    ServosNumeriques::moveTo(positionBrasOuvert, moteurBras);
}

void BrasTapis::fermerBras()
{
    ServosNumeriques::moveTo(positionBrasFerme, moteurBras);
}

#else


BrasTapis::BrasTapis(){}

void BrasTapis::ouvrirBras(){}

void BrasTapis::fermerBras(){}

BrasTapis *BrasTapis::getSingleton(COTE cote)
{
    return new BrasTapis();
}


#endif
