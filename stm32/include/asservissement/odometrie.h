#ifndef ODOMETRIE_H
#define ODOMETRIE_H

#include "constantes.h"
#include "angle.h"
#include "distance.h"
#include "positionPlusAngle.h"
#include "quadratureCoderHandler.h"
#include <stdint.h>
#include <math.h>

#ifndef ROBOTHW

// pour le simulateur
class Odometrie
{
    private:
        class Robot* robot;

    public:
        Odometrie(Robot* robot);
        PositionPlusAngle getPos() const;
        void setPos(const PositionPlusAngle& p);
        Angle getVitesseAngulaire() const;
        Distance getVitesseLineaire() const;
        float getInterAxisDistance();
        float getWheelSize();
        void setSettings(float interAxisDistance, float wheelSize);

        void update() {};
        /// @brief Attribue de classe contenant un pointeur vers l'unique instance de la classe odometrie executé lors de notre programme
        static Odometrie* odometrie;
};

#else
// pour le vrai robot


/// @brief Classe permettant de connaitre la position du robot
class Odometrie
{
    public:

        /**@brief Constructeur de l'odométrie
         *@param QuadratureCoderHandler* roueCodeuseGauche pour connaitre le nombre de tour fait par la roue gauche.
         *@param QuadratureCoderHandler* roueCodeuseDroite pour connaitre le nombre de tour fait par la roue droite. */
        Odometrie(QuadratureCoderHandler* roueCodeuseGauche, QuadratureCoderHandler* roueCodeuseDroite);

        /**@brief Destructeur de la classe */
        ~Odometrie();

        /**@brief Fonction utilisé à chaque mise à jour ( 20ms) pour enregistrer la nouvelle position du robot */
        void update();

        /**@brief Pour indiquer au robot qu'il est à une nouvelle position */
        void setPos(const PositionPlusAngle& p);

        /**@brief Pour récupérer la position du robot */
        PositionPlusAngle getPos() const;

        /**@brief Pour connaitre la vitesse angulaire du robot */
        Angle getVitesseAngulaire() const;

        /**@brief Pour récupérer l'angle absolu du robot */
        Angle getAbsoluteAngle() const;

        /**@brief Pour connaitre la vitesse linéaire du robot */
        Distance getVitesseLineaire() const;

        float getInterAxisDistance();

        float getWheelSize();

        void setSettings(float interAxisDistance, float wheelSize);

        /**@brief Attribue de classe contenant un pointeur vers l'unique instance de la classe odometrie executé lors de notre programme*/
        static Odometrie* odometrie;

        /**@brief Permet de connaitre le nombre de tick envoyés par la roue codeuse droite donc connaitre le nombre de tour de celle ci */
        QuadratureCoderHandler* roueCodeuseDroite;

        /**@brief Permet de connaitre le nombre de tick envoyés par la roue codeuse gauche donc connaitre le nombre de tour de celle ci */
        QuadratureCoderHandler* roueCodeuseGauche;

        /**@brief Stock la position et l'angle du robot */
        PositionPlusAngle positionPlusAngle;

        /**@brief Stock la vitesse linéaire du robot */
        Vitesse vitesseLineaire;

        /**@brief Stock la vitesse angulaire du robot */
        VitesseAngulaire vitesseAngulaire;

        /**@brief Stock le nombre de tick de la roue gauche du robot à l'étape précédente pour éviter les incohérences entre deux mesures succéssives */
        static const int tailleTabPrevTicks = 2;
        int32_t prevDeltaTicksRoueGauche[tailleTabPrevTicks];

        /**@brief Stock le nombre de tick de la roue droite du robot à l'étape précédente pour éviter les incohérences entre deux mesures succéssives */
        int32_t prevDeltaTicksRoueDroite[tailleTabPrevTicks];

        /**@brief taille de l'entraxe du robot */
        double entraxe;

        /**@brief rayon de la roue codeuse */
        double rayonRoueCodeuse;

        /**@brief nombre de tick enregistré pour une tour de roue codeuse */
        double nbTicksParTour;

        /**@brief coefficient pour relier le nombre de ticks de chaque roue à la distance parcouru */
        double coeffDistance;

        /**@brief coefficient pour relier le nombre de ticks de chaque roue à l'angle réalisé */
        double coeffAngle;

        // position et angle plus précis
        double posX, posY, ang;

        /** @brief Permet de définir une nouvelle valeur pour la position x du robot
        *   @param x Nouvelle position x du robot */
        void setX(Distance x);

        /** @brief Permet de définir une nouvelle valeur pour la position y du robot
        *   @param Nouvelle position y du robot*/
        void setY(Distance y);

        /** @brief Permet de définir une nouvelle valeur pour l'angle du robot
        *   @param a Nouvel angle du robot en radian */
        void setAngle(Angle a);

    private:
        /**@brief Position absolue du robot depuis le départ */
        Angle absAngle;

};

#endif // ROBOTHW

#endif // ODOMETRIE_H
