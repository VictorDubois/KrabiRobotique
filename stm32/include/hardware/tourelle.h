#ifndef GUARD_DISTANCESENSOR
#define GUARD_DISTANCESENSOR

//RobotTHW has to be defined for the class to be active, else it will only send void results, for testing purpose of a robot in a simulator, without the sensors

#ifdef STM32F40_41xxx // for H405
    #include "stm32f4xx_rcc.h"
    #include "stm32f4xx_gpio.h"
    #include "stm32f4xx_usart.h"
    #define TURRET_USART_INDEX USART2//UART5//USART6//USART3

#elif defined(STM32F10X_MD) || defined(STM32F10X_CL) // for H107
    #include "stm32f10x_rcc.h"
    #include "stm32f10x_gpio.h"
    #include "stm32f10x_usart.h"
    #define TURRET_USART_INDEX USART1 //UART5 //USART2
#endif



// PositionData //
/* Description: represents a position in 2D polar coordinates */
struct PositionData
{
	unsigned long angle;
	unsigned int distance;
};

class PositionsList
{
	public:
		// Constructor
		PositionsList();
		// Copy constructor (O(n))
		PositionsList(const PositionsList&);

		// Append element to the set (O(1) amortized).
		void append(const PositionData& element);

		// Returns the size of the data set
		unsigned int size() const;

		// Access to i-ist element in the set (O(1)). Warning: there are no bound checks
		PositionData& operator[](unsigned int i);
		const PositionData& operator[](unsigned int i) const;

		PositionData get(unsigned int idx);

		// Clear the data set (O(1)). Does not actually free the memory.
		void clear();

		// Swap two PositionsList with as little copies as possible (O(1))
		void copyTo(PositionsList&);

	private:
		// Resize the internal buffer (O(i+n))
		void reserve(unsigned int i);

		// Buffer
		PositionData* 	m_array;
		// Buffer size
		unsigned int 	m_allocatedSize;
		// Actual size of the data set
		unsigned int 	m_usedSize;
};






// DistanceSensor //
/* Description: this class manage the distance sensor. As a singleton, it can only be invoqued through DistanceSensor::getSingleton()
It allows access to the position of the beacons detected during its last revolution. */
class DistanceSensor
{
	public:
		// Public methods //

		// Get the singleton instance
		static DistanceSensor* getSingleton();
        //Updates the data in the variables with those in the Serial buffer//
        void update();
		// Returns a particular 'ping'. idx must be stricly inferior to the amount of beacons detected
		PositionData 	getPositionData(unsigned int idx);
		// Returns all 'pings'
		PositionsList 	getPositionsList() const;
		// Returns the amount of beacons detected
		unsigned int 	beaconsDetected();

        bool dataAvailable();

	private:
		/// Private methods ///
		// Private constructor
		DistanceSensor();

		//Initializes Serial Communication//
		/** initialize the gpio pins TX & RX for the usart, set the remap/alternate function and the associated clock
		* - for the H107 : the af argument corresponds to the remap
		* - for the H405 : the af argument corresponds to the alternate function
		*/
        void initClocksAndPortsGPIO(uint32_t usart_rcc_index, uint32_t usart_af, GPIO_TypeDef* GPIOx_RX, uint16_t GPIO_Pin_RX, GPIO_TypeDef* GPIOx_TX, uint16_t GPIO_Pin_TX);

        // initializes the given usart (usart_index) at baudrate
        void initUART(USART_TypeDef* usart_index, int baudRate);

		// Internal call when the sensor has completed a revolution
		void reset();

		// Internal call when the microprocessor has received data from the sensor
		unsigned int receiveData();


		/// Private attributes ///
		// 'pings' from the last revolution
		PositionsList m_closedList;
		// 'pings' from the current revolution (incomplete list)
		PositionsList m_currentList;
		//Temporary Variables used during a cycle//
		unsigned int angstr, tempdist;
		unsigned long tempang;

        //Current status of the receiving protocol//
        int stat;
};

#endif
