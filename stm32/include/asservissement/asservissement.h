#ifndef ASSERVISSEMENT_H
#define ASSERVISSEMENT_H

#ifdef ROBOTHW
#ifdef STM32F40_41xxx
    #include "stm32f4xx_tim.h"
    #include "stm32f4xx.h"
    #include "stm32f4xx_rcc.h"
    #include "stm32f4xx_gpio.h"
#elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
    #include "stm32f10x.h"
    #include "stm32f10x_tim.h"
    #include "stm32f10x_rcc.h"
    #include "stm32f10x_gpio.h"
#endif


#include "roues.h"
//#include "capteurs.h"
#endif

#include "sensors.h"
#include "constantes.h"
#include "odometrie.h"
#include "positionPlusAngle.h"
#include "distance.h"
#include "pidFilterDistance.h"
#include "pidFilterAngle.h"
#include "command.h"

#ifdef REMOTE_ON
    #include "remote.h"
#endif

#include <stdint.h>
#include <math.h>

#define STK_CTRL_ADDR 0xe000e010
#define STK_LOAD_ADDR (STK_CTRL_ADDR+0x04)

#define FIXED_LINEAR_DUTY_MAX 0.2
#define FIXED_ANGULAR_DUTY_MAX 0.2

#define NB_VERIFICATION_BLOQUAGE_PAR_SECONDE 10

/**@brief classe permettant de vérifier que le robot fait bien ce qu'on lui dit et de corriger les erreurs */
class Asservissement
{
    private:

        /**@brief vitesse réelle à appliquer à la roue pour obtenir la bonne vitesse linéaire*/
        float linearDutySent;

        /**@brief vitesse réelle à appliquer à la roue pour obtenir la bonne vitesse angulaire*/
        float angularDutySent;

        /**@brief outils de gestion de la vitesse linéaire */
        PIDFilterDistance pid_filter_distance;

        /**@brief outils de gestion de la vitesse angulaire */
        PIDFilterAngle pid_filter_angle;

#ifdef ROBOTHW
        /**@brief définition des roues du robot */
        Roues roues;
#endif

#ifdef CAPTEURS
        /**@brief Pointeur vers les capteurs du robot */
        Sensors* sensors;
#endif //capteurs_old

//Vieille tentative, jemais codée
//        /**@brief différence d'accélération à partir de laquel on concidére qu'il y a collision */
//        float seuil_collision;
//
//        /**@brief Pour savoir s'il y a eu un grand nombre de collision succéssive */
//        unsigned int buffer_collision;

        /*############## Section détection de bloquage ##############*/
        /**@brief Position précédente, pour détecter si on bouge ou pas */
        float positionPlusAnglePrecedenteX;
        float positionPlusAnglePrecedenteY;
        float positionPlusAnglePrecedenteAngle;

        /**@brief Compteur jusqu'à 1/10 de seconde */
        uint16_t compteurRemplissageQuatum;

        uint16_t nombreQuatumParDixiemeDeSeconde;

        /**@brief Tableau des quantum de déplacement linéaire sur la dernière seconde : chaque case correspond à la somme des variations absolues d'un 10ème de seconde */
        float deplacementLineaires[NB_VERIFICATION_BLOQUAGE_PAR_SECONDE];//NB_VERIFICATION_BLOQUAGE_PAR_SECONDE = 10 pour l'instant, une vérification tous les dixièmes

        /**@brief Tableau des quantum de déplacement angulaire sur la dernière seconde : chaque case correspond à la somme des variations absolues d'un 10ème de seconde */
        float deplacementAngulaire[NB_VERIFICATION_BLOQUAGE_PAR_SECONDE];

        /**@brief Tableau des quantum de d'accélération linéaire sur la dernière seconde : chaque case correspond à la somme des valeurs sur 10ème de seconde */
        float accelerationLineaires[NB_VERIFICATION_BLOQUAGE_PAR_SECONDE];

        /**@brief Tableau des quantum de d'accélération angulaire sur la dernière seconde : chaque case correspond à la somme des valeurs sur 10ème de seconde */
        float accelerationAngulaires[NB_VERIFICATION_BLOQUAGE_PAR_SECONDE];

        /**@brief booleun vrai si il faut s'arrêter à cause d'un bloquage detecte */
        bool obstacleDetecte;

        /**@brief compteur du nombre d'update depuis qu'il faut s'arrêter à cause d'un bloquage detecte*/
        uint32_t nbUpdateDepuisObstacleDetecte;
        /*############ Fin Section détection de bloquage ############*/

        /**@brief Pour connaitre la position exacte du robot */
        Odometrie* odometrie;

        /**@brief Pour connaitre le nombre d'appelle à l'asservissement */
        int asserCount;

        Vitesse vitesseLineaire;
        Angle vitesseAngulaire;

        bool activePIDDistance, activePIDAngle;

        float fixedLinearDuty, fixedAngularDuty;

    public:

        /**@brief Constructeur de l'asservissement (avec forcement l'odometrie) */
        Asservissement(Odometrie* _odometrie);

        /**@brief Modifie la vitesse linéaire à atteindre */
        void setLinearSpeed(Vitesse vitesse);

        /**@brief Modifie la vitesse angulaire à atteindre */
        void setAngularSpeed(VitesseAngulaire vitesse);

        void setCommandSpeeds(Command* command);

        /**@brief Pour connaitre la vitesse lineaire attendu du robot */
        Vitesse getLinearSpeed();

        /**@brief Pour connaitre la vitesse angulaire attendu du robot */
        Angle getAngularSpeed();

        /**@brief On stock l'asservissement en statique car un seul peut exister en meme temps */
        static Asservissement* asservissement;

        /**@brief temps entre deux mise à jours */
        static const uint16_t nb_ms_between_updates;

        /**@brief fonction appelée à chaque mise à jour */
        void update(void);

        void setEnabledPIDDistance(bool enabled);

        void setEnabledPIDAngle(bool enabled);

        void setLinearDuty(float duty);

        void setAngularDuty(float duty);

        void resetFixedDuty();

        static void finMatch();

        static bool matchFini;

        /**@brief detecteur de robot bloqué contre un obstacle (adversaire, mur...). Sert à arrêter le robot pour ne pas abîmer les moteurs, le décor, l'adversaire... */
        void computeObstacleDetecte(float linearDutySent, float angularDutySent, PositionPlusAngle* positionPlusAngleActuelle);

        /**@brief Reset les erreurs, pour repartir doucement après un arrêt*/
        void resetAsserv();
};

static long systick_count = 0;

/**@brief fonction externe appellé directement par le microcontroleur à chaque mise à jour. C'est grace à cette fonction que des actions sont exécutés à intervalle régulier */
extern "C" void SysTick_Handler();

#endif // ASSERVISSEMENT_H
