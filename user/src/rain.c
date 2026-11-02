#include "rain.h"

/*
函数功能:初始化ADC
返回值:无
参数:无
备注:ADC2_IN9    PA1
*/
void Rain_Init(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2,  ENABLE); //使能ADC时钟
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M
	
	/*初始化ADC2通道9 的IO口*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; /*模拟输入*/
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;
	GPIO_Init(GPIOA, &GPIO_InitStructure);       /*初始化*/

	

	/*初始化ADC2*/
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode               = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode       = DISABLE;					  //非扫描模式	
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;					  //关闭连续转换
	ADC_InitStructure.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None; //禁止触发检测，使用软件触发
	ADC_InitStructure.ADC_DataAlign          = ADC_DataAlign_Right;		  //右对齐	
	ADC_InitStructure.ADC_NbrOfChannel       = 1;						  //1个转换在规则序列中 也就是只转换规则序列1 
	ADC_Init(ADC2, &ADC_InitStructure);/*初始化*/
	
	ADC_Cmd(ADC2, ENABLE);/*开启ADC*/
	
	//校准--复位状态
	ADC_ResetCalibration(ADC2);                //重置指定的ADC的校准寄存器
	while(ADC_GetResetCalibrationStatus(ADC2));//获取ADC重置校准寄存器的状态
	
	ADC_StartCalibration(ADC2);                //开始指定ADC的校准状态
	while(ADC_GetCalibrationStatus(ADC2));     //获取指定ADC的校准程序

	ADC_SoftwareStartConvCmd(ADC2, ENABLE);    //使能或者失能指定的ADC的软件转换启动功能
}
/*
函数功能:获得adc的值
返回值:u32 value
参数:无
*/
u32 Get_Rain_value(void)
{
	ADC_RegularChannelConfig(ADC2, ADC_Channel_1,1,ADC_SampleTime_239Cycles5);//设置规则通道1 一个序列 采样时间 
	ADC_SoftwareStartConvCmd(ADC2, ENABLE);        //使能指定的ADC1的软件转换
	while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC)); //等待转换结束
	return ADC_GetConversionValue(ADC2);           //读取转换结果  -- 已经存在转换数据 -- 数字量（0-4095）
}
/*
函数功能:获得平均值
返回值:u32 value
参数:无
*/
float Get_Rain_average_value(void)
{
	float value = 0;   //存放转换值
	u8 i = 0;
	for(i = 0; i < 5; i++)
	{
		value += Get_Rain_value();   //提取5次转换值，使用平均值
	}
	value /= 5.0f;
	value = (value * 100.0f) / 4096.0f;   //转换为百分比
	return value;//返回值
	

}











