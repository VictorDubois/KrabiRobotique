#include "PositionPlusAngle.h"

PositionPlusAngle::PositionPlusAngle(Position pos, Angle ang) : position(pos), angle(ang)
{
}

PositionPlusAngle PositionPlusAngle::operator+(const Distance &distance)
{
    return PositionPlusAngle(Position(position.getX() + distance*cos(angle), position.getY() + distance*sin(angle)), angle);
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
        return ((position==p.position) && (angle==p.angle));
    }


 bool PositionPlusAngle::presqueEgales(PositionPlusAngle &positionPlusAngle){
    return(position.presqueEgales(positionPlusAngle.position) && angleEq(angle,positionPlusAngle.angle));
}

PositionPlusAngle::PositionPlusAngle(const PositionPlusAngle &original) : position(original.position), angle(original.angle)
{
}

Position PositionPlusAngle::getPosition(){
    return position;
}

void PositionPlusAngle::setPosition(Position p){
    position=p;
}

Angle PositionPlusAngle::getAngle(){
    return angle;
}

void PositionPlusAngle::setAngle(Angle a){
    angle=a;
}
