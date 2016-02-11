#ifndef Turret_H
#define Turret_H

#ifdef STM32F40_41xxx
    #include "stm32f4xx_rcc.h"
    #include "stm32f4xx_gpio.h"
    #include "stm32f4xx_usart.h"
    #define TURRET_USART_INDEX USART2//UART5//USART6//USART3
#elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
    #include "stm32f10x_rcc.h"
    #include "stm32f10x_gpio.h"
    #include "stm32f10x_usart.h"
    #define TURRET_USART_INDEX USART1 //UART5 //USART2
#endif

#define USART_BAUDRATE 9600

class Turret
{
    public:
        static Turret* getSingleton();
        static void log(char* msg);

        void sendData(int data);

        int receiveData();
        bool dataAvailable();

        void update();
        int getDist(int i);
        int getAng(int i);
        bool isTurretMode();
    protected:
    private:
        Turret();
        static Turret* singleton;
        bool TurretMode;

        void initClocksAndPortsGPIO();
        void initUART(int baudRate);

        int messstat;
        int angcentaine, tempdist,tempang;
        int ang[3], dist[3];

        virtual ~Turret();
};
#endif
