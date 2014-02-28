#include "strategiev3.h"
#include "strategieV2.h"
#include "actionGoTo.h"
#include "leds.h"
#include "odometrie.h"
#include "asservissement.h"
#include "dijkstra.h"
#include "etape.h"
//#include <iostream>


StrategieV3::StrategieV3(bool isBlue) : MediumLevelAction()
{
    this->avoiding = false;
    this->etapeEnCours = 0;
    this->statusStrat=1;

    actionEtape[0] = ActionGoTo(Position(200, 1850, isBlue), false);
    actionEtape[1] = ActionGoTo(Position(200, 1400, isBlue), false);
    actionEtape[2] = ActionGoTo(Position(900, 1400, isBlue), false);
    actionEtape[3] = ActionGoTo(Position(400, 900, isBlue), false);
    actionEtape[4] = ActionGoTo(Position(900, 400, isBlue), false);
    actionEtape[5] = ActionGoTo(Position(2100, 400, isBlue), false);
    actionEtape[6] = ActionGoTo(Position(2600, 900, isBlue), false);
    actionEtape[7] = ActionGoTo(Position(2100, 1400, isBlue), false);
    actionEtape[8] = ActionGoTo(Position(1100, 900, isBlue), false);
    actionEtape[NOMBRE_ETAPES-1]= ActionGoTo(Position(1900, 900, isBlue), false);

    Etape* etape1;
    Etape* etape2;
    Etape* etape3;
    Etape* etape4;
    Etape* etape5;
    Etape* etape6;
    Etape* etape7;
    Etape* etape8;
    Etape* etape9;
    Etape* etape10;

    Etape** tableauEtapes1 = new Etape*[1];
    Etape** tableauEtapes2 = new Etape*[3];
    Etape** tableauEtapes3 = new Etape*[4];
    Etape** tableauEtapes4 = new Etape*[3];
    Etape** tableauEtapes5 = new Etape*[3];
    Etape** tableauEtapes6 = new Etape*[3];
    Etape** tableauEtapes7 = new Etape*[2];
    Etape** tableauEtapes8 = new Etape*[3];
    Etape** tableauEtapes9 = new Etape*[2];
    Etape** tableauEtapes10 = new Etape*[2];

    //arguments : Position, tableau des etapes liées, nombre d'étapes liées, numéro de l'étape, type d'étape, état de l'étape
    etape1 = new Etape(Position(200, 1850, isBlue), tableauEtapes1, 1, 1, Etape::DEPART, -1);
    etape2 = new Etape(Position(200, 1400, isBlue), tableauEtapes2, 3, 2, Etape::POINT_PASSAGE,-1);
    etape3 = new Etape(Position(900, 1400, isBlue), tableauEtapes3, 4, 3, Etape::FEU,-1);
    etape4 = new Etape(Position(400, 900, isBlue), tableauEtapes4, 3, 4, Etape::FEU,-1);
    etape5 = new Etape(Position(900, 400, isBlue), tableauEtapes5, 3, 5, Etape::FEU,-1);
    etape6 = new Etape(Position(2100, 400, isBlue), tableauEtapes6, 3, 6, Etape::FEU,-1);
    etape7 = new Etape(Position(2600, 900, isBlue), tableauEtapes7, 2, 7, Etape::FEU,-1);
    etape8 = new Etape(Position(2100, 1400, isBlue), tableauEtapes8, 3, 8, Etape::FEU,-1);
    etape9 = new Etape(Position(1100, 900, isBlue), tableauEtapes9, 2, 9, Etape::POINT_PASSAGE,-1);
    etape10 = new Etape(Position(1900, 900, isBlue), tableauEtapes10, 2, 10, Etape::POINT_PASSAGE,-1);

    tableauEtapes1[0] = etape2;

    tableauEtapes2[0] = etape1;
    tableauEtapes2[1] = etape3;
    tableauEtapes2[2] = etape4;

    tableauEtapes3[0] = etape2;
    tableauEtapes3[1] = etape4;
    tableauEtapes3[2] = etape8;
    tableauEtapes3[3] = etape9;

    tableauEtapes4[0] = etape2;
    tableauEtapes4[1] = etape3;
    tableauEtapes4[2] = etape5;

    tableauEtapes5[0] = etape4;
    tableauEtapes5[1] = etape6;
    tableauEtapes5[2] = etape9;

    tableauEtapes6[0] = etape5;
    tableauEtapes6[1] = etape7;
    tableauEtapes6[2] = etape10;

    tableauEtapes7[0] = etape6;
    tableauEtapes7[1] = etape8;

    tableauEtapes8[0] = etape3;
    tableauEtapes8[1] = etape7;
    tableauEtapes8[2] = etape10;

    tableauEtapes9[0] = etape3;
    tableauEtapes9[1] = etape5;

    tableauEtapes10[0] = etape6;
    tableauEtapes10[1] = etape8;

    etape1->setChildren(tableauEtapes1);
    etape2->setChildren(tableauEtapes2);
    etape3->setChildren(tableauEtapes3);
    etape4->setChildren(tableauEtapes4);
    etape5->setChildren(tableauEtapes5);
    etape6->setChildren(tableauEtapes6);
    etape7->setChildren(tableauEtapes7);
    etape8->setChildren(tableauEtapes8);
    etape9->setChildren(tableauEtapes9);
    etape10->setChildren(tableauEtapes10);

    Etape** tableauEtapesTotal = new Etape*[10];
    tableauEtapesTotal[0] = etape1;
    tableauEtapesTotal[1] = etape2;
    tableauEtapesTotal[2] = etape3;
    tableauEtapesTotal[3] = etape4;
    tableauEtapesTotal[4] = etape5;
    tableauEtapesTotal[5] = etape6 ;
    tableauEtapesTotal[6] = etape7 ;
    tableauEtapesTotal[7] = etape8 ;
    tableauEtapesTotal[8] = etape9 ;
    tableauEtapesTotal[9] = etape10;

    this->dijkstra = new Dijkstra(tableauEtapesTotal, NOMBRE_ETAPES);
    this->tableauEtapes = tableauEtapesTotal;

    dijkstra->setEtapeCourante(0);
}

