#ifndef ACTIONSUIVRECHEMIN_H_INCLUDED

#define ACTIONSUIVRECHEMIN_H_INCLUDED

#include "action.h"
#include "odometrie.h"
#include "CommandGoTo.h"

class ActionSuivreChemin : public Action
{
    ActionBase* chemin;
    int taille;
    int pointSuivant;
    bool faitquelquechose;
    Odometrie* odometrie;
    public:
        ActionSuivreChemin(ActionBase* tab, int n, Odometrie* odo);

        virtual ~ActionSuivreChemin();

        virtual bool executer();

};

#endif
