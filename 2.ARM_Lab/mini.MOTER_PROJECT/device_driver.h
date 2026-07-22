#include "stm32f4xx.h"
#include "option.h"
#include "macro.h"
#include "malloc.h"

#define PWM_INPUT_FREQ       10000
#define MOTOR_SPEED_INIT     50
#define MOTOR_SPEED_UP       5
#define MOTOR_SPEED_STEP(x)  ((MOTOR_SPEED_UP) + ((MOTOR_SPEED_INIT) * (x)))

typedef enum
{
    MOTOR_STOP,
    MOTOR_CW,
    MOTOR_CCW
} MotorState;

extern MotorState prev_state;
extern MotorState curr_state;


// Uart.c

extern void Uart2_Init(int baud);
extern void Uart2_Send_Byte(char data);
extern char Uart2_Get_Pressed(void);

extern void Uart1_Init(int baud);
extern void Uart1_Send_Byte(char data);
extern void Uart1_Send_String(char *pt);
extern void Uart1_Printf(char *fmt,...);
extern char Uart1_Get_Char(void);
extern char Uart1_Get_Pressed(void);

// SysTick.c

extern void SysTick_Run(unsigned int msec);
extern int SysTick_Check_Timeout(void);
extern unsigned int SysTick_Get_Time(void);
extern unsigned int SysTick_Get_Load_Time(void);
extern void SysTick_Stop(void);

// Led.c

extern void LED_Init(void);
extern void LED_On(void);
extern void LED_Off(void);

// Clock.c

extern void Clock_Init(void);

// Key.c

extern void Key_Poll_Init(void);
extern int Key_Get_Pressed(void);
extern void Key_Wait_Key_Released(void);
extern void Key_Wait_Key_Pressed(void);

// Timer.c

extern void Timer5_Init(void);
extern void Timer2_Init(void);
extern void Timer2_Start(int time);
extern void Timer2_Stop(void);
extern void Timer5_Out_Pwm_Generator(int duty);
extern void Timer2_Delay(int time);
extern int Timer2_IsTimeout(void);

//motor.c
extern void Motor_Init(void);
extern void Motor_Main(int flag);
extern void Motor_Stop(void);
extern void Motor_Left(int duty);
extern void Motor_Right(int duty);
extern void Motor_RotateCW(void);
extern void Motor_RotateCCW(void);
extern void Motor_ProcessState(void);