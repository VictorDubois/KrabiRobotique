#include "interfaceServosNumeriques.h"
//#include "stm32f4xx_usart.h"

void ServosNumeriques_sendData(int data)
{
    // Wait until the send buffer is cleared finishes
    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
    USART_SendData(USART3, (u16) data);
}

namespace ServosNumeriques
{

void initClocksAndPortsGPIO()
{
#ifdef STM32F40_41xxx // Pin pour le stm32 h405
    // bus APB1 : allow usart 3
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

    // on remap l'usart3 pour que le stm soit bien configuré sur les ports 10 et 11 du GPIOC, et le sens sur le par 5 du GPIOB
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);
    //GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
 	// port C pin 10 TX : un servo numérique en Ecriture
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    #ifdef STM32F40_41xxx
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;// the pins are configured as alternate function so the USART peripheral has access to them
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;// this defines the output type as push pull mode (as opposed to open drain)
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;// this activates the pullup resistors on the IO pins
    #elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    #endif
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOC, &GPIO_InitStructure);

 	// port C pin 11 RX : un servo numérique en Lecture
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOC, &GPIO_InitStructure);

 	// port B pin 5 : la direction (TX/RX)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    #ifdef STM32F40_41xxx
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    #elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    #endif
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOB, &GPIO_InitStructure);

#endif
#ifdef STM32F10X_MD // Pin pour le stm32 h103
    // bus APB1 : allow usart 3
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

    // on remap l'usart3 pour que le stm soit bien configuré sur les ports 10 et 11 du GPIOC, et le sens sur le par 5 du GPIOB
    GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
 	// port C pin 10 TX : un servo numérique en Ecriture
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOC, &GPIO_InitStructure);

 	// port C pin 11 RX : un servo numérique en Lecture
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOC, &GPIO_InitStructure);

 	// port B pin 5 : la direction (TX/RX)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOB, &GPIO_InitStructure);
#endif
#ifdef STM32F10X_CL // Pin pour le stm32 h107
    // bus APB1 : allow usart 3
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

    // on remap l'usart3 pour que le stm soit bien configuré sur les ports 8 9 et 10 du GPIOD
    GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
 	// port D pin 8 TX : un servo numérique en Ecriture
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOD, &GPIO_InitStructure);

 	// port D pin 9 RX : un servo numérique en Lecture
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOD, &GPIO_InitStructure);

 	// port D pin 10 : la direction (TX/RX)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOD, &GPIO_InitStructure);
#endif


}

void initUART(int baudRate)
{
    USART_InitTypeDef USART_InitStruct;
	// Protocole ax12 : Half duplex Asynchronous Serial Communication (8bit,1stop,No Parity)
 	/* Initialisation des caracteristiques USART_InitStruct */
 	USART_InitStruct.USART_BaudRate = baudRate;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No ;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	/* On configure et on lance */
	USART_Init(USART3, &USART_InitStruct);
	//USART_ClockInit(USART3, &USART_ClockInitStruct);
	USART_Cmd(USART3, ENABLE);
}

void sendMode()
{
	// on veut envoyer des paquets, on met le bit d'envoi à 1
	#ifdef STM32F10X_CL
	GPIO_WriteBit(GPIOD, GPIO_Pin_10, Bit_SET);
	#elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
	GPIO_WriteBit(GPIOB, GPIO_Pin_5, Bit_SET);
	#endif
}
void receiveMode()
{
	// on veut recevoir des paquets, on met le bit d'envoi à 0
	#ifdef STM32F10X_CL
	GPIO_WriteBit(GPIOD, GPIO_Pin_10, Bit_RESET);
	#elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
	GPIO_WriteBit(GPIOB, GPIO_Pin_5, Bit_SET);
	#endif
}

void sendData(int data)
{
    // Wait until the send buffer is cleared finishes
    while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
    USART_SendData(USART3, (u16) data);
}

int receiveData()
{
    while (!(USART3->SR & USART_FLAG_RXNE));

    return ((int)(USART3->DR & 0x1FF));
}

int receiveStatusPacket(int* tableau)
{
    int msg = receiveData();
    int i = 0;
    while(msg == 0) {
        msg = receiveData();
    } // on attend de lire quelque chose
    if (msg == 0xff) { // début fanion
        msg = receiveData();
        if (msg == 0xff) { // fin fanion
            tableau[i++] = receiveData(); // on lit quel servo a envoyé le msg
            tableau[i++] = receiveData(); // on lit la taille du message
            for (int i = 2; i < tableau[1]+2; i++) {
                tableau[i] = receiveData();
            }
            // on a tout lu : check la checksum
            unsigned int sum = 0;
            for (int i = 0; i < tableau[1]+2; i++) {
                sum += tableau[i];
            }
            if ((int16_t)~(sum) != tableau[tableau[1]+1])
                return -1;
            return 0;
        }
    }
    return 1;
}

