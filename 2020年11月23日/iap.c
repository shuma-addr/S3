#include "h\SC93F843X_C.H"	
#include "h\data_type.h"
#include "lib\SensorMethod.h"
#include "config.h"

#define IapTotal 0x02	  //0x00��ѡ��ROM������  0x02��ѡ��EEPROM������
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
//IAPд����
void IAPWrite(uint Addr,uchar Data)
{	
	EA =0;
	IAPADE=IapTotal;
	IAPDAT=Data;      //д������Data
	IAPADH=(uchar)((Addr>>8)&0X3F);   //д���ַ�ĸ�5λ
	IAPADL=(uchar)Addr;               //д���ַ�ĵ�8λ
	
	  //IapTotal=0x00��ѡ��ROM������  IapTotal=0x02��ѡ��EEPROM������
	IAPKEY=0xf0;		   //IAP������������ʱ��
	IAPCTL=0x0A;     //CPU hold timeΪ2ms��д���������
//	_nop_();
//	_nop_();
//	_nop_();
//	_nop_();
//	_nop_();
	Delay_us(10);
	IAPADE=0x00;
	EA=1;	
}
//IAP������
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