#include "stm32f10x.h"                  // Device header

void GPIO_Config(){
	
	GPIO_InitTypeDef	GPIOInitStructere;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIOInitStructere.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIOInitStructere.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIOInitStructere.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIOInitStructere);

}


void delay(uint32_t time){
	while(time--);

}

int main(){
	
	GPIO_Config();
	int ledArray[3] = {GPIO_Pin_0, GPIO_Pin_1, GPIO_Pin_2};
	
	
	while(1){
		
		for(int i=0;i<3;i++){
			GPIO_SetBits(GPIOB, ledArray[i]);
			delay(360000);
			GPIO_ResetBits(GPIOB, ledArray[i]);
			delay(360000);
		}

}






}