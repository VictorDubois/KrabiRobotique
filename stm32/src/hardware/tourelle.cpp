#ifdef ROBOTHW

/* Includes ------------------------------------------------------------------*/
#include "tourelle.h"
#include "misc.h"
#include "leds.h"

//Variable pouvant être accédées par les interruptions C

///** @brief derniers temps mis pour faire un tour */
//uint16_t lastTurnTimes[20];
//
///** @brief tableau des instants de détection des objets */
//uint16_t objectDetectionInstant[20];

/** @brief nombre d'objets détectés */
uint8_t nombreObjetDetecte;

Tourelle::Tourelle()
{
    alerte = false;

    nombreObjetDetecte = 0;

    //EXTILine2_Config();
    EXTILine3_Config();
//    #ifdef STM32F40_41xxx
//        EXTILine3_Config();
//    #elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
//        EXTILine5_Config();
//    #endif

}

//Tourelle::Tourelle(TIM_TypeDef* timer_tourelle, uint16_t angleDecalage): timer_tourelle(timer_tourelle), angleDecalage(angleDecalage)
//{
//    alerte = false;
//
//    for(int i = 0 ; i < 20 ; i++)
//    {
//        this->objectDirection[i] = (uint16_t) -1;
//    }
//
//    for(int i = 0 ; i < 20 ; i++)
//    {
//        objectDetectionInstant[i] = (uint16_t) -1;
//    }
//
//    for(int i = 1 ; i < 20 ; i++)
//    {
//        lastTurnTimes[i] = (uint16_t) -1;
//    }
//    lastTurnTimes[0] = 60; //Valeur initiale réaliste, environ 30 tours/secondes
//    meanTurnTime = lastTurnTimes[0];
//
//    nombreObjetDetecte = 0;
//
//    resetZonesCritiques();
//    setZoneCritique(9000, 27000);
//
//    EXTILine2_Config();
//    EXTILine3_Config();
//    eteindreLED();
//    TIM6_Config();
//
//    lastTurnTimes[0] = 100;
//
//
//    objectDetectionInstant[0] = 50;
//
//    nombreObjetDetecte = 1;
//
//
////    objectDetectionInstant[0] = 50;
////
////    nombreObjetDetecte = 1;
////
////    uint16_t resultAngle = this->calculAngle(0);//décomposer calculAngle
////
////    objectDetectionInstant[0] = 0;
////    resultAngle = this->calculAngle(0);
////    objectDetectionInstant[0] = 10;
////    resultAngle = this->calculAngle(0);
////    objectDetectionInstant[0] = 20;
////    resultAngle = this->calculAngle(0);
////    objectDetectionInstant[0] = 40;
////    resultAngle = this->calculAngle(0);
////
////    bool resultUpdate = this->update();
////    nombreObjetDetecte = 1;
////    resultUpdate = this->update();
////    nombreObjetDetecte = 1;
////    resultUpdate = this->update();
////    resultUpdate = this->update();
////    resultUpdate = this->update();
////
////    resultUpdate = this->update();
////    nombreObjetDetecte = 1;
//}


//uint8_t Tourelle::setZoneCritique(uint16_t angleDebut, uint16_t angleFin)
//{
//    //Trouver le prochain emplacement libre
//    uint8_t emplacement = (uint8_t) -1;
//    for(int i = 0 ; i < 20 ; i++)
//    {
//        if(this->zonesCritiques[i][0] == (uint16_t) -1)//Si l'emplacement est libre
//        {
//            emplacement = i;
//            break;
//        }
//    }
//
//    //Si on a trouvé un emplacement libre, on y stocke la nouvelle zoneCritique
//    if(emplacement != (uint8_t) -1)
//    {
//        this->zonesCritiques[emplacement][0] = angleDebut;
//        this->zonesCritiques[emplacement][1] = angleFin;
//    }
//
//    return emplacement;
//}

