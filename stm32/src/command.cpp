#include "command.h"
#include <math.h>

template<class T> T min(T a, T b)
{
	return a < b ? a : b;
}

template<class T> T max(T a, T b)
{
	return a > b ? a : b;
}

Command::Command() :
    vitesse_lineaire_a_atteindre(0),
    vitesse_angulaire_a_atteindre(0),
#if 0
    vitesse_lineaire_max(4.), // en mm par nb_ms_between_updates
    vitesse_angulaire_max(M_PI/100.0), // en radian par nb_ms_between_updates
    acceleration_lineaire(4./200.0), // en mm par nb_ms_between_updates
    acceleration_angulaire((M_PI/100.0)/200.0) // en radian par nb_ms_between_updates
#else
    vitesse_lineaire_max(4.), // en mm par nb_ms_between_updates
    vitesse_angulaire_max(M_PI/500.0), // en radian par nb_ms_between_updates
    acceleration_lineaire(4./200.0), // en mm par nb_ms_between_updates
    acceleration_angulaire((M_PI/100.0)/200.0) // en radian par nb_ms_between_updates
#endif
{
}

#include <iostream>

void Command::update(PositionPlusAngle positionPlusAngleActuelle, Angle vitesse_angulaire_atteinte, float vitesse_lineaire_atteinte)
{
	Position vecteur_pos_actuelle_pos_arrivee = destination-positionPlusAngleActuelle.position;
	
	Distance distance_restante = (vecteur_pos_actuelle_pos_arrivee).getNorme();
	Angle angle_restant = vecteur_pos_actuelle_pos_arrivee.getAngle() - positionPlusAngleActuelle.angle;

	if(false) //distance_restante < 5)
		vitesse_lineaire_a_atteindre = 0;
	else
        	vitesse_lineaire_a_atteindre = getVitesseLineaireAfterTrapeziumFilter(vitesse_lineaire_atteinte, distance_restante, angle_restant);

	if(false) //fabs(angle_restant.getValueInRadian()) < 0.01)
		vitesse_angulaire_a_atteindre = 0;
	else
		vitesse_angulaire_a_atteindre = getVitesseAngulaireAfterTrapeziumFilter(vitesse_angulaire_atteinte, angle_restant);
	std::cout << "Ook " << distance_restante << " " << vitesse_lineaire_a_atteindre << std::endl;
}



Distance Command::getVitesseLineaireAfterTrapeziumFilter(Distance vitesse_lineaire_atteinte, Distance distance_restante, Angle angle_restant)
{

    // Le pivot est la distance que l'on parcourerait si on commencait à décélérer dès maintenant jusqu'une vitesse nulle
    Distance pivot(vitesse_lineaire_a_atteindre*vitesse_lineaire_a_atteindre/(2*acceleration_lineaire));
    if( (distance_restante-pivot)<=0 &&
         ((fabs((angle_restant - Angle(0)).getValueInRadian())>M_PI_2 && vitesse_lineaire_atteinte<=0)
          || (fabs((angle_restant - Angle(0)).getValueInRadian())<=M_PI_2 && vitesse_lineaire_atteinte>=0))
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
    else if(fabs((angle_restant - Angle(0)).getValueInRadian())>M_PI_2)
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

Angle Command::getVitesseAngulaireAfterTrapeziumFilter(Angle vitesse_angulaire_atteinte, Angle angle_restant)
{
    if(fabs((angle_restant.wrap()).getValueInRadian())>M_PI_2 + 0.01)
    {
        angle_restant = (angle_restant+Angle(M_PI)).wrap();
    }

    Angle pivot(vitesse_angulaire_a_atteindre.getValueInRadian()*vitesse_angulaire_a_atteindre.getValueInRadian()/(2*acceleration_angulaire.getValueInRadian()));

    if((Angle(fabs(angle_restant.getValueInRadian()))-pivot).getValueInRadian()<=0)
    {
        return vitesse_angulaire_a_atteindre-Angle(copysign(min((float)fabs(vitesse_angulaire_a_atteindre.getValueInRadian()), acceleration_angulaire.getValueInRadian()), vitesse_angulaire_a_atteindre.getValueInRadian()));
    }
    else
    {
        return vitesse_angulaire_a_atteindre + Angle(copysign(min(acceleration_angulaire.getValueInRadian(), vitesse_angulaire_max.getValueInRadian()-(float)fabs(vitesse_angulaire_a_atteindre.getValueInRadian())), angle_restant.getValueInRadian()));
    }
}

void Command::goTo(Position position, bool stop)
{
    destination = position;
    direction = false;
    en_mouvement = true;
    this->stop = stop;
}
