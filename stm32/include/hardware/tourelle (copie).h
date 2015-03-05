#ifndef TOURELLE_H_INCLUDED
#define TOURELLE_H_INCLUDED

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_exti.h"
#include "misc.h"
#include "leds.h"

/** @addtogroup STM32F4_Discovery_Peripheral_Examples
  * @{
  */

/** @addtogroup EXTI
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

//EXTI_InitTypeDef   EXTI_InitStructure;
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
//void EXTILine2_Config(void);
//void LEDInit(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  EXTI Example program
  * @param  None
  * @retval None
  */
void ExtInt(void);


/**
  * @brief  Configures EXTI Line2 (connected to PA2 pin) in interrupt mode
  * @param  None
  * @retval None
  */
void EXTILine2_Config(void);

/**
  * @brief  This function handles External line 2 interrupt request.
  * @param  None
  * @retval None
  */
extern "C" void EXTI2_IRQHandler(void);

#endif