//void Tourelle::resetZonesCritiques(void)
//{
//    for(int i = 0 ; i < 20 ; i++)
//    {
//        this->zonesCritiques[i][0] = (uint16_t) -1;
//        this->zonesCritiques[i][1] = (uint16_t) -1;
//    }
//}

//void Tourelle::resetZoneCritique(uint8_t numeroZone)
//{
//    this->zonesCritiques[numeroZone][0] = (uint16_t) -1;
//    this->zonesCritiques[numeroZone][1] = (uint16_t) -1;
//}

bool Tourelle::getAlerte(void)
{
    return this->alerte;
}

//uint16_t Tourelle::calculAngle(uint8_t numeroObjet)
//{
//    //return (uint16_t) 36000*((uint16_t) (objectDetectionInstant[numeroObjet]/this->meanTurnTime));
//    return (uint16_t) ((uint32_t) ((uint32_t) 36000 * (uint32_t) objectDetectionInstant[numeroObjet]) / (uint32_t) this->meanTurnTime);
//}


//bool Tourelle::update(void)
//{
//    bool newAlerte = false;
//
//    //Copie locale pour être thread-safe, et avoir une chance infime de louper un objet une fois
//    uint8_t nombreObjets = nombreObjetDetecte;
//    meanTurnTime = lastTurnTimes[0];
//
//    //Il n'y a que 20 objets max.
//    if(nombreObjets > 19)
//    {
//        nombreObjets = 19;
//    }
//
//    //Mise à jour du temps moyen pour faire un tour
//    //uint8_t nombreToursEffectues = -1;
////    for(int i = 0 ; i < 19 ; i++)
////    {
////        lastTurnTimes[i+1] = lastTurnTimes[i];
//////        if(lastTurnTimes[i] != -1)//Si le tour i a déjà été effectué, utile uniquement pour le 20 premiers tours
//////        {
//////            nombreToursEffectues = i;
//////        }
////    }
//
////    uint16_t sommeTempsTours = 0;
////
////    for(int i = 0 ; i < nombreToursEffectues ; i++)
////    {
////        sommeTempsTours += lastTurnTimes[i];
////    }
////
////    meanTurnTime = (uint16_t) sommeTempsTours/nombreToursEffectues;
//
//
//    for(uint8_t i = 0 ; i < nombreObjets ; i++)
//    {
//        if(objectDetectionInstant[i] != (uint8_t) -1)
//        {
//            //Calcul de la direction de l'objet
//            //calculAngle(0);
//            this->calculAngle(i);
//
//            this->objectDirection[i] = this->calculAngle(i);
//
//            //Vérification : est ce que l'objet est dans une zone critique
//            for(int j = 0 ; j < 20 ; j++)
//            {
//                //Si la zone critique existe
//                if(this->zonesCritiques[j][0] != (uint16_t) -1)
//                {
//                    //Si 0° non inclu dans la zone critique
//                    if(zonesCritiques[j][0] < zonesCritiques[j][1])
//                    {
//                        //Si l'objet est compris dans la zone critique
//                        if(zonesCritiques[j][0] < this->objectDirection[i] && this->objectDirection[i] < zonesCritiques[j][1])
//                        {
//                            newAlerte = true;
//                        }
//                    }
//                    else //Sinon 0° inclu dans la zone critique
//                    {
//                        //Si l'objet est plus proche de 0° que les bornes de la zone critique
//                        if(zonesCritiques[j][0] > this->objectDirection[i] || this->objectDirection[i] > zonesCritiques[j][1])
//                        {
//                            newAlerte = true;
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    nombreObjetDetecte = 0;
//
//    this->alerte = newAlerte;
//
//    return newAlerte;
//}

bool Tourelle::updateSimple(void)
{
    //Copie locale pour être thread-safe, et avoir une chance infime de louper un objet une fois
    uint8_t nombreObjets = nombreObjetDetecte;
    nombreObjetDetecte = 0;
    if(nombreObjets)
    {
        this->alerte = true;
        return true;
    }
    else
    {
        this->alerte = false;
        return false;
    }
}


