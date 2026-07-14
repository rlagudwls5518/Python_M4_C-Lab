// 여기에 사용자 임의의 define을 작성하시오
#if 0
#define GPIOA_MODER		(*(unsigned long *)0x40020000)
#define GPIOA_OTYPER	(*(unsigned long *)0x40020004)
#define GPIOA_ODR		(*(unsigned long *)0x40020014)

void Main(void)
{
	// LED GPA[5]를 출력(General Push Pull) 모드로 설정하시오

	GPIOA_MODER = 0x400;
	GPIOA_OTYPER = 0x00;

	// GPA[5] LED를 ON 시키도록 설정하시오

	GPIOA_ODR = 0x20;
}
#endif

#if 1
#define GPIOA_MODER		(*(unsigned long *)0x40020000)
#define GPIOA_OTYPER	(*(unsigned long *)0x40020004)
#define GPIOA_ODR		(*(unsigned long *)0x40020014)

void Main(void)
{
	// LED GPA[7]를 출력(open_drain) 모드로 설정하시오

	GPIOA_MODER = 0x4000;
	GPIOA_OTYPER = 0x80;

	// GPA[7] LED를 ON 시키도록 설정하시오

	GPIOA_ODR = 0x00;
}
#endif
