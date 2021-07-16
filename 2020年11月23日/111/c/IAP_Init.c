#include "H/SC93F843X_C.H"
#include "H/Function_Init.H"

#define IapTotal 0x00	  //0x00：选择ROM区操作  0x02：选择EEPROM区操作
unsigned char code *IapAddr=0x00;

void IAPWrite(uint Addr,uchar Data);
uchar IAPRead(uint Addr);
/*****************************************************
*函数名称：void IAP_Init(void)
*函数功能：IAP初始化
*入口参数：void
*出口参数：void
*****************************************************/
void IAP_Init(void)
{
	uint i,IapReadData;
	for(i=0;i<128;i++)
	{		
		IAPWrite(i,0xff);
		IapReadData=IAPRead(i);
	}
}

//IAP写操作
void IAPWrite(uint Addr,uchar Data)
{	
	IAPDAT=Data;      //写入数据Data
	IAPADH=(uchar)((Addr>>8)&0X3F);   //写入地址的高5位
	IAPADL=(uchar)Addr;               //写入地址的低8位
	
	IAPADE=IapTotal;  //IapTotal=0x00：选择ROM区操作  IapTotal=0x02：选择EEPROM区操作
	IAPKEY=240;		   //IAP开启保护控制时间
	IAPCTL=0x06;     //CPU hold time为2ms，写入操作命令
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}
//IAP读操作
uchar IAPRead(uint Addr)
{
	IAPADE=IapTotal;
	return (*(IapAddr+Addr));	
}