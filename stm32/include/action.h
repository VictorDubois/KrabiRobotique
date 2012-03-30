#ifndef ACTION_H_INCLUDED
#define ACTION_H_INCLUDED

#include "PositionPlusAngle.h"
#include "odometrie.h"
#include "CommandGoTo.h"
#include "variable.h"

class Action {
    public:
        Action() {}
        virtual ~Action() {}
        virtual bool executer() = 0; // renvoit vrai si l'action est terminee
};

class ActionBase
{
    public:
    ActionBase();

    Position position;
    bool reculer;
};


class ActionChercherPiece : public Action
{
    private:
    Position destinationFinale;
    Odometrie* odometrie;
    CommandGoTo* commandActuelle;
    Position positionIntermediaire;
    int nbPositionIntermediaire;
    int numeroPositionSuivante;
    Position positionIntermediaireUn;
    Position positionIntermediaireDeux;

    public:

    ActionChercherPiece(Position destinationFinale, Odometrie* odometrie, bool is_Blue);
    virtual ~ActionChercherPiece();
    virtual bool executer();
};

class ListeDActions {
    private:
        Action* actionActuelle;
        ActionBase** actions;
        int* nbActionsBase;
        static const int nbActionsMax=30;// taille du tableau
        int nbActions;
        Odometrie* odom;
    public:
        ListeDActions(Odometrie* odo);
        ~ListeDActions();
        void ajouter(ActionBase* action);
        void initialiserTableauDeBase();
        void supprimerPremiereAction();
        Action* creerPremiereAction();
        Action* getActionActuelle();
        void reordonnerSerieDAction(int n);
        //bien penser au cas où elle n'est pas dans la liste
        //Action* chercherMeilleureAction(int x, int y);
};

#endif
