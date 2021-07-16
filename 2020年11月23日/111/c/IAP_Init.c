#include "H/SC93F843X_C.H"
#include "H/Function_Init.H"

#define IapTotal 0x00	  //0x00��ѡ��ROM������  0x02��ѡ��EEPROM������
unsigned char code *IapAddr=0x00;

void IAPWrite(uint Addr,uchar Data);
uchar IAPRead(uint Addr);
/*****************************************************
*�������ƣ�void IAP_Init(void)
*�������ܣ�IAP��ʼ��
*��ڲ�����void
*���ڲ�����void
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

//IAPд����
void IAPWrite(uint Addr,uchar Data)
{	
	IAPDAT=Data;      //д������Data
	IAPADH=(uchar)((Addr>>8)&0X3F);   //д���ַ�ĸ�5λ
	IAPADL=(uchar)Addr;               //д���ַ�ĵ�8λ
	
	IAPADE=IapTotal;  //IapTotal=0x00��ѡ��ROM������  IapTotal=0x02��ѡ��EEPROM������
	IAPKEY=240;		   //IAP������������ʱ��
	IAPCTL=0x06;     //CPU hold timeΪ2ms��д���������
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}
//IAP������
uchar IAPRead(uint Addr)
{
	IAPADE=IapTotal;
	return (*(IapAddr+Addr));	
}