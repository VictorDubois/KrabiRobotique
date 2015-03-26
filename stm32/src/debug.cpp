#include "debug.h"
//#include "krabipacket.h"

// DMA
#define ADC3_DR_ADDRESS     ((uint32_t)0x4001224C)

void Debug::run()
{
    // test run
}

void Debug::testServoAnalog()
{
    Timer* timer1 = new Timer(TIM1, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);

    Servo* servo1 = new Servo(timer1, 1, 0.01f, 0.11f);
    Servo* servo2 = new Servo(timer1, 2, 0.01f, 0.11f);
    Servo* servo3 = new Servo(timer1, 3, 0.01f, 0.11f);
    Servo* servo4 = new Servo(timer1, 4, 0.01f, 0.11f);

    for(int i=0; i<2000; i++)
    {
        servo1->goToAngle(70);
        /*servo2->goToAngle(BALAI_G_CLOSED);
        servo3->goToAngle(BALAI_G_CLOSED);
        servo4->goToAngle(BALAI_G_CLOSED);*/
        allumerLED();

        for(int j=0; j<10000000; j++);

        servo1->goToAngle(165);
        /*servo2->goToAngle(BALAI_G_OPEN);
        servo3->goToAngle(BALAI_G_OPEN);
        servo4->goToAngle(BALAI_G_OPEN);*/
        eteindreLED();

        for(int j=0; j<10000000; j++);
    }
}

/**
    @brief Read the PC0 pin
*/
void Debug::testADCSampleF4()
{
    __ADCSampleF4_adc_configure();//Start configuration

    int convertedValue = -1;
    while(true)
    {
        convertedValue = __ADCSampleF4_adc_convert();//Read the ADC converted value
    }
}

void Debug::__ADCSampleF4_adc_configure()
{
#if defined(STM32F40_41xxx)
    ADC_InitTypeDef ADC_init_structure; //Structure for adc confguration
    GPIO_InitTypeDef GPIO_initStructre; //Structure for analog input pin
    //Clock configuration
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//The ADC1 is connected the APB2 peripheral bus thus we will use its clock source
    RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_GPIOCEN,ENABLE);//Clock for the ADC port!! Do not forget about this one ;)
    //Analog pin configuration
    GPIO_initStructre.GPIO_Pin = GPIO_Pin_0;//The channel 10 is connected to PC0
    GPIO_initStructre.GPIO_Mode = GPIO_Mode_AN; //The PC0 pin is configured in analog mode
    GPIO_initStructre.GPIO_PuPd = GPIO_PuPd_NOPULL; //We don't need any pull up or pull down
    GPIO_Init(GPIOC,&GPIO_initStructre);//Affecting the port with the initialization structure configuration
    //ADC structure configuration
    ADC_DeInit();
    ADC_init_structure.ADC_DataAlign = ADC_DataAlign_Right;//data converted will be shifted to right
    ADC_init_structure.ADC_Resolution = ADC_Resolution_12b;//Input voltage is converted into a 12bit number giving a maximum value of 4096
    ADC_init_structure.ADC_ContinuousConvMode = ENABLE; //the conversion is continuous, the input data is converted more than once
    ADC_init_structure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;// conversion is synchronous with TIM1 and CC1 (actually I'm not sure about this one :/)
    ADC_init_structure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//no trigger for conversion
    ADC_init_structure.ADC_NbrOfConversion = 1;//I think this one is clear :p
    ADC_init_structure.ADC_ScanConvMode = DISABLE;//The scan is configured in one channel
    ADC_Init(ADC1,&ADC_init_structure);//Initialize ADC with the previous configuration
    //Enable ADC conversion
    ADC_Cmd(ADC1,ENABLE);
    //Select the channel to be read from
    ADC_RegularChannelConfig(ADC1,ADC_Channel_10,1,ADC_SampleTime_144Cycles);
#endif
}

