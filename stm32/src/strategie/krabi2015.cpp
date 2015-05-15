#include "krabi2015.h"
#include "ascenseur.h"
#include "pinces.h"

Krabi2015::Krabi2015(bool isYellow) : StrategieV3(isYellow)
{
    // Initialisation des stocks

    //Initialisation des tableaux d'étapes
    this->nombreEtapes = NOMBRE_ETAPES;
    this->numeroEtapeGarage = ETAPE_GARAGE;
    tableauEtapesTotal = Etape::initTableauEtapeTotal(NOMBRE_ETAPES);//new Etape*[NOMBRE_ETAPES];
    //actionEtape = new MediumLevelAction*[NOMBRE_ETAPES];
    //actionGoto = new ActionGoTo[NOMBRE_ETAPES];


    // Création des étapes
    // Les étapes correspondant à des actions sont créées automatiquement lors de l'ajout d'actions
    new Etape(0, Position(250, 1000, isYellow), Etape::DEPART);            // départ au fond de la zone de départ
    // Points de passage
    // numéro étape, position

    new Etape(1, COLOR_POSITION(700, 1000, isYellow));
    new Etape(3, COLOR_POSITION(880, 1140, isYellow));
    new Etape(5, COLOR_POSITION(1120, 1203, isYellow));
    new Etape(7, COLOR_POSITION(1303, 883, isYellow));
    new Etape(21, COLOR_POSITION(1493, 716, isYellow));
    new Etape(22, COLOR_POSITION(1763, 876, isYellow));
    new Etape(23, COLOR_POSITION(1593, 1150, isYellow));
    new Etape(24, COLOR_POSITION(1896, 1156, isYellow));
    new Etape(27, COLOR_POSITION(2086, 1156, isYellow));
    new Etape(28, COLOR_POSITION(1706, 1563, isYellow));
    new Etape(29, COLOR_POSITION(1976, 1550, isYellow));
    new Etape(31, COLOR_POSITION(596, 1413, isYellow));
    new Etape(34, COLOR_POSITION(756, 1606, isYellow));
    new Etape(35, COLOR_POSITION(1116, 1563, isYellow));
    new Etape(37, COLOR_POSITION(2376, 1413, isYellow));
    new Etape(38, COLOR_POSITION(2216, 1636, isYellow));
    new Etape(39, COLOR_POSITION(2460, 1610, isYellow));
    new Etape(33, COLOR_POSITION(260, 1450, isYellow));

    new Etape(21, COLOR_POSITION(1046, 1040, isYellow));

    new Etape(34, COLOR_POSITION(773, 340, isYellow));

    new Etape(8, COLOR_POSITION(620, 700, isYellow));
    new Etape(12, COLOR_POSITION(747, 650, isYellow));

    new Etape(49, COLOR_POSITION(836, 1563, isYellow));

    // Manipulation dans les coins
//    new Etape(14, new ManipulationCoinGaucheHaut(COLOR_POSITION(695, 445, isYellow), isYellow) );
//    new Etape(40, new ManipulationCoinGaucheHautPiedSolitaire(COLOR_POSITION(315, 330, isYellow), isYellow) );
//    new Etape(30, new ManipulationCoinGaucheBas( COLOR_POSITION(260, 1570, isYellow), isYellow) );
    new Etape(14, COLOR_POSITION(695, 445, isYellow));
    new Etape(40, COLOR_POSITION(315, 330, isYellow));
    new Etape(30, COLOR_POSITION(260, 1570, isYellow));

    //Si gobelets:
    new Etape(15, COLOR_POSITION(2293, 540, isYellow));
    new Etape(16, COLOR_POSITION(2500, 273, isYellow));

    //Pour pousser les objets (bourrin) du coin bas gauche avant de faire les claps
    new Etape(45, COLOR_POSITION(600, 1670, isYellow));
    //C'est provisoire: assurer les claps et bannir ces objets
    //En plus de ça on commente les voisins de l'étape 4

    // Actions
    // numéro étape, mediumLevelAction

    // Claps
    new Etape(2, new Clap(COLOR_POSITION(836, 1770, isYellow), COLOR_POSITION(933, 1770, isYellow)) );
    new Etape(4, new Clap(COLOR_POSITION(286, 1780, isYellow), COLOR_POSITION(400, 1780, isYellow)) );
    new Etape(6, new Clap(COLOR_POSITION(2460, 1780, isYellow), COLOR_POSITION(2300, 1770, isYellow)) );
    new Etape(42, COLOR_POSITION(900, 1776, isYellow) );
    new Etape(43, COLOR_POSITION(400, 1780, isYellow) );
    new Etape(44, COLOR_POSITION(2300, 1780, isYellow) );

    // Ramasser Gobelets
    new Etape(9, new Gobelet(COLOR_POSITION(910, 805, isYellow)) );
    new Etape(10, new Gobelet(COLOR_POSITION(1500, 1650, isYellow)) );
    new Etape(11, new Gobelet(COLOR_POSITION(2090, 800, isYellow)) );

    // pousser pied
    //new Etape(11, new PousserPied(COLOR_POSITION(760, 1100, isYellow)) );

    // Déposer Gobelet
    new Etape(25, new DeposerGobelet(COLOR_POSITION(2696, 1496, isYellow)) );
    new Etape(26, new DeposerGobelet(COLOR_POSITION(2786, 576, isYellow)) );
    new Etape(32, new DeposerGobelet(COLOR_POSITION(490, 1000, isYellow)) );
    new Etape(13, new DeposerGobelet(COLOR_POSITION(283, 496, isYellow)) );


    // Tapis
    new Etape(17, new Tapis(COLOR_POSITION(1070, 850, isYellow)) );
    new Etape(36, new Tapis(COLOR_POSITION(1420, 850, isYellow)) );

    // Ramasser Pied
    new Etape(18, new RamasserPied(COLOR_POSITION(870, 1355, isYellow)) );
    new Etape(19, new RamasserPied(COLOR_POSITION(1100, 1770, isYellow), true) );
    new Etape(20, new RamasserPied(COLOR_POSITION(1300, 1400, isYellow)) );
    // Ramasser Pied, version sans arriver jusqu'au point du graphe
    new Etape(46, new RamasserPied(COLOR_POSITION(856, 210, isYellow)) );
    new Etape(47, new RamasserPied(COLOR_POSITION(850, 106, isYellow)) );
    new Etape(48, new RamasserPied(COLOR_POSITION(90, 203, isYellow)) );


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

    //Deposer Pieds
    new Etape(41, new DeposerPied(COLOR_POSITION(500, 1000, isYellow), isYellow) );


    // pousser pied
//    Etape::get(2)->addVoisin(11);


    // Voisins
    Etape::get(0)->addVoisin(1, false);

    Etape::get(1)->addVoisins(3, 8, 31);
    Etape::get(1)->addVoisins(12, 21, 45);

    Etape::get(3)->addVoisins(31, 36);

//    Etape::get(4)->addVoisins(30, 33, 45, 18);
    Etape::get(4)->addVoisins(45);

    Etape::get(5)->addVoisins(23);
    //Etape::get(5)->addVoisins(35);

    Etape::get(7)->addVoisins(5, 22);
    Etape::get(7)->addVoisins(23, 3);

    Etape::get(14)->addVoisins(34);



    //Voisins des pieds
//    Etape::get(18)->addVoisins(3, 5, 1);
//    Etape::get(18)->addVoisins(31, 35, 27, 45);
//    Etape::get(19)->addVoisins(35, 42);
//    Etape::get(20)->addVoisins(5, 35, 23, 28);
//    Etape::get(20)->addVoisins(7);

//    Etape::get(46)->addVoisins(34);
//    Etape::get(47)->addVoisins(34);
//    Etape::get(48)->addVoisins(40);



    Etape::get(21)->addVoisins(3, 27);
    Etape::get(21)->addVoisins(7);
//    Etape::get(21)->addVoisins(17);

    Etape::get(22)->addVoisins(24, 27, 36);

    Etape::get(23)->addVoisins(22, 24);
    Etape::get(23)->addVoisins(3);


    Etape::get(27)->addVoisins(24, 37);

    Etape::get(29)->addVoisins(24, 28, 38);

    Etape::get(30)->addVoisins(33);

    Etape::get(31)->addVoisins(30, 33, 17);

//    Etape::get(34)->addVoisins(19, 35, 43, 45);
    //Etape::get(34)->addVoisins(2);
    //Etape::get(34)->addVoisins(30, 31, 18, 1);

//    Etape::get(36)->addVoisins(36);
    Etape::get(35)->addVoisins(28, 2);

    Etape::get(36)->addVoisins(5);

    Etape::get(37)->addVoisins(25, 38);

    Etape::get(38)->addVoisins(6, 28);

    Etape::get(39)->addVoisins(25, 37, 38, 6);


    Etape::get(40)->addVoisins(12, 13, 14);
    Etape::get(8)->addVoisins(12, 13, 14);
    Etape::get(12)->addVoisins(14);
    Etape::get(13)->addVoisins(14);
    Etape::get(15)->addVoisins(16, 26);
    Etape::get(16)->addVoisins(26);

    Etape::get(17)->addVoisins(7);
    Etape::get(36)->addVoisins(7, 17);

    Etape::get(41)->addVoisins(1);

    //aretes pour baisser les claps
    Etape::get(2)->addVoisins(42);
    Etape::get(4)->addVoisins(43);
    Etape::get(6)->addVoisins(44);
//    Etape::get(42)->addVoisins(45);
    Etape::get(43)->addVoisins(30);

    Etape::get(43)->addVoisins(2);
    Etape::get(44)->addVoisins(37);
    Etape::get(44)->addVoisins(38);

    Etape::get(45)->addVoisins(31);
    Etape::get(45)->addVoisins(35);

    Etape::get(49)->addVoisins(2, 35);

    //aretes pour coin gauche haut
    Etape::get(8)->addVoisins(40);

    //Les trajets transversaux:
    Etape::get(27)->addVoisins(1);

    //Seulement si on fait les gobelets
//    Etape::get(9)->addVoisins(3, 5, 7);
//    Etape::get(9)->addVoisins(12, 36, 1);
//    Etape::get(10)->addVoisins(20, 35, 23, 28);
//    Etape::get(11)->addVoisins(22, 24, 27, 15);
//    Etape::get(11)->addVoisins(18);



    // Lancer Dijkstra
    startDijkstra();
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
            return 1000;
//            return 1000000;
        case Etape::TAPIS :
            return 900;//STRATEGIE
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
        case Etape::DEPOSER_PIED :
            if (Ascenseur::getSingleton()->getNbrPiedsStockes()==3)
                return 10000;//STRATEGIE
//                return 0;
            else if (Ascenseur::getSingleton()->getNbrPiedsStockes()==2)
                return 5;//STRATEGIE
//                return 0;
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
