#include "krabi2016.h"
#include "ascenseur.h"
#include "pinces.h"

#ifndef ROBOTHW
    #include <QDebug>
#endif


Krabi2016::Krabi2016(bool isYellow) : StrategieV3(isYellow)
{
    // Création de la benne
    benne = Benne::getInstance(); // NB: Tu pourrais utiliser getInstance partout et te passer de l'attribut

    //Initialisation des tableaux d'étapes
    this->numeroEtapeGarage = ETAPE_GARAGE;
    tableauEtapesTotal = Etape::initTableauEtapeTotal(NOMBRE_ETAPES);//new Etape*[NOMBRE_ETAPES];

    // Création des étapes
    // Les étapes correspondant à des actions sont créées automatiquement lors de l'ajout d'actions

    int start = Etape::makeEtape(Position(250, 900, true), Etape::DEPART); // départ au fond de la zone de départ

    /** Points de passage **/
    Position p1_position = Position(600,  900, true);
    int p1 = Etape::makeEtape(p1_position);

    int p2 = Etape::makeEtape(Position(680,  700, true));
    int p3 = Etape::makeEtape(Position(1000,  500, true));

    Position p4_position = Position(400,  500, true);
    int p4 = Etape::makeEtape(p4_position);

    int p5 = Etape::makeEtape(Position(950,  425, true));
    int p6 = Etape::makeEtape(Position(1400,  425, true));

    // On crée l'étape "pousse les cubes du début"
    int cubedebut = Etape::makeEtape(new CubeDebut(Position(900, 900, true), p1_position));


    /** Actions **/
    // Zone de construction
    int zc1 = Etape::makeEtape(new ZoneConstruction(Position(1050, 600, true), benne));
    int zc2 = Etape::makeEtape(new ZoneConstruction(Position(1150, 600, true), benne));


    // Dune
    int dune1 = Etape::makeEtape(new Dune(Position(1200,  280, true), benne));
    int dune2 = Etape::makeEtape(new Dune(Position(1400, 280, true), benne));
    int dune3 = Etape::makeEtape(new Dune(Position(950, 250, true), benne));
    int dune4 = Etape::makeEtape(new Dune(Position(1500, 280, true), benne));

    // Cabines de plage
    int cabine1 = Etape::makeEtape(new Cabine(Position(250, 50, true), p4_position));
    int cabine2 = Etape::makeEtape(new Cabine(Position(500, 50, true), p4_position));


    /** Liens **/
    // [WIP]
    Etape::get(start)    ->addVoisin(p1);
    Etape::get(p1)       ->addVoisin(p2);
    Etape::get(p1)       ->addVoisin(p4);
    Etape::get(cubedebut)->addVoisin(p1);

    Etape::get(p3)      ->addVoisin(zc1);
    Etape::get(p3)      ->addVoisin(zc2);
    Etape::get(p3)      ->addVoisin(dune4);

    Etape::get(cabine1)     ->addVoisin(p4);
    Etape::get(cabine2)     ->addVoisin(p4);

    Etape::get(p4)         ->addVoisin(p2);
    Etape::get(dune1)      ->addVoisin(p2);
    Etape::get(dune2)      ->addVoisin(dune1);
    Etape::get(dune3)      ->addVoisin(p5);

    Etape::get(p5)      ->addVoisin(p1);
    Etape::get(p5)      ->addVoisin(p2);
    Etape::get(p5)      ->addVoisin(p3);
    Etape::get(p5)      ->addVoisin(p4);
    Etape::get(p5)      ->addVoisin(dune1);

    Etape::get(p5)      ->addVoisin(dune2);
    Etape::get(p5)      ->addVoisin(dune4);
    Etape::get(p5)      ->addVoisin(p3);

    Etape::get(zc1)     ->addVoisin(dune1);
    Etape::get(zc1)     ->addVoisin(dune2);

    Etape::get(zc2)     ->addVoisin(dune1);
    Etape::get(zc2)     ->addVoisin(dune2);
    Etape::get(zc2)     ->addVoisin(p5);

#ifndef ROBOTHW
    qDebug() << Etape::getTotalEtapes();
#endif


    // Certaines actions d'étapes ne finnissent pas là où elles ont commencé :
    // Clapets:
    // Etape::get(4)->setNumeroEtapeFinAction(43); //Clapet notre côté vers notre bord


    this->nombreEtapes = Etape::getTotalEtapes();

    // Lancer Dijkstra
    startDijkstra();
}

int Krabi2016::getScoreEtape(int i)
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
        case Etape::ZONE_CONSTRUCTION : {
            if (benne->getIsBenneEmpty()) {
                return 1;
            }
            else {
                return 1000;
            }
        }

        case Etape::CABINE :
            return 400;

        case Etape::CUBE_DEBUT :
            return 500;

        case Etape::DUNE : {

            if( benne->getIsBenneEmpty() ) {
                return 400;
            }

            else {
                return 1;
            }
        }

        default :
            return 1; /* DEBUG (0 sinon) */
    }
}
