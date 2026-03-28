#include "stm32f10x.h"                  // Device header

#define State_Normal_Operation            0         //正常运行状态，可直接输入密码
#define State_Setting_LED_Luminance       1         //修改设备指示灯亮度状态
#define State_Setting_Password            2         //设置密码状态


/**@define 该变量为设备状态标志位
  *
  *@brief 置 0 表示设备处于正常状态，可直接输入密码
  *@brief 置 1 表示设备处于修改设备指示灯亮度状态
  *@brief 置 2 表示设备进入设置密码状态
  */
uint8_t Device_State = 0;




/**@define 该函数用于设置设备状态
  *
  *@brief 置 Device_NewState 则设备进入新设置的状态，可开始该状态可进行的操作
  *@brief Device_NewState的值可以是：
  *
  *@value State_Setting_LED_Luminance
  *@value State_Normal_Operation
  *
  */
void Set_Device_State(uint8_t Device_NewState)
{
	Device_State = Device_NewState;
}




/**@define 该函数用于返回状态机状态
  *
  *@brief 返回State_Setting_LED_Luminance表示设备处于调亮度状态
  *@brief 返回State_Normal_Operation表示设备处于正常状态
  */
uint8_t Get_Device_State(void)
{
	return Device_State;
}
