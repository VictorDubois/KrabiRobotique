#ifndef REMOTE_H
#define REMOTE_H

#include "misc.h"
#ifdef STM32F40_41xxx   //STM32 H405
    #include "stm32f4xx_rcc.h"
    #include "stm32f4xx_gpio.h"
    #include "stm32f4xx_usart.h"
    #define REMOTE_USART_INDEX USART2
    #define REMOTE_USART_IRQ_HANDLER USART2_IRQHandler
    #define REMOTE_USART_IRQn USART2_IRQn
#elif defined(STM32F10X_MD) || defined(STM32F10X_CL) // STM32F10X (i.e. STM32 H107)
    #include "stm32f10x_rcc.h"
    #include "stm32f10x_gpio.h"
    #include "stm32f10x_usart.h"

    // USART name
    #define REMOTE_USART_INDEX USART1
    // Interruption handler name
    #define REMOTE_USART_IRQ_HANDLER USART1_IRQHandler
    #define REMOTE_USART_IRQn USART1_IRQn

#endif

#include "krabipacket.h"

#define USART_BUFFER_SIZE 128
#define USART_BAUDRATE 9600
#define LINEAR_REMOTE_SPEED_LIMIT 2.0
#define ANGULAR_REMOTE_SPEED_LIMIT 0.01

struct GenericBuffer
{
    GenericBuffer();

    bool append(uint8_t d);
    uint8_t pop_front();
    bool isEmpty() const;

    uint8_t size;
    uint8_t buf[USART_BUFFER_SIZE];
};

extern "C" void REMOTE_USART_IRQ_HANDLER(void);

class Remote
{
    public:
        static Remote* getSingleton();
        static void logDirect(char* text);

        void addData(int data);
        void send(char *text);
        void send(KrabiPacket &packet);

        void treat(KrabiPacket &packet);
        void sendWatch(KrabiPacket::W_TABLE w, int time = -1);

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

        static GenericBuffer bufferRecv, bufferSend;
    protected:
    private:
        static Remote* singleton;
        Remote();

        void initClocksAndPortsGPIO();
        void initUART(int baudRate);

        //long timerLances;
        bool mRemoteMod, mRemoteControl;//, isOpenContainer, isOpenLeftArm, isOpenRightArm, brakInv, brakOut;
        float linSpeed, angSpeed;

        bool mWatchesEnabled[KrabiPacket::MAX_WATCHES];

        //uint8_t mBufferSize;
        //uint8_t mBuffer[KRABIPACKET_MAXSIZE];
};

#endif // REMOTE_H
