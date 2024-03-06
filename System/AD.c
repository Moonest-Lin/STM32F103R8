#include "GPIO.h"

void AD_Init(void)
{
	RCC_APB2PeriphClockCmd($AD_ADCRCC, ENABLE);
	RCC_APB2PeriphClockCmd($AD_GPIORCC, ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin = $AD_GPIOPin;	
	GPIO_Init($AD_GPIOPort, &GPIO_InitStruct);
	
	ADC_RegularChannelConfig($AD_ADC,$AD_ADCChannel,$AD_ADCRank,$AD_ADCTime);
	
	ADC_InitTypeDef ADC_InitStructure;
	
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	
	ADC_Init($AD_ADC,&ADC_InitStructure);
	
	ADC_Cmd($AD_ADC,ENABLE);
	
	ADC_ResetCalibration($AD_ADC);
	while(ADC_GetResetCalibrationStatus($AD_ADC) == SET);
	ADC_StartCalibration($AD_ADC);
	while(ADC_GetCalibrationStatus($AD_ADC) == SET);
}

u16 AD_GetValue(void)
{
	ADC_SoftwareStartConvCmd($AD_ADC,ENABLE);
	while(ADC_GetFlagStatus($AD_ADC,ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue($AD_ADC);
}
