#ifndef MEDIUMLEVELACTION_H_INCLUDED
#define MEDIUMLEVELACTION_H_INCLUDED

#include "vector.h"
#include "lowLevelAction.h"

class MediumLevelAction {

private:
	vector<LowLevelAction*> actionsToDo;
	int status;
	int robotPosition[2];

public:
    MediumLevelAction(int posX = -1, int posY = -1, vector<LowLevelAction*> actions = vector<LowLevelAction*>(0));
    virtual ~MediumLevelAction();
	/**
	 * Renvoie la variable statut.
	 * Statut = n<2: réservé pour besoins futurs
	 * Statut = -2 : l'action peut être mise à jour par la suite mais ne nécessite pas un monopole
	 * Statut = -1 : l'action est terminée, ne nécessite plus de mise à jour
	 * Statut = 0  : l'action n'a pas été commencée
	 * Statut = 1 : l'action a été commencée
	 * Statut = n>1 : utilisé par la sous-classe pour gérer ou elle en est
	 */
	virtual int update();

	void getRobotPosition(int* ptr);

	void setRobotPosition(int robotPosition[2]);

	int getStatus();

	void setStatus(int status);
};
#endif
