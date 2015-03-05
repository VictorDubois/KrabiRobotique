#ifndef FRESQUE_H
#define FRESQUE_H
#include "sensors.h"
#include "mediumLevelAction.h"

class Fresque : public MediumLevelAction
{
    public:
        Fresque(bool isBlue, Position positionDepart, Position positionFin, float precision = 30.0f);
        Fresque();
        virtual ~Fresque();
        
        virtual int update();

    protected:
    private:
        Sensors* sensor;
        Position positionDepart;
        bool isBlue;
        float precision;
        Position positionIntermediaire, positionFin;
        int tempsColleALaFresque, tempsRecule;
};

#endif // FRESQUE_H