///**
//  * @brief  Configures EXTI Line2 (connected to PA2 pin) in interrupt mode
//  * @param  None
//  * @retval None
//  */
//void EXTILine2_Config(void)
//{
//    GPIO_InitTypeDef   GPIO_InitStructure;
//    NVIC_InitTypeDef   NVIC_InitStructure;
//
//    EXTI_InitTypeDef   EXTI_InitStructure;
//
//    /* Enable GPIOA clock */
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
//    /* Enable SYSCFG clock */
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
//
//    /* Configure PA2 pin as input floating */
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
//    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);
//
//    /* Connect EXTI Line2 to PA2 pin */
//    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource2);
//
//    /* Configure EXTI Line2 */
//    EXTI_InitStructure.EXTI_Line = EXTI_Line2;
//    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//    EXTI_Init(&EXTI_InitStructure);
//
//    /* Enable and set EXTI Line2 Interrupt to the (not anymore) lowest priority */
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x09;//0x01 for lowest priority
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
//}

/**
  * @brief  Configures EXTI Line3 (connected to PA3 pin) in interrupt mode
  * @param  None
  * @retval None
  */
void EXTILine3_Config(void)
{
#ifdef STM32F40_41xxx


    GPIO_InitTypeDef   GPIO_InitStructure;
    NVIC_InitTypeDef   NVIC_InitStructure;

    EXTI_InitTypeDef   EXTI_InitStructure;

    /* Enable GPIOA clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    /* Enable SYSCFG clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    /* Configure PA3 pin as input floating */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Connect EXTI Line3 to PA3 pin */
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource3);

    /* Configure EXTI Line3 */
    EXTI_InitStructure.EXTI_Line = EXTI_Line3;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* Enable and set EXTI Line3 Interrupt to the (not anymore) lowest priority */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x08;//0x01 for lowest priority
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

#elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
    GPIO_InitTypeDef   GPIO_InitStructure;
    NVIC_InitTypeDef   NVIC_InitStructure;

    EXTI_InitTypeDef   EXTI_InitStructure;

    /* Enable GPIOA clock */
    RCC_AHBPeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    /* Enable SYSCFG clock */
    //RCC_AHBPeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    /* AFIO clock enabled dans initialisation.cpp */


    /* Configure PA3 pin as input floating */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Connect EXTI Line3 to PD5 pin */
    //GPIO_EventOutputConfig(GPIO_PortSourceGPIOA, GPIO_PinSource3);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource3);

    /* Configure EXTI Line3 */
    EXTI_InitStructure.EXTI_Line = EXTI_Line3;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* Enable and set EXTI Line5 Interrupt to the (not anymore) lowest priority */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//EXTI5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x08;//0x01 for lowest priority
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
#endif
}

void EXTILine5_Config(void)
{
#ifdef STM32F40_41xxx

#elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
    GPIO_InitTypeDef   GPIO_InitStructure;
    NVIC_InitTypeDef   NVIC_InitStructure;

    EXTI_InitTypeDef   EXTI_InitStructure;

    /* Enable GPIOA clock */
    RCC_AHBPeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

    /* Enable SYSCFG clock */
    //RCC_AHBPeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    /* AFIO clock enabled dans initialisation.cpp */


    /* Configure PA3 pin as input floating */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Connect EXTI Line3 to PD5 pin */
    //GPIO_EventOutputConfig(GPIO_PortSourceGPIOA, GPIO_PinSource3);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource5);

    /* Configure EXTI Line5 */
    EXTI_InitStructure.EXTI_Line = EXTI_Line5;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* Enable and set EXTI Line5 Interrupt to the (not anymore) lowest priority */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//EXTI5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//0x01 for lowest priority
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
#endif
}

