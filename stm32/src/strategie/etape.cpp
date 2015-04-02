#include "etape.h"
#include "dijkstra.h"
#ifndef ROBOTHW
    #include <QDebug>
#endif

Etape::Etape(Position position, /*int nbChildren, */int numero, Etape** tableauEtapesTotal, EtapeType type = POINT_PASSAGE, int state=-1, int nombreEtapesLieesParFinirEtape = 0)
{
    this->position = position;
    //this->children = new Etape*[nbChildren];
    this->type = type;
    this->state = state;
    //this->nbChildren = nbChildren;
    this->nbChildren = 0;
    this->distance = -1;
    this->numero = numero;
    this->nombreEtapesLieesParFinirEtape = nombreEtapesLieesParFinirEtape;
    this->score = 0;

    //Initialisation du tableau de voisins à vide
    for(int i = 0 ; i < nbChildren ; i++)
    {
        this->children[i] = 0;
    }

    tableauEtapesTotal[numero] = this;
}

Etape::Etape(){}

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
    if(!aEviter())
    {
        this->type = (EtapeType)(this->type + ROBOT_VU_ICI);
    }
}

int Etape::getNumero()
{
    return this->numero;
}

bool Etape::aEviter()
{
    if(((int) this->getEtapeType()) > ROBOT_VU_ICI-1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Etape::oublieRobotVu()
{
    if(this->aEviter())
    {
        //On oublie qu'on a vu un robot
        this->setEtapeType((EtapeType) ((int)this->getEtapeType() - ROBOT_VU_ICI));
    }
}

int* Etape::getDistances()
{
    return this->distances;
}

void Etape::setDistances(int* distances)
{
    this->distances = distances;
}

void Etape::computeChildDistances(){
    this->distances = new int[this->nbChildren];

    for(int i=0; i<this->nbChildren; i++)
    {
        this->distances[i] = Dijkstra::calculDistanceDirect(this->children[i], this);
    }
}

int* Etape::getEtapesLieesParFinirEtape()
{
    return this->numerosEtapesLieesParFinirEtape;
}

void Etape::setEtapesLieesParFinirEtape(int* numerosEtapesLieesParFinirEtape)
{
    this->numerosEtapesLieesParFinirEtape = numerosEtapesLieesParFinirEtape;
}

int Etape::getNombreEtapesLieesParFinirEtape()
{
    return this->nombreEtapesLieesParFinirEtape;
}

void Etape::finir(void)
{
    if(this->type == FRUIT)
    {
        this->type = POINT_PASSAGE;
    }
}

void Etape::setScore(int score)
{
    this->score = score;
}

int Etape::getScore()
{
    return this->score;
}

Etape* Etape::addVoisin(Etape* newVoisin, bool autreSens)
{
    if(this->nbChildren==0)
    {
        this->children = new Etape*[1];
        this->children[0] = newVoisin;
        this->nbChildren++;
    }
    else
    {
        Etape** temp = new Etape*[nbChildren];
        for(int i=0; i<nbChildren; i++)
        {
            temp[i] = this->children[i];
        }
        this->children = new Etape*[nbChildren+1];
        for(int i=0; i<nbChildren; i++)
        {
            this->children[i] = temp[i];
        }
        delete[] temp;
        this->children[nbChildren] = newVoisin;
        this->nbChildren++;
    }


    /*int i = 0;
    //On cherche le premier voisin non-initialisé
    while(this->children[i]!=0 && i < this->nbChildren)
    {
        i++;
    }
    //Erreur, il y a trop de voisins !
    if (i == nbChildren)
    {
#ifndef ROBOTHW
        qDebug() << "ERREUR, TROP DE VOISINS !!!";
#endif
    }
    this->children[i] = newVoisin;
    */
    if (autreSens)
    {
        newVoisin->addVoisin(this, false);
    }
}
