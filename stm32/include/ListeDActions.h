#ifndef LISTEDACTION_H_INCLUDED
#define LISTEDACTION_H_INCLUDED

#include "PositionPlusAngle.h"
#include "odometrie.h"
#include "CommandGoTo.h"
#include "action.h"

class ListeDActions {
    private:
        Action* actionActuelle;
        ActionBase** actions;
        int* nbActionsBase;
        static const int nbActionsMax=30;// taille du tableau
        int nbActions;
        Odometrie* odom;
    public:
        ListeDActions(Odometrie* odo,bool is_blue);
        ~ListeDActions();
        void ajouter(ActionBase* action);
        void initialiserTableauDeBase(bool is_Blue);
        void supprimerPremiereAction();
        Action* creerPremiereAction();
        Action* getActionActuelle();
        void reordonnerSerieDAction(int n);
        //bien penser au cas où elle n'est pas dans la liste
        //Action* chercherMeilleureAction(int x, int y);
};

#endif
