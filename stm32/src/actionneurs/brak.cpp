#include "brak.h"
#ifndef ROBOTHW
#include <QDebug>
#endif

Brak* Brak::singleton = 0;

Brak* Brak::getSingleton()
{
    if (singleton == 0)
    {
        singleton = new Brak;
    }

    return singleton;
}

Brak::Brak()
{
    POSITION_RANGE = 0x0100;
    POSITION_INTERMEDIAIRE = 0x01a0;
    POSITION_FEU_HAUT_TORCHE = 0x0215;
    POSITION_FEU_MILIEU_TORCHE = 0x0230;
    POSITION_FEU_BAS_TORCHE = 0x025a;
    POSITION_FEU_TABLE = 0x0280;
    POSITION_RETOURNEE = 0x00d0;

    VENTOUSE_VERS_BAS = 0x0110;
    VENTOUSE_VERS_HAUT = 0x0310;

    MOTEUR_BAS = 10;
    MOTEUR_HAUT = 12;
#ifdef ROBOTHW
    ServosNumeriques::setTorqueLimite(0x03ff, MOTEUR_HAUT);
    ServosNumeriques::setTorqueLimite(0x03ff, MOTEUR_BAS);
#endif
}

void Brak::positionBasse()
{
#ifdef ROBOTHW
    for(int i = 0; i<10; i++)
        ServosNumeriques::moveTo(POSITION_FEU_TABLE, MOTEUR_HAUT);
#endif
#ifndef ROBOTHW
    qDebug() << "bracquemart position basse";
#endif
}

void Brak::positionIntermediaire()
{
#ifdef ROBOTHW
    for(int i = 0; i<10; i++)
        ServosNumeriques::moveTo(Brak::POSITION_INTERMEDIAIRE, MOTEUR_HAUT);
#endif
#ifndef ROBOTHW
    qDebug() << "bracquemart position intermediaire";
#endif
}

void Brak::positionHaute()
{
#ifdef ROBOTHW
    for(int i = 0; i<10; i++)
        ServosNumeriques::moveTo(POSITION_RANGE, MOTEUR_HAUT);
#endif
#ifndef ROBOTHW
    qDebug() << "bracquemart position haute";
#endif
}

void Brak::positionFeuHautTorche()
{
#ifdef ROBOTHW
    for(int i = 0; i<10; i++)
        ServosNumeriques::moveTo(POSITION_FEU_HAUT_TORCHE, MOTEUR_HAUT);
#endif
#ifndef ROBOTHW
    qDebug() << "bracquemart position feu en haut de torche";
#endif
}

void Brak::positionFeuMilieuTorche()
{
#ifdef ROBOTHW
    for(int i = 0; i<10; i++)
        ServosNumeriques::moveTo(POSITION_FEU_MILIEU_TORCHE, MOTEUR_HAUT);
#endif
#ifndef ROBOTHW
    qDebug() << "bracquemart position feu en milieu de torche";
#endif
}

void Brak::positionFeuBasTorche()
{
#ifdef ROBOTHW
    for(int i = 0; i<10; i++)
        ServosNumeriques::moveTo(POSITION_FEU_BAS_TORCHE, MOTEUR_HAUT);
#endif
#ifndef ROBOTHW
    qDebug() << "bracquemart position feu en bas de torche";
#endif
}

void Brak::positionBasseRetourne()
{
#ifdef ROBOTHW
    for(int i = 0; i<10; i++)
        ServosNumeriques::moveTo(POSITION_RETOURNEE, MOTEUR_HAUT);
#endif
#ifndef ROBOTHW
    qDebug() << "bracquemart en position basse et retourné";
#endif
}

void Brak::attraperFeu()
{
    #ifdef ROBOTHW
       GPIO_WriteBit(GPIOD, GPIO_Pin_14, Bit_SET); //activation de la pompe à vide
    #endif
#ifndef ROBOTHW
    qDebug() << "attrapage de feu";
#endif
}

void Brak::relacherFeu()
{
    #ifdef ROBOTHW
        GPIO_WriteBit(GPIOD, GPIO_Pin_14, Bit_RESET); //désactivation de la pompe à vide
    #endif
#ifndef ROBOTHW
    qDebug() << "relachage de feu";
#endif
}

void Brak::orienterBas()
{
#ifdef ROBOTHW
    for(int i = 0; i<10; i++)
        ServosNumeriques::moveTo(VENTOUSE_VERS_BAS, MOTEUR_BAS);
#endif
#ifndef ROBOTHW
    qDebug() << "bracquemart retourné vers haut";
#endif
}

void Brak::orienterHaut()
{
#ifdef ROBOTHW
    for(int i = 0; i<10; i++)
        ServosNumeriques::moveToAtSpeed(VENTOUSE_VERS_HAUT, 0x03ff, MOTEUR_BAS);
#endif
#ifndef ROBOTHW
    qDebug() << "bracquemart retourné vers bas";
#endif
}
