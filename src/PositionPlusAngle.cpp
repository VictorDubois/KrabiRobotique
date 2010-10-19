#include "PositionPlusAngle.h"
#include "Position.h"
#include "Angle.h"
#include <math.h>

PositionPlusAngle::PositionPlusAngle(Position pos, Angle ang) : position(pos), angle(ang)
{
}

PositionPlusAngle PositionPlusAngle::operator+(const Distance &distance)
{
    return PositionPlusAngle(Position(position.x.getValueInMillimeters() + distance.getValueInMillimeters()*cos(angle.getValueInRadian()), position.y.getValueInMillimeters() + distance.getValueInMillimeters()*sin(angle.getValueInRadian())), angle);
}

PositionPlusAngle PositionPlusAngle::operator-(const Distance &distance)
{
    return *this + (-distance);
}

PositionPlusAngle PositionPlusAngle::operator=(const PositionPlusAngle &positionPlusAngle)
{
    position=positionPlusAngle.position;
    angle=positionPlusAngle.angle;

    return *this;
}

bool PositionPlusAngle::operator==(PositionPlusAngle &p)
    {
        if ((position==p.position) && (angle==p.angle))
            return true;
        return false;
    }


 bool PositionPlusAngle::presqueEgales(PositionPlusAngle &positionPlusAngle){
    if((position.presqueEgales(positionPlusAngle.position)) && (angle.presqueEgales(positionPlusAngle.angle)))
        return true;
    return false;
}

PositionPlusAngle::PositionPlusAngle(const PositionPlusAngle &original) : position(original.position), angle(original.angle)
{
}


