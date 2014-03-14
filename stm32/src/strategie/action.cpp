#include "action.h"

typedef struc{
    int posX;
    int posY;
    int errX;
    int errY;
    } Position;

class Action {

public :

    Action::Action(Position n_posIni, Position n_posEnd, int n_priority, bool n_controle, vector<actionneurs> actio): posIni(n_posIni),
            posEnd(n_posEnd), priority(n_priority), controle(n_controle), actionneurs(actio){
    }

    void Action::onCreate(){
        if (controle)
            moManager();
    }

    int Action::calPriority(){
        return astar(posIni);
    }

    void Action::onEnd(){
        priority = 1;
        rangerActionneurs();
        priority = 0;
    }

    void Action::moManager(){
        goToPosIni();
        goToPosEnd();
    }

    void Action::onInterrupt(){
        rangerActionneur();
    }

    void Action::onRun(Position curPos){

    }

    void Action::rangerActionneurs(){
        int i =0;
        for (i=0; i<actionneurs.size();i++){
            actionneurs[i].ranger();
        }
    }

    int Action::getPriority(){
        return priority;
        }



private :

    Position posIni;
    Position posEnd;

    int priority;

//Vrai si l avtion prend le controle de la direction
    bool controle;

    vector<Actionneur*> actionnneurs;

}
