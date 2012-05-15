#ifndef ACTIONSUIVRECHEMIN_H_INCLUDED

#define ACTIONSUIVRECHEMIN_H_INCLUDED

#include "action.h"
#include "odometrie.h"
#include "CommandGoTo.h"

class ActionSuivreChemin : public Action
{
    ActionBase* chemin;
    /** @brief Pointeur vers la premier action*/
    int taille;
    /** @brief Taille du chemin a suivre*/
    int pointSuivant;
    /** @brief Action suivante a effectuer dans le chemin*/
    bool faitquelquechose;
    /** @brief Variable utiliser pour faire demarrer la robot*/
    Odometrie* odometrie;
    /** @brief Pointeur vers l'odometrie*/
    Position* positionRobotAdverseUn;
    /** @brief Premiere position du robot adverse*/
    Position* positionRobotAdverseDeux;
    /** @brief deuxieme position du robot adverse*/
    Position* positionRobotAdverseTrois;
    /** @brief troisieme position du robot adverse*/
    bool strategieNormal;
    /** @brief Variable utiliser par la strategie d'evitement pour decider d'effectuer la strategie normal *
    *   @return retourne vrai pour decider de la faire */
    int nbCapteurs;
    /** @brief stocke sous forme d'entier le capteurs allumés */
    public:
        ActionSuivreChemin(ActionBase* tab, int n, Odometrie* odo);
        /** @brief Constructeur du tableau chemin*/

        virtual ~ActionSuivreChemin();
        /** @brief Destructeur du tableau chemin*/

        virtual bool executer();
        /** @brief Suit le chemin imposer par le tableau chemin en gerant les bras et le balai*/

        bool eviterDecoreEtRobot(Position pos,Position* posRobotAdverseUn,Position* posRobotAdverseDeux,Position* posRobotAdverseTrois);
        /** @brief Regarde s'il y a collision entre notre robot et un element du decore ou un robot adverse *
        *   @return renvoie vrai si il y a collision */

        bool trajetPossible(Position objectif,Position* posRobotAdverseUn,Position* posRobotAdverseDeux,Position* posRobotAdverseTrois);
        /** @brief Evalue si le trajet entre la position actuelle et la position objectif est possible, c'est-à-dire s-il n'y a pas de collision *
        *   @return renvoie vrai si il n'y a pas de collision sur le trajet et celui-ci est donc possible*/

        int intOfSensors();
        /** @brief Renvoie un entier correspondant au capteurs ayant detecter un obstacle */

        void affectePosRobotAdverse(int capteursOuverts, int cote);
        /** @brief Affecte les trois valeurs de position du robot adverse en fonction des capteurs allumés */
};

#endif
