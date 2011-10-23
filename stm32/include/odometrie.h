#ifndef ODOMETRIE_H_INCLUDED
#define ODOMETRIE_H_INCLUDED

#include "variable.h"
#include "distance.h"
#include "PositionPlusAngle.h"
#include "quadrature_coder_handler.h"
#include <stdint.h>
#include <math.h>

/**@brief Classe permettant de connaitre la position du robot*/
class Odometrie
{
    public:
        /**@brief Constructeur de l'odometrie
         *@param QuadratureCoderHandler* roueCodeuseGauche pour connaitre le nombre de tour fait par la roue gauche.
         *@param QuadratureCoderHandler* roueCodeuseDroite pour connaitre le nombre de tour fait par la roue droite. */
        Odometrie(QuadratureCoderHandler* roueCodeuseGauche, QuadratureCoderHandler* roueCodeuseDroite);
        /**@brief Fonction utilisé à chaque mise à jour ( 20ms) pour enregistrer la nouvelle position du robot */
        void update();
        /**@brief Pour indiquer au robot qu'il est à une nouvelle position */
        void setPos(PositionPlusAngle p);
        /**@brief Pour récupérer la position du robot */
        PositionPlusAngle getPos();
        /**@brief Pour connaitre la vitesse angulaire du robot */
        Angle getVitesseAngulaire();
        /**@brief Pour connaitre la vitesse linéaire du robot */
        Distance getVitesseLineaire();

    private:
        /**@brief Permet de connaitre le nombre de tick envoyés par la roue codeuse droite donc connaitre le nombre de tour de celle ci */
        QuadratureCoderHandler* roueCodeuseDroite;
        /**@brief Permet de connaitre le nombre de tick envoyés par la roue codeuse gauche donc connaitre le nombre de tour de celle ci */
        QuadratureCoderHandler* roueCodeuseGauche;
        /**@brief Stock la position et l'angle du robot */
        PositionPlusAngle positionPlusAngle;
        /**@brief Stock la vitesse linéaire du robot */
        Distance vitesseLineaire;
        /**@brief Stock la vitesse angulaire du robot */
        Angle vitesseAngulaire;
        /**@brief Stock le nombre de tick de la roue gauche du robot à l'étape précédente pour éviter les incohérences entre deux mesures succéssives */
        int32_t prevDeltaTicksRoueGauche;
        /**@brief Stock le nombre de tick de la roue droite du robot à l'étape précédente pour éviter les incohérences entre deux mesures succéssives */
        int32_t prevDeltaTicksRoueDroite;
        /**@brief taille de l'entraxe du robot */
        const double entraxe;
        /**@brief rayon de la roue codeuse */
        const double rayonRoueCodeuse;
        /**@brief nombre de tick enregistré pour une tour de roue codeuse */
        const double nbTicksParTour;
        /**@brief coéfficient pour relier le nombre de tick de chaque roue à la distance parcouru */
        const double coeffDistance;
        /**@brief coéfficient pour relier le nombre de tick de chaque roue à l'angle réalisé */
        const double coeffAngle;
};

#endif // ODOMETRIE_H_INCLUDED
