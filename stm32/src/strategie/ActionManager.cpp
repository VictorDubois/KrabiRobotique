#include "ActionManager.h"

class ActionManager{
    ActionManager::ActionManager()
    {
        //ctor
    }

    ActionManager::~ActionManager()
    {
        //dtor
    }

    void ActionManager::main(){
        while(1){
            int i = 0;
            for (i=0; i<actions.size(); i++)
                actions[i].calPriority();
            int mini = 500;
            int pos = 0;
            for (i=0; i<actions.size();i++){
                if (actions[i].getPriority() < mini)
                    mini = actions[i].getPriority();
                    pos = i;
                    }
            actions[i].onCreate();
            while (1){
                if(accessible(position))
                    actions[i].onRun();
                else
                    actions[i].onInterrupt();
                    evitement();
            }
        }
    }

    private:
    vector<Action*> actions;
}
