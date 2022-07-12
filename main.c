

#include "stm32f10x.h"   



void timer_config(void);
void delay_ms(uint16_t );

int main(){
	
	RCC->APB2ENR |= (1<<2); // set portA clock bus enable
	GPIOA->CRL = 0X300000; // set PA5 output
	
	timer_config();
	 
	while(1){
		
		GPIOA->ODR ^= (1<<5);
		delay_ms(1000);
}
	
}

void timer_config(void){
	
	RCC->APB1ENR = 0X01; // set TIM2 clock bus enable
	TIM2->PSC = 8000 - 1; // 8 MHz / 8000 = 1000Hz --> 1 ms period
	TIM2->ARR = 0xFFFF; // load ARR register by 65535 value
	TIM2->CR1 = 0X01; // counter enable
	while(!(TIM2->SR & 0x01)); //wait for flag set
}

void delay_ms(uint16_t time){
	
	TIM2->CNT = 0;
	while (TIM2->CNT < time);
}


