#ifndef REMOTE_H
#define REMOTE_H

#ifdef STM32F40_41xxx
    #include "stm32f4xx_rcc.h"
    #include "stm32f4xx_gpio.h"
    #include "stm32f4xx_usart.h"
    #define REMOTE_USART_INDEX USART2
#elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
    #include "misc.h"
    #include "stm32f10x_rcc.h"
    #include "stm32f10x_gpio.h"
    #include "stm32f10x_usart.h"
    #define REMOTE_USART_INDEX USART3
#endif

#include "krabipacket.h"

#define USART_BUFFER_SIZE 128
#define USART_BAUDRATE 9600
#define LINEAR_REMOTE_SPEED_LIMIT 2.0
#define ANGULAR_REMOTE_SPEED_LIMIT 0.01

struct GenericBuffer {
    uint8_t size;
    uint8_t buf[USART_BUFFER_SIZE];
};

extern "C" void USART3_IRQHandler(void);

class Remote
{
    public:
        static Remote* getSingleton();
        static void logDirect(char* text);

        void sendRaw(int data);
        void send(char *text);
        void send(KrabiPacket &packet);

        void treat(KrabiPacket &packet);
        void requireWatch(KrabiPacket &packet);

        int receiveData();
        bool dataAvailable();

        void update(bool allowChangeMode = false);

        bool isInRemoteMod();
        bool isInRemoteControl();

        template<typename T>
        void watch(uint16_t index, T value)
        {
            KrabiPacket packet(KrabiPacket::WATCH_VARIABLE);
            packet.add(index);
            packet.add(value);

            send(packet);
        }

        template<typename T1, typename T2>
        void watch(uint16_t index, T1 value1, T2 value2)
        {
            KrabiPacket packet(KrabiPacket::WATCH_VARIABLE);
            packet.add(index);
            packet.add(value1);
            packet.add(value2);

            send(packet);
        }

        template<typename T1, typename T2, typename T3>
        void watch(uint16_t index, T1 value1, T2 value2, T3 value3)
        {
            KrabiPacket packet(KrabiPacket::WATCH_VARIABLE);
            packet.add(index);
            packet.add(value1);
            packet.add(value2);
            packet.add(value3);

            send(packet);
        }

        void log(const char* format, ...);
        void debug(const char* format, ...);

        void waitForConnection();

        float getLeftPWM();
        float getRightPWM();

        static GenericBuffer buffer;
    protected:
    private:
        static Remote* singleton;
        Remote();

        void initClocksAndPortsGPIO();
        void initUART(int baudRate);

        //long timerLances;
        bool mRemoteMod, mRemoteControl;//, isOpenContainer, isOpenLeftArm, isOpenRightArm, brakInv, brakOut;
        float linSpeed, angSpeed;

        //uint8_t mBufferSize;
        //uint8_t mBuffer[KRABIPACKET_MAXSIZE];
};

#endif // REMOTE_H
