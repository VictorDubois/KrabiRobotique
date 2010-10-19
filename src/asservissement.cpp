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
#include <stdlib.h>

#define STK_CTRL_ADDR 0xe000e010
#define STK_LOAD_ADDR (STK_CTRL_ADDR+0x04)

#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))

#define DBG_SIZE 300

//int roueGauche[DBG_SIZE];
//int roueDroite[DBG_SIZE];
/*float vitesseLin[DBG_SIZE];
float vitesseLinE[DBG_SIZE];
float linearDuty[DBG_SIZE];*/
//float vitesseAng[DBG_SIZE];
//float vitesseAngE[DBG_SIZE];
//float angularDuty[DBG_SIZE];
float posx[DBG_SIZE];
float posy[DBG_SIZE];
float angle[DBG_SIZE];


Asservissement * Asservissement::asservissement = NULL;
const uint16_t Asservissement::nb_ms_between_updates = 10;

Asservissement::Asservissement(Odometrie* _odometrie) :
    vitesse_lineaire_a_atteindre(0),
    vitesse_angulaire_a_atteindre(0),
    #ifdef DONTUSE
    vitesse_lineaire_max(2.55254403), // en mm par nb_ms_between_updates
    vitesse_angulaire_max(M_PI/200.0), // en radian par nb_ms_between_updates
    acceleration_lineaire(2.55254403/200.0), // en mm par nb_ms_between_updates
    acceleration_angulaire((M_PI/200.0)/200.0), // en radian par nb_ms_between_updates
    #else
    vitesse_lineaire_max(4.), // en mm par nb_ms_between_updates
    vitesse_angulaire_max(M_PI/100.0), // en radian par nb_ms_between_updates
    acceleration_lineaire(4./200.0), // en mm par nb_ms_between_updates
    acceleration_angulaire((M_PI/100.0)/200.0), // en radian par nb_ms_between_updates
    #endif
    seuil_collision(3.5),
    buffer_collision(0xffffffff),
    nb_echantillons_buffer_collision(10),
    destination(_odometrie->getPos().position)
{
	odometrie = _odometrie;
    caca=0; toto = 0;
    linearDutySent = 0;
    angularDutySent = 0;
    en_mouvement = false;
    Asservissement::asservissement = this;
}

int asserCount = 0;

#include <iostream>

float min(float a, float b)
{
	return a < b ? a : b;
}

float max(float a, float b)
{
	return a > b ? a : b;
}

