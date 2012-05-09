#ifndef ACTIONSUIVRECHEMIN_H_INCLUDED

#define ACTIONSUIVRECHEMIN_H_INCLUDED

#include "action.h"
#include "odometrie.h"
#include "CommandGoTo.h"

class ActionSuivreChemin : public Action
{
    ActionBase* chemin;
    /** @brief Pointeur vers la premier action*/
    int taille;
    /** @brief Taille du chemin a suivre*/
    int pointSuivant;
    /** @brief Action suivante a effectuer dans le chemin*/
    bool faitquelquechose;
    /** @brief Variable utiliser pour faire demarrer la robot*/
    Odometrie* odometrie;
    /** @brief Pointeur vers l'odometrie*/
    Position* positionRobotadverse;
    /** @brief */
    public:
        ActionSuivreChemin(ActionBase* tab, int n, Odometrie* odo);
        /** @brief Constructeur du tableau chemin*/

        virtual ~ActionSuivreChemin();
        /** @brief Destructeur du tableau chemin*/

        virtual bool executer();
        /** @brief Suit le chemin imposer par le tableau chemin*/

};

#endif
