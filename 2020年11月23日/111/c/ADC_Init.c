#include "H/SC93F843X_C.H"
#include "H/Function_Init.H"

/*****************************************************
*�������ƣ�void ADC_Init(void)
*�������ܣ�ADC��ʼ��
*��ڲ�����void
*���ڲ�����void
*****************************************************/
unsigned int ADCValue = 0x0000;
void ADC_Init(void)
{
	ADCCON = 0X89;		//����ADC��ADC����Ƶ��Ϊ2M ,ѡ��AIN9λADC������
	ADCCFG0 = 0x00;   //����AIN9��Ϊ������
	ADCCFG1 = 0X02;   //����AIN9��Ϊ������
//	IE = 0X40;        //����ADC�ж�
	EA = 1;

	ADCCON |= 0X40;   //��ʼADCת��
	while(!(ADCCON&0x10));	         		 //�ȴ� ADCת�����;
	ADCValue=(ADCVH<<4)+(ADCVL>>4);
}

/*****************************************************
*�������ƣ�void ADC_TS_Init(void)
*�������ܣ�ADC�ɼ��¶ȴ�������ѹֵ
*��ڲ�����void
*���ڲ�����void
*****************************************************/
void ADC_TS_Init(void)
{
	unsigned int AD_TS0=0,AD_TS1=0,AD_TSSUM=0;
	
	ADCCON = 0x8E;		//����ADC��ADC����Ƶ��Ϊ2M ,ADC����Ϊ�¶ȴ��������
	ADCCFG0 = 0x00;   //
	ADCCFG1 = 0X00;   //
	while(1)
	{
		TSCFG = 0X80;
		ADCCON |= 0x40;   //��ʼADCת��		
		while(!(ADCCON&0x10));
		ADCCON &= 0xEF;   //���жϱ�־λ
		AD_TS0 = (ADCVH<<4)+(ADCVL>>4);  //��һ���¶ȴ�������ֵ
		
		TSCFG |= 0X01;
		ADCCON |= 0x40;   //��ʼADCת��		
		while(!(ADCCON&0x10));
		ADCCON &= 0xEF;   //���жϱ�־λ
		AD_TS1 = (ADCVH<<4)+(ADCVL>>4);  //�ڶ����¶ȴ�������ֵ
		
		AD_TSSUM = (AD_TS0+AD_TS1)/2;    //�¶ȴ�������ֵ
	}
}