void Asservissement::update(void)
{
    //PositionPlusAngle before(odometrie.positionPlusAngle);
    asserCount++;

    if(asserCount < 87000)
    {

#ifdef CAPTEURS
        capteurs.startConversion();
#endif 
        odometrie->update();

        PositionPlusAngle positionPlusAngleActuelle = odometrie->getPos();
        Angle vitesse_angulaire_atteinte = odometrie->vitesseAngulaire();
        Distance vitesse_lineaire_atteinte = odometrie->vitesseLineaire();

        buffer_collision <<= 1;
        bool tmp = (fabs((vitesse_lineaire_atteinte - vitesse_lineaire_a_atteindre).getValueInMillimeters()) < seuil_collision);
        buffer_collision |= tmp;


        if (buffer_collision << (16 - nb_echantillons_buffer_collision)) {
            // Pas collision !!!
            Position vecteur_pos_actuelle_pos_arrivee = destination-positionPlusAngleActuelle.position;

            Distance distance_restante = (vecteur_pos_actuelle_pos_arrivee).getNorme();
            Angle angle_restant = (direction ? destAngle : vecteur_pos_actuelle_pos_arrivee.getAngle()) - positionPlusAngleActuelle.angle;
#ifdef CAPTEURS
            bool is_there_someone_in_front = capteurs.getValue(Capteurs::AvantGauche) || capteurs.getValue(Capteurs::AvantDroite) || capteurs.getValue(Capteurs::Avant);
#else
            bool is_there_someone_in_front = false;
#endif
            //is_there_someone_in_front = false;

            //On s’arrête si l’on a atteint la cible ou s’il y a le robot adverse devant
            if((distance_restante > Distance(20) && !is_there_someone_in_front && !direction) || (direction && fabs(angle_restant.getValueInRadian()) > 0.1))
            {
                if( (min(fabs(angle_restant.getValueInRadian()), fabs((angle_restant-Angle(M_PI)).getValueInRadian()))< M_PI_4) && !direction)
                {
                    vitesse_lineaire_a_atteindre = getVitesseLineaireAfterTrapeziumFilter(vitesse_lineaire_atteinte, distance_restante, angle_restant);
#ifdef ROUES
                    float linear_duty_component = pid_filter_distance.getFilteredValue(vitesse_lineaire_a_atteindre-/*blah*/vitesse_lineaire_atteinte);
                    linearDutySent += linear_duty_component;
#endif
                }
                else
                    linearDutySent=0;

                vitesse_angulaire_a_atteindre = getVitesseAngulaireAfterTrapeziumFilter(vitesse_angulaire_atteinte, angle_restant);
#ifdef ROUES
                float angular_duty_component = pid_filter_angle.getFilteredValue(vitesse_angulaire_a_atteindre-/*didou*/vitesse_angulaire_atteinte);

                angularDutySent += angular_duty_component;

                if(toto == 10)
                {
                    if(caca<DBG_SIZE)
                    {

        //roueGauche[caca] = odometrie.roueCodeuseGauche->getTickValue();
        //roueDroite[caca] = odometrie.roueCodeuseDroite->getTickValue();
                        /*vitesseLin[caca] = vitesse_lineaire_atteinte.getValueInMillimeters();
                        vitesseLinE[caca] = vitesse_lineaire_a_atteindre.getValueInMillimeters();
                        linearDuty[caca] = linearDutySent;*/
                        /*vitesseAng[caca] = vitesse_angulaire_atteinte.getValueInRadian();
                        vitesseAngE[caca] = vitesse_angulaire_a_atteindre.getValueInRadian();
                        angularDuty[caca] = angularDutySent;*/
                        posx[caca] = positionPlusAngleActuelle.position.x.getValueInMillimeters();
                        posy[caca] = positionPlusAngleActuelle.position.y.getValueInMillimeters();
                        angle[caca] = positionPlusAngleActuelle.angle.getValueInRadian(); //*angle_restant.getValueInRadian();*/distance_restante.getValueInMillimeters(); //positionPlusAngleActuelle.angle.getValueInRadian()*180/M_PI;
                        caca++;
                    }
                    toto = 0;
                }
                toto++;

                linearDutySent = min(max(linearDutySent, -0.40),0.40);
                angularDutySent = min(max(angularDutySent, -0.50),0.50);

                roues.gauche.tourne(min(max(linearDutySent-angularDutySent, -0.9),0.9));
                roues.droite.tourne(min(max(linearDutySent+angularDutySent, -0.9),0.9));
#endif
            }
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
            }

        }
        else // collision
        {
#ifdef ROUES
            roues.gauche.tourne(0);
            roues.droite.tourne(0);
#endif
            vitesse_lineaire_a_atteindre = Distance(0);
            vitesse_angulaire_a_atteindre = Angle(0);
            linearDutySent = 0;
            angularDutySent = 0;

            if(en_mouvement)
            {
                en_mouvement = false;
                strategie->collisionDetected();
            }
        }
    }
    else
    {
#ifdef ROUES
        roues.gauche.tourne(0);
        roues.droite.tourne(0);
#endif
        strategie->theEnd();
    }
}

void Asservissement::recule(Distance distance) {
    goTo((odometrie->getPos() - distance).position);
}

