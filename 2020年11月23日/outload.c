#include "h\SC93F843X_C.H"	
#include "h\data_type.h"
#include "lib\SensorMethod.h"
#include "config.h"

//bit ForceClose_lev1(void);


#define	  	IO_REL1		P50//P41	
#define	  	IO_REL2		P11//P40			 
#define		IO_FAN		P51//P17
//#define		IO_LAMP		P10

#define WARMON 1  //��������
#define COLDON 2   //��������
#define BOTHCLOSE 0	  //�������ȶ���

#define CLOSE 0	   //���ȹ�
#define HALF 1	  //���Ȱ빦�����
#define ALL 111	 //����ȫ�������





unsigned char s_temp_trend=0;

void PowerOnClearLoad(void)
{
	s_temp_trend=0;	
}

void Output(unsigned char temp)
{
	switch(temp)
	{
		case WARMON:
				IO_REL1=1;
				IO_REL2=0;
				break;
		case COLDON:
				IO_REL1=0;
				IO_REL2=1;
				break;
		default:
				IO_REL1=0;
				IO_REL2=0;
				break;										
				
	}
}

void OutputBf(unsigned char temp)
{
	switch (temp)
	{
		case TEMPADD:  //�¶ȴ�������״̬
			Output(WARMON);	//����
			break;
		case TEMPSUB:
			Output(COLDON);//����
			break;
		default:
			Output(BOTHCLOSE);
			break;
	}
}

unsigned char Output_led()
{
	return(s_temp_trend);
}

void RelayWork_C(unsigned char set)
{
	if(s_temp_trend == TEMPSUB)	  //�¶ȱ仯���� ��
	{
		if(Tmp_C <= set)
			s_temp_trend = 0;		
	}
	else if(s_temp_trend == TEMPADD)//�¶ȱ仯���� ��
	{
		if(Tmp_C >= set)
			s_temp_trend = 0;				
	}
	else
	{
		if(Tmp_C > (set+1))
			s_temp_trend = TEMPSUB;	//�¶ȱ仯���� ��			
		else if(Tmp_C < (set-1))
			s_temp_trend = TEMPADD;	//�¶ȱ仯���� ��
		else
		{}				
	}
}
void RelayWork_H(unsigned char set)
{
	if(s_temp_trend == TEMPSUB)	  //�¶ȱ仯���� ��
	{
		if(Tmp_H <= set)
			s_temp_trend = 0;		
	}
	else if(s_temp_trend == TEMPADD) //�¶ȱ仯���� ��
	{
		if(Tmp_H >= set)
			s_temp_trend = 0;				
	}
	else
	{
		if(Tmp_H > (set+1))					
			s_temp_trend = TEMPSUB;	//�¶ȱ仯���� ��			
		else if(Tmp_H < (set-1))
			s_temp_trend = TEMPADD;	//�¶ȱ仯���� ��
		else
		{}				
	}
}
void Relaywork()
{
	/*IO_REL1*/	//����
	bit ftl_closeall=0;
	unsigned char set;
	//���ڻ���״̬����ת�������ϣ���������״̬��ֱ���ã�
	if(rsg_show_H)
		set = TurnToCenti(Settmp);
	else
		set = Settmp;


	ftl_closeall = ForceClose_lev1();//ǿ�ƹرյȼ����

	if(f_onoff)
	{
		if(ftl_closeall) //ǿ�ƹ�
		{
			s_temp_trend = 0;
		}
		else
		{
			if(f_settemp)
			{}
			else
			{
				if(rsg_show_H)//��ʾ�����¶�
					RelayWork_H(Settmp);
				else
					RelayWork_C(Settmp);	
//					if(s_temp_trend == TEMPSUB)
//					{
//						if(Tmp_C <= set)
//							s_temp_trend = 0;		
//					}
//					else if(s_temp_trend == TEMPADD)
//					{
//						if(Tmp_C >= set)
//							s_temp_trend = 0;				
//					}
//					else
//					{
//						if(Tmp_C > (set+1))
//						{
//							s_temp_trend = TEMPSUB;				
//						}
//						else if(Tmp_C < (set-1))
//						{
//							s_temp_trend = TEMPADD;	
//						}
//						else
//						{}				
//					}
			}
		}
	}
	else
		s_temp_trend = 0;


   	
	OutputBf(s_temp_trend);	//���ݵ�ǰ���¶����ƣ��ж������仹������



}
void Output_FAN(unsigned char temp)
{
	switch(temp)
	{
		case HALF:
			IO_FAN ^=1;
			break;
		case ALL:
			IO_FAN =1;
			break;
		default:
			IO_FAN =0;
			break;					
	}
}
void FanWork(void) //10ms
{
	if(f_onoff)
	{
		if(IO_REL2|IO_REL1)
		{
			if(fsg_lowpower)
				Output_FAN(HALF);
			else
				Output_FAN(ALL); 
		}
		else
			Output_FAN(CLOSE);	
	}
	else
		Output_FAN(CLOSE);
}