#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

#include "capteurCouleur.h"
#include "timerHandler.h"

// permet d'initialiser une pin
void initialiserPinCapteur(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin_x)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_x;
    GPIO_Init(GPIOx, &GPIO_InitStructure);
    GPIO_WriteBit(GPIOx, GPIO_Pin_x, Bit_RESET);
}

/// @brief Constructeur en spécifiant le timer et la pin
/// Le channel 1 du timer doit etre utiliseé
/// On donne aussi les pins des diodes rouges, bleues et les 2 pins de selection du capteur
CapteurCouleur::CapteurCouleur(TIM_TypeDef* TIMx, GPIO_TypeDef* GPIO_timer, uint16_t GPIO_Pin_timer,
                               GPIO_TypeDef* GPIO_diodesRouges, uint16_t GPIO_Pin_diodesRouges,
                               GPIO_TypeDef* GPIO_diodesBleues, uint16_t GPIO_Pin_diodesBleues,
                               GPIO_TypeDef* GPIO_selectCapteur1, uint16_t GPIO_Pin_selectCapteur1,
                               GPIO_TypeDef* GPIO_selectCapteur2, uint16_t GPIO_Pin_selectCapteur2)
    : m_TIMx(TIMx)
    , m_GPIO_diodesRouges(GPIO_diodesRouges), m_GPIO_Pin_diodesRouges(GPIO_Pin_diodesRouges)
    , m_GPIO_diodesBleues(GPIO_diodesBleues), m_GPIO_Pin_diodesBleues(GPIO_Pin_diodesBleues)
    , m_GPIO_selectCapteur1(GPIO_selectCapteur1), m_GPIO_Pin_selectCapteur1(GPIO_Pin_selectCapteur1)
    , m_GPIO_selectCapteur2(GPIO_selectCapteur2), m_GPIO_Pin_selectCapteur2(GPIO_Pin_selectCapteur2)
{
    // Initialisation de la pin du timer
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_timer;
    GPIO_Init(GPIO_timer, &GPIO_InitStructure);

    // Active l'horloge du timer
    Timer::enableTimerClock(TIMx);

    // initialisation du timer
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Prescaler     = 0;
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period        = 0xFFFF;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    // utilise une horloge externe
    // le counter est incrementé à chaque monté du signal sur le channel 1
    TIM_TIxExternalClockConfig(TIM2, TIM_TIxExternalCLK1Source_TI1ED, TIM_ICPolarity_Rising, 0);

    // met le timer à disposition
    TIM_Cmd(TIM2, ENABLE);

    // met le counter à 0
    TIM_SetCounter(TIMx, 0);

    // initialisation des autres pins
    initialiserPinCapteur(m_GPIO_diodesRouges, m_GPIO_Pin_diodesRouges);
    initialiserPinCapteur(m_GPIO_diodesBleues, m_GPIO_Pin_diodesBleues);
    initialiserPinCapteur(m_GPIO_selectCapteur1, m_GPIO_Pin_selectCapteur1);
    initialiserPinCapteur(m_GPIO_selectCapteur2, m_GPIO_Pin_selectCapteur2);
}

// allume/éteint les diodes
void CapteurCouleur::allumerDiodesRouge(bool allumer)
{
    GPIO_WriteBit(m_GPIO_diodesRouges, m_GPIO_Pin_diodesRouges, allumer ? Bit_SET : Bit_RESET);
}

void CapteurCouleur::allumerDiodesBleues(bool allumer)
{
    GPIO_WriteBit(m_GPIO_diodesBleues, m_GPIO_Pin_diodesBleues, allumer ? Bit_SET : Bit_RESET);
}

// selectionne le capteur
void CapteurCouleur::activerCapteur(PositionCapteurCouleur position)
{
    // selection du capteur
    switch (position)
    {
        case GAUCHE_HAUT:
            GPIO_WriteBit(m_GPIO_selectCapteur1, m_GPIO_Pin_selectCapteur1, Bit_RESET);
            GPIO_WriteBit(m_GPIO_selectCapteur2, m_GPIO_Pin_selectCapteur2, Bit_RESET);
            break;
        case GAUCHE_BAS:
            GPIO_WriteBit(m_GPIO_selectCapteur1, m_GPIO_Pin_selectCapteur1, Bit_RESET);
            GPIO_WriteBit(m_GPIO_selectCapteur2, m_GPIO_Pin_selectCapteur2, Bit_SET);
            break;
        case DROITE_HAUT:
            GPIO_WriteBit(m_GPIO_selectCapteur1, m_GPIO_Pin_selectCapteur1, Bit_SET);
            GPIO_WriteBit(m_GPIO_selectCapteur2, m_GPIO_Pin_selectCapteur2, Bit_RESET);
            break;
        case DROITE_BAS:
            GPIO_WriteBit(m_GPIO_selectCapteur1, m_GPIO_Pin_selectCapteur1, Bit_SET);
            GPIO_WriteBit(m_GPIO_selectCapteur2, m_GPIO_Pin_selectCapteur2, Bit_SET);
            break;
    }

    // remet à 0
    TIM_SetCounter(m_TIMx, 0);
}

// Permet de connaitre le nombre de ticks depuis le dernier appel de cette fonction
// ou depuis le dernier appel de la selection du capteur
uint16_t CapteurCouleur::getTickValue()
{
    // récupère le nombre de ticks depuis la dernière mise à 0
    uint16_t tick = TIM_GetCounter(m_TIMx);

    // remet à 0
    TIM_SetCounter(m_TIMx, 0);

    return tick;
}
