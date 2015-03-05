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
     ///KRABI !!!
      #ifdef KRABI
    this->nombreFruitsTransporte = 0;
    this->nombreFeuxTransporte = 0;
    this->nombreFresquesTransporte = 2;
    this->nombreLancesTransporte = 6;


        actionGoto[0] = ActionGoTo(Position(200, 1850, isBlue), false);
        actionGoto[1] = ActionGoTo(Position(200, 1500, isBlue), false);
        actionGoto[2] = ActionGoTo(Position(700, 1500, isBlue), false);
        actionGoto[3] = ActionGoTo(Position(1300, 1500, isBlue), false);
        actionGoto[4] = ActionGoTo(Position(1300, 1850, isBlue), false);
        actionGoto[5] = ActionGoTo(Position(1150, 1100, isBlue), false);
        actionGoto[6] = ActionGoTo(Position(1150, 800, isBlue), false);
        actionGoto[7] = ActionGoTo(Position(1500, 1500, isBlue), false);
        actionGoto[8] = ActionGoTo(Position(1500, 1850, isBlue), false);
        actionGoto[9] = ActionGoTo(Position(1700, 1500, isBlue), false);
        actionGoto[10] = ActionGoTo(Position(1700, 1850, isBlue), false);
        actionGoto[11] = ActionGoTo(Position(1850, 1100, isBlue), false);
        actionGoto[12] = ActionGoTo(Position(1850, 800, isBlue), false);
        actionGoto[13] = ActionGoTo(Position(1400, 1300, isBlue), false);
        actionGoto[14] = ActionGoTo(Position(1600, 1300, isBlue), false);
        actionGoto[15] = ActionGoTo(Position(1400, 600, isBlue), false);
        actionGoto[16] = ActionGoTo(Position(1600, 600, isBlue), false);
        actionGoto[17] = ActionGoTo(Position(2300, 1500, isBlue), false);
        actionGoto[18] = ActionGoTo(Position(400, 900, isBlue), false);
        actionGoto[19] = ActionGoTo(Position(900, 400, isBlue), false);
        actionGoto[20] = ActionGoTo(Position(2100, 400, isBlue), false);
        actionGoto[21] = ActionGoTo(Position(2600, 900, isBlue), false);

        actionFresque[0] = Fresque(isBlue, Position(1300, 1850, isBlue));
        actionFresque[1] = Fresque(isBlue, Position(1500, 1850, isBlue));
        actionFresque[2] = Fresque(isBlue, Position(1700, 1850, isBlue));

        actionEtape[0] = &actionGoto[0];
        actionEtape[1] = &actionGoto[1];
        actionEtape[2] = &actionGoto[2];
        actionEtape[3] = &actionGoto[3];
        actionEtape[4] = &actionFresque[0];//&actionGoto[4];
        actionEtape[5] = &actionGoto[5];
        actionEtape[6] = &actionGoto[6];
        actionEtape[7] = &actionGoto[7];
        actionEtape[8] = &actionFresque[1];//&actionGoto[8];
        actionEtape[9] = &actionGoto[9];
        actionEtape[10] = &actionFresque[2];//&actionGoto[10];
        actionEtape[11] = &actionGoto[11];
        actionEtape[12] = &actionGoto[12];
        actionEtape[13] = &actionGoto[13];
        actionEtape[14] = &actionGoto[14];
        actionEtape[15] = &actionGoto[15];
        actionEtape[16] = &actionGoto[16];
        actionEtape[17] = &actionGoto[17];
        actionEtape[18] = &actionGoto[18];
        actionEtape[19] = &actionGoto[19];
        actionEtape[20] = &actionGoto[20];
        actionEtape[21] = &actionGoto[21];


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

        Etape** tableauEtapes1 = new Etape*[1];
        Etape** tableauEtapes2 = new Etape*[3];
        Etape** tableauEtapes3 = new Etape*[4];
        Etape** tableauEtapes4 = new Etape*[6];
        Etape** tableauEtapes5 = new Etape*[1];
        Etape** tableauEtapes6 = new Etape*[4];
        Etape** tableauEtapes7 = new Etape*[3];
        Etape** tableauEtapes8 = new Etape*[5];
        Etape** tableauEtapes9 = new Etape*[1];
        Etape** tableauEtapes10 = new Etape*[6];
        Etape** tableauEtapes11 = new Etape*[1];
        Etape** tableauEtapes12 = new Etape*[4];
        Etape** tableauEtapes13 = new Etape*[3];
        Etape** tableauEtapes14 = new Etape*[5];
        Etape** tableauEtapes15 = new Etape*[5];
        Etape** tableauEtapes16 = new Etape*[3];
        Etape** tableauEtapes17 = new Etape*[3];
        Etape** tableauEtapes18 = new Etape*[3];
        Etape** tableauEtapes19 = new Etape*[3];
        Etape** tableauEtapes20 = new Etape*[4];
        Etape** tableauEtapes21 = new Etape*[4];
        Etape** tableauEtapes22 = new Etape*[2];

        //arguments : Position, tableau des etapes liées, nombre d'étapes liées, numéro de l'étape, type d'étape, état de l'étape, nombreEtapesLieesParFinirEtape
        etape1 = new Etape(Position(200, 1850, isBlue), tableauEtapes1, 1, 1, Etape::DEPART, -1, 0);
        etape2 = new Etape(Position(200, 1500, isBlue), tableauEtapes2, 3, 2, Etape::POINT_PASSAGE,-1, 0);
        etape3 = new Etape(Position(700, 1500, isBlue), tableauEtapes3, 4, 3, Etape::TIR_MAMMOUTH,-1, 0);
        etape4 = new Etape(Position(1300, 1500, isBlue), tableauEtapes4, 6, 4, Etape::POINT_PASSAGE,-1, 0);
        //etape5 = new Etape(Position(1300, 1850, isBlue), tableauEtapes5, 1, 5, Etape::FRESQUE,-1, 0);
        etape5 = new Etape(Position(1300, 1600, isBlue), tableauEtapes5, 1, 5, Etape::FRESQUE,-1, 0);
        etape6 = new Etape(Position(1150, 1100, isBlue), tableauEtapes6, 4, 6, Etape::TORCHE_MOBILE,-1, 0);
        etape7 = new Etape(Position(1150, 800, isBlue), tableauEtapes7, 3, 7, Etape::TORCHE_MOBILE,-1, 0);
        etape8 = new Etape(Position(1500, 1500, isBlue), tableauEtapes8, 5, 8, Etape::POINT_PASSAGE,-1, 0);
        //etape9 = new Etape(Position(1500, 1850, isBlue), tableauEtapes9, 1, 9, Etape::FRESQUE,-1, 0);
        etape9 = new Etape(Position(1500, 1600, isBlue), tableauEtapes9, 1, 9, Etape::FRESQUE,-1, 0);
        etape10 = new Etape(Position(1700, 1500, isBlue), tableauEtapes10, 6, 10, Etape::POINT_PASSAGE,-1, 0);
        //etape11 = new Etape(Position(1700, 1850, isBlue), tableauEtapes11, 1, 11, Etape::FRESQUE, -1, 0);
        etape11 = new Etape(Position(1700, 1600, isBlue), tableauEtapes11, 1, 11, Etape::FRESQUE, -1, 0);
        etape12 = new Etape(Position(1850, 1100, isBlue), tableauEtapes12, 4, 12, Etape::TORCHE_MOBILE, -1, 0);
        etape13 = new Etape(Position(1850, 800, isBlue), tableauEtapes13, 3, 13, Etape::TORCHE_MOBILE, -1, 0);
        etape14 = new Etape(Position(1400, 1300, isBlue), tableauEtapes14, 5, 14, Etape::POINT_PASSAGE, -1, 0);
        etape15 = new Etape(Position(1600, 1300, isBlue), tableauEtapes15, 5, 15, Etape::POINT_PASSAGE, -1, 0);
        etape16 = new Etape(Position(1400, 600, isBlue), tableauEtapes16, 3, 16, Etape::POINT_PASSAGE, -1, 0);
        etape17 = new Etape(Position(1600, 600, isBlue), tableauEtapes17, 3, 17, Etape::POINT_PASSAGE, -1, 0);
        etape18 = new Etape(Position(2300, 1500, isBlue), tableauEtapes18, 3, 18, Etape::TIR_MAMMOUTH, -1, 0);
        etape19 = new Etape(Position(400, 900, isBlue), tableauEtapes19, 3, 19, Etape::FEU, -1, 0);
        etape20 = new Etape(Position(900, 400, isBlue), tableauEtapes20, 4, 20, Etape::FEU, -1, 0);//1);
        etape21 = new Etape(Position(2100, 400, isBlue), tableauEtapes21, 4, 21, Etape::FEU, -1, 0);//1);
        etape22 = new Etape(Position(2600, 900, isBlue), tableauEtapes22, 2, 22, Etape::FEU, -1, 0);




        tableauEtapes1[0] = etape2;

        tableauEtapes2[0] = etape1;
        tableauEtapes2[1] = etape3;
        tableauEtapes2[2] = etape19;

        tableauEtapes3[0] = etape2;
        tableauEtapes3[1] = etape4;
        tableauEtapes3[2] = etape6;
        tableauEtapes3[3] = etape19;

        tableauEtapes4[0] = etape3;
        tableauEtapes4[1] = etape5;
        tableauEtapes4[2] = etape6;
        tableauEtapes4[3] = etape8;
        tableauEtapes4[4] = etape14;
        tableauEtapes4[5] = etape15;

        tableauEtapes5[0] = etape4;

        tableauEtapes6[0] = etape3;
        tableauEtapes6[1] = etape4;
        tableauEtapes6[2] = etape7;
        tableauEtapes6[3] = etape14;

        tableauEtapes7[0] = etape6;
        tableauEtapes7[1] = etape16;
        tableauEtapes7[2] = etape20;

        tableauEtapes8[0] = etape4;
        tableauEtapes8[1] = etape9;
        tableauEtapes8[2] = etape10;
        tableauEtapes8[3] = etape14;
        tableauEtapes8[4] = etape15;

        tableauEtapes9[0] = etape8;

        tableauEtapes10[0] = etape8;
        tableauEtapes10[1] = etape11;
        tableauEtapes10[2] = etape12;
        tableauEtapes10[3] = etape14;
        tableauEtapes10[4] = etape15;
        tableauEtapes10[5] = etape18;

        tableauEtapes11[0] = etape10;

        tableauEtapes12[0] = etape10;
        tableauEtapes12[1] = etape13;
        tableauEtapes12[2] = etape15;
        tableauEtapes12[3] = etape18;

        tableauEtapes13[0] = etape12;
        tableauEtapes13[1] = etape17;
        tableauEtapes13[2] = etape21;

        tableauEtapes14[0] = etape4;
        tableauEtapes14[1] = etape6;
        tableauEtapes14[2] = etape8;
        tableauEtapes14[3] = etape10;
        tableauEtapes14[4] = etape15;

        tableauEtapes15[0] = etape4;
        tableauEtapes15[1] = etape8;
        tableauEtapes15[2] = etape10;
        tableauEtapes15[3] = etape12;
        tableauEtapes15[4] = etape14;

        tableauEtapes16[0] = etape7;
        tableauEtapes16[1] = etape17;
        tableauEtapes16[2] = etape20;

        tableauEtapes17[0] = etape13;
        tableauEtapes17[1] = etape16;
        tableauEtapes17[2] = etape21;

        tableauEtapes18[0] = etape10;
        tableauEtapes18[1] = etape12;
        tableauEtapes18[2] = etape22;

        tableauEtapes19[0] = etape2;
        tableauEtapes19[1] = etape3;
        tableauEtapes19[2] = etape20;

        tableauEtapes20[0] = etape7;
        tableauEtapes20[1] = etape16;
        tableauEtapes20[2] = etape19;
        tableauEtapes20[3] = etape21;

        tableauEtapes21[0] = etape13;
        tableauEtapes21[1] = etape17;
        tableauEtapes21[2] = etape20;
        tableauEtapes21[3] = etape22;

        tableauEtapes22[0] = etape18;
        tableauEtapes22[1] = etape21;

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

        Etape** tableauEtapesTotal = new Etape*[22];
        tableauEtapesTotal[0] = etape1;
        tableauEtapesTotal[1] = etape2;
        tableauEtapesTotal[2] = etape3;
        tableauEtapesTotal[3] = etape4;
        tableauEtapesTotal[4] = etape5;
        tableauEtapesTotal[5] = etape6 ;
        tableauEtapesTotal[6] = etape7 ;
        tableauEtapesTotal[7] = etape8 ;
        tableauEtapesTotal[8] = etape9 ;
        tableauEtapesTotal[9] = etape10;
        tableauEtapesTotal[10] = etape11;
        tableauEtapesTotal[11] = etape12;
        tableauEtapesTotal[12] = etape13;
        tableauEtapesTotal[13] = etape14;
        tableauEtapesTotal[14] = etape15;
        tableauEtapesTotal[15] = etape16;
        tableauEtapesTotal[16] = etape17;
        tableauEtapesTotal[17] = etape18;
        tableauEtapesTotal[18] = etape19;
        tableauEtapesTotal[19] = etape20;
        tableauEtapesTotal[20] = etape21;
        tableauEtapesTotal[21] = etape22;
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
                actionEtape[17] = &actionGoto[17];
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
                Etape* etape31;

                Etape** tableauEtapes1 = new Etape*[2];
                Etape** tableauEtapes2 = new Etape*[2];
                Etape** tableauEtapes3 = new Etape*[2];
                Etape** tableauEtapes4 = new Etape*[2];
                Etape** tableauEtapes5 = new Etape*[4];
                Etape** tableauEtapes6 = new Etape*[3];
                Etape** tableauEtapes7 = new Etape*[3];
                Etape** tableauEtapes8 = new Etape*[3];
                Etape** tableauEtapes9 = new Etape*[4];
                Etape** tableauEtapes10 = new Etape*[5];
                Etape** tableauEtapes11 = new Etape*[2];
                Etape** tableauEtapes12 = new Etape*[3];
                Etape** tableauEtapes13 = new Etape*[3];
                Etape** tableauEtapes14 = new Etape*[3];
                Etape** tableauEtapes15 = new Etape*[3];
                Etape** tableauEtapes16 = new Etape*[2];
                Etape** tableauEtapes17 = new Etape*[3];
                Etape** tableauEtapes18 = new Etape*[3];
                Etape** tableauEtapes19 = new Etape*[2];
                Etape** tableauEtapes20 = new Etape*[4];
                Etape** tableauEtapes21 = new Etape*[5];
                Etape** tableauEtapes22 = new Etape*[6];
                Etape** tableauEtapes23 = new Etape*[4];
                Etape** tableauEtapes24 = new Etape*[4];
                Etape** tableauEtapes25 = new Etape*[4];
                Etape** tableauEtapes26 = new Etape*[3];
                Etape** tableauEtapes27 = new Etape*[2];
                Etape** tableauEtapes28 = new Etape*[3];
                Etape** tableauEtapes29 = new Etape*[2];
                Etape** tableauEtapes30 = new Etape*[5];
                Etape** tableauEtapes31 = new Etape*[6];

                etape1 = new Etape(Position(185, 1500, isBlue), tableauEtapes1, 2, 1, Etape::DEPART, -1, 0);
                etape2 = new Etape(Position(185, 1200, isBlue), tableauEtapes2, 2, 2, Etape::FEU_COTE_NOTRE_COULEUR_FACE_EXTERIEUR, -1, 0);
                etape3 = new Etape(Position(185, 900, isBlue), tableauEtapes3, 2, 3, Etape::FEU, -1, 1);
                etape4 = new Etape(Position(185, 800, isBlue), tableauEtapes4, 2, 4, Etape::FRUIT, -1, 0);
                etape5 = new Etape(Position(185, 600, isBlue), tableauEtapes5, 4, 5, Etape::FRUIT, -1, 0);
                etape6 = new Etape(Position(600, 185, isBlue), tableauEtapes6, 3, 6, Etape::FRUIT, -1, 0);
                etape7 = new Etape(Position(800, 185, isBlue), tableauEtapes7, 3, 7, Etape::FRUIT, -1, 0);
                etape8 = new Etape(Position(900, 185, isBlue), tableauEtapes8, 3, 8, Etape::FEU, -1, 1);
                etape9 = new Etape(Position(1300, 185, isBlue), tableauEtapes9, 4, 9, Etape::FEU_COTE_NOTRE_COULEUR_FACE_TERRAIN, -1, 0);
                etape10 = new Etape(Position(1700, 185, isBlue), tableauEtapes10, 5, 10, Etape::FEU_COTE_NOTRE_COULEUR_FACE_EXTERIEUR, -1, 0);
                etape11 = new Etape(Position(2100, 185, isBlue), tableauEtapes11, 2, 11, Etape::FEU, -1, 1);
                etape12 = new Etape(Position(2200, 185, isBlue), tableauEtapes12, 3, 12, Etape::FRUIT, -1, 0);
                etape13 = new Etape(Position(2400, 185, isBlue), tableauEtapes13, 3, 13, Etape::FRUIT, -1, 0);
                etape14 = new Etape(Position(2815, 600, isBlue), tableauEtapes14, 3, 14, Etape::FRUIT, -1, 0);
                etape15 = new Etape(Position(2815, 800, isBlue), tableauEtapes15, 3, 15, Etape::FRUIT, -1, 0);
                etape16 = new Etape(Position(2815, 900, isBlue), tableauEtapes16, 2, 16, Etape::FEU, -1, 1);
                etape17 = new Etape(Position(2815, 1200, isBlue), tableauEtapes17, 3, 17, Etape::FEU_COTE_NOTRE_COULEUR_FACE_TERRAIN, -1, 0);
                etape18 = new Etape(Position(2400, 1550, isBlue), tableauEtapes18, 3, 18, Etape::DEPOSE_FRUIT, -1, 0);
                etape19 = new Etape(Position(2100, 1550, isBlue), tableauEtapes19, 2, 19, Etape::FEU, -1, 1);
                etape20 = new Etape(Position(600, 900, isBlue), tableauEtapes20, 4, 20, Etape::FEU, -1, 1);
                etape21 = new Etape(Position(900, 600, isBlue), tableauEtapes21, 5, 21, Etape::FEU, -1, 1);
                etape22 = new Etape(Position(1500, 600, isBlue), tableauEtapes22, 6, 22, Etape::POINT_PASSAGE, -1, 0);
                etape23 = new Etape(Position(2100, 600, isBlue), tableauEtapes23, 4, 23, Etape::FEU, -1, 0);
                etape24 = new Etape(Position(1800, 800, isBlue), tableauEtapes24, 4, 24, Etape::POINT_PASSAGE, -1, 0);
                etape25 = new Etape(Position(2400, 900, isBlue), tableauEtapes25, 4, 25, Etape::FEU, -1, 1);
                etape26 = new Etape(Position(2100, 1200, isBlue), tableauEtapes26, 3, 26, Etape::FEU, -1, 1);
                etape27 = new Etape(Position(1800, 1550, isBlue), tableauEtapes27, 2, 27, Etape::POINT_PASSAGE, -1, 0);
                etape28 = new Etape(Position(1800, 1000, isBlue), tableauEtapes28, 3, 28, Etape::POINT_PASSAGE, -1, 0);
                etape29 = new Etape(Position(600, 1100, isBlue), tableauEtapes29, 2, 29, Etape::POINT_PASSAGE, -1, 0);
                etape30 = new Etape(Position(600, 600, isBlue), tableauEtapes30, 5, 30, Etape::POINT_PASSAGE, -1, 0);
                etape31 = new Etape(Position(2400, 600, isBlue), tableauEtapes31, 6, 31, Etape::POINT_PASSAGE, -1, 0);

                tableauEtapes1[0] = etape2;
                tableauEtapes1[1] = etape29;

                tableauEtapes2[0] = etape1;
                tableauEtapes2[1] = etape3;

                tableauEtapes3[0] = etape2;
                tableauEtapes3[1] = etape4;

                tableauEtapes4[0] = etape3;
                tableauEtapes4[1] = etape5;

                tableauEtapes5[0] = etape4;
                tableauEtapes5[1] = etape6;
                tableauEtapes5[2] = etape20;
                tableauEtapes5[3] = etape30;

                tableauEtapes6[0] = etape5;
                tableauEtapes6[1] = etape7;
                tableauEtapes6[2] = etape30;

                tableauEtapes7[0] = etape6;
                tableauEtapes7[1] = etape8;
                tableauEtapes7[2] = etape30;

                tableauEtapes8[0] = etape7;
                tableauEtapes8[1] = etape9;
                tableauEtapes8[2] = etape22;

                tableauEtapes9[0] = etape8;
                tableauEtapes9[1] = etape10;
                tableauEtapes9[2] = etape21;
                tableauEtapes9[3] = etape22;

                tableauEtapes10[0] = etape9;
                tableauEtapes10[1] = etape11;
                tableauEtapes10[2] = etape21;
                tableauEtapes10[3] = etape22;
                tableauEtapes10[4] = etape24;

                tableauEtapes11[0] = etape10;
                tableauEtapes11[1] = etape12;

                tableauEtapes12[0] = etape11;
                tableauEtapes12[1] = etape13;
                tableauEtapes12[2] = etape31;

                tableauEtapes13[0] = etape12;
                tableauEtapes13[1] = etape14;
                tableauEtapes13[2] = etape31;

                tableauEtapes14[0] = etape13;
                tableauEtapes14[1] = etape15;
                tableauEtapes14[2] = etape31;

                tableauEtapes15[0] = etape14;
                tableauEtapes15[1] = etape16;
                tableauEtapes15[2] = etape31;

                tableauEtapes16[0] = etape15;
                tableauEtapes16[1] = etape17;

                tableauEtapes17[0] = etape16;
                tableauEtapes17[1] = etape18;
                tableauEtapes17[2] = etape26;

                tableauEtapes18[0] = etape17;
                tableauEtapes18[1] = etape19;
                tableauEtapes18[2] = etape25;

                tableauEtapes19[0] = etape18;
                tableauEtapes19[1] = etape27;

                tableauEtapes20[0] = etape5;
                tableauEtapes20[1] = etape21;
                tableauEtapes20[2] = etape29;
                tableauEtapes20[3] = etape30;

                tableauEtapes21[0] = etape9;
                tableauEtapes21[1] = etape10;
                tableauEtapes21[2] = etape20;
                tableauEtapes21[3] = etape22;
                tableauEtapes21[4] = etape30;

                tableauEtapes22[0] = etape8;
                tableauEtapes22[1] = etape9;
                tableauEtapes22[2] = etape10;
                tableauEtapes22[3] = etape21;
                tableauEtapes22[4] = etape23;
                tableauEtapes22[5] = etape24;

                tableauEtapes23[0] = etape22;
                tableauEtapes23[1] = etape24;
                tableauEtapes23[2] = etape25;
                tableauEtapes23[3] = etape31;

                tableauEtapes24[0] = etape10;
                tableauEtapes24[1] = etape22;
                tableauEtapes24[2] = etape23;
                tableauEtapes24[3] = etape28;

                tableauEtapes25[0] = etape18;
                tableauEtapes25[1] = etape23;
                tableauEtapes25[2] = etape26;
                tableauEtapes25[3] = etape31;

                tableauEtapes26[0] = etape17;
                tableauEtapes26[1] = etape25;
                tableauEtapes26[2] = etape28;

                tableauEtapes27[0] = etape19;
                tableauEtapes27[1] = etape28;

                tableauEtapes28[0] = etape24;
                tableauEtapes28[1] = etape26;
                tableauEtapes28[2] = etape27;

                tableauEtapes29[0] = etape1;
                tableauEtapes29[1] = etape20;

                tableauEtapes30[0] = etape5;
                tableauEtapes30[1] = etape6;
                tableauEtapes30[2] = etape7;
                tableauEtapes30[3] = etape20;
                tableauEtapes30[4] = etape21;

                tableauEtapes31[0] = etape12;
                tableauEtapes31[1] = etape13;
                tableauEtapes31[2] = etape14;
                tableauEtapes31[3] = etape15;
                tableauEtapes31[4] = etape23;
                tableauEtapes31[5] = etape25;

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
                etape31->setChildren(tableauEtapes31);

                Etape** tableauEtapesTotal = new Etape*[NOMBRE_ETAPES];
                tableauEtapesTotal[0] = etape1;
                tableauEtapesTotal[1] = etape2;
                tableauEtapesTotal[2] = etape3;
                tableauEtapesTotal[3] = etape4;
                tableauEtapesTotal[4] = etape5;
                tableauEtapesTotal[5] = etape6 ;
                tableauEtapesTotal[6] = etape7 ;
                tableauEtapesTotal[7] = etape8 ;
                tableauEtapesTotal[8] = etape9 ;
                tableauEtapesTotal[9] = etape10;
                tableauEtapesTotal[10] = etape11;
                tableauEtapesTotal[11] = etape12;
                tableauEtapesTotal[12] = etape13;
                tableauEtapesTotal[13] = etape14;
                tableauEtapesTotal[14] = etape15;
                tableauEtapesTotal[15] = etape16;
                tableauEtapesTotal[16] = etape17;
                tableauEtapesTotal[17] = etape18;
                tableauEtapesTotal[18] = etape19;
                tableauEtapesTotal[19] = etape20;
                tableauEtapesTotal[20] = etape21;
                tableauEtapesTotal[21] = etape22;
                tableauEtapesTotal[22] = etape23;
                tableauEtapesTotal[23] = etape24;
                tableauEtapesTotal[24] = etape25;
                tableauEtapesTotal[25] = etape26;
                tableauEtapesTotal[26] = etape27;
                tableauEtapesTotal[27] = etape28;
                tableauEtapesTotal[28] = etape29;
                tableauEtapesTotal[29] = etape30;
                tableauEtapesTotal[30] = etape31;
        /*
        this->nombreFruitsTransporte = 0;
        this->nombreFeuxTransporte = 0;
        this->nombreFresquesTransporte = 0;
        this->nombreLancesTransporte = 0;

        //etape2 = new Etape(Position(185, 1200, isBlue), tableauEtapes2, 2, 2, Etape::FEU_COTE_NOTRE_COULEUR_FACE_EXTERIEUR, -1, 0);
        actionFeuCote[0] = FeuCote(isBlue, Position(185, 1200, isBlue), 0,0,0);


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
        actionGoto[23] = ActionGoTo(Position(1850, 900, isBlue), false);
        actionGoto[24] = ActionGoTo(Position(2400, 900, isBlue), false);
        actionGoto[25] = ActionGoTo(Position(2100, 1200, isBlue), false);

        actionEtape[0] = &actionGoto[0];
        //actionEtape[1] = &actionGoto[1];
        actionEtape[1] = &actionFeuCote[0];
        actionEtape[2] = &actionGoto[2];
        actionEtape[3] = &actionGoto[3];
        actionEtape[4] = &actionGoto[4];
        actionEtape[5] = &actionGoto[5];
        actionEtape[6] = &actionGoto[6];
        actionEtape[7] = &actionGoto[7];
        actionEtape[8] = &actionGoto[8];
        actionEtape[9] = &actionGoto[9];
        actionEtape[10] = &actionGoto[10];
        actionEtape[11] = &actionGoto[11];
        actionEtape[12] = &actionGoto[12];
        actionEtape[13] = &actionGoto[13];
        actionEtape[14] = &actionGoto[14];
        actionEtape[15] = &actionGoto[15];
        actionEtape[16] = &actionGoto[16];
        actionEtape[17] = &actionGoto[17];
        actionEtape[18] = &actionGoto[18];
        actionEtape[19] = &actionGoto[19];
        actionEtape[20] = &actionGoto[20];
        actionEtape[21] = &actionGoto[21];
        actionEtape[22] = &actionGoto[22];
        actionEtape[23] = &actionGoto[23];
        actionEtape[24] = &actionGoto[24];
        actionEtape[25] = &actionGoto[25];

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

        Etape** tableauEtapes1 = new Etape*[2];
        Etape** tableauEtapes2 = new Etape*[2];
        Etape** tableauEtapes3 = new Etape*[2];
        Etape** tableauEtapes4 = new Etape*[2];
        Etape** tableauEtapes5 = new Etape*[4];
        Etape** tableauEtapes6 = new Etape*[4];
        Etape** tableauEtapes7 = new Etape*[2];
        Etape** tableauEtapes8 = new Etape*[3];
        Etape** tableauEtapes9 = new Etape*[4];
        Etape** tableauEtapes10 = new Etape*[5];
        Etape** tableauEtapes11 = new Etape*[3];
        Etape** tableauEtapes12 = new Etape*[2];
        Etape** tableauEtapes13 = new Etape*[4];
        Etape** tableauEtapes14 = new Etape*[4];
        Etape** tableauEtapes15 = new Etape*[2];
        Etape** tableauEtapes16 = new Etape*[2];
        Etape** tableauEtapes17 = new Etape*[4];
        Etape** tableauEtapes18 = new Etape*[4];
        Etape** tableauEtapes19 = new Etape*[2];
        Etape** tableauEtapes20 = new Etape*[4];
        Etape** tableauEtapes21 = new Etape*[5];
        Etape** tableauEtapes22 = new Etape*[7];
        Etape** tableauEtapes23 = new Etape*[6];
        Etape** tableauEtapes24 = new Etape*[5];
        Etape** tableauEtapes25 = new Etape*[6];
        Etape** tableauEtapes26 = new Etape*[4];

        etape1 = new Etape(Position(185, 1500, isBlue), tableauEtapes1, 2, 1, Etape::DEPART, -1, 0);
        etape2 = new Etape(Position(185, 1200, isBlue), tableauEtapes2, 2, 2, Etape::FEU_COTE_NOTRE_COULEUR_FACE_EXTERIEUR, -1, 0);
        etape3 = new Etape(Position(185, 900, isBlue), tableauEtapes3, 2, 3, Etape::FEU, -1, 1);
        etape4 = new Etape(Position(185, 800, isBlue), tableauEtapes4, 2, 4, Etape::FRUIT, -1, 0);
        etape5 = new Etape(Position(185, 600, isBlue), tableauEtapes5, 4, 5, Etape::FRUIT, -1, 0);
        etape6 = new Etape(Position(600, 185, isBlue), tableauEtapes6, 4, 6, Etape::FRUIT, -1, 0);
        etape7 = new Etape(Position(800, 185, isBlue), tableauEtapes7, 2, 7, Etape::FRUIT, -1, 0);
        etape8 = new Etape(Position(900, 185, isBlue), tableauEtapes8, 3, 8, Etape::FEU, -1, 1);
        etape9 = new Etape(Position(1300, 185, isBlue), tableauEtapes9, 4, 9, Etape::FEU_COTE_NOTRE_COULEUR_FACE_TERRAIN, -1, 0);
        etape10 = new Etape(Position(1700, 185, isBlue), tableauEtapes10, 5, 10, Etape::FEU_COTE_NOTRE_COULEUR_FACE_EXTERIEUR, -1, 0);
        etape11 = new Etape(Position(2100, 185, isBlue), tableauEtapes11, 3, 11, Etape::FEU, -1, 1);
        etape12 = new Etape(Position(2200, 185, isBlue), tableauEtapes12, 2, 12, Etape::FRUIT, -1, 0);
        etape13 = new Etape(Position(2400, 185, isBlue), tableauEtapes13, 4, 13, Etape::FRUIT, -1, 0);
        etape14 = new Etape(Position(2815, 600, isBlue), tableauEtapes14, 4, 14, Etape::FRUIT, -1, 0);
        etape15 = new Etape(Position(2815, 800, isBlue), tableauEtapes15, 2, 15, Etape::FRUIT, -1, 0);
        etape16 = new Etape(Position(2815, 900, isBlue), tableauEtapes16, 2, 16, Etape::FEU, -1, 1);
        etape17 = new Etape(Position(2815, 1200, isBlue), tableauEtapes17, 4, 17, Etape::FEU_COTE_NOTRE_COULEUR_FACE_TERRAIN, -1, 0);
        etape18 = new Etape(Position(2400, 1550, isBlue), tableauEtapes18, 4, 18, Etape::DEPOSE_FRUIT, -1, 0);
        etape19 = new Etape(Position(2100, 1550, isBlue), tableauEtapes19, 2, 19, Etape::FEU, -1, 1);
        etape20 = new Etape(Position(600, 900, isBlue), tableauEtapes20, 4, 20, Etape::FEU, -1, 1);
        etape21 = new Etape(Position(900, 600, isBlue), tableauEtapes21, 5, 21, Etape::FEU, -1, 1);
        etape22 = new Etape(Position(1500, 600, isBlue), tableauEtapes22, 7, 22, Etape::POINT_PASSAGE, -1, 0);
        etape23 = new Etape(Position(2100, 600, isBlue), tableauEtapes23, 6, 23, Etape::FEU, -1, 1);
        etape24 = new Etape(Position(1850, 900, isBlue), tableauEtapes24, 5, 24, Etape::POINT_PASSAGE, -1, 0);
        etape25 = new Etape(Position(2400, 900, isBlue), tableauEtapes25, 6, 25, Etape::FEU, -1, 1);
        etape26 = new Etape(Position(2100, 1200, isBlue), tableauEtapes26, 4, 26, Etape::FEU, -1, 1);

        tableauEtapes1[0] = etape2;
        tableauEtapes1[1] = etape20;

        tableauEtapes2[0] = etape1;
        tableauEtapes2[1] = etape3;

        tableauEtapes3[0] = etape2;
        tableauEtapes3[1] = etape4;

        tableauEtapes4[0] = etape3;
        tableauEtapes4[1] = etape5;

        tableauEtapes5[0] = etape4;
        tableauEtapes5[1] = etape6;
        tableauEtapes5[2] = etape20;
        tableauEtapes5[3] = etape21;

        tableauEtapes6[0] = etape5;
        tableauEtapes6[1] = etape7;
        tableauEtapes6[2] = etape20;
        tableauEtapes6[3] = etape21;

        tableauEtapes7[0] = etape6;
        tableauEtapes7[1] = etape8;

        tableauEtapes8[0] = etape7;
        tableauEtapes8[1] = etape9;
        tableauEtapes8[2] = etape22;

        tableauEtapes9[0] = etape8;
        tableauEtapes9[1] = etape10;
        tableauEtapes9[2] = etape21;
        tableauEtapes9[3] = etape22;

        tableauEtapes10[0] = etape9;
        tableauEtapes10[1] = etape11;
        tableauEtapes10[2] = etape22;
        tableauEtapes10[3] = etape23;
        tableauEtapes10[4] = etape24;

        tableauEtapes11[0] = etape10;
        tableauEtapes11[1] = etape12;
        tableauEtapes11[2] = etape22;

        tableauEtapes12[0] = etape11;
        tableauEtapes12[1] = etape13;

        tableauEtapes13[0] = etape12;
        tableauEtapes13[1] = etape14;
        tableauEtapes13[2] = etape23;
        tableauEtapes13[3] = etape25;

        tableauEtapes14[0] = etape13;
        tableauEtapes14[1] = etape15;
        tableauEtapes14[2] = etape23;
        tableauEtapes14[3] = etape25;

        tableauEtapes15[0] = etape14;
        tableauEtapes15[1] = etape16;

        tableauEtapes16[0] = etape15;
        tableauEtapes16[1] = etape17;

        tableauEtapes17[0] = etape16;
        tableauEtapes17[1] = etape18;
        tableauEtapes17[2] = etape25;
        tableauEtapes17[3] = etape26;

        tableauEtapes18[0] = etape17;
        tableauEtapes18[1] = etape19;
        tableauEtapes18[2] = etape25;
        tableauEtapes18[3] = etape26;

        tableauEtapes19[0] = etape18;
        tableauEtapes19[1] = etape24;

        tableauEtapes20[0] = etape1;
        tableauEtapes20[1] = etape5;
        tableauEtapes20[2] = etape6;
        tableauEtapes20[3] = etape21;

        tableauEtapes21[0] = etape5;
        tableauEtapes21[1] = etape6;
        tableauEtapes21[2] = etape9;
        tableauEtapes21[3] = etape20;
        tableauEtapes21[4] = etape22;

        tableauEtapes22[0] = etape8;
        tableauEtapes22[1] = etape9;
        tableauEtapes22[2] = etape10;
        tableauEtapes22[3] = etape11;
        tableauEtapes22[4] = etape21;
        tableauEtapes22[5] = etape23;
        tableauEtapes22[6] = etape24;

        tableauEtapes23[0] = etape10;
        tableauEtapes23[1] = etape13;
        tableauEtapes23[2] = etape14;
        tableauEtapes23[3] = etape22;
        tableauEtapes23[4] = etape24;
        tableauEtapes23[5] = etape25;

        tableauEtapes24[0] = etape10;
        tableauEtapes24[1] = etape19;
        tableauEtapes24[2] = etape22;
        tableauEtapes24[3] = etape23;
        tableauEtapes24[4] = etape26;

        tableauEtapes25[0] = etape13;
        tableauEtapes25[1] = etape14;
        tableauEtapes25[2] = etape17;
        tableauEtapes25[3] = etape18;
        tableauEtapes25[4] = etape23;
        tableauEtapes25[5] = etape26;

        tableauEtapes26[0] = etape17;
        tableauEtapes26[1] = etape18;
        tableauEtapes26[2] = etape24;
        tableauEtapes26[3] = etape25;

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

        Etape** tableauEtapesTotal = new Etape*[26];
        tableauEtapesTotal[0] = etape1;
        tableauEtapesTotal[1] = etape2;
        tableauEtapesTotal[2] = etape3;
        tableauEtapesTotal[3] = etape4;
        tableauEtapesTotal[4] = etape5;
        tableauEtapesTotal[5] = etape6 ;
        tableauEtapesTotal[6] = etape7 ;
        tableauEtapesTotal[7] = etape8 ;
        tableauEtapesTotal[8] = etape9 ;
        tableauEtapesTotal[9] = etape10;
        tableauEtapesTotal[10] = etape11;
        tableauEtapesTotal[11] = etape12;
        tableauEtapesTotal[12] = etape13;
        tableauEtapesTotal[13] = etape14;
        tableauEtapesTotal[14] = etape15;
        tableauEtapesTotal[15] = etape16;
        tableauEtapesTotal[16] = etape17;
        tableauEtapesTotal[17] = etape18;
        tableauEtapesTotal[18] = etape19;
        tableauEtapesTotal[19] = etape20;
        tableauEtapesTotal[20] = etape21;
        tableauEtapesTotal[21] = etape22;
        tableauEtapesTotal[22] = etape23;
        tableauEtapesTotal[23] = etape24;
        tableauEtapesTotal[24] = etape25;
        tableauEtapesTotal[25] = etape26;*/
        /// FIN KRABI-JUNIOR
    #endif
