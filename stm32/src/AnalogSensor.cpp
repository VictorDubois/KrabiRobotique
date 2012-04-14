#include "AnalogSensor.h"

AnalogSensor::AnalogSensor(uint8_t channel, uint16_t* pData)
{
    this->channel = channel;
    this->data = pData;
}

AnalogSensor::~AnalogSensor()
{
    //dtor
}


uint16_t* AnalogSensor::initialiserADC(int nbChannel)
{
   uint16_t* data = new uint16_t[nbChannel];

    ADC_InitTypeDef ADC_InitStructure;
    // ADC1 fonctionne tout seul (on n'utilise ni ADC2 ni ADC3)
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    // On scanne tous les channels
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    // Single conversion mode
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    // Pas d'external trigger (on lance la conversion à la main)
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = nbChannel;
    ADC_Init(ADC1, &ADC_InitStructure);

    // Activation du périphérique
    ADC_Cmd(ADC1, ENABLE);

    // Calibrage
    // On remet la calibration à zéro
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    // On lance la calibration
    ADC_StartCalibration(ADC1);
    // Et on attend que ce soit fini
    while(ADC_GetCalibrationStatus(ADC1));

/*    // Définition des canaux à convertir
    //ADC_RegularChannelConfig (ADC_TypeDef *ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime)
    for (int i=0; i<nbChannel; i++) {
        ADC_RegularChannelConfig (ADC1, Channels[i], i+1, ADC_SampleTime_1Cycles5);
    }
 */   // active le transfert des résultats de conversion en SRAM
    ADC_DMACmd(ADC1, ENABLE);

    DMA_InitTypeDef DMA_InitStructure;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(ADC1->DR); // ADC regular data register contient le résultat de la conversion
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)data ; // Adresse de destination
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; // On transfère du périphérique (ADC) à la mémoire (SRAM)
    DMA_InitStructure.DMA_BufferSize = nbChannel; // Nombre de conversions à transférer
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; // L'adresse du résultat de la conversion ne change pas
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; // Incrémente le pointeur destination pour enregistrer les différentes conversions
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    // Note : le registre ADC_DR fait 32 bits mais seuls les bits 0:15 nous intéressent
    // Ici tout devrait fonctionner correctement : cf doc p.189 (tableau 56) (malgré une petite erreur dans le tableau)
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    // On ne permet pas de lancer un transfert en software (car lancé par le périphérique ADC)
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    // Channel1 : cf p.192 tableau 58
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);
    DMA_Cmd(DMA1_Channel1, ENABLE);

    return data;
}
