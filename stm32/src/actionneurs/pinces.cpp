#include "pinces.h"

#ifndef ROBOTHW
#include <QDebug>
#endif

Pinces* Pinces::singleton = 0;

Pinces::Pinces()
{
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
#ifdef ROBOTHW
    ServosNumeriques::moveTo(POS_PINCES_OUVERTES, INDEX_MOTEUR_PINCE_DROITE);
    ServosNumeriques::moveTo(POS_PINCES_OUVERTES, INDEX_MOTEUR_PINCE_GAUCHE);
#else
    qDebug() << "On ouvre les pinces";
#endif
}

void Pinces::fermerPinces()
{
#ifdef ROBOTHW
    ServosNumeriques::moveTo(POS_PINCES_FERMEES, INDEX_MOTEUR_PINCE_DROITE);
    ServosNumeriques::moveTo(POS_PINCES_FERMEES, INDEX_MOTEUR_PINCE_GAUCHE);
#else
    qDebug() << "On ferme les pinces";
#endif
}

void Pinces::saisirPied()
{
#ifdef ROBOTHW
    ServosNumeriques::moveTo(POS_PINCES_SAISIR, INDEX_MOTEUR_PINCE_DROITE);
    ServosNumeriques::moveTo(POS_PINCES_SAISIR, INDEX_MOTEUR_PINCE_GAUCHE);
#else
    qDebug() << "On ferme les pinces";
#endif
}

bool Pinces::estDispo()
{
    return dispo;
}

void Pinces::setDispo(bool dispo)
{
    this->dispo = dispo;
}