/*
    actionEtape[0] = ActionGoTo(Position(200, 1850, isBlue), false);
    actionEtape[1] = ActionGoTo(Position(200, 1500, isBlue), false);
    actionEtape[2] = ActionGoTo(Position(700, 1500, isBlue), false);
    actionEtape[3] = ActionGoTo(Position(1300, 1500, isBlue), false);
    actionEtape[4] = ActionGoTo(Position(1300, 1850, isBlue), false);
    actionEtape[5] = ActionGoTo(Position(1150, 1100, isBlue), false);
    actionEtape[6] = ActionGoTo(Position(1150, 800, isBlue), false);
    actionEtape[7] = ActionGoTo(Position(1500, 1500, isBlue), false);
    actionEtape[8] = ActionGoTo(Position(1500, 1850, isBlue), false);
    actionEtape[9] = ActionGoTo(Position(1700, 1500, isBlue), false);
    actionEtape[10] = ActionGoTo(Position(1700, 1850, isBlue), false);
    actionEtape[11] = ActionGoTo(Position(1850, 1100, isBlue), false);
    actionEtape[12] = ActionGoTo(Position(1850, 800, isBlue), false);
    actionEtape[13] = ActionGoTo(Position(1400, 1300, isBlue), false);
    actionEtape[14] = ActionGoTo(Position(1600, 1300, isBlue), false);
    actionEtape[15] = ActionGoTo(Position(1400, 600, isBlue), false);
    actionEtape[16] = ActionGoTo(Position(1600, 600, isBlue), false);
    actionEtape[17] = ActionGoTo(Position(2300, 1500, isBlue), false);
    actionEtape[18] = ActionGoTo(Position(400, 900, isBlue), false);
    actionEtape[19] = ActionGoTo(Position(900, 400, isBlue), false);
    actionEtape[20] = ActionGoTo(Position(2100, 400, isBlue), false);
    actionEtape[21] = ActionGoTo(Position(2600, 900, isBlue), false);

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

    Etape** tableauEtapes1 = new Etape*[1];
    Etape** tableauEtapes2 = new Etape*[3];
    Etape** tableauEtapes3 = new Etape*[4];
    Etape** tableauEtapes4 = new Etape*[6];
    Etape** tableauEtapes5 = new Etape*[1];
    Etape** tableauEtapes6 = new Etape*[4];
    Etape** tableauEtapes7 = new Etape*[3];
    Etape** tableauEtapes8 = new Etape*[5];
    Etape** tableauEtapes9 = new Etape*[1];
    Etape** tableauEtapes10 = new Etape*[6];
    Etape** tableauEtapes11 = new Etape*[1];
    Etape** tableauEtapes12 = new Etape*[4];
    Etape** tableauEtapes13 = new Etape*[3];
    Etape** tableauEtapes14 = new Etape*[5];
    Etape** tableauEtapes15 = new Etape*[5];
    Etape** tableauEtapes16 = new Etape*[3];
    Etape** tableauEtapes17 = new Etape*[3];
    Etape** tableauEtapes18 = new Etape*[3];
    Etape** tableauEtapes19 = new Etape*[3];
    Etape** tableauEtapes20 = new Etape*[4];
    Etape** tableauEtapes21 = new Etape*[4];
    Etape** tableauEtapes22 = new Etape*[2];

    //arguments : Position, tableau des etapes liées, nombre d'étapes liées, numéro de l'étape, type d'étape, état de l'étape
    etape1 = new Etape(Position(200, 1850, isBlue), tableauEtapes1, 1, 1, Etape::DEPART, -1);
    etape2 = new Etape(Position(200, 1500, isBlue), tableauEtapes2, 3, 2, Etape::POINT_PASSAGE,-1);
    etape3 = new Etape(Position(700, 1500, isBlue), tableauEtapes3, 4, 3, Etape::TIR_MAMMOUTH,-1);
    etape4 = new Etape(Position(1300, 1500, isBlue), tableauEtapes4, 6, 4, Etape::POINT_PASSAGE,-1);
    etape5 = new Etape(Position(1300, 1850, isBlue), tableauEtapes5, 1, 5, Etape::FEU,-1);//FRESQUE
    etape6 = new Etape(Position(1150, 1100, isBlue), tableauEtapes6, 4, 6, Etape::TORCHE_MOBILE,-1);
    etape7 = new Etape(Position(1150, 800, isBlue), tableauEtapes7, 3, 7, Etape::TORCHE_MOBILE,-1);
    etape8 = new Etape(Position(1500, 1500, isBlue), tableauEtapes8, 5, 8, Etape::POINT_PASSAGE,-1);
    etape9 = new Etape(Position(1500, 1850, isBlue), tableauEtapes9, 1, 9, Etape::FEU,-1);//FRESQUE
    etape10 = new Etape(Position(1700, 1500, isBlue), tableauEtapes10, 6, 10, Etape::POINT_PASSAGE,-1);
    etape11 = new Etape(Position(1700, 1850, isBlue), tableauEtapes11, 1, 11, Etape::FEU, -1);//FRESQUE
    etape12 = new Etape(Position(1850, 1100, isBlue), tableauEtapes12, 4, 12, Etape::TORCHE_MOBILE, -1);
    etape13 = new Etape(Position(1850, 800, isBlue), tableauEtapes13, 3, 13, Etape::TORCHE_MOBILE, -1);
    etape14 = new Etape(Position(1400, 1300, isBlue), tableauEtapes14, 5, 14, Etape::POINT_PASSAGE, -1);
    etape15 = new Etape(Position(1600, 1300, isBlue), tableauEtapes15, 5, 15, Etape::POINT_PASSAGE, -1);
    etape16 = new Etape(Position(1400, 600, isBlue), tableauEtapes16, 3, 16, Etape::POINT_PASSAGE, -1);
    etape17 = new Etape(Position(1600, 600, isBlue), tableauEtapes17, 3, 17, Etape::POINT_PASSAGE, -1);
    etape18 = new Etape(Position(2300, 1500, isBlue), tableauEtapes18, 3, 18, Etape::TIR_MAMMOUTH, -1);
    etape19 = new Etape(Position(400, 900, isBlue), tableauEtapes19, 3, 19, Etape::FEU, -1);
    etape20 = new Etape(Position(900, 400, isBlue), tableauEtapes20, 4, 20, Etape::FEU, -1);
    etape21 = new Etape(Position(2100, 400, isBlue), tableauEtapes21, 4, 21, Etape::FEU, -1);
    etape22 = new Etape(Position(2600, 900, isBlue), tableauEtapes22, 2, 22, Etape::FEU, -1);

    tableauEtapes1[0] = etape2;

    tableauEtapes2[0] = etape1;
    tableauEtapes2[1] = etape3;
    tableauEtapes2[2] = etape19;

    tableauEtapes3[0] = etape2;
    tableauEtapes3[1] = etape4;
    tableauEtapes3[2] = etape6;
    tableauEtapes3[3] = etape19;

    tableauEtapes4[0] = etape3;
    tableauEtapes4[1] = etape5;
    tableauEtapes4[2] = etape6;
    tableauEtapes4[3] = etape8;
    tableauEtapes4[4] = etape14;
    tableauEtapes4[5] = etape15;

    tableauEtapes5[0] = etape4;

    tableauEtapes6[0] = etape3;
    tableauEtapes6[1] = etape4;
    tableauEtapes6[2] = etape7;
    tableauEtapes6[3] = etape14;

    tableauEtapes7[0] = etape6;
    tableauEtapes7[1] = etape16;
    tableauEtapes7[2] = etape20;

    tableauEtapes8[0] = etape4;
    tableauEtapes8[1] = etape9;
    tableauEtapes8[2] = etape10;
    tableauEtapes8[3] = etape14;
    tableauEtapes8[4] = etape15;

    tableauEtapes9[0] = etape8;

    tableauEtapes10[0] = etape8;
    tableauEtapes10[1] = etape11;
    tableauEtapes10[2] = etape12;
    tableauEtapes10[3] = etape14;
    tableauEtapes10[4] = etape15;
    tableauEtapes10[5] = etape18;

    tableauEtapes11[0] = etape10;

    tableauEtapes12[0] = etape10;
    tableauEtapes12[1] = etape13;
    tableauEtapes12[2] = etape15;
    tableauEtapes12[3] = etape18;

    tableauEtapes13[0] = etape12;
    tableauEtapes13[1] = etape17;
    tableauEtapes13[2] = etape21;

    tableauEtapes14[0] = etape4;
    tableauEtapes14[1] = etape6;
    tableauEtapes14[2] = etape8;
    tableauEtapes14[3] = etape10;
    tableauEtapes14[4] = etape15;

    tableauEtapes15[0] = etape4;
    tableauEtapes15[1] = etape8;
    tableauEtapes15[2] = etape10;
    tableauEtapes15[3] = etape12;
    tableauEtapes15[4] = etape14;

    tableauEtapes16[0] = etape7;
    tableauEtapes16[1] = etape17;
    tableauEtapes16[2] = etape20;

    tableauEtapes17[0] = etape13;
    tableauEtapes17[1] = etape16;
    tableauEtapes17[2] = etape21;

    tableauEtapes18[0] = etape10;
    tableauEtapes18[1] = etape12;
    tableauEtapes18[2] = etape22;

    tableauEtapes19[0] = etape2;
    tableauEtapes19[1] = etape3;
    tableauEtapes19[2] = etape20;

    tableauEtapes20[0] = etape7;
    tableauEtapes20[1] = etape16;
    tableauEtapes20[2] = etape19;
    tableauEtapes20[3] = etape21;

    tableauEtapes21[0] = etape13;
    tableauEtapes21[1] = etape17;
    tableauEtapes21[2] = etape20;
    tableauEtapes21[3] = etape22;

    tableauEtapes22[0] = etape18;
    tableauEtapes22[1] = etape21;

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

    Etape** tableauEtapesTotal = new Etape*[22];
    tableauEtapesTotal[0] = etape1;
    tableauEtapesTotal[1] = etape2;
    tableauEtapesTotal[2] = etape3;
    tableauEtapesTotal[3] = etape4;
    tableauEtapesTotal[4] = etape5;
    tableauEtapesTotal[5] = etape6 ;
    tableauEtapesTotal[6] = etape7 ;
    tableauEtapesTotal[7] = etape8 ;
    tableauEtapesTotal[8] = etape9 ;
    tableauEtapesTotal[9] = etape10;
    tableauEtapesTotal[10] = etape11;
    tableauEtapesTotal[11] = etape12;
    tableauEtapesTotal[12] = etape13;
    tableauEtapesTotal[13] = etape14;
    tableauEtapesTotal[14] = etape15;
    tableauEtapesTotal[15] = etape16;
    tableauEtapesTotal[16] = etape17;
    tableauEtapesTotal[17] = etape18;
    tableauEtapesTotal[18] = etape19;
    tableauEtapesTotal[19] = etape20;
    tableauEtapesTotal[20] = etape21;
    tableauEtapesTotal[21] = etape22;

  */
