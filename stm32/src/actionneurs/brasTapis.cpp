#include "brasTapis.h"

BrasTapis* BrasTapis::singletonGauche = 0;
BrasTapis* BrasTapis::singletonDroit = 0;

#ifdef ROBOTHW
BrasTapis::BrasTapis(COTE cote)
{
    //Angle des servos: on augmente la valeur pour augmenter l'angle (servo, verticale, bras)
    if(cote == DROIT){
        this->moteurBras = 20;
        this->positionBrasOuvert = 0x0285;//0x00ff;
        this->positionBrasFerme = 0x0200;//0x0200;//0x01f0;
    }
    else{//GAUCHE
        this->moteurBras = 13;
        this->positionBrasOuvert = 0x0315;//0x0400;//0x00ff;
        this->positionBrasFerme = 0x0275;//0x0330;//0x0200;//0x01f0;
    }
    this->fermerBras();
}

BrasTapis* BrasTapis::getSingleton(COTE cote)
{
    if(cote == DROIT)
    {
        if(singletonDroit == 0)
            singletonDroit = new BrasTapis(DROIT);
        return singletonDroit;
    }
    else//GAUCHE
    {
        if(singletonGauche == 0)
            singletonGauche = new BrasTapis(GAUCHE);
        return singletonGauche;
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
