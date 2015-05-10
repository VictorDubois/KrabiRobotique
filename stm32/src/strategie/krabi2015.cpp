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
    new Etape(3, Position(1000, 1780, isYellow));
    new Etape(5, Position(400, 1780, isYellow));
    new Etape(7, Position(2300, 1780, isYellow));
    new Etape(21, Position(1250, 1800, isYellow), Etape::AMPOULE);
    new Etape(22, Position(1750, 1800, isYellow), Etape::AMPOULE);
    new Etape(23, Position(1500, 850, isYellow));
    new Etape(24, Position(2300, 1500, isYellow));
    new Etape(27, Position(1100, 1650, isYellow));
    new Etape(28, Position(560, 1290, isYellow));
    new Etape(29, Position(720, 1600, isYellow));
    new Etape(30, Position(420, 1600, isYellow));
    new Etape(31, Position(300, 1500, isYellow));
    new Etape(32, Position(400, 430, isYellow));
    new Etape(33, Position(1110, 1130, isYellow));
    new Etape(34, Position(1480, 1150, isYellow));
    new Etape(35, Position(1850, 1160, isYellow));
    new Etape(36, Position(1950, 1530, isYellow));
    new Etape(37, Position(1890, 1365, isYellow));
    /*new Etape(Position(1450, 750, isYellow), Etape::DEPOSE_PIED);
    new Etape(Position(1450, 750, isYellow), Etape::DEPOSE_PIED);
    new Etape(Position(1450, 750, isYellow), Etape::DEPOSE_PIED);*/

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
    new Etape(8, new Gobelet(Position(250, 1750, isYellow)) );
    new Etape(9, new Gobelet(Position(910, 830, isYellow)) );
    new Etape(10, new Gobelet(Position(1500, 1650, isYellow)) );
    new Etape(11, new Gobelet(Position(2090, 830, isYellow)) );
    new Etape(12, new Gobelet(Position(2750, 1750, isYellow)) );

    // Déposer Gobelet
    new Etape(1, new DeposerGobelet(Position(700, 1000, isYellow)) );
    new Etape(25, new DeposerGobelet(Position(2710, 1500, isYellow)) );
    new Etape(26, new DeposerGobelet(Position(2630, 460, isYellow)) );

    // Tapis
    new Etape(38, new Tapis(Position(1000, 850, isYellow)) );
    new Etape(39, new Tapis(Position(1450, 850, isYellow)) );

    // Ramasser Pied
    new Etape(13, new RamasserPied(Position(90, 1750, isYellow)) );
    new Etape(14, new RamasserPied(Position(90, 1850, isYellow)) );
    new Etape(15, new RamasserPied(Position(90, 200, isYellow)) );
    new Etape(16, new RamasserPied(Position(850, 100, isYellow)) );
    new Etape(17, new RamasserPied(Position(850, 200, isYellow)) );
    new Etape(18, new RamasserPied(Position(870, 1355, isYellow)) );
    new Etape(19, new RamasserPied(Position(1100, 1770, isYellow)) );
    new Etape(20, new RamasserPied(Position(1300, 1400, isYellow)) );

    // Voisins
    Etape::get(0)->addVoisin(1, false);

    Etape::get(1)->addVoisins(2, 9, 18, 33);

    Etape::get(2)->addVoisins(3, 4);

    Etape::get(4)->addVoisins(3, 5, 8, 13);

    Etape::get(6)->addVoisins(7, 10, 12, 24);

    Etape::get(9)->addVoisins(17, 32, 38);

    Etape::get(10)->addVoisins(11, 20, 22, 35);

    Etape::get(11)->addVoisins(9, 20, 24, 33);
    Etape::get(11)->addVoisins(34, 35, 39); //26

    Etape::get(12)->addVoisins(25);

    Etape::get(14)->addVoisins(8, 13);

    Etape::get(15)->addVoisins(17, 32);

    Etape::get(16)->addVoisins(15, 17);

    Etape::get(18)->addVoisins(2, 4, 9, 19);
    Etape::get(18)->addVoisins(20, 28, 29);

    Etape::get(21)->addVoisins(22);

    Etape::get(23)->addVoisins(9, 11, 20, 33);
    Etape::get(23)->addVoisins(34, 35, 38, 39);

    Etape::get(24)->addVoisins(7, 12, 25);

    Etape::get(27)->addVoisins(3, 19, 21);

    Etape::get(28)->addVoisins(29, 30, 31);

    Etape::get(29)->addVoisins(5, 31);

    Etape::get(30)->addVoisins(4, 18, 29, 31);

    Etape::get(33)->addVoisins(9, 20, 24, 34);

    Etape::get(35)->addVoisins(24, 37);

    Etape::get(36)->addVoisins(6, 7, 34, 37);

    Etape::get(38)->addVoisins(39);


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
            if (Pinces::getSingleton()->getEstDispo())
                return 40;
            else
                return 0;
        case Etape::AMPOULE :
            return 0;
        case Etape::RAMASSER_PIED :
            if (Ascenseur::getSingleton()->getNbrPiedsStockes()==3)
                return 0;
            else
                return 100;
        case Etape::TAPIS :
            return 500;
        case Etape::DEPOSE_GOBELET :
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
