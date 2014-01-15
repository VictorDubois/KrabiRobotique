#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"

#include "initialisation.h"

// Initialise le système d'horloge
void Clk_Init()
{
#ifdef STM32F10X_CL //Pour le stm32 h107
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
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
#ifdef STM32F10X_CL // stm h107
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE);
#endif
}



// Mettez toutes vos initialisations de PIN dans la fonction "initialisation"
// On l'appellera ensuite dans le main au tout début pour tout initialiser d'un coup
void initialisationDesPIN()
{
    GPIO_InitTypeDef GPIO_InitStructure;

#ifdef STM32F10X_CL // Pour le stm32 h107

    // Patte coté de la partie bleu ou jaune
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
/*
    // Tirette
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    // Pattes des servos

    // servo 1 (bras gauche)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // servo 2 (bras droite)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // servo 3 (balais)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);


    // servo 4 (UltraSon)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
*/
    // LED Verte
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_RESET);

    // LED Jaune
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_RESET);

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
    GPIO_PinRemapConfig(GPIO_Remap_TIM3, ENABLE);

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


}



