#include "device_driver.h"
#include <stdio.h>

static void Sys_Init(int baud) 
{
	SCB->CPACR |= (0x3 << 10*2)|(0x3 << 11*2); 
	Clock_Init();
	Uart2_Init(baud);
	setvbuf(stdout, NULL, _IONBF, 0);
	LED_Init();
	Key_Poll_Init();
}

#if 0

void Main(void)
{
	Sys_Init(115200);
	printf("TIM2 stopwatch test\n");

	int i;

	for(i = 1; i <= 10; i++)
	{
		i % 2 ? LED_On() : LED_Off();

		TIM2_Stopwatch_Start();
		SysTick_Run(100 * i);
		while(!SysTick_Check_Timeout());
		SysTick_Stop();

		unsigned int r = TIM2_Stopwatch_Stop();

		printf("[%d] Elapsed Time = %f msec\n", i, r/1000.);
	}
}

#endif

#if 0

void Main(void)
{
	Sys_Init(115200);
	printf("TIM2 delay test\n");

	for(;;)
	{
		LED_On();
		TIM2_Delay(1000);
		printf(".");

		LED_Off();
		TIM2_Delay(1000);
		printf(".");
	}
}

#endif

#if 0

void Main(void)
{
	Sys_Init(115200);
	printf("TIM2 long delay test\n");

	for(;;)
	{
		LED_On();
		TIM2_Delay(5000);
		printf(".");

		LED_Off();
		TIM2_Delay(5000);
		printf(".");
	}
}

#endif

#if 0

void Main(void)
{
	Sys_Init(115200);
	printf("TIM4 repeat timeout test\n");

	int i = 1, j = 1;

	TIM4_Repeat(500);
	SysTick_Run(500);

	for(;;)
	{
		if(TIM4_Check_Timeout())
		{
			printf("Timer4 [%d]\n", i++);
			if(i > 20) TIM4_Stop();
		}

	    if(SysTick_Check_Timeout())
	    {
			printf("SysTick [%d]\n", j++);
			if(j > 20) SysTick_Stop();
	    }
	}
}

#endif

#if 0

void Main(void)
{
	Sys_Init(115200);
	printf("TIM4 variable interval test\n");

	int i = 1;
	TIM4_Repeat(50);

	for(;;)
	{
		if(TIM4_Check_Timeout())
		{
			printf("[%d]\n", i++);
			if(i > 20) i = 1;
			TIM4_Change_Value(50 * i);
			i % 2 ? LED_On() : LED_Off();
		}
	}
}

#endif

#if 1
void Main(void)
{
	Sys_Init(115200);
	printf("\nUART Echo-Back Test1\n");
	int lock = 0;
	int dir =0;
	
	//Uart1_Init(115200);
	GPIOA->MODER = ((GPIOA->MODER & ~0xF) | 0x5);
	GPIOA->OTYPER &= ~0x3;

	GPIOC->MODER = ((GPIOC->MODER & ~(0x3 << 26)) | (0x0 << 26));

	for(;;){

		if((lock == 0) && Key_Get_Pressed())
		{
			TIM2_Stopwatch_Start_value(3000);
			lock = 1;    
		}

		if((lock == 1) && TIM2_Check_Timeout() && Key_Get_Pressed())
		{
			GPIOA->ODR &= ~0x3; 
			TIM2_Stop();
			lock = 2;           
		}

		if(((lock == 1) || (lock == 2) ) && !Key_Get_Pressed())
		{
			if(lock == 1){
				GPIOA->ODR &= ~0x3;
				TIM2_Delay(1000);
						
				if(dir)
				{
					GPIOA->ODR |= 0x1; 
					dir = 0;
				}
				else
				{
					GPIOA->ODR |= 0x2; 
					dir = 1;
				}
			}
			lock = 0;
		}
	
	}
	
}
#endif