/*

    actionEtape[0] = ActionGoTo(Position(200, 1850, isBlue), false);
        actionEtape[1] = ActionGoTo(Position(200, 1400, isBlue), false);
        actionEtape[2] = ActionGoTo(Position(900, 1400, isBlue), false);
        actionEtape[3] = ActionGoTo(Position(400, 900, isBlue), false);
        actionEtape[4] = ActionGoTo(Position(900, 400, isBlue), false);
        actionEtape[5] = ActionGoTo(Position(2100, 400, isBlue), false);
        actionEtape[6] = ActionGoTo(Position(2600, 900, isBlue), false);
        actionEtape[7] = ActionGoTo(Position(2100, 1400, isBlue), false);
        actionEtape[8] = ActionGoTo(Position(1100, 900, isBlue), false);
        actionEtape[NOMBRE_ETAPES-1]= ActionGoTo(Position(1900, 900, isBlue), false);

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

        Etape** tableauEtapes1 = new Etape*[1];
        Etape** tableauEtapes2 = new Etape*[3];
        Etape** tableauEtapes3 = new Etape*[4];
        Etape** tableauEtapes4 = new Etape*[3];
        Etape** tableauEtapes5 = new Etape*[3];
        Etape** tableauEtapes6 = new Etape*[3];
        Etape** tableauEtapes7 = new Etape*[2];
        Etape** tableauEtapes8 = new Etape*[3];
        Etape** tableauEtapes9 = new Etape*[2];
        Etape** tableauEtapes10 = new Etape*[2];

        //arguments : Position, tableau des etapes liées, nombre d'étapes liées, numéro de l'étape, type d'étape, état de l'étape
        etape1 = new Etape(Position(200, 1850, isBlue), tableauEtapes1, 1, 1, Etape::DEPART, -1);
        etape2 = new Etape(Position(200, 1400, isBlue), tableauEtapes2, 3, 2, Etape::POINT_PASSAGE,-1);
        etape3 = new Etape(Position(900, 1400, isBlue), tableauEtapes3, 4, 3, Etape::FEU,-1);
        etape4 = new Etape(Position(400, 900, isBlue), tableauEtapes4, 3, 4, Etape::FEU,-1);
        etape5 = new Etape(Position(900, 400, isBlue), tableauEtapes5, 3, 5, Etape::FEU,-1);
        etape6 = new Etape(Position(2100, 400, isBlue), tableauEtapes6, 3, 6, Etape::FEU,-1);
        etape7 = new Etape(Position(2600, 900, isBlue), tableauEtapes7, 2, 7, Etape::FEU,-1);
        etape8 = new Etape(Position(2100, 1400, isBlue), tableauEtapes8, 3, 8, Etape::FEU,-1);
        etape9 = new Etape(Position(1100, 900, isBlue), tableauEtapes9, 2, 9, Etape::POINT_PASSAGE,-1);
        etape10 = new Etape(Position(1900, 900, isBlue), tableauEtapes10, 2, 10, Etape::POINT_PASSAGE,-1);

        tableauEtapes1[0] = etape2;

        tableauEtapes2[0] = etape1;
        tableauEtapes2[1] = etape3;
        tableauEtapes2[2] = etape4;

        tableauEtapes3[0] = etape2;
        tableauEtapes3[1] = etape4;
        tableauEtapes3[2] = etape8;
        tableauEtapes3[3] = etape9;

        tableauEtapes4[0] = etape2;
        tableauEtapes4[1] = etape3;
        tableauEtapes4[2] = etape5;

        tableauEtapes5[0] = etape4;
        tableauEtapes5[1] = etape6;
        tableauEtapes5[2] = etape9;

        tableauEtapes6[0] = etape5;
        tableauEtapes6[1] = etape7;
        tableauEtapes6[2] = etape10;

        tableauEtapes7[0] = etape6;
        tableauEtapes7[1] = etape8;

        tableauEtapes8[0] = etape3;
        tableauEtapes8[1] = etape7;
        tableauEtapes8[2] = etape10;

        tableauEtapes9[0] = etape3;
        tableauEtapes9[1] = etape5;

        tableauEtapes10[0] = etape6;
        tableauEtapes10[1] = etape8;

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

        Etape** tableauEtapesTotal = new Etape*[10];
        tableauEtapesTotal[0] = etape1;
        tableauEtapesTotal[1] = etape2;
        tableauEtapesTotal[2] = etape3;
        tableauEtapesTotal[3] = etape4;
        tableauEtapesTotal[4] = etape5;
        tableauEtapesTotal[5] = etape6 ;
        tableauEtapesTotal[6] = etape7 ;
        tableauEtapesTotal[7] = etape8 ;
        tableauEtapesTotal[8] = etape9 ;
        tableauEtapesTotal[9] = etape10;
*/

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
//            qDebug() << this->dijkstra->calculDistanceDirect(this->tableauEtapes[numeroEtape], this->tableauEtapes[numeroEtape]->getChild(numeroChild)) << ", // vers etape " << (this->tableauEtapes[numeroEtape]->getChild(numeroChild)->getNumero()-1);
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
            qDebug().nospace() << "tableauDistances" << numeroEtape << "[" << numeroChild << "] = " << this->dijkstra->calculDistanceDirect(this->tableauEtapes[numeroEtape], this->tableauEtapes[numeroEtape]->getChild(numeroChild)) << "; // vers etape " << (this->tableauEtapes[numeroEtape]->getChild(numeroChild)->getNumero()-1);
