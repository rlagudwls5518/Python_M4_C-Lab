#include "device_driver.h"
#include <stdio.h>

static void Sys_Init(int baud) 
{
	SCB->CPACR |= (0x3 << 10*2)|(0x3 << 11*2); 
	Clock_Init();
	Uart2_Init(baud);
	setvbuf(stdout, NULL, _IONBF, 0);
	LED_Init();
	Timer2_Init();
	Timer5_Init();
	Key_Poll_Init();
	Motor_Init();
}

#if 1
void Main(void)
{
	Sys_Init(115200);
	printf("\nMOTER_PROJECT\n");

	int lock = 0;

	for(;;){
		
		if((lock == 0) && Key_Get_Pressed())
		{
			
			Timer2_Start(3000);
			lock = 1;    
		}

		if((lock == 1) && Timer2_IsTimeout() && Key_Get_Pressed())
		{
			Timer2_Stop();
			
			Motor_Main(1);  
			lock = 2;         
		}

		if((lock == 1) | (lock == 2)  && !Key_Get_Pressed())
		{
			if(lock == 1){
				
				Motor_ProcessState();
				Motor_Main(0);
			}
			lock = 0;
		}
	
	}
	
}
#endif

