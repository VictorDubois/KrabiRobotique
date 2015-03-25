#include "brasLaterauxKrabi.h"
#define RC180DEGRES_BRAS 90
#define BRAS_GAUCHE_DEPLOYE 90
#define BRAS_GAUCHE_REPLIE 90
#define BRAS_DROIT_DEPLOYE 90
#define BRAS_DROIT_REPLIE 90

BrasLaterauxKrabi* BrasLaterauxKrabi::brasLaterauxKrabi = 0;
//BrasLaterauxKrabi* BrasLaterauxKrabi::brasDroit = new Servo(TIM1,1,0,RC180DEGRES_BRAS);
//BrasLaterauxKrabi* BrasLaterauxKrabi::brasGauche = new Servo(TIM1,2,0,RC180DEGRES_BRAS);

BrasLaterauxKrabi::BrasLaterauxKrabi():
brasGaucheDeploye(false), brasDroitDeploye(false)
{
BrasLaterauxKrabi::brasLaterauxKrabi=this;
}

BrasLaterauxKrabi::~BrasLaterauxKrabi()
{
    brasGauche->shutDownServo();
    brasDroit->shutDownServo();
    delete brasGauche;
    delete brasDroit;
    delete brasLaterauxKrabi;
}

void BrasLaterauxKrabi::deployerBrasGauche()
{
    brasGauche->goToAngle(BRAS_GAUCHE_DEPLOYE);
    brasGaucheDeploye=true;
}

void BrasLaterauxKrabi::replierBrasGauche()
{
    brasGauche->goToAngle(BRAS_GAUCHE_REPLIE);
    brasGaucheDeploye=false;
}

void BrasLaterauxKrabi::deployerBrasDroit()
{
    brasDroit->goToAngle(BRAS_DROIT_DEPLOYE);
    brasDroitDeploye=true;
}

void BrasLaterauxKrabi::replierBrasDroit()
{
    brasDroit->goToAngle(BRAS_DROIT_REPLIE);
    brasDroitDeploye=false;
}

BrasLaterauxKrabi* BrasLaterauxKrabi::getBrasLaterauxKrabi()
{
    return BrasLaterauxKrabi::brasLaterauxKrabi;
}
