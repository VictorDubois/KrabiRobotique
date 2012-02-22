#include "TrapezoidalCommand.h"


TrapezoidalCommand::~TrapezoidalCommand()
{
       Command* & c = Asservissement::asservissement->command;
       c = NULL;
}

TrapezoidalCommand::TrapezoidalCommand() :
    Command(),      //apparement ça fonctionne sans mais c'est bizarre
    vitesse_lineaire_a_atteindre(0),
    vitesse_angulaire_a_atteindre(0),
    fini(false)
{
}

float TrapezoidalCommand::getLinearSpeed()
{
	return vitesse_lineaire_a_atteindre;
}

Angle TrapezoidalCommand::getAngularSpeed()
{
	return vitesse_angulaire_a_atteindre;
}

void TrapezoidalCommand::update(PositionPlusAngle positionPlusAngleActuelle, Angle vitesse_angulaire_atteinte, Distance vitesse_lineaire_atteinte)
{
    // Il faut toujour utiliser goTo() lorsque l'on déclare une commande
	Position vecteur_pos_actuelle_pos_arrivee = destination-positionPlusAngleActuelle.getPosition();
	Angle angle_restant;

	if(en_mouvement && !direction)
	{
		Distance distance_restante = (vecteur_pos_actuelle_pos_arrivee).getNorme();
		angle_restant = vecteur_pos_actuelle_pos_arrivee.getAngle() - positionPlusAngleActuelle.getAngle();

		if(distance_restante < DISTANCE_ARRET){
		    fini = true;
			Strategie::strategie->done();
			vitesse_lineaire_a_atteindre = 0;
		}
		else{
            vitesse_lineaire_a_atteindre = getVitesseLineaireAfterTrapeziumFilter(vitesse_lineaire_atteinte, distance_restante, angle_restant);
		}

		if(distance_restante < DISTANCE_ARRET || fabs(wrapAngle(angle_restant)) < ANGLE_ARRET){
			vitesse_angulaire_a_atteindre = 0;
		}
		else{
			vitesse_angulaire_a_atteindre = getVitesseAngulaireAfterTrapeziumFilter(vitesse_angulaire_a_atteindre, angle_restant);
		}
	}
	else if(direction && !en_mouvement)
	{
	angle_restant = vecteur_pos_actuelle_pos_arrivee.getAngle() - positionPlusAngleActuelle.getAngle();

		if(fabs(wrapAngle(angle_restant)) < ANGLE_ARRET)
		{
			vitesse_angulaire_a_atteindre = 0;
			fini = true;
			Strategie::strategie->done();
        }
		else
			vitesse_angulaire_a_atteindre = getVitesseAngulaireAfterTrapeziumFilter(vitesse_angulaire_a_atteindre, angle_restant);
	}
	else if(!direction && !en_mouvement)
	{
        destination.setX(destination.getX()-vitesse_angulaire_atteinte);
		if(fabs(destination.getX()) < ANGLE_ARRET)
        {
			vitesse_angulaire_a_atteindre = 0;
			fini = true;
			Strategie::strategie->done();
        }
		else
			vitesse_angulaire_a_atteindre = getVitesseAngulaireAfterTrapeziumFilter(vitesse_angulaire_a_atteindre, destination.getX());
	}
	else if(direction && en_mouvement)
    {
		destination.setX(destination.getX() - vitesse_lineaire_atteinte);

		if(destination.getX() < DISTANCE_ARRET)
        {
			Strategie::strategie->done();
			fini = true;
			vitesse_lineaire_a_atteindre = 0;
        }
		else
        {
            vitesse_lineaire_a_atteindre = getVitesseLineaireAfterTrapeziumFilter(vitesse_lineaire_atteinte, destination.getX(), angle_restant);
        }
    }
}



