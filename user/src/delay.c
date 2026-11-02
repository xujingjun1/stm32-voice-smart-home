#include "delay.h"

/*****************************
*函数名	 :delay_us
*函数功能:机器指令实现延时
*函数参数:u32 utime  需要延时的时长
*返回值	 :void
*函数描述：1/72MHz=13.88ns  * 72 = 1us
*****************************/
void delay_us(u32 utime)  //1us
{
	while(utime--)
	{
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
		__nop();__nop();
	}	
}

/***********************************************
*函数名	 :delay_ms
*函数功能:机器指令实现延时
*函数形参:u32 mtime  需要延时的时长
*返回值	 :void
*函数描述:
***********************************************/
void delay_ms(u32 mtime)   //delay_ms(1000)
{
	while(mtime--)
	{
		delay_us(1000);
	}
}
