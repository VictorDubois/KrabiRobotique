#ifndef MEDIUMLEVELACTION_H_INCLUDED
#define MEDIUMLEVELACTION_H_INCLUDED

#include "lowLevelAction.h"
#include "position.h"

class MediumLevelAction {

private:
    LowLevelAction* actionsToDo[10];
    int numberOfActions;
	int status;
	Position robotPosition;

public:
    MediumLevelAction(Position position = Position(-1,-1), int numberOfActions = 0);
    virtual ~MediumLevelAction();
	/**
	 * Renvoie la variable statut.
	 * Statut = n<2: réservé pour besoins futurs
	 * Statut = -2 : l'action peut être mise à jour par la suite mais ne nécessite pas un monopole
	 * Statut = -1 : l'action est terminée, ne nécessite plus de mise à jour
	 * Statut = 0  : l'action n'a pas été commencée
	 * Statut = 1 : l'action a été commencée
	 * Statut = n>1 : utilisé par la sous-classe pour gérer ou elle en est
	 */
	virtual int update();

    Position getRobotPosition();

    void setRobotPosition(Position position);

	int getStatus();

	void setStatus(int status);
};
#endif
