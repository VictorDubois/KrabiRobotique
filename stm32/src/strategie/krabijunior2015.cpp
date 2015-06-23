#include "krabijunior2015.h"


KrabiJunior2015::KrabiJunior2015(bool isYellow) : StrategieV3(isYellow)
{
    // Initialisation des stocks

    //Initialisation des tableaux d'étapes
    this->nombreEtapes = NOMBRE_ETAPES;
    this->numeroEtapeGarage = ETAPE_GARAGE;
    tableauEtapesTotal = Etape::initTableauEtapeTotal(NOMBRE_ETAPES);
    /*actionEtape = new MediumLevelAction*[NOMBRE_ETAPES];
    actionGoto = new ActionGoTo[NOMBRE_ETAPES];*/


    // Création des étapes
    // Les étapes correspondant à des actions sont créées automatiquement lors de l'ajout d'actions
    new Etape(0, Position(250, 1000, true), Etape::DEPART);            // départ au fond de la zone de départ
    // Points de passage
    // numéro étape, position
    new Etape(1, Position(600, 1000, true));
    new Etape(2, Position(700, 1000, true));
    new Etape(3, Position(1200, 1000, true));
    new Etape(4, Position(1000, 1300, true));
    new Etape(5, Position(1500, 1300, true));
    new Etape(6, Position(1800, 1200, true));
    new Etape(7, Position(1700, 800, true));
    new Etape(8, Position(1200, 800, true));
    new Etape(9, Position(1200, 600, true), Etape::TAPIS);

    // Actions
    // numéro étape, mediumLevelAction

    // Tapis
    //new Etape(9, new Tapis(Position(1200, 600)) );

    // Voisins
    Etape::get(0)->addVoisins(0, 2);

    Etape::get(2)->addVoisins(1, 3);

    Etape::get(3)->addVoisins(4, 5, 6, 7);
    Etape::get(3)->addVoisins(8);

    Etape::get(5)->addVoisins(4, 6);

    Etape::get(7)->addVoisins(6, 8);

    Etape::get(8)->addVoisins(9);


    // Lancer Dijkstra
    startDijkstra();
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

