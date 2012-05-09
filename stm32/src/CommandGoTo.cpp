#include "CommandGoTo.h"

CommandGoTo::CommandGoTo(Position DestinationFinale) :
    Command()
{
    vitesseFinale = 0;
    vitesse_lineaire_a_atteindre = 0;
    vitesse_angulaire_a_atteindre = 0;
    goBack = false;
    destination =  PositionPlusAngle(DestinationFinale, (DestinationFinale - Odometrie::odometrie->getPos().getPosition()).getAngle()); // La destination est à la position finale souhaitée et on choisit d'arrivé dans la direction formé par le point de départ et le point d'arrivé
}

CommandGoTo::CommandGoTo(Position DestinationFinale, bool goBack) :
    Command()
{
    vitesseFinale = 0;
    vitesse_lineaire_a_atteindre = 0;
    vitesse_angulaire_a_atteindre = 0;
    this->goBack = goBack;
    destination =  PositionPlusAngle(DestinationFinale, (DestinationFinale - Odometrie::odometrie->getPos().getPosition()).getAngle()); // La destination est à la position finale souhaitée et on choisit d'arrivé dans la direction formé par le point de départ et le point d'arrivé
}

CommandGoTo::~CommandGoTo()
{
    //dtor
}

Vitesse CommandGoTo::getLinearSpeed(void)
{
    return vitesse_lineaire_a_atteindre;
}

VitesseAngulaire CommandGoTo::getAngularSpeed(void)
{
    return vitesse_angulaire_a_atteindre;
}


void CommandGoTo::update()
{
        Distance distance_restante = (destination.getPosition() - (Odometrie::odometrie->getPos()).getPosition()).getNorme();
        Angle angle_restant = (distance_restante > DISTANCE_ARRET) ? (wrapAngle((destination.getPosition() -  Odometrie::odometrie->getPos().getPosition()).getAngle() - Odometrie::odometrie->getPos().getAngle())) : 0;//(wrapAngle(destination.getAngle() - Odometrie::odometrie->getPos().getAngle()));
        distance_restante = fabs(wrapAngle(angle_restant)) > 0.5 ? 0 : distance_restante;

		if( distance_restante < DISTANCE_ARRET)
        {
			vitesse_lineaire_a_atteindre = 0;
        }
		else
        {
            vitesse_lineaire_a_atteindre = getVitesseLineaireAfterTrapeziumFilter(Odometrie::odometrie->getVitesseLineaire(), distance_restante, angle_restant, vitesseFinale, goBack);
        }
        if (Angle(fabs(angle_restant)) < ANGLE_ARRET)
        {
            vitesse_angulaire_a_atteindre = 0;
        }
        else //if (fabs(wrapAngle(angle_restant))<3*M_PI_4)
        {
            vitesse_angulaire_a_atteindre = getVitesseAngulaireAfterTrapeziumFilter(Odometrie::odometrie->getVitesseAngulaire(), angle_restant, goBack);
        }
/*        else
        {
            vitesse_angulaire_a_atteindre = getVitesseAngulaireAfterTrapeziumFilter(Odometrie::odometrie->getVitesseAngulaire(), wrapAngle(angle_restant+M_PI), goBack);
        }
*/
}


