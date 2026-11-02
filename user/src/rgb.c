#include "rgb.h"


/*
	函数功能：rgb引脚初始化
	函数参数：无
	函数返回值：无
	备注：
			WS2812_DIN  -- PB9 推挽输出模式     
*/
void Rgb_Init(void)
{
	//1.配置时钟信号
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //端口B时钟使能
	
	//2.配置GPIO控制器
	//Configurate 和 Initializes相似的作用，配置初始化（配置功能）
	//快捷查找方式：选中内容，ctrl+f快速查找
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;  //推挽输出模式
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;   
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	RGB_DATA_H;
	

//	
//	Rgb_Write_Color(0,0,0);
//	Rgb_Write_Color(0,0,0);
//	delay_us(60);

}


/*
	函数功能：发送24bit数据 -- 先处理8bit
	函数参数：u8 三基色数据
	函数返回值：无
	备注：数据高位先发
方式1：
data = 1011 0111 & 0x80 -》 1000 0000

i = 0；1011 0111 & 1000 0000 = 1000 0000  结果为真 1
i	= 1；1011 0111 & 0100 0000 = 0000 0000  结果为假 0
i = 2；1011 0111 & 0010 0000 = 0010 0000  结果为真 1
i = 3；1011 0111 & 0001 0000 = 0001 0000  结果为真 1
......

方式2：
data = 1011 0111 & 0x80
1011 0111 & 1000 0000 = 1000 0000    1

data << 1
0110 1110 & 1000 0000 = 0000 0000    0
 
data << 1
1101 1100 & 1000 0000 = 1000 0000    1
......


0码：0.4us高电平+0.85us低电平
1码：0.85us高电平+0.4us低电平

850ns / 13.88 = ?
400ns  / 13.88 = ?
*/
void Rgb_Send_Data(u8 data)
{
	for(u8 i = 0; i < 8; i++)
	{
		if(data & (0x80 >> i))
		{
			//得到 “1码”
			RGB_DATA_H;
			 // 约 45 个 NOP (配合代码开销，凑够 0.8us)
			__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
			__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
			__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
			__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
			__NOP(); __NOP(); __NOP(); __NOP(); __NOP();
			RGB_DATA_L;
			// 约 20 个 NOP
			__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
			__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
		}
		else
		{
			//得到 “0码”
			RGB_DATA_H;
			// 仅仅 15 个 NOP (确保高电平被迅速拉低，绝对不会被误认为 1)
			__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
			__NOP(); __NOP(); __NOP(); __NOP(); __NOP();
			RGB_DATA_L;
			// 约 45 个 NOP
			__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
			__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
			__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
			__NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP(); __NOP();
			__NOP(); __NOP(); __NOP(); __NOP(); __NOP();
		}
	}
}

/*
	函数功能：写入24bit数据到rgb内部
	函数参数：无
	函数返回值：无
	备注：按照GRB格式存储
*/
void Rgb_Write_Color(u8 r, u8 g, u8 b)   //255 255 255 -> 101.....
{
	u32 color = 0;   //最终有24bit
	
	//1.获取24bit数据后，将rgb三个颜色拼接为24bit
	color |= r << 16;   //color= 11111111 00000000 00000000
	color |= g << 8;
	color |= b;
	
	//2.将拼接好的数据按照GRB存放
	Rgb_Send_Data((color >> 8) & 0xff);  //写入绿色
	Rgb_Send_Data((color >> 16) & 0xff); //写入红色
	Rgb_Send_Data(color & 0xff);         //写入蓝色
}


//1.时序
//2.复位时间太长/太短
//3.数据发错















