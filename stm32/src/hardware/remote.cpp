#include "remote.h"

#include "leds.h"
//#include "canonLances.h"
//#include "canonFilet.h"
//#include "brak.h"
#include "brasLateraux.h"

Remote* Remote::singleton = 0;

Remote* Remote::getSingleton()
{
    if (singleton==0)
        singleton = new Remote();

    return singleton;
}


Remote::Remote()
{
#ifdef ROBOTHW
    initClocksAndPortsGPIO();
    initUART(USART_BAUDRATE);
#endif

    remoteMode = false;

    isOpenContainer = false;
    isOpenLeftArm = false;
    isOpenRightArm = false;
    timerLances = -1;

    brakInv = false;
    brakOut = false;

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
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);//Ne pas utiliser l'UART 5 TX : c'est la led de debug
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
//
//    GPIO_InitTypeDef GPIO_InitStructure;
//
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//GPIO_PuPd_NOPULL;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOC, &GPIO_InitStructure);
//
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//GPIO_PuPd_NOPULL;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOD, &GPIO_InitStructure);
//
//    /* Connect USART pins to AF */
//    GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5);
//    GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);

    //USART6, fonctionne
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
//
//    GPIO_InitTypeDef GPIO_InitStructure;
//
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//GPIO_PuPd_NOPULL;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOC, &GPIO_InitStructure);
//
//    /* Connect USART pins to AF */
//    GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);
//    GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);

    //USART 3, déjà utilisé par les AX-12
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
//
//    GPIO_InitTypeDef GPIO_InitStructure;
//
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//GPIO_PuPd_NOPULL;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOB, &GPIO_InitStructure);
//
//    /* Connect USART pins to AF */
//    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
//    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);

    //USART 2, me marche pas en réception, probablement à cause de la fonction USB (OTG) sur cette patte
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
//
//    GPIO_InitTypeDef GPIO_InitStructure;
//
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//GPIO_PuPd_NOPULL;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);
//
//    /* Connect USART pins to AF */
//    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
//    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
#endif
#ifdef STM32F10X_CL // Pin pour le stm32 h107
    //RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    // port D pin 8 TX : un servo numérique en Ecriture
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // port D pin 9 RX : un servo numérique en Lecture
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOB, &GPIO_InitStructure);

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
#endif
}

void Remote::sendData(int data)
{
#ifdef ROBOTHW
    // Wait until the send buffer is cleared finishes
    while (USART_GetFlagStatus(REMOTE_USART_INDEX, USART_FLAG_TXE) == RESET);
    USART_SendData(REMOTE_USART_INDEX, (u16) data);
#endif
}

//void Remote::sendData(KrabiPacket* packet)
//{
//    int size = packet->getLength();
//    uint8_t* data = packet->getPacket();
//    for(int i = 0; i<size; i++)
//        sendData(data[i]);

//    delete [] data;
//}

void Remote::log(char* msg)
{
    int pos = 0;
    while(msg[pos] != '\0' )
    {
        Remote::getSingleton()->sendData(msg[pos]);
        pos++;
    }
    for(int i=0; i<10; i++)
        Remote::getSingleton()->sendData(' ');
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

void Remote::update(bool allowChangeMode)
{/*
#ifdef KRABI
    if (timerLances>=0)
    {
        timerLances--;
        if (timerLances==150)
            CanonLances::getSingleton()->fire();
    }
#endif
*/
    //if (allowChangeMode)
    {
        if (dataAvailable() && !remoteMode)
        {
            remoteMode = true;
            Remote::log("Reçu, avant toute commandant !");
        }
        if (remoteMode)
            Led::setOn(1);
        else
            Led::setOff(1);
    }

    if (!allowChangeMode && remoteMode && dataAvailable())
    {
        int order = receiveData();
        Remote::log("Got:");
        Remote::getSingleton()->sendData(order);
        /*
#ifdef KRABI_JR
        switch(order)
        {
        case 1:
            if (isOpenContainer)
                Container::getSingleton()->close();
            else
                Container::getSingleton()->open();
            isOpenContainer = !isOpenContainer;
            break;
        case 2:
            if (isOpenLeftArm)
                BrasLateral::getLeft()->collapse();
            else
                BrasLateral::getLeft()->expand();
            isOpenLeftArm = !isOpenLeftArm;
            break;
        case 3:
            if (isOpenRightArm)
                BrasLateral::getRight()->collapse();
            else
                BrasLateral::getRight()->expand();
            isOpenRightArm = !isOpenRightArm;
            break;
        }
#endif
#ifdef KRABI
        switch(order)
        {
        case 1:
            CanonFilet::getSingleton()->shoot();
            break;
        case 2:
            if (timerLances<0)
            {
                CanonLances::getSingleton()->arm();
                timerLances = 300;
            }
            break;
        case 3:
            if (isOpenLeftArm)
                BrasLateral::getLeft()->collapse();
            else
                BrasLateral::getLeft()->expand();
            isOpenLeftArm = !isOpenLeftArm;
            break;
        case 4:
            if (isOpenRightArm)
                BrasLateral::getRight()->collapse();
            else
                BrasLateral::getRight()->expand();
            isOpenRightArm = !isOpenRightArm;
            break;
        case 5:
            if (!brakInv)
                Brak::getSingleton()->positionHaute();
            else
            {
                Brak::getSingleton()->positionIntermediaire();
                brakOut = false;
            }
            break;
        case 6:
            if (!brakInv)
                Brak::getSingleton()->positionBasse();
            else
            {
                Brak::getSingleton()->positionBasseRetourne();
                brakOut = true;
            }
            break;
        case 10:
            CanonLances::getSingleton()->shootAtWill();
            break;
        case 11:
            CanonLances::getSingleton()->stopShootAtWill();
            break;
        case 12:
            Brak::getSingleton()->attraperFeu();
            break;
        case 13:
            Brak::getSingleton()->relacherFeu();
            break;
        case 14:
            if (brakOut)
            {
                Brak::getSingleton()->positionIntermediaire();
                Brak::getSingleton()->orienterHaut();
                brakInv = true;
            }
            break;
        case 15:
            if (brakOut)
            {
                Brak::getSingleton()->positionIntermediaire();
                Brak::getSingleton()->orienterBas();
                brakInv = true;
            }
            break;
        }
#endif
*/
        // Linear Speed
        if (order>=0 and order<=50)
            linSpeed = ((float)(order-25)) / 25. * LINEAR_REMOTE_SPEED_LIMIT;

        // Angular Speed
        if (order>=51 and order<=101)
            angSpeed = -((float)(order-75)) / 25. * ANGULAR_REMOTE_SPEED_LIMIT;
    }
}

bool Remote::isRemoteMode()
{
    return remoteMode;
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