Vitesse CommandGoTo::getVitesseLineaireAfterTrapeziumFilter(Vitesse vitesse_lineaire_a_atteindre, Distance distance_restante,Angle angle_restant, Vitesse vitesseFinale, bool goBack)
{
    Distance pivot = (vitesse_lineaire_a_atteindre-vitesseFinale)*((vitesse_lineaire_a_atteindre-vitesseFinale)/2+vitesseFinale)/acceleration_lineaire; // La distance pivot est la distance qu'il resterait à parcourir si le robot commençait maintenant à décélérer avec sa décélération maximale (acceleration_lineaire) (Vaa-Vf)^2/2a+(Vaa-Vf)*Vf/a (calculer l'aire sous la courbe de vitesse)
    if (false && distance_restante <= VITESSE_LINEAIRE_MAX/VITESSE_ANGULAIRE_MAX && fabs(angle_restant) > ANGLE_ARRET + 0.2)
    {
        return 0 ; // sinon on se retrouve concé dans un cercle infini car l'accélaration angulaire et linaire du robot ne permet pas d'atteindre le point souhaité (on tourne autour infiniment)
    }
    else
    {
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
        else if (!goBack)//fabs(wrapAngle(angle_restant))<3*M_PI_4) // Le point d'arrivé est encore devant nous
        {
            return vitesse_lineaire_a_atteindre + Vitesse(MIN(acceleration_lineaire,vitesse_lineaire_max/*-10000/(distance_restante*distance_restante*distance_restante)*/-vitesse_lineaire_a_atteindre)); // si vitesse_lineaire_max-vitesse_lineaire_a_atteindre > acceleration_lineaire*dt alors on est encore dans la fase assendante du trapéze.
        }
        else // Il est maintenant derière nous donc il faut reculer
        {
            return vitesse_lineaire_a_atteindre + Vitesse(MAX(-acceleration_lineaire,-vitesse_lineaire_max/*+10000/(distance_restante*distance_restante*distance_restante)*/-vitesse_lineaire_a_atteindre)); // si vitesse_lineaire_max-vitesse_lineaire_a_atteindre > acceleration_lineaire*dt alors on est encore dans la fase assendante du trapéze.
        }
    }

}

VitesseAngulaire CommandGoTo::getVitesseAngulaireAfterTrapeziumFilter(VitesseAngulaire vitesse_angulaire_a_atteindre, Angle angle_restant, bool goBack)
{
    Angle pivot = wrapAngle(vitesse_angulaire_a_atteindre*vitesse_angulaire_a_atteindre/(2*acceleration_angulaire)); // idem qu'en linéaire

    if((Angle((fabs(angle_restant)-fabs(pivot))))<=0)
    {
        return vitesse_angulaire_a_atteindre-VitesseAngulaire(copysign(MIN((float)fabs(vitesse_angulaire_a_atteindre), (float)acceleration_angulaire), vitesse_angulaire_a_atteindre));
    }
    else
    {
        return vitesse_angulaire_a_atteindre + VitesseAngulaire(copysign(MIN(acceleration_angulaire, vitesse_angulaire_max-(float)fabs(vitesse_angulaire_a_atteindre)), angle_restant));
    }
}

PositionPlusAngle** CommandGoTo::path(Position DestinationFinale)
{
    PositionPlusAngle destination =  PositionPlusAngle(DestinationFinale, (DestinationFinale - Odometrie::odometrie->getPos().getPosition()).getAngle()); // La destination est à la position finale souhaitée et on choisit d'arrivé dans la direction formé par le point de départ et le point d'arrivé
    PositionPlusAngle** trajectoire = new PositionPlusAngle*[PATH_LENGTH];

    trajectoire[0] = new PositionPlusAngle(Odometrie::odometrie->getPos().getPosition(),Odometrie::odometrie->getPos().getAngle());

    Vitesse vitesse_lineaire_atteinte = 0;
    VitesseAngulaire vitesse_angulaire_atteinte = 0;

    for (int i=1; i<PATH_LENGTH; i++)
    {
        Distance distance_restante = (destination.getPosition() - trajectoire[i-1]->getPosition()).getNorme();
        Angle angle_restant = (distance_restante > DISTANCE_ARRET) ? (wrapAngle((destination.getPosition() -  trajectoire[i-1]->getPosition()).getAngle() - trajectoire[i-1]->getAngle())) : (wrapAngle(destination.getAngle() - trajectoire[i-1]->getAngle()));

        PositionPlusAngle* positionPlusAngle = new PositionPlusAngle(Position(0.,0.),Angle(0.));


        if( distance_restante < DISTANCE_ARRET)
        {
            vitesse_lineaire_atteinte = 0;
        }
        else
        {
            vitesse_lineaire_atteinte = getVitesseLineaireAfterTrapeziumFilter(vitesse_lineaire_atteinte, distance_restante, angle_restant,0,false);
        }
        if (Angle(fabs(angle_restant)) < ANGLE_ARRET)
        {
            vitesse_angulaire_atteinte = 0;
        }
        else
        {
             vitesse_angulaire_atteinte = getVitesseAngulaireAfterTrapeziumFilter(vitesse_angulaire_atteinte, angle_restant, false);
        }
        positionPlusAngle->setAngle(trajectoire[i-1]->getAngle()+Angle(vitesse_angulaire_atteinte));
        positionPlusAngle->setPosition(trajectoire[i-1]->getPosition() + Position(Distance(vitesse_lineaire_atteinte)*cos(trajectoire[i-1]->getAngle()), Distance(vitesse_lineaire_atteinte)*sin(trajectoire[i-1]->getAngle())));    //mettre sinx si ça marche pas et non sin
        trajectoire[i] = positionPlusAngle;
    }
    return trajectoire;
}

