#include "pinces.h"

Pinces* Pinces::singleton = 0;

#ifdef ROBOTHW
Pinces::Pinces()
{
    this->positionPincesOuvertes = 0x00;
    this->positionPincesFermees = 0x0227;
    this->moteurPinceGauche = 15;
    this->moteurPinceDroite = 16;

    this->fermerPinces();
}

Pinces* Pinces::getSingleton()
{
    if (singleton == 0)
        singleton = new Pinces();
    return singleton;
}

void Pinces::ouvrirPinces()
{
    ServosNumeriques::moveTo(positionPincesOuvertes, moteurPinceDroite);
    ServosNumeriques::moveTo(positionPincesOuvertes, moteurPinceGauche);
}

void Pinces::fermerPinces()
{
    ServosNumeriques::moveTo(positionPincesFermees, moteurPinceDroite);
    ServosNumeriques::moveTo(positionPincesFermees, moteurPinceGauche);
}

#else

Pinces::Pinces(){}

void Pinces::ouvrirPinces(){}

void Pinces::fermerPinces(){}

Pinces *Pinces::getSingleton()
{
    if (singleton == 0)
        singleton = new Pinces();
    return singleton;
}

#endif

bool Pinces::getEstDispo()
{
    return estDispo;
}

void Pinces::setEstDispo()
{
    this->estDispo = true;
}

void Pinces::setEstNonDispo()
{
    this->estDispo = false;
}

