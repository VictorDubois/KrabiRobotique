#include "Bras.h"

#ifdef ROBOTHW

Bras* Bras::bras = NULL;

Bras::Bras()
{
    Bras::bras = this;

    balaiGauche = new Servo(1);
    balaiGauche->goToAngle(BALAI_G_CLOSED);

    balaiDroite = new Servo(2);
    balaiDroite->goToAngle(BALAI_D_CLOSED);

    rateau = new Servo(4);
    rateau->goToAngle(RATEAU_HAUT);
}

void Bras::ouvrirBalaiDroit()
{
    balaiGauche->goToAngle(BALAI_G_OPEN);
    balaiDroite->goToAngle(BALAI_D_CLOSED);
}

void Bras::ouvrirBalaiGauche()
{
    balaiGauche->goToAngle(BALAI_G_CLOSED);
    balaiDroite->goToAngle(BALAI_D_OPEN);
}

void Bras::fermerBalaiDroit()
{
    balaiDroite->goToAngle(BALAI_D_CLOSED);
}

void Bras::fermerBalaiGauche()
{
    balaiDroite->goToAngle(BALAI_G_CLOSED);
}

void Bras::fermerBalais()
{
    balaiDroite->goToAngle(BALAI_D_CLOSED);
    balaiDroite->goToAngle(BALAI_G_CLOSED);
}

void Bras::ouvrirBalais()
{
    balaiDroite->goToAngle(BALAI_D_OPEN);
    balaiDroite->goToAngle(BALAI_G_OPEN);
}

void Bras::descendreRateau()
{
    rateau->goToAngle(RATEAU_BAS);
}

void Bras::dropRateau()
{
    rateau->shutDownServo();
}

void Bras::monterRateau()
{
    rateau->goToAngle(RATEAU_HAUT);
}

Bras::~Bras()
{
    delete balaiDroite;
    delete balaiGauche;
    delete rateau;
}

#endif // ROBOTHW
