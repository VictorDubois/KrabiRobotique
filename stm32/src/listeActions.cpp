#include "listeActions.h"
#include "actionSuivreChemin.h"

#include "stm32f10x_gpio.h"

#undef STM32F10X_CL // pour le simulateur, parce que un des fichiers définit cette macro et ne devrait pas. a commenter lors de la compil
// allume ou éteint une LED
void xxxallumerLED()
{
#ifdef STM32F10X_MD // stm32 h103
    GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_RESET);
#endif
#ifdef STM32F10X_CL // stm32 h107
    GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_SET); // LED verte
#endif
}

void xxxeteindreLED()
{
#ifdef STM32F10X_MD // stm32 h103
    GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_SET);
#endif
#ifdef STM32F10X_CL // stm32 h107
    GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_RESET); // LED verte
#endif
}

// 2ème LED du stm h107 (LED jaune)

void xxxallumerLED2()
{
#ifdef STM32F10X_CL
    GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_SET);
#endif
}
void xxxeteindreLED2()
{
#ifdef STM32F10X_CL
    GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_RESET);
#endif
}

ListeActions::ListeActions(Odometrie* odo, bool is_Blue)
{

    actionActuelle = NULL;
    actions = NULL;
    nbActions = 0;
    odom = odo;
    nbActionsBase = NULL;


    initialiserTableauDeBase(is_Blue);

}

ListeActions::~ListeActions()
{
    if (actions!=NULL)
    {
        for(int i=0;i<nbActions;i++)
            delete[] actions[i];
        delete[] actions;
    }

    if (nbActionsBase!=NULL)
        delete[] nbActionsBase;

    if ( actionActuelle != NULL)
        delete actionActuelle;

}

void ListeActions::ajouter(ActionBase* actionBase)
{
    if (nbActions<nbActionsMax)
    {
        actions[nbActions]=actionBase;
        nbActions++;
    }
}

void ListeActions::initialiserTableauDeBase(bool is_Blue)
{
    float cote = is_Blue ? 1 : -1;

    actions = new ActionBase*[nbActionsMax];
    nbActionsBase = new int[nbActionsMax];
    for(int i = 0 ; i < nbActionsMax ; i++)
        nbActionsBase[i] = 0;

if (is_Blue) // Violet
{
// HOMOLOGATION

actions[0]=new ActionBase[4];
actions[0][0].position = Position(1100,600*cote);//550*cote);
//actions[0][0].position = Position(760,0*cote);//550*cote);
actions[0][1].position = Position(260,800*cote);//1000*cote);
actions[0][1].balaiGauche = true;
actions[0][2].position = Position(700,800*cote);//550*cote);
actions[0][2].reculer = true; // a reculon
actions[0][2].wait = 5000;
nbActionsBase[0] = 3;

// *******************
/*
actions[0]=new ActionBase[8];
actions[0][0].position = Position(600,250*cote);//550*cote);
actions[0][1].position = Position(1350,760*cote);//1000*cote);
actions[0][2].position = Position(1100,780*cote);//1000*cote);
actions[0][2].reculer=true;
actions[0][2].balaiDroit=true;
actions[0][2].desactiveCapteur=true;
actions[0][2].rateau=false;
actions[0][3].position = Position(650,780*cote);//780*cote);//1000*cote);
actions[0][3].reculer=true;
actions[0][3].balaiDroit=true;
actions[0][3].desactiveCapteur=true;
actions[0][3].rateau=false;
actions[0][4].position = Position(750,1000*cote);//300#1000#//1000*cote);
actions[0][5].position = Position(750,1200*cote);
actions[0][6].position = Position(300,850*cote);//550*cote);
actions[0][6].rateau=false;
actions[0][7].position = Position(700,800*cote);//550*cote);
actions[0][7].reculer = true; // a reculon
nbActionsBase[0] = 7;
*/
}
else //Rouge
{

//HOMOLOGATION
/*
actions[0]=new ActionBase[3];
actions[0][0].position = Position(1100,600*cote);//550*cote);
actions[0][1].position = Position(240,800*cote);//1000*cote);
actions[0][1].balaiDroit = true;
actions[0][2].position = Position(700,670*cote);//550*cote);
actions[0][2].reculer = true; // a reculon
actions[0][2].wait = 1500;
actions[0][3].position = Position(1350,670*cote);//550*cote);
nbActionsBase[0] = 2;
*/
// *******************




actions[0]=new ActionBase[8];

//actions[0][0].position = Position(600,250*cote);//550*cote);
float tmpo = 250.0f*cote;

xxxeteindreLED2();
Position p(600.0f,tmpo);

actions[0][0].position = p;

actions[0][1].position = Position(1350,740*cote);//1000*cote);
actions[0][2].position = Position(1100,750*cote);//1000*cote);
actions[0][2].reculer=true;
actions[0][2].balaiGauche=true;
actions[0][2].desactiveCapteur=true;
actions[0][2].rateau=false;

actions[0][3].position = Position(600,800*cote);//780*cote);//1000*cote);
actions[0][3].reculer=true;
actions[0][3].balaiGauche=true;
actions[0][3].desactiveCapteur=true;
actions[0][3].rateau=false;
actions[0][4].position = Position(720,1000*cote);//300#1000#//1000*cote);
actions[0][5].position = Position(720,1200*cote);
actions[0][6].position = Position(300,850*cote);//550*cote);
actions[0][6].rateau=false;
actions[0][7].position = Position(800,600*cote);//550*cote);
actions[0][7].reculer = true; // a reculon
nbActionsBase[0] = 8;



}

   /* actions[1]=new ActionBase[8];
    actions[1][0].position = Position(740,1400*cote);//3c
    actions[1][1].position = Position(1325,1550*cote);//3d
    actions[1][2].position = Position(1500,1353*cote);//4
    actions[1][3].position = Position(1500,1330*cote);//5
    actions[1][4].position = Position(1300,1330*cote);//6
    actions[1][5].position = Position(930,1170*cote);//7
    actions[1][6].position = Position(300,700*cote);//8
    actions[1][7].position = Position(740,1000*cote);//9
    actions[1][7].reculer = true; // a reculon
    nbActionsBase[1] = 8;*/


    nbActions=1;
}

void ListeActions::supprimerPremiereAction()
{
    if (nbActions!=0)
    {
        delete actions[0];
        for(int i=0;i<nbActions;i++)
        {
            actions[i]=actions[i+1];
            nbActionsBase[i] = nbActionsBase[i+1];
        }
        nbActions--;
    }
    else
    {
        delete actions;
    }
}

Action* ListeActions::creerPremiereAction()
{
    if (actionActuelle != NULL)
        delete actionActuelle;
    if (nbActions!=0)
    {
        actionActuelle = new ActionSuivreChemin(actions[0], nbActionsBase[0],odom);
    }
    else
    {
        actionActuelle = NULL;
    }
    return actionActuelle;
}

Action* ListeActions::getActionActuelle()
{
    return actionActuelle;
}

void ListeActions::reordonnerSerieActions(int n)
{
    if(n>=nbActionsMax)
    return;
    ActionBase** nouveau=new ActionBase*[nbActionsMax];
    for(int i=n;i<nbActions;i++)
    {
        nouveau[i-n]=actions[i];
    }
    for(int i=0;i<n;i++)
    {
        nouveau[i+n]=actions[i];
    }
    delete[] actions;
    actions=nouveau;
}
