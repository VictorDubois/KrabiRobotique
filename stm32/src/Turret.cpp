#include "Turret.h"

Turret::~Turret()
{
    //destructeur
}

Turret* Turret::singleton = 0;

Turret* Turret::getSingleton()

{
    if (singleton==0)
        singleton = new Turret();

    return singleton;
}


Turret::Turret()
{
#ifdef ROBOTHW
    initClocksAndPortsGPIO();
    initUART(USART_BAUDRATE);

    messstat = 0;
#endif

    TurretMode = false;

}

void Turret::initClocksAndPortsGPIO()
{

#ifdef ROBOTHW

#ifdef STM32F40_41xxx // Pin pour le stm32 h405
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* Connect USART pins to AF */
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);

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

void Turret::initUART(int baudRate)
{
#ifdef ROBOTHW
    USART_InitTypeDef USART_InitStructure;

    USART_InitStructure.USART_BaudRate = baudRate;

    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(TURRET_USART_INDEX, &USART_InitStructure);

    USART_Cmd(TURRET_USART_INDEX, ENABLE);
#endif
}

//void Turret::sendData(int data)
//{
//#ifdef ROBOTHW
//    // Wait until the send buffer is cleared finishes
//    while (USART_GetFlagStatus(TURRET_USART_INDEX, USART_FLAG_TXE) == RESET);
//    USART_SendData(TURRET_USART_INDEX, (u16) data);
//#endif
//}
//
//void Turret::log(char* msg)
//{
//    int pos = 0;
//    while(msg[pos] != '\0' )
//    {
//        Turret::getSingleton()->sendData(msg[pos]);
//        pos++;
//    }
//    for(int i=0; i<10; i++)
//        Turret::getSingleton()->sendData(' ');
//}

bool Turret::dataAvailable()
{
#ifdef ROBOTHW
    return TURRET_USART_INDEX->SR & USART_FLAG_RXNE;
#else
    return false;
#endif
}

int Turret::receiveData()
{
#ifdef ROBOTHW
    while (!(TURRET_USART_INDEX->SR & USART_FLAG_RXNE));

    return ((int)(TURRET_USART_INDEX->DR & 0x1FF));
#else
    return 0;
#endif
}

int getdist(int i){
return dist[i]
}

int getang(int i){
return ang[i]
}

void Turret::update()
{
while (dataAvailable())
    {
        switch(messstat)
        {
        case 0  :
            {
                int mem = receiveData()
                if mem==250 {
                    messstat++;
                }
                if mem==255{messstat=8;}
            }
            break;
        case 1  :
            {
                angcentaine = receiveData();
                messstat++;
            }
            break;
        case 2  :
            {
                tempang=(100*angcentaine)+receiveData();
                messstat++;
            }
            break;
        case 3  :
            {
                tempdist=receiveData()();
                messstat++;
            }
            break;
        case 4  :
            if (receiveData()==255)
            {
                dis[rob]=tempdist;
                ang[rob]=tempang;
                messstat=0;
                rob= (rob+1)%3;
            }
            break;
        case 8  :
            if (receiveData()==255)
            {
                messstat=0;
                rob= 0;
            }
            break;
        }
    }
}
