#include "pinces.h"

Pinces* Pinces::singleton = 0;

#ifdef ROBOTHW
Pinces::Pinces()
{
    this->positionPincesOuvertes = 0x01D0;
    this->positionPincesFermees = 0x0327;
    this->moteurPinceGauche = 10;
    this->moteurPinceDroite = 11;

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

