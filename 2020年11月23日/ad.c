#include "h\SC93F843X_C.H"	
#include "h\data_type.h"
#include "lib\SensorMethod.h"
#include "config.h"

#define DEFAULTTEMP 25
//#define ADC_MAX_NTC 828   //杩欎袱涓�间笉鑳芥槸琛ㄦ牸鐨勬瀬闄?
//#define ADC_MIN_NTC 139

#define ADC_MAX 828
#define ADC_MIN 141

#define ADH_MAX 796
#define ADH_MIN 197

//#define TMP_MIN_NTC 0
//#define TMP_MAX_NTC	80


bit AdcFlag = 0;

static xdata unsigned char ad8_cnt; 
static xdata unsigned int ad8_result,ad8_result_sum,ad8_result_ave;
static bit s_ad8_over=0;

unsigned int AD_TS0=0,AD_TS1=0,AD_TSSUM=0;

//static xdata unsigned char ad1_cnt; 
//static xdata unsigned int ad1_result,ad1_result_sum,ad1_result_ave;
//static bit s_ad1_over=0;
//
//static xdata unsigned char ad2_cnt; 
//xdata unsigned int ad2_result,ad2_result_sum,ad2_result_ave;
//static bit s_ad2_over=0;

code unsigned int TABC_NTC[90]={	  //摄氏温度表
828,821,813,805,797,789,781,772,763,    //-9到-1
755,746,737,728,719,709,700,690,681,671, //0-9
661,651,641,631,621,611,601,591,581,571,//10-19
561,551,541,531,521,512,502,492,482,473, //20-29
463,454,444,435,426,417,408,399,390,382, //30-39
373,365,357,349,341,333,325,318,310,303, //40-49
296,289,282,275,268,262,256,249,243,237, //50-59
232,226,220,215,210,204,199,194,190,185, //60-69
180,176,171,167,163,159,155,151,147,144, //70-79
140
};



code unsigned int TABH_NTC[131]={	  //华氏温度表
797,791,785,780,775,770,766,764,760,//23到31
755,750,745,740,735,730,725,720,715,709, //32-41
704,699,694,689,684,679,673,666,661,655, //42-51
649,643,637,631,626,621,616,611,605,600, //52-61
594,588,582,576,571,566,561,555,550,544, //62-71
538,532,527,522,517,512,506,502,496,490, //72-81
485,478,473,468,463,458,453,448,443,438, //82-91
433,428,423,417,412,407,402,397,392,387,//92-101 
382,377,373,368,363,358,353,349,345,341, //102-111
337,333,328,324,320,316,312,308,304,300, //112-121
296,292,288,284,280,276,272,268,265,262,	 //122-131
258,254,250,247,244,241,238,235,232,229,	 //132-141
226,223,220,217,215,212,209,206,203,200,//142-151
198,196,							 //152-153

};


void ADIOinit(void)//AD鍙ｏ紝IO鍙ｅ垵濮嬪寲   璇ュ嚱鏁版斁鍦ㄧ郴缁熶笂鐢碉紝杩涘叆涓诲惊鐜箣鍓嶏紱
{
//	P15输入口，AD口
	P1CON &= ~0x20;  //0010 0000 
	P1PH  &= ~0x20;	

}
void ADinit(void)
{
	ADIOinit();
	s_ad8_over=0;//
   	ADCCON = 0X00;	//0000 0000   选择频率2M  

	ADCCFG0 |= 0x00;
	ADCCFG1 |= 0x01;///0000 0001  设置AD8为AD输入口

	ADCCON |= 0X80;	 //打开AD电源
	IE &= ~0X40;        //关闭ADC中断
	EA = 1;

	err_NTC_short=0;	
	err_NTC_open=0;
}

unsigned int  ADC_Convert(void)						
{
	unsigned int adcdat;

	ADCCON |= 0X40;   //开始ADC转换
	while(!(ADCCON&0x10));	         		 //等待 ADC转换完成;
	ADCCON &= ~(0X10);
	adcdat=(ADCVH<<4)+(ADCVL>>4);

	return(adcdat);
}
void Ch_ADchannel(unsigned char channel)
{
	ADCCON &= ~0x0f;///0000 1111
	ADCCON |= channel;		
}
//void ADC_Interrupt(void) interrupt 6
//{
////	ADCCON &= ~(0X20);  //清中断标志位
//	AdcFlag = 1;
//	ADCCON &= ~(0X10);
//}
void  ADC_ave(void)
{
	static xdata unsigned char AdIndx;	
    switch(AdIndx)
	{
		case 0: 	//AdIndx++;
					Ch_ADchannel(8);	  //
					ad8_result=ADC_Convert();
					ad8_result_sum=ad8_result_sum+ad8_result;
					if(++ad8_cnt>=16)
					{
					 	ad8_cnt=0;
						ad8_result_sum=ad8_result_sum>>4;
						/*12位数据转10位*/
						ad8_result_sum= (ad8_result_sum>>2)&0x03ff;
						ad8_result_ave= ad8_result_sum;
						ad8_result_sum=0;
						s_ad8_over=1;
					}
					break;

//		case 1:		AdIndx++;
//					Ch_ADchannel(0x01);	 //CN3   腔体
//					ad2_result=ADC_Convert();
//					ad2_result_sum=ad2_result_sum+ad2_result;
//					if(++ad2_cnt>=16)
//					{
//					 	ad2_cnt=0;
//						ad2_result_sum=ad2_result_sum>>4;
//						ad2_result_ave=ad2_result_sum;
//						ad2_result_sum=0;
//						s_ad2_over=1;
//					}
//					break;
//		case 2:		AdIndx++;
//					Ch_ADchannel(0x02);	   //CN4  蒸汽发生器
//					ad1_result=ADC_Convert();
//					ad1_result_sum=ad1_result_sum+ad1_result;
//					if(++ad1_cnt>=16)
//					{
//					 	ad1_cnt=0;
//						ad1_result_sum=ad1_result_sum>>4;
//						/*12位数据转10位*/
//						ad1_result_sum= (ad1_result_sum>>2)&0x03ff;
//						ad1_result_ave=ad1_result_sum;
//						ad1_result_sum=0;
//						s_ad1_over=1;
//					}
//					break;
//					
//		case 3:		AdIndx=0;
//
//					break;
		default:    AdIndx=0;
					break;
	}
	
}

