#include "hardware/remote.h"
#include "initKrabiJunior.h"
#include "initkrabi.h"

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