//            if(numeroChild == (this->tableauEtapes[numeroEtape]->getNbChildren()-1))
//            {
//                qDebug() << this->dijkstra->calculDistanceDirect(this->tableauEtapes[numeroEtape], this->tableauEtapes[numeroEtape]->getChild(numeroChild));
//                //qDebug() << this->dijkstra->calculDistanceDirect(this->tableauEtapes[numeroEtape], this->tableauEtapes[numeroEtape]->getChild(numeroChild)) << " // vers etape " << (this->tableauEtapes[numeroEtape]->getChild(numeroChild)->getNumero()-1);
//            }
//            else
//            {
//                qDebug() << this->dijkstra->calculDistanceDirect(this->tableauEtapes[numeroEtape], this->tableauEtapes[numeroEtape]->getChild(numeroChild)) << ",";
//                //qDebug() << this->dijkstra->calculDistanceDirect(this->tableauEtapes[numeroEtape], this->tableauEtapes[numeroEtape]->getChild(numeroChild)) << ", // vers etape " << (this->tableauEtapes[numeroEtape]->getChild(numeroChild)->getNumero()-1);
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

    int* tableauDistances0 = new int[1];
tableauDistances0[0] = 350; // vers etape 1
this->tableauEtapes[0]->setDistances(tableauDistances0);

