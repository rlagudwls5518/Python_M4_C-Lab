#include "device_driver.h"

#define TIM2_TICK         	(20) 				// usec
#define TIM2_FREQ 	  		(1000000/TIM2_TICK)	// Hz
#define TIME2_PLS_OF_1ms  	(1000/TIM2_TICK)
#define TIM2_MAX	  		(0xffffu)

void Timer2_Init(void){
	Macro_Set_Bit(RCC->APB1ENR, 0);
	TIM2->CR1 = (1<<4)|(1<<3);
}

void Timer5_Init(void){
	Macro_Set_Bit(RCC->APB1ENR, 3);
	TIM5->CR1 = (1<<4)|(1<<3);
}

void Timer2_Start(int time)
{
	TIM2->PSC = (unsigned int)(TIMXCLK/50000.0 + 0.5)-1;
	TIM2->ARR = time * TIME2_PLS_OF_1ms;

	Macro_Set_Bit(TIM2->EGR,0);
	Macro_Clear_Bit(TIM2->SR, 0);
	Macro_Set_Bit(TIM2->CR1, 0);
}

void Timer2_Delay(int time)
{
	int i;
	unsigned int t = TIME2_PLS_OF_1ms * time;
	TIM2->PSC = (unsigned int)(TIMXCLK/(double)TIM2_FREQ + 0.5)-1;
	TIM2->ARR = 0xffff;
	Macro_Set_Bit(TIM2->EGR,0);

	for(i=0; i<(t/0xffffu); i++)
	{
		Macro_Set_Bit(TIM2->EGR,0);
		Macro_Clear_Bit(TIM2->SR, 0);
		Macro_Set_Bit(TIM2->CR1, 0);
		while(Macro_Check_Bit_Clear(TIM2->SR, 0));
	}

	TIM2->ARR = t % 0xffffu;
	Macro_Set_Bit(TIM2->EGR,0);
	Macro_Clear_Bit(TIM2->SR, 0);
	Macro_Set_Bit(TIM2->CR1, 0);
	while (Macro_Check_Bit_Clear(TIM2->SR, 0));

	Macro_Clear_Bit(TIM2->CR1, 0);
}

int Timer2_IsTimeout(void)
{
	if(Macro_Check_Bit_Set(TIM2->SR, 0))
	{
		Macro_Clear_Bit(TIM2->SR, 0);
		return 1;
	}
	else
	{
		return 0;
	}
}

void Timer2_Stop(void)
{
	Macro_Clear_Bit(TIM2->CR1, 0);
}

#define TIM5_FREQ					(8000000)			// Hz
#define TIM5_TICK					(1000000/TIM3_FREQ)	// usec
#define TIME5_PLS_OF_1ms			(1000/TIM3_TICK)

void Timer5_Out_Pwm_Generator(int duty)
{
	// Timer 주파수가 TIM3_FREQ가 되도록 PSC 설정
	TIM5->PSC = (unsigned int)(TIMXCLK/(double)TIM5_FREQ + 0.5) - 1;
	// 요청한 주파수가 되도록 ARR 설정
	//TIM3->ARR = freq * TIME3_PLS_OF_1ms;
	TIM5->ARR = (int)(((double)TIM5_FREQ / PWM_INPUT_FREQ + 0.5)-1);
	// Duty Rate 50%가 되도록 CCR3 설정
	TIM5->CCR3 = (double)(TIM5->ARR / 100) * duty;
	// Manual Update(UG 발생)
	Macro_Set_Bit(TIM5->EGR, 0);
	// Down Counter, Repeat Mode, Timer Start
	Macro_Set_Bit(TIM5->CR1, 0);
	
}