int Debug::__ADCSampleF4_adc_convert(){
#if defined(STM32F40_41xxx)
    ADC_SoftwareStartConv(ADC1);//Start the conversion
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));//Processing the conversion
    return ADC_GetConversionValue(ADC1); //Return the converted data
#endif
}

void Debug::testSharps()
{
    /*
    Sensors* sensors = new Sensors();
    SharpSensor** sharps = sensors->getSharpSensorsList();

    float values[10] = {0};
    while(1)
    {
        AnalogSensor::startConversion();
        //allumerLED2();
        for (int i = 0; i < 8; i++)
            sharps[i]->updateValue();
        for (int i = 0; i < 8; i++)
            values[i] = sharps[i]->getValue().f;


        / *bool allume = false;
        for (int i = 0; i < 10; i++)
        {
            if (sharps[i]->getValue().b)
            {
                allume = true;
            }
        }
        if (allume) {
            allumerLED();
        }
        else {
            eteindreLED();
        }
        for (int i = 0; i < 1000; i++)
        {
        }
        eteindreLED2();
        for (int i = 0; i < 1000; i++)
        {
        }*/
  //  }

}


//__IO uint32_t ADC3ConvertedValue[4];
__IO uint16_t ADC3ConvertedValueN = 0;

void Debug::testADC_DMASampleF4()
{
#if defined(STM32F40_41xxx)
    __ADC_DMASampleF4_init();//Start configuration

    ADC_SoftwareStartConv(ADC3);

    uint32_t convertedValue = -1;
    while(true)
    {
        convertedValue = ADC3ConvertedValueN;//Read the ADC converted value
    }
#endif
}

void Debug::__ADC_DMASampleF4_init(void)
{
#if defined(STM32F40_41xxx)
    /*ADC_InitTypeDef       ADC_InitStructure;
    ADC_CommonInitTypeDef ADC_CommonInitStructure;
    DMA_InitTypeDef       DMA_InitStructure;
    GPIO_InitTypeDef      GPIO_InitStructure;

    // Enable ADC3, DMA2 and GPIO clocks ****************************************
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 | RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);

    // DMA2 Stream0 channel0 configuration **************************************
    DMA_DeInit(DMA2_Stream0);
    DMA_InitStructure.DMA_Channel = DMA_Channel_2;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(ADC1->DR);//(uint32_t)ADC3_DR_ADDRESS;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&ADC3ConvertedValue[0];
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_BufferSize = 4;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; // orig dis
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //orig dis
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(DMA2_Stream0, &DMA_InitStructure);
    DMA_Cmd(DMA2_Stream0, ENABLE);

    // Configure ADC3 Channel12 pin as analog input ******************************
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    // ADC Common Init **********************************************************
    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; // Orig dis
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
    ADC_CommonInit(&ADC_CommonInitStructure);

    // ADC3 Init ****************************************************************
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE; //orig disable
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfConversion = 4;
    ADC_Init(ADC3, &ADC_InitStructure);

    // ADC3 regular channel12 configuration *************************************
    ADC_RegularChannelConfig(ADC3, ADC_Channel_11, 1, ADC_SampleTime_15Cycles);
    ADC_RegularChannelConfig(ADC3, ADC_Channel_12, 2, ADC_SampleTime_15Cycles);
    ADC_RegularChannelConfig(ADC3, ADC_Channel_14, 3, ADC_SampleTime_15Cycles);
    ADC_RegularChannelConfig(ADC3, ADC_Channel_15, 4, ADC_SampleTime_15Cycles);

    // Enable DMA request after last transfer (Single-ADC mode) *
    ADC_DMARequestAfterLastTransferCmd(ADC3, ENABLE);

    // Enable ADC3 DMA *
    ADC_DMACmd(ADC3, ENABLE);

    // Enable ADC3 *
    ADC_Cmd(ADC3, ENABLE);*/

    /******************************************************************************/
/*               ADCs interface clock, pin and DMA configuration              */
/******************************************************************************/

    ADC_InitTypeDef       ADC_InitStructure;
    ADC_CommonInitTypeDef ADC_CommonInitStructure;
    DMA_InitTypeDef       DMA_InitStructure;
    GPIO_InitTypeDef      GPIO_InitStructure;

    /* Enable ADC3, DMA2 and GPIO clocks ****************************************/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 | RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);

    /* DMA2 Stream0 channel0 configuration **************************************/
    DMA_InitStructure.DMA_Channel = DMA_Channel_2;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)0x4001224C;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&ADC3ConvertedValueN;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_BufferSize = 1;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(DMA2_Stream0, &DMA_InitStructure);
    DMA_Cmd(DMA2_Stream0, ENABLE);

    /* Configure ADC3 Channel12 pin as analog input ******************************/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* ADC Common Init **********************************************************/
    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
    ADC_CommonInit(&ADC_CommonInitStructure);

    /* ADC3 Init ****************************************************************/
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfConversion = 1;
    ADC_Init(ADC3, &ADC_InitStructure);

    /* ADC3 regular channel12 configuration *************************************/
    ADC_RegularChannelConfig(ADC3, ADC_Channel_12, 1, ADC_SampleTime_3Cycles);

    /* Enable DMA request after last transfer (Single-ADC mode) */
    ADC_DMARequestAfterLastTransferCmd(ADC3, ENABLE);

    /* Enable ADC3 DMA */
    ADC_DMACmd(ADC3, ENABLE);

    /* Enable ADC3 */
    ADC_Cmd(ADC3, ENABLE);
