#include "h\SC93F843X_C.H"	
#include "h\data_type.h"
#include "lib\SensorMethod.h"
#include "config.h"

bit fsg_keynocol=0;

#define K1_num  1
#define K2_num  2
#define K3_num 	3
#define K4_num 	4
#define K5_num 	5
#define K6_num 	6
#define K7_num 	7
#define K8_num 	8
#define K9_num 	9
#define K10_num 	10
#define K11_num 	11
#define K12_num 	12
#define K3K4_num 	13

//#define TOUCH_TIME  100  //长按时间
//#define FAST_TIME	4    //快进时间

#define TOUCH_TIME  150  //触碰3秒，算长按键
#define FAST_TIME	5	 //快进时间  100ms
#define MAX_C  65
#define MIN_C 0
#define MAX_H  149
#define MIN_H 32




static unsigned char keyram,keyreg,keynum; //这里定义的变量只在3个函数中使用
static bit bit_k1=0;
static unsigned char k1_cnt=0;
static bit bit_k2=0;
static unsigned char k2_cnt=0;
//static bit bit_k3=0;
//static unsigned char k3_cnt=0;
//static bit bit_k4=0;
//static unsigned char k4_cnt=0;
static bit bit_k3k4=0;
static unsigned char k3k4_cnt=0;	
static bit bit_k3, bit_k3_L;
static unsigned char k3_cnt=0;
static bit bit_k4, bit_k4_L;
static unsigned char k4_cnt=0;
xdata unsigned char r_K3K4used=0;
xdata unsigned char cnt_K3K4used=0;	


unsigned char   bdata  keyflag_1;
sbit    shortkeyk1            = keyflag_1 ^0;
sbit    shortkeyk2            = keyflag_1 ^1;
sbit    shortkeyk3           = keyflag_1 ^2;
sbit    shortkeyk4           = keyflag_1 ^3;
sbit    shortkeyk5        = keyflag_1 ^4;  //设置工作时间
sbit    shortkeyk6         = keyflag_1 ^5;
sbit    shortkeyk7           = keyflag_1 ^6;
sbit    shortkeyk8            = keyflag_1 ^7;

unsigned char   bdata  keyflag_2;
sbit    shortkeyk9            = keyflag_2 ^0;
sbit    shortkeyk10            = keyflag_2 ^1;
sbit    shortkeyk11           = keyflag_2 ^2;
sbit    longkeyk1           = keyflag_2 ^3;
sbit    longkeyk3k4        = keyflag_2 ^4;  //设置工作时间
sbit    longkeyk4         = keyflag_2 ^5;
sbit    longkeyk3           = keyflag_2 ^6;
sbit    longkeyk2            = keyflag_2 ^7;

//void CloseAllLed(void)
//{
//		 led_delay=0;	
//		 led_lamp=0;   
//		 led_power=0;   
//		 led_high=0;    
//		 led_low=0;  
//}
INT32U exKeyValueFlag = 0;		//当前轮按键标志

bit k3k4isdown()
{
	if(k3_cnt|k4_cnt)
		return(1);
	else
		return(0);
}

void Key_Add(void)
{
	if(rsg_show_H)
	{
		Settmp++;
		if(Settmp>MAX_H)
			Settmp=MAX_H;	
	}
	else
	{
		Settmp++;
		if(Settmp>MAX_C)
			Settmp=MAX_C;
	}
	ClearSetTimeCount();	
}
void Key_Sub(void)
{
	if(rsg_show_H)
	{
//		Settmp--;
//		if(Settmp < MIN_H)
//			Settmp = MIN_H;	
		if(Settmp>MIN_H)
			Settmp--;
		else
			Settmp=MIN_H;	
	}
	else
	{
		if(Settmp>MIN_C)
			Settmp--;
		else
			Settmp=MIN_C;
//		if(Settmp < MIN_C)
//			Settmp = MIN_C;
	}

	ClearSetTimeCount();
}
void BuzWork(unsigned char temp)
{
	if(temp==1)
	{
		Delaybuzz=15;
	}
}
int TurnToCenti(int temp)////摄氏度 = (华氏度 - 32) ÷ 1.8
{
	int temp_1;
	temp_1 = ((temp-32)*5)/9;
//	if(temp_1<MIN_C)
//		temp_1=MIN_C;
//	if(temp_1>MAX_C)
//		temp_1=MAX_C;
	return(temp_1);	
}
int TurnToFahren(int temp)//华氏度 = 32+ 摄氏度 × 1.8	摄氏2度等同于华氏36度	摄氏60度等同于华氏140
{
	int temp_1;
	temp_1 = ((temp*9)/5)+32;
//	if(temp_1<MIN_H)
//		temp_1=MIN_H;
//	if(temp_1>MAX_H)
//		temp_1=MAX_H;
	return(temp_1);	
}