int* tableauDistances1 = new int[3];
tableauDistances1[0] = 350; // vers etape 0
tableauDistances1[1] = 500; // vers etape 2
tableauDistances1[2] = 632; // vers etape 18
this->tableauEtapes[1]->setDistances(tableauDistances1);

int* tableauDistances2 = new int[4];
tableauDistances2[0] = 500; // vers etape 1
tableauDistances2[1] = 600; // vers etape 3
tableauDistances2[2] = 602; // vers etape 5
tableauDistances2[3] = 670; // vers etape 18
this->tableauEtapes[2]->setDistances(tableauDistances2);

int* tableauDistances3 = new int[6];
tableauDistances3[0] = 600; // vers etape 2
tableauDistances3[1] = 100; // vers etape 4
tableauDistances3[2] = 427; // vers etape 5
tableauDistances3[3] = 200; // vers etape 7
tableauDistances3[4] = 223; // vers etape 13
tableauDistances3[5] = 360; // vers etape 14
this->tableauEtapes[3]->setDistances(tableauDistances3);

int* tableauDistances4 = new int[1];
tableauDistances4[0] = 100; // vers etape 3
this->tableauEtapes[4]->setDistances(tableauDistances4);

int* tableauDistances5 = new int[4];
tableauDistances5[0] = 602; // vers etape 2
tableauDistances5[1] = 427; // vers etape 3
tableauDistances5[2] = 300; // vers etape 6
tableauDistances5[3] = 320; // vers etape 13
this->tableauEtapes[5]->setDistances(tableauDistances5);