int StrategieV3::update()
{
    this->actionEtape[this->etapeEnCours].reset();
    Etape* etape1 = this->tableauEtapes[0];
    Etape* etape2 = this->tableauEtapes[1];
    Etape* etape3 = this->tableauEtapes[2];
    Etape* etape4 = this->tableauEtapes[3];
    Etape* etape5 = this->tableauEtapes[4];
    Etape* etape6 = this->tableauEtapes[5];
    Etape* etape7 = this->tableauEtapes[6];
    Etape* etape8 = this->tableauEtapes[7];
    Etape* etape9 = this->tableauEtapes[8];
    Etape* etape10 = this->tableauEtapes[9];


    //Si on est en train d'éviter, on revient à l'étape précédente, et on marque l'étape comme à éviter
    if(this->avoiding)
    {
        this->tableauEtapes[this->etapeEnCours]->robotVu();
        this->tableauEtapes[this->etapeEnCours]->setState(-2);
        this->etapeEnCours = this->tableauEtapes[etapeEnCours]->getParent()->getNumero()-1;

        //On retourne à l'étape intermédiaire précédente
        StrategieV2::addTemporaryAction(&actionEtape[etapeEnCours]);
        this->avoiding = false;
    }
    else
    {
        if(this->statusStrat==2)//Si on vient d'arriver à une étape intermédiare
        {
            this->updateIntermedaire();
        }
        else//Sinon, statusStrat==1, et il faut donc choisir un nouvel objectif
        {
            //L'objectif qu'on vient de remplir est maintenant un simple point de passage
            this->tableauEtapes[this->etapeEnCours]->setEtapeType(Etape::POINT_PASSAGE);

            //On recalcul les distances par rapport à l'étape où l'on vient d'arriver
            dijkstra->setEtapeCourante(this->etapeEnCours);
            dijkstra->run();

            //On sélectionne l'objectif le plus prometteur : pas trop loin et qui rapporte
            //CETTE PARTIE EST A AMELIORER
            //on pourrait prendre en compte :
            //le fait le transporter un feu, ce qui active les objectifs de dépose
            //le temps que prend chaque action
            //le temps restant
            //la trajectoire de notre autre robot
            //...
            int meilleurEtape = -1;
            int scoreMaxi = -100000;
            for(int i = 0 ; i < NOMBRE_ETAPES ; i++)
            {
                if(this->tableauEtapes[i]->getEtapeType()==Etape::FEU)
                {
                    if(scoreMaxi < (1000-(this->tableauEtapes[i]->getDistance())))
                    {
                        scoreMaxi = (1000-(this->tableauEtapes[i]->getDistance()));
                        meilleurEtape = i;
                    }
                }
            }
            if(meilleurEtape==-1)
            {
                this->statusStrat=-1;//Plus rien à faire, on passe à l'action suivante de stratégieV2
            }
            else
            {
                this->goal = meilleurEtape;
                this->statusStrat = 2;//Jusqu'à preuve du contraire, la prochaine étape est une étape intermédiaire
                this->updateIntermedaire();//On y va
            }
        }
    }
    return this->statusStrat;
}

void StrategieV3::collisionAvoided(){
    this->avoiding = true;
}


void StrategieV3::updateIntermedaire()
{
    //Note : le parent d'une étape est l'étape le rapprochant le plus de l'étape d'origine
    //Ainsi, le parent du parent du parent... de n'importe quelle étape est l'étape d'origine
    //(sauf peut être le parent de l'étape d'origine, mais on s'en fout

    //std::cout << "updateIntermedaire\n";
    int etapeOuOnVientDArriver = this->etapeEnCours;
    this->etapeEnCours = this->goal;
    Etape* toto = this->tableauEtapes[1];
    Etape* toto2 = this->tableauEtapes[2];

    // Si la prochaine étape est le goal, alors au prochain update il faudra trouver un nouvel objectif -> status = 1;
    if(((this->tableauEtapes[this->etapeEnCours]->getParent()->getNumero()-1)) == etapeOuOnVientDArriver)
    {
        //std::cout << "la prochaine étape est le goal\n";
        this->statusStrat = 1;
    }

    //On cherche l'étape suivant vers l'etape - but
    while(((this->tableauEtapes[this->etapeEnCours]->getParent()->getNumero()-1)) != etapeOuOnVientDArriver)
    {
        //std::cout << "On cherche l'étape suivant vers l'etape - but" << this->etapeEnCours << "\n";
        this->etapeEnCours = ((this->tableauEtapes[this->etapeEnCours]->getParent()->getNumero()-1));
    }

    //On ajoute l'action d'aller en ligne droite vers cette étape
    StrategieV2::addTemporaryAction(&actionEtape[this->etapeEnCours]);
}


