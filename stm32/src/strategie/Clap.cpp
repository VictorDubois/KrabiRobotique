#include "strategieV2.h"
#include "asservissement.h"
#include "odometrie.h"
#include "Clap.h"

Clap::Clap(){}

Clap::Clap(bool isGreen, Position positionDepart, Position positionFin) : MediumLevelAction()
{

    //J'ai considéré qu il n y avait qu un bras sur le cote droit du robot. Du coup il recule pour actionner certain clap. Valentin m a dit qu il y aurait à son avis deux bras. Je changerait donc ca.

    this->isGreen = isGreen;
    this->positionDepart = positionDepart;
    this->positionFin = positionFin;
    this->versLaGauche = Position(0, 1761, isGreen);
    this->versLaDroite = Position(3000, 1761, isGreen);
    this->goalPosition = positionDepart;
    if ((positionDepart.getX()-positionFin.getX())>0)
    {
        this->direction = versLaGauche;
        this->goBack = true;
    }
    else
    {
        this->direction = versLaDroite;
        this->goBack = false;
    }
    /*this->positionDepartClapGreen = Position(2800, 1761, isGreen);
    this->positionFinClapGreen = Position(2600, 1761, isGreen);
    this->positionDepartClapYellow = Position(200, 1761, isGreen);
    this->positionFinClapYellow = Position(400, 1761, isGreen);*/
}


int Clap::update()
{
    if (status == 0)
    {
        StrategieV2::setCurrentGoal(this->goalPosition, false, VITESSE_LINEAIRE_MAX);
        status++;
        //Est ce qu il a atteint la position avant d'incrémenter le statut?
        //A quoi sert exactement la foncion EmptySharpsToCheck ?
        //Si elle sert à remettre à zéro tous les capteurs, le probleme c est que je ne sais pas ou est la boucle qui continue d'appeler une fonction de déplacement tant que les capteurs ne sont pas true.
     }
    else if (status == 1)
    {
        //StrategieV2::lookAt(this->direction, VITESSE_LINEAIRE_MAX);
        status++;
        //Je voulais me servir de la fonction LooAt avec un angle en argument mais je ne connait pas l'origine pour le mesurer. Est ce que je mets simplement M_PI ou 0 ?
        //Est ce qu il a finit de se positionner lorsqu il incremente le statut?
    }
    else if (status == 2)
    {
        #ifndef ROBOTHW
                qDebug() << "Deployer le bras";
        #endif
        //J'ai essayé de me servir u simul mais alors ce genre d'ecriture (ifndef..) je ne vois pas du tout comment s en servir.
        //J ai rajouté des etapes (de simples deplacements) dans krabi2015 pour essayer. Mais il ne s arrete pas quand il a effectué toutes les etapes. Il fait des allers retour entre la derniere et l avant derniere..pas normal ^^'Surtout que sur le truc initial y a pas ce souci du tout.
        //Bras::ouvrirBalaiDroit()
        status++;
    }
    else if (status == 3)
    {
        //deplacement = ActionGoTo(this->positionFin, this->goBack, VITESSE_LINEAIRE_MAX);
        //deplacement.update();
        status++;
        //On est d accord..j ai pas besion de lui redéfinir cette position comme CurrentGoal. Les CurrentGoal c est uniquement après dans la stratégie pour pondérer les goals.. Ou on les pondere? :/ suis paumée
    }
    else if (status == 4)
    {
        #ifndef ROBOTHW
                qDebug() << "Ranger le bras";
        #endif
        //Bras::fermerBalaiDroit()
        //status++;
                status = -1;
    }

//Je dois liberer de la place? delete depacement; delete versLaGauche; delete versLaDroite ?

    return status;
}
