#include "stm32f10x.h"                  // Device header
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC

uint16_t adc_value = 0;
float voltage_value = 0;

void GPIO_Config(){
	GPIO_InitTypeDef	GPIOInitstructure;
	
	//POT 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIOInitstructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIOInitstructure.GPIO_Pin = GPIO_Pin_0;
	GPIOInitstructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIOInitstructure);

}

void ADC_Config(){
	ADC_InitTypeDef	ADCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	ADCInitStructure.ADC_ContinuousConvMode 	= ENABLE;
	ADCInitStructure.ADC_DataAlign 						= ADC_DataAlign_Right;
	ADCInitStructure.ADC_ExternalTrigConv 		= ADC_ExternalTrigConv_None;
	ADCInitStructure.ADC_Mode 								= ADC_Mode_Independent;
	ADCInitStructure.ADC_NbrOfChannel 				= 1;
	ADCInitStructure.ADC_ScanConvMode					= DISABLE;
	
	ADC_Init(ADC1,&ADCInitStructure);
	ADC_Cmd(ADC1,ENABLE);

}

uint16_t read_adc(){
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==RESET);
	
	return ADC_GetConversionValue(ADC1);

}

int main(){
	GPIO_Config();
	ADC_Config();
	
	while(1){
		adc_value = read_adc();
		voltage_value = adc_value *(3.3/4095);	
	
	}

}