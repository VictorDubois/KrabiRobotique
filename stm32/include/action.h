#ifndef ACTION_H_INCLUDED
#define ACTION_H_INCLUDED

#include "PositionPlusAngle.h"
#include "odometrie.h"
#include "CommandGoTo.h"
#include "variable.h"

/** @brief Classe permettant de gérer toutes les actions du robot*/
class Action {
    public:
        Action() {}
        /** @brief Constructeur de la classe*/
        virtual ~Action() {}
        /** @brief Destructeur de la classe*/
        virtual bool executer() = 0; // renvoit vrai si l'action est terminee
        /** @brief Fonction utiliser dans les classes filles pour executer une action*/
};

class ActionBase
/** @brief Ce sont les actions de base que le robot peut faire tels que avancer ou reculer a une position, baisser le balai ou activer un des bras latéral*/
{
    public:
    ActionBase();

    Position position;
    bool reculer;
    bool balaiGauche;
    bool balaiDroit;
    bool rateau;
};

#endif
