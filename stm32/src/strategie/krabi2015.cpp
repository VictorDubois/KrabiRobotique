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
    Etape* etape0 = new Etape(Position(300, 1000, isBlue),   numeroEtape++, tableauEtapesTotal, Etape::DEPART, -1, 0);
    Etape* etape1 = new Etape(Position(836, 1700, isBlue),   numeroEtape++, tableauEtapesTotal, Etape::CLAP, -1, 0);
    Etape* etape2  = new Etape(Position(1500, 1100, isBlue), numeroEtape++, tableauEtapesTotal, Etape::CENTRE_TABLE,-1, 0);
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
            case Etape::CENTRE_TABLE :
                return 200;
                break;
            case Etape::CLAP :
                return 100;
                break;
            default :
                return 0;
                break;
    }
}
