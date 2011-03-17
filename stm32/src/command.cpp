#include "command.h"
#include "asservissement.h"
#include "strategie.h"
#include <math.h>

#ifndef ROBOTHW
#include <iostream>
#endif

float Command::vitesse_lineaire_max = 3; // en mm par nb_ms_between_updates (peut monter à 6)
float Command::vitesse_angulaire_max = 0.03; // en radian par nb_ms_between_updates
float Command::acceleration_lineaire = 0.05; // en mm par nb_ms_between_updates
float Command::acceleration_angulaire = (2*M_PI/30000.0); // en radian par nb_ms_between_updates

template<class T> T min(T a, T b)
{
	return a < b ? a : b;
}

template<class T> T max(T a, T b)
{
	return a > b ? a : b;
}

Command::Command()
{
	Command* & c = Asservissement::asservissement->command;
       //if(c)
	   //    delete c;
       c = this;
}

Command::~Command()
{

}

TrapezoidalCommand::~TrapezoidalCommand()
{

}

TrapezoidalCommand::TrapezoidalCommand() :
    vitesse_lineaire_a_atteindre(0),
    vitesse_angulaire_a_atteindre(0)
{
}

void TrapezoidalCommand::update(PositionPlusAngle positionPlusAngleActuelle, Angle vitesse_angulaire_atteinte, float vitesse_lineaire_atteinte)
{
	Position vecteur_pos_actuelle_pos_arrivee = destination-positionPlusAngleActuelle.position;

	Distance distance_restante = (vecteur_pos_actuelle_pos_arrivee).getNorme();
	Angle angle_restant = vecteur_pos_actuelle_pos_arrivee.getAngle() - positionPlusAngleActuelle.angle;

	if(distance_restante < 5)
		Strategie::strategie->done();

	if(distance_restante < 5)
		vitesse_lineaire_a_atteindre = 0;
	else
        	vitesse_lineaire_a_atteindre = getVitesseLineaireAfterTrapeziumFilter(vitesse_lineaire_atteinte, distance_restante, angle_restant);

	if(distance_restante < 5 || fabs(wrapAngle(angle_restant)) < 0.07)
		vitesse_angulaire_a_atteindre = 0;
	else
		vitesse_angulaire_a_atteindre = getVitesseAngulaireAfterTrapeziumFilter(vitesse_angulaire_a_atteindre, angle_restant);
}



Distance TrapezoidalCommand::getVitesseLineaireAfterTrapeziumFilter(Distance vitesse_lineaire_atteinte, Distance distance_restante, Angle angle_restant)
{

    // Le pivot est la distance que l'on parcourerait si on commencait à décélérer dès maintenant jusqu'une vitesse nulle
    float pivot = vitesse_lineaire_a_atteindre*vitesse_lineaire_a_atteindre/(2*acceleration_lineaire);
    if( (distance_restante-pivot)<=0 &&
         ( (fabs(wrapAngle(angle_restant))>M_PI_2 && vitesse_lineaire_atteinte<=0)
         ||(fabs(wrapAngle(angle_restant))<=M_PI_2 && vitesse_lineaire_atteinte>=0))
         && stop)
    {
        //On est proche de la cible et l’on doit décélerer
        if(vitesse_lineaire_a_atteindre>0.)
        {
            return vitesse_lineaire_a_atteindre-Distance(min(vitesse_lineaire_a_atteindre, acceleration_lineaire));
        }
        else
        {
            return vitesse_lineaire_a_atteindre-Distance(max(vitesse_lineaire_a_atteindre, -acceleration_lineaire));
        }

    }
    else if(fabs(wrapAngle(angle_restant))>M_PI_2)
    {
        // Sinon, on est en phase d'accélération
        // Si la destination est derrière nous
        // Alors on ajoute à la vitesse une accélération négative (jusqu'à la valeur (-vitesse_lineaire_max))
        // Autrement dit, si on avance dans la mauvaise direction on ralenti et si on recule dans la bonne direction alors on recule plus vite
        return vitesse_lineaire_a_atteindre
               + Distance(max(-acceleration_lineaire, (-vitesse_lineaire_max-vitesse_lineaire_a_atteindre)));
    }
    else
    {
        // Sinon, la destination est devant nous
        // Alors on ajoute à la vitesse une accélération positive (jusqu'à la valeur (vitesse_lineaire_max))
        // Autrement dit, si on recule dans la mauvaise direction on ralenti et si on avance dans la bonne direction alors on avance plus vite
        return vitesse_lineaire_a_atteindre
               + Distance(min(acceleration_lineaire, (vitesse_lineaire_max-vitesse_lineaire_a_atteindre)));
    }
}

Angle TrapezoidalCommand::getVitesseAngulaireAfterTrapeziumFilter(Angle vitesse_angulaire_atteinte, Angle angle_restant)
{
    if(fabs(wrapAngle(angle_restant))>M_PI_2 + 0.01)
    {
        angle_restant = wrapAngle(angle_restant+Angle(M_PI));
    }

    Angle pivot(vitesse_angulaire_a_atteindre*vitesse_angulaire_a_atteindre/(2*acceleration_angulaire));

    if((Angle(fabs(angle_restant))-pivot)<=0)
    {
        return vitesse_angulaire_a_atteindre-Angle(copysign(min((float)fabs(vitesse_angulaire_a_atteindre), (float)acceleration_angulaire), vitesse_angulaire_a_atteindre));
    }
    else
    {
        return vitesse_angulaire_a_atteindre + Angle(copysign(min(acceleration_angulaire, vitesse_angulaire_max-(float)fabs(vitesse_angulaire_a_atteindre)), angle_restant));
    }
}

void TrapezoidalCommand::goTo(Position position, bool stop)
{
    destination = position;
    direction = false;
    en_mouvement = true;
    this->stop = stop;
}
