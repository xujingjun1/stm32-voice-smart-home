#include "led.h"


/*
	函数功能：led引脚初始化
	函数参数：无
	函数返回值：无
	备注：
			LED1  -- PB9      引脚输出低电平，led亮，高电平熄灭
			LED2	-- PB8			引脚输出低电平，led亮，高电平熄灭
			LED3  -- PA15     引脚输出低电平，led亮，高电平熄灭
*/
void Led_Init(void)
{
	//1.配置时钟信号
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);  //端口B时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);        //复用为传输功能
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);    //解除默认功能
	
	//2.配置GPIO控制器
	//Configurate 和 Initializes相似的作用，配置初始化（配置功能）
	//快捷查找方式：选中内容，ctrl+f快速查找
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;  //推挽输出模式
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_9 | GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;   //低速
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_15;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//引脚初始化后，默认输出低电平信号 
	//改为默认关闭，需要的时候再开启
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;
	//ALT + SHIFT + 鼠标左键拖选 -- 选择多行操作
}

/*
	闪烁功能
*/
void Led_Change(void)
{
	LED1_ON;
	delay_ms(500);
	LED1_OFF;
	delay_ms(500);
}
	

/*
	滚动功能
*/
void Led_Flow(u32 time)
{
	LED1_OFF;
	LED2_ON;
	delay_ms(time);
	LED2_OFF;
	LED3_ON;
	delay_ms(time);
	LED1_ON;
	LED3_OFF;
	delay_ms(time);
}


/*
	呼吸功能
	亮 -》暗   暗 -》 亮
*/
void Led_Breath(void)
{
	//暗-》亮
	for(u32 i = 0; i < 1000; i++)
	{
		LED3_ON;
		delay_us(i);         //  0    1    2   ...  1000
		LED3_OFF;
		delay_us(1000 - i);  //  1000 999  998 ...  0
	}
	//亮 -》暗
	for(u32 i = 0; i < 1000; i++)
	{
		LED3_ON;
		delay_us(1000 - i);  //  1000 999  998 ...  0      
		LED3_OFF;
		delay_us(i);  			 //  0    1    2   ...  1000
	}
}





