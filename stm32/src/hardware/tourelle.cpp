#include "tourelle.h"
#include <string.h>
#define min(a,b) a<b?a:b;


#define USART_BAUDRATE 9600

#define STAT_OUT 0
#define STAT_INMAIN 1
#define STAT_DIST 2
#define STAT_ANGHUND 3
#define STAT_ANG 4
  ///////////////////
 // PositionsList //
///////////////////

PositionsList::PositionsList():m_usedSize(0),m_allocatedSize(0),m_array(0)
{
	reserve(5);
}

PositionsList::PositionsList(const PositionsList& l):m_usedSize(0),m_allocatedSize(0),m_array(0)
{
	reserve(l.m_allocatedSize);
	m_usedSize=l.m_usedSize;
	memcpy(m_array,l.m_array,m_usedSize);
}

void PositionsList::reserve(unsigned int i)
{
	PositionData* ptr = new PositionData[i];

	memset(ptr, 0, i*sizeof(PositionData));

	m_usedSize = min(m_usedSize, i);
	m_allocatedSize=i;

	memcpy(ptr, m_array, m_usedSize*sizeof(PositionData));

	delete m_array;
	m_array = ptr;
}

void PositionsList::append(const PositionData& element)
{
	if(m_usedSize == m_allocatedSize)
		reserve((m_allocatedSize+2)*2);
    m_array[m_usedSize]=element;
    m_usedSize++;
}

unsigned int PositionsList::size() const
{
	return m_usedSize;
}

void PositionsList::clear()
{
	m_usedSize=0;
}

void PositionsList::copyTo(PositionsList& l)
{
	unsigned int us		= l.m_usedSize;
	l.m_usedSize		= m_usedSize;
	m_usedSize			= us;

	unsigned int as		= l.m_allocatedSize;
	l.m_allocatedSize	= m_allocatedSize;
	m_allocatedSize		= as;

	PositionData* ar	= l.m_array;
	l.m_array			= m_array;
	m_array				= ar;
}

PositionData& PositionsList::operator[](unsigned int i)
{
	return m_array[i];
}

const PositionData& PositionsList::operator[](unsigned int i) const
{
	return (*this)[i];
}

  ////////////////////
 // DistanceSensor //
////////////////////

void DistanceSensor::initClocksAndPortsGPIO(uint32_t usart_rcc_index, uint32_t usart_af, GPIO_TypeDef* GPIOx_RX, uint16_t GPIO_Pin_RX, GPIO_TypeDef* GPIOx_TX, uint16_t GPIO_Pin_TX)
{

#ifdef ROBOTHW

#ifdef STM32F40_41xxx // For stm32 h405
    RCC_APB1PeriphClockCmd(usart_rcc_index, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_TX;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOx_TX, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_RX;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOx_RX, &GPIO_InitStructure);

    /* Connect USART pins to AF */
    GPIO_PinAFConfig(GPIOx_RX, GPIO_Pin_RX, usart_af);
    GPIO_PinAFConfig(GPIOx_TX, GPIO_Pin_TX, usart_af);
#endif

#ifdef STM32F10X_CL // For stm32 h107

    RCC_APB2PeriphClockCmd(usart_rcc_index, ENABLE);

    GPIO_PinRemapConfig(usart_af, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    // pin TX :
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_TX;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // port's refresh rate
    GPIO_Init(GPIOx_TX, &GPIO_InitStructure);

    // pin RX :
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_RX;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // port's refresh rate
    GPIO_Init(GPIOx_RX, &GPIO_InitStructure);
#endif
#endif
}

void DistanceSensor::initUART(USART_TypeDef* usart_index, int baudRate)
{
#ifdef ROBOTHW
    USART_InitTypeDef USART_InitStructure;

    USART_InitStructure.USART_BaudRate = baudRate;

    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(usart_index, &USART_InitStructure);

    USART_Cmd(usart_index, ENABLE);
#endif
}

DistanceSensor* DistanceSensor::getSingleton()
{
    static DistanceSensor* ptr = NULL;
	if(ptr == NULL)
		ptr = new DistanceSensor();
	return ptr;
}


DistanceSensor::DistanceSensor()
{
#ifdef ROBOTHW
    initClocksAndPortsGPIO(RCC_APB1Periph_USART2, GPIO_Remap_USART2, GPIOC, GPIO_Pin_12, GPIOD, GPIO_Pin_2);
    initUART(TURRET_USART_INDEX, USART_BAUDRATE);
#endif
}


void DistanceSensor::reset()
{
	m_currentList.copyTo(m_closedList);
	m_currentList.clear();
}


unsigned int DistanceSensor::beaconsDetected()
{
	return m_closedList.size();
}

PositionData DistanceSensor::getPositionData(unsigned int idx)
{
	return m_closedList.get(idx);
}

PositionData PositionsList::get(unsigned int idx)
{
    return m_array[idx];
}

PositionsList DistanceSensor::getPositionsList() const
{
	return m_closedList;
}

bool DistanceSensor::dataAvailable()
{
#ifdef ROBOTHW
    return TURRET_USART_INDEX->SR & USART_FLAG_RXNE;
#else
    return false;
#endif
}

unsigned int DistanceSensor::receiveData()
{
#ifdef ROBOTHW
    while (!(TURRET_USART_INDEX->SR & USART_FLAG_RXNE));

    return ((unsigned int)(TURRET_USART_INDEX->DR & 0x1FF));
#else
    return 0;
#endif
}



void DistanceSensor::update()
{
    while (dataAvailable())
    {
        switch(stat)
        {
            case STAT_OUT  :
            {
                unsigned int mem = receiveData();
                if (mem==250)
                {
                    stat++;
                }
                else
                {
                    if (mem==254)
                        reset();
                }
            }
            break;
            case STAT_INMAIN  :
            {
                tempdist=receiveData();
                stat++;
            }
            break;
            case STAT_DIST  :
            {
                angstr = receiveData();
                stat++;
            }
            break;
            case STAT_ANGHUND :
            {
                tempang=(256*angstr)+receiveData();
                stat++;
            }
            break;
            case STAT_ANG :
            if (receiveData()==255)
            {
                PositionData dat;
                dat.distance=tempdist;
                dat.angle=tempang;
                m_currentList.append(dat);
                stat=STAT_OUT;
            }
            else
            {
                stat=STAT_OUT;
            }
            break;

            default:
                m_currentList.clear();
        }
    }
}




