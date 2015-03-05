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

#include "remote.h"

#include <stdint.h>
#include <math.h>

#define STK_CTRL_ADDR 0xe000e010
#define STK_LOAD_ADDR (STK_CTRL_ADDR+0x04)

#define FIXED_LINEAR_DUTY_MAX 0.2
#define FIXED_ANGULAR_DUTY_MAX 0.2

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

        /**@brief différence d'accélération à partir de laquel on concidére qu'il y a collision */
        float seuil_collision;

        /**@brief Pour savoir s'il y a eu un grand nombre de collision succéssive */
        unsigned int buffer_collision;

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

};

static long systick_count = 0;

/**@brief fonction externe appellé directement par le microcontroleur à chaque mise à jour. C'est grace à cette fonction que des actions sont exécutés à intervalle régulier */
extern "C" void SysTick_Handler();

#endif // ASSERVISSEMENT_H
