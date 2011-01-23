#include "Position.h"
#include "distance.h"
#include <math.h>

Position::Position(Distance blah_x, Distance blah_y) : x(blah_x), y(blah_y){
}

Position Position::operator+(const Position &position){
    Position resultat(x+position.x,y+position.y);
    return resultat;

}

Position Position::operator-(const Position &position){
    Position resultat(x-position.x,y-position.y);
    return resultat;
}

Position Position::operator=(const Position &position){
    this->x=position.x;
    this->y=position.y;

    return *this;
}

Position Position::operator+=(const Position &position){
    this->x+=position.x;
    this->y+=position.y;

    return *this;
}

Position Position::operator-=(const Position &position){
    this->x-=position.x;
    this->y-=position.y;

    return *this;
}

bool Position::presqueEgales(const Position &p){
	return ::presqueEgales(x, p.x) && ::presqueEgales(y,p.y);
}

bool Position::operator==(const Position &p){
    return (this->x == p.x && this->y == p.y);
}

Distance Position::getNorme(){
    return Distance(sqrt(x*x+y*y));
}

Angle Position::getAngle()
{
	return atan2(y,x);
}
