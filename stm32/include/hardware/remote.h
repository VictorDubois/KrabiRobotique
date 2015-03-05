#ifndef REMOTE_H
#define REMOTE_H

#ifdef STM32F40_41xxx
    #include "stm32f4xx_rcc.h"
    #include "stm32f4xx_gpio.h"
    #include "stm32f4xx_usart.h"
    #define REMOTE_USART_INDEX USART2
#elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
    #include "stm32f10x_rcc.h"
    #include "stm32f10x_gpio.h"
    #include "stm32f10x_usart.h"
    #define REMOTE_USART_INDEX USART1
#endif

#ifdef KRABI_JR
    #include "container.h"
    #include "braslateral.h"
#endif

//#include "krabipacket.h"

#define USART_BAUDRATE 9600
#define LINEAR_REMOTE_SPEED_LIMIT 2.0
#define ANGULAR_REMOTE_SPEED_LIMIT 0.01

class Remote
{
    public:
        static Remote* getSingleton();
        static void log(char* msg);

        void sendData(int data);
        //void sendData(KrabiPacket* packet);
        int receiveData();
        bool dataAvailable();

        void update(bool allowChangeMode = false);

        bool isRemoteMode();

        float getLeftPWM();
        float getRightPWM();
    protected:
    private:
        static Remote* singleton;
        Remote();

        void initClocksAndPortsGPIO();
        void initUART(int baudRate);

        long timerLances;
        bool remoteMode, isOpenContainer, isOpenLeftArm, isOpenRightArm, brakInv, brakOut;
        float linSpeed, angSpeed;
};

#endif // REMOTE_H
