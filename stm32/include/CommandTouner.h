#ifndef COMMANDTOUNER_H
#define COMMANDTOUNER_H

#include <command.h>
#include <Angle.h>
#include <odometrie.h>

/** @brief Permet d'ordonner au robot de tourner sur lui même */
class CommandTouner : public Command
{
    public:
        /**@brief Constructeur la classe utilisé si on veut tourner d'un certain angle en s'arrêtant à la fin de l'ordre
        *  @param angle Angle que l'on souhaite tourner*/
        CommandTouner(Angle angle);
        /**@brief Constructeur la classe utilisé si on veut tourner d'un certain angle en finissant l'ordre avec une certaine vitesse angulaire
        *  @param angle Angle que l'on souhaite tourner
        *  @param vitesseAngulaireFinale Vitesse angulaire avec laquel on souhaite que le robot termine sont ordre*/
        CommandTouner(Angle angle, VitesseAngulaire vitesseAngulaireFinale);
        /**@brief Destructeur de la classe */
        virtual ~CommandTouner();
        /**@brief Retourne la vitesse lineaire à atteindre par le robot */
        Vitesse getLinearSpeed();
        /**@brief Retourne la vitesse angulaire à atteindre par le robot */
        Angle getAngularSpeed();
        /**@brief Fonction appeller toutes les 20 ms permettant de mettre à jour les ordres envoyé à l'asservicement */
        void update();
    protected:
    private:
        /**@brief C'est la vitesse angulaire qu'on aimerait que le robot aiet à le fin */
        VitesseAngulaire vitesseAngulaireFinale;
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

#endif // COMMANDTOUNER_H
