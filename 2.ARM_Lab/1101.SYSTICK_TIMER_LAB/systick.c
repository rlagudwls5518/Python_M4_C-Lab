#include "device_driver.h"

void SysTick_Run(unsigned int msec)
{
	// Timer 설정 : 인터럽트 발생 안함, clock source는 HCLK/8, Timer 정지
	SysTick->CTRL = 0;
	// 주어진 msec 값 만큼의 msec를 count하는 초기값 설정 (LOAD)
	SysTick->LOAD = msec * (int)((HCLK/8.) / 1000. + 0.5);
	// VAL 레지스터 값 초기화(0) 및 COUNTFLAG Clear
	SysTick->VAL = 0;
	// Timer Start (시작이 되면 자동으로 LOAD의 값을 VAL로 가져간다)
	SysTick->CTRL |= 0x1;

	//타이머의 주파수를 너무 많이 주면(고주파) 바로 끝나버리고  너무 적게 주면  정밀도가 떨어진다 

}

int SysTick_Check_Timeout(void)
{
	// Timer의 Timeout이 발생하면 참(1)리턴, 아니면 거짓(0) 리턴
	return ((SysTick->CTRL >> 16) & 0x1);

}

unsigned int SysTick_Get_Time(void)
{
	// Timer의 현재 count 값 리턴
	return SysTick->VAL;
}

unsigned int SysTick_Get_Load_Time(void)
{
	// Timer에 설정된 초기값을 리턴
	return SysTick->LOAD;

}

void SysTick_Stop(void)
{
	// Timer Stop
	SysTick->CTRL |= 0x0;

}
