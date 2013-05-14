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

////////////////////////////////////
//         CapteurCouleur         //
////////////////////////////////////

/// @brief Constructeur en spécifiant le timer et la pin
/// Le channel 1 du timer doit etre utiliseé
/// On donne aussi les pins des diodes rouges, bleues et les 2 pins de selection du capteur
CapteurCouleur::CapteurCouleur(TIM_TypeDef* TIMx, GPIO_TypeDef* GPIO_timer, uint16_t GPIO_Pin_timer,  
                               GPIO_TypeDef* GPIO_diodesRouges, uint16_t GPIO_Pin_diodesRouges,
                               GPIO_TypeDef* GPIO_diodesBleues, uint16_t GPIO_Pin_diodesBleues,
                               GPIO_TypeDef* GPIO_selectCapteur1, uint16_t GPIO_Pin_selectCapteur1,
                               GPIO_TypeDef* GPIO_selectCapteur2, uint16_t GPIO_Pin_selectCapteur2,
                               GPIO_TypeDef* GPIO_selectFiltre1, uint16_t GPIO_Pin_selectFiltre1,
                               GPIO_TypeDef* GPIO_selectFiltre2, uint16_t GPIO_Pin_selectFiltre2)
    : m_TIMx(TIMx)
    , m_GPIO_diodesRouges(GPIO_diodesRouges), m_GPIO_Pin_diodesRouges(GPIO_Pin_diodesRouges)
    , m_GPIO_diodesBleues(GPIO_diodesBleues), m_GPIO_Pin_diodesBleues(GPIO_Pin_diodesBleues)
    , m_GPIO_selectCapteur1(GPIO_selectCapteur1), m_GPIO_Pin_selectCapteur1(GPIO_Pin_selectCapteur1)
    , m_GPIO_selectCapteur2(GPIO_selectCapteur2), m_GPIO_Pin_selectCapteur2(GPIO_Pin_selectCapteur2)
    , m_GPIO_selectFiltre1(GPIO_selectFiltre1), m_GPIO_Pin_selectFiltre1(GPIO_Pin_selectFiltre1)
    , m_GPIO_selectFiltre2(GPIO_selectFiltre2), m_GPIO_Pin_selectFiltre2(GPIO_Pin_selectFiltre2)
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
    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);

    // utilise une horloge externe
    // le counter est incrementé à chaque monté du signal sur le channel 1
    TIM_TIxExternalClockConfig(TIMx, TIM_TIxExternalCLK1Source_TI1ED, TIM_ICPolarity_Rising, 0);

    // met le timer à disposition
    TIM_Cmd(TIMx, ENABLE);

    // met le counter à 0
    TIM_SetCounter(TIMx, 0);

    // initialisation des autres pins
    initialiserPinCapteur(m_GPIO_diodesRouges, m_GPIO_Pin_diodesRouges);
    initialiserPinCapteur(m_GPIO_diodesBleues, m_GPIO_Pin_diodesBleues);
    initialiserPinCapteur(m_GPIO_selectCapteur1, m_GPIO_Pin_selectCapteur1);
    initialiserPinCapteur(m_GPIO_selectCapteur2, m_GPIO_Pin_selectCapteur2);
    initialiserPinCapteur(m_GPIO_selectFiltre1, m_GPIO_Pin_selectFiltre1);
    initialiserPinCapteur(m_GPIO_selectFiltre2, m_GPIO_Pin_selectFiltre2);
}

// allume/éteint les diodes
void CapteurCouleur::allumerDiodesRouges(bool allumer)
{
    GPIO_WriteBit(m_GPIO_diodesRouges, m_GPIO_Pin_diodesRouges, allumer ? Bit_SET : Bit_RESET);
}

void CapteurCouleur::allumerDiodesBleues(bool allumer)
{
    GPIO_WriteBit(m_GPIO_diodesBleues, m_GPIO_Pin_diodesBleues, allumer ? Bit_SET : Bit_RESET);
}

// selectionne un filtre
void CapteurCouleur::selectionnerFiltre(FiltreCapteurCouleur filtre)
{
    switch (filtre)
    {
        case FILTRE_ROUGE:
            GPIO_WriteBit(m_GPIO_selectFiltre1, m_GPIO_Pin_selectFiltre1, Bit_RESET);
            GPIO_WriteBit(m_GPIO_selectFiltre2, m_GPIO_Pin_selectFiltre2, Bit_RESET);

            break;
        case FILTRE_BLEU:
            GPIO_WriteBit(m_GPIO_selectFiltre1, m_GPIO_Pin_selectFiltre1, Bit_SET);
            GPIO_WriteBit(m_GPIO_selectFiltre2, m_GPIO_Pin_selectFiltre2, Bit_RESET);
            break;
        case FILTRE_BLANC:
            GPIO_WriteBit(m_GPIO_selectFiltre1, m_GPIO_Pin_selectFiltre1, Bit_RESET);
            GPIO_WriteBit(m_GPIO_selectFiltre2, m_GPIO_Pin_selectFiltre2, Bit_SET);
            break;
        case FILTRE_VERT:
            GPIO_WriteBit(m_GPIO_selectFiltre1, m_GPIO_Pin_selectFiltre1, Bit_SET);
            GPIO_WriteBit(m_GPIO_selectFiltre2, m_GPIO_Pin_selectFiltre2, Bit_SET);
            break;
    }
}

