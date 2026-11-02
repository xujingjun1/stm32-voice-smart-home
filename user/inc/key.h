#ifndef _KEY_H     //if not define  //防止重定义
#define _KEY_H


#include "stm32f10x.h"
#include "delay.h"



#define KEY1 (!GPIO_ReadInputDataBit(GPIOA,  GPIO_Pin_5))  //1  0
#define KEY2 (!GPIO_ReadInputDataBit(GPIOA,  GPIO_Pin_6))
#define KEY3 (!GPIO_ReadInputDataBit(GPIOA,  GPIO_Pin_7))





/********函数声明位置**********/
void Key_Init(void);
u8 key_scan(void) ;

#endif    //结束定义

