#ifndef ACTIONSUIVRECHEMIN_H
#define ACTIONSUIVRECHEMIN_H

#include "action.h"
#include "odometrie.h"
#include "commandGoTo.h"
#include "bras.h"

class ActionSuivreChemin : public Action
{
    private:

        Bras* bras;

        /** @brief Pointeur vers la premier action*/
        ActionBase* chemin;

        /** @brief Taille du chemin a suivre*/
        int taille;

        /** @brief Action suivante a effectuer dans le chemin*/
        int pointSuivant;

        /** @brief Variable utiliser pour faire demarrer la robot*/
        bool faitquelquechose;

        /** @brief Pointeur vers l'odometrie*/
        Odometrie* odometrie;

        /** @brief Premiere position du robot adverse*/
        Position* positionRobotAdverseUn;

        /** @brief deuxieme position du robot adverse*/
        Position* positionRobotAdverseDeux;

         /** @brief troisieme position du robot adverse*/
        Position* positionRobotAdverseTrois;

       /** @brief Variable utiliser par la strategie d'evitement pour decider d'effectuer la strategie normal *
        *   @return retourne vrai pour decider de la faire */
        bool strategieNormal;

        /** @brief stocke sous forme d'entier le capteurs allumés */
        int nbCapteurs;

    public:

        /** @brief Constructeur du tableau chemin*/
        ActionSuivreChemin(ActionBase* tab, int n, Odometrie* odo);

        /** @brief Destructeur du tableau chemin*/
        virtual ~ActionSuivreChemin();

        /** @brief Suit le chemin imposer par le tableau chemin en gerant les bras et le balai*/
        virtual bool executer();

        /** @brief Regarde s'il y a collision entre notre robot et un element du decore ou un robot adverse *
        *   @return renvoie vrai si il y a collision */
        bool eviterDecoreEtRobot(Position pos,Position* posRobotAdverseUn,Position* posRobotAdverseDeux,Position* posRobotAdverseTrois);

        /** @brief Evalue si le trajet entre la position actuelle et la position objectif est possible, c'est-à-dire s-il n'y a pas de collision *
        *   @return renvoie vrai si il n'y a pas de collision sur le trajet et celui-ci est donc possible*/
        bool trajetPossible(Position objectif,Position* posRobotAdverseUn,Position* posRobotAdverseDeux,Position* posRobotAdverseTrois);

        /** @brief Renvoie un entier correspondant au capteurs ayant detecter un obstacle */
        int intOfSensors();

        /** @brief Affecte les trois valeurs de position du robot adverse en fonction des capteurs allumés */
        void affectePosRobotAdverse(int capteursOuverts, int cote);
};

#endif
