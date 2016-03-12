#include "tourelle.h"

#ifndef ROBOTHW
    #include "../simul/table.h"
    #include <ctime>
#endif

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


PositionData PositionsList::get(unsigned int idx)
{
    return m_array[idx];
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

#ifndef ROBOTHW
PositionsList PositionsList::fromQList(const QList<PositionData>& list)
{
    PositionsList l;

    for(size_t i=0; i<list.size();++i)
        l.append(list[i]);
    return l;
}
#endif

  ////////////////////
 // Tourelle //
////////////////////
#ifdef ROBOTHW
void Tourelle::initClocksAndPortsGPIO(uint32_t usart_rcc_index, uint32_t usart_af, GPIO_TypeDef* GPIOx_RX, uint16_t GPIO_Pin_RX, GPIO_TypeDef* GPIOx_TX, uint16_t GPIO_Pin_TX)
{//processeur : pour faire les recherches, c'est en fait f10 pour h107, et f04 pour h405

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

    RCC_APB1PeriphClockCmd(usart_rcc_index, ENABLE);

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

}

void Tourelle::initUART(USART_TypeDef* usart_index, int baudRate)
{
    USART_InitTypeDef USART_InitStructure;

    USART_InitStructure.USART_BaudRate = baudRate;

    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(usart_index, &USART_InitStructure);

    USART_Cmd(usart_index, ENABLE);

}
#endif

Tourelle* Tourelle::getSingleton()
{
    static Tourelle* ptr = NULL;
	if(ptr == NULL)
		ptr = new Tourelle();
	return ptr;
}


Tourelle::Tourelle()
{
#ifdef ROBOTHW
#ifdef STM32F10X_CL //h107
    initClocksAndPortsGPIO(RCC_APB1Periph_USART2, GPIO_Remap_USART2, GPIOD, GPIO_Pin_6, GPIOD, GPIO_Pin_5);
    initUART(TURRET_USART_INDEX, USART_BAUDRATE);
#endif
#ifdef STM32F40_41xxx // For stm32 h405

#endif

#endif
}


void Tourelle::reset()
{
	m_currentList.copyTo(m_closedList);
	m_currentList.clear();
}


unsigned int Tourelle::beaconsDetected()
{
#ifdef ROBOTHW
	return m_closedList.size();
#else
    return Table::getMainInstance()->getBeaconsRelativePosition().size();
#endif
}

#ifndef ROBOTHW
int alea(int mi, int ma)
{
    if(ma == mi)
        return mi;

    if(mi > ma)
    {
        int t = ma;
        ma = mi;
        mi = t;
    }

    static bool ini = false;
    if(!ini)
    {
        srand(time(0));
        ini = true;
    }
    return rand()%(ma-mi+1)+mi;
}
#endif


PositionData Tourelle::getPositionData(unsigned int idx)
{
#ifdef ROBOTHW
	return m_closedList.get(idx);
#else
    PositionData pos = Table::getMainInstance()->getBeaconsRelativePosition()[idx];
    pos.angle += alea(-TURRET_TEST_MAX_ANGLE_DEV, +TURRET_TEST_MAX_ANGLE_DEV);
    pos.distance += alea(-TURRET_TEST_MAX_LIN_DEV, +TURRET_TEST_MAX_LIN_DEV);
    return pos;
#endif
}

PositionsList Tourelle::getPositionsList() const
{
#ifdef ROBOTHW
	return m_closedList;
#else
    PositionsList l = PositionsList::fromQList(Table::getMainInstance()->getBeaconsRelativePosition());
    for(size_t i = 0; i < l.size(); ++i)
    {
        l[i].angle += alea(-TURRET_TEST_MAX_ANGLE_DEV, +TURRET_TEST_MAX_ANGLE_DEV);
        l[i].distance += alea(-TURRET_TEST_MAX_LIN_DEV, +TURRET_TEST_MAX_LIN_DEV);
    }

    return l;
#endif
}

bool Tourelle::dataAvailable()
{
#ifdef ROBOTHW
    return TURRET_USART_INDEX->SR & USART_FLAG_RXNE;
#else
    return false;
#endif
}

unsigned int Tourelle::receiveData()
{
#ifdef ROBOTHW
    while (!(TURRET_USART_INDEX->SR & USART_FLAG_RXNE));

    return ((unsigned int)(TURRET_USART_INDEX->DR & 0x1FF));
#else
    return 0;
#endif
}



void Tourelle::update()
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