void Keyinit()
{
	TouchKeyInit();
	r_K3K4used=0;
	cnt_K3K4used=0;	
}
/**************************************************
*函数名称：void  Sys_Scan(void) 
*函数功能：扫描TK和显示
*入口参数：void
*出口参数：void  
**************************************************/
void Sys_Scan(void)
{      				
//	if(SOCAPI_TouchKeyStatus&0x40)		//当按键个数大于8个时，要判断半轮标志是否被置起，然后启动下半轮
//	{
//		SOCAPI_TouchKeyStatus &= 0xBf;	// 清除标志位， 需要外部清除。
//		TouchKeyRestart();				//启动下一轮转换
//	}
	if(SOCAPI_TouchKeyStatus&0x80)	    //重要步骤2:  触摸键扫描一轮标志，是否调用TouchKeyScan()一定要根据此标志位置起后
	 {	   																	
		SOCAPI_TouchKeyStatus &= 0x7f;	//重要步骤3: 清除标志位， 需要外部清除。													    
		exKeyValueFlag = TouchKeyScan();//按键数据处理函数    
		TouchKeyRestart();				//启动下一轮转换																														 			
	}		  	   
}
void readkey(void)
{
	unsigned long temp;
	Sys_Scan();
	temp=0;  
	temp=exKeyValueFlag;//读取按键值
	
	switch(temp)
	{
		  case 0x00000001:  //TK0	 k2
		  		keyreg=K2_num;	
//				Led_value = 10; 
//				ShowTmp(0);
//				CloseAllLed();
//				led_high=1;
		  		break;				
		  case 0x00000002:  //TK1	  k1
		  		keyreg=K1_num;
//				ShowTmp(1);	
//				Led_value = 7;
//				CloseAllLed();
//			    led_low=1;
		  		break;
		 case 0x00000004: 	 //TK2	   k4
		  		keyreg=K4_num;
//				ShowTmp(2);
//				Led_value = 8;
//				CloseAllLed();
//				   led_power=1;
		  		break;
		  case 0x00000008: 	 //TK3	   k3
		  		keyreg=K3_num;
//				ShowTmp(3);
//				Led_value = 9;
//				CloseAllLed();
//				led_lamp=1;
		  		break;
		  case 0x0000000c:   //TK4+TK3
		 		keyreg=K3K4_num;
//				Led_value = 1;
//				CloseAllLed();
//				 led_delay=1; 
		  		break;
//		  case 0x00000020:   //TK5
//		 		keyreg=K2_num;
//				Led_value = 2;
////				CloseAllLed();
////				 led_delay=1; 
//		  		break;
//		  case 0x00000100:  //TK8
//		 		keyreg=K3_num;
//				Led_value = 3;
////				CloseAllLed();
////				 led_delay=1; 
//		  		break;
//		  case 0x00000200:  //TK9
//		 		keyreg=K4_num;
//				Led_value = 4;
////				CloseAllLed();
////				 led_delay=1; 
//		  		break;	
//		  case 0x00001000:   //TK12
//		 		keyreg=K5_num;
//				Led_value = 5;
////				CloseAllLed();
////				 led_delay=1; 
//		  		break;	
//		  case 0x00002000:  //TK13
//		 		keyreg=K6_num;
//				Led_value = 6;
////				CloseAllLed();
////				 led_delay=1; 
//		  		break;
//		  case 0x00004000:  //TK14
//		 		keyreg=K12_num;
//				Led_value = 12;
////				CloseAllLed();
////				 led_delay=1; 
//		  		break;	
//		  case 0x00008000:  //TK15
//		 		keyreg=K11_num;
//				Led_value = 11;
////				CloseAllLed();
////				 led_delay=1; 
//		  		break;							
		  default:	
				keyreg=0;
		  			break;
	}	
}
void keyImplement(void)
{
	if(keyram==K1_num )  // 
	{	
//		shortkeyk1=1;
		return;
	}
	if(keyram==K2_num )   // 
	{	
//		shortkeyk2=1;
		return;
	}
	if(keyram==K3_num )   // 
	{
//		shortkeyk3=1;
		return;
	}
	if(keyram==K4_num )   //
	{	
//		shortkeyk4=1;
		return;
	}
//	if(keyram==K5_num )   //
//	{	
//		shortkeyk5=1;
//		return;
//	}
}
void keydebouce(void)		//按键消抖
{
	readkey();     //My_keydata送keyreg
	keynum++;	   //扫描次数加1
	switch(keynum)
	{
		case 1:
		if(keyreg==0) {keynum=0;return;} 
		keyram=keyreg;
		return;	   
		case 2:
		if(keyreg==0) {keynum=0;return;}
		keyram=keyreg;	      
		return;				
		case 3:
		if(keyram!=keyreg) {keyram=0;keynum=0;return;}
		keyImplement();      //按键执行
		return;
		case 4:
		if(keyreg==0){return;}

		if(keyreg==K1_num)
		{
			if(bit_k1==0)
			{
				k1_cnt++;
				if(k1_cnt>=TOUCH_TIME)
				{
					k1_cnt=0;
					bit_k1=1;
					longkeyk1=1;			
				}	
			}	
		}

		if(keyreg==K2_num)
		{
			if(bit_k2==0)
			{
				k2_cnt++;
				if(k2_cnt>=TOUCH_TIME)
				{
					k2_cnt=0;
					bit_k2=1;
					longkeyk2=1;			
				}	
			}	
		}

		if(keyreg==K3_num)
		{
			if(bit_k3==0)
			{
				k3_cnt++;
				if(k3_cnt >= TOUCH_TIME )
				{
					k3_cnt =  0;
					bit_k3=1;
					longkeyk3=1;
					bit_k3_L=1;
				}
			}
			else
			{
				bit_k3_L=1;	//已 长 按	 防长按后，再一个短按
				k3_cnt++;
				if(k3_cnt >= FAST_TIME)//快进
				{
					k3_cnt=0;
					longkeyk3=1;
					fsg_keynocol=1;
				}					
			}
	   	}
		if(keyreg==K4_num)
		{
			if(bit_k4==0)
			{
				k4_cnt++;
				if(k4_cnt >= TOUCH_TIME )
				{
					k4_cnt =  0;
					bit_k4=1;
					longkeyk4=1;
					bit_k4_L=1;
				}
			}
			else
			{
				bit_k4_L=1;	//已 长 按	 防长按后，再一个短按
				k4_cnt++;
				if(k4_cnt >= FAST_TIME)//快进
				{
					k4_cnt=0;
					longkeyk4=1;
					fsg_keynocol=1;
				}					
			}
	   	 }
		if(keyreg==K3K4_num )
		{
			if(bit_k3k4==0)
			{
				k3k4_cnt++;
				if(k3k4_cnt>=TOUCH_TIME)
				{
					k3k4_cnt=0;
					bit_k3k4=1;
					longkeyk3k4=1;
				}	
			}
			r_K3K4used=1;
			cnt_K3K4used=0;		
		}
		return;
		case 5:
		if(keyreg==0)
		{
			if(  (k1_cnt<TOUCH_TIME)  &  (k1_cnt>0)  )
				shortkeyk1=1;

			if(  (k2_cnt<TOUCH_TIME)  &  (k2_cnt>0)  )
				shortkeyk2=1;

			if(!bit_k3_L)
			{
				if((k3_cnt<TOUCH_TIME) && (k3_cnt>0))	   //
				{
					shortkeyk3=1;
				}
			}

			if(!bit_k4_L)
			{
				if((k4_cnt<TOUCH_TIME) && (k4_cnt>0))	   //
				{
					shortkeyk4=1;
				}
			}

			k1_cnt=0;
			bit_k1=0;

			k2_cnt=0;
			bit_k2=0;

			k3k4_cnt=0;
			bit_k3k4=0;
//			k3_cnt=0;
//			bit_k3=0;
//
//			k4_cnt=0;
//			bit_k4=0;

			k3_cnt=0;
			bit_k3=0;
			bit_k3_L=0;

			k4_cnt=0;
			bit_k4=0;
			bit_k4_L=0;

			fsg_keynocol=0;


			keynum=0;
			keyram=0;
			return;
		}
		keynum--;	//退到case 4
		keynum--;
		return;
		default: 
		return;
	}
} 
void KeySelect(void)
{
	if(keyflag_1 | keyflag_2)
	{
	}

	if(r_K3K4used)
	{
		shortkeyk3=0;
		shortkeyk4=0;
		cnt_K3K4used++;
		if(cnt_K3K4used>=50)
		{
			cnt_K3K4used=0;
			r_K3K4used=0;
		}	
	}
}
void KeyFunction(void)
{
	if(shortkeyk1)	 // 电源
	{
		shortkeyk1=0;  

		if(!f_onoff)
		{
			f_onoff=1;
			BuzWork(1);
		}
	}
	if(longkeyk1)
	{
		longkeyk1=0;
		if(f_onoff)
		{
			f_onoff=0;
			f_settemp=0;
			fsg_lowpower=0;
			BuzWork(1);
		}			
	}
//	if(shortkeyk2)	 // 设置 
//	{
//		shortkeyk2=0;
//		if(f_onoff)
//		{
//			if(f_settemp)
//			{
//				f_settemp=0;
////				WriteROM();
//			}
//			else
//				f_settemp=1;
//			BuzWork(1);
//		}
//	}
	if(longkeyk2)
	{
		longkeyk2=0;
		if(f_onoff)
		{
			fsg_lowpower^=1;
		}
	}
	if(shortkeyk3|longkeyk3)	  // add
	{
		shortkeyk3=0; 
		longkeyk3=0;
		if(!f_settemp)
			f_settemp=1;
		else
		{
			BuzWork(1);
			Key_Add();
		}		 
	}

	if(shortkeyk4|longkeyk4)	 // sub
	{
		shortkeyk4=0;
		longkeyk4=0; 
		
		if(!f_settemp)
			f_settemp=1;
		else
		{
			BuzWork(1);
			Key_Sub();
		}    
	}

	if(longkeyk3k4)
	{
		longkeyk3k4=0;
		if(f_onoff)
		{
			if(rsg_show_H)
			{
				rsg_show_H=0;
				Settmp = TurnToCenti(Settmp);
				WriteROM();	
			}
			else
			{
				rsg_show_H=1;
				Settmp = TurnToFahren(Settmp);
				WriteROM();		
			}
		}
	}


//	if(shortkeyk5)
//	{
//		shortkeyk5=0;
//	}
//	if(shortkeyk6)	 
//	{
//		shortkeyk6=0;  
//	}
//	if(shortkeyk7)	
//	{
//		shortkeyk7=0;
//	}
//	if(shortkeyk8)
//	{
//		shortkeyk8=0;  
//	}
//	if(shortkeyk9)	
//	{
//		shortkeyk9=0;       
//	}
//	if(shortkeyk10)
//	{
//		shortkeyk10=0;
//	}
//	if(shortkeyk11)
//	{
//		shortkeyk11=0;
//	}
//	if(shortkeyk12)
//	{
//		shortkeyk12=0;
//	}
}
void ClearKey(void)
{
	keyflag_1=0;
	keyflag_2=0;
}
void KeyWork(void)
{
	keydebouce();
	KeySelect();
	KeyFunction();
	ClearKey();
}