int* tableauDistances6 = new int[3];
tableauDistances6[0] = 300; // vers etape 5
tableauDistances6[1] = 320; // vers etape 15
tableauDistances6[2] = 471; // vers etape 19
this->tableauEtapes[6]->setDistances(tableauDistances6);

int* tableauDistances7 = new int[5];
tableauDistances7[0] = 200; // vers etape 3
tableauDistances7[1] = 100; // vers etape 8
tableauDistances7[2] = 200; // vers etape 9
tableauDistances7[3] = 223; // vers etape 13
tableauDistances7[4] = 223; // vers etape 14
this->tableauEtapes[7]->setDistances(tableauDistances7);

int* tableauDistances8 = new int[1];
tableauDistances8[0] = 100; // vers etape 7
this->tableauEtapes[8]->setDistances(tableauDistances8);

int* tableauDistances9 = new int[6];
tableauDistances9[0] = 200; // vers etape 7
tableauDistances9[1] = 100; // vers etape 10
tableauDistances9[2] = 427; // vers etape 11
tableauDistances9[3] = 360; // vers etape 13
tableauDistances9[4] = 223; // vers etape 14
tableauDistances9[5] = 600; // vers etape 17
this->tableauEtapes[9]->setDistances(tableauDistances9);

int* tableauDistances10 = new int[1];
tableauDistances10[0] = 100; // vers etape 9
this->tableauEtapes[10]->setDistances(tableauDistances10);