void CommandGoTo::deletePath(PositionPlusAngle** path)
{
   for (int i=1; i<PATH_LENGTH; i++)
   {
       delete path[i];
   }
   delete path;
}


PositionPlusAngle** CommandGoTo::path()
{
    if (Asservissement::asservissement->command)
    {

        PositionPlusAngle destination =  ((CommandGoTo*) Asservissement::asservissement->command)->getDestination();
        PositionPlusAngle** trajectoire = new PositionPlusAngle*[PATH_LENGTH];

        trajectoire[0] = new PositionPlusAngle(Odometrie::odometrie->getPos().getPosition(),Odometrie::odometrie->getPos().getAngle());

        Vitesse vitesse_lineaire_atteinte = 0;
        VitesseAngulaire vitesse_angulaire_atteinte = 0;

        for (int i=1; i<PATH_LENGTH; i++)
        {
            PositionPlusAngle* positionPlusAngle = new PositionPlusAngle(Position(0.,0.),Angle(0.));


            Distance distance_restante = (destination.getPosition() - trajectoire[i-1]->getPosition()).getNorme();
            Angle angle_restant = (distance_restante > DISTANCE_ARRET) ? (wrapAngle((destination.getPosition() -  trajectoire[i-1]->getPosition()).getAngle() - trajectoire[i-1]->getAngle())) : (wrapAngle(destination.getAngle() - trajectoire[i-1]->getAngle()));
            distance_restante = fabs(wrapAngle(angle_restant)) > 0.5 ? 0 : distance_restante;

            if( distance_restante < DISTANCE_ARRET)
            {
                vitesse_lineaire_atteinte = 0;
            }
            else
            {
                vitesse_lineaire_atteinte = getVitesseLineaireAfterTrapeziumFilter(vitesse_lineaire_atteinte, distance_restante, angle_restant,0, ((CommandGoTo*) Asservissement::asservissement->command)->getGoBack());
            }
            if (Angle(fabs(angle_restant)) < ANGLE_ARRET)
            {
                vitesse_angulaire_atteinte = 0;
            }
            else //if (fabs(wrapAngle(angle_restant))<3*M_PI_4)
            {
                vitesse_angulaire_atteinte = getVitesseAngulaireAfterTrapeziumFilter(vitesse_angulaire_atteinte, wrapAngle(angle_restant),((CommandGoTo*) Asservissement::asservissement->command)->getGoBack());
            }
            /*else
            {
                 vitesse_angulaire_atteinte = getVitesseAngulaireAfterTrapeziumFilter(vitesse_angulaire_atteinte, wrapAngle(angle_restant+M_I));
            }
            */
            positionPlusAngle->setAngle(trajectoire[i-1]->getAngle()+Angle(vitesse_angulaire_atteinte));
            positionPlusAngle->setPosition(trajectoire[i-1]->getPosition() + Position(Distance(vitesse_lineaire_atteinte)*cos(trajectoire[i-1]->getAngle()), Distance(vitesse_lineaire_atteinte)*sin(trajectoire[i-1]->getAngle())));    //mettre sinx si ça marche pas et non sin
            trajectoire[i] = positionPlusAngle;
        }
        return trajectoire;
    }
    else
    {
        return NULL;
    }
}



PositionPlusAngle CommandGoTo::getDestination()
{
    return this->destination;
}

bool CommandGoTo::getGoBack()
{
    return goBack;
}
