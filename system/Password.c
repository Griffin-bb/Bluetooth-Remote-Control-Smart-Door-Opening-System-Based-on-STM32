#include "stm32f10x.h"                  // Device header
#include "HC_04BLE.h"
#include "Flash_Storage.h"
#include <string.h>

char Password[20];

/**@define 该函数用于设置开门密码
  *
  *@brief 传入New_Password即可将开门密码设为New_Password
  */
void Set_Password(char *New_Password)
{
	Store_String_In_Flash(New_Password);             //把用户发的新密码存进Flash
	strcpy(Password,New_Password);                   //把用户发的新密码赋给 @Password
}


void Password_Init(void)
{
	Get_String_From_Flash(Password,19);
}

/**@define 该函数用于给用户发送菜单
  *
  *@brief NULL
  */
void Send_Menu(void)                                 //把菜单发给用户
{
	HC_04BLE_printf("You can enter:\r\n");
	HC_04BLE_printf("1.[HELLO]\r\n");
	HC_04BLE_printf("2.[Password]\r\n");
	HC_04BLE_printf("3.[Set LED Luminance]\r\n");
	HC_04BLE_printf("4.[Set Password]\r\n");
}