void moveToAtSpeed(uint16_t position, uint16_t vitesse, uint8_t servo)
{
    int packet[16];
    int packetLength = AX12::getMoveInstruction(packet, position, vitesse, servo);
    for (int i = 0; i < packetLength; i++) {
        sendData(packet[i]);
    }
}
void moveTo(uint16_t position, uint8_t servo)
{
    int packet[16];
    int packetLength = AX12::getMoveToInstruction(packet, position, servo);
    for (int i = 0; i < packetLength; i++) {
        sendData(packet[i]);
    }
}
void moveAtSpeed(uint16_t vitesse, uint8_t servo, bool sensTrigoSiContinue)
{
    int packet[16];
    //Si rotation continue : de 0 à 1023 dans un sens, de 1024 à 2047 dans l'autre
    int packetLength = AX12::getMoveSpeedInstruction(packet, vitesse + 1024 * ((uint8_t) sensTrigoSiContinue), servo);//TODO : checker qu'on est bien en rotation continue si sensTrigoSiContinue == true;
    for (int i = 0; i < packetLength; i++) {
        sendData(packet[i]);
    }
}

void setLedState(uint8_t ledOn, uint8_t servo)
{
    int packet[16];
    int packetLength = AX12::getLedInstruction(packet, ledOn, servo);
    for (int i = 0; i < packetLength; i++) {
        sendData(packet[i]);
    }
}

void setMinimumAngle(uint16_t angle, uint8_t servo)
{
    int packet[16];
    int packetLength = AX12::getAngleLowerLimitInstruction(packet, angle, servo);
    for (int i = 0; i < packetLength; i++) {
        sendData(packet[i]);
    }
}

void setMaximumAngle(uint16_t angle, uint8_t servo)
{
    int packet[16];
    int packetLength = AX12::getAngleUpperLimitInstruction(packet, angle, servo);
    for (int i = 0; i < packetLength; i++) {
        sendData(packet[i]);
    }
}
void setBaudRate(uint8_t baudRate, uint8_t servo)
{
    int packet[16];
    int packetLength = AX12::getBaudRateInstruction(packet, baudRate, servo);
    for (int i = 0; i < packetLength; i++) {
        sendData(packet[i]);
    }
}


void setTorqueLimite(uint16_t torque, uint8_t servo) // dans la RAM
{
    int packet[16];
    int packetLength = AX12::getTorqueLimitInstruction(packet, torque, servo);
    for (int i = 0; i < packetLength; i++) {
        sendData(packet[i]);
    }
}
void setMaxTorque(uint16_t torque, uint8_t servo) // EEPROM, automatiquement mis dans la RAM au démarrage
{
    int packet[16];
    int packetLength = AX12::getMaxTorqueInstruction(packet, torque, servo);
    for (int i = 0; i < packetLength; i++) {
        sendData(packet[i]);
    }
}

void changeContinuousRotationMode(uint8_t servo, bool continuous, uint8_t step)
{
    if(continuous)
    {
        //On set les angles min et max à 0, et la position goal à 0
        switch(step)
        {
            case 1:
                setMinimumAngle(0, servo);
                break;

            case 2:
                setMaximumAngle(0, servo);
                break;

            case 3:
                moveTo(0, servo);
                break;

            default:
                setMinimumAngle(0, servo);
                for(int i = 0 ; i < 100000 ; i++){}//@TODO : trouver le temps minimum qui marche encore à coup sûr
                setMaximumAngle(0, servo);
                for(int i = 0 ; i < 100000 ; i++){}
                moveTo(0, servo);
                for(int i = 0 ; i < 100000 ; i++){}
        }
    }
    else
    {
        //On remet les valeurs par défaut
        switch(step)
        {
            case 1:
                setMinimumAngle(0, servo);
                break;

            case 2:
                setMaximumAngle(0, servo);
                break;

            case 3:
                moveTo(0, servo);
                break;

            default:
                setMinimumAngle(0, servo);
                for(int i = 0 ; i < 100000 ; i++){}
                setMaximumAngle(1023, servo);
                for(int i = 0 ; i < 100000 ; i++){}
                moveAtSpeed(0, servo);
                for(int i = 0 ; i < 100000 ; i++){}
        }
    }
}
int getPosition(uint8_t servo)
{
    int packet[16];
    int packetLength = 8;
    AX12::receivePositionInformation(packet, servo);
    for (int i = 0; i < packetLength; i++)
    {
        sendData(packet[i]);
    }

    ServosNumeriques::receiveMode();
    int packetReceived[16];
    receiveStatusPacket(packetReceived);
    ServosNumeriques::sendMode();
    uint16_t position = 0;

    if(packetReceived[0] == servo)
    {
        position = packetReceived[3] + (packetReceived[4] << 8);
    }
    return (int) position;
}
}
