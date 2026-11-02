#ifndef _LED_H     //if not define  //防止重定义
#define _LED_H


#include "stm32f10x.h"
#include "delay.h"

#define LED1_OFF GPIO_SetBits(GPIOB, GPIO_Pin_9)    //输出高电平1
#define LED1_ON  GPIO_ResetBits(GPIOB, GPIO_Pin_9)  //输出低电平0
#define LED2_OFF GPIO_SetBits(GPIOB, GPIO_Pin_8)    //输出高电平1
#define LED2_ON  GPIO_ResetBits(GPIOB, GPIO_Pin_8)  //输出低电平0
#define LED3_OFF GPIO_SetBits(GPIOA, GPIO_Pin_15)    //输出高电平1
#define LED3_ON  GPIO_ResetBits(GPIOA, GPIO_Pin_15)  //输出低电平0

#define LED1_OVERTURN	GPIOB->ODR ^= (1<<9)   //1 0
#define LED2_OVERTURN	GPIOB->ODR ^= (1<<8)
#define LED3_OVERTURN	GPIOA->ODR ^= (1<<15)


/********函数声明位置**********/
void Led_Init(void);
void Led_Change(void);
void Led_Flow(u32 time);
void Led_Breath(void);


#endif    //结束定义

