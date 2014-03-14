#ifndef ACTION_H_INCLUDED
#define ACTION_H_INCLUDED



#endif // ACTION_H_INCLUDED

class Action{

public :

void onCreate();
void onEnd();
void onInterrupt();
void onRun();
int calPriority();
void moManager();
void rangerActionneurs();
int getPriority();

private :

Position posIni;
Position posEnd

int priority;
bool controle;

vector<actionneurs*>




}
