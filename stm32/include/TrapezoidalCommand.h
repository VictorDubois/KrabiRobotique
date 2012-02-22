#ifndef TRAPEZOIDALCOMMAND_H_INCLUDED
#define TRAPEZOIDALCOMMAND_H_INCLUDED

#include "variable.h"
#include "command.h"
#include <math.h>
#include "strategie.h"
#include "Angle.h"
#include "odometrie.h"

/**@brief Cette classe permet de donner des ordres au robot et de les lui faire exécuter */
class TrapezoidalCommand : public Command
{
    private:
        /**@brief C'est la vitesse linaire que l'on aimerai qu'il atteigne */
        float vitesse_lineaire_a_atteindre;
        /**@brief C'est la vitesse angulaire que l'on aimerai qu'il atteigne */
        float vitesse_angulaire_a_atteindre;
        /**@brief C'est la position que l'on aimerai qu'il atteigne */
        Position destination;
        /**@brief C'est l'angle que l'on aimerai qu'il atteigne */
        Angle destAngle;
        /**@brief True si le robot doit se déplacer, false sinon */
        bool en_mouvement;
        /**@brief True si le robot est dans la bonne direction, false si il doit tourner */
        bool direction;
        /**@brief True si le robot doit s'arrete en arrivant à sa destination, false sinon */
        bool stop;
    public:
        /**@brief Constructeur par défault */
        TrapezoidalCommand();
        /**@brief Déstructeur de la classe */
        ~TrapezoidalCommand();
        /**@brief fonction appeller toute les 20 ms */
        void update(PositionPlusAngle positionPlusAngleActuelle, Angle vitesse_angulaire_atteinte, Distance vitesse_lineaire_atteinte);
        /**@brief Pour donner l'ordre au robot d'aller à un endroit
        *@param Position position est la position que doit atteindre le robot.
        *@param bool stop indique si le robot doit s'arreter ou non en arrivant à destination. */
        void goTo(Position position, bool stop=true);
        /**@brief Pour donner l'ordre au robot de tourner dans une direction
        *@param Position position est le points ou le robot doit faire face.
        *@param bool stop indique si le robot doit s'arreter ou non en arrivant à destination. */
        void face(Position position, bool stop=true);
        /**@brief Pour donner l'ordre au robot de tourner d'une certaine valeur
        *@param Position position continue dans position.x l'angle de rotation en deg° à réaliser par le robot.
        *@param bool stop indique si le robot doit s'arreter ou non en arrivant à destination. */
        void tourne(Position position, bool stop=true);
        /**@brief Pour donner l'ordre au robot d'avancer d'une certaine valeur
        *@param Position position continue dans position.x la distance que doit parcourir le robot.
        *@param bool stop indique si le robot doit s'arreter ou non en arrivant à destination. */
        void avance(Position position, bool stop=true);
        /**@brief Pour connaitre la vitesse linéaire à atteindre par le robot
        *@param Distance vitesse_lineaire_atteinte est la vitesse actuelle du robot.
        *@param Distance distance_restante est la distance qu'il reste à parcourir par le robot.
        *@param Angle angle_restant est l'angle dont doit encore tourner le robot. */
        Distance getVitesseLineaireAfterTrapeziumFilter(Distance vitesse_lineaire_atteinte, Distance distance_restante, Angle angle_restant);
        /**@brief Pour connaitre la vitesse angulaire à atteindre par le robot
        *@param Angle vitesse_angulaire_atteinte est la vitesse angulaire actuelle du robot.
        *@param Angle angle_restant est l'angle dont doit encore tourner le robot. */
        Angle getVitesseAngulaireAfterTrapeziumFilter(Angle vitesse_angulaire_atteinte, Angle angle_restant);
        /**@brief Retourne la vitesse lineaire à atteindre par le robot */
        float getLinearSpeed();
        /**@brief Retourne la vitesse angulaire à atteindre par le robot */
        Angle getAngularSpeed();
        /**@brief Indique si le robot a atteind sa destination ou non*/
        bool destinationAtteinte();
        /**@brief Indique si le robot a atteind sa destination ou non*/
        bool fini;
};

#endif
