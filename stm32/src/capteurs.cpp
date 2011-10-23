#include "capteurs.h"

Capteurs::Capteurs(): threshold(SEUIL_DETECTION), isConverted(false)
{
     uint8_t Channels[] = {10,11,12,13,15};
      NbrOfChannel = 5;

    // rawData contient les résultats bruts des conversions
    data = new uint16_t[NbrOfChannel];
    output = new uint32_t[NbrOfChannel];

    for(unsigned int i=0; i < NbrOfChannel; i++)
        output[i] = 0;

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
    ADC_InitStructure.ADC_NbrOfChannel = NbrOfChannel;
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
    for (int i=0; i<NbrOfChannel; i++) {
        ADC_RegularChannelConfig (ADC1, Channels[i], i+1, ADC_SampleTime_1Cycles5);
    }
    // active le transfert des résultats de conversion en SRAM
    ADC_DMACmd(ADC1, ENABLE);

    DMA_InitTypeDef DMA_InitStructure;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(ADC1->DR); // ADC regular data register contient le résultat de la conversion
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)data ; // Adresse de destination
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; // On transfère du périphérique (ADC) à la mémoire (SRAM)
    DMA_InitStructure.DMA_BufferSize = NbrOfChannel; // Nombre de conversions à transférer
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
}

void Capteurs::startConversion()
{
    isConverted = false;
    ADC_SoftwareStartConvCmd(ADC1, ENABLE); // lance une conversion
}

bool Capteurs::conversionFinished()
{
    //return (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == SET);
    return DMA_GetFlagStatus(DMA1_FLAG_TC1);
}

void Capteurs::convertirDonnees()
{
    isConverted = true;
    while (!conversionFinished());    // au cas où l'interrupt de l'asservissement tombe avant la fin de l'acquisition/conversion
    /***********************************************
     **                                           **
     **                                           **
     ** C'EST ICI QU'IL FAUT METTRE LE BREAKPOINT **
     **     POUR AVOIR LA VALEUR DES CAPTEURS     **
     **                                           **
     **                                           **
     ***********************************************/
    for(int i=0;i<NbrOfChannel;i++)  { // Ceci est un compteur binaire, qui ajoute un bit à droite chaque fois qu'un objet est detecté
        output[i] <<= 1;
        output[i] |= (data[i] > threshold);
    }
}

uint16_t Capteurs::getValue(Capteurs::Direction direction) // Retourne vrai si et seulement si le seuil du capteur a été dépassé pendant plus de 8 coups d'horloge car àxff = 8bits à 1
{
    if (!isConverted)
        convertirDonnees();
    return (output[direction] & 0xff) == 0xff;
}

uint8_t Capteurs::getNbrOfChannel(){
    return NbrOfChannel;
}
