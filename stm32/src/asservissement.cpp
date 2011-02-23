#ifdef ROBOTHW
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "misc.h"
#endif

#include "asservissement.h"
#include "strategie.h"
#include <math.h>

#define STK_CTRL_ADDR 0xe000e010
#define STK_LOAD_ADDR (STK_CTRL_ADDR+0x04)

#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))

#define DBG_SIZE 600

//int roueGauche[DBG_SIZE];
//int roueDroite[DBG_SIZE];
/*
float vitesseLin[DBG_SIZE];
float vitesseLinE[DBG_SIZE];
float linearDuty[DBG_SIZE];
*/


float vitesseAng[DBG_SIZE];
float vitesseAngE[DBG_SIZE];
float angularDuty[DBG_SIZE];


/*float posx[DBG_SIZE];
float posy[DBG_SIZE];
float angle[DBG_SIZE];
*/
#ifndef NULL
#define NULL 0
#endif

Asservissement * Asservissement::asservissement = NULL;
const uint16_t Asservissement::nb_ms_between_updates = 10;
uint32_t dbgInc = 0;
Asservissement::Asservissement(Odometrie* _odometrie) :
    seuil_collision(3.5),
    buffer_collision(0xffffffff),
    nb_echantillons_buffer_collision(10)
{
	odometrie = _odometrie;
	command = NULL;
    toto = 0;
    linearDutySent = 0;
    angularDutySent = 0;
    Asservissement::asservissement = this;

#ifdef ROBOTHW
    *((uint32_t *)(STK_CTRL_ADDR)) = 0x03; // CLKSOURCE:0 ; TICKINT: 1 ; ENABLE:1
    *((uint32_t *)(STK_LOAD_ADDR)) = 9000*nb_ms_between_updates; // valeur en ms*9000 (doit etre inférieur à 0x00FFFFFF=16 777 215)

    NVIC_InitTypeDef SysTick_IRQ;

    SysTick_IRQ.NVIC_IRQChannel = SysTick_IRQn;
    SysTick_IRQ.NVIC_IRQChannelCmd = ENABLE;
    SysTick_IRQ.NVIC_IRQChannelPreemptionPriority = 0;
    SysTick_IRQ.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&SysTick_IRQ);
#endif
}

int asserCount = 0;

void Asservissement::update(void)
{
    asserCount++;

    if(asserCount > 87000)
    {
#ifdef ROUES
        roues.gauche.tourne(0);
        roues.droite.tourne(0);
#endif
        strategie->theEnd();
    }

#ifdef CAPTEURS
        capteurs.startConversion();
#endif
        odometrie->update();

        PositionPlusAngle positionPlusAngleActuelle = odometrie->getPos();
        Angle vitesse_angulaire_atteinte = odometrie->getVitesseAngulaire();
        Distance vitesse_lineaire_atteinte = odometrie->getVitesseLineaire();

	command->update(positionPlusAngleActuelle, vitesse_angulaire_atteinte, vitesse_lineaire_atteinte);

        buffer_collision <<= 1;
        bool tmp = (fabs((vitesse_lineaire_atteinte - command->getLinearSpeed())) < seuil_collision);
        buffer_collision |= tmp;


        float vitesse_lineaire_a_atteindre = command->getLinearSpeed();
        float vitesse_angulaire_a_atteindre = command->getAngularSpeed();
#ifdef ROUES
        float linear_duty_component = pid_filter_distance.getFilteredValue(vitesse_lineaire_a_atteindre-vitesse_lineaire_atteinte);
        linearDutySent += linear_duty_component;

        float angular_duty_component = pid_filter_angle.getFilteredValue(vitesse_angulaire_a_atteindre-vitesse_angulaire_atteinte);

        angularDutySent += angular_duty_component;

        linearDutySent = min(max(linearDutySent, -0.40),0.40);
        angularDutySent = min(max(angularDutySent, -0.50),0.50);

            if(toto < 1 && dbgInc<DBG_SIZE)
            {

        //roueGauche[caca] = odometrie.roueCodeuseGauche->getTickValue();
        //roueDroite[caca] = odometrie.roueCodeuseDroite->getTickValue();
                   /*vitesseLin[dbgInc] = vitesse_lineaire_atteinte;
                   vitesseLinE[dbgInc] = vitesse_lineaire_a_atteindre;
                   linearDuty[dbgInc] = linearDutySent;*/

                   vitesseAng[dbgInc] = vitesse_angulaire_atteinte;
                   vitesseAngE[dbgInc] = vitesse_angulaire_a_atteindre;
                   angularDuty[dbgInc] = angularDutySent;

                   //posx[caca] = positionPlusAngleActuelle.position.x;
                   //posy[caca] = positionPlusAngleActuelle.position.y;
                   //angle[caca] = positionPlusAngleActuelle.angle.getValueInRadian(); //*angle_restant.getValueInRadian();*/distance_restante; //positionPlusAngleActuelle.angle.getValueInRadian()*180/M_PI;
                   dbgInc++;
               }
           toto = (toto+1) % 1;



           roues.gauche.tourne(min(max(-linearDutySent+angularDutySent, -0.9),0.9));
           roues.droite.tourne(min(max(-linearDutySent-angularDutySent, -0.9),0.9));
#endif
}

//Some olds function which may or not have been replaced by function of the TrapezoidalCommand
//void Asservissement::recule(Distance distance) {
    //goTo((odometrie->getPos() - distance).position);
//}

//void Asservissement::goTo(Position position, bool stop)
//{
//    destination = position;
//    direction = false;
//    en_mouvement = true;
//    this->stop = stop;
//}
//
//void Asservissement::goToDirection(Angle angle)
//{
//    destination = odometrie->getPos().position;
//    destAngle = angle;
//    direction = true;
//    en_mouvement = true;
//    this->stop = true;
//}
//
//void Asservissement::tourne(Angle angle){
//    goToDirection(odometrie->getPos().angle+angle);
//}

extern "C" void SysTick_Handler()
{
    Asservissement::asservissement->update();
}