// selectionne le capteur
void CapteurCouleur::activerCapteur(PositionCapteurCouleur position)
{
    // selection du capteur
    switch (position)
    {
        case GAUCHE_HAUT:
            GPIO_WriteBit(m_GPIO_selectCapteur1, m_GPIO_Pin_selectCapteur1, Bit_RESET);
            GPIO_WriteBit(m_GPIO_selectCapteur2, m_GPIO_Pin_selectCapteur2, Bit_SET);
            break;
        case GAUCHE_BAS:
            GPIO_WriteBit(m_GPIO_selectCapteur1, m_GPIO_Pin_selectCapteur1, Bit_SET);
            GPIO_WriteBit(m_GPIO_selectCapteur2, m_GPIO_Pin_selectCapteur2, Bit_SET);
            break;
        case DROITE_HAUT:
            GPIO_WriteBit(m_GPIO_selectCapteur1, m_GPIO_Pin_selectCapteur1, Bit_RESET);
            GPIO_WriteBit(m_GPIO_selectCapteur2, m_GPIO_Pin_selectCapteur2, Bit_RESET);
            break;
        case DROITE_BAS:
            GPIO_WriteBit(m_GPIO_selectCapteur1, m_GPIO_Pin_selectCapteur1, Bit_SET);
            GPIO_WriteBit(m_GPIO_selectCapteur2, m_GPIO_Pin_selectCapteur2, Bit_RESET);
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

    /////////////////////////////////////
    //  CommandCalibrerCapteurCouleur  //
    /////////////////////////////////////


// permet de calibrer le capteur couleur en calculant la valeur moyenne de chaque capteur
// nécessite 5 updates chaque 5 ms
// la première update peut se faire juste après la construction
CommandCalibrerCapteurCouleur::CommandCalibrerCapteurCouleur(CapteurCouleur* capteur)
    : capteurCouleur(capteur), state(0), resultat(0)
{
}

// récupère la valeur d'un capteur et passe à un autre
void CommandCalibrerCapteurCouleur::update()
{
    switch (state)
    {
        case 0:
            capteurCouleur->activerCapteur(GAUCHE_HAUT);
            state++;
            break;
        case 1:
            resultat += capteurCouleur->getTickValue();
            capteurCouleur->activerCapteur(GAUCHE_BAS);
            state++;
            break;
        case 2:
            resultat += capteurCouleur->getTickValue();
            capteurCouleur->activerCapteur(DROITE_HAUT);
            state++;
            break;
        case 3:
            resultat += capteurCouleur->getTickValue();
            capteurCouleur->activerCapteur(DROITE_BAS);
            state++;
            break;
        case 4:
            resultat += capteurCouleur->getTickValue();
            resultat /= 4;
            state++;
            break;
    }
}

// renvoient 0
Vitesse CommandCalibrerCapteurCouleur::getLinearSpeed()
{
    return 0.0f;
}

Angle CommandCalibrerCapteurCouleur::getAngularSpeed()
{
    return 0.0f;
}

// renvoit si le capteur a fini sa calibration
// le résultat est lisible dans getTicksMoyens()
bool CommandCalibrerCapteurCouleur::fini() const
{
    return (state > 4);
}

// une fois fini, renvoit le seuil calculé
uint16_t CommandCalibrerCapteurCouleur::getTicksMoyens() const
{
    return resultat;
}

    //////////////////////////////
    //    CommandCheckCouleur   //
    //////////////////////////////

// check la couleur d'un capteur
CommandCheckCouleur::CommandCheckCouleur(CapteurCouleur* capteur, PositionCapteurCouleur pos, uint16_t seuil)
    : seuilMoyenne(seuil), capteurCouleur(capteur), bleuMesure(0), rougeMesure(0)
    , nbUpdatesRestantes(nbUpdatePourAllumerLed), state(0)
{
    capteur->allumerDiodesBleues(true);
    capteur->allumerDiodesRouges(false);
    capteur->activerCapteur(pos);
    nbUpdatesRestantes = nbUpdatePourAllumerLed;
}

// check la couleur
void CommandCheckCouleur::update()
{
    switch (state)
    {
        // attente d'allumage de la diode bleu
        case 0:
            if (nbUpdatesRestantes >=0)
                nbUpdatesRestantes--;
            else
            {
                state++;
                capteurCouleur->getTickValue();
            }
            break;

        // récupération de la valeur bleu
        case 1:
            bleuMesure = capteurCouleur->getTickValue();
            capteurCouleur->allumerDiodesBleues(false);
            capteurCouleur->allumerDiodesRouges(true);
            nbUpdatesRestantes = nbUpdatePourAllumerLed;
            state++;

        // attente d'allumage de la diode rouge
        case 2:
            if (nbUpdatesRestantes >=0)
                nbUpdatesRestantes--;
            else
            {
                state++;
                capteurCouleur->getTickValue();
            }
            break;
        // récupération de la valeur bleu
        case 3:
            rougeMesure = capteurCouleur->getTickValue();
            capteurCouleur->allumerDiodesBleues(false);
            capteurCouleur->allumerDiodesRouges(false);
            state++;
    }
}

// renvoient 0
Vitesse CommandCheckCouleur::getLinearSpeed()
{
    return 0.0f;
}

Angle CommandCheckCouleur::getAngularSpeed()
{
    return 0.0f;
}

// renvoit si le capteur a fini de check la couleur
// le résultat est disponible dans les fonctions bleue() et rouge()
bool CommandCheckCouleur::fini() const
{
    return (state >= 4);
}

// une fois fini, renvoit la couleur
// les 2 peuvent renvoyer true si on est pas sur de la couleur
bool CommandCheckCouleur::bleue() const
{
    return (float)bleuMesure > 1.15f*(float)seuilMoyenne;
}

bool CommandCheckCouleur::rouge() const
{
    return (float)rougeMesure > 1.15f*(float)seuilMoyenne;
}
