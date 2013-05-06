#ifndef STRATEGIE_H
#define STRATEGIE_H

#ifndef ROBOTHW
#include "element.h"
#endif
/*
#include <stdint.h>
#include "PositionPlusAngle.h"
*/
#include "constantes.h"
#include "command.h"

class Odometrie;    //Pour éviter les dépendance cycliques

/**@brief Classe définissant les actions que va réaliser le robot */
class Strategie
{
    private:

        /**@brief Numéro de l'instruction courante */
        int instruction_nb;

        /**@brief True si une collision a été détecté, false sinon */
        bool collision_detected;

        /**@brief Nombre de collision qu'il y a eu depuis le début. Numéro de l'instruction de collision à réaliser */
        int instruction_collision_nb;

        /**@brief On a besoin de la position du robot pour choisir une stratégie de déplacement */
        Odometrie* odometrie;

        Command* commande;

    public:

        /**@brief On sauvegarde la stratégie en static puisqu'une seul peut avoir lieu en même temps. */
        static Strategie* strategie;

        /**@brief Constructeur prenant en entrée la position du robot et le coté du plateau sur lequel on se trouve */
        Strategie(bool is_blue, Odometrie* odometrie);

        /**@brief Permet de valider une action demandé à la stratégie */
        void update();

        /**@brief True si on est du coté bleu, false sinon */
        bool is_blue;

#ifndef ROBOTHW
	/**@brief */
	void updateElement(unsigned int id, Element elem);
#endif

};

#endif // STRATEGIE_H
