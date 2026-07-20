#include "device_driver.h"
#include <stdio.h>

static void Sys_Init(int baud) 
{
	SCB->CPACR |= (0x3 << 10*2)|(0x3 << 11*2); 
	Clock_Init();
	Uart2_Init(baud);
	setvbuf(stdout, NULL, _IONBF, 0);
	LED_Init();
}
#if 0
void Main(void)
{
	Sys_Init(115200);
	printf("\nUART Echo-Back Test\n");

	Uart1_Init(115200);

	char x, y;

	for(x = 'A'; x <= 'Z'; x++)
	{
		// 송신 버퍼가 비면 x의 글자를 출력
		
		
		// 수신 버퍼에 글자가 입력되면 y에 글자를 수신


		printf("%c ", y);
	}
}
#endif

#if 0
void Main(void)
{
	Sys_Init(115200);
	printf("\nUART Echo-Back Test1\n");

	Uart1_Init(115200);
// 수신이 있으면 그대로 송신(echo back)

	char x ;

	for (;;){

		while(!((USART1->SR >> 5) & 0x1));
		x = USART1->DR;

		while(!((USART1->SR >> 7) & 0x1));
		USART1->DR = x;
		printf("%d ",x);
	}
}
#endif

#if 1
void Main(void)
{
	Sys_Init(115200);
	printf("\nUART Echo-Back Test1\n");
	int lock = 0;
	

	
	//Uart1_Init(115200);
	GPIOA->MODER = ((GPIOA->MODER & ~0xF) | 0x5);
	GPIOA->OTYPER = ((GPIOA->OTYPER & ~0x3) | 0x0);

	GPIOC->MODER = ((GPIOC->MODER & ~(0x3 << 26)) | (0x0 << 26));
	GPIOA->ODR &= ~0x3;

	for(;;){
		volatile int i;

		if((lock == 0) && Key_Get_Pressed())
		{
			GPIOA->ODR &= ~0x3;
			for(i = 0; i< 0xffff; i++);
			GPIOA->ODR = 0x2;
			lock = 1;
		}
		
		else if((lock == 1) && Key_Get_Pressed())
		{
			GPIOA->ODR &= ~0x3;
			for(i = 0; i< 0xffff; i++);
			GPIOA->ODR = 0x1;
			lock = 0;
		}
	}
	
}
#endif
