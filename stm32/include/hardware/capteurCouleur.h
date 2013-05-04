#ifndef CAPTEURCOULEUR_H
#define CAPTEURCOULEUR_H

#ifdef ROBOTHW
#include "stm32f10x_tim.h"

enum PositionCapteurCouleur
{
    GAUCHE_HAUT,
    GAUCHE_BAS,
    DROITE_HAUT,
    DROITE_BAS
};

/// @brief Classe permettant de connaitre le nombre de ticks des capteurs couleur
/// Le capteur renvoit un signal en créneaux dont la fréquence dépend de la luminosité
/// Il se branche sur le channel 1 d'un timer
class CapteurCouleur
{
    private:

        /// @brief Le Timer utilisé
        TIM_TypeDef* m_TIMx;

        // pin des diodes
        GPIO_TypeDef* m_GPIO_diodesRouges;
        uint16_t m_GPIO_Pin_diodesRouges;
        GPIO_TypeDef* m_GPIO_diodesBleues;
        uint16_t m_GPIO_Pin_diodesBleues;

        // pins de selection
        GPIO_TypeDef* m_GPIO_selectCapteur1;
        uint16_t m_GPIO_Pin_selectCapteur1;
        GPIO_TypeDef* m_GPIO_selectCapteur2;
        uint16_t m_GPIO_Pin_selectCapteur2;

    public:

        /// @brief Constructeur en spécifiant le timer et la pin
        /// Le channel 1 du timer doit etre utiliseé
        /// On donne aussi les pins des diodes rouges, bleues et les 2 pins de selection du capteur
        CapteurCouleur(TIM_TypeDef* TIMx, GPIO_TypeDef* GPIO_timer, uint16_t GPIO_Pin_timer,
                       GPIO_TypeDef* GPIO_diodesRouges, uint16_t GPIO_Pin_diodesRouges,
                       GPIO_TypeDef* GPIO_diodesBleues, uint16_t GPIO_Pin_diodesBleues,
                       GPIO_TypeDef* GPIO_selectCapteur1, uint16_t GPIO_Pin_selectCapteur1,
                       GPIO_TypeDef* GPIO_selectCapteur2, uint16_t GPIO_Pin_selectCapteur2);

        // allume/éteint les diodes
        void allumerDiodesRouge(bool allumer);
        void allumerDiodesBleues(bool allumer);

        // selectionne le capteur
        void activerCapteur(PositionCapteurCouleur position);

        // Permet de connaitre le nombre de ticks depuis le dernier appel de cette fonction
        // ou depuis le dernier appel de la selection du capteur
        uint16_t getTickValue();
};

#endif // ROBOTHW

#endif // QUADRATURECODERHANDLER_H
