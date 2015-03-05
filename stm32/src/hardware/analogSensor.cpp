#include "analogSensor.h"

int AnalogSensor::nbCapteurDejaInitialise = 0;

AnalogSensor::AnalogSensor(uint8_t channel, DMA_MEMORY_TYPE* pData)
{
    this->channel = channel;
    this->data = pData + AnalogSensor::nbCapteurDejaInitialise;

    AnalogSensor::nbCapteurDejaInitialise++;
}

AnalogSensor::~AnalogSensor()
{
}

#ifdef ROBOTHW // pour le vrai robot

DMA_MEMORY_TYPE* AnalogSensor::initialiserADC(uint8_t nbChannel, uint8_t* channels)
{
    #ifdef STM32F40_41xxx
        DMA_MEMORY_TYPE* data = new DMA_MEMORY_TYPE[nbChannel];

        /*ADC_InitTypeDef ADC_InitStructure;
        ADC_CommonInitTypeDef ADC_CommonInitStructure;
        // ADC1 fonctionne tout seul (on n'utilise ni ADC2 ni ADC3)

        ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
        // On scanne tous les channels
        ADC_InitStructure.ADC_ScanConvMode = ENABLE;
        // Single conversion mode
        ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
        // Pas d'external trigger (on lance la conversion à la main)
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigInjecConvEdge_None;//ADC_ExternalTrigConv_None;
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
        ADC_InitStructure.ADC_NbrOfConversion = nbChannel;
        ADC_Init(ADC1, &ADC_InitStructure);
        ADC_CommonInit(&ADC_CommonInitStructure);

        // Activation du périphérique
        ADC_Cmd(ADC1, ENABLE);

        // Calibrage //Pas besoin pour le F4
        // On remet la calibration à zéro
        // Définition des canaux à convertir
        //ADC_RegularChannelConfig (ADC_TypeDef *ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime)
        for (int i=0; i<nbChannel; i++) {
            ADC_RegularChannelConfig (ADC1, channels[i], i+1, ADC_SampleTime_15Cycles);//ADC_SampleTime_1Cycles5);
        }

        // active le transfert des résultats de conversion en SRAM
        ADC_DMACmd(ADC1, ENABLE);

        DMA_InitTypeDef DMA_InitStructure;
        DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(ADC1->DR); // ADC regular data register contient le résultat de la conversion
        DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)data ; // Adresse de destination
        DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory; // On transfère du périphérique (ADC) à la mémoire (SRAM)
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
        //DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
        // Channel1 : cf p.192 tableau 58
        DMA_Init(DMA1_Stream1, &DMA_InitStructure);//DMA1_Channel1, &DMA_InitStructure);
        DMA_Cmd(DMA1_Stream1, ENABLE);*///DMA1_Channel1, ENABLE);

        ADC_InitTypeDef       ADC_InitStructure;
        ADC_CommonInitTypeDef ADC_CommonInitStructure;
        DMA_InitTypeDef       DMA_InitStructure;

        /* DMA2 Stream0 channel0 configuration **************************************/
        DMA_InitStructure.DMA_Channel = DMA_Channel_2;
        DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC3_DR_ADDRESS;
        DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)data;
        DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
        DMA_InitStructure.DMA_BufferSize = nbChannel;
        DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
        DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
        DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
        DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
        DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
        DMA_InitStructure.DMA_Priority = DMA_Priority_High;
        DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
        DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
        DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
        DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
        DMA_Init(DMA2_Stream0, &DMA_InitStructure);
        DMA_Cmd(DMA2_Stream0, ENABLE);

        /* ADC Common Init **********************************************************/
        ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
        ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
        ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
        ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
        ADC_CommonInit(&ADC_CommonInitStructure);

        /* ADC3 Init ****************************************************************/
        ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
        ADC_InitStructure.ADC_ScanConvMode = ENABLE;
        ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
        ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
        ADC_InitStructure.ADC_NbrOfConversion = nbChannel;
        ADC_Init(ADC3, &ADC_InitStructure);

        /* ADC3 regular channel12 configuration *************************************/
        //ADC_RegularChannelConfig(ADC3, ADC_Channel_12, 1, ADC_SampleTime_3Cycles);
        for (int i=0; i<nbChannel; i++)
            ADC_RegularChannelConfig(ADC3, channels[i], i+1, ADC_SampleTime_3Cycles);

        /* Enable DMA request after last transfer (Single-ADC mode) */
        ADC_DMARequestAfterLastTransferCmd(ADC3, ENABLE);

        /* Enable ADC3 DMA */
        ADC_DMACmd(ADC3, ENABLE);

        /* Enable ADC3 */
        ADC_Cmd(ADC3, ENABLE);

        /* Start ADC3 Software Conversion */
        ADC_SoftwareStartConv(ADC3);

        return data;
    #else
        DMA_MEMORY_TYPE* data = new DMA_MEMORY_TYPE[nbChannel];

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

        // Définition des canaux à convertir
        //ADC_RegularChannelConfig (ADC_TypeDef *ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime)
        for (int i=0; i<nbChannel; i++)
            ADC_RegularChannelConfig (ADC1, channels[i], i+1, ADC_SampleTime_1Cycles5);

        // active le transfert des résultats de conversion en SRAM
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
    #endif
}

void AnalogSensor::startConversion()
{
    #ifdef STM32F40_41xxx
        ADC_SoftwareStartConv(ADC1);
    #else
        ADC_SoftwareStartConvCmd(ADC1, ENABLE); // lance une conversion
    #endif
}

bool AnalogSensor::conversionFinished()
{
    //return (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == SET);
   // DMA_Stream_TypeDef
   //return DMA_GetFlagStatus(DMA1_Stream1_BASE, DMA_FLAG_TCIF1);
   //return DMA_GetFlagStatus(DMA1_FLAG_TC1);
   //return DMA_GetFlagStatus(DMA1_Stream1, DMA_FLAG_TCIF1);//I have no idea what I am doing
    //TOBECONTINUED
    #ifdef STM32F40_41xxx
        return true;
    #else
        return DMA_GetFlagStatus(DMA1_FLAG_TC1);
    #endif
}

#else // pour le simulateur

#ifndef NULL
#define NULL 0
#endif
DMA_MEMORY_TYPE* AnalogSensor::initialiserADC(uint8_t nbChannel, uint8_t* channels)
{
    return NULL;
}

void AnalogSensor::startConversion()
{
}

bool AnalogSensor::conversionFinished()
{
    return true;
}

#endif
