#include <math.h>

#include "positionPlusAngle.h"

PositionPlusAngle::PositionPlusAngle()
{
}

PositionPlusAngle::PositionPlusAngle(const Position& pos, Angle ang)
    : position(pos), angle(ang)
{
}

PositionPlusAngle::PositionPlusAngle(const PositionPlusAngle& original)
    : position(original.position), angle(original.angle)
{
}

PositionPlusAngle PositionPlusAngle::operator+(Distance distance) const
{
    return PositionPlusAngle(Position(position.getX() + distance*cos(angle), position.getY() + distance*sin(angle)), angle);
}

PositionPlusAngle PositionPlusAngle::operator+(const PositionPlusAngle& posAngAdd) const
{
    return PositionPlusAngle(Position(position.getX() + posAngAdd.getPosition().getX(), position.getY() + posAngAdd.getPosition().getY()), angle + posAngAdd.getAngle());
}

PositionPlusAngle PositionPlusAngle::operator-(Distance distance) const
{
    return *this + (-distance);
}

const PositionPlusAngle& PositionPlusAngle::operator=(const PositionPlusAngle& positionPlusAngle)
{
    position = positionPlusAngle.position;
    angle = positionPlusAngle.angle;

    return *this;
}

bool PositionPlusAngle::operator==(const PositionPlusAngle& p) const
{
    return ((position==p.position) && (angle==p.angle));
}

bool PositionPlusAngle::presqueEgales(const PositionPlusAngle& positionPlusAngle) const
{
    return(position.presqueEgales(positionPlusAngle.position) && angleEq(angle,positionPlusAngle.angle));
}

Position PositionPlusAngle::getPosition() const
{
    return position;
}

void PositionPlusAngle::setPosition(const Position& p)
{
    position = p;
}

Angle PositionPlusAngle::getAngle() const
{
    return angle;
}

void PositionPlusAngle::setAngle(Angle a)
{
    angle = a;
}

void PositionPlusAngle::setX(Distance X)
{
    position.setX(X);
}

void PositionPlusAngle::setY(Distance Y)
{
    position.setY(Y);
}
