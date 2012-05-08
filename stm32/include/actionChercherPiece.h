#ifndef ACTIONCHERCHERPIECE_H_INCLUDED

#define ACTIONCHERCHERPIECE_H_INCLUDED

#include "PositionPlusAngle.h"
#include "odometrie.h"
#include "CommandGoTo.h"
#include "action.h"

/** @brief Classe permettant d'éviter les totems*/
class ActionChercherPiece : public Action
{
    private:
    Position destinationFinale;
    /** @brief Variable enregistrant l'objectif*/
    Odometrie* odometrie;
    /** @brief Pointeur vers l'odometrie*/
    CommandGoTo* commandActuelle;
    /** @brief Pointeur vers la command actuelle*/
    Position positionIntermediaire;
    /** @brief variable enregistrant une des position intermediaire cree*/
    int nbPositionIntermediaire;
    /** Nombre de position intermediaire*/
    int numeroPositionSuivante;
    /** @brief Numero de la position suivante a atteindre*/
    Position positionIntermediaireUn;
    /** @brief Premiere position intermediaire*/
    Position positionIntermediaireDeux;
    /** @brief Seconde position inermediaire*/

    public:

    ActionChercherPiece(Position destinationFinale, Odometrie* odometrie, bool is_Blue);
    /** @brief Fonction qui contourne les totems si besoin*/
    virtual ~ActionChercherPiece();
    /** @brief Destructeur*/
    virtual bool executer();
    /** @brief Calcul la quelle position intermediaire a atteindre*/
};

#endif
