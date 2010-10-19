#include "distance.h"
#include <math.h>


/*Toutes les paramètres doivent être donnés en centimètre */

Distance::Distance(){
    this->value=0;
}

Distance::Distance(float distance_en_millimetres){
    this->value=distance_en_millimetres;
}

Distance Distance::operator+(const Distance &dist){
    Distance resultat(this->value + dist.value);
    return resultat;
}

Distance Distance::operator*(const Distance &dist){
    Distance resultat(this->value * dist.value);
    return resultat;
}

Distance Distance::operator*(float dist){
    Distance resultat(this->value * dist);
    return resultat;
}

Distance Distance::operator-(const Distance &dist){
    Distance resultat(this->value - dist.value);
    return resultat;
}

Distance Distance::operator-() const
{
    return Distance(-value);
}

Distance Distance::operator=(const Distance &dist){
    this->value=dist.value;

    return *this;
}

Distance Distance::operator+=(const Distance &dist){
    this->value += dist.value;
    return *this;
}

Distance Distance::operator-=(const Distance &dist){
    this->value -= dist.value;
    return *this;
}

bool Distance::presqueEgales(const Distance &d){
    if(fabs(this->value - d.value) < /*0.44*/10)
        return true;
    return false;
}

bool Distance::operator>(const Distance &dist){
    return this->value > dist.value;
}

bool Distance::operator<(const Distance &dist){
    return this->value < dist.value;
}

bool Distance::operator==(const Distance &d){
    return (this->value == d.value);
}

float Distance::getValueInMillimeters() const {
    return value;
}