#endif
}

void Debug::testQuadrature(QuadratureCoderHandler* rcg, QuadratureCoderHandler* rcd)
{
    long r = 0, l = 0;
    while(true)
    {
        r += rcd->getTickValue();
        l += rcg->getTickValue();
        for(int i=0; i<1000000; i++);
    }
}

void Debug::testBrasLateraux()
{
    /*Timer* timer3 = new Timer(TIM3, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
    TIM_CtrlPWMOutputs(TIM3, ENABLE);

    Servo* porteGaucheAsc = new Servo(timer3, 1, 0.01f, 0.11f);
    Servo* porteDroiteAsc = new Servo(timer3, 2, 0.01f, 0.11f);
    Servo* porteDroiteBas = new Servo(timer3, 3, 0.01f, 0.11f);
    Servo* porteGaucheBas = new Servo(timer3, 4, 0.02f, 0.14f);


    //Portes* portesAscenseur = new Portes(porteGaucheAsc, porteDroiteAsc, 20.0f, 50.0f, 160.0f, 130.0f);

    while(1)
    {

        porteGaucheAsc->goToAngle(0.0f);
        porteDroiteAsc->goToAngle(0.0f);
        porteDroiteBas->goToAngle(0.0f);
        porteGaucheBas->goToAngle(0.0f);
        for (int i = 0; i < 10000000; i++);

        porteGaucheAsc->goToAngle(90.0f);
        porteDroiteAsc->goToAngle(90.0f);
        porteDroiteBas->goToAngle(90.0f);
        porteGaucheBas->goToAngle(90.0f);
        for (int i = 0; i < 10000000; i++);
    }*/

    BrasLateraux::initBrasLateraux();

    while(true)
    {
        BrasLateraux::getLeft()->expand();
        BrasLateraux::getRight()->expand();
        Led::toggle(0);

        for(int i=0; i<10000000; i++);

        //BrasLateral::getLeft()->front();
        /*BrasLateral::getRight()->front();
        Led::toggle(0);

        for(int i=0; i<10000000; i++);*/

        BrasLateraux::getLeft()->collapse();
        BrasLateraux::getRight()->collapse();
        Led::toggle(0);

        for(int i=0; i<10000000; i++);
    }
}

