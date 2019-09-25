

#include "stm32f10x.h"                  // Device header
#include "delay.h"
uint16_t sayac=0;


void  timer3_init(void);
void pin_init(void);






int main()
	
{
	delay_init();
	pin_init(); //pb0 olacak.
	timer3_init();
	
	
	//TIM3->CCR3=600;
	
	while(1)
	{
		
		 sayac =sayac+4000;
		
		TIM3->CCR3 =sayac;
		delay_ms(5);
		
		if(sayac>11999)
		{
			sayac=0;
			TIM3->CCR3 =sayac;
			delay_ms(5);
		}
			
	
		
		
	}
	
	
}
void pin_init()
{

   RCC->APB2ENR |=1<<3;//B portu aktif.
	 RCC->APB2ENR |=1<<0;//Alternatif fonksiyon enable.
   GPIOB->CRL &=0x00;//Temizleme.
	 GPIOB ->CRL =0x0000000A;//B0  ALTERNATIVE OUTPUT.
	AFIO->MAPR     |=1<<11;   //PB0 için. Alternatif fonksiyon ayari 	  
  AFIO ->MAPR    &=~(1<<10);//PBO için. Alternatif fonksiyon ayari 	
	 GPIOB ->BSRR =1<<0;
}

void timer3_init()
{

	RCC->APB1ENR  |=1<<1; //TIMER3 AKTIF.
	

	
	TIM3->CR1 &=~(1<<6); //SECME MODU
	TIM3->CR1 &=~(1<<5); //SECME MODU
	
	TIM3->CR1 |=1<<7;
	
	TIM3->CR1 &=~(1<<4); //UPCOUNT
	
	TIM3->CR1 &=~(1<<0);//UDIS
	
	TIM3->CCMR1 = 0;
	TIM3->RCR =0;
	TIM3->PSC =1;
	TIM3->ARR =11999;
	
	
	TIM3->CCER  &=~(1<<9);//CC3P
	TIM3->CCER  |=1<<8;//CC3E
	
	
	
	TIM3->CCMR2 &=~(1<<4);  //PWM1
	TIM3->CCMR2  |=1<<5;    //PWM1
	TIM3->CCMR2  |=1<<6;   //PWM1
	
	//TIM3->CCMR2  |=1<<3;//OCXPE PRELOAD ENABLE.
	
	
	
	TIM3->CCR3=0;
	TIM3->CR1 |=1<<0;//ENABLE.
	
 
	
}

