#include "krabi2016.h"
#include "ascenseur.h"
#include "pinces.h"

#ifndef ROBOTHW
    #include <QDebug>
#endif

Krabi2016::Krabi2016(bool isYellow) : StrategieV3(isYellow)
{
    //Initialisation des tableaux d'étapes
    this->numeroEtapeGarage = ETAPE_GARAGE;
    tableauEtapesTotal = Etape::initTableauEtapeTotal(NOMBRE_ETAPES);//new Etape*[NOMBRE_ETAPES];
    //actionEtape = new MediumLevelAction*[NOMBRE_ETAPES];
    //actionGoto = new ActionGoTo[NOMBRE_ETAPES];


    // Création des étapes
    // Les étapes correspondant à des actions sont créées automatiquement lors de l'ajout d'actions

    int start = Etape::makeEtape(Position(250, 1000, true), Etape::DEPART); // départ au fond de la zone de départ


    /** Points de passage **/
    int wa = Etape::makeEtape(Position(700,  1000, true));
    int wb = Etape::makeEtape(Position(880,  1140, true));
    int wc = Etape::makeEtape(Position(1120, 1203, true));

    /** Actions **/
    // Gobelets
    int ga = Etape::makeEtape(new Gobelet(Position(910,  805,    true)));
    int gb = Etape::makeEtape(new Gobelet(Position(1500, 1650,   true)));
    int gc = Etape::makeEtape(new Gobelet(Position(2090, 800,    true)));

    // Pieds
    int pa = Etape::makeEtape(new RamasserPied(Position(870,    1355, true)));
    int pb = Etape::makeEtape(new RamasserPied(Position(1100,   1770, true)));

    // Etc.


    /** Liens **/
    // [WIP]
    Etape::get(start)   ->addVoisin(wa);
    Etape::get(wa)      ->addVoisin(wb, wc);
    Etape::get(wb)      ->addVoisin(wc);
    Etape::get(ga)      ->addVoisin(wb, gb);
    Etape::get(gb)      ->addVoisin(wc);
    Etape::get(gc)      ->addVoisin(wc);
    Etape::get(pa)      ->addVoisin(wb, wc);
    Etape::get(pb)      ->addVoisin(pa, wc);

#ifndef ROBOTHW
    qDebug() << Etape::getTotalEtapes();
#endif


    // Certaines actions d'étapes ne finnissent pas là où elles ont commencé :
    // Clapets:
//    Etape::get(4)->setNumeroEtapeFinAction(43); //Clapet notre côté vers notre bord


    // Voisins
/*    Etape::get(0)->addVoisin(1, false);

    Etape::get(1)->addVoisins(3, 8, 31);
    Etape::get(1)->addVoisins(12, 21, 45); */


    this->nombreEtapes = Etape::getTotalEtapes();

    // Lancer Dijkstra
    startDijkstra();
}

int Krabi2016::getScoreEtape(int i){
    /* TODO : Supprimer le modificateur temporel et inclure directement un coefficient dans le score pour les actions longues
       Plus tard : pourquoi pas changer le système en ayant les FEU etc... fils de Etape, ça éviterait aussi le switch dans updateStock().
       Juste faire attention à comment transmettre le stock à update.
     */
    switch (this->tableauEtapesTotal[i]->getEtapeType())
    {
        case Etape::DEPART :
            return 0;
        case Etape::CLAP :
            return 10;
//            return 1000000;
        case Etape::TAPIS :
            return 1000;//STRATEGIE
//            return 0;

        case Etape::CABINE :
            return 0;//STRATEGIE

        case Etape::AMPOULE :
            return 0;

        case Etape::DEPOSER_GOBELET :
            /*if (!Pinces::getSingleton()->getEstDispo())
                return 40;
            else*/
                return 0;
        case Etape::COIN_GAUCHE_HAUT :
            return 0;
        case Etape::SPOT_SOLITAIRE_COIN :
            return 0;
        case Etape::COIN_GAUCHE_BAS :
            return 0;
        case Etape::POINT_PASSAGE :
            return 0;
        default :
            return 0;
    }
}
