#include "etape.h"

Etape::Etape(Position position, Etape** children, int nbChildren, int numero, EtapeType type = POINT_PASSAGE, int state=-1)
{
    this->position = position;
    this->children = children;
    this->type = type;
    this->state = state;
    this->nbChildren = nbChildren;
    this->distance = -1;
    this->numero = numero;
}

Etape::Etape(){};

Etape* Etape::getChild(int nb){
    return this->children[nb];
}

Etape** Etape::getChildren(){
    return this->children;
}

Etape* Etape::getParent(){
    return this->parent;
}

Position Etape::getPosition()
{
    return this->position;
}

int Etape::getState(){
    return this->state;
}

void Etape::setState(int state){
    this->state = state;
}

int Etape::getDistance(){
    return this->distance;
}

void Etape::setDistance(int distance){
    this->distance = distance;
}

void Etape::setParent(Etape* parent){
    this->parent = parent;
}

int Etape::getNbChildren(){
    return this->nbChildren;
}

void Etape::setChildren(Etape** children)
{
    this->children = children;
}

Etape::EtapeType Etape::getEtapeType()
{
    return this->type;
}

void Etape::setEtapeType(Etape::EtapeType type)
{
    this->type = type;
}

void Etape::robotVu()
{
    this->type = (EtapeType)(this->type + 20);
}

int Etape::getNumero()
{
    return this->numero;
}
