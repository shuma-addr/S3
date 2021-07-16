#include "H/SC93F843X_C.H"
#include "H/Function_Init.H"

/*****************************************************
*函数名称：void Uart1_Init(void)
*函数功能：Uart1中断初始化
*入口参数：void
*出口参数：void
*****************************************************/
void Uart1_Init(void)
{
	OTCON = 0xC0;    //串行接口SSI选择Uart1通信
	SSCON0 = 0x50;   //设置通信方式为模式一，允许接收
	SSCON1 = 0x9C;   //波特率低位控制，在主频为24M时，波特率为9600
	SSCON2 = 0x00;   //波特率高位控制，在主频为24M时，波特率为9600
	IE1 = 0x01;      //开启SSI中断
  EA = 1;	
	while(1)
	{
		SSDAT = 0x55;
		delay(100);
	}
}

/*****************************************************
*函数名称：void TWI_Init(void)
*函数功能：TWI初始化
*入口参数：void
*出口参数：void
*****************************************************/
void TWI_Init(void)
{
	OTCON = 0x80;  //选择TWI模式
	SSCON0 = 0x80;  // ---- x---  0为不允许接收，1为允许接收
	SSCON1 = 0x01;  //xxxx xxxy  x为地址寄存器，y为0禁止/1允许通用地址响应
	IE1 = 0x01;
	EA = 1;
}

/*****************************************************
*函数名称：void TWI_Init(void)
*函数功能：TWI初始化
*入口参数：void
*出口参数：void
*****************************************************/
void SPI_Init(void)
{
	OTCON = 0X40;  //选择SPI模式
	SSCON0 = 0x2F; //设置SPI为设备，SCK空闲时间为低电平，SCK周期第二沿采集数据，时钟速率为Fsys/512
	SSCON1=0x01;   //允许发送中断
	SSCON0 |=0x80; //开启SPI
	IE1 = 0x01;
	EA = 1;
	while(1)
	{
		SSDAT = 0x55;
	}
}


/*****************************************************
*函数名称：void TWI_Int() interrupt 7
*函数功能：SSI中断函数
*入口参数：void
*出口参数：void
*****************************************************/
void Uart1_Int() interrupt 7   //Uart1中断函数
{
	if(SSCON0&0x02)    //接收标志位判断
	{
		SSCON0&=0xFD;
	}
	if((SSCON0&0x01))  //发送标志位判断
	{
		SSCON0&=0xFE;
	}
}

//void TWI_Int() interrupt 7     //TWI中断函数
//{
//	if(SSCON0&0x40)
//	{
//		SSCON0 &= 0xbf;  //中断清零
//	}	
//}

//void SpiInt(void) interrupt 7    //SPI中断函数
//{	  
//	if(SSCON1&0X08)    //发送缓存器空标志判断
//	{
//		SSCON1&=~0X08;
//	}
//	if(SSCON1&0X80)    //数据传输标志位判断
//	{
//		SSCON1&=~0X80;
//	}
//}