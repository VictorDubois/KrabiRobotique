#ifdef STM32F40_41xxx
    #include "stm32f4xx_rcc.h"
    #include "stm32f4xx_gpio.h"
    #include "stm32f4xx_tim.h"
#elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
    #include "stm32f10x_rcc.h"
    #include "stm32f10x_gpio.h"
    #include "stm32f10x_tim.h"
#endif
//#include "stm32f10x_remap.h"

#include "initialisation.h"

#include "hardware/tourelle.h"

//pour lancer l'update à chaque tic d'horloge
extern "C" void SysTick_Handler()
{
    // Count the number of SysTick_Handler call
    systick_count++;

#if DEBUG_BLINK_EACH_SECOND
    if (systick_count%200 == 0){
        Led::toggle(0);
    }
#endif

#ifndef STM32F40_41xxx
    Odometrie::odometrie->update();


    //StrategieV2::update();


    Tourelle::getSingleton()->update();

    Asservissement::asservissement->update();
#endif
}

#ifdef ROBOTHW
Initialisation::Initialisation(PositionPlusAngle position) : start(position), tirette(0)
{
	rcd = 0;
	rcg = 0;
}
#else
#include <QDebug>
Initialisation::Initialisation(PositionPlusAngle position, bool yellow, Robot* robot) : start(position), robot(robot)
{
    setYellow(yellow);
}
#endif

void Initialisation::init()
{
    initClock();
    initGPIO();
    initRotaryEncoders();

#ifdef ROBOTHW
    odometrie = new Odometrie(rcg, rcd);

#else
    odometrie = new Odometrie(this->robot);
#endif

    strategie = new StrategieV2(isYellow());
/*
#ifdef ROBOTHW
    tirette->attendreRemise();
    tirette->attendreEnlevee();
#endif
*/
    asservissement = new Asservissement(odometrie);

#ifdef ROBOTHW
    setYellow();
#endif

    if(!isYellow())
    {
        start = start.getSymetrical();
    }

    odometrie->setPos(start);
}

bool Initialisation::isYellow()
{
    return yellow;
}


Asservissement* Initialisation::getAsservissement()
{
    return asservissement;
}

Odometrie* Initialisation::getOdometrie()
{
    return odometrie;
}

StrategieV2* Initialisation::getStrategie()
{
    return strategie;
}

void Initialisation::setYellow(bool val)
{
    yellow = val;
}

#ifdef PONEY
// Initialise le système d'horloge
void Clk_Init()
{
    //Rien pour le STM32F4, tout est déjà fait dans SystemInit(), appelée implicitement
    #if defined(STM32F10X_MD) || defined(STM32F10X_CL)
        // Démarre l'horloge interne (8 MHz)
        RCC_HSICmd(ENABLE);
        // On attend qu'elle soit allumée
        while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
        // Une fois demarée, on utilise celle ci
        RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);

        // Démarre l'horloge externe à 25MHz
        RCC_HSEConfig(RCC_HSE_ON);
        // On attend qu'elle soit allumée
        while(RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);


        // PLL2 à (8/5) * 25Mhz = 40 Mhz
        RCC_PREDIV2Config(RCC_PREDIV2_Div5);
        RCC_PLL2Config(RCC_PLL2Mul_8);
        // On démarre le PLL2 une fois la config entrée
        RCC_PLL2Cmd(ENABLE);
        // On attend qu'il soit vraiment allumé
        while(RCC_GetFlagStatus(RCC_FLAG_PLL2RDY) == RESET);

        // Initialisation du PL à (9/5) * 40MHz = 72MHz
        RCC_PREDIV1Config(RCC_PREDIV1_Source_PLL2, RCC_PREDIV1_Div5);
        RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_9);
        // On démarre le PLL une fois la config entrée
        RCC_PLLCmd(ENABLE);
        // On attend qu'il soit vraiment allumé
        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

        // On démarre les composants internes au microcontroleur
        RCC_OTGFSCLKConfig(RCC_OTGFSCLKSource_PLLVCO_Div3); // USB OTG FS clock (OTGFSCLK)
        RCC_ADCCLKConfig(RCC_PCLK2_Div6); // ADC clock (ADCCLK) : 72MHz / 6 = 12MHz
        RCC_PCLK2Config(RCC_HCLK_Div1); // High Speed APB clock (PCLK2) : 72Mhz
        RCC_PCLK1Config(RCC_HCLK_Div2); // Low Speed APB clock (PCLK1) : 72Mhz / 2 = 36MHz
        RCC_HCLKConfig(RCC_SYSCLK_Div1); // AHB clock (HCLK) : 72Mhz
        // Flash 1 wait state
        *(vu32 *)0x40022000 = 0x12;
        // On utilise le PLL comme horloge de référence
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); // system clock (SYSCLK) : 72MHz
    #endif
}

// Définit quelques horloges supplémentaires
void initAutresHorloges()
{
    #ifdef STM32F40_41xxx
        RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE);
        RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB, ENABLE);
        RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOC, ENABLE);
        RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOD, ENABLE);
        RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOE, ENABLE);
        /*RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_DMA1,  ENABLE);
        RCC_APB2PeriphClockCmd( RCC_APB2Periph_ADC1,  ENABLE);
        //RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); no equivalent in F4, seems to be unecessary

        // Sharps
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);

    #elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
        #ifdef STM32F10X_CL // stm h107
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE);
        #endif
    #endif
}


// Mettez toutes vos initialisations de PIN dans la fonction "initialisation"
// On l'appellera ensuite dans le main au tout début pour tout initialiser d'un coup
void initialisationDesPIN()
{


#ifdef STM32F10X_CL // Pour le stm32 h107

    // Pompe à vide


#endif //STM32F10X_CL

#ifdef STM32F10X_MD // pour la STM32 H103 2014 v1 :

    // Patte coté de la partie bleu ou jaune
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // Tirette
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    // Pattes des servos
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);

    // servo 1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // servo 2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // servo 3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // servo 4
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // LED Verte
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_RESET);

#endif //STM32F10X_MD

#ifdef STM32F40_41xxx // pour la STM32 H405 2014 v1 :

    // Roues codeuses
    GPIO_PinAFConfig (GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);
    GPIO_PinAFConfig (GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);
    GPIO_PinAFConfig (GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
    GPIO_PinAFConfig (GPIOA, GPIO_PinSource9, GPIO_AF_TIM1);

    // Moteurs
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_SET);*/
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM2);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM2);

    // Sharps
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 |GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // Patte coté de la partie bleu ou jaune
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // Tirette
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // Pattes des servos
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM3);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM3);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM3);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_TIM3);

    // servo 1
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // servo 2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // servo 3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // servo 4
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // LED Verte
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_WriteBit(GPIOC, GPIO_Pin_12, Bit_SET);

#endif //STM32F40_41xxx

}
#endif //PONEY


