#ifndef _RGB_H     //if not define  //防止重定义
#define _RGB_H


#include "stm32f10x.h"
#include "delay.h"



#define RGB_DATA_H  GPIO_SetBits(GPIOB, GPIO_Pin_9)    //输出高电平1
#define RGB_DATA_L  GPIO_ResetBits(GPIOB, GPIO_Pin_9)  //输出低电平0



/********函数声明位置**********/
void Rgb_Init(void);
void Rgb_Send_Data(u8 data);
void Rgb_Write_Color(u8 r, u8 g, u8 b);

#endif    //结束定义

