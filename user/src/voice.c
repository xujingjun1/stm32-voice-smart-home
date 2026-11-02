#include "voice.h"


/*
	函数功能：usart3-voice引脚初始化
	函数参数：无
	函数返回值：无
	备注：
		PB10  -- USART3_TX
		PB11  -- USART3_RX
*/
void Voice_Init(u32 baud)
{
	//1.时钟信号
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	//2.引脚配置
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF_PP;          //复用输出推挽模式
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_10;  						 //指定工作引脚
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;         //高速
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN_FLOATING;    //浮空输入模式
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_11;  						 //指定工作引脚
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	//3.时钟信号
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
	//4.串口控制器 -- 如何配置？串口协议格式：波特率115200 数据位：8 校验位：无 停止位：1
	//函数文件usart.c中
	USART_InitTypeDef USART_InitStruct = {0};
	USART_InitStruct.USART_BaudRate 					  = baud;   											  //波特率115200
	USART_InitStruct.USART_HardwareFlowControl  = USART_HardwareFlowControl_None; //无硬件流控制模式
	USART_InitStruct.USART_Mode       					= USART_Mode_Rx | USART_Mode_Tx;  //使能发送和接收模式
	USART_InitStruct.USART_Parity     					= USART_Parity_No;								//无奇偶校验
	USART_InitStruct.USART_StopBits   					= USART_StopBits_1;								//1bit停止位
	USART_InitStruct.USART_WordLength 					= USART_WordLength_8b;						//8bit字长
	USART_Init(USART3, &USART_InitStruct);
	
	//6.中断控制器初始化
	//分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  // 7-2
	
	NVIC_InitTypeDef NVIC_InitStruct = {0};
	NVIC_InitStruct.NVIC_IRQChannel    								= USART3_IRQn;    //串口3中断通道
	NVIC_InitStruct.NVIC_IRQChannelCmd 								= ENABLE;					//使能中断通道
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;							//抢占值1
	NVIC_InitStruct.NVIC_IRQChannelSubPriority        = 2;							//响应值2
	NVIC_Init(&NVIC_InitStruct);
	
	//7.使能接收中断 和 空闲中断
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);
	
	//5.打开usart控制器
	USART_Cmd(USART3, ENABLE);
}



/*
	串口中断服务函数
	跟普通比较：名字固定；
							函数无参无返回值；
							不需要调用，随机发生（只要触发条件满足）；
*/
u8 Res;
u8 USART3_RX_CMD = 0;
void USART3_IRQHandler(void)
{
	//接收中断
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //AA
	{
		//清除中断标记位
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
		
		Res = USART_ReceiveData(USART3);   //读取数据 //AA AB 02 CC
		USB_SendData(Res);    //通过虚拟串口传输
		USART3_RX_CMD = Res; 
	}		
	//空闲中断
	if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)  //没有数据--空闲
	{
		//清除中断标记位
		USART3->SR;
		USART3->DR;
	}
}

//接收指令，判断功能
void Voice_Rec(void)
{
	switch(USART3_RX_CMD)   //判断指令
	{
		case 0xAA: LED1_ON; LED2_ON; LED3_ON; break;
		case 0xAB: LED1_OFF; LED2_OFF; LED3_OFF; break;
		case 0xAC: Rgb_Write_Color(255,0,0); break;
		case 0xAD: Rgb_Write_Color(0,255,0); break;
		case 0xAE: Rgb_Write_Color(0,0,255); break;
		case 0xAF: Rgb_Write_Color(0,0,0); break;
		default: break;
	}
	
	 RGB_DATA_L;
   delay_us(60); // 稍微多给一点余量，防止闪烁
}































