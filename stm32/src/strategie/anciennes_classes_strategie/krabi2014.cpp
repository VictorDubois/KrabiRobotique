#include "krabi2014.h"

Krabi2014::Krabi2014(bool isBlue) : StrategieV3(isBlue)
{
    // Initialisation des stocks
    this->nombreFruitsTransporte = 0;
    this->nombreFeuxTransporte = 0;
    this->nombreFresquesTransporte = 2;
    this->nombreLancesTransporte = 6;

    //Initialisation des tableaux d'étapes
    this->nombreEtapes = NOMBRE_ETAPES;
    tableauEtapesTotal = new Etape*[NOMBRE_ETAPES];
    actionEtape = new MediumLevelAction*[NOMBRE_ETAPES];
    actionGoto = new ActionGoTo[NOMBRE_ETAPES];
    // TODO: A supprimer pour une variable statique dans Etape
    int numeroEtape = 0;

    // Création des étapes
    //arguments : Position, tableau des etapes liées, nombre d'étapes liées, numéro de l'étape, type d'étape, état de l'étape, nombreEtapesLieesParFinirEtape
    Etape* etape0 = new Etape(Position(200, 1850, isBlue),         numeroEtape++, tableauEtapesTotal, Etape::DEPART, -1, 0);
    Etape* etape1 = new Etape(Position(200, 1500, isBlue),         numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE,-1, 0);
    Etape* etape2  = new Etape(Position(500, 1400, isBlue),        numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE,-1, 0); //cette étape krabi baisse le bras
    Etape* etape3  = new Etape(Position(790, 1200, isBlue),        numeroEtape++, tableauEtapesTotal, Etape::FEU_MINI_BRAS,-1, 0); //cette étape krabi ramasse le feu et le garde
    Etape* etape4  = new Etape(Position(750, 1200, isBlue),        numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE,-1, 0);
    Etape* etape5  = new Etape(Position(1050, 1300, isBlue),       numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE,-1, 0);
    Etape* etape6  = new Etape(Position(1050, 800, isBlue),        numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE,-1, 0);
    Etape* etape7  = new Etape(Position(1500, 450, isBlue),        numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE,-1, 0);
    Etape* etape8  = new Etape(Position(670, 680, isBlue),         numeroEtape++, tableauEtapesTotal, Etape::TORCHE_MOBILE,-1, 0);
    Etape* etape9  = new Etape(Position(1900, 1300, isBlue),       numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE,-1, 0);
    Etape* etape10 = new Etape(Position(1300, 1400, isBlue),       numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE,-1, 0);
    Etape* etape11 = new Etape(Position(1500, 1450, isBlue),       numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE,-1, 0);
    Etape* etape12 = new Etape(Position(1700, 1400, isBlue),       numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE,-1, 0); // idem que etape3 mais la suivante est etape17
    Etape* etape13 = new Etape(Position(1320, 1700, isBlue),       numeroEtape++, tableauEtapesTotal, Etape::FRESQUE, -1, 2); //les 3 FRESQUE sont liées
    Etape* etape14 = new Etape(Position(1500, 1700, isBlue),       numeroEtape++, tableauEtapesTotal, Etape::FRESQUE, -1, 2);
    Etape* etape15 = new Etape(Position(1680, 1700, isBlue),       numeroEtape++, tableauEtapesTotal, Etape::FRESQUE, -1, 2);
    Etape* etape16 = new Etape(Position(1850, 1400, isBlue),       numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0); //idem que etape4
    Etape* etape17 = new Etape(Position(2250, 1400, isBlue),       numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape18 = new Etape(Position(600, 1100, isBlue),        numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape19 = new Etape(Position(590, 1060, isBlue),        numeroEtape++, tableauEtapesTotal, Etape::FEU_MINI_BRAS, -1, 0);
    Etape* etape20 = new Etape(Position(700, 700, isBlue),         numeroEtape++, tableauEtapesTotal, Etape::TIR_MAMMOUTH, -1, 0);
    Etape* etape21 = new Etape(Position(3000 - 1130, 680, isBlue), numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape22 = new Etape(Position(2350, 650, isBlue),        numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape23 = new Etape(Position(3000 - 640, 1350, isBlue), numeroEtape++, tableauEtapesTotal, Etape::TIR_MAMMOUTH, -1, 0);
    Etape* etape24 = new Etape(Position(2300, 1200, isBlue),       numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape25 = new Etape(Position(660, 1210, isBlue),        numeroEtape++, tableauEtapesTotal, Etape::TIR_FILET, -1, 0);
    Etape* etape26 = new Etape(Position(3000 - 660, 1210, isBlue), numeroEtape++, tableauEtapesTotal, Etape::TIR_FILET, -1, 0);
    Etape* etape27 = new Etape(Position(400, 1200, isBlue),        numeroEtape++, tableauEtapesTotal, Etape::FEU_COTE, -1, 0);
    Etape* etape28 = new Etape(Position(1300, 400, isBlue),        numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
    Etape* etape29 = new Etape(Position(1700, 400, isBlue),        numeroEtape++, tableauEtapesTotal, Etape::FEU_COTE, -1, 0);
    Etape* etape30 = new Etape(Position(2600, 1200, isBlue),       numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);

    //Initialisation des actions par défaut
    for(int i = 0 ; i < NOMBRE_ETAPES ; i++)
    {
        actionGoto[i] = ActionGoTo(tableauEtapesTotal[i]->getPosition(), false);
        actionEtape[i] = &actionGoto[i];
    }

    actionFresque[0] = Fresque(isBlue, Position(1320, 1700, isBlue), Position(1320, 1500, isBlue));//1400 - 1750
    actionFresque[1] = Fresque(isBlue, Position(1500, 1700, isBlue), Position(1320, 1500, isBlue));
    actionFresque[2] = Fresque(isBlue, Position(1680, 1700, isBlue), Position(1320, 1500, isBlue));

    actionFeuKrabi[0] = FeuKrabi(isBlue, Position(500, 1400, isBlue), Position(9000, 1400, isBlue));
    actionFeuKrabi[1] = FeuKrabi(isBlue, Position(1700, 1400, isBlue), Position(2100, 1400, isBlue));

    actionFeuKrabiLateral[0] = FeuKrabiLateral(isBlue, Position(590, 1060, isBlue), DEGTORAD(15.) - M_PI/2, FeuKrabiLateral::RIGHT);
    actionFeuKrabiLateral[1] = FeuKrabiLateral(isBlue, Position(700, 290, isBlue), DEGTORAD(25.) + M_PI/2, FeuKrabiLateral::RIGHT);
    actionFeuKrabiLateral[2] = FeuKrabiLateral(isBlue, Position(790, 1200, isBlue), DEGTORAD(0.), FeuKrabiLateral::LEFT);

    actionFiletKrabi[0] = TireFilet(isBlue, Position(660, 1300, isBlue), true);
    actionFiletKrabi[1] = TireFilet(isBlue, Position(3000 - 660, 1300, isBlue), false);

    actionLancesKrabi[0] = TireLances(isBlue, Position(700, 700, isBlue), true, 6);
    actionLancesKrabi[1] = TireLances(isBlue, Position(3000 - 640, 1350, isBlue), false, 0);

    actionFeuCoteKrabi[0] = FeuCoteKrabi(isBlue, Position(400, 1200, isBlue), 0);
    actionFeuCoteKrabi[1] = FeuCoteKrabi(isBlue, Position(1300, 400, isBlue), 1);
    actionFeuCoteKrabi[2] = FeuCoteKrabi(isBlue, Position(1700, 400, isBlue), 2);
    actionFeuCoteKrabi[3] = FeuCoteKrabi(isBlue, Position(2600, 1200, isBlue), 3);

    actionTorcheMobile[0] = TorcheMobile(isBlue, Position(670, 680, isBlue), Position(900, 900, isBlue));
    actionTorcheMobile[0] = TorcheMobile(isBlue, Position(3000 - 1130, 680, isBlue), Position(3000 - 900, 900, isBlue));

    actionEtape[3] = &actionFeuKrabiLateral[2];//&actionGoto[3];
    actionEtape[8] = &actionTorcheMobile[0];//&actionGoto[8];//&actionGoto[8];
    actionEtape[13] = &actionFresque[0];//&actionGoto[13];
    actionEtape[14] = &actionFresque[1];//&actionGoto[14];
    actionEtape[15] = &actionFresque[2];//&actionGoto[15];
    actionEtape[19] = &actionFeuKrabiLateral[0];//&actionGoto[19];
    actionEtape[20] = &actionLancesKrabi[0];
    actionEtape[21] = &actionTorcheMobile[1];
    actionEtape[23] = &actionLancesKrabi[1];
    actionEtape[25] = &actionFiletKrabi[0];
    actionEtape[26] = &actionFiletKrabi[1];
    actionEtape[27] = &actionFeuCoteKrabi[0];
    actionEtape[28] = &actionFeuCoteKrabi[1];
    actionEtape[29] = &actionFeuCoteKrabi[2];
    actionEtape[30] = &actionFeuCoteKrabi[3];

    etape0->addVoisin(etape1, false);

    etape1->addVoisin(etape2, false);
    etape1->addVoisin(etape27);

    etape2->addVoisin(etape3);
    etape2->addVoisin(etape4);
    etape2->addVoisin(etape18);
    etape2->addVoisin(etape25);
    etape2->addVoisin(etape27);

    etape3->addVoisin(etape4);
    etape3->addVoisin(etape5);
    etape3->addVoisin(etape10);
    etape3->addVoisin(etape18);
    etape3->addVoisin(etape25);

    etape4->addVoisin(etape5);
    etape4->addVoisin(etape18);
    etape4->addVoisin(etape25);
    etape4->addVoisin(etape27);

    etape5->addVoisin(etape6);
    etape5->addVoisin(etape10);
    etape5->addVoisin(etape11);

    etape6->addVoisin(etape7);
    etape6->addVoisin(etape20);
    etape6->addVoisin(etape28);

    etape7->addVoisin(etape20);
    etape7->addVoisin(etape21);
    etape7->addVoisin(etape28);
    etape7->addVoisin(etape29);

    etape8->addVoisin(etape19);
    etape8->addVoisin(etape20);
    etape8->addVoisin(etape28);

    etape9->addVoisin(etape11);
    etape9->addVoisin(etape12);
    etape9->addVoisin(etape16);
    etape9->addVoisin(etape24);

    etape10->addVoisin(etape11);
    etape10->addVoisin(etape13);

    etape11->addVoisin(etape12);
    etape11->addVoisin(etape14);

    etape12->addVoisin(etape15);
    etape12->addVoisin(etape16);

    etape16->addVoisin(etape17);

    etape17->addVoisin(etape24);
    etape17->addVoisin(etape26);
    etape17->addVoisin(etape30);

    etape18->addVoisin(etape19);
    etape18->addVoisin(etape25);
    etape18->addVoisin(etape27);

    etape19->addVoisin(etape20);
    etape19->addVoisin(etape25);
    etape19->addVoisin(etape27);

    etape20->addVoisin(etape28);

    etape21->addVoisin(etape22);
    etape21->addVoisin(etape29);

    etape22->addVoisin(etape23);

    etape23->addVoisin(etape24);
    etape23->addVoisin(etape26);
    etape23->addVoisin(etape30);

    etape24->addVoisin(etape26);
    etape24->addVoisin(etape30);

    etape28->addVoisin(etape29);


    // Lancer Dijkstra
    startDijkstra();


    //liaison des étapes de la fresque
    int* tableauEtapesLieesParFinirEtape13 = new int[2];
    tableauEtapesLieesParFinirEtape13[0] = 14;
    tableauEtapesLieesParFinirEtape13[1] = 15;
    this->tableauEtapes[13]->setEtapesLieesParFinirEtape(tableauEtapesLieesParFinirEtape13);

    int* tableauEtapesLieesParFinirEtape14 = new int[2];
    tableauEtapesLieesParFinirEtape14[0] = 13;
    tableauEtapesLieesParFinirEtape14[1] = 15;
    this->tableauEtapes[14]->setEtapesLieesParFinirEtape(tableauEtapesLieesParFinirEtape14);

    int* tableauEtapesLieesParFinirEtape15 = new int[2];
    tableauEtapesLieesParFinirEtape15[0] = 13;
    tableauEtapesLieesParFinirEtape15[1] = 14;
    this->tableauEtapes[15]->setEtapesLieesParFinirEtape(tableauEtapesLieesParFinirEtape15);

    /*
    // Tableaux générés par le générateur de distance dans startDijkstra()

    int* tableauDistances0 = new int[1];
    tableauDistances0[0] = 350; // vers etape 1
    this->tableauEtapes[0]->setDistances(tableauDistances0);

    int* tableauDistances1 = new int[1];
    tableauDistances1[0] = 316; // vers etape 2
    this->tableauEtapes[1]->setDistances(tableauDistances1);

    int* tableauDistances2 = new int[4];
    tableauDistances2[0] = 150; // vers etape 3
    tableauDistances2[1] = 320; // vers etape 4
    tableauDistances2[2] = 141; // vers etape 18
    tableauDistances2[3] = 248; // vers etape 25
    this->tableauEtapes[2]->setDistances(tableauDistances2);

    int* tableauDistances3 = new int[6];
    tableauDistances3[0] = 150; // vers etape 2
    tableauDistances3[1] = 223; // vers etape 4
    tableauDistances3[2] = 583; // vers etape 5
    tableauDistances3[3] = 650; // vers etape 10
    tableauDistances3[4] = 111; // vers etape 18
    tableauDistances3[5] = 190; // vers etape 25
    this->tableauEtapes[3]->setDistances(tableauDistances3);

    int* tableauDistances4 = new int[5];
    tableauDistances4[0] = 320; // vers etape 2
    tableauDistances4[1] = 223; // vers etape 3
    tableauDistances4[2] = 412; // vers etape 5
    tableauDistances4[3] = 180; // vers etape 18
    tableauDistances4[4] = 90; // vers etape 25
    this->tableauEtapes[4]->setDistances(tableauDistances4);

    int* tableauDistances5 = new int[5];
    tableauDistances5[0] = 583; // vers etape 3
    tableauDistances5[1] = 412; // vers etape 4
    tableauDistances5[2] = 300; // vers etape 6
    tableauDistances5[3] = 335; // vers etape 10
    tableauDistances5[4] = 460; // vers etape 11
    this->tableauEtapes[5]->setDistances(tableauDistances5);

    int* tableauDistances6 = new int[3];
    tableauDistances6[0] = 300; // vers etape 5
    tableauDistances6[1] = 460; // vers etape 7
    tableauDistances6[2] = 353; // vers etape 20
    this->tableauEtapes[6]->setDistances(tableauDistances6);

    int* tableauDistances7 = new int[4];
    tableauDistances7[0] = 460; // vers etape 6
    tableauDistances7[1] = 460; // vers etape 8
    tableauDistances7[2] = 602; // vers etape 20
    tableauDistances7[3] = 602; // vers etape 21
    this->tableauEtapes[7]->setDistances(tableauDistances7);

    int* tableauDistances8 = new int[3];
    tableauDistances8[0] = 460; // vers etape 7
    tableauDistances8[1] = 300; // vers etape 9
    tableauDistances8[2] = 353; // vers etape 21
    this->tableauEtapes[8]->setDistances(tableauDistances8);

    int* tableauDistances9 = new int[5];
    tableauDistances9[0] = 300; // vers etape 8
    tableauDistances9[1] = 460; // vers etape 11
    tableauDistances9[2] = 335; // vers etape 12
    tableauDistances9[3] = 300; // vers etape 16
    tableauDistances9[4] = 460; // vers etape 24
    this->tableauEtapes[9]->setDistances(tableauDistances9);

    int* tableauDistances10 = new int[4];
    tableauDistances10[0] = 650; // vers etape 3
    tableauDistances10[1] = 335; // vers etape 5
    tableauDistances10[2] = 200; // vers etape 11
    tableauDistances10[3] = 350; // vers etape 13
    this->tableauEtapes[10]->setDistances(tableauDistances10);

    int* tableauDistances11 = new int[5];
    tableauDistances11[0] = 460; // vers etape 5
    tableauDistances11[1] = 460; // vers etape 9
    tableauDistances11[2] = 200; // vers etape 10
    tableauDistances11[3] = 200; // vers etape 12
    tableauDistances11[4] = 350; // vers etape 14
    this->tableauEtapes[11]->setDistances(tableauDistances11);

    int* tableauDistances12 = new int[4];
    tableauDistances12[0] = 335; // vers etape 9
    tableauDistances12[1] = 200; // vers etape 11
    tableauDistances12[2] = 350; // vers etape 15
    tableauDistances12[3] = 150; // vers etape 16
    this->tableauEtapes[12]->setDistances(tableauDistances12);

    int* tableauDistances13 = new int[2];
    tableauDistances13[0] = 350; // vers etape 10
    tableauDistances13[1] = 200; // vers etape 14
    this->tableauEtapes[13]->setDistances(tableauDistances13);

    int* tableauDistances14 = new int[3];
    tableauDistances14[0] = 350; // vers etape 11
    tableauDistances14[1] = 200; // vers etape 13
    tableauDistances14[2] = 200; // vers etape 15
    this->tableauEtapes[14]->setDistances(tableauDistances14);

    int* tableauDistances15 = new int[2];
    tableauDistances15[0] = 350; // vers etape 12
    tableauDistances15[1] = 200; // vers etape 14
    this->tableauEtapes[15]->setDistances(tableauDistances15);

    int* tableauDistances16 = new int[3];
    tableauDistances16[0] = 300; // vers etape 9
    tableauDistances16[1] = 150; // vers etape 12
    tableauDistances16[2] = 400; // vers etape 17
    this->tableauEtapes[16]->setDistances(tableauDistances16);

    int* tableauDistances17 = new int[3];
    tableauDistances17[0] = 400; // vers etape 16
    tableauDistances17[1] = 206; // vers etape 24
    tableauDistances17[2] = 210; // vers etape 26
    this->tableauEtapes[17]->setDistances(tableauDistances17);

    int* tableauDistances18 = new int[5];
    tableauDistances18[0] = 141; // vers etape 2
    tableauDistances18[1] = 111; // vers etape 3
    tableauDistances18[2] = 180; // vers etape 4
    tableauDistances18[3] = 651; // vers etape 19
    tableauDistances18[4] = 108; // vers etape 25
    this->tableauEtapes[18]->setDistances(tableauDistances18);

    int* tableauDistances19 = new int[2];
    tableauDistances19[0] = 651; // vers etape 18
    tableauDistances19[1] = 269; // vers etape 20
    this->tableauEtapes[19]->setDistances(tableauDistances19);

    int* tableauDistances20 = new int[3];
    tableauDistances20[0] = 353; // vers etape 6
    tableauDistances20[1] = 602; // vers etape 7
    tableauDistances20[2] = 269; // vers etape 19
    this->tableauEtapes[20]->setDistances(tableauDistances20);

    int* tableauDistances21 = new int[3];
    tableauDistances21[0] = 602; // vers etape 7
    tableauDistances21[1] = 353; // vers etape 8
    tableauDistances21[2] = 269; // vers etape 22
    this->tableauEtapes[21]->setDistances(tableauDistances21);

    int* tableauDistances22 = new int[2];
    tableauDistances22[0] = 269; // vers etape 21
    tableauDistances22[1] = 651; // vers etape 23
    this->tableauEtapes[22]->setDistances(tableauDistances22);

    int* tableauDistances23 = new int[3];
    tableauDistances23[0] = 651; // vers etape 22
    tableauDistances23[1] = 141; // vers etape 24
    tableauDistances23[2] = 108; // vers etape 26
    this->tableauEtapes[23]->setDistances(tableauDistances23);

    int* tableauDistances24 = new int[4];
    tableauDistances24[0] = 460; // vers etape 9
    tableauDistances24[1] = 206; // vers etape 17
    tableauDistances24[2] = 141; // vers etape 23
    tableauDistances24[3] = 41; // vers etape 26
    this->tableauEtapes[24]->setDistances(tableauDistances24);

    int* tableauDistances25 = new int[4];
    tableauDistances25[0] = 248; // vers etape 2
    tableauDistances25[1] = 190; // vers etape 3
    tableauDistances25[2] = 90; // vers etape 4
    tableauDistances25[3] = 108; // vers etape 18
    this->tableauEtapes[25]->setDistances(tableauDistances25);

    int* tableauDistances26 = new int[3];
    tableauDistances26[0] = 210; // vers etape 17
    tableauDistances26[1] = 108; // vers etape 23
    tableauDistances26[2] = 41; // vers etape 24
    this->tableauEtapes[26]->setDistances(tableauDistances26);*/

    /*

    //précalcul des distances
    int* tableauDistances0 = new int[1];
    tableauDistances0[0] = 450; // vers etape 1
    this->tableauEtapes[0]->setDistances(tableauDistances0);

    int* tableauDistances1 = new int[1];
    tableauDistances1[0] = 300; // vers etape 2
    this->tableauEtapes[1]->setDistances(tableauDistances1);

    int* tableauDistances2 = new int[3];
    tableauDistances2[0] = 150; // vers etape 3
    tableauDistances2[1] = 320; // vers etape 4
    tableauDistances2[2] = 509; // vers etape 18
    this->tableauEtapes[2]->setDistances(tableauDistances2);

    int* tableauDistances3 = new int[5];
    tableauDistances3[0] = 150; // vers etape 2
    tableauDistances3[1] = 223; // vers etape 4
    tableauDistances3[2] = 583; // vers etape 5
    tableauDistances3[3] = 650; // vers etape 10
    tableauDistances3[4] = 502; // vers etape 18
    this->tableauEtapes[3]->setDistances(tableauDistances3);

    int* tableauDistances4 = new int[4];
    tableauDistances4[0] = 320; // vers etape 2
    tableauDistances4[1] = 223; // vers etape 3
    tableauDistances4[2] = 412; // vers etape 5
    tableauDistances4[3] = 335; // vers etape 18
    this->tableauEtapes[4]->setDistances(tableauDistances4);

    int* tableauDistances5 = new int[5];
    tableauDistances5[0] = 583; // vers etape 3
    tableauDistances5[1] = 412; // vers etape 4
    tableauDistances5[2] = 300; // vers etape 6
    tableauDistances5[3] = 335; // vers etape 10
    tableauDistances5[4] = 460; // vers etape 11
    this->tableauEtapes[5]->setDistances(tableauDistances5);

    int* tableauDistances6 = new int[3];
    tableauDistances6[0] = 300; // vers etape 5
    tableauDistances6[1] = 460; // vers etape 7
    tableauDistances6[2] = 353; // vers etape 20
    this->tableauEtapes[6]->setDistances(tableauDistances6);

    int* tableauDistances7 = new int[4];
    tableauDistances7[0] = 460; // vers etape 6
    tableauDistances7[1] = 460; // vers etape 8
    tableauDistances7[2] = 602; // vers etape 20
    tableauDistances7[3] = 602; // vers etape 21
    this->tableauEtapes[7]->setDistances(tableauDistances7);

    int* tableauDistances8 = new int[3];
    tableauDistances8[0] = 460; // vers etape 7
    tableauDistances8[1] = 300; // vers etape 9
    tableauDistances8[2] = 353; // vers etape 21
    this->tableauEtapes[8]->setDistances(tableauDistances8);

    int* tableauDistances9 = new int[5];
    tableauDistances9[0] = 300; // vers etape 8
    tableauDistances9[1] = 460; // vers etape 11
    tableauDistances9[2] = 335; // vers etape 12
    tableauDistances9[3] = 300; // vers etape 16
    tableauDistances9[4] = 460; // vers etape 24
    this->tableauEtapes[9]->setDistances(tableauDistances9);

    int* tableauDistances10 = new int[4];
    tableauDistances10[0] = 650; // vers etape 3
    tableauDistances10[1] = 335; // vers etape 5
    tableauDistances10[2] = 200; // vers etape 11
    tableauDistances10[3] = 350; // vers etape 13
    this->tableauEtapes[10]->setDistances(tableauDistances10);

    int* tableauDistances11 = new int[5];
    tableauDistances11[0] = 460; // vers etape 5
    tableauDistances11[1] = 460; // vers etape 9
    tableauDistances11[2] = 200; // vers etape 10
    tableauDistances11[3] = 200; // vers etape 12
    tableauDistances11[4] = 350; // vers etape 14
    this->tableauEtapes[11]->setDistances(tableauDistances11);

    int* tableauDistances12 = new int[4];
    tableauDistances12[0] = 335; // vers etape 9
    tableauDistances12[1] = 200; // vers etape 11
    tableauDistances12[2] = 350; // vers etape 15
    tableauDistances12[3] = 150; // vers etape 16
    this->tableauEtapes[12]->setDistances(tableauDistances12);

    int* tableauDistances13 = new int[2];
    tableauDistances13[0] = 350; // vers etape 10
    tableauDistances13[1] = 200; // vers etape 14
    this->tableauEtapes[13]->setDistances(tableauDistances13);

    int* tableauDistances14 = new int[3];
    tableauDistances14[0] = 350; // vers etape 11
    tableauDistances14[1] = 200; // vers etape 13
    tableauDistances14[2] = 200; // vers etape 15
    this->tableauEtapes[14]->setDistances(tableauDistances14);

    int* tableauDistances15 = new int[2];
    tableauDistances15[0] = 350; // vers etape 12
    tableauDistances15[1] = 200; // vers etape 14
    this->tableauEtapes[15]->setDistances(tableauDistances15);

    int* tableauDistances16 = new int[3];
    tableauDistances16[0] = 300; // vers etape 9
    tableauDistances16[1] = 150; // vers etape 12
    tableauDistances16[2] = 400; // vers etape 17
    this->tableauEtapes[16]->setDistances(tableauDistances16);

    int* tableauDistances17 = new int[2];
    tableauDistances17[0] = 400; // vers etape 16
    tableauDistances17[1] = 206; // vers etape 24
    this->tableauEtapes[17]->setDistances(tableauDistances17);

    int* tableauDistances18 = new int[4];
    tableauDistances18[0] = 509; // vers etape 2
    tableauDistances18[1] = 502; // vers etape 3
    tableauDistances18[2] = 335; // vers etape 4
    tableauDistances18[3] = 254; // vers etape 19
    this->tableauEtapes[18]->setDistances(tableauDistances18);

    int* tableauDistances19 = new int[2];
    tableauDistances19[0] = 254; // vers etape 18
    tableauDistances19[1] = 269; // vers etape 20
    this->tableauEtapes[19]->setDistances(tableauDistances19);

    int* tableauDistances20 = new int[3];
    tableauDistances20[0] = 353; // vers etape 6
    tableauDistances20[1] = 602; // vers etape 7
    tableauDistances20[2] = 269; // vers etape 19
    this->tableauEtapes[20]->setDistances(tableauDistances20);

    int* tableauDistances21 = new int[3];
    tableauDistances21[0] = 602; // vers etape 7
    tableauDistances21[1] = 353; // vers etape 8
    tableauDistances21[2] = 269; // vers etape 22
    this->tableauEtapes[21]->setDistances(tableauDistances21);

    int* tableauDistances22 = new int[2];
    tableauDistances22[0] = 269; // vers etape 21
    tableauDistances22[1] = 254; // vers etape 23
    this->tableauEtapes[22]->setDistances(tableauDistances22);

    int* tableauDistances23 = new int[2];
    tableauDistances23[0] = 254; // vers etape 22
    tableauDistances23[1] = 316; // vers etape 24
    this->tableauEtapes[23]->setDistances(tableauDistances23);

    int* tableauDistances24 = new int[3];
    tableauDistances24[0] = 460; // vers etape 9
    tableauDistances24[1] = 206; // vers etape 17
    tableauDistances24[2] = 316; // vers etape 23
    this->tableauEtapes[24]->setDistances(tableauDistances24);*/
}

void Krabi2014::updateStock(){
    switch(this->tableauEtapes[this->etapeEnCours]->getEtapeType()){
        case Etape::FRUIT:
            nombreFruitsTransporte++;
            this->tableauEtapes[this->etapeEnCours]->setEtapeType(Etape::POINT_PASSAGE);
            break;
        case Etape::FEU_MINI_BRAS:
            this->tableauEtapes[this->etapeEnCours]->setEtapeType(Etape::POINT_PASSAGE);
            break;
        case Etape::FEU:
            this->tableauEtapes[this->etapeEnCours]->setEtapeType(Etape::POINT_PASSAGE);
            break;
        case Etape::DEPOSE_FRUIT:
            nombreFruitsTransporte = 0;
            break;
        case Etape::FEU_COTE:
            this->tableauEtapes[this->etapeEnCours]->setEtapeType(Etape::POINT_PASSAGE);
            #ifndef ROBOTHW
                    qDebug() << "feu coté transformé en point de passage";
            #endif
            break;
        case Etape::DEPOSE_FEU:
            nombreFeuxTransporte--;
            break;
        case Etape::TORCHE_MOBILE:
            this->tableauEtapes[this->etapeEnCours]->setEtapeType(Etape::POINT_PASSAGE);
            break;
        case Etape::FRESQUE:
            nombreFresquesTransporte = 0;
            break;
        case Etape::TIR_MAMMOUTH:
            nombreLancesTransporte -= ((TireLances*)(this->actionEtape[this->etapeEnCours]))->getNumberDone();
            break;
        default:
            // Si toutes les actions sont définies, il est impossible de tomber dans cet état.
            break;
    }
}

int Krabi2014::getScoreEtape(int i){
    int scoreTypeEtape = 0;
    /* TODO : Supprimer le modificateur temporel et inclure directement un coefficient dans le score pour les actions longues
    Plus tard : pourquoi pas changer le système en ayant les FEU etc... fils de Etape, ça éviterait aussi le switch dans updateStock().
    Juste faire attention à comment transmettre le stock à update.
    */
    float modificateurTemporel = 1.f;

    if(this->tableauEtapes[i]->getEtapeType()==Etape::FEU)
        scoreTypeEtape = 0;
    if(this->tableauEtapes[i]->getEtapeType()==Etape::TORCHE_MOBILE)
        scoreTypeEtape = 1200;
    if(this->tableauEtapes[i]->getEtapeType()==Etape::FRUIT)
    {
        scoreTypeEtape = 100;
        if(millisecondesRestantes < 10 * 1000)//Prise en compte du temps avant la fin du match
        {
            modificateurTemporel = 0.1;
        }
    }
    if(this->tableauEtapes[i]->getEtapeType()==Etape::DEPOSE_FRUIT)
    {
        scoreTypeEtape = 0 * this->nombreFruitsTransporte;
    }
    if(this->tableauEtapes[i]->getEtapeType()==Etape::DEPOSE_FEU)
    {
        scoreTypeEtape = 0 * this->nombreFeuxTransporte;
    }
    if(this->tableauEtapes[i]->getEtapeType()==Etape::FEU_MINI_BRAS)
    {
        scoreTypeEtape = 1200;
    }
    if(this->tableauEtapes[i]->getEtapeType()==Etape::TORCHE_MOBILE)
    {
        scoreTypeEtape = 1000;
    }
    if(this->tableauEtapes[i]->getEtapeType()==Etape::TIR_MAMMOUTH)
    {
        scoreTypeEtape = (((TireLances*)(this->actionEtape[i]))->getNumberDone() >= ((TireLances*)(this->actionEtape[i]))->getNumber() ) ? 0 : 1200 * (this->nombreLancesTransporte > 0);
/*
        scoreTypeEtape = 100 * this->nombreLancesTransporte;
        //scoreTypeEtape = (((TireLances*)(this->actionEtape[i]))->getNumberDone() >= ((TireLances*)(this->actionEtape[i]))->getNumber() ) ? 0 : 100 * this->nombreLancesTransporte;
7a420fecf2d3579c37bd537b72ebd1bfcbf934f1*/
    }
    if(this->tableauEtapes[i]->getEtapeType()==Etape::TIR_FILET)
    {
        scoreTypeEtape = 1000000 * (StrategieV2::getTimeSpent() >= 70000);//70000);
    }
    if(this->tableauEtapes[i]->getEtapeType()==Etape::FRESQUE)
    {
        scoreTypeEtape = 100 * this->nombreFresquesTransporte;// 10000 * this->nombreFresquesTransporte;
    }
    if(this->tableauEtapes[i]->getEtapeType()==Etape::FEU_COTE_NOTRE_COULEUR_FACE_EXTERIEUR
            || this->tableauEtapes[i]->getEtapeType()==Etape::FEU_COTE_NOTRE_COULEUR_FACE_TERRAIN)
    {
        scoreTypeEtape = 0;
    }
    if(this->tableauEtapes[i]->getEtapeType()==Etape::FEU_COTE)
    {
        scoreTypeEtape = 1000;
    }
    return scoreTypeEtape;
}
