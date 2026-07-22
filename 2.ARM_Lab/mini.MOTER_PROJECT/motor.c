#include "device_driver.h"


MotorState prev_state = MOTOR_STOP;
MotorState curr_state = MOTOR_STOP;

void Motor_Init(void){
	GPIOA->MODER = ((GPIOA->MODER & ~0xF) | 0x05);//PA0,1 alternate function
	GPIOA->OTYPER &= ~0x3;
}
void Motor_Main(int flag){
    

    if(flag){
        
        Motor_Stop();
        Timer2_Delay(1000);
        prev_state = MOTOR_STOP;
        return;
    }


    if(curr_state == MOTOR_CCW){
        
        Motor_RotateCCW(); 
    }
    else if(curr_state == MOTOR_CW){
        
        Motor_RotateCW();
    }
}

void Motor_ProcessState(){
    
    if(prev_state == MOTOR_STOP && curr_state == MOTOR_STOP){
        
        prev_state = MOTOR_CCW;
        curr_state = MOTOR_CCW;
    }
    else if(prev_state == MOTOR_STOP){
        
        prev_state = curr_state;
    }
    else if(prev_state == MOTOR_CW){
        
        prev_state = MOTOR_CCW;
        curr_state = MOTOR_CCW;
    }
    else if(prev_state == MOTOR_CCW){
    
        prev_state = MOTOR_CW;
        curr_state = MOTOR_CW;
    }
}

void Motor_Stop(){
    GPIOA->ODR &= ~0x3; 
}

void Motor_RotateCW(void){
    GPIOA->ODR = 0x1;
}

void Motor_RotateCCW(void){
    GPIOA->ODR = 0x2;
}

// void Motor_Left(int duty)
// {

// }
// void Motor_Right(int duty)
// {

// }

	