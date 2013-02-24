#ifndef INTERFACE_SERVOS_NUMERIQUES_H_INCLUDED
#define INTERFACE_SERVOS_NUMERIQUES_H_INCLUDED

#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"

void initGPIO()
{
 	// port D pin 8 : un servo numérique en réception
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOD, &GPIO_InitStructure);

 	// port D pin 9 : un servo numérique
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOD, &GPIO_InitStructure);

 	// port D pin 10 : la direction (TX/RX)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void initRCC()
{
	RCC_APB2PeriphResetCmd(RCC_APB1Periph_USART3, ENABLE); 
}

void initUART(USART_InitTypeDef* USART_InitStruct, USART_ClockInitTypeDef* USART_ClockInitStruct)
{
	// Protocole ax12 : Half duplex Asynchronous Serial Communication (8bit,1stop,No Parity) 
 	/* Initialisation des caracteristiques USART_InitStruct */
 	USART_InitStruct->USART_BaudRate = 0xF4240; /* 1000000 Baud */
	USART_InitStruct->USART_WordLength = USART_WordLength_8b;
	USART_InitStruct->USART_StopBits = USART_StopBits_1;
	USART_InitStruct->USART_Parity = USART_Parity_No ;
	USART_InitStruct->USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct->USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_ClockInitStruct->USART_Clock = USART_Clock_Disable;
	USART_ClockInitStruct->USART_CPOL = USART_CPOL_Low;
	USART_ClockInitStruct->USART_CPHA = USART_CPHA_1Edge;
	USART_ClockInitStruct->USART_LastBit = USART_LastBit_Disable;

	/* On configure et on lance */ 
	USART_Init(USART1, &USART_InitStructure);
	USART_ClockInit(USART1, &USART_ClockInitStructure);
	USART_Cmd(USART1, ENABLE);
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

void sendData(int8_t data)
{
  /* Transmit the character using USART1 */
  USART_SendData(USART1, data);

  /* Wait until transmit finishes */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}




#endif
