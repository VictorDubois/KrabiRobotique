#ifndef LISTEDACTION_H
#define LISTEDACTION_H

#include "positionPlusAngle.h"
#include "odometrie.h"
//#include "commandGoTo.h"
#include "action.h"

class ListeActions
{
    private:

        /// @brief Pointeur vers l'action en cours
        Action* actionActuelle;

        /// @brief Pointeur vers le tableau de tableau d'actions de bases
        ActionBase** actions;

        /// @brief Pointeur vers le tableau enregistrant le nombre d'actions de bases dans chaque actions
        int* nbActionsBase;

        /// @brief Taille maximal du tableau d'actions
        static const int nbActionsMax=30;// taille du tableau

        /// @brief Nombre d'actions dans le tableau
        int nbActions;

        /// @brief Pointeur vers l'odométrie
        Odometrie* odom;

    public:

        /// @brief Constructeur de la classe, construit et initialise le tableau de base
        ListeActions(Odometrie* odo, bool is_blue);

        /// @brief Destructeur de la classe
        ~ListeActions();

        /// @brief Ajoute une action dans le tableau de base a la fin
        void ajouter(ActionBase* action);

        /// @brief Initialise le tableau de base
        void initialiserTableauDeBase(bool is_Blue);

        /// @brief Supprime la premiere action apres que celle-ci ait ete execute
        void supprimerPremiereAction();

        /// @brief lit dans le tableau pour cree l'action a effectuee
        Action* creerPremiereAction();

        /// @brief Retourne l'action en cours
        Action* getActionActuelle();

        /// @brief echange toutes les actions apres l'action numero n avec celles avant, l'action numero n devient la premier dans le tableau
        //bien penser au cas où elle n'est pas dans la liste
        void reordonnerSerieActions(int n);

        //Action* chercherMeilleureAction(int x, int y);
};

#endif