void Debug::testContainer()
{
    Container::getSingleton();
    BrasLateraux::initBrasLateraux();

    while(true)
    {
        Container::getSingleton()->open();
        BrasLateraux::getLeft()->expand();
        BrasLateraux::getRight()->expand();
        Led::toggle(0);

        for(int i=0; i<10000000; i++);

        BrasLateraux::getLeft()->front();
        BrasLateraux::getRight()->front();
        Led::toggle(0);

        for(int i=0; i<10000000; i++);

        Container::getSingleton()->close();
        BrasLateraux::getLeft()->collapse();
        BrasLateraux::getRight()->collapse();
        Led::toggle(0);

        for(int i=0; i<20000000; i++);
    }

    /*Container::getSingleton();

    while(true)
    {
        Container::getSingleton()->open();
        Led::toggle(0);

        for(int i=0; i<10000000; i++);

        Container::getSingleton()->close();
        Led::toggle(0);

        for(int i=0; i<10000000; i++);
    }*/
}

void Debug::testTirette(Tirette* t)
{
    while(true)
    {
        if (t->enlevee())
            Led::setOff(0);
        else
            Led::setOn(0);
    }
}

void Debug::testRemote()
{
    Remote::getSingleton();

    //KrabiPacket packet;
//    packet.add("Bonjour");
//    packet.add(2);
//    packet.add(6);
//    packet.add(2048);

//    Remote::getSingleton()->sendData(&packet);

    int timer = 0;
    while(true)
    {
        if (Remote::getSingleton()->dataAvailable()) {
            Remote::getSingleton()->receiveData();
            Led::toggle(0);
        }

        if (timer==0) {
            Remote::getSingleton()->sendData('a');
            Led::toggle(0);
        }

        timer++;
        if (timer==1000000)
            timer = 0;
    }
}

/*void Debug::testPWM(QuadratureCoderHandler* rcg, QuadratureCoderHandler* rcd)
{
    long r = 0, l = 0;
    while(true)
    {
        r += rcd->getTickValue();
        l += rcg->getTickValue();
        for(int i=0; i<1000000; i++);
    }
}*/

/*
    Tirette tirette(GPIOA, GPIO_Pin_10);
    bool toto = tirette.enlevee();
    bool tata = tirette.enlevee();
    //tirette.attendreRemise();
    //tirette.attendreEnlevee();

    bool titi = tirette.enlevee();
    bool tutu = tirette.enlevee();*/
/*
    allumerLED();

    //GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);
    Servo::initPin(GPIOE, GPIO_Pin_9);

    Timer* timer3 = new Timer(TIM3, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
    TIM_CtrlPWMOutputs(TIM3, ENABLE);


    Servo* servo1 = new Servo(timer3, 1, 0.01f, 0.11f);
    Servo* servo2 = new Servo(timer3, 2, 0.01f, 0.11f);
    Servo* servo3 = new Servo(timer3, 3, 0.01f, 0.11f);
    Servo* servo4 = new Servo(timer3, 4, 0.01f, 0.11f);

    servo1->goToAngle(BALAI_G_CLOSED);
    servo2->goToAngle(BALAI_G_CLOSED);
    servo3->goToAngle(BALAI_G_CLOSED);
    servo4->goToAngle(BALAI_G_CLOSED);
    tirette.attendreRemise();
    tirette.attendreEnlevee();
   // eteindreLED();
    servo1->goToAngle(BALAI_G_OPEN);
    servo2->goToAngle(BALAI_G_OPEN);
    servo3->goToAngle(BALAI_G_OPEN);
    servo4->goToAngle(BALAI_G_OPEN);
    //Servo balaiGauche = new Servo(TIM3, unsigned char OCx, float RC0degre, float RC180degres);
*/
/*


    allumerLED();
    eteindreLED();

    allumerLED();
    eteindreLED();

    allumerLED();
    eteindreLED();

*/

