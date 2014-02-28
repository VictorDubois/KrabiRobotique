//Prononcer Da_ik_stra
//http://fr.wikipedia.org/wiki/Algorithme_de_Dijkstra

#include "dijkstra.h"
#include <math.h>

Dijkstra::Dijkstra(){}


Dijkstra::Dijkstra(Etape** tableauEtapes, int nbEtapes)
{
    this->tableauEtapes = tableauEtapes;
    this->nombreEtapes = nbEtapes;
}

Etape* Dijkstra::getEtapeCourante()
{
    return tableauEtapes[this->numeroEtapeCourante];
}

int Dijkstra::calculDistanceDirect(Etape* etapeDepart, Etape* etapeArrivee)
{
    //distance quartésienne : d = sqrt(x^2+y^2)
    //sqrt = square root, racine carrée
    //Cette étape est très gourmande en ressources, même si les calculs sont fait sur des entiers.
    //Une solution, vu que le STM32-H405 a plein de mémoire, serait de pré-calculer les distances, et de les stocker.
    //Cela permettrait aussi d'ajuster certaines distances si besoin, pour préférer certains passages à d'autres
    return sqrt(
                    pow(fabs((int) etapeDepart->getPosition().getX()-etapeArrivee->getPosition().getX()),2)+
                    pow(fabs((int) etapeDepart->getPosition().getY()-etapeArrivee->getPosition().getY()),2)
                    );
}

void Dijkstra::setEtapeCourante(int numeroEtapeCourante)
{
    this->numeroEtapeCourante = numeroEtapeCourante;
}

//Calcul des distances de toutes les étapes par rapport à l'étape en cours (étape origine)
void Dijkstra::run()
{
    initialiser();

    mettreAJourVoisins(this->numeroEtapeCourante);

    for(int i = 0 ; i < this->nombreEtapes-2 ; i++)
    {
        this->numeroEtapeCourante = trouverMin(i+1);
        mettreAJourVoisins(this->numeroEtapeCourante);
    }
}

//On réinitialise le tableau avant le commencer une nouvelle recherche
void Dijkstra::initialiser()
{
    for(int i = 0 ; i<this->nombreEtapes ; i++)
    {
        this->tableauEtapes[i]->setDistance(-1);
        if(this->tableauEtapes[i]->getState() != -2)
        {
            this->tableauEtapes[i]->setState(-1);
        }
    }
    this->tableauEtapes[this->numeroEtapeCourante]->setDistance(0);
    this->tableauEtapes[this->numeroEtapeCourante]->setState(0);
}

// Renvoi le numéro de l'étape la plus proche dont on n'a pas encore mis à jour les voisins
int Dijkstra::trouverMin(int classementEtapeMinimale)
{
    int minimum = -1;
    int numeroEtapeLaPlusProche;
    for(int i = 0 ; i < this->nombreEtapes ; i++)
    {
        if(this->tableauEtapes[i]->getState()==-1 && (minimum == -1 || (this->tableauEtapes[i]->getDistance() < minimum && this->tableauEtapes[i]->getDistance() >= 0)))
        {
            minimum = this->tableauEtapes[i]->getDistance();
            numeroEtapeLaPlusProche = i;
        }
    }
    this->tableauEtapes[numeroEtapeLaPlusProche]->setState(classementEtapeMinimale);
    return numeroEtapeLaPlusProche;
}

//Met à jour les voisin de l'étape spécifiée.
void Dijkstra::mettreAJourVoisins(int numeroEtape)
{
    int distanceEtapeCourante = this->tableauEtapes[numeroEtape]->getDistance();
    int distanceChildCourant;
    int distanceEtapeVersChild;

    for(int i = 0 ; i < this->tableauEtapes[numeroEtape]->getNbChildren() ; i++)
    {
        //Si cette étape n'est pas bannie
        if(this->tableauEtapes[numeroEtape]->getChild(i)->getState() > -2)
        {
            distanceChildCourant = this->tableauEtapes[numeroEtape]->getChild(i)->getDistance();
            distanceEtapeVersChild = calculDistanceDirect(this->tableauEtapes[numeroEtape]->getChild(i), this->tableauEtapes[numeroEtape]);

            //Si le chemin vers ce voisin est plus court en passant par l'étape actuelle, mise à jour de ce voisin
            //Si le voisin n'avait pas encore été atteind par un chemin, aors on le met à jour aussi (distanceChildCourant == -1)
            if(distanceChildCourant == -1 || distanceChildCourant > distanceEtapeCourante + distanceEtapeVersChild)
            {
                this->tableauEtapes[numeroEtape]->getChild(i)->setDistance(distanceEtapeCourante + distanceEtapeVersChild);
                this->tableauEtapes[numeroEtape]->getChild(i)->setParent(this->tableauEtapes[this->numeroEtapeCourante]);
            }
        }
    }
}

int Dijkstra::getDistance(int numeroEtape)
{
    return tableauEtapes[numeroEtape]->getDistance();
}

int Dijkstra::getDistance(Etape* etape)
{
    return etape->getDistance();
}
