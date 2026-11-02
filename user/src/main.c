#include "main.h"


int voice_updata = 0;  //烧录语音固件标记

int main(void)
{
	
	
	/*******函数初始化，只执行一次*******/
	Led_Init();       	//led初始化
	Key_Init();       	//key初始化
	Rgb_Init();					//rgb初始化
	Rain_Init();				//rain初始化
	
	/*********进入语音固件下载模式**********/
	//(1)长按key1不放，点击下载代码，下载完放开按键
	//目的是让芯片进入语音烧录模式
	if(KEY1)
	{
		LED1_ON;
		voice_updata = 1;
	}
	
	/***************************************/
	
	usb_vcp_init();		  //USB虚拟串口初始化
	Voice_Init(9600);   //voice初始化
	
	
	while(1)
	{
		Voice_Rec();
	}
}












