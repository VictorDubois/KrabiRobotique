#include "ValeursRoues.h"

ValeursRoues::ValeursRoues(uint32_t gauche_d, uint32_t droite_d){
    this->gauche = gauche_d;
    this->droite = droite_d;
}

ValeursRoues::ValeursRoues(){
    this->gauche = 0;
    this->droite = 0;
}

uint32_t ValeursRoues::getRoueGauche(){
    return this->gauche;
}

uint32_t ValeursRoues::getRoueDroite(){
    return this->droite;
}

void ValeursRoues::setRoueGauche(uint32_t gauche_d){
    this->gauche = gauche_d;
}

void ValeursRoues::setRoueDroite(uint32_t droite_d){
    this->droite = droite_d;
}
