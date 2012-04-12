#include "CommandTourner.h"

CommandTourner::CommandTourner(Angle angle) :
    Command(),
    vitesseAngulaireFinale(0),
    vitesse_lineaire_a_atteindre(0),
    vitesse_angulaire_a_atteindre(0)
{
    destination = PositionPlusAngle(Odometrie::odometrie->getPos().getPosition(), wrapAngle(Odometrie::odometrie->getPos().getAngle() + angle) );
}

CommandTourner::CommandTourner(Angle angle, VitesseAngulaire vitesseAngulaireFinale) :
    Command(),
    vitesseAngulaireFinale(vitesseAngulaireFinale),
    vitesse_lineaire_a_atteindre(0),
    vitesse_angulaire_a_atteindre(0)
{
    destination = PositionPlusAngle(Odometrie::odometrie->getPos().getPosition(), wrapAngle(Odometrie::odometrie->getPos().getAngle() + angle) );
}

CommandTourner::~CommandTourner()
{
    //dtor
}

Vitesse CommandTourner::getLinearSpeed(void)
{
    return vitesse_lineaire_a_atteindre;
}

VitesseAngulaire CommandTourner::getAngularSpeed(void)
{
    return vitesse_angulaire_a_atteindre;
}


void CommandTourner::update(void)
{
        Distance distance_restante = (destination.getPosition() - (Odometrie::odometrie->getPos()).getPosition()).getNorme();
        Angle angle_restant = (destination.getPosition()).getAngle() - Odometrie::odometrie->getPos().getAngle();

		if( distance_restante < DISTANCE_ARRET)
        {
			vitesse_lineaire_a_atteindre = 0;
        }
		else
        {
            vitesse_lineaire_a_atteindre = getVitesseLineaireAfterTrapeziumFilter(Odometrie::odometrie->getVitesseLineaire(), distance_restante,angle_restant);
        }
        if (Angle(fabs(angle_restant)) < ANGLE_ARRET)
        {
            vitesse_angulaire_a_atteindre = 0;
        }
        else
        {
            vitesse_angulaire_a_atteindre = getVitesseAngulaireAfterTrapeziumFilter(Odometrie::odometrie->getVitesseAngulaire(), angle_restant);
        }
}


Vitesse CommandTourner::getVitesseLineaireAfterTrapeziumFilter(Vitesse vitesse_lineaire_atteinte, Distance distance_restante, Angle angle_restant)
{
        Distance pivot = vitesse_lineaire_a_atteindre*vitesse_lineaire_a_atteindre/(2*acceleration_lineaire); // La distance pivot est la distance qu'il resterait à parcourir si le robot commençait maintenant à décélérer avec sa décélération maximale (acceleration_lineaire) (Vaa-Vf)^2/2a+(Vaa-Vf)*Vf/a (calculer l'aire sous la courbe de vitesse)

    if (distance_restante-pivot <=0)  //Le robot est assez proche (ou trop proche) du point d'arrivé pour pouvoir décélerer assez pour l'atteindre avec la vitesse final demandé.
    {
        if(vitesse_lineaire_a_atteindre>0)
        {
            return (vitesse_lineaire_a_atteindre - Vitesse(acceleration_lineaire) > 0 ?  vitesse_lineaire_a_atteindre - Vitesse(acceleration_lineaire) : 0 ); // Si Vlaa - al > vitesseFinale alors Vlaa = Vlaa - al sinon Vlaa = vitesseFinale
        }
        else
        {
            return (vitesse_lineaire_a_atteindre + Vitesse(acceleration_lineaire) <0 ?  vitesse_lineaire_a_atteindre + Vitesse(acceleration_lineaire) : 0 );
        }
    }
    else
    {
        return vitesse_lineaire_a_atteindre + Vitesse(MIN(acceleration_lineaire,vitesse_lineaire_max-vitesse_lineaire_a_atteindre)); // si vitesse_lineaire_max-vitesse_lineaire_a_atteindre > acceleration_lineaire*dt alors on est encore dans la fase assendante du trapéze.
    }
}


VitesseAngulaire CommandTourner::getVitesseAngulaireAfterTrapeziumFilter(VitesseAngulaire vitesse_angulaire_atteinte, Angle angle_restant)
{
    Angle pivot = (vitesse_angulaire_a_atteindre-vitesseAngulaireFinale)*((vitesse_angulaire_a_atteindre-vitesseAngulaireFinale)/2+vitesseAngulaireFinale)/acceleration_angulaire; // idem qu'en linéaire

    if((Angle(fabs(angle_restant))-pivot)<=0)
    {
        return vitesse_angulaire_a_atteindre-VitesseAngulaire(copysign(MIN((float)fabs(vitesse_angulaire_a_atteindre), (float)acceleration_angulaire), vitesse_angulaire_a_atteindre));
    }
    else
    {
        return vitesse_angulaire_a_atteindre + VitesseAngulaire(copysign(MIN(acceleration_angulaire, vitesse_angulaire_max-(float)fabs(vitesse_angulaire_a_atteindre)), angle_restant));
    }
}
