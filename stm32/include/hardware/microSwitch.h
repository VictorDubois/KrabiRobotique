#ifndef DEF_MICROSWITCH
#define DEF_MICROSWITCH

#ifdef ROBOTHW

#ifdef STM32F40_41xxx
    #include "stm32f4xx_gpio.h"
#elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
    #include "stm32f10x_gpio.h"
#endif

class MicroSwitch
{
    public:

        // initialise la pin du microSwitch
        MicroSwitch(GPIO_TypeDef* GPIOx_microSwitch, uint16_t GPIO_Pin_x_microSwitch);

        // est ce que le microSwitch est fermé ?
        bool ferme() const;

    protected:

        // la pin du microSwitch
        GPIO_TypeDef* GPIOx;
        uint16_t GPIO_Pin_x;
};

#else

class MicroSwitch
{
    public:

        // constructeur vide pour Qt
        MicroSwitch();
        ~MicroSwitch();

        // est ce que le microSwitch est fermé ?
        bool ferme() const;
};

#endif
#endif

