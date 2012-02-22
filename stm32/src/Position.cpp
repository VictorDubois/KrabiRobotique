#include "Position.h"

Position::Position(Distance blah_x, Distance blah_y) : x(blah_x), y(blah_y){
}

Distance Position::getX(){
    return x;
}

Distance Position::getY(){
    return y;
}

void Position::setX(Distance x){
    this->x=x;
}

void Position::setY(Distance y){
    this->y=y;
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
	return DistancePresqueEgales(x, p.x) && DistancePresqueEgales(y,p.y);
}

bool Position::operator==(const Position &p){
    return (this->x == p.x && this->y == p.y);
}

float sqrtx(float x)
{
    float h=x-1;
    return 1 + h*(0.5-h*(0.125+h*(0.0625-h*0.0390625)));
}

Distance Position::getNorme(){
    return Distance(sqrtx(x*x+y*y));
}

Angle atanx(float x)
{
    float y = x*x;
    return x*(1-y*(0.3333333333+y*(0.2-y*0.142857143)));
}

Angle atan2x(float y,float x)
{
    Angle f = atanx (fabs(y/x));
    if (y>0)
    {
        return (x>0 ? f : (x=0 ? M_PI_2 : (M_PI-f) ));
    }
    else
    {
        return (x>0 ? -f : (x=0 ? -M_PI_2 : -(M_PI-f) ));
    }
}

Angle Position::getAngle()
{
	return atan2x(y,x);
}
