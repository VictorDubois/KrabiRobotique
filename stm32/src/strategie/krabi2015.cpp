#include "krabi2015.h"

Krabi2015::Krabi2015(bool isBlue) : StrategieV3(isBlue)
{
    // Initialisation des stocks

    //Initialisation des tableaux d'étapes
    this->nombreEtapes = NOMBRE_ETAPES;
    this->numeroEtapeGarage = ETAPE_GARAGE;
    tableauEtapesTotal = new Etape*[NOMBRE_ETAPES];
    actionEtape = new MediumLevelAction*[NOMBRE_ETAPES];
    actionGoto = new ActionGoTo[NOMBRE_ETAPES];
    // TODO: A supprimer pour une variable statique dans Etape
    int numeroEtape = 0;

    // Création des étapes
    //arguments : Position, tableau des etapes liées, nombre d'étapes liées, numéro de l'étape, type d'étape, état de l'étape, nombreEtapesLieesParFinirEtape
    //Toutes ces étapes sont créées pour isBlue = isYellow
    int isYellow=isBlue;
    Etape* etape0 = new Etape(Position(250, 1000, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::DEPART, -1, 0); //départ au fond de la zone de départ
    Etape* etape1 = new Etape(Position(700, 1000, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape2 = new Etape(Position(836, 1700, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::CLAP, -1, 0);
    Etape* etape3 = new Etape(Position(1000, 1700, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape4 = new Etape(Position(236, 1700, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::CLAP, -1, 0);
    Etape* etape5 = new Etape(Position(400, 1700, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape6 = new Etape(Position(2500, 1700, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::CLAP, -1, 0);
    Etape* etape7 = new Etape(Position(2300, 1700, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape8 = new Etape(Position(250, 1750, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::GOBELET, -1, 0);
    Etape* etape9 = new Etape(Position(910, 830, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::GOBELET, -1, 0);
    Etape* etape10 = new Etape(Position(1500, 1650, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::GOBELET, -1, 0);
    Etape* etape11 = new Etape(Position(2090, 830, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::GOBELET, -1, 0);
    Etape* etape12 = new Etape(Position(2750, 1750, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::GOBELET, -1, 0);
    Etape* etape13 = new Etape(Position(90, 1750, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::PIED, -1, 0);
    Etape* etape14 = new Etape(Position(90, 1850, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::PIED, -1, 0);
    Etape* etape15 = new Etape(Position(90, 200, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::PIED, -1, 0);
    Etape* etape16 = new Etape(Position(850, 100, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::PIED, -1, 0);
    Etape* etape17 = new Etape(Position(850, 200, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::PIED, -1, 0);
    Etape* etape18 = new Etape(Position(870, 1355, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::PIED, -1, 0);
    Etape* etape19 = new Etape(Position(1100, 1770, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::PIED, -1, 0);
    Etape* etape20 = new Etape(Position(1300, 1400, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::PIED, -1, 0);
    Etape* etape21 = new Etape(Position(1250, 1800, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::AMPOULE, -1, 0);
    Etape* etape22 = new Etape(Position(1750, 1800, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::AMPOULE, -1, 0);
    Etape* etape23 = new Etape(Position(2300, 1500, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape24 = new Etape(Position(2800, 1450, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape25 = new Etape(Position(2800, 600, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);

    /*
    Etape* etape0 = new Etape(Position(250, 1000, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::DEPART, -1, 0); //départ au fond de la zone de départ
    Etape* etape1 = new Etape(Position(600, 1000, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape2 = new Etape(Position(700, 1000, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape9 = new Etape(Position(1200, 600, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::TAPIS, -1, 0);
    Etape* etape8 = new Etape(Position(1200, 800, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape3 = new Etape(Position(1200, 1000, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape4 = new Etape(Position(1000, 1300, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape5 = new Etape(Position(1500, 1300, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape6 = new Etape(Position(1800, 1200, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape7 = new Etape(Position(1700, 800, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);

    etape0->addVoisin(etape2);
    etape1->addVoisin(etape2);
    etape2->addVoisin(etape3);
    etape3->addVoisin(etape4);
    etape3->addVoisin(etape5);
    etape3->addVoisin(etape6);
    etape3->addVoisin(etape7);
    etape3->addVoisin(etape8);
    etape4->addVoisin(etape5);
    etape5->addVoisin(etape6);
    etape6->addVoisin(etape7);
    etape7->addVoisin(etape8);
    etape0->addVoisin(etape1);
    etape8->addVoisin(etape9);
    */

    //J ai modifié NOMBRE_ETAPES dans krabi2015.h et le etape.h



    //Initialisation des actions par défaut
    for(int i = 0 ; i < NOMBRE_ETAPES ; i++)
    {
        if (tableauEtapesTotal[i]->getState() == -1)
        {
            actionGoto[i] = ActionGoTo(tableauEtapesTotal[i]->getPosition());
            actionEtape[i] = &actionGoto[i];
        }

    }

    actionClap[0]= Clap(Position(836, 1700, isBlue),Position(1000, 1700, isBlue));
    actionEtape[1]= &actionClap[0];


    etape0->addVoisin(etape1);
    etape1->addVoisin(etape2);
    etape1->addVoisin(etape9);
    etape1->addVoisin(etape23);
    etape18->addVoisin(etape4);
    etape2->addVoisin(etape3);
    etape3->addVoisin(etape4);
    etape4->addVoisin(etape5);
    etape4->addVoisin(etape13);
    etape4->addVoisin(etape8);
    etape6->addVoisin(etape7);
    etape1->addVoisin(etape18);
    etape18->addVoisin(etape2);
    etape13->addVoisin(etape14);
    etape14->addVoisin(etape8);
    etape18->addVoisin(etape20);
    etape18->addVoisin(etape19);
    etape3->addVoisin(etape19);
    etape3->addVoisin(etape21);
    etape3->addVoisin(etape10);
    etape9->addVoisin(etape20);
    etape9->addVoisin(etape18);
    etape21->addVoisin(etape22);
    etape10->addVoisin(etape22);
    etape20->addVoisin(etape10);
    etape10->addVoisin(etape11);
    etape10->addVoisin(etape23);
    etape10->addVoisin(etape6);
    etape23->addVoisin(etape6);
    etape23->addVoisin(etape7);
    etape23->addVoisin(etape12);
    etape23->addVoisin(etape24);
    etape6->addVoisin(etape12);
    etape12->addVoisin(etape24);
    etape23->addVoisin(etape11);
    etape11->addVoisin(etape20);
    etape10->addVoisin(etape11);
    etape9->addVoisin(etape11);
    etape11->addVoisin(etape25);
    etape9->addVoisin(etape15);
    etape9->addVoisin(etape17);
    etape16->addVoisin(etape17);
    etape16->addVoisin(etape15);
    etape15->addVoisin(etape17);
    etape15->addVoisin(etape9);


    // Lancer Dijkstra
    startDijkstra();
}

void Krabi2015::updateStock(){
    switch(this->tableauEtapes[this->etapeEnCours]->getEtapeType()){
        case Etape::DEPART :
             this->tableauEtapes[this->etapeEnCours]->setEtapeType(Etape::POINT_PASSAGE);
            break;
        default :
            this->tableauEtapes[this->etapeEnCours]->setEtapeType(Etape::POINT_PASSAGE);
    }
}

int Krabi2015::getScoreEtape(int i){
    /* TODO : Supprimer le modificateur temporel et inclure directement un coefficient dans le score pour les actions longues
    Plus tard : pourquoi pas changer le système en ayant les FEU etc... fils de Etape, ça éviterait aussi le switch dans updateStock().
    Juste faire attention à comment transmettre le stock à update.
    */
    switch (this->tableauEtapesTotal[i]->getEtapeType()){
            case Etape::DEPART :
                return 0;
                break;
            case Etape::CLAP :
                return 50;
                break;
            case Etape::GOBELET :
                return 40;
            case Etape::AMPOULE :
                return 10;
            case Etape::PIED :
                return 0;//ce devrait être 20
            case Etape::POINT_PASSAGE :
                return 0;
            default :
                return 0;
                break;
    }
}
