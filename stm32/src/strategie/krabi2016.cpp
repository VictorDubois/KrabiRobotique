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
    int wa = Etape::makeEtape(Position(600,  900, true));
    int wb = Etape::makeEtape(Position(680,  700, true));
    int wc = Etape::makeEtape(Position(1000,  500, true));
    int wd = Etape::makeEtape(Position(400,  500, true));

    // On crée l'étape "pousse les cubes du début"
    int cd1 = Etape::makeEtape(new CubeDebut(Position(900, 900, true)));


    /** Actions **/
    // Zone de construction
    int zc1 = Etape::makeEtape(new ZoneConstruction(Position(1000, 600, true), benne));
    int zc2 = Etape::makeEtape(new ZoneConstruction(Position(1050, 600, true), benne));


    // Pieds
    int pa = Etape::makeEtape(new RamasserPied(Position(970,  260, true)));
    int pb = Etape::makeEtape(new RamasserPied(Position(1200, 260, true)));

    // Cabines de plage
    int cp1 = Etape::makeEtape(new Cabine(Position(250, 50, true)));
    int cp2 = Etape::makeEtape(new Cabine(Position(500, 50, true)));


    /** Liens **/
    // [WIP]
    Etape::get(start)   ->addVoisin(wa);
    Etape::get(wa)      ->addVoisin(wb, zc2);
    Etape::get(wc)      ->addVoisin(zc1);
    Etape::get(cd1)      ->addVoisin(wa);
    Etape::get(cp1)      ->addVoisin(wd);
    Etape::get(cp2)      ->addVoisin(wd);
    Etape::get(wc)      ->addVoisin(zc2);
    Etape::get(wd)      ->addVoisin(wb);
    Etape::get(pa)      ->addVoisin(wb, zc2);
    Etape::get(pb)      ->addVoisin(pa, zc2);

#ifndef ROBOTHW
    qDebug() << Etape::getTotalEtapes();
#endif


    // Certaines actions d'étapes ne finnissent pas là où elles ont commencé :
    // Clapets:
//    Etape::get(4)->setNumeroEtapeFinAction(43); //Clapet notre côté vers notre bord


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

        case Etape::CUBE_DEBUT :
            return 10000;

        case Etape::RAMASSER_PIED : {

            // On fait comme si on avait rammasé un cube, du coup la benne est pleine, en vrai on fera
            // tout ça dans la future classe cube

            benne->setBenneFull();
            return 100;
        }

        default :
            return 1; /* DEBUG (0 sinon) */
    }
}
