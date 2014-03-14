#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H


class ActionManager
{
    public:
        ActionManager();
        virtual ~ActionManager();
        void main();
    protected:
    private:
    vector<Action*> actions;
    Astar astar;
};

#endif // ACTIONMANAGER_H
