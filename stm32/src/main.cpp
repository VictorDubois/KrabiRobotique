#if 0
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"

#include "hardware/remote.h"

/* User defined function prototypes */
void GPIOA_Init(void);
void USART1_Init(void);
void led_toggle(void);

int main(void)
{
    /* Initialize GPIOA PIN8 */
    GPIOA_Init();
    /* Initialize USART1 */
    //USART1_Init();

    Remote::getSingleton()->waitForConnection();

    while(1)
    {
        /* Do nothing, all happens in ISR */
    }
}

#endif

#if defined(STM32F10X_CL)
    #include "initkrabi.h"
#elif defined(STM32F40_41xxx)
    #include "InitKrabiJunior.h"
#endif

#include "hardware/remote.h"

#define NVIC_CCR ((volatile unsigned long *)(0xE000ED14))

int main()
{
    #if defined(STM32F10X_MD) || defined(STM32F10X_CL)
        *NVIC_CCR = *NVIC_CCR | 0x200; // Set STKALIGN in NVIC
    #else
        SystemInit(); // Appelée implicitement ?
    #endif

    #if defined(STM32F40_41xxx) // H405
        InitKrabiJunior initKJ;
        initKJ.init();
    #elif defined(STM32F10X_CL) // H107
        InitKrabi initKrabi;
        initKrabi.init();
    #endif

    Remote::getSingleton()->waitForConnection();

    while(1);

    return 0;
}

