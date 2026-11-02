#include "key.h"



/*
	函数功能：key引脚初始化
	函数参数：无
	函数返回值：无
	备注：
			KEY1  -- PA5      按键按下，接收低电平；按键松开，接收高电平
			KEY2	-- PA6			按键按下，接收低电平；按键松开，接收高电平
			KEY3  -- PA7      按键按下，接收低电平；按键松开，接收高电平
*/
void Key_Init(void)
{
	//1.时钟配置 -- 确定使用GPIO控制器  确定具体端口号
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	
	//2.GPIO控制器配置
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;  		//输入模式
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);

	
	//3.读取输入数据
}

/*
	函数功能：按键扫描
	函数参数：无
	函数返回值：u8  返回值为1 2 3
	备注：
*/
u8 key_scan(void)  //1 2 3
{
	u8 key_value = 0;   //返回键值
	static u8 key_flag = 1;   //未按下=1  按下=0
	
	if((KEY1 ||  KEY2 ||  KEY3) && key_flag)
	{
		//按下
		//消抖处理
		delay_ms(15);
		
		if(KEY1)
		{
			key_value = 1;
			key_flag = 0;
		}
		if(KEY2)
		{
			key_value = 2;
			key_flag = 0;
		}
		if(KEY3)
		{
			key_value = 3;
			key_flag = 0;
		}
	}
	else if(!KEY1 && !KEY2 && !KEY3 && key_flag == 0)
	{
		//松开
		key_flag = 1;
	}
	
	return key_value;
}







