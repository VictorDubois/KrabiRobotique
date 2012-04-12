#ifndef COMMANDGOTO_H
#define COMMANDGOTO_H

#include <command.h>

/** @brief Permet d'ordonner au robot d'aller à un endroit précis */
class CommandGoTo : public Command
{
    public:
        /** @brief Constructeur de classe utiliser pour ordonner au robot d'aller à une position donnée (l'angle d'arrivé n'a pas d'importance, la vitesse linéaire et angulaire est nulle à la fin)
        *   @param DestinationFinale Position final que doit avoir le robot */
        CommandGoTo(Position DestinationFinale);
        virtual ~CommandGoTo();
        /** @brief Retourne la vitesse lineaire à atteindre par le robot */
        Vitesse getLinearSpeed();
        /** @brief Retourne la vitesse angulaire à atteindre par le robot */
        Angle getAngularSpeed();
        /** @brief Fonction appeller toutes les 20 ms permettant de mettre à jour les ordres envoyé à l'asservicement */
        void update();
        /** @brief Permet de routourner la trajectoir du robot *
        *   @return Retourne un tableau de taille PATH_LENTGH contenant les positions et angles respectif du robot tous les MS_BETWEEN_UPDATE ms */
        static PositionPlusAngle** path(Position DestinationFinale);
        /** @brief  Supprime le chemin de la mémoire *
        *   @return path Chemin que l'on souhaite supprimer */
        static void deletePath (PositionPlusAngle** path);
    private:
        /** @brief C'est la vitesse linéaire qu'on aimerait que le robot atteigne à le fin */
        Vitesse vitesseFinale;
        /** @brief C'est la position et l'angle que l'on aimerait que le robot atteigne à la fin de l'ordre */
        PositionPlusAngle destination;
        /** @brief C'est la vitesse linaire que l'on aimerait que le robot atteigne à cette instant t */
        Vitesse vitesse_lineaire_a_atteindre;
        /** @brief C'est la vitesse angulaire que l'on aimerait que le robot atteigne à cette instant t  */
        VitesseAngulaire vitesse_angulaire_a_atteindre;
        /** @brief Pour connaitre la vitesse linéaire à atteindre par le robot
        *   @param Distance vitesse_lineaire_atteinte est la vitesse actuelle du robot.
        *   @param Distance distance_restante est la distance qu'il reste à parcourir par le robot.
        *   @param Angle angle_restant est l'angle qu'il reste à parcourir par le robot.
        *   @param Vitesse vitesseFinale Vitesse que l'on souhaite que le robot ait à la fin de la commande*/
        static Vitesse getVitesseLineaireAfterTrapeziumFilter(Vitesse vitesse_lineaire_atteinte, Distance distance_restante, Angle angle_restant, Vitesse vitesseFinale);
        /** @brief Pour connaitre la vitesse angulaire à atteindre par le robot
        *   @param VitesseAngulaire vitesse_angulaire_atteinte est la vitesse angulaire actuelle du robot.
        *   @param Angle angle_restant est l'angle qu'il reste à parcourir par le robot.*/
        static VitesseAngulaire getVitesseAngulaireAfterTrapeziumFilter(VitesseAngulaire vitesse_angulaire_atteinte, Angle angle_restant);
};

#endif // COMMANDGOTO_H
