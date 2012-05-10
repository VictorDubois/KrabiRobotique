#include "ListeDActions.h"
#include "actionSuivreChemin.h"

ListeDActions::ListeDActions(Odometrie* odo,bool is_Blue)
{
    actionActuelle = NULL; actions = NULL;
    nbActions = 0;
    odom = odo;
    nbActionsBase = NULL;
    initialiserTableauDeBase(is_Blue);
}

ListeDActions::~ListeDActions()
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

void ListeDActions::ajouter(ActionBase* actionBase)
{
    if (nbActions<nbActionsMax)
    {
        actions[nbActions]=actionBase;
        nbActions++;
    }
}

void  ListeDActions::initialiserTableauDeBase(bool is_Blue)
{
    int cote = is_Blue? 1:-1;
       actions=new ActionBase*[nbActionsMax];
    nbActionsBase = new int[nbActionsMax];
    for(int i = 0 ; i < nbActionsMax ; i++)
        nbActionsBase[i] = 0;

    actions[0]=new ActionBase[4];
    actions[0][0].position = Position(800,200*cote);//1
  //  actions[0][0].position = Position(300,250*cote);//1
    actions[0][1].position = Position(1000,460*cote);//1
  //  actions[0][1].reculer = true;//1
  //  actions[0][1].position = Position(1250,250*cote);//1
    actions[0][2].position = Position(900,500*cote);//1
    actions[0][3].position = Position(300,785*cote);//2
  //  actions[0][4].position = Position(360,800*cote);//3
  //  actions[0][3].position = Position(740,785*cote);//3b
  //  actions[0][3].reculer = true; // a reculon
    nbActionsBase[0] = 4;


/*    actions[0]=new ActionBase[1];
    actions[0][0].position = Position(1500,500);//1
    nbActionsBase[0] = 2;
*/

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

void ListeDActions::supprimerPremiereAction()
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

Action* ListeDActions::creerPremiereAction()
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

Action* ListeDActions::getActionActuelle()
{
    return actionActuelle;
}

void ListeDActions::reordonnerSerieDAction(int n)
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
