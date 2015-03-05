#include "canonFilet.h"

#define RESSORT_DEBLOQUE 0

CanonFilet* CanonFilet::singleton = 0;

CanonFilet* CanonFilet::getSingleton()
{
    if (singleton==0)
        singleton = new CanonFilet();

    return singleton;
}

CanonFilet::CanonFilet()
{
#ifdef ROBOTHW
    POSITION_ATTENTE = 0x0370;//0x0384;//@TODO 700 ou 900
    POSITION_TIR = 0x02B0;//0x02BC;//0x0384;//@TODO 700 ou 900
//    POSITION_FEU_HAUT_TORCHE = 0x0215;
//    POSITION_FEU_MILIEU_TORCHE = 0x0230;
//    POSITION_FEU_BAS_TORCHE = 0x025a;
//    POSITION_FEU_TABLE = 0x0280;
//    POSITION_RETOURNEE = 0x00d0;

    //VENTOUSE_VERS_BAS = 0x0110;
    //VENTOUSE_VERS_HAUT = 0x0310;

    MOTEUR = 11;//TOTO trouver l'ID, 18 ou 20  priori
    //MOTEUR_HAUT = 12;
#ifdef ROBOTHW
    ServosNumeriques::setTorqueLimite(0x03ff, MOTEUR);
#endif
    //Maintenant c'est des AX-12
//    Timer* timer3 = new Timer(TIM3, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
//    TIM_CtrlPWMOutputs(TIM3, ENABLE);

//    ressort = new Servo(timer3,4,0.01f, 0.11f);

#endif
}

//CanonFilet::~CanonFilet()
//{
//    ressort->shutDownServo();
//    delete ressort;
//    delete canonFilet;
//}

void CanonFilet::attente()
{
#ifdef ROBOTHW
    ServosNumeriques::moveTo(POSITION_ATTENTE, MOTEUR);
//ressort->goToAngle(POSITION_ATTENTE);
#else
    qDebug() << "repositionnement filet";
#endif
}

void CanonFilet::shoot()
{
#ifdef ROBOTHW
    ServosNumeriques::moveTo(POSITION_TIR, MOTEUR);
#else
    qDebug() << "FILET !!!";
    //ressort->goToAngle(POSITION_TIR);
#endif
}



