#include "krabi2016.h"
#include "ascenseur.h"
#include "pinces.h"
#include "benne.h"

#ifndef ROBOTHW
    #include <QDebug>
#endif

Benne *benne = new Benne();

Krabi2016::Krabi2016(bool isYellow) : StrategieV3(isYellow)
{
    //Initialisation des tableaux d'étapes
    this->numeroEtapeGarage = ETAPE_GARAGE;
    tableauEtapesTotal = Etape::initTableauEtapeTotal(NOMBRE_ETAPES);//new Etape*[NOMBRE_ETAPES];


    // Création des étapes
    // Les étapes correspondant à des actions sont créées automatiquement lors de l'ajout d'actions

    int start = Etape::makeEtape(Position(250, 1000, true), Etape::DEPART); // départ au fond de la zone de départ



    /** Points de passage **/
    int wa = Etape::makeEtape(Position(600,  1000, true));
    int wb = Etape::makeEtape(Position(880,  1140, true));
    int wc = Etape::makeEtape(Position(1120, 1203, true));

    /** Actions **/
    // Zone de construction
    int zc1 = Etape::makeEtape(new ZoneConstruction(Position(650, 450, true)));


    // Pieds
    int pa = Etape::makeEtape(new RamasserPied(Position(870,    1755, true)));
    int pb = Etape::makeEtape(new RamasserPied(Position(1100,   1770, true)));

    // Etc.


    /** Liens **/
    // [WIP]
    Etape::get(start)   ->addVoisin(wa);
    Etape::get(wa)      ->addVoisin(wb, wc);
    Etape::get(wa)      ->addVoisin(zc1);
    Etape::get(wb)      ->addVoisin(wc);
    Etape::get(pa)      ->addVoisin(wb, wc);
    Etape::get(pb)      ->addVoisin(pa, wc);

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
        case Etape::ZONE_CONSTRUCTION :
            if (benne->getIsBenneEmpty()) {
                return 0;
            }
            else {
                return 100;
            }

        case Etape::RAMASSER_PIED : {

            benne->setIsBenneFull();
            return 10;

        }

        default :
            return 10; /* DEBUG (0 sinon) */
    }
}
