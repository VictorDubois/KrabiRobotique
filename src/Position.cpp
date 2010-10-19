#include "Position.h"
#include <math.h>

/*Toutes les paramètres doivent être donnés en centimètre */

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
    if(this->x.presqueEgales(p.x) && this->y.presqueEgales(p.y))
        return true;
    return false;
    /*if((this->x-p.x)*(this->x-p.x) + (this->y-p.y)*(this->y-p.y) < 1.41)
        return true;
    return false;*/
}

bool Position::operator==(const Position &p){
    return (this->x == p.x && this->y == p.y);
    /*return (this->x-p.x) == 0
           && (this->y-p.y) == 0;*/
}

Distance Position::getNorme(void){
    return Distance(sqrt(x.getValueInMillimeters()*x.getValueInMillimeters()+y.getValueInMillimeters()*y.getValueInMillimeters()));
}

Angle Position::getAngle(void){
    if(x==Distance(0)){
        return y>Distance(0) ? Angle(M_PI_2) : Angle(-M_PI_2);
    }
    else if(x>Distance(0)){
        return Angle(atan(y.getValueInMillimeters()/x.getValueInMillimeters()));
    }
    else {
        double tmp_val = atan(y.getValueInMillimeters()/x.getValueInMillimeters());
        return tmp_val>0 ? Angle(-M_PI+tmp_val) : Angle(M_PI+tmp_val);
    }
}
