#ifndef ETEINDREBOUGIEV2_H_INCLUDED
#define ETEINDREBOUGIEV2_H_INCLUDED

#include "mediumLevelAction.h"

class EteindreBougieV2 : public MediumLevelAction
{
    public:
        EteindreBougieV2(Position pos, float angle, bool bas, bool check, bool mine = false, bool bvr = true);
        virtual ~EteindreBougieV2();

        void setBleuVersRouge(bool bleuVrouge);
        int update();
    protected:
    private:
        float angleToHave;
        bool bleuVersRouge;
        bool bougieBasse;
        bool checked;
        bool mustPress;
};

#endif // ETEINDREBOUGIEV2_H_INCLUDED
