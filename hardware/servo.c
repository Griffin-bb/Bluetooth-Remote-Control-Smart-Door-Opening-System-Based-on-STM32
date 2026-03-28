#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "Delay.h"

void Servo_Init(void)
{
    PWM_Init();
}

void angle(float Angle)
{
    PWM_SetCompare1(Angle + 45);
}

/**@define 开门函数
  *
  *@brief NULL
  *@attention NULL
  */
void Door_Open(void)
{
	angle(90);	
	Delay_ms(1500);
	angle(0);
}
