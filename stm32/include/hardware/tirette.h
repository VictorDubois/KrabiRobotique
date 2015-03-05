#ifndef DEF_TIRETTE
#define DEF_TIRETTE

#ifdef STM32F40_41xxx
    #include "stm32f4xx_gpio.h"
#elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
    #include "stm32f10x_gpio.h"
#endif

class Tirette
{
    public:

        // initialise la pin de la tirette
        Tirette(GPIO_TypeDef* GPIOx_tirette, uint16_t GPIO_Pin_x_tirette);

        // attends jusqu'à ce que la tirette soit enlevée
        void attendreEnlevee() const;

        // attends jusqu'à ce que la tirette soit remise
        void attendreRemise() const;

        // est ce que la tirette est enlevée ?
        bool enlevee() const;

    protected:

        // la pin de la tirette
        GPIO_TypeDef* GPIOx;
        uint16_t GPIO_Pin_x;
};

#endif