//    allumerLED();

 //   allumerLED();
    //allumerLED2();

    //for (int i = 0; i < 1000000000; i++);


    //Etape** tableauEtapes;// = [sizeof(Etape)*10];
    //Etape* etape1;
    /*
    Etape* etape1;
    Etape* etape2;
    Etape* etape3;
    Etape* etape4;
    Etape* etape5;

    Etape** tableauEtapes1 = new Etape*[1];
    Etape** tableauEtapes2 = new Etape*[3];
    Etape** tableauEtapes3 = new Etape*[3];
    Etape** tableauEtapes4 = new Etape*[3];
    Etape** tableauEtapes5 = new Etape*[2];

    etape1 = new Etape(Position(100,100, true), tableauEtapes1, 1, Etape::DEPART,-1);
    etape2 = new Etape(Position(500,500, true), tableauEtapes2, 3, Etape::POINT_PASSAGE,-1);
    etape3 = new Etape(Position(1000,500, true), tableauEtapes3, 3, Etape::FEU,-1);
    etape4 = new Etape(Position(500,700, true), tableauEtapes4, 3, Etape::FEU,-1);
    etape5 = new Etape(Position(500,800, true), tableauEtapes5, 2, Etape::FEU,-1);

    tableauEtapes1[0] = etape2;

    tableauEtapes2[0] = etape1;
    tableauEtapes2[1] = etape3;
    tableauEtapes2[2] = etape4;

    tableauEtapes3[0] = etape2;
    tableauEtapes3[1] = etape4;
    tableauEtapes3[2] = etape5;

    tableauEtapes4[0] = etape2;
    tableauEtapes4[1] = etape3;
    tableauEtapes3[2] = etape5;

    tableauEtapes5[0] = etape3;
    tableauEtapes5[1] = etape4;

    etape1->setChildren(tableauEtapes1);
    etape2->setChildren(tableauEtapes2);
    etape3->setChildren(tableauEtapes3);
    etape4->setChildren(tableauEtapes4);
    etape5->setChildren(tableauEtapes5);

    Etape** tableauEtapesTotal = new Etape*[5];
    tableauEtapesTotal[0] = etape1;
    tableauEtapesTotal[1] = etape2;
    tableauEtapesTotal[2] = etape3;
    tableauEtapesTotal[3] = etape4;
    tableauEtapesTotal[4] = etape5;

    Dijkstra* dijkstra = new Dijkstra(tableauEtapesTotal, 5);

    dijkstra->setEtapeCourante(0);
    etape1->setState(-1);
    etape2->setState(-1);
    etape3->setState(-1);
    etape4->setState(-2);
    etape5->setState(-1);
    dijkstra->run();

    int distance = dijkstra->getDistance(3);
*/
    /*
    for (int i = 0; i < 10000; i++);
    ServosNumeriques::setLedState(1, MBD_ID);
    for (int i = 0; i < 10000; i++);
    ServosNumeriques::setLedState(1, MBG_ID);
    for (int i = 0; i < 10000; i++);
    ServosNumeriques::setLedState(1, MHD_ID);
    for (int i = 0; i < 10000; i++);
    ServosNumeriques::setLedState(1, MHG_ID);
        allumerLED();
        for (int i = 0; i < 10000000; i++)
        {
        }
    for (int i = 0; i < 10000; i++);
    ServosNumeriques::setLedState(0, MBD_ID);
    for (int i = 0; i < 10000; i++);
    ServosNumeriques::setLedState(0, MBG_ID);
    for (int i = 0; i < 10000; i++);
    ServosNumeriques::setLedState(0, MHD_ID);
    for (int i = 0; i < 10000; i++);
    ServosNumeriques::setLedState(0, MHG_ID);
        eteindreLED();
        for (int i = 0; i < 10000000; i++)
        {}*/

    /*
    while(1)
    {


       // Marteaux::enfoncerBasDroit();
        Marteaux::enfoncerBasGauche();
        //Marteaux::enfoncerHautDroit();
        //Marteaux::enfoncerHautGauche();
        allumerLED();
        for (int i = 0; i < 6000000; i++)
        {
        }

        eteindreLED();
        //Marteaux::releverBasDroit();
        Marteaux::releverBasGauche();
        //Marteaux::releverHautDroit();
       // Marteaux::releverHautGauche();
        for (int i = 0; i < 6000000; i++)
        {
        }

        //Marteaux::enfoncerBasDroit();
        Marteaux::enfoncerBasGauche();
        //Marteaux::enfoncerHautDroit();
        //Marteaux::enfoncerHautGauche();
        allumerLED();
        for (int i = 0; i < 6000000; i++)
        {
        }

        eteindreLED();
        //Marteaux::releverBasDroit();
        Marteaux::releverBasGauche();
        //Marteaux::releverHautDroit();
        //Marteaux::releverHautGauche();
        for (int i = 0; i < 13000000; i++)
        {
        }

        eteindreLED();
        //Marteaux::rangerBasDroit();
        Marteaux::rangerBasGauche();
        //Marteaux::rangerHautDroit();
        //Marteaux::rangerHautGauche();
        for (int i = 0; i < 10000000; i++)
        {
        }

    }*/

    // test fdc :
    /*
    LimitSwitchSensor* fdc1 = new LimitSwitchSensor(LimitSwitchSensor::BACK_LEFT, GPIO_Pin_14, GPIOD);
    LimitSwitchSensor* fdc2 = new LimitSwitchSensor(LimitSwitchSensor::BACK_RIGHT, GPIO_Pin_1, GPIOD);
    while(1)
    {
        fdc1->updateValue();
        fdc2->updateValue();
        if (fdc1->getValue().b)
            allumerLED();
        else
            eteindreLED();
        if (fdc2->getValue().b)
            allumerLED2();
        else
            eteindreLED2();
        for (int i = 0; i < 10000; i++)
        {
        }
    }*/
    /*
    CapteurCouleur* capteur = new CapteurCouleur(TIM5, GPIOA, GPIO_Pin_0,
                                               GPIOD, GPIO_Pin_0,
                                               GPIOD, GPIO_Pin_2,
                                               GPIOC, GPIO_Pin_8,
                                               GPIOC, GPIO_Pin_10,
                                               GPIOD, GPIO_Pin_7,
                                               GPIOC, GPIO_Pin_12);

    capteur->activerCapteur(GAUCHE_BAS);

    int valeurs[16];

    Tirette tirette(GPIOE, GPIO_Pin_5);
    bool t = true;

    for (int i = 0 ; i < 10000 ; i++)
    {
        if (i % 4 == 0)
        {
            capteur->allumerDiodesRouges(true);
            capteur->allumerDiodesBleues(false);
        }
        else if (i % 4 ==  2)
        {
            capteur->allumerDiodesRouges(false);
            capteur->allumerDiodesBleues(true);
        }
        else
        {
            capteur->allumerDiodesRouges(false);
            capteur->allumerDiodesBleues(false);
        }

        while (true)
        {
            for (int d = 0 ; d < 1000000 ; d++);
            capteur->getTickValue();
            if (tirette.enlevee() == t)
            {
                for (int d = 0 ; d < 1000000 ; d++);
                capteur->selectionnerFiltre(FILTRE_ROUGE);
                valeurs[i*4] = capteur->getTickValue();
                for (int d = 0 ; d < 1000000 ; d++);
                capteur->selectionnerFiltre(FILTRE_VERT);
                valeurs[i*4+1] = capteur->getTickValue();
                for (int d = 0 ; d < 1000000 ; d++);
                capteur->selectionnerFiltre(FILTRE_BLEU);
                valeurs[i*4+2] = capteur->getTickValue();
                for (int d = 0 ; d < 1000000 ; d++);
                capteur->selectionnerFiltre(FILTRE_BLANC);
                valeurs[i*4+3] = capteur->getTickValue();
                t = !t;
                break;
            }

        }
    }*/

    /*
    uint8_t channels[10] = {9,13,8,11,5,10,4,12,14,15};
    uint16_t* data = AnalogSensor::initialiserADC(10, channels);
    int nbSharp = 10;
    SharpSensor** sharps = new SharpSensor*[nbSharp];
    sharps[0] = new SharpSensor(SharpSensor::FRONT_LEFT, 9, data); // front left 9
    sharps[1] = new SharpSensor(SharpSensor::FRONT_RIGHT, 13, data); // front side right 13
    sharps[2] = new SharpSensor(SharpSensor::FRONT_SIDE_LEFT, 8, data); // front side left 8
    sharps[3] = new SharpSensor(SharpSensor::FRONT_SIDE_RIGHT, 11, data); // avant side droite 11
    sharps[4] = new SharpSensor(SharpSensor::BACK_LEFT, 5, data); // ARRIERE gauche 5
    sharps[5] = new SharpSensor(SharpSensor::BACK_MIDDLE, 10, data, 2500.); // back middle 10
    sharps[6] = new SharpSensor(SharpSensor::NONE, 4, data); // arriere droit 4
    sharps[7] = new SharpSensor(SharpSensor::ELEVATOR_TOP, 12, data); // capteur haut ascenseur 12
    sharps[8] = new SharpSensor(SharpSensor::ELEVATOR_DOWN, 14, data); // capteur bas ascenseur 14
    sharps[9] = new SharpSensor(SharpSensor::BACK_RIGHT, 15, data); // rien


    while(1)
    {
        AnalogSensor::startConversion();
        allumerLED2();
        for (int i = 0; i < 10; i++)
        {
            sharps[i]->updateValue();
        }
        bool allume = false;
        for (int i = 0; i < 10; i++)
        {
            if (sharps[i]->getValue().b)
            {
                allume = true;
            }
        }
        if (allume) {
            allumerLED();
        }
        else {
            eteindreLED();
        }
        for (int i = 0; i < 1000; i++)
        {
        }
        eteindreLED2();
        for (int i = 0; i < 1000; i++)
        {
        }
    }
    */
    /*StrategieV2* strat = new StrategieV2();

    while(1)
    {
        strat->update();
        for (int i = 0; i < 1000; i++);
    }*/
    /*
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);
    Servo::initPin(GPIOE, GPIO_Pin_9);
    Servo::initPin(GPIOE, GPIO_Pin_11);
    Servo::initPin(GPIOE, GPIO_Pin_13);
    Servo::initPin(GPIOE, GPIO_Pin_14);

    Timer* timer1 = new Timer(TIM1, PERIOD_TIMER_SERVO, PRESCALER_TIMER_SERVO, CLOCK_TIMER_SERVO);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);

    Servo* porteGaucheAsc = new Servo(timer1, 1, 0.01f, 0.11f);
    Servo* porteDroiteAsc = new Servo(timer1, 2, 0.01f, 0.11f);
  //  Servo* porteDroiteBas = new Servo(timer1, 3, 0.01f, 0.11f);
 //   Servo* porteGaucheBas = new Servo(timer1, 4, 0.02f, 0.14f);


    //Portes* portesAscenseur = new Portes(porteGaucheAsc, porteDroiteAsc, 20.0f, 50.0f, 160.0f, 130.0f);

    while(1)
    {
        for (int i = 0; i < 60000000; i++)
        {
        }
            porteGaucheAsc->goToAngle(0.0f);
        for (int i = 0; i < 60000000; i++)
        {
        }je vais peut être commencer à adapter le code du robot à ma carte STM32 H103 Krabi Jr 2014
            porteGaucheAsc->goToAngle(90.f);
    }*/