///**
//  * @brief  EXTI Example program
//  * @param  None
//  * @retval None
//  */
//void ExtInt(void)
//{
//  /*!< At this stage the microcontroller clock setting is already configured,
//       this is done through SystemInit() function which is called from startup
//       file (startup_stm32f4xx.s) before to branch to application main.
//       To reconfigure the default setting of SystemInit() function, refer to
//        system_stm32f4xx.c file
//     */
//
//  /* Configure EXTI Line2 (connected to PA2 pin) in interrupt mode */
////  EXTILine2_Config();
////  eteindreLED();
////  TIM6_Config();
//
//  /* Generate software interrupt: simulate a rising edge applied on EXTI2 line */
///*  EXTI_GenerateSWInterrupt(EXTI_Line2);
//  EXTI_GenerateSWInterrupt(EXTI_Line2);
//  EXTI_GenerateSWInterrupt(EXTI_Line2);*/
///*
//  while (1)
//  {
//  }*/
//}

/**
  * @brief  Configures TIM6 as a counter
  * @param  None
  * @retval None
  *
void TIM6_Config(void)
{
    //RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;  // Enable GPIOD clock
    //GPIOD->MODER |= GPIO_MODER_MODER15_0; // Enable output mode for D15
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;   // Enable TIM6 clock
    TIM6->PSC = 41999;                    // Set prescaler to 41999
    TIM6->ARR = 59999;                     // Set auto-reload to 5999
    TIM6->CR1 |= TIM_CR1_OPM;             // One pulse mode
    TIM6->EGR |= TIM_EGR_UG;              // Force update
    TIM6->SR &= ~TIM_SR_UIF;              // Clear the update flag
    TIM6->DIER |= TIM_DIER_UIE;           // Enable interrupt on update event
    NVIC_EnableIRQ(TIM6_DAC_IRQn);        // Enable TIM6 IRQ
    TIM6->CR1 |= TIM_CR1_CEN;             // Enable TIM6 counter
}*/

///**
//  * @brief  Handles the TIM6 interrupt (useless for the tourelle)
//  * @param  None
//  * @retval None
//  */
//extern "C" void TIM6_DAC_IRQHandler()
//{
//    if(TIM6->SR & TIM_SR_UIF != 0) // If update flag is set
//    {
//        allumerLED();
//    }
//    TIM6->SR &= ~TIM_SR_UIF; // Interrupt has been handled
//}



///**
//  * @brief  This function handles External line 2 interrupt request.
//  * @param  None
//  * @retval None
//  */
//extern "C" void EXTI2_IRQHandler(void)
//{
//    if(EXTI_GetITStatus(EXTI_Line2) != RESET)
//    {
//        //Stocke le temps mis pour faire un tour
//        lastTurnTimes[0] = TIM_GetCounter(TIM6);
//
//        TIM_SetCounter(TIM6, 0);
//
//        /* Clear the EXTI line 2 pending bit */
//        EXTI_ClearITPendingBit(EXTI_Line2);
//    }
//}

/**
  * @brief  This function handles External line 3 interrupt request.
  * @param  None
  * @retval None
  */
extern "C" void EXTI3_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line3) != RESET)
    {

//        if(nombreObjetDetecte < 20)
//        {
            //Stocke l'instant de détection de l'objet
            //objectDetectionInstant[nombreObjetDetecte] = TIM_GetCounter(TIM6);
            nombreObjetDetecte++;

            allumerLED2();

//        }

        /* Clear the EXTI line 2 pending bit */
        EXTI_ClearITPendingBit(EXTI_Line3);
    }
}

//extern "C" void EXTI9_5_IRQHandler(void)
//{
//    if(EXTI_GetITStatus(EXTI_Line5) != RESET)
//    {
//
////        if(nombreObjetDetecte < 20)
////        {
//            //Stocke l'instant de détection de l'objet
//            //objectDetectionInstant[nombreObjetDetecte] = TIM_GetCounter(TIM6);
//            nombreObjetDetecte++;
//            allumerLED2();
////        }
//
//        /* Clear the EXTI line 2 pending bit */
//        EXTI_ClearITPendingBit(EXTI_Line5);
//    }
//}


#endif
