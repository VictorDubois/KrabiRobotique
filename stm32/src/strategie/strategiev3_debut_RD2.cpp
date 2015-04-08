#include "strategiev3.h"
#include "strategieV2.h"
#include "actionGoTo.h"
#include "leds.h"
#include "odometrie.h"
#include "asservissement.h"
#include "dijkstra.h"
#include "etape.h"
#include "feuCote.h"

#ifndef ROBOTHW
    #include <QDebug>
#endif
//#include <iostream>


StrategieV3::StrategieV3(bool isBlue) : MediumLevelAction()
{
    this->avoiding = false;
    this->etapeEnCours = 0;
    this->statusStrat=1;
    this->enTrainEviterReculant = false;
    this->enTrainEviterAvancant = false;
    this->millisecondesRestantes = 90 * 1000;

#ifndef ROBOTHW
    colorLiaisonsEtapes = QColor("orange");
    colorEtapeGoal = QColor("red");
    colorEtapesIntermediaires = QColor("yellow");
    colorEtapes = QColor("orange");
    colorTexteEtapes = QColor("green");
    colorEtapesRobotVu = QColor("black");
#endif
     ///KRABI !!!
      #ifdef KRABI
    this->nombreFruitsTransporte = 0;
    this->nombreFeuxTransporte = 0;
    this->nombreFresquesTransporte = 2;
    this->nombreLancesTransporte = 6;


        actionGoto[0] = ActionGoTo(Position(200, 1850, isBlue), false);
        actionGoto[1] = ActionGoTo(Position(200, 1500, isBlue), false);
        actionGoto[2] = ActionGoTo(Position(500, 1400, isBlue), false);
        actionGoto[3] = ActionGoTo(Position(790, 1200, isBlue), false);
        actionGoto[4] = ActionGoTo(Position(750, 1200, isBlue), false);
        actionGoto[5] = ActionGoTo(Position(1050, 1300, isBlue), false);
        actionGoto[6] = ActionGoTo(Position(1050, 800, isBlue), false);
        actionGoto[7] = ActionGoTo(Position(1500, 400, isBlue), false);
        actionGoto[8] = ActionGoTo(Position(680, 680, isBlue), false);
        actionGoto[9] = ActionGoTo(Position(1850, 1300, isBlue), false);
        actionGoto[10] = ActionGoTo(Position(1300, 1400, isBlue), false);
        actionGoto[11] = ActionGoTo(Position(1500, 1400, isBlue), false);
        actionGoto[12] = ActionGoTo(Position(1700, 1400, isBlue), false);
        actionGoto[13] = ActionGoTo(Position(1320, 1700, isBlue), false);
        actionGoto[14] = ActionGoTo(Position(1500, 1700, isBlue), false);
        actionGoto[15] = ActionGoTo(Position(1680, 1700, isBlue), false);
        actionGoto[16] = ActionGoTo(Position(1850, 1400, isBlue), false);
        actionGoto[17] = ActionGoTo(Position(2250, 1400, isBlue), false);
        actionGoto[18] = ActionGoTo(Position(640, 1150, isBlue), false);
        actionGoto[19] = ActionGoTo(Position(590, 1060, isBlue), false);
        actionGoto[20] = ActionGoTo(Position(700, 290, isBlue), false);
        actionGoto[21] = ActionGoTo(Position(2100, 550, isBlue), false);
        actionGoto[22] = ActionGoTo(Position(2350, 650, isBlue), false);
        actionGoto[23] = ActionGoTo(Position(3000 - 640, 1350, isBlue), false);
        actionGoto[24] = ActionGoTo(Position(2300, 1200, isBlue), false);
        actionGoto[25] = ActionGoTo(Position(660, 1210, isBlue), false);
        actionGoto[26] = ActionGoTo(Position(3000 - 660, 1210, isBlue), false);
        actionGoto[27] = ActionGoTo(Position(400, 1200, isBlue), false);
        actionGoto[28] = ActionGoTo(Position(1300, 400, isBlue), false);
        actionGoto[29] = ActionGoTo(Position(1700, 400, isBlue), false);
        actionGoto[30] = ActionGoTo(Position(2600, 1200, isBlue), false);

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

        actionLancesKrabi[0] = TireLances(isBlue, Position(640, 1350, isBlue), true, 6);
        actionLancesKrabi[1] = TireLances(isBlue, Position(3000 - 640, 1350, isBlue), false, 0);

        actionFeuCoteKrabi[0] = FeuCoteKrabi(isBlue, Position(400, 1200, isBlue), 0);
        actionFeuCoteKrabi[1] = FeuCoteKrabi(isBlue, Position(1300, 400, isBlue), 1);
        actionFeuCoteKrabi[2] = FeuCoteKrabi(isBlue, Position(1700, 400, isBlue), 2);
        actionFeuCoteKrabi[3] = FeuCoteKrabi(isBlue, Position(2600, 1200, isBlue), 3);

        actionTorcheMobile[0] = TorcheMobile(isBlue, Position(680, 680, isBlue), Position(900, 900, isBlue));

        actionEtape[0] = &actionGoto[0];
        actionEtape[1] = &actionGoto[1];
        actionEtape[2] = &actionGoto[2];//&actionGoto[2];
        actionEtape[3] = &actionFeuKrabiLateral[2];//&actionGoto[3];
        actionEtape[4] = &actionGoto[4];//&actionGoto[4];
        actionEtape[5] = &actionGoto[5];
        actionEtape[6] = &actionGoto[6];
        actionEtape[7] = &actionGoto[7];
        actionEtape[8] = &actionTorcheMobile[0];//&actionGoto[8];//&actionGoto[8];
        actionEtape[9] = &actionGoto[9];
        actionEtape[10] = &actionGoto[10];//&actionGoto[10];
        actionEtape[11] = &actionGoto[11];
        actionEtape[12] = &actionGoto[12];//&actionGoto[12];
        actionEtape[13] = &actionFresque[0];//&actionGoto[13];
        actionEtape[14] = &actionFresque[1];//&actionGoto[14];
        actionEtape[15] = &actionFresque[2];//&actionGoto[15];
        actionEtape[16] = &actionGoto[16];
        actionEtape[17] = &actionGoto[17];
        actionEtape[18] = &actionLancesKrabi[0];
        actionEtape[19] = &actionFeuKrabiLateral[0];//&actionGoto[19];
        actionEtape[20] = &actionFeuKrabiLateral[1];
        actionEtape[21] = &actionGoto[21];
        actionEtape[22] = &actionGoto[22];
        actionEtape[23] = &actionLancesKrabi[1];
        actionEtape[24] = &actionGoto[24];
        actionEtape[25] = &actionFiletKrabi[0];
        actionEtape[26] = &actionFiletKrabi[1];
        actionEtape[27] = &actionFeuCoteKrabi[0];
        actionEtape[28] = &actionFeuCoteKrabi[1];
        actionEtape[29] = &actionFeuCoteKrabi[2];
        actionEtape[30] = &actionFeuCoteKrabi[3];

        Etape* etape0;
        Etape* etape1;
        Etape* etape2;
        Etape* etape3;
        Etape* etape4;
        Etape* etape5;
        Etape* etape6;
        Etape* etape7;
        Etape* etape8;
        Etape* etape9;
        Etape* etape10;
        Etape* etape11;
        Etape* etape12;
        Etape* etape13;
        Etape* etape14;
        Etape* etape15;
        Etape* etape16;
        Etape* etape17;
        Etape* etape18;
        Etape* etape19;
        Etape* etape20;
        Etape* etape21;
        Etape* etape22;
        Etape* etape23;
        Etape* etape24;
        Etape* etape25;
        Etape* etape26;
        Etape* etape27;
        Etape* etape28;
        Etape* etape29;
        Etape* etape30;


        Etape** tableauEtapes0 = new Etape*[1];
        Etape** tableauEtapes1  = new Etape*[2];
        Etape** tableauEtapes2  = new Etape*[5];
        Etape** tableauEtapes3  = new Etape*[6];
        Etape** tableauEtapes4  = new Etape*[6];
        Etape** tableauEtapes5  = new Etape*[5];
        Etape** tableauEtapes6  = new Etape*[4];
        Etape** tableauEtapes7  = new Etape*[6];
        Etape** tableauEtapes8  = new Etape*[4];
        Etape** tableauEtapes9  = new Etape*[5];
        Etape** tableauEtapes10 = new Etape*[4];
        Etape** tableauEtapes11 = new Etape*[5];
        Etape** tableauEtapes12 = new Etape*[4];
        Etape** tableauEtapes13 = new Etape*[1];
        Etape** tableauEtapes14 = new Etape*[1];
        Etape** tableauEtapes15 = new Etape*[1];
        Etape** tableauEtapes16 = new Etape*[3];
        Etape** tableauEtapes17 = new Etape*[4];
        Etape** tableauEtapes18 = new Etape*[6];
        Etape** tableauEtapes19 = new Etape*[4];
        Etape** tableauEtapes20 = new Etape*[4];
        Etape** tableauEtapes21 = new Etape*[4];
        Etape** tableauEtapes22 = new Etape*[2];
        Etape** tableauEtapes23 = new Etape*[4];
        Etape** tableauEtapes24 = new Etape*[5];
        Etape** tableauEtapes25 = new Etape*[5];
        Etape** tableauEtapes26 = new Etape*[3];
        Etape** tableauEtapes27 = new Etape*[4];
        Etape** tableauEtapes28 = new Etape*[4];
        Etape** tableauEtapes29 = new Etape*[4];
        Etape** tableauEtapes30 = new Etape*[3];

        //arguments : Position, tableau des etapes liées, nombre d'étapes liées, numéro de l'étape, type d'étape, état de l'étape, nombreEtapesLieesParFinirEtape
        etape0 = new Etape(Position(200, 1850, isBlue), tableauEtapes0, 1, 0, Etape::DEPART, -1, 0);
        etape1 = new Etape(Position(200, 1500, isBlue),         tableauEtapes1,  2, 1,  Etape::POINT_PASSAGE,-1, 0);
        etape2  = new Etape(Position(500, 1400, isBlue),        tableauEtapes2,  5, 2,  Etape::POINT_PASSAGE,-1, 0); //cette étape krabi baisse le bras
        etape3  = new Etape(Position(790, 1200, isBlue),        tableauEtapes3,  6, 3,  Etape::FEU_MINI_BRAS,-1, 0); //cette étape krabi ramasse le feu et le garde
        etape4  = new Etape(Position(750, 1200, isBlue),        tableauEtapes4,  6, 4,  Etape::POINT_PASSAGE,-1, 0);
        etape5  = new Etape(Position(1050, 1300, isBlue),       tableauEtapes5,  5, 5,  Etape::POINT_PASSAGE,-1, 0);
        etape6  = new Etape(Position(1050, 800, isBlue),        tableauEtapes6,  4, 6,  Etape::POINT_PASSAGE,-1, 0);
        etape7  = new Etape(Position(1500, 450, isBlue),        tableauEtapes7,  5, 7,  Etape::POINT_PASSAGE,-1, 0);
        etape8  = new Etape(Position(680, 680, isBlue),         tableauEtapes8,  3, 8,  Etape::TORCHE_MOBILE,-1, 0);
        etape9  = new Etape(Position(1900, 1300, isBlue),       tableauEtapes9,  4, 9,  Etape::POINT_PASSAGE,-1, 0);
        etape10 = new Etape(Position(1300, 1400, isBlue),       tableauEtapes10, 4, 10, Etape::POINT_PASSAGE,-1, 0);
        etape11 = new Etape(Position(1500, 1450, isBlue),       tableauEtapes11, 5, 11, Etape::POINT_PASSAGE,-1, 0);
        etape12 = new Etape(Position(1700, 1400, isBlue),       tableauEtapes12, 4, 12, Etape::POINT_PASSAGE,-1, 0); // idem que etape3 mais la suivante est etape17
        etape13 = new Etape(Position(1320, 1700, isBlue),       tableauEtapes13, 1, 13, Etape::FRESQUE, -1, 2); //les 3 FRESQUE sont liées
        etape14 = new Etape(Position(1500, 1700, isBlue),       tableauEtapes14, 1, 14, Etape::FRESQUE, -1, 2);
        etape15 = new Etape(Position(1680, 1700, isBlue),       tableauEtapes15, 1, 15, Etape::FRESQUE, -1, 2);
        etape16 = new Etape(Position(1850, 1400, isBlue),       tableauEtapes16, 3, 16, Etape::POINT_PASSAGE, -1, 0); //idem que etape4
        etape17 = new Etape(Position(2250, 1400, isBlue),       tableauEtapes17, 4, 17, Etape::POINT_PASSAGE, -1, 0);
        etape18 = new Etape(Position(640, 1350, isBlue),        tableauEtapes18, 6, 18, Etape::TIR_MAMMOUTH, -1, 0);
        etape19 = new Etape(Position(590, 1060, isBlue),        tableauEtapes19, 5, 19, Etape::FEU_MINI_BRAS, -1, 0);
        etape20 = new Etape(Position(700, 290, isBlue),         tableauEtapes20, 5, 20, Etape::FEU_MINI_BRAS, -1, 0);
        etape21 = new Etape(Position(2100, 550, isBlue),        tableauEtapes21, 3, 21, Etape::POINT_PASSAGE, -1, 0);
        etape22 = new Etape(Position(2350, 650, isBlue),        tableauEtapes22, 2, 22, Etape::POINT_PASSAGE, -1, 0);
        etape23 = new Etape(Position(3000 - 640, 1350, isBlue), tableauEtapes23, 3, 23, Etape::TIR_MAMMOUTH, -1, 0);
        etape24 = new Etape(Position(2300, 1200, isBlue),       tableauEtapes24, 5, 24, Etape::POINT_PASSAGE, -1, 0);
        etape25 = new Etape(Position(660, 1210, isBlue),        tableauEtapes25, 5, 25, Etape::TIR_FILET, -1, 0);
        etape26 = new Etape(Position(3000 - 660, 1210, isBlue), tableauEtapes26, 3, 26, Etape::TIR_FILET, -1, 0);
        etape27 = new Etape(Position(400, 1200, isBlue),        tableauEtapes27, 4, 27, Etape::FEU_COTE, -1, 0);
        etape28 = new Etape(Position(1300, 400, isBlue),        tableauEtapes28, 5, 28, Etape::POINT_PASSAGE, -1, 0);
        etape29 = new Etape(Position(1700, 400, isBlue),        tableauEtapes29, 3, 29, Etape::FEU_COTE, -1, 0);
        etape30 = new Etape(Position(2600, 1200, isBlue),       tableauEtapes30, 3, 30, Etape::POINT_PASSAGE, -1, 0);


        tableauEtapes0[0] = etape1;

        tableauEtapes1[0] = etape2;
        tableauEtapes1[1] = etape27;

        tableauEtapes2[0] = etape3;
        tableauEtapes2[1] = etape4;
        tableauEtapes2[2] = etape18;
        tableauEtapes2[3] = etape25;
        tableauEtapes2[4] = etape27;

        tableauEtapes3[0] = etape2;
        tableauEtapes3[1] = etape4;
        tableauEtapes3[2] = etape5;
        tableauEtapes3[3] = etape10;
        tableauEtapes3[4] = etape18;
        tableauEtapes3[5] = etape25;

        tableauEtapes4[0] = etape2;
        tableauEtapes4[1] = etape3;
        tableauEtapes4[2] = etape5;
        tableauEtapes4[3] = etape18;
        tableauEtapes4[4] = etape25;
        tableauEtapes4[5] = etape27;

        tableauEtapes5[0] = etape3;
        tableauEtapes5[1] = etape4;
        tableauEtapes5[2] = etape6;
        tableauEtapes5[3] = etape10;
        tableauEtapes5[4] = etape11;

        tableauEtapes6[0] = etape5;
        tableauEtapes6[1] = etape7;
        tableauEtapes6[2] = etape20;
        tableauEtapes6[3] = etape28;

        tableauEtapes7[0] = etape6;
        //tableauEtapes7[1] = etape8;
        tableauEtapes7[1] = etape20;
        tableauEtapes7[2] = etape21;
        tableauEtapes7[3] = etape28;
        tableauEtapes7[4] = etape29;

        //tableauEtapes8[1] = etape9;
        tableauEtapes8[0] = etape19;
        tableauEtapes8[1] = etape20;
        tableauEtapes8[2] = etape28;
        //tableauEtapes8[3] = etape29;

        tableauEtapes9[0] = etape11;
        tableauEtapes9[1] = etape12;
        tableauEtapes9[2] = etape16;
        tableauEtapes9[3] = etape24;

        tableauEtapes10[0] = etape3;
        tableauEtapes10[1] = etape5;
        tableauEtapes10[2] = etape11;
        tableauEtapes10[3] = etape13;

        tableauEtapes11[0] = etape5;
        tableauEtapes11[1] = etape9;
        tableauEtapes11[2] = etape10;
        tableauEtapes11[3] = etape12;
        tableauEtapes11[4] = etape14;

        tableauEtapes12[0] = etape9;
        tableauEtapes12[1] = etape11;
        tableauEtapes12[2] = etape15;
        tableauEtapes12[3] = etape16;


        tableauEtapes13[0] = etape10;
        //tableauEtapes13[1] = etape14;

        tableauEtapes14[0] = etape11;
        //tableauEtapes14[1] = etape13;
        //tableauEtapes14[2] = etape15;

        tableauEtapes15[0] = etape12;
        //tableauEtapes15[1] = etape14;

        tableauEtapes16[0] = etape9;
        tableauEtapes16[1] = etape12;
        tableauEtapes16[2] = etape17;

        tableauEtapes17[0] = etape16;
        tableauEtapes17[1] = etape24;
        tableauEtapes17[2] = etape26;
        tableauEtapes17[3] = etape30;

        tableauEtapes18[0] = etape2;
        tableauEtapes18[1] = etape3;
        tableauEtapes18[2] = etape4;
        tableauEtapes18[3] = etape19;
        tableauEtapes18[4] = etape25;
        tableauEtapes18[5] = etape27;

        tableauEtapes19[0] = etape18;
        tableauEtapes19[1] = etape20;
        tableauEtapes19[2] = etape25;
        tableauEtapes19[3] = etape27;
        tableauEtapes19[4] = etape8;

        tableauEtapes20[0] = etape6;
        tableauEtapes20[1] = etape7;
        tableauEtapes20[2] = etape19;
        tableauEtapes20[3] = etape28;
        tableauEtapes20[4] = etape8;

        tableauEtapes21[0] = etape7;
        //tableauEtapes21[1] = etape8;
        tableauEtapes21[1] = etape22;
        tableauEtapes21[2] = etape29;

        tableauEtapes22[0] = etape21;
        tableauEtapes22[1] = etape23;

        tableauEtapes23[0] = etape22;
        tableauEtapes23[1] = etape24;
        tableauEtapes23[2] = etape26;
        tableauEtapes23[3] = etape30;

        tableauEtapes24[0] = etape9;
        tableauEtapes24[1] = etape17;
        tableauEtapes24[2] = etape23;
        tableauEtapes24[3] = etape26;
        tableauEtapes24[4] = etape30;

        tableauEtapes25[0] = etape2;
        tableauEtapes25[1] = etape3;
        tableauEtapes25[2] = etape4;
        tableauEtapes25[3] = etape18;
        tableauEtapes25[4] = etape19;

        tableauEtapes26[0] = etape17;
        tableauEtapes26[1] = etape23;
        tableauEtapes26[2] = etape24;

        tableauEtapes27[0] = etape2;
        tableauEtapes27[1] = etape4;
        tableauEtapes27[2] = etape18;
        tableauEtapes27[3] = etape19;

        tableauEtapes28[0] = etape6;
        tableauEtapes28[1] = etape7;
        tableauEtapes28[2] = etape20;
        tableauEtapes28[3] = etape29;
        tableauEtapes28[4] = etape8;

        tableauEtapes29[0] = etape7;
        //tableauEtapes29[1] = etape8;
        tableauEtapes29[1] = etape21;
        tableauEtapes29[2] = etape28;

        tableauEtapes30[0] = etape17;
        tableauEtapes30[1] = etape23;
        tableauEtapes30[2] = etape24;

        etape0->setChildren(tableauEtapes0);
        etape1->setChildren(tableauEtapes1);
        etape2->setChildren(tableauEtapes2);
        etape3->setChildren(tableauEtapes3);
        etape4->setChildren(tableauEtapes4);
        etape5->setChildren(tableauEtapes5);
        etape6->setChildren(tableauEtapes6);
        etape7->setChildren(tableauEtapes7);
        etape8->setChildren(tableauEtapes8);
        etape9->setChildren(tableauEtapes9);
        etape10->setChildren(tableauEtapes10);
        etape11->setChildren(tableauEtapes11);
        etape12->setChildren(tableauEtapes12);
        etape13->setChildren(tableauEtapes13);
        etape14->setChildren(tableauEtapes14);
        etape15->setChildren(tableauEtapes15);
        etape16->setChildren(tableauEtapes16);
        etape17->setChildren(tableauEtapes17);
        etape18->setChildren(tableauEtapes18);
        etape19->setChildren(tableauEtapes19);
        etape20->setChildren(tableauEtapes20);
        etape21->setChildren(tableauEtapes21);
        etape22->setChildren(tableauEtapes22);
        etape23->setChildren(tableauEtapes23);
        etape24->setChildren(tableauEtapes24);
        etape25->setChildren(tableauEtapes25);
        etape26->setChildren(tableauEtapes26);
        etape27->setChildren(tableauEtapes27);
        etape28->setChildren(tableauEtapes28);
        etape29->setChildren(tableauEtapes29);
        etape30->setChildren(tableauEtapes30);

        Etape** tableauEtapesTotal = new Etape*[NOMBRE_ETAPES];
        tableauEtapesTotal[0] = etape0;
        tableauEtapesTotal[1] = etape1;
        tableauEtapesTotal[2] = etape2;
        tableauEtapesTotal[3] = etape3;
        tableauEtapesTotal[4] = etape4;
        tableauEtapesTotal[5] = etape5 ;
        tableauEtapesTotal[6] = etape6 ;
        tableauEtapesTotal[7] = etape7 ;
        tableauEtapesTotal[8] = etape8 ;
        tableauEtapesTotal[9] = etape9;
        tableauEtapesTotal[10] = etape10;
        tableauEtapesTotal[11] = etape11;
        tableauEtapesTotal[12] = etape12;
        tableauEtapesTotal[13] = etape13;
        tableauEtapesTotal[14] = etape14;
        tableauEtapesTotal[15] = etape15;
        tableauEtapesTotal[16] = etape16;
        tableauEtapesTotal[17] = etape17;
        tableauEtapesTotal[18] = etape18;
        tableauEtapesTotal[19] = etape19;
        tableauEtapesTotal[20] = etape20;
        tableauEtapesTotal[21] = etape21;
        tableauEtapesTotal[22] = etape22;
        tableauEtapesTotal[23] = etape23;
        tableauEtapesTotal[24] = etape24;
        tableauEtapesTotal[25] = etape25;
        tableauEtapesTotal[26] = etape26;
        tableauEtapesTotal[27] = etape27;
        tableauEtapesTotal[28] = etape28;
        tableauEtapesTotal[29] = etape29;
        tableauEtapesTotal[30] = etape30;
        //tableauEtapesTotal[31] = etape31;
        //FIN KRABI
    #endif

    #ifdef KRABI_JR
        /// KARBI-JUNIOR
        this->nombreFruitsTransporte = 0;
                this->nombreFeuxTransporte = 0;
                this->nombreFresquesTransporte = 0;
                this->nombreLancesTransporte = 0;

                //etape2 = new Etape(Position(185, 1200, isBlue), tableauEtapes2, 2, 2, Etape::FEU_COTE_NOTRE_COULEUR_FACE_EXTERIEUR, -1, 0);
                actionFeuCote[0] = FeuCote(isBlue, Position(185, 1200, isBlue), FeuCote::NOTRE_BORDURE, FeuCote::NOTRE_COULEUR_VERS_EXTERIEUR, FeuCote::COTE_NOTRE_DEPART);
                actionFeuCote[1] = FeuCote(isBlue, Position(1300, 185, isBlue), FeuCote::BORDURE_MILIEU, FeuCote::NOTRE_COULEUR_VERS_TERRAIN, FeuCote::COTE_NOTRE_DEPART);
                actionFeuCote[2] = FeuCote(isBlue, Position(1700, 185, isBlue), FeuCote::BORDURE_MILIEU, FeuCote::NOTRE_COULEUR_VERS_EXTERIEUR, FeuCote::COTE_DEPART_ADVERSAIRE);
                actionFeuCote[3] = FeuCote(isBlue, Position(2815, 1200, isBlue), FeuCote::BORDURE_ADVERSAIRE, FeuCote::NOTRE_COULEUR_VERS_EXTERIEUR, FeuCote::COTE_DEPART_ADVERSAIRE);
                //                etape18 = new Etape(Position(2400, 1550, isBlue), tableauEtapes18, 3, 18, Etape::DEPOSE_FRUIT, -1, 0);

                actionDeposeFruits[0] = DeposeFruits(isBlue, Position(2400, 1550, isBlue));

                actionGoto[0] = ActionGoTo(Position(185, 1500, isBlue), false);
                actionGoto[1] = ActionGoTo(Position(185, 1200, isBlue), false);
                actionGoto[2] = ActionGoTo(Position(185, 900, isBlue), false);
                actionGoto[3] = ActionGoTo(Position(185, 800, isBlue), false);
                actionGoto[4] = ActionGoTo(Position(185, 600, isBlue), false);
                actionGoto[5] = ActionGoTo(Position(600, 185, isBlue), false);
                actionGoto[6] = ActionGoTo(Position(800, 185, isBlue), false);
                actionGoto[7] = ActionGoTo(Position(900, 185, isBlue), false);
                actionGoto[8] = ActionGoTo(Position(1300, 185, isBlue), false);
                actionGoto[9] = ActionGoTo(Position(1700, 185, isBlue), false);
                actionGoto[10] = ActionGoTo(Position(2100, 185, isBlue), false);
                actionGoto[11] = ActionGoTo(Position(2200, 185, isBlue), false);
                actionGoto[12] = ActionGoTo(Position(2400, 185, isBlue), false);
                actionGoto[13] = ActionGoTo(Position(2815, 600, isBlue), false);
                actionGoto[14] = ActionGoTo(Position(2815, 800, isBlue), false);
                actionGoto[15] = ActionGoTo(Position(2815, 900, isBlue), false);
                actionGoto[16] = ActionGoTo(Position(2815, 1200, isBlue), false);
                actionGoto[17] = ActionGoTo(Position(2400, 1550, isBlue), false);
                actionGoto[18] = ActionGoTo(Position(2100, 1550, isBlue), false);
                actionGoto[19] = ActionGoTo(Position(600, 900, isBlue), false);
                actionGoto[20] = ActionGoTo(Position(900, 600, isBlue), false);
                actionGoto[21] = ActionGoTo(Position(1500, 600, isBlue), false);
                actionGoto[22] = ActionGoTo(Position(2100, 600, isBlue), false);
                actionGoto[23] = ActionGoTo(Position(1800, 800, isBlue), false);
                actionGoto[24] = ActionGoTo(Position(2400, 900, isBlue), false);
                actionGoto[25] = ActionGoTo(Position(2100, 1200, isBlue), false);
                actionGoto[26] = ActionGoTo(Position(1800, 1550, isBlue), false);
                actionGoto[27] = ActionGoTo(Position(1800, 1000, isBlue), false);
                actionGoto[28] = ActionGoTo(Position(600, 1100, isBlue), false);
                actionGoto[29] = ActionGoTo(Position(600, 600, isBlue), false);
                actionGoto[30] = ActionGoTo(Position(2400, 600, isBlue), false);

                actionEtape[0] = &actionGoto[0];
                //actionEtape[1] = &actionGoto[1];
                actionEtape[1] = &actionFeuCote[0];
                actionEtape[2] = &actionGoto[2];
                actionEtape[3] = &actionGoto[3];
                actionEtape[4] = &actionGoto[4];
                actionEtape[5] = &actionGoto[5];
                actionEtape[6] = &actionGoto[6];
                actionEtape[7] = &actionGoto[7];
                //actionEtape[8] = &actionGoto[8];
                actionEtape[8] = &actionFeuCote[1];
                //actionEtape[9] = &actionGoto[9];
                actionEtape[9] = &actionFeuCote[2];
                actionEtape[10] = &actionGoto[10];
                actionEtape[11] = &actionGoto[11];
                actionEtape[12] = &actionGoto[12];
                actionEtape[13] = &actionGoto[13];
                actionEtape[14] = &actionGoto[14];
                actionEtape[15] = &actionGoto[15];
                //actionEtape[16] = &actionGoto[16];
                actionEtape[16] = &actionFeuCote[3];
                actionEtape[17] = &actionDeposeFruits[0];//&actionGoto[17];
                actionEtape[18] = &actionGoto[18];
                actionEtape[19] = &actionGoto[19];
                actionEtape[20] = &actionGoto[20];
                actionEtape[21] = &actionGoto[21];
                actionEtape[22] = &actionGoto[22];
                actionEtape[23] = &actionGoto[23];
                actionEtape[24] = &actionGoto[24];
                actionEtape[25] = &actionGoto[25];
                actionEtape[26] = &actionGoto[26];
                actionEtape[27] = &actionGoto[27];
                actionEtape[28] = &actionGoto[28];
                actionEtape[29] = &actionGoto[29];
                actionEtape[30] = &actionGoto[30];

                Etape* etape0;
                Etape* etape1;
                Etape* etape2;
                Etape* etape3;
                Etape* etape4;
                Etape* etape5;
                Etape* etape6;
                Etape* etape7;
                Etape* etape8;
                Etape* etape9;
                Etape* etape10;
                Etape* etape11;
                Etape* etape12;
                Etape* etape13;
                Etape* etape14;
                Etape* etape15;
                Etape* etape16;
                Etape* etape17;
                Etape* etape18;
                Etape* etape19;
                Etape* etape20;
                Etape* etape21;
                Etape* etape22;
                Etape* etape23;
                Etape* etape24;
                Etape* etape25;
                Etape* etape26;
                Etape* etape27;
                Etape* etape28;
                Etape* etape29;
                Etape* etape30;

                Etape** tableauEtapes0 = new Etape*[2];
                Etape** tableauEtapes1 = new Etape*[2];
                Etape** tableauEtapes2 = new Etape*[2];
                Etape** tableauEtapes3 = new Etape*[2];
                Etape** tableauEtapes4 = new Etape*[4];
                Etape** tableauEtapes5 = new Etape*[3];
                Etape** tableauEtapes6 = new Etape*[3];
                Etape** tableauEtapes7 = new Etape*[3];
                Etape** tableauEtapes8 = new Etape*[4];
                Etape** tableauEtapes9 = new Etape*[5];
                Etape** tableauEtapes10 = new Etape*[2];
                Etape** tableauEtapes11 = new Etape*[3];
                Etape** tableauEtapes12 = new Etape*[3];
                Etape** tableauEtapes13 = new Etape*[3];
                Etape** tableauEtapes14 = new Etape*[3];
                Etape** tableauEtapes15 = new Etape*[2];
                Etape** tableauEtapes16 = new Etape*[3];
                Etape** tableauEtapes17 = new Etape*[3];
                Etape** tableauEtapes18 = new Etape*[2];
                Etape** tableauEtapes19 = new Etape*[4];
                Etape** tableauEtapes20 = new Etape*[5];
                Etape** tableauEtapes21 = new Etape*[6];
                Etape** tableauEtapes22 = new Etape*[4];
                Etape** tableauEtapes23 = new Etape*[4];
                Etape** tableauEtapes24 = new Etape*[4];
                Etape** tableauEtapes25 = new Etape*[3];
                Etape** tableauEtapes26 = new Etape*[2];
                Etape** tableauEtapes27 = new Etape*[3];
                Etape** tableauEtapes28 = new Etape*[2];
                Etape** tableauEtapes29 = new Etape*[5];
                Etape** tableauEtapes30 = new Etape*[6];

                etape0 =  new Etape(Position(185, 1500, isBlue),  tableauEtapes0,  2, 0,  Etape::DEPART, -1, 0);
                etape1 =  new Etape(Position(185, 1200, isBlue),  tableauEtapes1,  2, 1,  Etape::FEU_COTE_NOTRE_COULEUR_FACE_EXTERIEUR, -1, 0);
                etape2 =  new Etape(Position(185, 900, isBlue),   tableauEtapes2,  2, 2,  Etape::FEU, -1, 1);
                etape3 =  new Etape(Position(185, 800, isBlue),   tableauEtapes3,  2, 3,  Etape::FRUIT, -1, 0);
                etape4 =  new Etape(Position(185, 600, isBlue),   tableauEtapes4,  4, 4,  Etape::FRUIT, -1, 0);
                etape5 =  new Etape(Position(600, 185, isBlue),   tableauEtapes5,  3, 5,  Etape::FRUIT, -1, 0);
                etape6 =  new Etape(Position(800, 185, isBlue),   tableauEtapes6,  3, 6,  Etape::FRUIT, -1, 0);
                etape7 =  new Etape(Position(900, 185, isBlue),   tableauEtapes7,  3, 7,  Etape::FEU, -1, 1);//FEU
                etape8 =  new Etape(Position(1300, 185, isBlue),  tableauEtapes8,  4, 8,  Etape::FEU_COTE_NOTRE_COULEUR_FACE_TERRAIN, -1, 0);
                etape9 =  new Etape(Position(1700, 185, isBlue),  tableauEtapes9,  5, 9,  Etape::FEU_COTE_NOTRE_COULEUR_FACE_EXTERIEUR, -1, 0);
                etape10 = new Etape(Position(2100, 185, isBlue),  tableauEtapes10, 2, 10, Etape::FEU, -1, 1);
                etape11 = new Etape(Position(2200, 185, isBlue),  tableauEtapes11, 3, 11, Etape::FRUIT, -1, 0);
                etape12 = new Etape(Position(2400, 185, isBlue),  tableauEtapes12, 3, 12, Etape::FRUIT, -1, 0);
                etape13 = new Etape(Position(2815, 600, isBlue),  tableauEtapes13, 3, 13, Etape::FRUIT, -1, 0);
                etape14 = new Etape(Position(2815, 800, isBlue),  tableauEtapes14, 3, 14, Etape::FRUIT, -1, 0);
                etape15 = new Etape(Position(2815, 900, isBlue),  tableauEtapes15, 2, 15, Etape::FEU, -1, 1);
                etape16 = new Etape(Position(2815, 1200, isBlue), tableauEtapes16, 3, 16, Etape::FEU_COTE_NOTRE_COULEUR_FACE_TERRAIN, -1, 0);
                etape17 = new Etape(Position(2400, 1550, isBlue), tableauEtapes17, 3, 17, Etape::DEPOSE_FRUIT, -1, 0);
                etape18 = new Etape(Position(2100, 1550, isBlue), tableauEtapes18, 2, 18, Etape::TIR_MAMMOUTH, -1, 1);
                etape19 = new Etape(Position(600, 900, isBlue),   tableauEtapes19, 4, 19, Etape::FEU, -1, 1);
                etape20 = new Etape(Position(900, 600, isBlue),   tableauEtapes20, 5, 20, Etape::FEU, -1, 1);
                etape21 = new Etape(Position(1500, 600, isBlue),  tableauEtapes21, 6, 21, Etape::POINT_PASSAGE, -1, 0);
                etape22 = new Etape(Position(2100, 600, isBlue),  tableauEtapes22, 4, 22, Etape::FEU, -1, 0);
                etape23 = new Etape(Position(1800, 800, isBlue),  tableauEtapes23, 4, 23, Etape::TIR_MAMMOUTH, -1, 0);
                etape24 = new Etape(Position(2400, 900, isBlue),  tableauEtapes24, 4, 24, Etape::FEU, -1, 1);
                etape25 = new Etape(Position(2100, 1200, isBlue), tableauEtapes25, 3, 25, Etape::FEU, -1, 1);
                etape26 = new Etape(Position(1800, 1550, isBlue), tableauEtapes26, 2, 26, Etape::POINT_PASSAGE, -1, 0);
                etape27 = new Etape(Position(1800, 1000, isBlue), tableauEtapes27, 3, 27, Etape::POINT_PASSAGE, -1, 0);
                etape28 = new Etape(Position(600, 1100, isBlue),  tableauEtapes28, 2, 28, Etape::POINT_PASSAGE, -1, 0);
                etape29 = new Etape(Position(600, 600, isBlue),   tableauEtapes29, 5, 29, Etape::POINT_PASSAGE, -1, 0);
                etape30 = new Etape(Position(2400, 600, isBlue),  tableauEtapes30, 6, 30, Etape::POINT_PASSAGE, -1, 0);

                tableauEtapes0[0] = etape1;
                tableauEtapes0[1] = etape28;

                tableauEtapes1[0] = etape0;
                tableauEtapes1[1] = etape2;

                tableauEtapes2[0] = etape1;
                tableauEtapes2[1] = etape3;

                tableauEtapes3[0] = etape2;
                tableauEtapes3[1] = etape4;

                tableauEtapes4[0] = etape3;
                tableauEtapes4[1] = etape5;
                tableauEtapes4[2] = etape19;
                tableauEtapes4[3] = etape29;

                tableauEtapes5[0] = etape4;
                tableauEtapes5[1] = etape6;
                tableauEtapes5[2] = etape29;

                tableauEtapes6[0] = etape5;
                tableauEtapes6[1] = etape7;
                tableauEtapes6[2] = etape29;

                tableauEtapes7[0] = etape6;
                tableauEtapes7[1] = etape8;
                tableauEtapes7[2] = etape21;

                tableauEtapes8[0] = etape7;
                tableauEtapes8[1] = etape9;
                tableauEtapes8[2] = etape20;
                tableauEtapes8[3] = etape21;

                tableauEtapes9[0] = etape8;
                tableauEtapes9[1] = etape10;
                tableauEtapes9[2] = etape20;
                tableauEtapes9[3] = etape21;
                tableauEtapes9[4] = etape23;

                tableauEtapes10[0] = etape9;
                tableauEtapes10[1] = etape11;

                tableauEtapes11[0] = etape10;
                tableauEtapes11[1] = etape12;
                tableauEtapes11[2] = etape30;

                tableauEtapes12[0] = etape11;
                tableauEtapes12[1] = etape13;
                tableauEtapes12[2] = etape30;

                tableauEtapes13[0] = etape12;
                tableauEtapes13[1] = etape14;
                tableauEtapes13[2] = etape30;

                tableauEtapes14[0] = etape13;
                tableauEtapes14[1] = etape15;
                tableauEtapes14[2] = etape30;

                tableauEtapes15[0] = etape14;
                tableauEtapes15[1] = etape16;

                tableauEtapes16[0] = etape15;
                tableauEtapes16[1] = etape17;
                tableauEtapes16[2] = etape25;

                tableauEtapes17[0] = etape16;
                tableauEtapes17[1] = etape18;
                tableauEtapes17[2] = etape24;

                tableauEtapes18[0] = etape17;
                tableauEtapes18[1] = etape26;

                tableauEtapes19[0] = etape4;
                tableauEtapes19[1] = etape20;
                tableauEtapes19[2] = etape28;
                tableauEtapes19[3] = etape29;

                tableauEtapes20[0] = etape8;
                tableauEtapes20[1] = etape9;
                tableauEtapes20[2] = etape19;
                tableauEtapes20[3] = etape21;
                tableauEtapes20[4] = etape29;

                tableauEtapes21[0] = etape7;
                tableauEtapes21[1] = etape8;
                tableauEtapes21[2] = etape9;
                tableauEtapes21[3] = etape20;
                tableauEtapes21[4] = etape22;
                tableauEtapes21[5] = etape23;

                tableauEtapes22[0] = etape21;
                tableauEtapes22[1] = etape23;
                tableauEtapes22[2] = etape24;
                tableauEtapes22[3] = etape30;

                tableauEtapes23[0] = etape9;
                tableauEtapes23[1] = etape21;
                tableauEtapes23[2] = etape22;
                tableauEtapes23[3] = etape27;

                tableauEtapes24[0] = etape17;
                tableauEtapes24[1] = etape22;
                tableauEtapes24[2] = etape25;
                tableauEtapes24[3] = etape30;

                tableauEtapes25[0] = etape16;
                tableauEtapes25[1] = etape24;
                tableauEtapes25[2] = etape27;

                tableauEtapes26[0] = etape18;
                tableauEtapes26[1] = etape27;

                tableauEtapes27[0] = etape23;
                tableauEtapes27[1] = etape25;
                tableauEtapes27[2] = etape26;

                tableauEtapes28[0] = etape0;
                tableauEtapes28[1] = etape19;

                tableauEtapes29[0] = etape4;
                tableauEtapes29[1] = etape5;
                tableauEtapes29[2] = etape6;
                tableauEtapes29[3] = etape19;
                tableauEtapes29[4] = etape20;

                tableauEtapes30[0] = etape11;
                tableauEtapes30[1] = etape12;
                tableauEtapes30[2] = etape13;
                tableauEtapes30[3] = etape14;
                tableauEtapes30[4] = etape22;
                tableauEtapes30[5] = etape24;

                etape0->setChildren(tableauEtapes0);
                etape1->setChildren(tableauEtapes1);
                etape2->setChildren(tableauEtapes2);
                etape3->setChildren(tableauEtapes3);
                etape4->setChildren(tableauEtapes4);
                etape5->setChildren(tableauEtapes5);
                etape6->setChildren(tableauEtapes6);
                etape7->setChildren(tableauEtapes7);
                etape8->setChildren(tableauEtapes8);
                etape9->setChildren(tableauEtapes9);
                etape10->setChildren(tableauEtapes10);
                etape11->setChildren(tableauEtapes11);
                etape12->setChildren(tableauEtapes12);
                etape13->setChildren(tableauEtapes13);
                etape14->setChildren(tableauEtapes14);
                etape15->setChildren(tableauEtapes15);
                etape16->setChildren(tableauEtapes16);
                etape17->setChildren(tableauEtapes17);
                etape18->setChildren(tableauEtapes18);
                etape19->setChildren(tableauEtapes19);
                etape20->setChildren(tableauEtapes20);
                etape21->setChildren(tableauEtapes21);
                etape22->setChildren(tableauEtapes22);
                etape23->setChildren(tableauEtapes23);
                etape24->setChildren(tableauEtapes24);
                etape25->setChildren(tableauEtapes25);
                etape26->setChildren(tableauEtapes26);
                etape27->setChildren(tableauEtapes27);
                etape28->setChildren(tableauEtapes28);
                etape29->setChildren(tableauEtapes29);
                etape30->setChildren(tableauEtapes30);

                Etape** tableauEtapesTotal = new Etape*[NOMBRE_ETAPES];
                tableauEtapesTotal[0] = etape0;
                tableauEtapesTotal[1] = etape1;
                tableauEtapesTotal[2] = etape2;
                tableauEtapesTotal[3] = etape3;
                tableauEtapesTotal[4] = etape4;
                tableauEtapesTotal[5] = etape5;
                tableauEtapesTotal[6] = etape6;
                tableauEtapesTotal[7] = etape7;
                tableauEtapesTotal[8] = etape8;
                tableauEtapesTotal[9] = etape9;
                tableauEtapesTotal[10] = etape10;
                tableauEtapesTotal[11] = etape11;
                tableauEtapesTotal[12] = etape12;
                tableauEtapesTotal[13] = etape13;
                tableauEtapesTotal[14] = etape14;
                tableauEtapesTotal[15] = etape15;
                tableauEtapesTotal[16] = etape16;
                tableauEtapesTotal[17] = etape17;
                tableauEtapesTotal[18] = etape18;
                tableauEtapesTotal[19] = etape19;
                tableauEtapesTotal[20] = etape20;
                tableauEtapesTotal[21] = etape21;
                tableauEtapesTotal[22] = etape22;
                tableauEtapesTotal[23] = etape23;
                tableauEtapesTotal[24] = etape24;
                tableauEtapesTotal[25] = etape25;
                tableauEtapesTotal[26] = etape26;
                tableauEtapesTotal[27] = etape27;
                tableauEtapesTotal[28] = etape28;
                tableauEtapesTotal[29] = etape29;
                tableauEtapesTotal[30] = etape30;
        /// FIN KRABI-JUNIOR
    #endif

    this->dijkstra = new Dijkstra(tableauEtapesTotal, NOMBRE_ETAPES);

    this->tableauEtapes = tableauEtapesTotal;
    this->tableauEtapes[0]->setParent(this->tableauEtapes[0]);// Evite de planter si on detecte dès la première boucle (dans le simu)

    dijkstra->setEtapeCourante(0);
    //Affichage de toutes les distances
    #ifndef ROBOTHW




    //###########################################################################################
    //                                   Générateur de distances
    // ###########################################################################################
    qDebug() << "Affichage de toutes les distances\n";

//    //Calcul nombre distances
//    int nombreDistances = 0;
//    for(int numeroEtape = 0 ; numeroEtape < NOMBRE_ETAPES ; numeroEtape++)
//    {
//        nombreDistances += this->tableauEtapes[numeroEtape]->getNbChildren();
//    }
//        qDebug() << "int tableauDistancesTotal[" << nombreDistances << "] = {";

//    // Pour chaque enfant (child) de chaque étape, afficher la distance étape - enfant
//    for(int numeroEtape = 0 ; numeroEtape < NOMBRE_ETAPES ; numeroEtape++)
//    {
//        qDebug() << "// etape " << numeroEtape << ":";
//        for(int numeroChild = 0 ; numeroChild < this->tableauEtapes[numeroEtape]->getNbChildren() ; numeroChild++)
//        {
//            qDebug() << this->dijkstra->calculDistanceDirect(this->tableauEtapes[numeroEtape], this->tableauEtapes[numeroEtape]->getChild(numeroChild)) << ", // vers etape " << (this->tableauEtapes[numeroEtape]->getChild(numeroChild)->getNumero());
//        }
//    }
//    qDebug() << "};";

    // Pour chaque étape, afficher le tableau de distances étape - enfant
    for(int numeroEtape = 0 ; numeroEtape < NOMBRE_ETAPES ; numeroEtape++)
    {
        //qDebug().nospace() << "int tableauDistances" << numeroEtape << "[" << this->tableauEtapes[numeroEtape]->getNbChildren() << "] = {";
        qDebug().nospace() << "\nint* tableauDistances" << numeroEtape << " = new int[" << this->tableauEtapes[numeroEtape]->getNbChildren() << "];";
        for(int numeroChild = 0 ; numeroChild < this->tableauEtapes[numeroEtape]->getNbChildren() ; numeroChild++)
        {
            qDebug().nospace() << "tableauDistances" << numeroEtape << "[" << numeroChild << "] = " << this->dijkstra->calculDistanceDirect(this->tableauEtapes[numeroEtape], this->tableauEtapes[numeroEtape]->getChild(numeroChild)) << "; // vers etape " << (this->tableauEtapes[numeroEtape]->getChild(numeroChild)->getNumero());
//            if(numeroChild == (this->tableauEtapes[numeroEtape]->getNbChildren()))
//            {
//                qDebug() << this->dijkstra->calculDistanceDirect(this->tableauEtapes[numeroEtape], this->tableauEtapes[numeroEtape]->getChild(numeroChild));
//                //qDebug() << this->dijkstra->calculDistanceDirect(this->tableauEtapes[numeroEtape], this->tableauEtapes[numeroEtape]->getChild(numeroChild)) << " // vers etape " << (this->tableauEtapes[numeroEtape]->getChild(numeroChild)->getNumero());
//            }
//            else
//            {
//                qDebug() << this->dijkstra->calculDistanceDirect(this->tableauEtapes[numeroEtape], this->tableauEtapes[numeroEtape]->getChild(numeroChild)) << ",";
//                //qDebug() << this->dijkstra->calculDistanceDirect(this->tableauEtapes[numeroEtape], this->tableauEtapes[numeroEtape]->getChild(numeroChild)) << ", // vers etape " << (this->tableauEtapes[numeroEtape]->getChild(numeroChild)->getNumero());
//            }
        }
        //qDebug() << "};";
        qDebug().nospace() << "this->tableauEtapes[" << numeroEtape << "]->setDistances(tableauDistances" << numeroEtape << ");";
    }
    // ###########################################################################################
    // Mettre un point d'arrêt ici pour récupérer les distances dans la sortie standard du simu
    // ###########################################################################################



#endif
    // ###########################################################################################
    //                           Code généré par le bloc ci-dessus
    // ###########################################################################################

#ifdef KRABI

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
    this->tableauEtapes[26]->setDistances(tableauDistances26);

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
#endif

    // ###########################################################################################
    //                           Fin code généré
    // ###########################################################################################

#ifdef KRABI_JR
    // Deux côtés du feu terrain milieu côté départ
    int* tableauEtapesLieesParFinirEtape3 = new int[1];
    tableauEtapesLieesParFinirEtape3[0] = 20;
    this->tableauEtapes[2]->setEtapesLieesParFinirEtape(tableauEtapesLieesParFinirEtape3);

    int* tableauEtapesLieesParFinirEtape20 = new int[1];
    tableauEtapesLieesParFinirEtape20[0] = 3;
    this->tableauEtapes[19]->setEtapesLieesParFinirEtape(tableauEtapesLieesParFinirEtape20);

    // Deux côtés du feu terrain bas côté départ
    int* tableauEtapesLieesParFinirEtape21 = new int[1];
    tableauEtapesLieesParFinirEtape21[0] = 8;
    this->tableauEtapes[20]->setEtapesLieesParFinirEtape(tableauEtapesLieesParFinirEtape21);

    int* tableauEtapesLieesParFinirEtape8 = new int[1];
    tableauEtapesLieesParFinirEtape8[0] = 21;
    this->tableauEtapes[7]->setEtapesLieesParFinirEtape(tableauEtapesLieesParFinirEtape8);

    // Deux côtés du feu terrain bas côté adversaire
//Lances
//CanonLances shootAtWill
    int* tableauEtapesLieesParFinirEtape23 = new int[1];
    tableauEtapesLieesParFinirEtape23[0] = 11;
    this->tableauEtapes[22]->setEtapesLieesParFinirEtape(tableauEtapesLieesParFinirEtape23);

    int* tableauEtapesLieesParFinirEtape11 = new int[1];
    tableauEtapesLieesParFinirEtape11[0] = 23;
    this->tableauEtapes[10]->setEtapesLieesParFinirEtape(tableauEtapesLieesParFinirEtape11);

    // Deux côtés du feu terrain milieu côté adversaire
    int* tableauEtapesLieesParFinirEtape25 = new int[1];
    tableauEtapesLieesParFinirEtape25[0] = 16;
    this->tableauEtapes[24]->setEtapesLieesParFinirEtape(tableauEtapesLieesParFinirEtape25);

    int* tableauEtapesLieesParFinirEtape16 = new int[1];
    tableauEtapesLieesParFinirEtape16[0] = 25;
    this->tableauEtapes[15]->setEtapesLieesParFinirEtape(tableauEtapesLieesParFinirEtape16);

    // Deux côtés du feu terrain haut côté adversaire
    int* tableauEtapesLieesParFinirEtape26 = new int[1];
    tableauEtapesLieesParFinirEtape26[0] = 19;
    this->tableauEtapes[25]->setEtapesLieesParFinirEtape(tableauEtapesLieesParFinirEtape26);

    int* tableauEtapesLieesParFinirEtape19 = new int[1];
    tableauEtapesLieesParFinirEtape19[0] = 26;
    this->tableauEtapes[18]->setEtapesLieesParFinirEtape(tableauEtapesLieesParFinirEtape19);

    int* tableauDistances0 = new int[2];
    tableauDistances0[0] = 300; // vers etape 1
    tableauDistances0[1] = 576; // vers etape 28
    this->tableauEtapes[0]->setDistances(tableauDistances0);

    int* tableauDistances1 = new int[2];
    tableauDistances1[0] = 300; // vers etape 0
    tableauDistances1[1] = 300; // vers etape 2
    this->tableauEtapes[1]->setDistances(tableauDistances1);

    int* tableauDistances2 = new int[2];
    tableauDistances2[0] = 300; // vers etape 1
    tableauDistances2[1] = 100; // vers etape 3
    this->tableauEtapes[2]->setDistances(tableauDistances2);

    int* tableauDistances3 = new int[2];
    tableauDistances3[0] = 100; // vers etape 2
    tableauDistances3[1] = 200; // vers etape 4
    this->tableauEtapes[3]->setDistances(tableauDistances3);

    int* tableauDistances4 = new int[4];
    tableauDistances4[0] = 200; // vers etape 3
    tableauDistances4[1] = 586; // vers etape 5
    tableauDistances4[2] = 512; // vers etape 19
    tableauDistances4[3] = 415; // vers etape 29
    this->tableauEtapes[4]->setDistances(tableauDistances4);

    int* tableauDistances5 = new int[3];
    tableauDistances5[0] = 586; // vers etape 4
    tableauDistances5[1] = 200; // vers etape 6
    tableauDistances5[2] = 415; // vers etape 29
    this->tableauEtapes[5]->setDistances(tableauDistances5);

    int* tableauDistances6 = new int[3];
    tableauDistances6[0] = 200; // vers etape 5
    tableauDistances6[1] = 100; // vers etape 7
    tableauDistances6[2] = 460; // vers etape 29
    this->tableauEtapes[6]->setDistances(tableauDistances6);

    int* tableauDistances7 = new int[3];
    tableauDistances7[0] = 100; // vers etape 6
    tableauDistances7[1] = 400; // vers etape 8
    tableauDistances7[2] = 729; // vers etape 21
    this->tableauEtapes[7]->setDistances(tableauDistances7);

    int* tableauDistances8 = new int[4];
    tableauDistances8[0] = 400; // vers etape 7
    tableauDistances8[1] = 400; // vers etape 9
    tableauDistances8[2] = 576; // vers etape 20
    tableauDistances8[3] = 460; // vers etape 21
    this->tableauEtapes[8]->setDistances(tableauDistances8);

    int* tableauDistances9 = new int[5];
    tableauDistances9[0] = 400; // vers etape 8
    tableauDistances9[1] = 400; // vers etape 10
    tableauDistances9[2] = 901; // vers etape 20
    tableauDistances9[3] = 460; // vers etape 21
    tableauDistances9[4] = 623; // vers etape 23
    this->tableauEtapes[9]->setDistances(tableauDistances9);

    int* tableauDistances10 = new int[2];
    tableauDistances10[0] = 400; // vers etape 9
    tableauDistances10[1] = 100; // vers etape 11
    this->tableauEtapes[10]->setDistances(tableauDistances10);

    int* tableauDistances11 = new int[3];
    tableauDistances11[0] = 100; // vers etape 10
    tableauDistances11[1] = 200; // vers etape 12
    tableauDistances11[2] = 460; // vers etape 30
    this->tableauEtapes[11]->setDistances(tableauDistances11);

    int* tableauDistances12 = new int[3];
    tableauDistances12[0] = 200; // vers etape 11
    tableauDistances12[1] = 586; // vers etape 13
    tableauDistances12[2] = 415; // vers etape 30
    this->tableauEtapes[12]->setDistances(tableauDistances12);

    int* tableauDistances13 = new int[3];
    tableauDistances13[0] = 586; // vers etape 12
    tableauDistances13[1] = 200; // vers etape 14
    tableauDistances13[2] = 415; // vers etape 30
    this->tableauEtapes[13]->setDistances(tableauDistances13);

    int* tableauDistances14 = new int[3];
    tableauDistances14[0] = 200; // vers etape 13
    tableauDistances14[1] = 100; // vers etape 15
    tableauDistances14[2] = 460; // vers etape 30
    this->tableauEtapes[14]->setDistances(tableauDistances14);

    int* tableauDistances15 = new int[2];
    tableauDistances15[0] = 100; // vers etape 14
    tableauDistances15[1] = 300; // vers etape 16
    this->tableauEtapes[15]->setDistances(tableauDistances15);

    int* tableauDistances16 = new int[3];
    tableauDistances16[0] = 300; // vers etape 15
    tableauDistances16[1] = 542; // vers etape 17@em6.club.resel.fr:gitRobotique.git
    tableauDistances16[2] = 715; // vers etape 25
    this->tableauEtapes[16]->setDistances(tableauDistances16);

    int* tableauDistances17 = new int[3];
    tableauDistances17[0] = 542; // vers etape 16
    tableauDistances17[1] = 300; // vers etape 18
    tableauDistances17[2] = 650; // vers etape 24
    this->tableauEtapes[17]->setDistances(tableauDistances17);

    int* tableauDistances18 = new int[2];
    tableauDistances18[0] = 300; // vers etape 17
    tableauDistances18[1] = 300; // vers etape 26
    this->tableauEtapes[18]->setDistances(tableauDistances18);

    int* tableauDistances19 = new int[4];
    tableauDistances19[0] = 512; // vers etape 4
    tableauDistances19[1] = 424; // vers etape 20
    tableauDistances19[2] = 200; // vers etape 28
    tableauDistances19[3] = 300; // vers etape 29
    this->tableauEtapes[19]->setDistances(tableauDistances19);

    int* tableauDistances20 = new int[5];
    tableauDistances20[0] = 576; // vers etape 8
    tableauDistances20[1] = 901; // vers etape 9
    tableauDistances20[2] = 424; // vers etape 19
    tableauDistances20[3] = 600; // vers etape 21
    tableauDistances20[4] = 300; // vers etape 29
    this->tableauEtapes[20]->setDistances(tableauDistances20);

    int* tableauDistances21 = new int[6];
    tableauDistances21[0] = 729; // vers etape 7
    tableauDistances21[1] = 460; // vers etape 8
    tableauDistances21[2] = 460; // vers etape 9
    tableauDistances21[3] = 600; // vers etape 20
    tableauDistances21[4] = 600; // vers etape 22
    tableauDistances21[5] = 360; // vers etape 23
    this->tableauEtapes[21]->setDistances(tableauDistances21);

    int* tableauDistances22 = new int[4];
    tableauDistances22[0] = 600; // vers etape 21
    tableauDistances22[1] = 360; // vers etape 23
    tableauDistances22[2] = 424; // vers etape 24
    tableauDistances22[3] = 300; // vers etape 30
    this->tableauEtapes[22]->setDistances(tableauDistances22);

    int* tableauDistances23 = new int[4];
    tableauDistances23[0] = 623; // vers etape 9
    tableauDistances23[1] = 360; // vers etape 21
    tableauDistances23[2] = 360; // vers etape 22
    tableauDistances23[3] = 200; // vers etape 27
    this->tableauEtapes[23]->setDistances(tableauDistances23);

    int* tableauDistances24 = new int[4];
    tableauDistances24[0] = 650; // vers etape 17
    tableauDistances24[1] = 424; // vers etape 22
    tableauDistances24[2] = 424; // vers etape 25
    tableauDistances24[3] = 300; // vers etape 30
    this->tableauEtapes[24]->setDistances(tableauDistances24);

    int* tableauDistances25 = new int[3];
    tableauDistances25[0] = 715; // vers etape 16
    tableauDistances25[1] = 424; // vers etape 24
    tableauDistances25[2] = 360; // vers etape 27
    this->tableauEtapes[25]->setDistances(tableauDistances25);

    int* tableauDistances26 = new int[2];
    tableauDistances26[0] = 300; // vers etape 18
    tableauDistances26[1] = 550; // vers etape 27
    this->tableauEtapes[26]->setDistances(tableauDistances26);

    int* tableauDistances27 = new int[3];
    tableauDistances27[0] = 200; // vers etape 23
    tableauDistances27[1] = 360; // vers etape 25
    tableauDistances27[2] = 550; // vers etape 26
    this->tableauEtapes[27]->setDistances(tableauDistances27);

    int* tableauDistances28 = new int[2];
    tableauDistances28[0] = 576; // vers etape 0
    tableauDistances28[1] = 200; // vers etape 19
    this->tableauEtapes[28]->setDistances(tableauDistances28);

    int* tableauDistances29 = new int[5];
    tableauDistances29[0] = 415; // vers etape 4
    tableauDistances29[1] = 415; // vers etape 5
    tableauDistances29[2] = 460; // vers etape 6
    tableauDistances29[3] = 300; // vers etape 19
    tableauDistances29[4] = 300; // vers etape 20
    this->tableauEtapes[29]->setDistances(tableauDistances29);

    int* tableauDistances30 = new int[6];
    tableauDistances30[0] = 460; // vers etape 11
    tableauDistances30[1] = 415; // vers etape 12
    tableauDistances30[2] = 415; // vers etape 13
    tableauDistances30[3] = 460; // vers etape 14
    tableauDistances30[4] = 300; // vers etape 22
    tableauDistances30[5] = 300; // vers etape 24
    this->tableauEtapes[30]->setDistances(tableauDistances30);
#endif


}

