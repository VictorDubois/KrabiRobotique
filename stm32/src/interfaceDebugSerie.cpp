#include "interfaceDebugSerie.h"
//#include "stm32f4xx_usart.h"


#if defined(STM32F40_41xxx) || defined(STM32F10X_MD) // uart pour le stm32 h405 ou h103
#define UART_DEBUG USART2_BASE
#endif
#ifdef STM32F10X_CL // uart pour le stm32 h107
#define UART_DEBUG UART4_BASE
#endif

namespace UartDebug
{


void initClocksAndPortsGPIO()
{
#if defined(STM32F40_41xxx) || defined(STM32F10X_MD) // pin pour le stm32 h405 ou h103
    // bus APB1 : allow usart 2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);



    GPIO_InitTypeDef GPIO_InitStructure;
 	// port A pin 2 TX : du stm vers l'extérieur
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    #ifdef STM32F40_41xxx
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    #elif defined(STM32F10X_MD) || defined(STM32F10X_CL)
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    #endif
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOA, &GPIO_InitStructure);

 	// port A pin 3 RX : vers le stm
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOA, &GPIO_InitStructure);

#endif
#ifdef STM32F10X_CL // Pin pour le stm32 h107
    // bus APB1 : allow uart 4
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

    // on remap pas l'usrt4 pour que le stm soit bien configuré sur les ports 10 et 11 du GPIOC
    //GPIO_PinRemapConfig(GPIO_FullRemap_UART4, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
 	// port C pin 10 TX
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOC, &GPIO_InitStructure);

 	// port C pin 11 RX
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // La vitesse de rafraichissement du port
    GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif


}

void init(int baudRate)
{
    USART_InitTypeDef USART_InitStruct;
 	/* Initialisation des caracteristiques USART_InitStruct */
 	USART_InitStruct.USART_BaudRate = baudRate;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No ;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	/* On configure et on lance */
	USART_Init((USART_TypeDef *) UART_DEBUG, &USART_InitStruct);
	//USART_ClockInit(USART3, &USART_ClockInitStruct);
	USART_Cmd((USART_TypeDef *) UART_DEBUG, ENABLE);

    #ifdef STM32F40_41xxx
        GPIO_PinAFConfig(GPIOA, GPIO_Pin_2, GPIO_AF_USART2);
        GPIO_PinAFConfig(GPIOA, GPIO_Pin_3, GPIO_AF_USART2);
    #endif
}

void sendData(int data)
{
    // Wait until the send buffer is cleared finishes
    while (USART_GetFlagStatus((USART_TypeDef *) UART_DEBUG, USART_FLAG_TXE) == RESET);
    USART_SendData((USART_TypeDef *) UART_DEBUG, (u16) data);
}

int receiveData()//USART_TypeDef * uart)
{
    while (!(((USART_TypeDef *) UART_DEBUG)->SR & USART_FLAG_RXNE));

    return ((int)(((USART_TypeDef *) UART_DEBUG)->DR & 0x1FF));
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
}


