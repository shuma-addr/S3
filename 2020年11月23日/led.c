#include "h\SC93F843X_C.H"	
#include "h\data_type.h"
#include "config.h"

#define VERSION 1

xdata unsigned char segval[4];
code unsigned char TAB_SEG[15]={
0XBB,//数字：0
0X9,//数字：1
0XB5,//数字：2
0X9D,//数字：3
0XF,//数字：4
0X9E,//数字：5
0XBE,//数字：6
0X89,//数字：7
0XBF,//数字：8
0X9F,//数字：9
0XB6,//数字：E
0XA6,//数字：F
0X4,//数字：-
0X24,//数字：r
0X2F,//数字：H
};


void ledinit()
{
//	switch (ledlevel)
//	{
//		case 0:
//			IOHCON = 0X00;//0000 0000
//			break;
//		case 1:
//			IOHCON = 0X55;//0101 0101
//			break;
//		case 2:
//			IOHCON = 0XAA;//1010 1010
//			break;
//		case 3:
//			IOHCON = 0XFF;//1111 1111
//			break;
//		default:
//			break;
//	}
}

void CloseAllled()
{
	segval[0] = 0X00;
	segval[1] = 0X00;
	segval[2] = 0X00;//0xff;
	segval[3] = 0X00;//0xff;
}
void showtemp(int temp)
{
	if(temp<0)
	{
		segval[2] &= ~(PLED_B3+PLED_C3);  //不显示
		segval[0] = TAB_SEG[12];	  //显示负号
		segval[1] = TAB_SEG[0-temp];	//显示负数	
	}
	else if(temp<100)
	{
		segval[2] &= ~(PLED_B3+PLED_C3);
		segval[0] = TAB_SEG[temp/10];
		segval[1] = TAB_SEG[temp%10];		
	}
	else if(temp<200)
	{
		segval[2] |= PLED_B3+PLED_C3;
		temp = temp%100;
		segval[0] = TAB_SEG[temp/10];
		segval[1] = TAB_SEG[temp%10];	
	}
	else
	{
		segval[2] &= ~(PLED_B3+PLED_C3);
		segval[0] = TAB_SEG[10];// 错误代码，显示超过最大值
		segval[1] = TAB_SEG[8];	 	
	}


	if(rsg_show_H)
	{
	 	segval[3] |= PLED_A4+PLED_B4+PLED_D4+PLED_C4+PLED_F4;	
	}
	else
	{
		segval[3] |= PLED_A4+PLED_B4+PLED_D4+PLED_E4+PLED_F4;
	}
}

void showerr(unsigned char temp)
{
	if(temp==1)
	{
		segval[0] =	TAB_SEG[10];	//十位
		segval[1] =	TAB_SEG[temp];	//个位		
	}
}
void showver(unsigned char ver)
{
//	segval[2] =	0x71;	//显示F
	segval[0] =	TAB_SEG[11];	//显示-
	segval[1] =	TAB_SEG[ver];	//个位		
}
//void PowerOnClearDisp(void)
//{
//	rsg_showver=0; 
//}


void ledwork()
{
	CloseAllled();
	if(rsg_showver)
	{
		showver(VERSION); 
//		showtemp(105);		
	}
	else
	{
		if(f_onoff)
		{
			if(ForceClose_lev1())
			{
				showerr(1);	
			}
			else if(f_settemp)
			{
				if(col_500ms|fsg_keynocol)
					showtemp(Settmp);
			}
			else //if(fig_diswork_500ms)
			{
				if(rsg_show_H)
					showtemp(Tmp_H);
				else
					showtemp(Tmp_C);
			}
		}
//		else
//			showtemp(100);
	}

	//低功耗时，月亮亮；
	if(fsg_lowpower)
		segval[2] |= PLED_E3;

	if(Output_led() == TEMPSUB)
	{
		//制冷时，雪花亮	
		segval[2] |= PLED_A3;
	}
	else if(Output_led() == TEMPADD)
	{
		//制热时，太阳亮
		segval[2] |= PLED_D3;
	}
	else
	{}
//	showtemp(IOHCON);
	
}