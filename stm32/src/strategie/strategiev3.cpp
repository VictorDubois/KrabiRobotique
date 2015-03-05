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

    /*#ifdef KRABI_JR
        /// KRABI-JUNIOR
        this->nombreFruitsTransporte = 0;
        this->nombreFeuxTransporte = 0;
        this->nombreFresquesTransporte = 0;
        this->nombreLancesTransporte = 0;

        int numeroEtape = 0;


        Etape* etape0 =  new Etape(Position(185, 1500, isBlue),  numeroEtape++, tableauEtapesTotal, Etape::DEPART, -1, 0);
        Etape* etape1 =  new Etape(Position(185, 1200, isBlue),  numeroEtape++, tableauEtapesTotal, Etape::FEU_COTE_NOTRE_COULEUR_FACE_EXTERIEUR, -1, 0);
        Etape* etape2 =  new Etape(Position(185, 900, isBlue),   numeroEtape++, tableauEtapesTotal, Etape::FEU, -1, 1);
        Etape* etape3 =  new Etape(Position(185, 800, isBlue),   numeroEtape++, tableauEtapesTotal, Etape::FRUIT, -1, 0);
        Etape* etape4 =  new Etape(Position(185, 600, isBlue),   numeroEtape++, tableauEtapesTotal, Etape::FRUIT, -1, 0);
        Etape* etape5 =  new Etape(Position(600, 185, isBlue),   numeroEtape++, tableauEtapesTotal, Etape::FRUIT, -1, 0);
        Etape* etape6 =  new Etape(Position(800, 185, isBlue),   numeroEtape++, tableauEtapesTotal, Etape::FRUIT, -1, 0);
        Etape* etape7 =  new Etape(Position(900, 185, isBlue),   numeroEtape++, tableauEtapesTotal, Etape::FEU, -1, 1);//FEU
        Etape* etape8 =  new Etape(Position(1300, 185, isBlue),  numeroEtape++, tableauEtapesTotal, Etape::FEU_COTE_NOTRE_COULEUR_FACE_TERRAIN, -1, 0);
        Etape* etape9 =  new Etape(Position(1700, 185, isBlue),  numeroEtape++, tableauEtapesTotal, Etape::FEU_COTE_NOTRE_COULEUR_FACE_EXTERIEUR, -1, 0);
        Etape* etape10 = new Etape(Position(2100, 185, isBlue),  numeroEtape++, tableauEtapesTotal, Etape::FEU, -1, 1);
        Etape* etape11 = new Etape(Position(2200, 185, isBlue),  numeroEtape++, tableauEtapesTotal, Etape::FRUIT, -1, 0);
        Etape* etape12 = new Etape(Position(2400, 185, isBlue),  numeroEtape++, tableauEtapesTotal, Etape::FRUIT, -1, 0);
        Etape* etape13 = new Etape(Position(2815, 600, isBlue),  numeroEtape++, tableauEtapesTotal, Etape::FRUIT, -1, 0);
        Etape* etape14 = new Etape(Position(2815, 800, isBlue),  numeroEtape++, tableauEtapesTotal, Etape::FRUIT, -1, 0);
        Etape* etape15 = new Etape(Position(2815, 900, isBlue),  numeroEtape++, tableauEtapesTotal, Etape::FEU, -1, 1);
        Etape* etape16 = new Etape(Position(2815, 1200, isBlue), numeroEtape++, tableauEtapesTotal, Etape::FEU_COTE_NOTRE_COULEUR_FACE_TERRAIN, -1, 0);
        Etape* etape17 = new Etape(Position(2400, 1550, isBlue), numeroEtape++, tableauEtapesTotal, Etape::DEPOSE_FRUIT, -1, 0);
        Etape* etape18 = new Etape(Position(2100, 1550, isBlue), numeroEtape++, tableauEtapesTotal, Etape::TIR_MAMMOUTH, -1, 1);
        Etape* etape19 = new Etape(Position(600, 900, isBlue),   numeroEtape++, tableauEtapesTotal, Etape::FEU, -1, 1);
        Etape* etape20 = new Etape(Position(900, 600, isBlue),   numeroEtape++, tableauEtapesTotal, Etape::FEU, -1, 1);
        Etape* etape21 = new Etape(Position(1500, 600, isBlue),  numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
        Etape* etape22 = new Etape(Position(2100, 600, isBlue),  numeroEtape++, tableauEtapesTotal, Etape::FEU, -1, 0);
        Etape* etape23 = new Etape(Position(1800, 800, isBlue),  numeroEtape++, tableauEtapesTotal, Etape::TIR_MAMMOUTH, -1, 0);
        Etape* etape24 = new Etape(Position(2400, 900, isBlue),  numeroEtape++, tableauEtapesTotal, Etape::FEU, -1, 1);
        Etape* etape25 = new Etape(Position(2100, 1200, isBlue), numeroEtape++, tableauEtapesTotal, Etape::FEU, -1, 1);
        Etape* etape26 = new Etape(Position(1800, 1550, isBlue), numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
        Etape* etape27 = new Etape(Position(1800, 1000, isBlue), numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
        Etape* etape28 = new Etape(Position(600, 1100, isBlue),  numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
        Etape* etape29 = new Etape(Position(600, 600, isBlue),   numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);
        Etape* etape30 = new Etape(Position(2400, 600, isBlue),  numeroEtape++, tableauEtapesTotal, Etape::POINT_PASSAGE, -1, 0);

        //Initialisation des actions par défaut
        for(int i = 0 ; i < NOMBRE_ETAPES ; i++)
        {
            actionGoto[i] = ActionGoTo(tableauEtapesTotal[i]->getPosition(), false);
            actionEtape[i] = &actionGoto[i];
        }

        actionFeuCote[0] = FeuCote(isBlue, Position(185, 1200, isBlue), FeuCote::NOTRE_BORDURE, FeuCote::NOTRE_COULEUR_VERS_EXTERIEUR, FeuCote::COTE_NOTRE_DEPART);
        actionFeuCote[1] = FeuCote(isBlue, Position(1300, 185, isBlue), FeuCote::BORDURE_MILIEU, FeuCote::NOTRE_COULEUR_VERS_TERRAIN, FeuCote::COTE_NOTRE_DEPART);
        actionFeuCote[2] = FeuCote(isBlue, Position(1700, 185, isBlue), FeuCote::BORDURE_MILIEU, FeuCote::NOTRE_COULEUR_VERS_EXTERIEUR, FeuCote::COTE_DEPART_ADVERSAIRE);
        actionFeuCote[3] = FeuCote(isBlue, Position(2815, 1200, isBlue), FeuCote::BORDURE_ADVERSAIRE, FeuCote::NOTRE_COULEUR_VERS_EXTERIEUR, FeuCote::COTE_DEPART_ADVERSAIRE);

        actionDeposeFruits[0] = DeposeFruits(isBlue, Position(2400, 1550, isBlue));

        actionEtape[1] = &actionFeuCote[0];
        actionEtape[8] = &actionFeuCote[1];
        actionEtape[9] = &actionFeuCote[2];
        actionEtape[16] = &actionFeuCote[3];
        actionEtape[17] = &actionDeposeFruits[0];

        etape0->addVoisin(etape1);
        etape0->addVoisin(etape28);

        etape1->addVoisin(etape2);

        etape2->addVoisin(etape3);

        etape3->addVoisin(etape4);

        etape4->addVoisin(etape5);
        etape4->addVoisin(etape19);
        etape4->addVoisin(etape29);

        etape5->addVoisin(etape6);
        etape5->addVoisin(etape29);

        etape6->addVoisin(etape7);
        etape6->addVoisin(etape29);

        etape7->addVoisin(etape8);
        etape7->addVoisin(etape21);

        etape8->addVoisin(etape9);
        etape8->addVoisin(etape20);
        etape8->addVoisin(etape21);

        etape9->addVoisin(etape10);
        etape9->addVoisin(etape20);
        etape9->addVoisin(etape21);
        etape9->addVoisin(etape23);

        etape10->addVoisin(etape11);

        etape11->addVoisin(etape12);
        etape11->addVoisin(etape30);

        etape12->addVoisin(etape13);
        etape12->addVoisin(etape30);

        etape13->addVoisin(etape14);
        etape13->addVoisin(etape30);

        etape14->addVoisin(etape15);
        etape14->addVoisin(etape30);

        etape15->addVoisin(etape16);

        etape16->addVoisin(etape17);
        etape16->addVoisin(etape25);

        etape17->addVoisin(etape18);
        etape17->addVoisin(etape24);

        etape18->addVoisin(etape26);

        etape19->addVoisin(etape20);
        etape19->addVoisin(etape28);
        etape19->addVoisin(etape29);

        etape20->addVoisin(etape21);
        etape20->addVoisin(etape29);

        etape21->addVoisin(etape22);
        etape21->addVoisin(etape23);

        etape22->addVoisin(etape23);
        etape22->addVoisin(etape24);
        etape22->addVoisin(etape30);

        etape23->addVoisin(etape27);

        etape24->addVoisin(etape25);
        etape24->addVoisin(etape30);

        etape25->addVoisin(etape27);

        etape26->addVoisin(etape27);

        /// FIN KRABI-JUNIOR
    #endif
*/
/*
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
    */


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
        for(int i = 0 ; i < this->nombreEtapes ; i++)
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

                this->updateStock();

            }


            int score = 0;
            bool resteDesChosesAFaire = updateScores();

            // S'il n'y a plus d'objectif dans tout le graphe, on se replit vers une position où on ne bloque pas l'adversaire.
            // Sinon, il y a risque de prendre un avertissement pour anti-jeu (évité de peu pour le premier match de Krabi 2014)
            if(!resteDesChosesAFaire)
            {
                for(int i = 0 ; i < this->nombreEtapes ; i++)
                {
                    this->tableauEtapesTotal[i]->oublieRobotVu();
                }
                resteDesChosesAFaire = updateScores();

                //S'il n'y a VRAIMENT plus rien à faire
                if(!resteDesChosesAFaire)
                {
                    //Si on est au garage, on s'arrête
                    if(this->etapeEnCours == this->numeroEtapeGarage)
                    {
                        this->statusStrat=-1;//Plus rien à faire, on passe à l'action suivante de stratégieV2
                        return this->statusStrat;
                    }
                    else
                    {
                        //Sinon on y va
                        this->tableauEtapes[this->numeroEtapeGarage]->setScore(1000);
                    }
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

            int scoreTypeEtape = 0;
            for(int i = 0 ; i < this->nombreEtapes ; i++)
            {
                scoreTypeEtape = this->tableauEtapes[i]->getScore();
        //        score = modificateurTemporel*(10000-this->tableauEtapes[i]->getDistance() + scoreTypeEtape);
                score = (10000-this->tableauEtapes[i]->getDistance() + scoreTypeEtape);
                if((scoreMaxi < score) && scoreTypeEtape && (this->tableauEtapes[i]->getDistance() != -1))
                {
                    scoreMaxi = score;
                    meilleurEtape = i;
                }
            }

            if(meilleurEtape==-1)
            {
                if(this->etapeEnCours == this->numeroEtapeGarage)
                {
                    this->statusStrat=-1;//Plus rien à faire, on passe à l'action suivante de stratégieV2
                    return this->statusStrat;
                }
                else
                {
                    meilleurEtape = this->numeroEtapeGarage;
                }
            }

            //Si c'est un fruit, on considère déjà qu'on l'a attrapé
            /*if(this->tableauEtapes[meilleurEtape]->getEtapeType()==Etape::DEPOSE_FRUIT)
            {
                this->nombreFruitsTransporte++;
            }*/

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
    for(int numeroEtape = 0 ; numeroEtape<this->nombreEtapes ; numeroEtape++)
    {
        QPoint position = QPoint(
        this->tableauEtapes[numeroEtape]->getPosition().getX(),
        this->tableauEtapes[numeroEtape]->getPosition().getY());

        // Affichage des étapes
        p->setPen(colorEtapesIntermediaires);//"orange"));
        p->setBrush(colorEtapesIntermediaires);//"orange"));
        p->setOpacity(1.0f);
        p->drawEllipse(position,10,10);

        // Etape - but en surbrillance
        if(numeroEtape == this->goal)
        {
            p->setPen(colorEtapeGoal);
            p->setBrush(colorEtapeGoal);
            p->setOpacity(1.0f);
            p->drawEllipse(position,30,30);
        }

        // Etape actuelle en surbrillance
        if(numeroEtape == this->etapeEnCours)
        {
            p->setPen(colorEtapesIntermediaires);
            p->setBrush(colorEtapesIntermediaires);
            p->setOpacity(1.0f);
            p->drawEllipse(position,25,25);
        }

        // Etapes où on a vu un robot
        if(this->tableauEtapes[numeroEtape]->aEviter())
        {
            p->setPen(colorEtapesRobotVu);
            p->setBrush(colorEtapesRobotVu);
            p->setOpacity(1.0f);
            p->drawEllipse(position,20,20);
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
            (this->tableauEtapes[numeroEtape]->getChildren()[numeroChild]->getPosition().getY()+this->tableauEtapes[numeroEtape]->getPosition().getY())/2);
            p->setOpacity(0.5f);
            p->setPen(colorLiaisonsEtapes);
            p->setBrush(colorLiaisonsEtapes);
            p->drawLine(position.x(), position.y(),positionChild.x(),positionChild.y());
            p->drawEllipse(position,10,10);
        }

        //Affichage du type d'étape
        QPoint positionTypeEtape = QPoint(
        this->tableauEtapes[numeroEtape]->getPosition().getX(),
        this->tableauEtapes[numeroEtape]->getPosition().getY() - 50);
        p->setFont(font);
        p->setOpacity(1);
        p->setPen(colorTexteEtapes);
        p->setBrush(colorTexteEtapes);
        p->drawText(positionTypeEtape, QString::number(this->tableauEtapes[numeroEtape]->getEtapeType()));
    }
    p->setOpacity(1);
}
#endif

void StrategieV3::startDijkstra(){
    for(int i=0; i<this->nombreEtapes; i++)
        tableauEtapesTotal[i]->computeChildDistances();

    this->dijkstra = new Dijkstra(tableauEtapesTotal, this->nombreEtapes);

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
    for(int numeroEtape = 0 ; numeroEtape < this->nombreEtapes ; numeroEtape++)
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
}

bool StrategieV3::updateScores() {
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
    //float modificateurTemporel = 1.f;

    bool resteDesChosesAFaire = false;
    for(int i = 0 ; i < this->nombreEtapes ; i++)
    {
        scoreTypeEtape=this->getScoreEtape(i);
        if(scoreTypeEtape)
        {
            resteDesChosesAFaire = true;
        }

        this->tableauEtapes[i]->setScore(scoreTypeEtape);
    }
    return resteDesChosesAFaire;
}
