#include "device_driver.h"
#include <stdio.h>

static void Sys_Init(int baud) 
{
	SCB->CPACR |= (0x3 << 10*2)|(0x3 << 11*2); 
	Uart2_Init(baud);	
	setvbuf(stdout, NULL, _IONBF, 0);
}

#if 1

#define GPIOA_MODER		(*(unsigned long *)0x40020000)
#define GPIOA_OTYPER	(*(unsigned long *)0x40020004)
#define GPIOA_ODR		(*(unsigned long *)0x40020014)

void Main(void)
{
	Sys_Init(115200);
	printf("LED Toggling Test #1\n");

	GPIOA_MODER = 0x1 << 10;
	GPIOA_OTYPER = 0x0 << 5;

	volatile int i;

	for(;;) //무한 반복문 while(1) 쓰면 안됨
	{
		GPIOA_ODR = 0x1 << 5; 
		for(i=0; i<0x40000; i++);
		//딜레이 하는 역할인데 최적화가 되어서  i = 0x4000이 들어가진다
		//1. 컴파일러에 최적화 레벨을 낮춘다
		//make 파일에서 CFLAGS -O0으로 낮춘다
		// 이거할라고 전부다 최적화를 낮춰서  다시 원상복구하고 변수에 volatile을 추가한다

		//디버그 모드와 릴리즈 모드의 차이??
		// 내가 짠 프로그램은 디버그모드로 되어있으면 개발자의 코드를 최대한 존중 -> 최적화레벨이 낮음
		//릴리즈 모드는 양산형이기때문에 최적화가 잘됨
		//나중에 제품 출시 두달전에 릴리즈모드로 최적화해볼까 하지만 대부분 귀찮아서 대부분 디버그모드로 양산한다 
		
		//원하는 소프트웨어를 만들었는데 cpu나 rom ram 용량이 꽉찼다면
		//만약 제품개발하는 개발자라면 삼성의 프린트사업부 에서 잉크제품을 개발하는데 초도개발자가 개발을 하고 첫모델을 개발해놓고 이모델ㅇ 10-20년 개발이될까
		//끊임없이 부가기능을 추가해야함
		//처음에 프로그램을 작성했을때 프로그램 용량량을 상당히 여유를 남겨놔야 업그레이드할때 여유가있다
		//1. 최적화레벨을 맥시멈으로
		//2. vilataile을 쓰자

		
		GPIOA_ODR = 0x0 << 5; 
		for(i=0; i<0x40000; i++);
	}
}

#endif

#if 0

#define TIMER   (*(unsigned long *)0xE000E018)

void Main(void)
{
	int i;
	unsigned long a[10];

	Sys_Init(115200);
	printf("Timer Access #1\n");

	SysTick_Run();

	for(i=0; i<10; i++)
	{
		a[i] = TIMER;
		printf("%d => %#.8X\n", i, a[i]);
	}
}

#endif

#if 0

#define TIMER   (*(unsigned long *)0xE000E018)

void Main(void)
{
	int i;
	unsigned long a[10];

	Sys_Init(115200);
	printf("Timer Access #2\n");

	SysTick_Run();

	for(i=0; i<10; i++)
	{
		a[i] = TIMER;
	}

	for(i=0; i<10; i++)
	{
		printf("%d => %#.8X\n", i, a[i]);
	}
}

#endif

#if 0

#define TIMER   (*(volatile unsigned long *)0xE000E018)

void Main(void)
{
	int i;
	unsigned long a[10];

	Sys_Init(115200);
	printf("Timer Access #3\n");

	SysTick_Run();

	for(i=0; i<10; i++)
	{
		a[i] = TIMER;
	}

	for(i=0; i<10; i++)
	{
		printf("%d => %#.8X\n", i, a[i]);
	}
}

#endif

#if 0

#define GPIOA_MODER		(*(volatile unsigned long *)0x40020000)
#define GPIOA_OTYPER	(*(volatile unsigned long *)0x40020004)
#define GPIOA_ODR		(*(volatile unsigned long *)0x40020014)

void Main(void)
{
	Sys_Init(115200);
	printf("LED Toggling Test #2\n");

	GPIOA_MODER = 0x1 << 10;
	GPIOA_OTYPER = 0x0 << 5;

	volatile int i;

	for(;;)
	{
		GPIOA_ODR = 0x1 << 5; 
		for(i=0; i<0x40000; i++);
		
		GPIOA_ODR = 0x0 << 5; 
		for(i=0; i<0x40000; i++);
	}
}

#endif
