#ifndef DEPOSE_FRUITS_H
#define DEPOSE_FRUITS_H

#include "mediumLevelAction.h"
#include "braslateral.h"

class DeposeFruits : public MediumLevelAction
{
    public:
        DeposeFruits(bool isBlue, Position positionDepart, float precision = 30.0f);
        DeposeFruits();
        virtual ~DeposeFruits();

        virtual int update();


    protected:
    private:
        Position positionDepart;
        bool isBlue;
        float precision;
};

#endif // DEPOSE_FRUITS_H
