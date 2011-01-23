#ifndef POSITIONPLUSANGLE_H_INCLUDED
#define POSITIONPLUSANGLE_H_INCLUDED
#include "PositionPlusAngle.h"
#include "Position.h"
#include "Angle.h"

class PositionPlusAngle
{
    public:
    Position position;
    Angle angle;
    PositionPlusAngle(Position pos, Angle ang);
    PositionPlusAngle() { } 
    PositionPlusAngle operator+(const Distance &distance);
    PositionPlusAngle operator-(const Distance &distance);
    PositionPlusAngle operator=(const PositionPlusAngle &positionPlusAngle);
    bool operator==(PositionPlusAngle &p);
    PositionPlusAngle(const PositionPlusAngle &original);
    bool presqueEgales(PositionPlusAngle &positionPlusAngle);
};


#endif // POSITIONPLUSANGLE_H_INCLUDED
