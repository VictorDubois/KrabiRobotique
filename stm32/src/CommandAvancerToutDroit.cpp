#include "CommandAvancerToutDroit.h"
#include "odometrie.h"


CommandAvancerToutDroit::CommandAvancerToutDroit(Distance distance) :
    Command()
{
    vitesse_lineaire_a_atteindre = 0;
    vitesse_angulaire_a_atteindre = 0;
    vitesseFinale = 0;
    destination = Odometrie::odometrie->getPos() + distance;
}

CommandAvancerToutDroit::CommandAvancerToutDroit(Distance distance, Vitesse vitesseFinale) :
    Command()
{
    vitesse_lineaire_a_atteindre = 0;
    vitesse_angulaire_a_atteindre = 0;
    vitesseFinale = vitesseFinale;
    destination = Odometrie::odometrie->getPos() + distance;
}

CommandAvancerToutDroit::~CommandAvancerToutDroit()
{
       Command* & c = Asservissement::asservissement->command;
       c = NULL;
}

Vitesse CommandAvancerToutDroit::getLinearSpeed()
{
	return vitesse_lineaire_a_atteindre;
}

Angle CommandAvancerToutDroit::getAngularSpeed()
{
	return vitesse_angulaire_a_atteindre;
}

void CommandAvancerToutDroit::update()
{
        Distance distance_restante = (destination.getPosition() - (Odometrie::odometrie->getPos()).getPosition()).getNorme();
        Angle angle_restant = wrapAngle((destination.getPosition() -  Odometrie::odometrie->getPos().getPosition()).getAngle() - Odometrie::odometrie->getPos().getAngle());

		if( distance_restante < DISTANCE_ARRET)
        {
			vitesse_lineaire_a_atteindre = 0;
        }
		else
        {
            vitesse_lineaire_a_atteindre = getVitesseLineaireAfterTrapeziumFilter(Odometrie::odometrie->getVitesseLineaire(), distance_restante);
        }
        if (fabs(angle_restant) < ANGLE_ARRET)
        {
            vitesse_angulaire_a_atteindre = 0;
        }
        else
        {
            vitesse_angulaire_a_atteindre = getVitesseAngulaireAfterTrapeziumFilter(Odometrie::odometrie->getVitesseAngulaire(), angle_restant);
        }
}


Vitesse CommandAvancerToutDroit::getVitesseLineaireAfterTrapeziumFilter(Vitesse vitesse_lineaire_atteinte, Distance distance_restante)
{
    Distance pivot = (vitesse_lineaire_a_atteindre-vitesseFinale)*((vitesse_lineaire_a_atteindre-vitesseFinale)/2+vitesseFinale)/acceleration_lineaire; // La distance pivot est la distance qu'il resterait à parcourir si le robot commençait maintenant à décélérer avec sa décélération maximale (acceleration_lineaire) (Vaa-Vf)^2/2a+(Vaa-Vf)*Vf/a (calculer l'aire sous la courbe de vitesse)

    if (distance_restante-pivot <=0)  //Le robot est assez proche (ou trop proche) du point d'arrivé pour pouvoir décélerer assez pour l'atteindre avec la vitesse final demandé.
    {
        if(vitesse_lineaire_a_atteindre>vitesseFinale)
        {
            return (vitesse_lineaire_a_atteindre - Vitesse(acceleration_lineaire) > vitesseFinale ?  vitesse_lineaire_a_atteindre - Vitesse(acceleration_lineaire) : vitesseFinale ); // Si Vlaa - al > vitesseFinale alors Vlaa = Vlaa - al sinon Vlaa = vitesseFinale
        }
        else
        {
            return (vitesse_lineaire_a_atteindre + Vitesse(acceleration_lineaire) < vitesseFinale ?  vitesse_lineaire_a_atteindre + Vitesse(acceleration_lineaire) : vitesseFinale );
        }
    }
    else
    {
        return vitesse_lineaire_a_atteindre + Vitesse(MIN(acceleration_lineaire,vitesse_lineaire_max-vitesse_lineaire_a_atteindre)); // si vitesse_lineaire_max-vitesse_lineaire_a_atteindre > acceleration_lineaire*dt alors on est encore dans la fase assendante du trapéze.
    }
}

VitesseAngulaire CommandAvancerToutDroit::getVitesseAngulaireAfterTrapeziumFilter(VitesseAngulaire vitesse_angulaire_atteinte, Angle angle_restant)
{
    Angle pivot = vitesse_angulaire_a_atteindre*vitesse_angulaire_a_atteindre/acceleration_angulaire; // idem qu'en linéaire

    if((Angle(fabs(angle_restant))-pivot)<=0)
    {
        return vitesse_angulaire_a_atteindre-VitesseAngulaire(copysign(MIN((float)fabs(vitesse_angulaire_a_atteindre), (float)acceleration_angulaire), vitesse_angulaire_a_atteindre));
    }
    else
    {
        return vitesse_angulaire_a_atteindre + VitesseAngulaire(copysign(MIN(acceleration_angulaire, vitesse_angulaire_max-(float)fabs(vitesse_angulaire_a_atteindre)), angle_restant));
    }

}
