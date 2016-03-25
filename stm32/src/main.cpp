#include "hardware/remote.h"

#if defined(STM32F40_41xxx)
    #include "initKrabiJunior.h"
    #include "clock.h"
    #include "KJ2016Tempo.h"
#elif defined(STM32F10X_CL)
    #include "initkrabi.h"
#endif

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
        //initKJ.init(); // Not this year - we are NOT using odometry, strategiev2, etc, so it's best not to init them at all
        initKJ.initClock();
        initKJ.initGPIO();
        Clock::getInstance();
//        initKJ.initActionneurs(); // For servos
    #elif defined(STM32F10X_CL) // H107
        InitKrabi initKrabi;
        initKrabi.init();
    #endif

    //Remote::getSingleton()->waitForConnection();

    /** Action sequencing for KJ **/
    #ifdef STM32F40_41xxx
        //KJ2016Tempo::run(initKJ.isYellow());
    #endif

    while(1);

    return 0;
}