int GetTMP_NTC(unsigned int ad)//
{

	static int TMP_NTC=DEFAULTTEMP;//
	int temp;

	if(ad<=ADC_MIN)	//
		ad=ADC_MIN;
	else if(ad<=ADC_MAX)
	{}
	else
		ad=ADC_MAX;			

	if(TABC_NTC[0] < TABC_NTC[25]) //升序
	{
		if(ad<TABC_NTC[TMP_NTC])
		{
			if(TMP_NTC)
				TMP_NTC--;
		}
		else if(ad<TABC_NTC[TMP_NTC+1] )
		{

		}
		else
			TMP_NTC++;	
	}
	else //降序
	{
		if(ad<TABC_NTC[TMP_NTC+1])
		{
			TMP_NTC++;
		}
		else if(ad<TABC_NTC[TMP_NTC] )
		{
		}
		else
		{
			if(TMP_NTC)
				TMP_NTC--;
		}	
	}	 
	temp = TMP_NTC-9;
	return(temp);		
}

int LookUpTabH(unsigned int ad)
{
	static int TmpH=60;//当前温度默认为60
	int temp;

	if(ad<=ADH_MIN)
		ad=ADH_MIN;
	else if(ad<ADH_MAX)
	{}
	else
		ad=ADH_MAX;

	if(TABH_NTC[0] < TABH_NTC[25]) //升序
	{
		if(ad<TABH_NTC[TmpH])
		{
			if(TmpH)
				TmpH--;
		}
		else if(ad<TABH_NTC[TmpH+1] )
		{
		}
		else
			TmpH++;	
	}
	else //降序
	{
		if(ad<TABH_NTC[TmpH+1])
			TmpH++;
		else if(ad<TABH_NTC[TmpH] )
		{
		}
		else
		{
			if(TmpH)
				TmpH--;
		}	
	}	

	temp=TmpH+23;//+32-9;	

	return(temp);		
}	


void GetTmp(void)   //
{

	#define AD_L  10
	#define AD_H  1020
	unsigned int temp;
	static unsigned int ad3H_bak=0;
	static unsigned int ad3C_bak=0;

	if(s_ad8_over)	 //10位
	{
		if(ad3C_bak >= ad8_result_ave)//求差值 摄氏
			temp = ad3C_bak - ad8_result_ave;
		else
			temp = ad8_result_ave - ad3C_bak;

		if(ad8_result_ave<=ADC_MIN)
		{
			ad3C_bak = ad8_result_ave;
		}
		else if(ad8_result_ave<ADC_MAX)
		{
			//新检测到的AD值与上一次的之间的差值大于6，以新的AD值做温度转换；
			if(temp > 6)
				ad3C_bak = ad8_result_ave;
			else
			{/*ad3C_bak保持不变*/}	
		}
		else
		{
			ad3C_bak = ad8_result_ave;
		}	

		if(ad3H_bak >= ad8_result_ave)	//求差值  华氏
			temp = ad3H_bak - ad8_result_ave;
		else
			temp = ad8_result_ave - ad3H_bak;


		if(ad8_result_ave<=ADH_MIN)
		{
			ad3H_bak = ad8_result_ave;
		}
		else if(ad8_result_ave<ADH_MAX)
		{
			//新检测到的AD值与上一次的之间的差值大于6，以新的AD值做温度转换；
			if(temp > 6)
				ad3H_bak = ad8_result_ave;
			else
			{/*ad3H_bak保持不变*/}	
		}
		else
		{
			ad3H_bak = ad8_result_ave;
		}
			
		if(ad8_result_ave<AD_L)
		{
			err_NTC_open=1;
			err_NTC_short=0;
		}
		else if(ad8_result_ave<AD_H)
		{
			err_NTC_open=0;
			err_NTC_short=0;
			Tmp_C = GetTMP_NTC(ad3C_bak);
//			Tmp_C = -3;
			Tmp_H = LookUpTabH(ad3H_bak); //S
//			Tmp_H = 25;
		}
		else
		{
			err_NTC_short=1;	
			err_NTC_open=0;
		}				

	}
	else
	{
		Tmp_C = DEFAULTTEMP;//
		Tmp_H = 60;
	}

}
bit ForceClose_lev1(void)
{
 	if(err_NTC_open | err_NTC_short)
		return(1);
	else
		return(0);
}

