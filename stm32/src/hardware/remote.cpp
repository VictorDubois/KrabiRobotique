#include "remote.h"

#include "krabipacket.h"
#include "strategieV2.h"

#include "leds.h"
#include "brasLateraux.h"
#include "odometrie.h"
#include "asservissement.h"

#include <string.h>
#include <stdarg.h>
#include <stdio.h>

GenericBuffer Remote::bufferRecv = GenericBuffer();
GenericBuffer Remote::bufferSend = GenericBuffer();

GenericBuffer::GenericBuffer()
{
    size = 0;
    for(size_t i=0;i<USART_BUFFER_SIZE;++i)
        buf[i] = 0;
}

bool GenericBuffer::append(uint8_t d)
{
    if(size == USART_BUFFER_SIZE)
        return true;

    buf[size] = d;
    ++size;
    return false;
}

uint8_t GenericBuffer::pop_front()
{
    if(isEmpty())
        return 0;

    int d = buf[0];

    --size;
    memmove(buf, buf+1, size);
    return d;
}

bool GenericBuffer::isEmpty() const
{
    return size == 0;
}

Remote* Remote::singleton = 0;

Remote* Remote::getSingleton()
{
    if (singleton==0)
        singleton = new Remote();

    return singleton;
}


Remote::Remote() : mRemoteMod(true), mRemoteControl(false)
{
    #ifdef ROBOTHW
    initClocksAndPortsGPIO();
    initUART(USART_BAUDRATE);
#endif

    linSpeed = 0.;
    angSpeed = 0.;

    for(int i(0); i < KrabiPacket::MAX_WATCHES; i++)
        mWatchesEnabled[i] = false;
    mWatchesEnabled[KrabiPacket::W_POSITION] = true;
}

void Remote::initClocksAndPortsGPIO()
{
#ifdef STM32F10X_CL //H107

    /* Bit configuration structure for GPIOB PIN6 and PIN7 */
    GPIO_InitTypeDef gpioa_init_struct;

    /* Enalbe clock for USART1, AFIO and GPIOA */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO |
                           RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);


    /** USART remap **/
    // Enable USART1 remap from PA9 and PA10 (used by USB) to PB6 and PB7
    GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);

    /** GPIO setup **/
    GPIO_InitTypeDef GPIO_InitStructure;

    // port B pin 6 TX
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;

    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // port B pin 7 RX
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;

    GPIO_Init(GPIOB, &GPIO_InitStructure);
#endif
#ifdef STM32F40_41xxx //H405

/** /!\ NOT TESTED IN FOREVER /!\ **/

//CF tuto : http://eliaselectronics.com/stm32f4-discovery-usart-example/

    /* enable peripheral clock for USART2 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    /* GPIOA clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);


    GPIO_InitTypeDef GPIO_InitStructure;
 	// port A pin 2 TX : du stm vers l'extérieur
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;// the pins are configured as alternate function so the USART peripheral has access to them
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;// this defines the output type as push pull mode (as opposed to open drain)
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;// this activates the pullup resistors on the IO pins

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // La vitesse de rafraichissement du port (// this defines the IO speed and has nothing to do with the baudrate!)
    GPIO_Init(GPIOA, &GPIO_InitStructure);

 	// port A pin 3 RX : vers le stm
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

#endif
}

void Remote::initUART(int baudRate)
{
    /* USART configuration structure for USART */
    USART_InitTypeDef usart_init_struct;

    /* Enable USART */
    USART_Cmd(REMOTE_USART_INDEX, ENABLE);

    /* 8-bit data, One stop bit
     * No parity, Do both Rx and Tx, No HW flow control
     */
    usart_init_struct.USART_BaudRate   = baudRate;
    usart_init_struct.USART_WordLength = USART_WordLength_8b;
    usart_init_struct.USART_StopBits   = USART_StopBits_1;
    usart_init_struct.USART_Parity     = USART_Parity_No ;
    usart_init_struct.USART_Mode       = USART_Mode_Rx | USART_Mode_Tx;
    usart_init_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    /* Configure USART */
    USART_Init(REMOTE_USART_INDEX, &usart_init_struct);
    /* Enable RXNE interrupt */
    USART_ITConfig(REMOTE_USART_INDEX, USART_IT_RXNE, ENABLE);
    /* Enable USART global interrupt */
    NVIC_EnableIRQ(REMOTE_USART_IRQn);
}

