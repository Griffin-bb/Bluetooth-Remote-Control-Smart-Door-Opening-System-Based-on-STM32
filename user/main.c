#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "servo.h"
#include "Delay.h"
#include "OLED.h"
#include "HC_04BLE.h"
#include "StateDevice.h"
#include "Password.h"

#include <string.h>
#include <stdlib.h>


/**@define 设置密码步骤标志位
  *@brief 0为等待输入正确原密码
  *@brief 1为原密码正确，开始设置新密码
  */
uint8_t SetState;
#define SetState_Waiting                  0             //正在等待用户输入正确原密码状态
#define SetState_EnterSetting             1             //原密码正确，开始设置新密码状态


 
int main(void)
{
	OLED_Init();
	LED_Init();
	Servo_Init();
	HC_04BLE_Init();
	Password_Init();
	
	
	HC_04BLE_printf("HELLO");
	
	angle(0);

	while(1)
	{
		if(HC_04BLE_Flag() == 1)
		{
			switch(Get_Device_State())
			{
/***********************************正常状态State_Normal_Operation***********************************************/
				case State_Normal_Operation:
					//
					if(strcmp(HC_04BLE_GetDate,"HELLO") == 0)                       //打招呼指令
					{
						HC_04BLE_printf("HELLO!!!ψ(｀∇´)ψ\r\n");
					}
					else if(strcmp(HC_04BLE_GetDate,Password) == 0)                 //开门指令
					{
						Door_Open();
						HC_04BLE_printf("Password correct,the door is open!!!ヾ(≧▽≦*)o\r\n");
					}
					else if(strcmp(HC_04BLE_GetDate,"Password") == 0)               //提示用户输入密码
					{
						HC_04BLE_printf("Please enter password:\r\n");
					}
					else if(strcmp(HC_04BLE_GetDate,"Set LED Luminance") == 0)      //设置指示灯亮度指令
					{
						Set_Device_State(State_Setting_LED_Luminance);
						HC_04BLE_printf("OK Please Send Luminance value:\r\n");
					}
					else if(strcmp(HC_04BLE_GetDate,"Set Password") == 0)           //设置密码指令
					{
						Set_Device_State(State_Setting_Password);
						HC_04BLE_printf("Please enter old password:\r\n");
					}
					else if(strcmp(HC_04BLE_GetDate,"menu") == 0)                   //查看菜单指令
					{
						Send_Menu();
					}

					else                                                            //用户指令不匹配提示
					{
						HC_04BLE_printf("Command error,please refer to the menu!!!\r\n");
						HC_04BLE_printf("You can enter [menu] to view the menu!!!\r\n");
					}
					break;
/********************************进入设置指示灯亮度状态State_Setting_LED_Luminance************************************/
				case State_Setting_LED_Luminance:
					LED_SetLuminance(atoi(HC_04BLE_GetDate));
					HC_04BLE_printf("Successfully set luminance %d !!!\r\n",atoi(HC_04BLE_GetDate));
					Set_Device_State(State_Normal_Operation);                       //返回正常状态
				    break;
/********************************进入设置密码状态State_Setting_Password***********************************************/
				case State_Setting_Password:
					switch (SetState)
					{
						case SetState_Waiting:     //等待输入原密码状态SetState_Waiting
							
							if(strcmp(HC_04BLE_GetDate,Password) == 0)              //输入原密码验证身份
							{
								HC_04BLE_printf("OK,Please enter new Password!!!\r\n");
								SetState = SetState_EnterSetting;
							}
							else if(strcmp(HC_04BLE_GetDate,"AIENSS") == 0)         //输入原密码验证身份(后门)
							{
								HC_04BLE_printf("OK,Please enter new Password!!!\r\n");
								SetState = SetState_EnterSetting;
							}

							else if(strcmp(HC_04BLE_GetDate,"return") == 0)         //取消设置密码，退出设置密码状态
							{
								Set_Device_State(State_Normal_Operation);
								HC_04BLE_printf("OK,Successfully return!!!\r\n");
							}
							else
							{
								HC_04BLE_printf("Password error!!!\r\n");           //密码错误提示词
								HC_04BLE_printf("You can enter [return] cancel setting!!!\r\n");
							}
							break;
						case SetState_EnterSetting:    //等待输入新密码状态SetState_EnterSetting
							if(strcmp(HC_04BLE_GetDate,"return") == 0)              //取消设置密码，退出设置密码状态
							{
								Set_Device_State(State_Normal_Operation);
								HC_04BLE_printf("OK,Successfully return!!!\r\n");
								HC_04BLE_printf("You can continu playing!!!\r\n");
							}
							else
							{
								Set_Password(HC_04BLE_GetDate);
								HC_04BLE_printf("OK,Successfully Set Password!!!\r\n");
								
								SetState = SetState_Waiting;
								Set_Device_State(State_Normal_Operation);           //设置密码成功，返回正常状态
							}
							break;
					}
					break;
			}
		}
		HC_04BLE_SLEEP_Countdown();                    //倒计时
	}
}
