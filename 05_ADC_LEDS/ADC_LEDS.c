#include "stm32f10x.h"                  // Device header
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC

uint16_t adc_value = 0;
float map_value = 0;

void GPIO_Config(){
	GPIO_InitTypeDef	GPIOInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//LEDS
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//POT
	
	//LEDS
	GPIOInitStructure.GPIO_Mode 	= GPIO_Mode_Out_PP;
	GPIOInitStructure.GPIO_Pin 		= GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
	GPIOInitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIOInitStructure);

	//POT
	GPIOInitStructure.GPIO_Mode		= GPIO_Mode_AIN;
	GPIOInitStructure.GPIO_Pin		= GPIO_Pin_0;
	GPIOInitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIOInitStructure);

}

void ADC_Config(){
	ADC_InitTypeDef	ADCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	ADCInitStructure.ADC_ContinuousConvMode		= ENABLE;
	ADCInitStructure.ADC_DataAlign 						= ADC_DataAlign_Right;
	ADCInitStructure.ADC_ExternalTrigConv 		= ADC_ExternalTrigConv_None;
	ADCInitStructure.ADC_Mode 								= ADC_Mode_Independent;
	ADCInitStructure.ADC_NbrOfChannel 				= 1;
	ADCInitStructure.ADC_ScanConvMode 				= DISABLE;
	
	ADC_Init(ADC1,&ADCInitStructure);
	ADC_Cmd(ADC1, ENABLE);
	
}

uint16_t read_adc(){
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0, 1 , ADC_SampleTime_55Cycles5);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
	
	return ADC_GetConversionValue(ADC1);

}

float map(float adc_value, float max, float min, float conMax, float conMin){
	
	return adc_value*((conMax-conMin)/(max-min));

}


int main(){
	GPIO_Config();
	ADC_Config();
	
	while(1){
		adc_value = read_adc();
		map_value = map(adc_value, 4095, 0, 180, 0);
		
			if(map_value>=0 && map_value<60){
			GPIO_SetBits(GPIOB,GPIO_Pin_0);
			GPIO_ResetBits(GPIOB,GPIO_Pin_0 | GPIO_Pin_1);
		
		}
		if(map_value>=60 && map_value<120){
			GPIO_SetBits(GPIOB,GPIO_Pin_0 |GPIO_Pin_1);
			GPIO_ResetBits(GPIOB,GPIO_Pin_2);
		
		}
			if(map_value>=120 && map_value<180){
			GPIO_SetBits(GPIOB,GPIO_Pin_0 |GPIO_Pin_1 |GPIO_Pin_2);
		}
		
	}

}