int StrategieV3::update()
{

    this->actionEtape[this->etapeEnCours]->reset();
    this->actionGoto[this->etapeEnCours].reset();



    //Si on est en train d'éviter, on revient à l'étape précédente, et on marque l'étape comme à éviter
    if(this->avoiding)
    {
        this->tableauEtapes[this->etapeEnCours]->robotVu();
        //this->tableauEtapes[this->etapeEnCours]->setState(-2);
        this->tableauEtapes[etapeEnCours]->getParent()->setParent(this->tableauEtapes[this->etapeEnCours]);
        this->etapeEnCours = this->tableauEtapes[etapeEnCours]->getParent()->getNumero();



        //On recalcul les distances par rapport à l'étape où l'on vient d'arriver
        dijkstra->setEtapeCourante(this->etapeEnCours);

        if(this->enTrainEviterReculant)
        {
            this->enTrainEviterReculant = false;
            this->enTrainEviterAvancant = true;
            actionGoto[etapeEnCours].setGoBack(false);
            //actionEtape[etapeEnCours]->setGoBack(false);
        }
        else
        {
            this->enTrainEviterReculant = true;
            this->enTrainEviterAvancant = false;
            actionGoto[etapeEnCours].setGoBack(true);
            //actionEtape[etapeEnCours]->setGoBack(true);
        }

        StrategieV2::addTemporaryAction(&actionGoto[etapeEnCours]);
        //StrategieV2::addTemporaryAction(actionEtape[etapeEnCours]);
        //dijkstra->setEtapeCourante((this->tableauEtapes[this->etapeEnCours]->getParent()->getNumero()));
        if(dijkstra->run() != 0)
        {
            // Si run renvoit autre chose que 0, c'est que l'étape en cours a changée.
            // Cela arrive pour débloquer le robot
            //Etape* ancienneEtape = this->tableauEtapes[this->etapeEnCours];
            //this->etapeEnCours = this->tableauEtapes[this->etapeEnCours]->getParent()->getNumero();
            this->actionEtape[this->etapeEnCours]->reset();
            this->actionGoto[this->etapeEnCours].reset();
        }

        //On retourne à l'étape intermédiaire précédente, en marche arrière

        this->avoiding = false;
        statusStrat=1;
    }
    else
    {
        //On reset toute les directions à aller en marche avant
        for(int i = 0 ; i < NOMBRE_ETAPES ; i++)
        {
            actionGoto[i].setGoBack(false);
            actionEtape[i]->setGoBack(false);
        }
        this->enTrainEviterReculant = false;
        this->enTrainEviterAvancant = false;

        if(this->statusStrat==2)//Si on vient d'arriver à une étape intermédiare
        {
            this->updateIntermedaire();
        }
        else//Sinon, statusStrat==1, et il faut donc choisir un nouvel objectif
        {
            // Si on n'était pas en train d'éviter
            if(!(enTrainEviterReculant || enTrainEviterAvancant))
            {
                //L'objectif qu'on vient de remplir est maintenant un simple point de passage
                this->tableauEtapes[this->etapeEnCours]->finir();
                //Idem pour les autres étapes correspondant au même objectif
                for(int etapeLiee = 0 ; etapeLiee < this->tableauEtapes[this->etapeEnCours]->getNombreEtapesLieesParFinirEtape() ; etapeLiee++)
                {
                    int numeroEtapeLiee = this->tableauEtapes[this->etapeEnCours]->getEtapesLieesParFinirEtape()[etapeLiee];
                    this->tableauEtapes[numeroEtapeLiee]->finir();
                }

                //Mise à jour du stock
                if(this->tableauEtapes[this->etapeEnCours]->getEtapeType() == Etape::FRUIT)
                {
                    nombreFruitsTransporte++;
                    this->tableauEtapes[this->etapeEnCours]->setEtapeType(Etape::POINT_PASSAGE);
                }
                if(this->tableauEtapes[this->etapeEnCours]->getEtapeType() == Etape::FEU_MINI_BRAS)
                {
                    this->tableauEtapes[this->etapeEnCours]->setEtapeType(Etape::POINT_PASSAGE);
                }
                else if(this->tableauEtapes[this->etapeEnCours]->getEtapeType() == Etape::FEU)
                {
                    this->tableauEtapes[this->etapeEnCours]->setEtapeType(Etape::POINT_PASSAGE);
                }
                else if(this->tableauEtapes[this->etapeEnCours]->getEtapeType() == Etape::DEPOSE_FRUIT)
                {
                    nombreFruitsTransporte = 0;
                }
                if(this->tableauEtapes[this->etapeEnCours]->getEtapeType() == Etape::FEU_COTE)
                {
                    this->tableauEtapes[this->etapeEnCours]->setEtapeType(Etape::POINT_PASSAGE);
#ifndef ROBOTHW
                    qDebug() << "feu coté transformé en point de passage";
#endif
                }
                else if(this->tableauEtapes[this->etapeEnCours]->getEtapeType() == Etape::DEPOSE_FEU)
                {
                    nombreFeuxTransporte--;
                }
                else if(this->tableauEtapes[this->etapeEnCours]->getEtapeType() == Etape::TORCHE_MOBILE)
                {
                    this->tableauEtapes[this->etapeEnCours]->setEtapeType(Etape::POINT_PASSAGE);
                }
                else if(this->tableauEtapes[this->etapeEnCours]->getEtapeType() == Etape::FRESQUE)
                {
                    nombreFresquesTransporte = 0;
                }
                else if(this->tableauEtapes[this->etapeEnCours]->getEtapeType() == Etape::TORCHE_MOBILE)
                {
                    //nombreFeuxTransporte++;
                    this->tableauEtapes[this->etapeEnCours]->setEtapeType(Etape::POINT_PASSAGE);
#ifndef ROBOTHW
                    qDebug() << "Torche mobile transformée en point de passage";
#endif
                }
                else if(this->tableauEtapes[this->etapeEnCours]->getEtapeType() == Etape::TIR_MAMMOUTH)
                {
                    nombreLancesTransporte -= ((TireLances*)(this->actionEtape[this->etapeEnCours]))->getNumberDone();//nombreLancesTransporte--;
                }
                dijkstra->updateNombreElementsTransportes(nombreFeuxTransporte, nombreFruitsTransporte, nombreFresquesTransporte, nombreLancesTransporte, nombreFiletTransporte);
            }


            //Mise à jour du score correspondant à chaque étape
            //CETTE PARTIE EST A AMELIORER
            //on pourrait prendre en compte :
            //le fait le transporter un feu, ce qui active les objectifs de dépose done
            //le temps que prend chaque action
            //le temps restant done
            //la trajectoire de notre autre robot
            //...
            //C'est aussi utilisé pour savoir si on est dans un sous-graphe sans objectif,
            //et qu'il faut oublier qu'on a vu des robots
            int scoreTypeEtape = 0;
            float modificateurTemporel = 1.f;
            int score = 0;
            bool resteDesChosesAFaire = false;
            for(int i = 0 ; i < NOMBRE_ETAPES ; i++)
            {
                scoreTypeEtape = 0;

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
                    scoreTypeEtape = 1000;// * this->nombreFruitsTransporte;
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

                    scoreTypeEtape = (((TireLances*)(this->actionEtape[i]))->getNumberDone() >= ((TireLances*)(this->actionEtape[i]))->getNumber() ) ? 0 : 10000 * this->nombreLancesTransporte;
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

                if(scoreTypeEtape)
                {
                    resteDesChosesAFaire = true;

                }

                this->tableauEtapes[i]->setScore(scoreTypeEtape);
            }

            // S'il n'y a plus d'objectif dans tout le graphe, on se replit vers une position où on ne bloque pas l'adversaire.
            // Sinon, il y a risque de prendre un avertissement pour anti-jeu (évité de peu pour le premier match de Krabi 2014)
            if(!resteDesChosesAFaire)
            {
                if(this->etapeEnCours == 25)
                {
                    this->statusStrat=-1;//Plus rien à faire, on passe à l'action suivante de stratégieV2
                    return this->statusStrat;
                }
                else
                {
                    this->tableauEtapes[25]->setScore(1000);
                }
            }

            //On recalcul les distances par rapport à l'étape où l'on vient d'arriver
            dijkstra->setEtapeCourante(this->etapeEnCours);
            if(dijkstra->run() != 0)
            {
                // Si run renvoit autre chose que 0, c'est que l'étape en cours a changée.
                // Cela arrive pour débloquer le robot
                //Etape* ancienneEtape = this->tableauEtapes[this->etapeEnCours];
                //this->etapeEnCours = this->tableauEtapes[this->etapeEnCours]->getParent()->getNumero();
                this->actionEtape[this->etapeEnCours]->reset();
            }

            //On sélectionne l'objectif le plus prometteur : pas trop loin et qui rapporte
            int meilleurEtape = -1;
            int scoreMaxi = -100000;

            //int scoreTypeEtape = 0;
            for(int i = 0 ; i < NOMBRE_ETAPES ; i++)
            {
                scoreTypeEtape = this->tableauEtapes[i]->getScore();
                score = modificateurTemporel*(10000-this->tableauEtapes[i]->getDistance() + scoreTypeEtape);
                if((scoreMaxi < score) && scoreTypeEtape && (this->tableauEtapes[i]->getDistance() != -1))
                {
                    scoreMaxi = score;
                    meilleurEtape = i;
                }
            }

            if(meilleurEtape==-1)
            {
                if(this->etapeEnCours == 25)
                {
                    this->statusStrat=-1;//Plus rien à faire, on passe à l'action suivante de stratégieV2
                    return this->statusStrat;
                }
                else
                {
                    meilleurEtape = 25;
                }
            }

            //Si c'est un fruit, on considère déjà qu'on l'a attrapé
            if(this->tableauEtapes[meilleurEtape]->getEtapeType()==Etape::DEPOSE_FRUIT)
            {
                this->nombreFruitsTransporte++;
            }
#ifndef ROBOTHW
                    qDebug() << "nombreFruitsTransporte : " << this->nombreFruitsTransporte;
#endif

            this->goal = meilleurEtape;
            this->statusStrat = 2;//Jusqu'à preuve du contraire, la prochaine étape est une étape intermédiaire
            this->updateIntermedaire();//On y va
        }
    }
    return this->statusStrat;
}

