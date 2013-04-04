#include "interfaceServosNumeriques.h"

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
    // bus APB1 : allow usart 3
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

    // on remap l'usart3 pour que le stm soit bien configuré sur les ports 8 9 et 10 du GPIOD
    GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
 	// port D pin 8 TX : un servo numérique en Ecriture
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOD, &GPIO_InitStructure);

 	// port D pin 9 RX : un servo numérique en Lecture
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOD, &GPIO_InitStructure);

 	// port D pin 10 : la direction (TX/RX)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOD, &GPIO_InitStructure);

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
	GPIO_WriteBit(GPIOD, GPIO_Pin_10, Bit_SET);
}
void receiveMode()
{
	// on veut recevoir des paquets, on met le bit d'envoi à 0
	GPIO_WriteBit(GPIOD, GPIO_Pin_10, Bit_RESET);
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
void moveAtSpeed(uint16_t vitesse, uint8_t servo)
{
    int packet[16];
    int packetLength = AX12::getMoveSpeedInstruction(packet, vitesse, servo);
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


}
