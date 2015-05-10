#include "remote.h"

#include "krabipacket.h"

#include "leds.h"
//#include "canonLances.h"
//#include "canonFilet.h"
//#include "brak.h"
#include "brasLateraux.h"
#include "odometrie.h"

#include <string.h>
#include <stdarg.h>
#include <stdio.h>

GenericBuffer Remote::buffer = GenericBuffer();

Remote* Remote::singleton = 0;

Remote* Remote::getSingleton()
{
    if (singleton==0)
        singleton = new Remote();

    return singleton;
}


Remote::Remote() : mRemoteMod(false), mRemoteControl(false)
{
#ifdef ROBOTHW
    initClocksAndPortsGPIO();
    initUART(USART_BAUDRATE);
#endif

    /*isOpenContainer = false;
    isOpenLeftArm = false;
    isOpenRightArm = false;
    timerLances = -1;

    brakInv = false;
    brakOut = false;*/

    linSpeed = 0.;
    angSpeed = 0.;
}

void Remote::initClocksAndPortsGPIO()
{

#ifdef ROBOTHW

#ifdef STM32F40_41xxx // Pin pour le stm32 h405

//CF tuto : http://eliaselectronics.com/stm32f4-discovery-usart-example/

/* enable peripheral clock for USART2 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
/* GPIOA clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);


    GPIO_InitTypeDef GPIO_InitStructure;
 	// port A pin 2 TX : du stm vers l'extérieur
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    #ifdef STM32F40_41xxx
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;// the pins are configured as alternate function so the USART peripheral has access to them
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;// this defines the output type as push pull mode (as opposed to open drain)
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;// this activates the pullup resistors on the IO pins
    #elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    #endif
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // La vitesse de rafraichissement du port (// this defines the IO speed and has nothing to do with the baudrate!)
    GPIO_Init(GPIOA, &GPIO_InitStructure);

 	// port A pin 3 RX : vers le stm
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    #ifdef STM32F40_41xxx
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
        GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
    #endif
#endif
#ifdef STM32F10X_CL // Pin pour le stm32 h107
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    // port C pin 10 TX - ext2 15
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // port C pin 11 RX - ext2 14
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // port D pin 10 : la direction (TX/RX)
    /*GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOD, &GPIO_InitStructure);*/

    /*GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3);     // Tx
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3);*/     // Rx
#endif

#endif

}

