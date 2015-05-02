#include "krabi2015.h"

Krabi2015::Krabi2015(bool isYellow) : StrategieV3(isYellow)
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
    // Arguments : Position, numéro étape, tableau des étapes, type d'étape, état de l'étape, nombre étapes liées
    Etape* etape0 = new Etape(Position(250, 1000, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::DEPART, -1, 0); //départ au fond de la zone de départ
    Etape* etape1 = new Etape(Position(700, 1000, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::DEPOSE_GOBELET, -1, 0);
    Etape* etape2 = new Etape(Position(836, 1780, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::CLAP, -1, 0);
    Etape* etape3 = new Etape(Position(1000, 1780, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape4 = new Etape(Position(236, 1780, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::CLAP, -1, 0);
    Etape* etape5 = new Etape(Position(400, 1780, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape6 = new Etape(Position(2500, 1780, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::CLAP, -1, 0);
    Etape* etape7 = new Etape(Position(2300, 1780, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape8 = new Etape(Position(250, 1750, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::GOBELET, -1, 0);
    Etape* etape9 = new Etape(Position(910, 830, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::GOBELET, -1, 0);
    Etape* etape10 = new Etape(Position(1500, 1650, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::GOBELET, -1, 0);
    Etape* etape11 = new Etape(Position(2090, 830, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::GOBELET, -1, 0);
    Etape* etape12 = new Etape(Position(2750, 1750, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::GOBELET, -1, 0);
    Etape* etape13 = new Etape(Position(90, 1750, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::RAMASSER_PIED, -1, 0);
    Etape* etape14 = new Etape(Position(90, 1850, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::RAMASSER_PIED, -1, 0);
    Etape* etape15 = new Etape(Position(90, 200, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::RAMASSER_PIED, -1, 0);
    Etape* etape16 = new Etape(Position(850, 100, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::RAMASSER_PIED, -1, 0);
    Etape* etape17 = new Etape(Position(850, 200, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::RAMASSER_PIED, -1, 0);
    Etape* etape18 = new Etape(Position(870, 1355, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::RAMASSER_PIED, -1, 0);
    Etape* etape19 = new Etape(Position(1100, 1770, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::RAMASSER_PIED, -1, 0);
    Etape* etape20 = new Etape(Position(1300, 1400, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::RAMASSER_PIED, -1, 0);
    Etape* etape21 = new Etape(Position(1250, 1800, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::AMPOULE, -1, 0);
    Etape* etape22 = new Etape(Position(1750, 1800, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::AMPOULE, -1, 0);
    Etape* etape23 = new Etape(Position(1500, 850, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape24 = new Etape(Position(2300, 1500, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape25 = new Etape(Position(2710, 1500, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::DEPOSE_GOBELET, -1, 0);
    Etape* etape26 = new Etape(Position(2630, 460, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::DEPOSE_GOBELET, -1, 0);
    Etape* etape27 = new Etape(Position(1100, 1650, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape28 = new Etape(Position(560, 1290, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape29 = new Etape(Position(720, 1600, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape30 = new Etape(Position(420, 1600, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape31 = new Etape(Position(300, 1500, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape32 = new Etape(Position(400, 430, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape33 = new Etape(Position(1110, 1130, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape34 = new Etape(Position(1480, 1150, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape35 = new Etape(Position(1850, 1160, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape36 = new Etape(Position(1950, 1530, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape37 = new Etape(Position(1890, 1365, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape38 = new Etape(Position(1000, 750, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::TAPIS, -1, 0);
    Etape* etape39 = new Etape(Position(1450, 750, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::TAPIS, -1, 0);
    /*Etape* etape40 = new Etape(Position(1450, 750, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::DEPOSE_PIED, -1, 0);
    Etape* etape41 = new Etape(Position(1450, 750, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::DEPOSE_PIED, -1, 0);
    Etape* etape42 = new Etape(Position(1450, 750, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::DEPOSE_PIED, -1, 0);*/
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

    actionClap[0]= Clap(Position(836, 1780, isYellow),Position(1000, 1780, isYellow));
    actionEtape[2]= &actionClap[0];
    actionClap[1] = Clap(Position(236, 1780, isYellow),Position(400, 1780, isYellow));
    actionEtape[4] = &actionClap[1];
    actionClap[2] = Clap(Position(2500, 1780, isYellow),Position(2300, 1780, isYellow));
    actionEtape[6] = &actionClap[2];
    actionGobelet[0] = Gobelet(Position(250, 1750, isYellow));
    actionEtape[8] = &actionGobelet[0];
    actionGobelet[1] = Gobelet(Position(910, 830, isYellow));
    actionEtape[9] = &actionGobelet[1];
    actionGobelet[2] = Gobelet(Position(1500, 1650, isYellow));
    actionEtape[10] = &actionGobelet[2];
    actionGobelet[3] = Gobelet(Position(2090, 830, isYellow));
    actionEtape[11] = &actionGobelet[3];
    actionGobelet[4] = Gobelet(Position(2750, 1750, isYellow));
    actionEtape[12] = &actionGobelet[4];
    actionTapis[0] = Tapis(Position(1000, 750, isYellow));
    actionEtape[38] = &actionTapis[0];
    actionTapis[1] = Tapis(Position(1450, 750, isYellow));
    actionEtape[39] = &actionTapis[1];
    actionDeposerGobelet[0] = DeposerGobelet(Position(700, 1000, isYellow));
    actionEtape[1] = &actionDeposerGobelet[0];
    actionDeposerGobelet[1] = DeposerGobelet(Position(2710, 1500, isYellow));
    actionEtape[25] = &actionDeposerGobelet[1];
    actionDeposerGobelet[2] = DeposerGobelet(Position(2630, 460, isYellow));
    actionEtape[26] = &actionDeposerGobelet[2];

    actionRamasserPied[0] = RamasserPied(Position(90, 1750, isYellow));
    actionEtape[13] = &actionRamasserPied[0];
    actionRamasserPied[1] = RamasserPied(Position(90, 1850, isYellow));
    actionEtape[14] = &actionRamasserPied[1];
    actionRamasserPied[2] = RamasserPied(Position(90, 200, isYellow));
    actionEtape[15] = &actionRamasserPied[2];
    actionRamasserPied[3] = RamasserPied(Position(850, 100, isYellow));
    actionEtape[16] = &actionRamasserPied[3];
    actionRamasserPied[4] = RamasserPied(Position(850, 200, isYellow));
    actionEtape[17] = &actionRamasserPied[4];
    actionRamasserPied[5] = RamasserPied(Position(870, 1355, isYellow));
    actionEtape[18] = &actionRamasserPied[5];
    actionRamasserPied[6] = RamasserPied(Position(1100, 1770, isYellow));
    actionEtape[19] = &actionRamasserPied[6];
    actionRamasserPied[7] = RamasserPied(Position(1300, 1400, isYellow));
    actionEtape[20] = &actionRamasserPied[7];

    etape0->addVoisin(etape1);
    etape1->addVoisin(etape2);
    etape1->addVoisin(etape9);
    etape1->addVoisin(etape33);
    etape33->addVoisin(etape24);
    etape18->addVoisin(etape4);
    etape2->addVoisin(etape3);
    etape3->addVoisin(etape4);
    etape2->addVoisin(etape4);
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
    etape19->addVoisin(etape27);
    etape27->addVoisin(etape21);
    etape3->addVoisin(etape27);
    etape9->addVoisin(etape33);
    etape33->addVoisin(etape20);
    etape9->addVoisin(etape18);
    etape21->addVoisin(etape22);
    etape10->addVoisin(etape22);
    etape20->addVoisin(etape10);
    etape10->addVoisin(etape35);
    etape35->addVoisin(etape11);
    etape28->addVoisin(etape31);
    etape10->addVoisin(etape6);
    etape24->addVoisin(etape6);
    etape24->addVoisin(etape7);
    etape24->addVoisin(etape12);
    etape24->addVoisin(etape25);
    etape6->addVoisin(etape12);
    etape12->addVoisin(etape25);
    etape24->addVoisin(etape11);
    etape11->addVoisin(etape20);
    etape10->addVoisin(etape11);
    etape9->addVoisin(etape11);
 //   etape11->addVoisin(etape26);
    etape9->addVoisin(etape32);
    etape32->addVoisin(etape15);
    etape9->addVoisin(etape17);
    etape16->addVoisin(etape17);
    etape16->addVoisin(etape15);
    etape15->addVoisin(etape17);
    etape23->addVoisin(etape9);
    etape23->addVoisin(etape20);
    etape23->addVoisin(etape11);
    etape18->addVoisin(etape28);
    etape18->addVoisin(etape29);
    etape29->addVoisin(etape30);
    etape29->addVoisin(etape31);
    etape30->addVoisin(etape31);
    etape30->addVoisin(etape18);
    etape30->addVoisin(etape4);
    etape28->addVoisin(etape29);
    etape28->addVoisin(etape30);
    etape28->addVoisin(etape31);
    etape33->addVoisin(etape34);
    etape34->addVoisin(etape35);
    etape35->addVoisin(etape24);
    etape35->addVoisin(etape37);
    etape37->addVoisin(etape36);
    etape36->addVoisin(etape6);
    etape36->addVoisin(etape7);
    etape23->addVoisin(etape33);
    etape23->addVoisin(etape34);
    etape23->addVoisin(etape35);
    etape11->addVoisin(etape33);
    etape11->addVoisin(etape34);
    etape23->addVoisin(etape38);
    etape23->addVoisin(etape39);
    etape9->addVoisin(etape38);
    etape38->addVoisin(etape39);
    etape39->addVoisin(etape11);
    etape5->addVoisin(etape29);

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
            return 0;
            break;
        case Etape::GOBELET :
            return 0;//ce devrait être 40
            break;
        case Etape::AMPOULE :
            return 0;
            break;
        case Etape::RAMASSER_PIED :
            return 100;//ce devrait être 20
            break;
        case Etape::TAPIS :
            return 0;
            break;
        case Etape::DEPOSE_GOBELET :
            return 0;
            break;
        case Etape::POINT_PASSAGE :
            return 0;
            break;
        default :
            return 0;
            break;
    }
}
