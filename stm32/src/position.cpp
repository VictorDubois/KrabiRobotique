#include <math.h>

#include "position.h"


// Constructeur par défaut avec des coordonnées nulles.
Position::Position()
    : x(0), y(0)
{
}

Position::Position(Distance X, Distance Y)
    : x(X), y(Y)
{
}

Distance Position::getX() const
{
    return x;
}

Distance Position::getY() const
{
    return y;
}

void Position::setX(Distance X)
{
    x = X;
}

void Position::setY(Distance Y)
{
    y = Y;
}

Position Position::operator+(const Position &position) const
{
    Position resultat(x+position.x,y+position.y);
    return resultat;
}

Position Position::operator-(const Position &position) const
{
    Position resultat(x-position.x,y-position.y);
    return resultat;
}

void Position::operator=(Position position)
{

    x = position.x;
    y = position.y;

}

Position Position::operator+=(const Position &position)
{
    this->x+=position.x;
    this->y+=position.y;

    return *this;
}

Position Position::operator-=(const Position &position)
{
    this->x-=position.x;
    this->y-=position.y;

    return *this;
}

bool Position::presqueEgales(const Position &p) const
{
	return (distancePresqueEgales(x, p.x) && distancePresqueEgales(y,p.y));
}

bool Position::operator==(const Position &p) const
{
    return (x == p.x && y == p.y);
}

Distance Position::getNorme() const
{
    return Distance(sqrt(x*x+y*y));
}

Angle Position::getAngle() const
{
	return atan2(y,x);
}