extern "C"
{
/** Interruption handler **/
void REMOTE_USART_IRQ_HANDLER(void)
{
    if(USART_GetFlagStatus(REMOTE_USART_INDEX, USART_FLAG_RXNE) != RESET) //Interuption type: 'RX register Not Empty' (i.e. data to be read)
    {
        uint8_t d = USART_ReceiveData(REMOTE_USART_INDEX); // We can only read one byte at a time
        Remote::bufferRecv.append(d);

        //Debug
        //Remote::getSingleton()->addData(d);
    }

    if(USART_GetFlagStatus(REMOTE_USART_INDEX, USART_FLAG_TXE) != RESET) //Interuption type: 'TX register Empty' (i.e. ready to send)
    {
        if(!Remote::bufferSend.isEmpty()) // There IS some data to send
            USART_SendData(REMOTE_USART_INDEX, Remote::bufferSend.pop_front()); // We can only send one byte per TXE interrupt
        else // We ran out of data to send
            USART_ITConfig(REMOTE_USART_INDEX, USART_IT_TXE, DISABLE); // Disable the TXE interrupt
    }
}
}

void Remote::addData(int data)
{
    if (!mRemoteMod)
        return;

    USART_ITConfig(REMOTE_USART_INDEX, USART_IT_TXE, ENABLE); // Enable the TXE interrupt

    Remote::bufferSend.append(data);
}

void Remote::send(KrabiPacket &packet)
{
    uint8_t size = packet.length();
    uint8_t* data = packet.data();
    for(uint8_t i = 0; i<size; i++)
        addData(data[i]);

    addData(0x0D);
    addData(0x0A);
}

void Remote::send(char* text)
{
    int pos = 0;
    while(text[pos] != '\0' )
    {
        addData(text[pos]);
        pos++;
    }

    addData(0x0D);
    addData(0x0A);
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
    while(Remote::bufferRecv.isEmpty());

    update();

    for(int i(0); i<20; ++i)
        debug(".");
}

void Remote::update(bool allowChangeMode)
{
    static long tick = 0;
    tick++;

    for(int i(0); i < KrabiPacket::MAX_WATCHES; i++)
        if (mWatchesEnabled[i])
        {
            if ((KrabiPacket::W_TABLE)i == KrabiPacket::W_POSITION)
            {
                if (tick % 20 == i)
                    sendWatch((KrabiPacket::W_TABLE)i);
            }
            else if (tick % 10 == i)
                    sendWatch((KrabiPacket::W_TABLE)i);
        }

    /*static int test = 0;
    test++;
    if (test % 20 == 0)
        log("test pika");*/

    if (bufferRecv.size > 2)
    {
        mRemoteMod = true;

        static int aa = 0;
        /*aa++;
        if (aa % 100 == 0)*/
            //log("R %d %d %d", buffer.size, buffer.buf[buffer.size - 2], buffer.buf[buffer.size - 1]);
        for(int i(0); i < bufferRecv.size - 1; ++i)
            if (bufferRecv.buf[i] == 0x0D && bufferRecv.buf[i + 1]== 0x0A)
            {
                //log("R %d %d %d", buffer.size, buffer.buf[buffer.size - 2], buffer.buf[buffer.size - 1]);
                KrabiPacket p(bufferRecv.buf, i);
                if (i < bufferRecv.size - 2)
                    memmove(bufferRecv.buf, bufferRecv.buf + i + 2, bufferRecv.size - (i + 2));
                bufferRecv.size -= i + 2;
                i = 0;

                if (p.isValid())
                    treat(p);
            }
    }

    /*static int test = 0;
    test++;
    if (test % 100 == 0)
    {
        test = 0;
        Remote::getSingleton()->watch(KrabiPacket::W_POSITION, 10.f, 20.f, (float)ang);
    }*/
    /*if (systick_count%10 == 0)
    {
        PositionPlusAngle p = Odometrie::odometrie->getPos();
        Remote::getSingleton()->sendWatch(KrabiPacket::W_POSITION, p.position.x, p.position.y, p.angle);
    }

    if (systick_count%10 == 2)
    {
        Remote::getSingleton()->sendWatch(KrabiPacket::W_SPEED, Odometrie::odometrie->getVitesseLineaire(), Odometrie::odometrie->getVitesseAngulaire());
    }

    if (systick_count%10 == 4)
    {
        Remote::getSingleton()->sendWatch(KrabiPacket::W_SPEED_TARGET, Asservissement::asservissement->getLinearSpeed(), Asservissement::asservissement->getAngularSpeed());
    }*/

    if (tick % 200 == 5)
    {
        KrabiPacket p(KrabiPacket::TIME_SYNC);
        p.add((uint16_t)StrategieV2::getTimeSpent());
        Remote::getSingleton()->send(p);
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
        case KrabiPacket::SET_PID_LIN:
        {
            float p = packet.get<float>();
            float i = packet.get<float>();
            float d = packet.get<float>();
            bool enabled = packet.get<bool>();
            Asservissement::asservissement->getPIDDistance().setSettings(p, i, d);
            Asservissement::asservissement->setEnabledPIDDistance(enabled);
            break;
        }
        case KrabiPacket::SET_PID_ANG:
        {
            float p = packet.get<float>();
            float i = packet.get<float>();
            float d = packet.get<float>();
            bool enabled = packet.get<bool>();
            Asservissement::asservissement->getPIDAngle().setSettings(p, i, d);
            Asservissement::asservissement->setEnabledPIDAngle(enabled);
            break;
        }
        case KrabiPacket::RUN_PID_TEST:
        {
            StrategieV2::resetTime();

            float lin = packet.get<float>();
            float ang = packet.get<float>();
            float limit = packet.get<float>();
            uint16_t duration = packet.get<uint16_t>();

            Asservissement::asservissement->runTest(duration, lin, ang, limit);

            break;
        }
        case KrabiPacket::RUN_GOTO:
        {
            float x = packet.get<float>();
            float y = packet.get<float>();
            float speed = packet.get<float>();

            /*if (speed > 0)
                StrategieV2::setCurrentGoal(Position(x, y));
            else
                StrategieV2::setCurrentGoal(Position(x, y));*/

            Asservissement::asservissement->resume();

            StrategieV2::addTemporaryAction(new ActionGoTo(Position(x, y)), true);
            break;
        }
        case KrabiPacket::STOP:
        {
            Asservissement::asservissement->stop();
            break;
        }
        case KrabiPacket::WATCH_REQUIRE_ONCE:
        {
            uint16_t w = packet.get<uint16_t>();
            sendWatch((KrabiPacket::W_TABLE)w);
            break;
        }
        case KrabiPacket::WATCH_SET:
        {
            uint16_t w = packet.get<uint16_t>();
            mWatchesEnabled[w] = true;
            break;
        }
        case KrabiPacket::WATCH_RESET:
        {
            uint16_t w = packet.get<uint16_t>();
            mWatchesEnabled[w] = false;
            break;
        }
        case KrabiPacket::WATCH_DESELECT_ALL:
        {
            for(int i(0); i < KrabiPacket::MAX_WATCHES; i++)
                mWatchesEnabled[i] = false;
            break;
        }
        case KrabiPacket::TIME_RESET:
            StrategieV2::resetTime();
            break;
    }
}

