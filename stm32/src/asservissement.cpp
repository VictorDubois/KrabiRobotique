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
//#include <stdlib.h>

#define STK_CTRL_ADDR 0xe000e010
#define STK_LOAD_ADDR (STK_CTRL_ADDR+0x04)

#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))

#define DBG_SIZE 300

//int roueGauche[DBG_SIZE];
//int roueDroite[DBG_SIZE];
//float vitesseLin[DBG_SIZE];
//float vitesseLinE[DBG_SIZE];
/*float linearDuty[DBG_SIZE];*/
float vitesseAng[DBG_SIZE];
float vitesseAngE[DBG_SIZE];
//float angularDuty[DBG_SIZE];
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
Asservissement::Asservissement(Odometrie* _odometrie, Command* command) :
    seuil_collision(3.5),
    buffer_collision(0xffffffff),
    nb_echantillons_buffer_collision(10)
{
	odometrie = _odometrie;
	this->command = command;
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
    //PositionPlusAngle before(odometrie.positionPlusAngle);
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


        if (buffer_collision << (16 - nb_echantillons_buffer_collision)) {
            // Pas collision !!!
//#ifdef CAPTEURS
//            bool is_there_someone_in_front = capteurs.getValue(Capteurs::AvantGauche) || capteurs.getValue(Capteurs::AvantDroite) || capteurs.getValue(Capteurs::Avant);
//#else
//            bool is_there_someone_in_front = false;
//#endif
            //is_there_someone_in_front = false;

            //On s’arrête si l’on a atteint la cible ou s’il y a le robot adverse devant
            //if((distance_restante > Distance(20) && !is_there_someone_in_front && !direction) || (direction && fabs(angle_restant.getValueInRadian()) > 0.1))
            //{
                //if( (min(fabs(angle_restant.getValueInRadian()), fabs((angle_restant-Angle(M_PI)).getValueInRadian()))< M_PI_4) && !direction)
                {
#ifdef ROUES
                    float linear_duty_component = pid_filter_distance.getFilteredValue(vitesse_lineaire_a_atteindre-/*blah*/vitesse_lineaire_atteinte);
                    linearDutySent += linear_duty_component;
#endif
                }
                //else
                //    linearDutySent=0;

#ifdef ROUES
                float angular_duty_component = pid_filter_angle.getFilteredValue(vitesse_angulaire_a_atteindre-/*didou*/vitesse_angulaire_atteinte);

                angularDutySent += angular_duty_component;

                    if(dbgInc<DBG_SIZE)
                    {

        //roueGauche[caca] = odometrie.roueCodeuseGauche->getTickValue();
        //roueDroite[caca] = odometrie.roueCodeuseDroite->getTickValue();
                        //vitesseLin[caca] = vitesse_lineaire_atteinte;
                        //vitesseLinE[caca] = vitesse_lineaire_a_atteindre;
                        /*linearDuty[caca] = linearDutySent;*/
                        vitesseAng[dbgInc] = vitesse_angulaire_atteinte.getValueInRadian();
                        vitesseAngE[dbgInc] = vitesse_angulaire_a_atteindre.getValueInRadian();
                        //angularDuty[caca] = angularDutySent;
                        //posx[caca] = positionPlusAngleActuelle.position.x;
                        //posy[caca] = positionPlusAngleActuelle.position.y;
                        //angle[caca] = positionPlusAngleActuelle.angle.getValueInRadian(); //*angle_restant.getValueInRadian();*/distance_restante; //positionPlusAngleActuelle.angle.getValueInRadian()*180/M_PI;
                        dbgInc++;
                    }
                toto++;

                linearDutySent = 0; //min(max(linearDutySent, -0.40),0.40);
                angularDutySent = min(max(angularDutySent, -0.50),0.50);

                roues.gauche.tourne(min(max(linearDutySent-angularDutySent, -0.9),0.9));
                roues.droite.tourne(min(max(linearDutySent+angularDutySent, -0.9),0.9));
#endif
            /*}
            else
            {
                if(stop || is_there_someone_in_front)
                {
#ifdef ROUES
                    roues.gauche.tourne(0);
                    roues.droite.tourne(0);
#endif
                    vitesse_lineaire_a_atteindre = Distance(0);
                    vitesse_angulaire_a_atteindre = Angle(0);
                    linearDutySent = 0;
                    angularDutySent = 0;
                }

                if(en_mouvement && !is_there_someone_in_front)
                {
                    en_mouvement = false;
                    strategie->done();
                }
            }*/

        }
        else // collision
        {
#ifdef ROUES
            roues.gauche.tourne(0);
            roues.droite.tourne(0);
#endif
            //vitesse_lineaire_a_atteindre = Distance(0);
            //vitesse_angulaire_a_atteindre = Angle(0);
            linearDutySent = 0;
            angularDutySent = 0;

            //if(en_mouvement)
            //{
            //    en_mouvement = false;
            //    strategie->collisionDetected();
            //}
        }
}