Distance Asservissement::getVitesseLineaireAfterTrapeziumFilter(Distance vitesse_lineaire_atteinte, Distance distance_restante, Angle angle_restant)
{

    // Le pivot est la distance que l'on parcourerait si on commencait à décélérer dès maintenant jusqu'une vitesse nulle
    Distance pivot(vitesse_lineaire_a_atteindre.getValueInMillimeters()*vitesse_lineaire_a_atteindre.getValueInMillimeters()/(2*acceleration_lineaire.getValueInMillimeters()));
    if( (distance_restante-pivot).getValueInMillimeters()<=0 &&
         ((fabs((angle_restant - Angle(0)).getValueInRadian())>M_PI_2 && vitesse_lineaire_atteinte.getValueInMillimeters()<=0)
          || (fabs((angle_restant - Angle(0)).getValueInRadian())<=M_PI_2 && vitesse_lineaire_atteinte.getValueInMillimeters()>=0))
         && stop)
    {
        //On est proche de la cible et l’on doit décélerer
        if(vitesse_lineaire_a_atteindre.getValueInMillimeters()>0)
        {
            return vitesse_lineaire_a_atteindre-Distance(min(vitesse_lineaire_a_atteindre.getValueInMillimeters(), acceleration_lineaire.getValueInMillimeters()));
        }
        else
        {
            return vitesse_lineaire_a_atteindre-Distance(max(vitesse_lineaire_a_atteindre.getValueInMillimeters(), -acceleration_lineaire.getValueInMillimeters()));
        }

    }
    else if(fabs((angle_restant - Angle(0)).getValueInRadian())>M_PI_2)
    {
        // Sinon, on est en phase d'accélération
        // Si la destination est derrière nous
        // Alors on ajoute à la vitesse une accélération négative (jusqu'à la valeur (-vitesse_lineaire_max))
        // Autrement dit, si on avance dans la mauvaise direction on ralenti et si on recule dans la bonne direction alors on recule plus vite
        return vitesse_lineaire_a_atteindre
               + Distance(max(-acceleration_lineaire.getValueInMillimeters(), (-vitesse_lineaire_max.getValueInMillimeters()-vitesse_lineaire_a_atteindre.getValueInMillimeters())));
    }
    else
    {
        // Sinon, la destination est devant nous
        // Alors on ajoute à la vitesse une accélération positive (jusqu'à la valeur (vitesse_lineaire_max))
        // Autrement dit, si on recule dans la mauvaise direction on ralenti et si on avance dans la bonne direction alors on avance plus vite
        return vitesse_lineaire_a_atteindre
               + Distance(min(acceleration_lineaire.getValueInMillimeters(), (vitesse_lineaire_max.getValueInMillimeters()-vitesse_lineaire_a_atteindre.getValueInMillimeters())));
    }
}

Angle Asservissement::getVitesseAngulaireAfterTrapeziumFilter(Angle vitesse_angulaire_atteinte, Angle angle_restant)
{
    if(fabs((angle_restant - Angle(0)).getValueInRadian())>M_PI_2)
    {
        angle_restant = angle_restant-Angle(M_PI);
    }
    Angle didou(angle_restant);
    Angle pivot(vitesse_angulaire_a_atteindre.getValueInRadian()*vitesse_angulaire_a_atteindre.getValueInRadian()/(2*acceleration_angulaire.getValueInRadian()));

    if((Angle(fabs(angle_restant.getValueInRadian()))-pivot).getValueInRadian()<=0)
    {
        return vitesse_angulaire_a_atteindre-Angle(copysign(min(fabs(vitesse_angulaire_a_atteindre.getValueInRadian()), acceleration_angulaire.getValueInRadian()), vitesse_angulaire_a_atteindre.getValueInRadian()));
    }
    else
    {
        return vitesse_angulaire_a_atteindre + Angle(copysign(min(acceleration_angulaire.getValueInRadian(), vitesse_angulaire_max.getValueInRadian()-fabs(vitesse_angulaire_a_atteindre.getValueInRadian())), angle_restant.getValueInRadian()));
    }
}

void Asservissement::goTo(Position position, bool stop)
{
    destination = position;
    direction = false;
    en_mouvement = true;
    this->stop = stop;
}

void Asservissement::goToDirection(Angle angle)
{
    destination = odometrie->getPos().position;
    destAngle = angle;
    direction = true;
    en_mouvement = true;
    this->stop = true;
}

void Asservissement::tourne(Angle angle){
    goToDirection(odometrie->getPos().angle+angle);
}

