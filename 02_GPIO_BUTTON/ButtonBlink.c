#include "stm32f10x.h"                  // Device header

uint16_t buttonState = 0;
	
void GPIO_Config(){
	GPIO_InitTypeDef	GPIOInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //for led clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //for button clock
	
	//LED
	GPIOInitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIOInitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIOInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIOInitStructure);
	
	//BUTTON
	
	GPIOInitStructure.GPIO_Mode = GPIO_Mode_IPD; //PD connect GND
	GPIOInitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOC, &GPIOInitStructure);
	

}


int main(){
	GPIO_Config();
	
	
	while(1){
	buttonState = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6);
	
		if(buttonState==1){
			GPIO_SetBits(GPIOB, GPIO_Pin_0);
		
		
		}else{
		GPIO_ResetBits(GPIOB, GPIO_Pin_0);
		
		}
	
	}



}