#include "krabijunior2015.h"


KrabiJunior2015::KrabiJunior2015(bool isBlue) : StrategieV3(isBlue)
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
    Etape* etape1 = new Etape(Position(600, 1000, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape2 = new Etape(Position(700, 1000, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape3 = new Etape(Position(1200, 1000, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape4 = new Etape(Position(1000, 1300, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape5 = new Etape(Position(1500, 1300, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape6 = new Etape(Position(1800, 1200, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape7 = new Etape(Position(1700, 800, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape9 = new Etape(Position(1200, 600, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::TAPIS, -1, 0);
    Etape* etape8 = new Etape(Position(1200, 800, isYellow),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);

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

    //J ai modifié NOMBRE_ETAPES dans krabijunior2015.h et le etape.h



    //Initialisation des actions par défaut
    for(int i = 0 ; i < NOMBRE_ETAPES ; i++)
    {
        if (tableauEtapesTotal[i]->getState() == -1)
        {
            actionGoto[i] = ActionGoTo(tableauEtapesTotal[i]->getPosition());
            actionEtape[i] = &actionGoto[i];
        }

    }





    // Lancer Dijkstra
    startDijkstra();
}

void KrabiJunior2015::updateStock(){
    switch(this->tableauEtapes[this->etapeEnCours]->getEtapeType()){
        case Etape::DEPART :
             this->tableauEtapes[this->etapeEnCours]->setEtapeType(Etape::POINT_PASSAGE);
            break;
        default :
            this->tableauEtapes[this->etapeEnCours]->setEtapeType(Etape::POINT_PASSAGE);
    }
}

int KrabiJunior2015::getScoreEtape(int i){
    /* TODO : Supprimer le modificateur temporel et inclure directement un coefficient dans le score pour les actions longues
    Plus tard : pourquoi pas changer le système en ayant les FEU etc... fils de Etape, ça éviterait aussi le switch dans updateStock().
    Juste faire attention à comment transmettre le stock à update.
    */
    switch (this->tableauEtapesTotal[i]->getEtapeType()){
            case Etape::DEPART :
                return 10;
                break;
            case Etape::TAPIS :
                return 10;
                break;
            default :
                return 0;
                break;
    }
}

