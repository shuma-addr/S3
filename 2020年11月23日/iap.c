#include "h\SC93F843X_C.H"	
#include "h\data_type.h"
#include "lib\SensorMethod.h"
#include "config.h"

#define IapTotal 0x02	  //0x00：选择ROM区操作  0x02：选择EEPROM区操作
unsigned char code *IapAddr=0x00;

//void IAPWrite(uint Addr,uchar Data);
//uchar IAPRead(uint Addr);

//void IAP_Init(void)
//{
//	uint i,IapReadData;
//	for(i=0;i<128;i++)
//	{		
//		IAPWrite(i,0xff);
//		IapReadData=IAPRead(i);
//	}
//}
void Delay_us(unsigned char temp)
{
	while(temp)
		temp--;
}
//IAP写操作
void IAPWrite(uint Addr,uchar Data)
{	
	EA =0;
	IAPADE=IapTotal;
	IAPDAT=Data;      //写入数据Data
	IAPADH=(uchar)((Addr>>8)&0X3F);   //写入地址的高5位
	IAPADL=(uchar)Addr;               //写入地址的低8位
	
	  //IapTotal=0x00：选择ROM区操作  IapTotal=0x02：选择EEPROM区操作
	IAPKEY=0xf0;		   //IAP开启保护控制时间
	IAPCTL=0x0A;     //CPU hold time为2ms，写入操作命令
//	_nop_();
//	_nop_();
//	_nop_();
//	_nop_();
//	_nop_();
	Delay_us(10);
	IAPADE=0x00;
	EA=1;	
}
//IAP读操作
unsigned char IAPRead(uint Addr)
{
	unsigned char dat;
	EA=0;
	IAPADE=IapTotal;
	dat	 =  *(IapAddr+Addr);
	IAPADE=0x00;
	EA=1;
	return (dat);	
}

void WriteROM(void)
{
	IAPWrite(0,Settmp);
	IAPWrite(1,rsg_show_H);
	IAPWrite(2,EEP_FLAG);
	IAPWrite(3,EEP_FLAG1);
}