int* tableauDistances11 = new int[4];
tableauDistances11[0] = 427; // vers etape 9
tableauDistances11[1] = 300; // vers etape 12
tableauDistances11[2] = 320; // vers etape 14
tableauDistances11[3] = 602; // vers etape 17
this->tableauEtapes[11]->setDistances(tableauDistances11);

int* tableauDistances12 = new int[3];
tableauDistances12[0] = 300; // vers etape 11
tableauDistances12[1] = 320; // vers etape 16
tableauDistances12[2] = 471; // vers etape 20
this->tableauEtapes[12]->setDistances(tableauDistances12);

int* tableauDistances13 = new int[5];
tableauDistances13[0] = 223; // vers etape 3
tableauDistances13[1] = 320; // vers etape 5
tableauDistances13[2] = 223; // vers etape 7
tableauDistances13[3] = 360; // vers etape 9
tableauDistances13[4] = 200; // vers etape 14
this->tableauEtapes[13]->setDistances(tableauDistances13);

int* tableauDistances14 = new int[5];
tableauDistances14[0] = 360; // vers etape 3
tableauDistances14[1] = 223; // vers etape 7
tableauDistances14[2] = 223; // vers etape 9
tableauDistances14[3] = 320; // vers etape 11
tableauDistances14[4] = 200; // vers etape 13
this->tableauEtapes[14]->setDistances(tableauDistances14);

int* tableauDistances15 = new int[3];
tableauDistances15[0] = 320; // vers etape 6
tableauDistances15[1] = 200; // vers etape 16
tableauDistances15[2] = 538; // vers etape 19
this->tableauEtapes[15]->setDistances(tableauDistances15);

int* tableauDistances16 = new int[3];
tableauDistances16[0] = 320; // vers etape 12
tableauDistances16[1] = 200; // vers etape 15
tableauDistances16[2] = 538; // vers etape 20
this->tableauEtapes[16]->setDistances(tableauDistances16);

int* tableauDistances17 = new int[3];
tableauDistances17[0] = 600; // vers etape 9
tableauDistances17[1] = 602; // vers etape 11
tableauDistances17[2] = 670; // vers etape 21
this->tableauEtapes[17]->setDistances(tableauDistances17);

int* tableauDistances18 = new int[3];
tableauDistances18[0] = 632; // vers etape 1
tableauDistances18[1] = 670; // vers etape 2
tableauDistances18[2] = 707; // vers etape 19
this->tableauEtapes[18]->setDistances(tableauDistances18);

int* tableauDistances19 = new int[4];
tableauDistances19[0] = 471; // vers etape 6
tableauDistances19[1] = 538; // vers etape 15
tableauDistances19[2] = 707; // vers etape 18
tableauDistances19[3] = 1200; // vers etape 20
this->tableauEtapes[19]->setDistances(tableauDistances19);

int* tableauDistances20 = new int[4];
tableauDistances20[0] = 471; // vers etape 12
tableauDistances20[1] = 538; // vers etape 16
tableauDistances20[2] = 1200; // vers etape 19
tableauDistances20[3] = 707; // vers etape 21
this->tableauEtapes[20]->setDistances(tableauDistances20);

int* tableauDistances21 = new int[2];
tableauDistances21[0] = 670; // vers etape 17
tableauDistances21[1] = 707; // vers etape 20
this->tableauEtapes[21]->setDistances(tableauDistances21);
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
#endif


}