void StrategieV3::resetEverything(){
    for(int i = 0 ; i < 10 ; i++){
        this->tableauEtapes[i]->setState(0);
    }
}

void StrategieV3::collisionAvoided(){
    this->avoiding = true;
}


void StrategieV3::updateIntermedaire()
{
    //Note : le parent d'une étape est l'étape le rapprochant le plus de l'étape d'origine
    //Ainsi, le parent du parent du parent... de n'importe quelle étape est l'étape d'origine
    //(sauf peut être le parent de l'étape d'origine, mais on s'en fout

    #ifndef ROBOTHW
        qDebug() << "updateIntermedaire\n";
    #endif
    int etapeOuOnVientDArriver = this->etapeEnCours;
    this->etapeEnCours = this->goal;
    Etape* toto = this->tableauEtapes[1];
    Etape* toto2 = this->tableauEtapes[2];

    // Si la prochaine étape est le goal, alors au prochain update il faudra trouver un nouvel objectif -> status = 1;
    if(((this->tableauEtapes[this->etapeEnCours]->getParent()->getNumero())) == etapeOuOnVientDArriver)
    {
        #ifndef ROBOTHW
            qDebug() << "la prochaine étape est le goal\n";
        #endif
        this->statusStrat = 1;
    }

    //On cherche l'étape suivant vers l'etape - but
    while(((this->tableauEtapes[this->etapeEnCours]->getParent()->getNumero())) != etapeOuOnVientDArriver)
    {
        #ifndef ROBOTHW
        qDebug() << "On cherche l'étape suivant vers l'etape - but" << this->etapeEnCours << "\n";
        #endif
        this->etapeEnCours = ((this->tableauEtapes[this->etapeEnCours]->getParent()->getNumero()));
    }

    if(this->statusStrat == 1)
    {
        //On réalise l'action de l'étape - but
        StrategieV2::addTemporaryAction(actionEtape[this->etapeEnCours]);
    }
    else
    {
        //On ajoute l'action d'aller en ligne droite vers cette étape intermédiaire
        StrategieV2::addTemporaryAction(&actionGoto[this->etapeEnCours]);
    }
}


