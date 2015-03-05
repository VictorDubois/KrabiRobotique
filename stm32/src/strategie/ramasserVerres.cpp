#include "ramasserVerres.h"
#include "strategieV2.h"
#include "leds.h"

RamasserVerres::RamasserVerres() : MediumLevelAction()
{
    bool isBlue = StrategieV2::getIsBlue();
    positionsToGo[0][0] = ActionGoTo(Position(600, 1300, isBlue), false);
    //positionsToGo[0][1] = new ActionGoTo(Position(2100, 1300, isBlue), false);
    positionsToGo[0][1] = ActionGoTo(Position(700, 1360, isBlue), false);
    //positionsToGo[0][2] = new ActionGoTo(Position(2100, 1050, isBlue), false);
    positionsToGo[0][2] = ActionGoTo(Position(2100, 1250, isBlue), true);
    positionsToGo[0][3] = ActionGoTo(Position(2100, 1050, isBlue), false);
    positionsToGo[0][4] = ActionGoTo(Position(900, 1050, isBlue), false);
    positionsToGo[0][5] = ActionGoTo(Position(350, 1250, isBlue), false);
    positionsToGo[0][6] = ActionGoTo(Position(900, 1050, isBlue), true);

    positionsToGo[1][0] = ActionGoTo(Position(600, 1050, isBlue), false);
    //positionsToGo[1][1] = new ActionGoTo(Position(2100, 1050, isBlue), false);
    positionsToGo[1][1] = ActionGoTo(Position(1350, 1050, isBlue), false);
    //positionsToGo[1][2] = new ActionGoTo(Position(1950, 800, isBlue), false);
    positionsToGo[1][2] = ActionGoTo(Position(2100, 1050, isBlue), true);
    positionsToGo[1][3] = ActionGoTo(Position(2100, 760, isBlue), false);
    positionsToGo[1][4] = ActionGoTo(Position(900, 760, isBlue), false);
    positionsToGo[1][5] = ActionGoTo(Position(370, 760, isBlue), false);
    positionsToGo[1][6] = ActionGoTo(Position(500, 760, isBlue), true);

    positionsToGo[2][0] = ActionGoTo(Position(600, 800, isBlue), false);
    //positionsToGo[2][1] = new ActionGoTo(Position(2100, 800, isBlue), false);
    positionsToGo[2][1] = ActionGoTo(Position(700, 1360, isBlue), false);
    //positionsToGo[2][2] = new ActionGoTo(Position(2100, 550, isBlue), false);
    positionsToGo[2][2] = ActionGoTo(Position(2100, 760, isBlue), true);
    positionsToGo[2][3] = ActionGoTo(Position(2100, 550, isBlue), false);
    positionsToGo[2][4] = ActionGoTo(Position(900, 550, isBlue), false);
    positionsToGo[2][5] = ActionGoTo(Position(350, 450, isBlue), false);
    positionsToGo[2][6] = ActionGoTo(Position(350, 450, isBlue), true);


    positionsToGo[3][0] = ActionGoTo(Position(600, 800, isBlue), false);
    //positionsToGo[2][1] = new ActionGoTo(Position(2100, 800, isBlue), false);
    positionsToGo[3][1] = ActionGoTo(Position(2100, 800, isBlue), false);
    //positionsToGo[2][2] = new ActionGoTo(Position(2100, 550, isBlue), false);
    positionsToGo[3][2] = ActionGoTo(Position(2100, 1200, isBlue), false);
    positionsToGo[3][3] = ActionGoTo(Position(2100, 1050, isBlue), false);
    positionsToGo[3][4] = ActionGoTo(Position(1500, 1050, isBlue), false);
    positionsToGo[3][5] = ActionGoTo(Position(350, 350, isBlue), false);
    positionsToGo[3][6] = ActionGoTo(Position(30, 1050, isBlue), true);


    positionsToGo[4][0] = ActionGoTo(Position(600, 1050, isBlue), false);
    //positionsToGo[2][1] = new ActionGoTo(Position(2100, 800, isBlue), false);
    positionsToGo[4][1] = ActionGoTo(Position(2100, 550, isBlue), false);
    //positionsToGo[2][2] = new ActionGoTo(Position(2100, 550, isBlue), false);
    positionsToGo[4][2] = ActionGoTo(Position(2100, 1050, isBlue), false);
    positionsToGo[4][3] = ActionGoTo(Position(2100, 800, isBlue), false);
    positionsToGo[4][4] = ActionGoTo(Position(1500, 800, isBlue), false);
    positionsToGo[4][5] = ActionGoTo(Position(350, 350, isBlue), false);
    positionsToGo[4][6] = ActionGoTo(Position(1500, 800, isBlue), true);


    positionsToGo[5][0] = ActionGoTo(Position(600, 800, isBlue), false);
    //positionsToGo[2][1] = new ActionGoTo(Position(2100, 800, isBlue), false);
    positionsToGo[5][1] = ActionGoTo(Position(2100, 800, isBlue), false);
    //positionsToGo[2][2] = new ActionGoTo(Position(2100, 550, isBlue), false);
    positionsToGo[5][2] = ActionGoTo(Position(2100, 800, isBlue), false);
    positionsToGo[5][3] = ActionGoTo(Position(2100, 550, isBlue), false);
    positionsToGo[5][4] = ActionGoTo(Position(1500, 550, isBlue), false);
    positionsToGo[5][5] = ActionGoTo(Position(350, 350, isBlue), false);
    positionsToGo[5][6] = ActionGoTo(Position(1000, 1000, isBlue), true);


    for (int i = 0; i < 6; i++)
        for(int j = 0; j < 2; j++)
            demiLignesRamassees[i][j] = false;

    myTurn = false;
    nextPosition = 0;
    ligneEnCours = -1;
}

