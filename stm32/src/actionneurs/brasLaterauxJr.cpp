#include "brasLaterauxJr.h"
#define RC180DEGRES_BRAS 90.f
#define BRAS_GAUCHE_DEPLOYE 90
#define BRAS_GAUCHE_REPLIE 90
#define BRAS_DROIT_DEPLOYE 90
#define BRAS_DROIT_REPLIE 90

BrasLateraux* BrasLateraux::brasLateraux = NULL;
Servo(Timer* timer, unsigned char OCx, float RC0degre, float RC180degres);
BrasLateraux* BrasLateraux::brasDroit = new Servo(TIM3,1,0,RC180DEGRES_BRAS);
BrasLateraux* BrasLateraux::brasGauche = new Servo(TIM3,2,0,RC180DEGRES_BRAS);

BrasLateraux::BrasLateraux():
brasGaucheDeploye(false), brasDroitDeploye(false)
{
BrasLateraux::brasLateraux=this;
}

BrasLateraux::~BrasLateraux()
{
    brasGauche->shutDownServo();
    brasDroit->shutDownServo();
    delete brasGauche;
    delete brasDroit;
    delete brasLateraux;
}

BrasLateraux::deployerBrasGauche()
{
    brasGauche->goToAngle(BRAS_GAUCHE_DEPLOYE)
    brasGaucheDeploye=true;
}

BrasLateraux::replierBrasGauche()
{
    brasGauche->goToAngle(BRAS_GAUCHE_REPLIE)
    brasGaucheDeploye=false;
}

BrasLateraux::deployerBrasDroit()
{
    brasDroit>goToAngle(BRAS_DROIT_DEPLOYE)
    brasDroitDeploye=true;
}

BrasLateraux::replierBrasDroit()
{
    brasDroit->goToAngle(BRAS_DROIT_REPLIE)
    brasDroitDeploye=false;
}

BrasLateraux::getBrasLateraux()
{
    return BrasLateraux::brasLateraux;
}
