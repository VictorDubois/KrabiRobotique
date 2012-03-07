#ifndef COMMANDAVANCERTOUTDROIT_H
#define COMMANDAVANCERTOUTDROIT_H

#include <command.h>

/**@brief Permet d'ordonner au robot d'avancer tout droit dans la direction qu'il est en train de pointer au moment ou l'odre est lancé */
class CommandAvancerToutDroit : public Command
{
    public:
        /**@brief Constructeur de base de la classe. Le robot termine l'ordre avec une vitesse nulle.
        *  @param distance Indique la distance qu'on aimerait qu'il parcourt */
        CommandAvancerToutDroit(Distance distance);
        /**@brief Constructeur de base de la classe. Le robot termine l'ordre avec une vitesse non nulle.
        *  @param distance Indique la distance qu'on aimerait qu'il parcourt
        *  @param vitesseFinal Indique la vitesse qu'on aimerait que le robot aiet à la fin de l'ordre */
        CommandAvancerToutDroit(Distance distance, Vitesse vitesseFinale);
        /**@brief Destructeur de la classe */
        virtual ~CommandAvancerToutDroit();
        /**@brief Retourne la vitesse lineaire à atteindre par le robot */
        Vitesse getLinearSpeed();
        /**@brief Retourne la vitesse angulaire à atteindre par le robot */
        Angle getAngularSpeed();
        /**@brief Fonction appeller toutes les 20 ms permettant de mettre à jour les ordres envoyé à l'asservicement */
        void update();
    private:
        /**@brief C'est la vitesse qu'on aimerait qu'il aiet à le fin */
        Vitesse vitesseFinale;
        /**@brief C'est la position et l'angle que l'on aimerait que le robot atteigne à la fin de l'ordre */
        PositionPlusAngle destination;
        /**@brief C'est la vitesse linaire que l'on aimerait que le robot atteigne à cette instant t */
        Vitesse vitesse_lineaire_a_atteindre;
        /**@brief C'est la vitesse angulaire que l'on aimerait que le robot atteigne à cette instant t  */
        VitesseAngulaire vitesse_angulaire_a_atteindre;
        /**@brief Pour connaitre la vitesse linéaire à atteindre par le robot
        *@param Distance vitesse_lineaire_atteinte est la vitesse actuelle du robot.
        *@param Distance distance_restante est la distance qu'il reste à parcourir par le robot.*/
        Vitesse getVitesseLineaireAfterTrapeziumFilter(Vitesse vitesse_lineaire_atteinte, Distance distance_restante);
        /**@brief Pour connaitre la vitesse angulaire à atteindre par le robot
        *@param VitesseAngulaire vitesse_angulaire_atteinte est la vitesse angulaire actuelle du robot.
        *@param Angle angle_restant est l'angle qu'il reste à parcourir par le robot.*/
        VitesseAngulaire getVitesseAngulaireAfterTrapeziumFilter(VitesseAngulaire vitesse_angulaire_atteinte, Angle angle_restant);
};

#endif // COMMANDAVANCERTOUTDROIT_H
