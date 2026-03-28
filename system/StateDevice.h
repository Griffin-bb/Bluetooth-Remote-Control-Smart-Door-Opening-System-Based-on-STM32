#ifndef __STATEDEVICE_H
#define __STATEDEVICE_H

#define State_Normal_Operation            0         //正常运行状态，可直接输入密码
#define State_Setting_LED_Luminance       1         //修改设备指示灯亮度状态
#define State_Setting_Password            2         //设置密码状态

extern uint8_t Device_State;
void Set_Device_State(uint8_t Device_NewState);
uint8_t Get_Device_State(void);

#endif
