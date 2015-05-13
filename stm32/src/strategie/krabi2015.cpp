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

    new Etape(1, Position(700, 1000, isYellow));
    new Etape(3, Position(880, 1140, isYellow));
    new Etape(5, Position(1120, 1203, isYellow));
    new Etape(7, Position(1303, 883, isYellow));
    new Etape(21, Position(1493, 716, isYellow));
    new Etape(22, Position(1763, 876, isYellow));
    new Etape(23, Position(1593, 1150, isYellow));
    new Etape(24, Position(1896, 1156, isYellow));
    new Etape(27, Position(2086, 1156, isYellow));
    new Etape(28, Position(1706, 1586, isYellow));
    new Etape(29, Position(1976, 1550, isYellow));
    new Etape(31, Position(596, 1413, isYellow));
    new Etape(33, Position(260, 1450, isYellow));
    new Etape(34, Position(756, 1606, isYellow));
    new Etape(35, Position(1070, 1543, isYellow));
    new Etape(37, Position(2376, 1413, isYellow));
    new Etape(38, Position(2216, 1636, isYellow));
    new Etape(39, Position(2460, 1610, isYellow));

    new Etape(8, Position(620, 700, isYellow));
    new Etape(12, Position(747, 650, isYellow));
    new Etape(13, Position(283, 496, isYellow));
    new Etape(14, Position(421, 283, isYellow));
    //Si gobelets:
    new Etape(15, Position(2293, 540, isYellow));
    new Etape(16, Position(2500, 273, isYellow));

    // Actions
    // numéro étape, mediumLevelAction

    // Claps
    new Etape(2, new Clap(Position(836, 1780, isYellow), Position(1000, 1780, isYellow)) );
    new Etape(4, new Clap(Position(236, 1780, isYellow), Position(400, 1780, isYellow)) );
    new Etape(6, new Clap(Position(2500, 1780, isYellow), Position(2300, 1780, isYellow)) );

    // Certaines actions d'étapes ne finnissent pas là où elles ont commencé :
    Etape::get(2)->setNumeroEtapeFinAction(3); //Clapet notre côté vers milieu
    Etape::get(4)->setNumeroEtapeFinAction(5); //Clapet notre côté vers notre bord
    Etape::get(6)->setNumeroEtapeFinAction(7); //Clapet côté adverse

    // Ramasser Gobelets
    new Etape(9, new Gobelet(Position(910, 805, isYellow)) );
    new Etape(10, new Gobelet(Position(1500, 1650, isYellow)) );
    new Etape(11, new Gobelet(Position(2090, 800, isYellow)) );

    // Déposer Gobelet
    new Etape(25, new DeposerGobelet(Position(2696, 1496, isYellow)) );
    new Etape(26, new DeposerGobelet(Position(2786, 576, isYellow)) );
    new Etape(32, new DeposerGobelet(Position(490, 1000, isYellow)) );


    // Tapis
    new Etape(17, new Tapis(Position(1366, 780, isYellow)) );
    new Etape(36, new Tapis(Position(1126, 780, isYellow)) );

    // Ramasser Pied
    new Etape(18, new RamasserPied(Position(870, 1355, isYellow)) );
    new Etape(19, new RamasserPied(Position(1100, 1770, isYellow)) );
    new Etape(20, new RamasserPied(Position(1300, 1400, isYellow)) );

    //Deposer Pieds
    new Etape(41, new DeposerPied(Position(500, 1000, isYellow), isYellow) );

    // Manipulation dans les coins
    new Etape(30, Position(420, 1600, isYellow));
    new Etape(40, Position(695, 445, isYellow));

    // Voisins
    Etape::get(0)->addVoisin(1, false);

    Etape::get(1)->addVoisins(3, 8, 9, 31);
    Etape::get(1)->addVoisins(12);


    Etape::get(2)->addVoisins(3, 4);

    Etape::get(4)->addVoisins(30, 33, 34);

    Etape::get(5)->addVoisins(23);

    Etape::get(7)->addVoisins(5, 21, 22);
    Etape::get(7)->addVoisins(20, 23, 3);

    Etape::get(9)->addVoisins(3, 5, 7);
    Etape::get(9)->addVoisins(12);

    Etape::get(10)->addVoisins(20, 35);

    Etape::get(11)->addVoisins(22, 24, 27, 15);

//    Etape::get(12)->addVoisins(12);

//    Etape::get(15)->addVoisins(15);

//    Etape::get(16)->addVoisins(16);
//    Etape::get(17)->addVoisins(17);

    Etape::get(18)->addVoisins(3, 5);
    Etape::get(18)->addVoisins(31, 34, 35);

    Etape::get(19)->addVoisins(35);

    Etape::get(20)->addVoisins(5, 35);

    Etape::get(21)->addVoisins(22);

    Etape::get(23)->addVoisins(10, 20, 22, 24);


    Etape::get(27)->addVoisins(24, 37);

    Etape::get(28)->addVoisins(10, 20);

    Etape::get(29)->addVoisins(24, 28, 38);

    Etape::get(30)->addVoisins(33, 34);

    Etape::get(31)->addVoisins(30, 33, 34);

    Etape::get(34)->addVoisins(2, 19, 35);

//    Etape::get(36)->addVoisins(36);

    Etape::get(37)->addVoisins(25, 38);

    Etape::get(39)->addVoisins(25, 37, 38, 6);


    Etape::get(40)->addVoisins(12, 13, 14);
    Etape::get(8)->addVoisins(12, 13, 14);
    Etape::get(12)->addVoisins(14);
    Etape::get(13)->addVoisins(14);
    Etape::get(15)->addVoisins(16, 26);
    Etape::get(16)->addVoisins(26);

    Etape::get(17)->addVoisins(7, 21);
    Etape::get(36)->addVoisins(9, 7, 17);

    Etape::get(41)->addVoisin(1);

    //Les trajets transversaux:
    Etape::get(27)->addVoisins(1, 18);
    Etape::get(11)->addVoisins(18);


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
            return 1;
        case Etape::GOBELET :
            if (Pinces::getSingleton()->estDispo())
                return 0;
            else
                return 0;
        case Etape::AMPOULE :
            return 0;
        case Etape::RAMASSER_PIED :
            if (Ascenseur::getSingleton()->getNbrPiedsStockes()==1)
                return 0;
            else
                return 100;
        case Etape::DEPOSER_PIED :
            if (Ascenseur::getSingleton()->getNbrPiedsStockes()==1)
                return 100;
            else
                return 0;
        case Etape::TAPIS :
            return 0;
        case Etape::DEPOSER_GOBELET :
            /*if (!Pinces::getSingleton()->getEstDispo())
                return 40;
            else*/
                return 0;
        case Etape::POINT_PASSAGE :
            return 0;
        default :
            return 0;
    }
}
