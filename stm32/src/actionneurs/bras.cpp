#include "bras.h"

Bras* Bras::bras = NULL;

#ifdef ROBOTHW

Bras::Bras()
{
    Bras::bras = this;
/*
    balaiGauche = new Servo(1);
    balaiGauche->goToAngle(BALAI_G_CLOSED);

    balaiDroite = new Servo(2);
    balaiDroite->goToAngle(BALAI_D_CLOSED);

    rateau = new Servo(4);
    rateau->goToAngle(RATEAU_HAUT);*/
}

Bras::~Bras()
{
    delete balaiDroite;
    delete balaiGauche;
    delete rateau;
}

void Bras::ouvrirBalaiDroit()
{
    balaiDroite->goToAngle(BALAI_D_OPEN);
}

void Bras::ouvrirBalaiGauche()
{
    balaiGauche->goToAngle(BALAI_G_OPEN);
}

void Bras::fermerBalaiDroit()
{
    balaiDroite->goToAngle(BALAI_D_CLOSED);
}

void Bras::fermerBalaiGauche()
{
    balaiGauche->goToAngle(BALAI_G_CLOSED);
}

void Bras::fermerBalais()
{
    balaiDroite->goToAngle(BALAI_D_CLOSED);
    balaiGauche->goToAngle(BALAI_G_CLOSED);
}

void Bras::ouvrirBalais()
{
    balaiDroite->goToAngle(BALAI_D_OPEN);
    balaiGauche->goToAngle(BALAI_G_OPEN);
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

void Bras::arretUrgence()
{
    rateau->shutDownServo();
    balaiDroite->shutDownServo();
    balaiGauche->shutDownServo();
}

#else

Bras::Bras(){Bras::bras = this;}

Bras::~Bras(){}

void Bras::ouvrirBalaiDroit(){}

void Bras::ouvrirBalaiGauche(){}

void Bras::fermerBalaiDroit(){}

void Bras::fermerBalaiGauche(){}

void Bras::fermerBalais(){}

void Bras::ouvrirBalais(){}

void Bras::monterRateau(){}

void Bras::descendreRateau(){}

void Bras::dropRateau(){}

void Bras::arretUrgence(){}

#endif // ROBOTHW

Bras* Bras::getBras()
{
    return Bras::bras;
}

