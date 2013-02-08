#ifndef ACTION_H
#define ACTION_H

#include "positionPlusAngle.h"
#include "odometrie.h"
//#include "commandGoTo.h"
#include "constantes.h"

/** @brief Classe permettant de gérer toutes les actions du robot*/
class Action
{
    public:

        /// @brief Constructeur de la classe
        Action() {}

        /// @brief Destructeur de la classe
        virtual ~Action() {}

        /// @brief Fonction utiliser dans les classes filles pour executer une action
        virtual bool executer() = 0; // renvoit vrai si l'action est terminee
};

/// @brief Ce sont les actions de base que le robot peut faire tels que avancer ou reculer a une position, baisser le balai ou activer un des bras latéral
class ActionBase
{
    public:
    ActionBase();

    Position position;
    bool reculer;
    bool balaiGauche;
    bool balaiDroit;
    bool rateau;
    bool desactiveCapteur;
    /** @brief To wait wait milli-seconde avant de lancer la commande */
    int wait;
};

#endif
