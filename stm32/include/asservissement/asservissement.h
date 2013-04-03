#ifndef ASSERVISSEMENT_H
#define ASSERVISSEMENT_H

#ifdef ROBOTHW
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

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

#include <stdint.h>
#include <math.h>

#define STK_CTRL_ADDR 0xe000e010
#define STK_LOAD_ADDR (STK_CTRL_ADDR+0x04)

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

        /**@brief Pour connaitre le nombre d'appels à l'asservissement */
        int asserCount;

    public:

        /**@brief Les commandes appliquées au robot */
        Command* command;

        /**@brief Constructeur de l'asservissement (avec forcement l'odometrie) */
        Asservissement(Odometrie* _odometrie);

        /**@brief Pour connaitre la vitesse lineaire attendu du robot */
        Vitesse getLinearSpeed();

        /**@brief Pour connaitre la vitesse angulaire attendu du robot */
        Angle getAngularSpeed();

        /**@brief On stock l'asservissement en statique car un seul peut exister en meme temps */
        static Asservissement* asservissement;

        /**@brief temps entre deux mise à jours */
        static const uint16_t nb_ms_between_updates;

        /**@brief fonction appellées à chaque mise à jours */
        void update(void);

        /** @brief Permet de changer la command courante utilisée par la stratégie */
        static void setCommand(Command* command);

        /** @brief Permet récupérer la command courante utilisée par la stratégie */
        static Command* getCommand();

        static void finMatch();

        static bool matchFini;

};

/**@brief fonction externe appellé directement par le microcontroleur à chaque mise à jour. C'est grace à cette fonction que des actions sont exécutés à intervalle régulier */
extern "C" void SysTick_Handler();

#endif // ASSERVISSEMENT_H