#include "krabi2015.h"
#include "ascenseur.h"
#include "pinces.h"

Krabi2015::Krabi2015(bool isYellow) : StrategieV3(isYellow)
{
    #if 0
    // Initialisation des stocks

    //Initialisation des tableaux d'étapes
    this->nombreEtapes = NOMBRE_ETAPES;
    this->numeroEtapeGarage = ETAPE_GARAGE;
    tableauEtapesTotal = Etape::initTableauEtapeTotal(NOMBRE_ETAPES);//new Etape*[NOMBRE_ETAPES];
    //actionEtape = new MediumLevelAction*[NOMBRE_ETAPES];
    //actionGoto = new ActionGoTo[NOMBRE_ETAPES];


    new Etape(0, Position(250, 1000, true), Etape::DEPART); // départ au fond de la zone de départ
    // Points de passage
    // numéro étape, position

    new Etape(1, Position(700, 1000, true));
    new Etape(3, Position(320, 1203, true));
    new Etape(5, Position(1120, 1203, true));
    new Etape(7, Position(1303, 883, true));
    new Etape(8, Position(620, 700, true));
    new Etape(12, Position(747, 650, true));
    new Etape(14, Position(695, 445, true));
    new Etape(15, Position(2293, 540, true));
    new Etape(16, Position(2500, 273, true));
    new Etape(21, Position(1493, 716, true));
    new Etape(22, Position(2463, 676, true));
    new Etape(23, Position(1593, 1150, true));
    new Etape(24, Position(1896, 1156, true));
    new Etape(27, Position(1206, 1586, true));
    new Etape(28, Position(1706, 1586, true));
    new Etape(29, Position(1976, 1550, true));
    new Etape(30, Position(260, 1570, true));
    new Etape(31, Position(596, 1413, true));
    new Etape(33, Position(260, 1450, true));
    new Etape(34, Position(756, 1606, true));
    new Etape(35, Position(1116, 1600, true));
    new Etape(37, Position(2376, 1413, true));
    new Etape(38, Position(2216, 1636, true));
    new Etape(39, Position(2460, 1610, true));
    new Etape(40, Position(315, 330, true));
    new Etape(41, Position(300, 1610, true));
    new Etape(42, Position(933, 1780, true) );
    new Etape(43, Position(400, 1780, true) );
    new Etape(44, Position(2300, 1780, true) );
    new Etape(45, Position(550, 1670, true));
    new Etape(49, Position(750, 1530, true));

    // Actions
    // numéro étape, mediumLevelAction

    // Claps
    new Etape(6, new Clap(Position(2500, 1780, true), Position(2300, 1780, true)) );


    // Ramasser Gobelets
    new Etape(9, new Gobelet(Position(910, 805, true)) );
    new Etape(10, new Gobelet(Position(1500, 1650, true)) );
    new Etape(11, new Gobelet(Position(2090, 800, true)) );

    // Déposer Gobelet
    new Etape(25, new DeposerGobelet(Position(2696, 1496, true)) );
    new Etape(26, new DeposerGobelet(Position(2786, 576, true)) );
    new Etape(32, new DeposerGobelet(Position(790, 1000, true)) );
    new Etape(13, new DeposerGobelet(Position(183, 496, true)) );


    // Cabine
    new Etape(17, new Cabine(Position(480, 780, true)) );
    new Etape(36, new Tapis(Position(1420, 180, true)) );

    // Ramasser Pied
    new Etape(18, new RamasserPied(Position(870, 1355, true)) );
    new Etape(19, new RamasserPied(Position(1100, 1770, true)) );
    new Etape(20, new RamasserPied(Position(1300, 1400, true)) );

    // Ramasser Pied, version sans arriver jusqu'au point du graphe
    new Etape(46, new RamasserPied(Position(856, 210, true)) );
    new Etape(47, new RamasserPied(Position(850, 106, true)) );



    // Certaines actions d'étapes ne finnissent pas là où elles ont commencé :

    // Clapets:
    Etape::get(4)->setNumeroEtapeFinAction(43); //Clapet notre côté vers notre bord
    Etape::get(2)->setNumeroEtapeFinAction(42); //Clapet notre côté vers milieu
    Etape::get(6)->setNumeroEtapeFinAction(44); //Clapet côté adverse

    // Ramasser pieds sans aller jusqu'au point:
    Etape::get(19)->setNumeroEtapeFinAction(-1);
    Etape::get(46)->setNumeroEtapeFinAction(-1);
    Etape::get(47)->setNumeroEtapeFinAction(-1);
    Etape::get(48)->setNumeroEtapeFinAction(-1);


    // Voisins
    Etape::get(0)->addVoisin(1);
    Etape::get(17)->addVoisins(1);
    Etape::get(18)->addVoisins(5, 1);
    Etape::get(18)->addVoisins(35, 27);
    Etape::get(20)->addVoisins(5, 35 , 28);
    Etape::get(21)->addVoisins(3, 27);
    Etape::get(22)->addVoisins(27, 36);
    Etape::get(29)->addVoisins(28, 38);
    Etape::get(42)->addVoisins(1);


    // Lancer Dijkstra
    startDijkstra();
    #endif
}

int Krabi2015::getScoreEtape(int i){
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
        case Etape::GOBELET :
            if (Pinces::getSingleton()->estDispo())
                return 0;
            else
                return 0;
        case Etape::AMPOULE :
            return 0;
        case Etape::RAMASSER_PIED :
            if (Ascenseur::getSingleton()->getNbrPiedsStockes()==3)
                return 40;//STRATEGIE
//                return 0;
            else if (Ascenseur::getSingleton()->getNbrPiedsStockes()==2)
                return 30;//STRATEGIE
//                return 0;
            else if (Ascenseur::getSingleton()->getNbrPiedsStockes()==1)
                return 20;//STRATEGIE
//                return 100000;
            else
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
