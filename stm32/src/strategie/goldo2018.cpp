#include "goldo2018.h"

#ifdef QTGUI
    #include <QDebug>
#endif


Goldo2018::Goldo2018(bool isYellow) : StrategieV3(isYellow)
{
    //Initialisation des tableaux d'étapes
    this->numeroEtapeGarage = ETAPE_GARAGE;
    tableauEtapesTotal = Etape::initTableauEtapeTotal(NOMBRE_ETAPES);//new Etape*[NOMBRE_ETAPES];

    // Création des étapes
    // Les étapes correspondant à des actions sont créées automatiquement lors de l'ajout d'actions

    // Initialisation in simulator in initKrabi.cpp
    int start = Etape::makeEtape(Position(200, 350, true), Etape::DEPART); // départ au fond de la zone de départ

    /** Points de passage **/
    Position p1_position = Position(600,  350, true);
    int p1 = Etape::makeEtape(p1_position);

    int p2 = Etape::makeEtape(Position(600, 1400, true));

    int p3 = Etape::makeEtape(Position(220, 1600, true));

    Etape::get(p1)->addVoisins(start);
    Etape::get(p1)->addVoisins(p2);

    // ABEILLE
    Etape::get(p3)->addVoisins(p2);
    int abeille = Etape::makeEtape(new Abeille(Position(210, 1800, true)));
    Etape::get(abeille)->addVoisins(p3);

    // Reservoir eau proche
    int reservoirProche = Etape::makeEtape(new ReservoirEau(Position(220, 840, true)));
    int pReservoirProche = Etape::makeEtape(Position(600, 840, true)); // passage associé

    Etape::get(p1)->addVoisins(pReservoirProche);
    Etape::get(pReservoirProche)->addVoisins(reservoirProche);
    Etape::get(pReservoirProche)->addVoisins(p2);

    // Navigation centrale
    int pCentrale1 = Etape::makeEtape(Position(1500, 350, true));
    int pCentrale2 = Etape::makeEtape(Position(1500, 1400, true));

    Etape::get(p1)->addVoisins(pCentrale1);
    Etape::get(pCentrale1)->addVoisins(pCentrale2);
    Etape::get(p2)->addVoisins(pCentrale2);

    // Bouton poussoir

    int bouton = Etape::makeEtape(new Abeille(Position(1130, 200, true)));
    int pBouton = Etape::makeEtape(Position(1130, 350, true));

    Etape::get(p1)-> addVoisins(pBouton);
    Etape::get(pCentrale1)-> addVoisins(pBouton);
    Etape::get(pBouton)-> addVoisins(bouton);


    /** Liens **/
    // [WIP]
//    Etape::get(p1)      ->addVoisins(start, cubedebut, p2, p4);
//    Etape::get(p3)      ->addVoisins(zc1, zc2, dune4);
//    Etape::get(p4)      ->addVoisins(cabine1, cabine2, p2);
//    Etape::get(p5)      ->addVoisins(p1,p2,p3,p4, p6);
//    Etape::get(p5)      ->addVoisins(dune1,dune2, dune4);

//    Etape::get(dune1)   ->addVoisin(p2);
//    Etape::get(dune2)   ->addVoisin(dune1);
//    Etape::get(dune3)   ->addVoisin(p5);

//    Etape::get(zc1)     ->addVoisins(dune1, dune2);
//    Etape::get(zc2)     ->addVoisins(dune1, dune2, p5);

#ifdef QTGUI
    qDebug() << Etape::getTotalEtapes();
#endif


    // Certaines actions d'étapes ne finnissent pas là où elles ont commencé :
    // Clapets:
    // Etape::get(4)->setNumeroEtapeFinAction(43); //Clapet notre côté vers notre bord


    this->nombreEtapes = Etape::getTotalEtapes();

    // Lancer Dijkstra
    startDijkstra();
}

int Goldo2018::getScoreEtape(int i)
{

    switch (this->tableauEtapesTotal[i]->getEtapeType())
    {
        /*case Etape::TYPE_ACTION:
            return NB_POINTS_ACTION; */


        // A faire : remplacer la priorite par le nombre de points obtenables a l'etape

        case Etape::DEPART :
            return 0;
        case Etape::POINT_PASSAGE :
            return 0;
        case Etape::ABEILLE :
            return 100;
        case Etape::RESERVOIR_EAU :
            return 200;


//        case Etape::ZONE_CONSTRUCTION : {
//            if (benne->getIsBenneEmpty()) {
//                return 1;
//            }
//            else {
//                return 1000;
//            }
//        }
//
//        case Etape::CABINE :
//            return 400;
//
//        case Etape::CUBE_DEBUT :
//            return 500;
//
//        case Etape::DUNE : {
//            if( benne->getIsBenneEmpty() ) {
//                return 400;
//            }
//            else {
//                return 1;
//            }
//        }

        default :
            return 1; /* DEBUG (0 sinon) */
    }
}
