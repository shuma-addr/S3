#include "H/SC93F843X_C.H"
#include "H/Function_Init.H"

/*****************************************************
*函数名称：void ADC_Init(void)
*函数功能：ADC初始化
*入口参数：void
*出口参数：void
*****************************************************/
unsigned int ADCValue = 0x0000;
void ADC_Init(void)
{
	ADCCON = 0X89;		//开启ADC，ADC采样频率为2M ,选择AIN9位ADC采样口
	ADCCFG0 = 0x00;   //设置AIN9作为采样口
	ADCCFG1 = 0X02;   //设置AIN9作为采样口
//	IE = 0X40;        //开启ADC中断
	EA = 1;

	ADCCON |= 0X40;   //开始ADC转换
	while(!(ADCCON&0x10));	         		 //等待 ADC转换完成;
	ADCValue=(ADCVH<<4)+(ADCVL>>4);
}

/*****************************************************
*函数名称：void ADC_TS_Init(void)
*函数功能：ADC采集温度传感器电压值
*入口参数：void
*出口参数：void
*****************************************************/
void ADC_TS_Init(void)
{
	unsigned int AD_TS0=0,AD_TS1=0,AD_TSSUM=0;
	
	ADCCON = 0x8E;		//开启ADC，ADC采样频率为2M ,ADC输入为温度传感器输出
	ADCCFG0 = 0x00;   //
	ADCCFG1 = 0X00;   //
	while(1)
	{
		TSCFG = 0X80;
		ADCCON |= 0x40;   //开始ADC转换		
		while(!(ADCCON&0x10));
		ADCCON &= 0xEF;   //清中断标志位
		AD_TS0 = (ADCVH<<4)+(ADCVL>>4);  //第一次温度传感器数值
		
		TSCFG |= 0X01;
		ADCCON |= 0x40;   //开始ADC转换		
		while(!(ADCCON&0x10));
		ADCCON &= 0xEF;   //清中断标志位
		AD_TS1 = (ADCVH<<4)+(ADCVL>>4);  //第二次温度传感器数值
		
		AD_TSSUM = (AD_TS0+AD_TS1)/2;    //温度传感器数值
	}
}
