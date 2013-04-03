#ifndef MEDIUMLEVELACTION_H_INCLUDED
#define MEDIUMLEVELACTION_H_INCLUDED

#include "lowLevelAction.h"
#include "position.h"

enum MEDIUM_LEVEL_ACTION_TYPE
{
    RAMASSER_VERRE,
    ETEINDRE_BOUGIE,
    DEPOSER_VERRES
};

class MediumLevelAction
{

public:
    MediumLevelAction(Position position = Position(-1,-1), int numberOfActions = 0, MEDIUM_LEVEL_ACTION_TYPE type = RAMASSER_VERRE);
    virtual ~MediumLevelAction();
	/**
	 * Renvoie la variable statut.
     * Statut = n<2: réservé pour besoins éventuels
	 * Statut = -2 : l'action peut être mise à jour par la suite mais ne nécessite pas un monopole
	 * Statut = -1 : l'action est terminée, ne nécessite plus de mise à jour
     * Statut = 0  : l'action n'a pas été commencée
     * Statut = n>0 : l'action a été commencée, utilisé par la sous-classe pour gérer ou elle en est
	 */
    virtual int update();

    Position getRobotPosition();

    void setRobotPosition(Position position);

	int getStatus();

	void setStatus(int status);
    void addLowLevelAction(LowLevelAction* action);
    MEDIUM_LEVEL_ACTION_TYPE getType();
    bool getGoBack();

protected:
    LowLevelAction* actionsToDo[10];
    int numberOfActions;
    int status;
    Position robotPosition;
    MEDIUM_LEVEL_ACTION_TYPE type;

};
#endif
