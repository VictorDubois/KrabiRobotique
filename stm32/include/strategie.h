#ifndef STRATEGIE_H_INCLUDED
#define STRATEGIE_H_INCLUDED

#ifdef ROBOTHW
#include "quadrature_coder_handler.h"
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "servo.h"
#endif

#ifndef ROBOTHW
#include "element.h"
#endif

#include <stdint.h>
#include "PositionPlusAngle.h"
#include "TrapezoidalCommand.h"
#include <math.h>
#include "variable.h"

class Odometrie;    //Pour éviter les dépendance cycliques

/**@brief Classe définissant les actions que va réaliser le robot */
class Strategie {
    private:
        /**@brief True si on est du coté bleu, false sinon */
        bool is_blue;
        /**@brief Numéro de l'instruction courante */
        int instruction_nb;
        /**@brief True si une collision a été détecté, false sinon */
        bool collision_detected;
        /**@brief Nombre de collision qu'il y a eu depuis le début. Numéro de l'instruction de collision à réaliser */
        int instruction_collision_nb;
        /**@brief On a besoin de la position du robot pour choisir une stratégie de déplacement */
        Odometrie* odometrie;

    public:
        /**@brief On sauvegarde la stratégie en static puisqu'une seul peut avoir lieu en même temps. */
        static Strategie* strategie;
        /**@brief Fonction appellé lorsqu'une collision est détectée */
        void collisionDetected();
        /**@brief Constructeur prenant en entrée la position du robot et le coté du plateau sur lequel on se trouve */
        Strategie(bool is_blue, Odometrie* odometrie);
        /**@brief Permet de valider une action demandé à la stratégie */
        void done();
        /**@brief Fonction lançant l'exécution de l'instruction n */
        void doNthInstruction(uint16_t n);
#ifndef ROBOTHW
	/**@brief */
	void updateElement(unsigned int id, Element elem);
#endif

};

class Action {
    public:
        Action();
        virtual ~Action();
        virtual bool executer() = 0;
};

class ListeDActions {
    private:
        Action** actions;
        const int nbActionsMax=30;// taille du tableau
        int nbActions;
    public:
        ListeDActions();
        ~ListeDActions();
        void ajouter(Action* action);
        void initialiserTableauDeBase();
        void supprimerPremiereAction();
        Action* premiereAction();
        void reordonnerSerieDAction(int n);
        //bien penser au cas où elle n'est pas dans la liste
        Action* chercherMeilleureAction(int x, int y);
};

#endif // STRATEGIE_H_INCLUDED