int StrategieV3::update()
{
    Etape* etape1 = this->tableauEtapes[0];
    Etape* etape2 = this->tableauEtapes[1];
    Etape* etape3 = this->tableauEtapes[2];
    Etape* etape4 = this->tableauEtapes[3];
    Etape* etape5 = this->tableauEtapes[4];
    Etape* etape6 = this->tableauEtapes[5];
    Etape* etape7 = this->tableauEtapes[6];
    Etape* etape8 = this->tableauEtapes[7];
    Etape* etape9 = this->tableauEtapes[8];
    Etape* etape10 = this->tableauEtapes[9];
    Etape* etape11 = this->tableauEtapes[10];
    Etape* etape12 = this->tableauEtapes[11];
    Etape* etape13 = this->tableauEtapes[12];
    Etape* etape14 = this->tableauEtapes[13];
    Etape* etape15 = this->tableauEtapes[14];
    Etape* etape16 = this->tableauEtapes[15];
    Etape* etape17 = this->tableauEtapes[16];
    Etape* etape18 = this->tableauEtapes[17];
    Etape* etape19 = this->tableauEtapes[18];
    Etape* etape20 = this->tableauEtapes[19];
    Etape* etape21 = this->tableauEtapes[20];
    Etape* etape22= this->tableauEtapes[21];

    this->actionEtape[this->etapeEnCours]->reset();
    this->actionGoto[this->etapeEnCours].reset();



    //Si on est en train d'éviter, on revient à l'étape précédente, et on marque l'étape comme à éviter
    if(this->avoiding)
    {
        this->tableauEtapes[this->etapeEnCours]->robotVu();
        //this->tableauEtapes[this->etapeEnCours]->setState(-2);
        this->tableauEtapes[etapeEnCours]->getParent()->setParent(this->tableauEtapes[this->etapeEnCours]);
        this->etapeEnCours = this->tableauEtapes[etapeEnCours]->getParent()->getNumero()-1;



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
            //this->etapeEnCours = this->tableauEtapes[this->etapeEnCours]->getParent()->getNumero()-1;
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
                    int numeroEtapeLiee = this->tableauEtapes[this->etapeEnCours]->getEtapesLieesParFinirEtape()[etapeLiee]-1;
                    this->tableauEtapes[numeroEtapeLiee]->finir();
                }

                //Mise à jour du stock
                if(this->tableauEtapes[this->etapeEnCours]->getEtapeType() == Etape::FRUIT)
                {
                    nombreFruitsTransporte++;
                }
                else if(this->tableauEtapes[this->etapeEnCours]->getEtapeType() == Etape::DEPOSE_FRUIT)
                {
                    nombreFruitsTransporte = 0;
                }
                else if(this->tableauEtapes[this->etapeEnCours]->getEtapeType() == Etape::DEPOSE_FEU)
                {
                    nombreFeuxTransporte--;
                }
                else if(this->tableauEtapes[this->etapeEnCours]->getEtapeType() == Etape::FRESQUE)
                {
                    nombreFresquesTransporte = 0;
                }
                else if(this->tableauEtapes[this->etapeEnCours]->getEtapeType() == Etape::TORCHE_MOBILE)
                {
                    nombreFeuxTransporte++;
                }
                else if(this->tableauEtapes[this->etapeEnCours]->getEtapeType() == Etape::TIR_MAMMOUTH)
                {
                    nombreLancesTransporte = 0;//nombreLancesTransporte--;
                }
                dijkstra->updateNombreElementsTransportes(nombreFeuxTransporte, nombreFruitsTransporte, nombreFresquesTransporte, nombreLancesTransporte);
            }

            //On recalcul les distances par rapport à l'étape où l'on vient d'arriver
            dijkstra->setEtapeCourante(this->etapeEnCours);
            if(dijkstra->run() != 0)
            {
                // Si run renvoit autre chose que 0, c'est que l'étape en cours a changée.
                // Cela arrive pour débloquer le robot
                //Etape* ancienneEtape = this->tableauEtapes[this->etapeEnCours];
                //this->etapeEnCours = this->tableauEtapes[this->etapeEnCours]->getParent()->getNumero()-1;
                this->actionEtape[this->etapeEnCours]->reset();
            }

            //On sélectionne l'objectif le plus prometteur : pas trop loin et qui rapporte
            //CETTE PARTIE EST A AMELIORER
            //on pourrait prendre en compte :
            //le fait le transporter un feu, ce qui active les objectifs de dépose
            //le temps que prend chaque action
            //le temps restant
            //la trajectoire de notre autre robot
            //...
            int meilleurEtape = -1;
            int scoreMaxi = -100000;
            for(int i = 0 ; i < NOMBRE_ETAPES ; i++)
            {
                int scoreTypeEtape = 0;
                float modificateurTemporel = 1.f;
                if(this->tableauEtapes[i]->getEtapeType()==Etape::FEU)
                    scoreTypeEtape = 100;
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
                    scoreTypeEtape = 100 * this->nombreFruitsTransporte;
                }
                if(this->tableauEtapes[i]->getEtapeType()==Etape::DEPOSE_FEU)
                {
                    scoreTypeEtape = 100 * this->nombreFeuxTransporte;
                }
                if(this->tableauEtapes[i]->getEtapeType()==Etape::TIR_MAMMOUTH)
                {
                    scoreTypeEtape = 100 * this->nombreLancesTransporte;
                }
                if(this->tableauEtapes[i]->getEtapeType()==Etape::FRESQUE)
                {
                    scoreTypeEtape = 0;//10000 * this->nombreLancesTransporte;
                }
                if(this->tableauEtapes[i]->getEtapeType()==Etape::FEU_COTE_NOTRE_COULEUR_FACE_EXTERIEUR
                        || this->tableauEtapes[i]->getEtapeType()==Etape::FEU_COTE_NOTRE_COULEUR_FACE_TERRAIN)
                {
                    scoreTypeEtape = 100;
                }
                if(scoreTypeEtape)
                {
                    if(scoreMaxi < modificateurTemporel*(1000-this->tableauEtapes[i]->getDistance() + scoreTypeEtape))
                    {
                        scoreMaxi = modificateurTemporel*(1000-this->tableauEtapes[i]->getDistance() + scoreTypeEtape);
                        meilleurEtape = i;
                    }
                }
            }
            if(meilleurEtape==-1)
            {
                //TODO : oublier ce qu'on a vu et recommencer
                this->statusStrat=-1;//Plus rien à faire, on passe à l'action suivante de stratégieV2
            }
            else
            {
                this->goal = meilleurEtape;
                this->statusStrat = 2;//Jusqu'à preuve du contraire, la prochaine étape est une étape intermédiaire
                this->updateIntermedaire();//On y va
            }
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
    if(((this->tableauEtapes[this->etapeEnCours]->getParent()->getNumero()-1)) == etapeOuOnVientDArriver)
    {
        #ifndef ROBOTHW
            qDebug() << "la prochaine étape est le goal\n";
        #endif
        this->statusStrat = 1;
    }

    //On cherche l'étape suivant vers l'etape - but
    while(((this->tableauEtapes[this->etapeEnCours]->getParent()->getNumero()-1)) != etapeOuOnVientDArriver)
    {
        #ifndef ROBOTHW
        qDebug() << "On cherche l'étape suivant vers l'etape - but" << this->etapeEnCours << "\n";
        #endif
        this->etapeEnCours = ((this->tableauEtapes[this->etapeEnCours]->getParent()->getNumero()-1));
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

        p->setOpacity(0.8f);
        p->setPen(QColor("orange"));
        p->setBrush(QBrush("orange"));
        p->drawEllipse(position,10,-10);

        QFont font;
        font.setPixelSize(50);
        p->setFont(font);
        p->setOpacity(1);
        p->setPen(QColor("green"));
        p->setBrush(QBrush("green"));
        p->drawText(position, QString::number(this->tableauEtapes[numeroEtape]->getNumero()));

        for(int numeroChild = 0 ; numeroChild < this->tableauEtapes[numeroEtape]->getNbChildren() ; numeroChild++)
        {
//            QPoint positionChild = QPoint(
//            this->tableauEtapes[numeroEtape]->getChildren()[numeroChild]->getPosition().getX(),
//            -(this->tableauEtapes[numeroEtape]->getChildren()[numeroChild]->getPosition().getY()));
            QPoint positionChild = QPoint(
            (this->tableauEtapes[numeroEtape]->getChildren()[numeroChild]->getPosition().getX()+this->tableauEtapes[numeroEtape]->getPosition().getX())/2,
            -((this->tableauEtapes[numeroEtape]->getChildren()[numeroChild]->getPosition().getY()+this->tableauEtapes[numeroEtape]->getPosition().getY())/2));
            p->setOpacity(0.5f);
            p->setPen(QColor("orange"));
            p->setBrush(QBrush("orange"));
            p->drawLine(position.x(), position.y(),positionChild.x(),positionChild.y());
            p->drawEllipse(position,10,-10);
        }
    }
    p->setOpacity(1);
}
#endif


