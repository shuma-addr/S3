#include "h\SC93F843X_C.H"	
#include "h\data_type.h"
#include "config.h"

#define VERSION 1

xdata unsigned char segval[4];
code unsigned char TAB_SEG[15]={
0XBB,//���֣�0
0X9,//���֣�1
0XB5,//���֣�2
0X9D,//���֣�3
0XF,//���֣�4
0X9E,//���֣�5
0XBE,//���֣�6
0X89,//���֣�7
0XBF,//���֣�8
0X9F,//���֣�9
0XB6,//���֣�E
0XA6,//���֣�F
0X4,//���֣�-
0X24,//���֣�r
0X2F,//���֣�H
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
		segval[2] &= ~(PLED_B3+PLED_C3);  //����ʾ
		segval[0] = TAB_SEG[12];	  //��ʾ����
		segval[1] = TAB_SEG[0-temp];	//��ʾ����	
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
		segval[0] = TAB_SEG[10];// ������룬��ʾ�������ֵ
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
		segval[0] =	TAB_SEG[10];	//ʮλ
		segval[1] =	TAB_SEG[temp];	//��λ		
	}
}
void showver(unsigned char ver)
{
//	segval[2] =	0x71;	//��ʾF
	segval[0] =	TAB_SEG[11];	//��ʾ-
	segval[1] =	TAB_SEG[ver];	//��λ		
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

	//�͹���ʱ����������
	if(fsg_lowpower)
		segval[2] |= PLED_E3;

	if(Output_led() == TEMPSUB)
	{
		//����ʱ��ѩ����	
		segval[2] |= PLED_A3;
	}
	else if(Output_led() == TEMPADD)
	{
		//����ʱ��̫����
		segval[2] |= PLED_D3;
	}
	else
	{}
//	showtemp(IOHCON);
	
}