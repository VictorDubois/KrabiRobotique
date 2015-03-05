#ifndef MEDIUMLEVELACTION_H_INCLUDED
#define MEDIUMLEVELACTION_H_INCLUDED

#include "position.h"
#ifndef ROBOTHW
#include <QPainter>;
#endif

class MediumLevelAction
{
    public:
        MediumLevelAction(Position goalPos = Position(0,0));
        virtual ~MediumLevelAction();

        virtual int     update() = 0;
        virtual bool    getGoBack();
        virtual void    collisionAvoided();
        virtual void reset();
        void            setGoBack(bool val);

        #ifndef ROBOTHW
        virtual void paint(QPainter* p);
        #endif

        Position getGoalPosition();

        /** @brief Met à jour le temps restant avant la fin du match */
        void updateTime(int millisecondesRestantes);

    protected:
        Position goalPosition;
        int status;
        bool goBack;

        /** @brief temps restant avant la fin du match */
        int millisecondesRestantes;
    private:
};

#endif // MEDIUMLEVELACTION_H_INCLUDED
