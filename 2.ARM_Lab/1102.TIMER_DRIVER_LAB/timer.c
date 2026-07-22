#include "device_driver.h"
#include "option.h"
#define TIM2_TIC		20 					//usec
#define TIM2_FREQ		(1000000./TIM2_TIC) //Hz
#define TIM2_1ms_PLS 	(TIM2_FREQ/1000.)
#define TIM2_MAX 		(0xffffu)

#define TIM4_FREQ		(1000000./TIM2_TIC) //Hz
#define TIM4_1ms_PLS 	(TIM2_FREQ/1000.)

void TIM2_Stopwatch_Start(void)
{
	Macro_Set_Bit(RCC->APB1ENR, 0);

	// TIM2 CR1 설정: down count, one pulse
	TIM2->CR1 = (0x1 << 4)|(0x1 << 3);
	// PSC 초기값 설정 => 20usec tick이 되도록 설계 (50KHz)
	TIM2->PSC = (HCLK/50000) -1;
	//TIM2->PSC = (int)(TIMXCLK/TIM2_FREQ +0.5) - 1;

	// ARR 초기값 설정 => 최대값 0xFFFFFFFF 설정
	TIM2->ARR = 0xffffffff;

	// UG 이벤트 발생
	Macro_Set_Bit(TIM2->EGR,0);
	// TIM2 start
	Macro_Set_Bit(TIM2->CR1, 0);

}

void TIM2_Stopwatch_Start_value(int time)
{
	Macro_Set_Bit(RCC->APB1ENR, 0);

	// TIM4 CR1: ARPE=0, down counter
	TIM2->CR1 = (0x1 << 4)|(0x1 << 3);
	// PSC(50KHz),  ARR(reload시 값) 설정
	TIM2->PSC = (int)(TIMXCLK/TIM4_FREQ +0.5) - 1;
	TIM2->ARR = time * TIM4_1ms_PLS;
	// UG 이벤트 발생
	Macro_Set_Bit(TIM2->EGR,0);
	// Update Interrupt Pending Clear
	Macro_Clear_Bit(TIM2->SR, 0);
	// TIM4 start
	Macro_Set_Bit(TIM2->CR1, 0);

}

unsigned int TIM2_Stopwatch_Stop(void)
{
	unsigned int time;

	// TIM2 stop
	Macro_Clear_Bit(TIM2->CR1, 0);
	// CNT 초기 설정값 (0xffff)와 현재 CNT의 펄스수 차이를 구하고
	// 그 펄스수 하나가 20usec이므로 20을 곱한값을 time에 저장
	// 계산된 time 값을 리턴(단위는 usec)
	time = (TIM2->ARR - TIM2->CNT) * TIM2_TIC;
	return time;

}

#if 0
void TIM2_Delay(int time)
{
	Macro_Set_Bit(RCC->APB1ENR, 0);

	// TIM2 CR1 설정: down count, one pulse
	TIM2->CR1 = (0x1 << 4)|(0x1 << 3);
	// PSC 초기값 설정 => 20usec tick이 되도록 설계 (50KHz)
	TIM2->PSC = (int)(TIMXCLK/TIM2_FREQ +0.5) - 1;
	// ARR 초기값 설정 => 요청한 time msec에 해당하는 초기값 설정
	TIM2->ARR = time * TIM2_1ms_PLS;
	// UG 이벤트 발생
	Macro_Set_Bit(TIM2->EGR,0);
	// UIF(Update Interrupt Pending) Clear
	Macro_Clear_Bit(TIM2->SR, 0);
	// TIM2 start
	Macro_Set_Bit(TIM2->CR1, 0);
	// Wait timeout
	while(!(TIM2->SR  & 0x1));
	// TIM2 Stop
	Macro_Clear_Bit(TIM2->CR1, 0);
}
#endif
#if 1
void TIM2_Delay(int time)
{
	Macro_Set_Bit(RCC->APB1ENR, 0);

	// TIM2 CR1 설정: down count, one pulse
	TIM2->CR1 = (0x1 << 4)|(0x1 << 3);
	// PSC 초기값 설정 => 20usec tick이 되도록 설계 (50KHz)
	TIM2->PSC = (int)(TIMXCLK/TIM2_FREQ +0.5) - 1;
	// ARR 초기값 설정 => 요청한 time msec에 해당하는 초기값 설정
	unsigned int pls = time * TIM2_1ms_PLS;
	int n = pls / TIM2_MAX; 
	int m = pls % TIM2_MAX;
	int i;

	for (i = 0; i < n; i++){
		TIM2->ARR = TIM2_MAX;
		Macro_Set_Bit(TIM2->EGR,0);
		Macro_Clear_Bit(TIM2->SR, 0);
		Macro_Set_Bit(TIM2->CR1, 0);
		while(!(TIM2->SR  & 0x1));
	}
	TIM2->ARR = m;
	Macro_Set_Bit(TIM2->EGR,0);
	Macro_Clear_Bit(TIM2->SR, 0);
	Macro_Set_Bit(TIM2->CR1, 0);
	while(!(TIM2->SR  & 0x1));

	// TIM2->ARR = time * TIM2_1ms_PLS;
	// // UG 이벤트 발생
	// Macro_Set_Bit(TIM2->EGR,0);
	// // UIF(Update Interrupt Pending) Clear
	// Macro_Clear_Bit(TIM2->SR, 0);
	// // TIM2 start
	// Macro_Set_Bit(TIM2->CR1, 0);
	// // Wait timeout
	// while(!(TIM2->SR  & 0x1));
	// TIM2 Stop
	Macro_Clear_Bit(TIM2->CR1, 0);
}
#endif
void TIM2_Repeat(int time)
{
	Macro_Set_Bit(RCC->APB1ENR, 2);

	// TIM4 CR1: ARPE=0, down counter, repeat mode
	TIM2->CR1 = (0x1 << 4);
	// PSC(50KHz),  ARR(reload시 값) 설정
	TIM2->PSC = (int)(TIMXCLK/TIM4_FREQ +0.5) - 1;
	TIM2->ARR = time * TIM4_1ms_PLS;
	// UG 이벤트 발생
	Macro_Set_Bit(TIM2->EGR,0);
	// Update Interrupt Pending Clear
	Macro_Clear_Bit(TIM2->SR, 0);
	// TIM4 start
	Macro_Set_Bit(TIM2->CR1, 0);

}

int TIM2_Check_Timeout(void)
{
	// 타이머가 timeout 이면 1 리턴, 아니면 0 리턴
	if(TIM2->SR & 0x1){
		Macro_Clear_Bit(TIM2->SR, 0);
		return 1;
	}
	else{
		return 0;
	}
	
}

void TIM2_Stop(void)
{
	Macro_Clear_Bit(TIM2->CR1, 0);
}

void TIM4_Change_Value(int time)
{
	TIM4->ARR = 50 * time;
}