#ifndef ROBOTHW
void StrategieV3::paint(QPainter* p)
{
    for(int numeroEtape = 0 ; numeroEtape<NOMBRE_ETAPES ; numeroEtape++)
    {
        QPoint position = QPoint(
        this->tableauEtapes[numeroEtape]->getPosition().getX(),
        -(this->tableauEtapes[numeroEtape]->getPosition().getY()));

        // Affichage des étapes
        p->setPen(colorEtapesIntermediaires);//"orange"));
        p->setBrush(colorEtapesIntermediaires);//"orange"));
        p->setOpacity(1.0f);
        p->drawEllipse(position,10,-10);

        // Etape - but en surbrillance
        if(numeroEtape == this->goal)
        {
            p->setPen(colorEtapeGoal);
            p->setBrush(colorEtapeGoal);
            p->setOpacity(1.0f);
            p->drawEllipse(position,30,-30);
        }

        // Etape actuelle en surbrillance
        if(numeroEtape == this->etapeEnCours)
        {
            p->setPen(colorEtapesIntermediaires);
            p->setBrush(colorEtapesIntermediaires);
            p->setOpacity(1.0f);
            p->drawEllipse(position,25,-25);
        }

        // Etapes où on a vu un robot
        if(this->tableauEtapes[numeroEtape]->aEviter())
        {
            p->setPen(colorEtapesRobotVu);
            p->setBrush(colorEtapesRobotVu);
            p->setOpacity(1.0f);
            p->drawEllipse(position,20,-20);
        }

        //Affichage du numéro des étapes
        QFont font;
        font.setPixelSize(50);
        p->setFont(font);
        p->setOpacity(1);
        p->setPen(colorTexteEtapes);
        p->setBrush(colorTexteEtapes);
        p->drawText(position, QString::number(this->tableauEtapes[numeroEtape]->getNumero()));

        // Affichage des liaisons entre étapes
        for(int numeroChild = 0 ; numeroChild < this->tableauEtapes[numeroEtape]->getNbChildren() ; numeroChild++)
        {
//            Affichages de liaisons
//            QPoint positionChild = QPoint(
//            this->tableauEtapes[numeroEtape]->getChildren()[numeroChild]->getPosition().getX(),
//            -(this->tableauEtapes[numeroEtape]->getChildren()[numeroChild]->getPosition().getY()));

            // Affichage des demi-liaisons, pour mieux voir les liens mono-directionnels
            QPoint positionChild = QPoint(
            (this->tableauEtapes[numeroEtape]->getChildren()[numeroChild]->getPosition().getX()+this->tableauEtapes[numeroEtape]->getPosition().getX())/2,
            -((this->tableauEtapes[numeroEtape]->getChildren()[numeroChild]->getPosition().getY()+this->tableauEtapes[numeroEtape]->getPosition().getY())/2));
            p->setOpacity(0.5f);
            p->setPen(colorLiaisonsEtapes);
            p->setBrush(colorLiaisonsEtapes);
            p->drawLine(position.x(), position.y(),positionChild.x(),positionChild.y());
            p->drawEllipse(position,10,-10);
        }

        //Affichage du type d'étape
        QPoint positionTypeEtape = QPoint(
        this->tableauEtapes[numeroEtape]->getPosition().getX(),
        -(this->tableauEtapes[numeroEtape]->getPosition().getY() - 50));
        p->setFont(font);
        p->setOpacity(1);
        p->setPen(colorTexteEtapes);
        p->setBrush(colorTexteEtapes);
        p->drawText(positionTypeEtape, QString::number(this->tableauEtapes[numeroEtape]->getEtapeType()));
    }
    p->setOpacity(1);
}
#endif
