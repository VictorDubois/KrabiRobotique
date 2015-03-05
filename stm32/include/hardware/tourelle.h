#ifndef TOURELLE_H_INCLUDED
#define TOURELLE_H_INCLUDED

//Tuto utilisés : http://www.farrellf.com/projects/hardware/2012-08-11_STM32F4_Basics:_Timers_%28Part_1%29/
//et : http://www.coocox.org/show_exam/EXTI/444.html

/* Includes ------------------------------------------------------------------*/

#include "misc.h"
#include "leds.h"
#ifdef STM32F40_41xxx
    #include "stm32f4xx_tim.h"
    #include "stm32f4xx.h"
    #include "stm32f4xx_syscfg.h"
    #include "stm32f4xx_rcc.h"
    #include "stm32f4xx_gpio.h"
    #include "stm32f4xx_exti.h"
#elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
    #include "stm32f10x_tim.h"
    #include "stm32f10x.h"
    //#include "stm32f10x_syscfg.h"
    #include "stm32f10x_rcc.h"
    #include "stm32f10x_gpio.h"
    #include "stm32f10x_exti.h"
#endif



///**
//  * @brief  This function handles External line 2 interrupt request.
//  * @param  None
//  * @retval None
//  */
//extern "C" void EXTI2_IRQHandler(void);

/**
  * @brief  This function handles External line 3 interrupt request.
  * @param  None
  * @retval None
  */
extern "C" void EXTI3_IRQHandler(void);

///**
//  * @brief  This function handles External line 5 interrupt request.
//  * @param  None
//  * @retval None
//  */
//extern "C" void EXTI9_5_IRQHandler(void);

///**
//  * @brief  Configures TIM6 as a counter
//  * @param  None
//  * @retval None
//  */
//void TIM6_Config(void);
//
///**
//  * @brief  Handles the TIM6 interrupt (useless for the tourelle)
//  * @param  None
//  * @retval None
//  */
//extern "C" void TIM6_DAC_IRQHandler();
//
///**
//  * @brief  Configures EXTI Line2 (connected to PA2 pin) in interrupt mode
//  * @param  None
//  * @retval None
//  */
//void EXTILine2_Config(void);

/**
  * @brief  Configures EXTI Line3 (connected to PA3 pin) in interrupt mode
  * @param  None
  * @retval None
  */
void EXTILine3_Config(void);

/**
  * @brief  Configures EXTI Line5 (connected to PD5 pin) in interrupt mode
  * @param  None
  * @retval None
  */
void EXTILine5_Config(void);

class Tourelle
{
    public:
//        /**
//          * @brief  Constructeur de la tourelle
//          * @note   Pas de paramètres pour les numéros d'interruption, vu que les noms de fonctions en dépendent. Hard-codé.
//          * @param  timer_tourelle le timer que va utiliser la tourelle. Prendre un timer interne dédié (TIM6 ou plus, selon disponibilité)
//          * @param  angleDecalage l'angle entre l'avant du robot (0°) et la position du compteur de tours
//          * @retval None
//          */
//        Tourelle(TIM_TypeDef* timer_tourelle, uint16_t angleDecalage);
        Tourelle();
//
//        /**
//          * @brief  Set une zone critique. Si quelquechose y est détécté, il faut freiner
//          * @param  angleDebut l'angle de début de la zone critique
//          * @param  angleDebut l'angle de fin de la zone critique
//          * @retval numéro de zone
//          */
//        uint8_t setZoneCritique(uint16_t angleDebut, uint16_t angleFin);
//
//        /** @brief Efface toutes les zones critiques
//          * @param  None
//          * @retval None
//          */
//        void resetZonesCritiques(void);
//
//        /** @brief Efface une zone critique
//          * @param  numeroZone le numéro de la zone a effacer
//          * @retval None
//          */
//        void resetZoneCritique(uint8_t numeroZone);
//
        /** @brief Retourne true si un robot est détécté une zone critique, et donc qu'on doit freiner
          * @param  None
          * @retval alerte
          */
        bool getAlerte(void);
//
//        /** @brief Calcul l'angle d'un objet
//          * @param  numeroObjet le numéro de l'objet détecté
//          * @retval alerte
//          */
//        uint16_t calculAngle(uint8_t numeroObjet);
//
//        /** @brief Update la détection si un tour vient de finir
//          * @param  None
//          * @retval alerte
//          */
//        bool update(void);

        bool updateSimple(void);

    private:
//        /** @brief le timer que va utiliser la tourelle. Prendre un timer interne dédié (TIM6 ou plus, selon disponibilité) */
//        TIM_TypeDef* timer_tourelle;
//
//        /** @brief l'angle entre l'avant du robot (0°) et la position du compteur de tours */
//        uint16_t angleDecalage;

        /** @brief un objet est-il détécté dans un zone critique (soit le robot doit-il ralentir) */
        bool alerte;

//        /** @brief tableau des directions des objets détectés */
//        uint16_t objectDirection[20];
//
//        /** @brief temps moyen pour faire un tour */
//        uint16_t meanTurnTime;
//
//        /** @brief zones critiques */
//        uint16_t zonesCritiques[20][2];
//
//        /** @brief derniers temps mis pour faire un tour */
//        uint16_t lastTurnTimes[20];
//
//        /** @brief tableau des instants de détection des objets */
//        uint16_t objectDetectionInstant[20];

        /** @brief nombre d'objets détectés */
        //uint8_t nombreObjetDetecte;
};


#endif