//void Asservissement::recule(Distance distance) {
    //goTo((odometrie->getPos() - distance).position);
//}

//Distance Asservissement::getVitesseLineaireAfterTrapeziumFilter(Distance vitesse_lineaire_atteinte, Distance distance_restante, Angle angle_restant)
//{
//
//    // Le pivot est la distance que l'on parcourerait si on commencait à décélérer dès maintenant jusqu'une vitesse nulle
//    Distance pivot(vitesse_lineaire_a_atteindre*vitesse_lineaire_a_atteindre/(2*acceleration_lineaire));
//    if( (distance_restante-pivot)<=0 &&
//         ((fabs((angle_restant - Angle(0)).getValueInRadian())>M_PI_2 && vitesse_lineaire_atteinte<=0)
//          || (fabs((angle_restant - Angle(0)).getValueInRadian())<=M_PI_2 && vitesse_lineaire_atteinte>=0))
//         && stop)
//    {
//        //On est proche de la cible et l’on doit décélerer
//        if(vitesse_lineaire_a_atteindre>0.)
//        {
//            return vitesse_lineaire_a_atteindre-Distance(min(vitesse_lineaire_a_atteindre, acceleration_lineaire));
//        }
//        else
//        {
//            return vitesse_lineaire_a_atteindre-Distance(max(vitesse_lineaire_a_atteindre, -acceleration_lineaire));
//        }
//
//    }
//    else if(fabs((angle_restant - Angle(0)).getValueInRadian())>M_PI_2)
//    {
//        // Sinon, on est en phase d'accélération
//        // Si la destination est derrière nous
//        // Alors on ajoute à la vitesse une accélération négative (jusqu'à la valeur (-vitesse_lineaire_max))
//        // Autrement dit, si on avance dans la mauvaise direction on ralenti et si on recule dans la bonne direction alors on recule plus vite
//        return vitesse_lineaire_a_atteindre
//               + Distance(max(-acceleration_lineaire, (-vitesse_lineaire_max-vitesse_lineaire_a_atteindre)));
//    }
//    else
//    {
//        // Sinon, la destination est devant nous
//        // Alors on ajoute à la vitesse une accélération positive (jusqu'à la valeur (vitesse_lineaire_max))
//        // Autrement dit, si on recule dans la mauvaise direction on ralenti et si on avance dans la bonne direction alors on avance plus vite
//        return vitesse_lineaire_a_atteindre
//               + Distance(min(acceleration_lineaire, (vitesse_lineaire_max-vitesse_lineaire_a_atteindre)));
//    }
//}
//
//Angle Asservissement::getVitesseAngulaireAfterTrapeziumFilter(Angle vitesse_angulaire_atteinte, Angle angle_restant)
//{
//    if(fabs((angle_restant - Angle(0)).getValueInRadian())>M_PI_2)
//    {
//        angle_restant = angle_restant-Angle(M_PI);
//    }
//    Angle didou(angle_restant);
//    Angle pivot(vitesse_angulaire_a_atteindre.getValueInRadian()*vitesse_angulaire_a_atteindre.getValueInRadian()/(2*acceleration_angulaire.getValueInRadian()));
//
//    if((Angle(fabs(angle_restant.getValueInRadian()))-pivot).getValueInRadian()<=0)
//    {
//        return vitesse_angulaire_a_atteindre-Angle(copysign(min(fabs(vitesse_angulaire_a_atteindre.getValueInRadian()), acceleration_angulaire.getValueInRadian()), vitesse_angulaire_a_atteindre.getValueInRadian()));
//    }
//    else
//    {
//        return vitesse_angulaire_a_atteindre + Angle(copysign(min(acceleration_angulaire.getValueInRadian(), vitesse_angulaire_max.getValueInRadian()-fabs(vitesse_angulaire_a_atteindre.getValueInRadian())), angle_restant.getValueInRadian()));
//    }
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
