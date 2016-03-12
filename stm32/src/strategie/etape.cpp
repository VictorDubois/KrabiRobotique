#include "etape.h"
#include "dijkstra.h"
#include "actionGoTo.h"

#ifndef ROBOTHW
    #include <QDebug>
#endif

Etape** Etape::tableaudebug = 0;

Etape::Etape(){}

Etape::Etape(int numero)
{
    this->position = Position();
    this->type = POINT_PASSAGE;
    this->state = -1;
    this->numero = numero;
    this->nombreEtapesLieesParFinirEtape = 0;

    postInit();
}

Etape::Etape(int numero, MediumLevelAction* action)
{
    this->position = Position();
    this->type = POINT_PASSAGE;
    this->state = -1;
    this->numero = numero;
    this->nombreEtapesLieesParFinirEtape = 0;

    postInit();

    setAction(action);
}

Etape::Etape(int numero, Position position, EtapeType type, int state, int nombreEtapesLieesParFinirEtape)
{
    this->position = position;
    this->type = type;
    this->state = state;
    this->numero = numero;
    this->nombreEtapesLieesParFinirEtape = nombreEtapesLieesParFinirEtape;
    this->numeroEtapeFinAction = numero;//Par défaut, on fini à l'endroit de l'étape

    //Initialisation du tableau de voisins à vide
    /*for(int i = 0 ; i < nbChildren ; i++)
    {
        this->children[i] = 0;
    }*/

    postInit();
}

Etape::Etape(Position position, int numero, Etape** tableaudebug, EtapeType type, int state, int nombreEtapesLieesParFinirEtape)
{
    this->position = position;
    this->type = type;
    this->state = state;
    this->numero = numero;
    this->nombreEtapesLieesParFinirEtape = nombreEtapesLieesParFinirEtape;

    postInit();
}

void Etape::postInit()
{
    this->action = 0;
    this->nbChildren = 0;
    this->distance = -1;
    this->score = 0;
    this->numeroEtapeFinAction = numero;//Par défaut, on fini à l'endroit de l'étape

    tableaudebug[this->numero] = this;

    this->actionGoTo = new ActionGoTo(getPosition());
}

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

void Etape::setAction(MediumLevelAction *action)
{
    this->action = action;

    if (this->position == Position())
    {
        this->position = action->getGoalPosition();
        this->type = action->getType();

        if (this->actionGoTo != 0)
            delete this->actionGoTo;
        this->actionGoTo = new ActionGoTo(getPosition());
    }
}

MediumLevelAction* Etape::getAction()
{
    return this->action;
}

ActionGoTo* Etape::getActionGoTo()
{
    return this->actionGoTo;
}

void Etape::addVoisin(Etape* newVoisin, bool autreSens)
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

void Etape::reset()
{
    if (this->action != 0)
        this->action->reset();
    if (this->actionGoTo != 0)
        this->actionGoTo->reset();
}


void Etape::setGoBack(bool val)
{
    if (this->action != 0)
        this->action->setGoBack(val);
    if (this->actionGoTo != 0)
        this->actionGoTo->setGoBack(val);
}

void Etape::addVoisin(int newVoisinIndex, bool autreSens)
{
    this->addVoisin(get(newVoisinIndex), autreSens);
}

void Etape::addVoisins(int newVoisinIndex)
{
    this->addVoisin(newVoisinIndex);
}

void Etape::addVoisins(int newVoisinIndex1, int newVoisinIndex2)
{
    this->addVoisin(newVoisinIndex1);
    this->addVoisin(newVoisinIndex2);
}

void Etape::addVoisins(int newVoisinIndex1, int newVoisinIndex2, int newVoisinIndex3)
{
    this->addVoisin(newVoisinIndex1);
    this->addVoisin(newVoisinIndex2);
    this->addVoisin(newVoisinIndex3);
}

void Etape::addVoisins(int newVoisinIndex1, int newVoisinIndex2, int newVoisinIndex3, int newVoisinIndex4)
{
    this->addVoisin(newVoisinIndex1);
    this->addVoisin(newVoisinIndex2);
    this->addVoisin(newVoisinIndex3);
    this->addVoisin(newVoisinIndex4);
}

void Etape::addVoisins(int newVoisinIndex1, int newVoisinIndex2, int newVoisinIndex3, int newVoisinIndex4, int newVoisinIndex5)
{
    this->addVoisin(newVoisinIndex1);
    this->addVoisin(newVoisinIndex2);
    this->addVoisin(newVoisinIndex3);
    this->addVoisin(newVoisinIndex4);
    this->addVoisin(newVoisinIndex5);
}

void Etape::setNumeroEtapeFinAction(int newNumeroEtapeFinAction)
{
    this->numeroEtapeFinAction = newNumeroEtapeFinAction;
}

int Etape::getNumeroEtapeFinAction()
{
    return this->numeroEtapeFinAction;
}

Etape** Etape::initTableauEtapeTotal(int number)
{
    tableaudebug = new Etape*[number];
    for(int i(0); i<number; ++i)
        tableaudebug[i] = 0;
    return tableaudebug;
}

Etape* Etape::get(int index)
{
    if (tableaudebug[index] == 0)
        new Etape(index);
    return tableaudebug[index];
}

Etape** Etape::getTableaudebug()
{
    return tableaudebug;
}

#ifndef ROBOTHW
QString Etape::getNameType(EtapeType type)
{
    switch(type)
    {
    case POINT_PASSAGE:
        return "Passage";
    case DEPART:
        return "Départ";
    case CLAP:
        return "Clap";
    case GOBELET:
        return "Gobelet";
    case RAMASSER_PIED:
        return "Pied";
    case AMPOULE:
        return "Ampoule";
    case TAPIS:
        return "Tapis";
    case DEPOSER_GOBELET:
        return "Déposer Gobelet";
    default:
        return QString::number(type);
    }
}

QString Etape::getShortNameType(EtapeType type)
{
    switch(type)
    {
    case POINT_PASSAGE:
        return "";
    case DEPART:
        return "Start";
    case CLAP:
        return "Clap";
    case GOBELET:
        return "Gob";
    case RAMASSER_PIED:
        return "Pied";
    case AMPOULE:
        return "Amp";
    case TAPIS:
        return "Tapis";
    case DEPOSER_GOBELET:
        return "D.G";
    default:
        return "";
    }
}

#endif
