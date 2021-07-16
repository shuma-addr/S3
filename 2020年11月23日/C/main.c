//************************************************************
//  Copyright (c) 深圳市赛元微电子有限公司
//	文件名称	: main.c
//	作者		: Yanni
//	模块功能	: SC93F843X触控DEMO
//  最后更正日期:
// 	版本		: 2015-12-25:
//              :  
//*************************************************************
#include "h\SC93F843X_C.H"	
#include "h\data_type.h"
#include "lib\SensorMethod.h"
#include "config.h"




void Leddriveinit();
void Leddrivework();
void ledinit();
void KeyWork(void);
void ADinit(void);
void  ADC_ave(void);
void GetTmp(void);
void PowerOnClearLoad(void);
void Relaywork();
void Keyinit();
bit k3k4isdown();



//*****************全局变量区***************************************************

//INT8U  Timercount = 0;			//定时器计数


static bit f_2ms,f_10ms,timerwork_20ms,f_100ms,f_500ms,f_BTM500MS,f_BTM500MS_bak,f_1s;
static unsigned int t_cnt0;
unsigned char r_cnt1,r_cnt2,r_cnt4,r_cnt5;
static unsigned char r_ex=0;
static xdata unsigned char cnt_set=0;
static unsigned char r_excnt;
static unsigned char nocolcnt=0;
static unsigned int t_cnt3;
int uu_1,uu;

 /**************************************************
*函数名称：void TimerInit(void) 
*函数功能：定时器初始化
*入口参数：void
*出口参数：void
**************************************************/
void TimerInit(void)
{
	TMCON = (TMCON&0xfe)|(0<<0);		//bit0: 0为FOSC/12,1为FOSO

	TMOD = TMOD&0xf0;		  			//设置定时0，工作方式0
	TMOD = TMOD|0x00;
	TH0=(8192-500)/32;       			//1MS
	TL0=(8192-500)%32;
	TF0 = 0;						    //清中断标志
	TR0=0;								//关定时器0
   	ET0=1;								//使能定时器0中断
	TR0=1;
}

/**************************************************
*函数名称：void timer0()interrupt 1 
*函数功能：定时器中断服务函数
*入口参数：void
*出口参数：void 
**************************************************/
void timer0()interrupt 1
{
	TH0 = (8192-500)/32;       			
	TL0 = (8192-500)%32;	
//	TimerFlag_1ms = 1;	



	r_cnt1++;
	if(r_cnt1 >= 10)
	{
		r_cnt1=0;
		f_10ms=1;



		r_cnt2++;
		if(r_cnt2 >= 10)
		{
			r_cnt2=0;
			f_100ms=1;
		}	




		r_cnt4++;
		if(r_cnt4 >= 2)
		{
			r_cnt4=0;
			timerwork_20ms=1;
		}
	}

	t_cnt3++;
	if(t_cnt3 >= 500)
	{
		t_cnt3=0;
		f_500ms=1;
		fs_col500ms ^= 1;
		fig_diswork_500ms ^= 1;
		col_500ms ^= 1;
		P04 = ~P04;
	}	
	
	r_cnt5++;
	if(r_cnt5 >= 2)
	{
		r_cnt5=0;
		f_2ms=1;
	}	

	
}
 /**************************************************
*函数名称：void  Sys_Init(void) 
*函数功能：系统初始化
*入口参数：void
*出口参数：void  
**************************************************/
void  Sys_Init(void)
{	
//	WDTCON  = 0x10;				    //1--1 -- 00    开WDT,WDT清0,WDT 524.288ms溢出;烧录时，可Code Option选择ENWDT
	//TK对应的IO设置为强推挽输出1
	P0CON = 0xFF;
	P0PH  = 0xFF;	
	P1CON = 0xFF;
	P1PH  = 0xFF;
	P2CON = 0xFF;
	P2PH  = 0xFF;
	P5CON = 0xFF;
	P5PH  = 0xFF;
	P0 = 0xFF;
	P1 = 0xFF;
	P2 = 0xFF;
	P5 = 0x00; 	
		   
	EA = 1;						//开总中断	
    TimerInit(); 				//定时器初始化
}
void ClearSetTimeCount(void)  //清设置计时
{
	cnt_set=0;
	fsg_keynocolbf=1;
	col_500ms=1;
	t_cnt3 =0;
}
void TimerWork()
{
	
	if(timerwork_20ms)
	{
		timerwork_20ms=0;
		if(Delaybuzz)
			Delaybuzz--;

		if(f_settemp)
		{
			if(k3k4isdown())
			{
				cnt_set=0;
			}
			else
			{
				cnt_set++;
				if(cnt_set>=250)
				{
					cnt_set=0;
					f_settemp=0;
					WriteROM();
				}
			}
		}
		else
			cnt_set=0;

		if(fsg_keynocolbf)
		{
			nocolcnt++;
			if(nocolcnt>=15)
			{
				nocolcnt=0;
				fsg_keynocolbf=0;
			}
		}
		else
			nocolcnt=0;

		if(fsg_keynocolbf)
			fsg_keynocol=1;
		else
			fsg_keynocol=0;	
	}
}

void Argumentinit()
{
	rsg_show_H = 0;
//	if()
//	Settmp=22;
	PowerOnClearLoad();

	f_onoff=1;//上电即开机
}


/**************************************************
*函数名称：void main(void)								  
*函数功能：主函数
*入口参数：void
*出口参数：void  
**************************************************/
void main(void)
{					
	Sys_Init();
	Leddriveinit();
	ledinit();
	ADinit();
//	IAP_Init();
	
	//触控按键初始化
//	TouchKeyInit();
	Keyinit();
	Argumentinit();

	


	if(IAPRead(2) == EEP_FLAG)
	{
		Settmp=IAPRead(0);//25;
		rsg_show_H=IAPRead(1);//上点显示摄氏
	}
	else
	{
		Settmp=10;
		rsg_show_H=0;//上点显示摄氏		
	}


	while(1)
	{
//	   WDTCON  = 0x10;
	   TimerWork();
	   	   	   	  
		if(f_2ms)
		{
			f_2ms=0;
			Leddrivework();
			r_ex=1;
		}
		else
		{
			if(r_ex)
			{
				r_ex=0;
				r_excnt++;
				if(r_excnt>=5)
				{
					r_excnt=0;
					KeyWork();
				}
			}	   	
		}

	   	if(f_10ms)
		{
			f_10ms=0;
			FanWork() ;
			ADC_ave();
			ledwork();
//			showtemp(uu_1);
		}
		GetTmp();
		
		if(f_100ms)
		{
			f_100ms=0;
			
			 
		}

		if(f_500ms)
		{
			f_500ms=0;
			Relaywork();
//		uu_1++;
//		if(uu_1>-1)
//			uu_1=-9;
		}
	//   	ADCCON &= ~(0X10);
	
		  
//		uu = TurnToFahren(uu_1); 
	} 
}


 

















