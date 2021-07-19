#include "h\SC93F843X_C.H"	
#include "h\data_type.h"
#include "lib\SensorMethod.h"
#include "config.h"

//bit ForceClose_lev1(void);


#define	  	IO_REL1		P50//P41	
#define	  	IO_REL2		P11//P40			 
#define		IO_FAN		P51//P17
//#define		IO_LAMP		P10

#define WARMON 1  //开启制热
#define COLDON 2   //开启制冷
#define BOTHCLOSE 0	  //制冷制热都关

#define CLOSE 0	   //风扇关
#define HALF 1	  //风扇半功率输出
#define ALL 19	 //风扇全功率输出





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
		case TEMPADD:  //温度处于上升状态
			Output(WARMON);	//制热
			break;
		case TEMPSUB:
			Output(COLDON);//制冷
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
	if(s_temp_trend == TEMPSUB)	  //温度变化趋势 减
	{
		if(Tmp_C <= set)
			s_temp_trend = 0;		
	}
	else if(s_temp_trend == TEMPADD)//温度变化趋势 加
	{
		if(Tmp_C >= set)
			s_temp_trend = 0;				
	}
	else
	{
		if(Tmp_C > (set+1))
			s_temp_trend = TEMPSUB;	//温度变化趋势 减			
		else if(Tmp_C < (set-1))
			s_temp_trend = TEMPADD;	//温度变化趋势 加
		else
		{}				
	}
}
void RelayWork_H(unsigned char set)
{
	if(s_temp_trend == TEMPSUB)	  //温度变化趋势 减
	{
		if(Tmp_H <= set)
			s_temp_trend = 0;		
	}
	else if(s_temp_trend == TEMPADD) //温度变化趋势 加
	{
		if(Tmp_H >= set)
			s_temp_trend = 0;				
	}
	else
	{
		if(Tmp_H > (set+1))					
			s_temp_trend = TEMPSUB;	//温度变化趋势 减			
		else if(Tmp_H < (set-1))
			s_temp_trend = TEMPADD;	//温度变化趋势 加
		else
		{}				
	}
}
void Relaywork()
{
	/*IO_REL1*/	//制热
	bit ftl_closeall=0;
	unsigned char set;
	//若在华氏状态，则转化成摄氏；若在摄氏状态就直接用；
	if(rsg_show_H)
		set = TurnToCenti(Settmp);
	else
		set = Settmp;


	ftl_closeall = ForceClose_lev1();//强制关闭等级最高

	if(f_onoff)
	{
		if(ftl_closeall) //强制关
		{
			s_temp_trend = 0;
		}
		else
		{
			if(f_settemp)
			{}
			else
			{
				if(rsg_show_H)//显示华氏温度
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


   	
	OutputBf(s_temp_trend);	//根据当前的温度趋势，判定是制冷还是制热



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