void Remote::initUART(int baudRate)
{
#ifdef ROBOTHW
    USART_InitTypeDef USART_InitStructure;

    USART_InitStructure.USART_BaudRate = baudRate;

    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(REMOTE_USART_INDEX, &USART_InitStructure);

    USART_Cmd(REMOTE_USART_INDEX, ENABLE);

    USART_ITConfig(REMOTE_USART_INDEX, USART_IT_RXNE, ENABLE);

    /**** IT ***/
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Configure the NVIC Preemption Priority Bits */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

    /* Enable the USARTy Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
#endif
}

extern "C" void USART3_IRQHandler(void)
{
    volatile unsigned int IIR;

    IIR = REMOTE_USART_INDEX->SR;
    if (IIR & USART_FLAG_RXNE)
    {
        if (Remote::buffer.size < USART_BUFFER_SIZE)
            Remote::buffer.buf[Remote::buffer.size++] = (REMOTE_USART_INDEX->DR & 0x1FF);

        REMOTE_USART_INDEX->SR &= ~USART_FLAG_RXNE;
    }
}

void Remote::sendRaw(int data)
{
    if (!mRemoteMod)
        return;

#ifdef ROBOTHW
    // Wait until the send buffer is cleared finishes
    USART_SendData(REMOTE_USART_INDEX, (u16) data);
    while (USART_GetFlagStatus(REMOTE_USART_INDEX, USART_FLAG_TC) == RESET);
#endif
}

void Remote::send(KrabiPacket &packet)
{
    uint8_t size = packet.length();
    uint8_t* data = packet.data();
    for(uint8_t i = 0; i<size; i++)
        sendRaw(data[i]);

    sendRaw(0x0D);
    sendRaw(0x0A);
}

void Remote::send(char* text)
{
    int pos = 0;
    while(text[pos] != '\0' )
    {
        sendRaw(text[pos]);
        pos++;
    }

    sendRaw(0x0D);
    sendRaw(0x0A);
}

void Remote::logDirect(char* text)
{
    Remote::getSingleton()->send(text);
}

void Remote::log(const char* format, ...)
{
    char text[32];

    va_list argptr;
    va_start(argptr, format);
    vsprintf(text, format, argptr);
    va_end(argptr);

    KrabiPacket packet(KrabiPacket::LOG_NORMAL);
    packet.addString(text);

    send(packet);
}

void Remote::debug(const char* format, ...)
{
    char text[32];

    va_list argptr;
    va_start(argptr, format);
    vsprintf(text, format, argptr);
    va_end(argptr);

    KrabiPacket packet(KrabiPacket::LOG_DEBUG);
    packet.addString(text);

    send(packet);
}

bool Remote::dataAvailable()
{
#ifdef ROBOTHW
    return REMOTE_USART_INDEX->SR & USART_FLAG_RXNE;
#else
    return false;
#endif
}

int Remote::receiveData()
{
#ifdef ROBOTHW
    while (!(REMOTE_USART_INDEX->SR & USART_FLAG_RXNE));
    return ((int)(REMOTE_USART_INDEX->DR & 0x1FF));
#else
    return 0;
#endif
}

void Remote::waitForConnection()
{
    while(!dataAvailable());

    update();

    for(int i(0); i<20; ++i)
        debug(".");
}

void Remote::update(bool allowChangeMode)
{
    /*while(dataAvailable())
    {
        mRemoteMod = true;
        mBuffer[mBufferSize++] = receiveData();

        if (mBufferSize > 2)
        {
            log("R %d", buffer.size);
            if (mBuffer[mBufferSize - 2] == 0x0D && mBuffer[mBufferSize - 1]== 0x0A)
            {
                KrabiPacket p(mBuffer, mBufferSize - 2);
                mBufferSize = 0;

                if (p.isValid())
                    treat(p);
            }
        }
    }*/

    if (buffer.size > 2)
    {
        mRemoteMod = true;

        static int aa = 0;
        /*aa++;
        if (aa % 100 == 0)*/
            //log("R %d %d %d", buffer.size, buffer.buf[buffer.size - 2], buffer.buf[buffer.size - 1]);
        for(int i(0); i < buffer.size - 1; ++i)
            if (buffer.buf[i] == 0x0D && buffer.buf[i + 1]== 0x0A)
            {
                log("R %d %d %d", buffer.size, buffer.buf[buffer.size - 2], buffer.buf[buffer.size - 1]);
                KrabiPacket p(buffer.buf, i);
                if (i < buffer.size - 2)
                    memmove(buffer.buf, buffer.buf + i + 2, buffer.size - (i + 2));
                buffer.size -= i + 2;
                i = 0;

                if (p.isValid())
                    treat(p);
            }
    }

    /*if (!allowChangeMode && remoteMode && dataAvailable())
    {
        int order = receiveData();
        Remote::log("Got:");
        Remote::getSingleton()->sendData(order);

        // Linear Speed
        if (order>=0 and order<=50)
            linSpeed = ((float)(order-25)) / 25. * LINEAR_REMOTE_SPEED_LIMIT;

        // Angular Speed
        if (order>=51 and order<=101)
            angSpeed = -((float)(order-75)) / 25. * ANGULAR_REMOTE_SPEED_LIMIT;
    }*/
}

void Remote::treat(KrabiPacket &packet)
{
    switch(packet.id())
    {
        case KrabiPacket::REMOTE_MOD_SET:
            mRemoteMod = true;
            break;
        case KrabiPacket::REMOTE_MOD_RESET:
            mRemoteMod = false;
            break;
        case KrabiPacket::REMOTE_CONTROL_SET:
            mRemoteMod = true;
            mRemoteControl = true;
            break;
        case KrabiPacket::REMOTE_CONTROL_RESET:
            mRemoteControl = false;
            break;
        case KrabiPacket::SET_ODOMETRIE:
        {
            float wheelsize = packet.get<float>();
            float interaxis = packet.get<float>();
            Odometrie::odometrie->setSettings(interaxis, wheelsize);
            break;
        }
        case KrabiPacket::WATCH_REQUIRE:
            requireWatch(packet);
            break;
    }
}

void Remote::requireWatch(KrabiPacket &packet)
{
    uint16_t w = packet.get<uint16_t>();
    switch(w)
    {
    case KrabiPacket::W_ODOMETRIE:
        KrabiPacket p(KrabiPacket::WATCH_VARIABLE, KrabiPacket::W_ODOMETRIE);
        p.add(Odometrie::odometrie->getWheelSize());
        p.add(Odometrie::odometrie->getInterAxisDistance());
        send(p);
        break;
    }
}

bool Remote::isInRemoteMod()
{
    return mRemoteMod;
}

bool Remote::isInRemoteControl()
{
    return mRemoteControl;
}

float Remote::getLeftPWM()
{
    return linSpeed;
#if defined(STM32F40_41xxx) || defined(STM32F10X_MD)
    return linSpeed + angSpeed;
#else
    return linSpeed - angSpeed;
#endif
}

float Remote::getRightPWM()
{
    return angSpeed;
#if defined(STM32F40_41xxx) || defined(STM32F10X_MD)
    return linSpeed - angSpeed;
#else
    return linSpeed + angSpeed;
#endif
}