Distance TrapezoidalCommand::getVitesseLineaireAfterTrapeziumFilter(Distance vitesse_lineaire_atteinte, Distance distance_restante, Angle angle_restant)
{
    // Le pivot est la distance que l'on parcourerait si on commencait à décélérer dès maintenant jusqu'une vitesse nulle
    float pivot = vitesse_lineaire_a_atteindre*vitesse_lineaire_a_atteindre/(2*acceleration_lineaire);
    if((distance_restante-pivot)<=0 && stop)
    {
        //On est proche de la cible et l’on doit décélerer
        if(vitesse_lineaire_a_atteindre>0.)
        {
            return vitesse_lineaire_a_atteindre-Distance(MIN(vitesse_lineaire_a_atteindre, acceleration_lineaire));
        }
        else
        {
            return vitesse_lineaire_a_atteindre-Distance(MAX(vitesse_lineaire_a_atteindre, -acceleration_lineaire));
        }
    }
    else if(direction || fabs(wrapAngle(angle_restant))<M_PI_2)
    {
        // Si la destination est devant nous
        // Alors on ajoute à la vitesse une accélération positive (jusqu'à la valeur (vitesse_lineaire_max))
        // Autrement dit, si on recule dans la mauvaise direction on ralenti et si on avance dans la bonne direction alors on avance plus vite
        return vitesse_lineaire_a_atteindre + Distance(MIN(acceleration_lineaire, (vitesse_lineaire_max-vitesse_lineaire_a_atteindre)));
    }
    else{
        // Si la destination est derrière nous
        // Alors on ajoute à la vitesse une accélération négative (jusqu'à la valeur (-vitesse_lineaire_max))
        // Autrement dit, si on avance dans la mauvaise direction on ralenti et si on recule dans la bonne direction alors on recule plus vite
        return vitesse_lineaire_a_atteindre + Distance(MAX(-acceleration_lineaire, (-vitesse_lineaire_max-vitesse_lineaire_a_atteindre)));
    }
}

Angle TrapezoidalCommand::getVitesseAngulaireAfterTrapeziumFilter(Angle vitesse_angulaire_atteinte, Angle angle_restant)
{
    //est ce que le deuxiéme if ne suffit pas? (else if je devrais dire)
    if(!direction && fabs(angle_restant)>M_PI_2 + 0.01)
    {
        angle_restant = angle_restant+Angle(M_PI);
    }
    else if(direction && fabs(wrapAngle(angle_restant))>M_PI_2 + 0.01)
    {
        angle_restant = wrapAngle(angle_restant+Angle(M_PI));
    }
    // pivot = angle parcouru pour s'arreter
    Angle pivot(vitesse_angulaire_a_atteindre*vitesse_angulaire_a_atteindre/(2*acceleration_angulaire));
    if((Angle(fabs(angle_restant))-pivot)<=0)
    {
        return vitesse_angulaire_a_atteindre-Angle(copysign(MIN((float)fabs(vitesse_angulaire_a_atteindre), (float)acceleration_angulaire), vitesse_angulaire_a_atteindre));
    }
    else
    {
        return vitesse_angulaire_a_atteindre + Angle(copysign(MIN(acceleration_angulaire, vitesse_angulaire_max-(float)fabs(vitesse_angulaire_a_atteindre)), angle_restant));
    }
}
//aller à une position
void TrapezoidalCommand::goTo(Position position, bool stop)
{
    fini = false;
    destination = position;
    direction = false;
    en_mouvement = true;
    this->stop = stop;
}

//faire face à une position
void TrapezoidalCommand::face(Position position, bool stop)
{
    fini = false;
	destination = position;
	direction = true;
	en_mouvement = false;
	this->stop = stop;
}

//tourner du premier chiffre des positions (en degre)
void TrapezoidalCommand::tourne(Position position, bool stop)
{
    fini = false;
	destination = position;
	destination.setX(DEGTORAD(destination.getX()));
	direction = false;
	en_mouvement = false;
	this->stop = stop;
}

//avancer tout droit
void TrapezoidalCommand::avance(Position position, bool stop)
{
    fini = false;
	destination = position;
	direction = true;
	en_mouvement = true;
	this->stop = stop;
}

bool TrapezoidalCommand::destinationAtteinte()
{
    return fini;
}