RamasserVerres::~RamasserVerres()
{
    //dtor
}

int RamasserVerres::update()
{
    if (status == 0)
        status = 1;
    if (status == 1) // commencer une action
    {
        ligneEnCours ++; //= ligneAFaire
        // calcul de la ligne a faire :
        //int ligneAFaire = -1;
        /*for (int i = 5; i >= 0; i--)
        {
            if (demiLignesRamassees[i][0] == false || demiLignesRamassees[i][1] == false)
            {
                ligneAFaire = i;
            }
        }*/
        // une ligne non entierement faite est détectée

        if (ligneEnCours >= 0 && ligneEnCours < 3) // if (ligneAFaire >= 0 && ligneAFaire <=5)
        {
            // reste-il la demi-ligne la plus lointaine ?
            //ramasserTouteLaLigne = (! demiLignesRamassees[ligneEnCours][1]);
            //if (ramasserTouteLaLigne)
            //    nextPosition = 2;
            //else
            if (ligneEnCours == 0)
                nextPosition = 1;
            else
                nextPosition = 1;
            if ((nextPosition == 0 && myTurn) || nextPosition == 1 &&  myTurn) // si on doit aller se positionner, et qu'on vient de finir la ligne précédente
            {
                positionsToGo[ligneEnCours][nextPosition].setGoBack(true); // on continue à reculer.
            }
            status = 2; // on passe a l'action
        }
        else
        {
            status = -1; // on a tout fini
            return status;
        }
    }
    else if (status == 2) // suivre les positions
    {
//        allumerLED2();
        if (nextPosition >= 6) // fini
        {
            myTurn = true; // on vient de finir notre action
            // enregistrer les actions faites
            if (ramasserTouteLaLigne)
            {
                demiLignesRamassees[ligneEnCours][0] = true;
                demiLignesRamassees[ligneEnCours][1] = true;
            }
            else
            {
                demiLignesRamassees[ligneEnCours][0] = true;
            }
            status = 1; // passer a l'action suivante
        }
        else
        {
            // config des capteurs sharp
            //StrategieV2::emptySharpsToCheck();
            /*if (positionsToGo[ligneEnCours][nextPosition]->getGoBack()) // si on recule
            {
                StrategieV2::sharpsToCheck[SharpSensor::BACK_LEFT] = true;
                StrategieV2::sharpsToCheck[SharpSensor::BACK_MIDDLE] = true;
                StrategieV2::sharpsToCheck[SharpSensor::BACK_RIGHT] = true;
                StrategieV2::sharpsToCheck[SharpSensor::FRONT_LEFT] = true;
                StrategieV2::sharpsToCheck[SharpSensor::FRONT_RIGHT] = true;
                StrategieV2::sharpsToCheck[SharpSensor::FRONT_SIDE_LEFT] = true;
                StrategieV2::sharpsToCheck[SharpSensor::FRONT_SIDE_RIGHT] = true;
            }
            else
            {
            }*/
            /*
                StrategieV2::sharpsToCheck[SharpSensor::BACK_LEFT] = true;
                StrategieV2::sharpsToCheck[SharpSensor::BACK_MIDDLE] = true;
                StrategieV2::sharpsToCheck[SharpSensor::BACK_RIGHT] = true;
                StrategieV2::sharpsToCheck[SharpSensor::ELEVATOR_TOP] = true;
                StrategieV2::sharpsToCheck[SharpSensor::ELEVATOR_DOWN] = true;
                StrategieV2::sharpsToCheck[SharpSensor::NONE] = true;
                StrategieV2::sharpsToCheck[SharpSensor::FRONT_LEFT] = true;
                //StrategieV2::sharpsToCheck[SharpSensor::FRONT_RIGHT] = true;
                StrategieV2::sharpsToCheck[SharpSensor::FRONT_SIDE_LEFT] = true;
                StrategieV2::sharpsToCheck[SharpSensor::FRONT_SIDE_RIGHT] = true;*/
            nextPosition++;
            StrategieV2::addTemporaryAction(&positionsToGo[ligneEnCours][nextPosition]);
            //status = 1; //status = 900;
        }
    }
    if (status == 900)
    {

    }

    return status;
}

void RamasserVerres::othersTurn()
{
    myTurn = false;
    status = 1; // on revient au choix des actions
}
