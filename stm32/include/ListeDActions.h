#ifndef LISTEDACTION_H_INCLUDED
#define LISTEDACTION_H_INCLUDED

#include "PositionPlusAngle.h"
#include "odometrie.h"
#include "CommandGoTo.h"
#include "action.h"

class ListeDActions {
    private:
        Action* actionActuelle;
        /** @brief Pointeur vers l'action en cours*/
        ActionBase** actions;
        /** @brief Pointeur vers le tableau de tableau d'actions de bases*/
        int* nbActionsBase;
        /** @brief Pointeur vers le tableau enregistrant le nombre d'actions de bases dans chaque actions*/
        static const int nbActionsMax=30;// taille du tableau
        /** @brief Taille maximal du tableau d'actions*/
        int nbActions;
        /** @brief Nombre d'actions dans le tableau*/
        Odometrie* odom;
        /** @brief Pointeur vers l'odométrie*/
    public:
        ListeDActions(Odometrie* odo,bool is_blue);
        /** @brief Constructeur de la classe, construit et initialise le tableau de base*/
        ~ListeDActions();
        /** @brief Destructeur de la classe*/
        void ajouter(ActionBase* action);
        /** @brief Ajoute une action dans le tableau de base a la fin*/
        void initialiserTableauDeBase(bool is_Blue);
        /** @brief Initialise le tableau de base*/
        void supprimerPremiereAction();
        /** @brief Supprime la premiere action apres que celle-ci ait ete execute*/
        Action* creerPremiereAction();
        /** @brief lit dans le tableau pour cree l'action a effectuee*/
        Action* getActionActuelle();
        /** @brief Retourne l'action en cours*/
        void reordonnerSerieDAction(int n);
        /** @brief echange toutes les actions apres l'action numero n avec celles avant, l'action numero n devient la premier dans le tableau*/
        //bien penser au cas où elle n'est pas dans la liste
        //Action* chercherMeilleureAction(int x, int y);
};

#endif