void Remote::sendWatch(KrabiPacket::W_TABLE w, int time)
{
    KrabiPacket p(time == -1 ? KrabiPacket::WATCH_VARIABLE : KrabiPacket::WATCH_VARIABLE_TIMED, w);
    if (time >= 0)
        p.add((uint32_t) time);

    switch(w)
    {
        case KrabiPacket::W_WATCHES:
        {
            for(int i(1); i < KrabiPacket::MAX_WATCHES; i++)
            {
                p.add((uint8_t) i);
                p.add(mWatchesEnabled[i]);
            }
            break;
        }
        case KrabiPacket::W_POSITION:
        {
            PositionPlusAngle pos = Odometrie::odometrie->getPos();
            p.add(pos.position.x);
            p.add(pos.position.y);
            p.add(pos.angle);
            break;
        }
        case KrabiPacket::W_SPEED:
        {
            p.add(Odometrie::odometrie->getVitesseLineaire());
            p.add(Odometrie::odometrie->getVitesseAngulaire());
            break;
        }
        case KrabiPacket::W_SPEED_TARGET:
        {
            p.add(Asservissement::asservissement->getLinearSpeed());
            p.add(Asservissement::asservissement->getAngularSpeed());
            break;
        }
        case KrabiPacket::W_ODOMETRIE:
        {
            p.add(Odometrie::odometrie->getWheelSize());
            p.add(Odometrie::odometrie->getInterAxisDistance());
            break;
        }
        case KrabiPacket::W_PID_LIN:
        {
            p.add(Asservissement::asservissement->getPIDDistance().getKp());
            p.add(Asservissement::asservissement->getPIDDistance().getKi());
            p.add(Asservissement::asservissement->getPIDDistance().getKd());
            break;
        }
        case KrabiPacket::W_PID_ANG:
        {
            p.add(Asservissement::asservissement->getPIDAngle().getKp());
            p.add(Asservissement::asservissement->getPIDAngle().getKi());
            p.add(Asservissement::asservissement->getPIDAngle().getKd());
            break;
        }
        case KrabiPacket::W_SHARPS:
        {
            for(int i(4); i < 8/*SharpSensor::END_SHARP_NAME*/; i++)
            {
                Sensor::OutputSensor out = StrategieV2::getSensors()[i]->getValue();
                p.add((uint16_t) out.f);
                p.add(out.b);
            }
            break;
        }
        default:
            return;
    }

    send(p);
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

