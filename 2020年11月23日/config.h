#ifndef _CONFIG_H
#define _CONFIG_H

#define PLED_A3  (1<<7)	//segval[2]
#define PLED_B3  (1<<0)
#define PLED_C3  (1<<3)
#define PLED_D3  (1<<4)
#define PLED_E3  (1<<5)

//#define G3  (1<<2)

#define PLED_A4  (1<<7)	//segval[3]
#define PLED_B4  (1<<0)
#define PLED_C4  (1<<3)
#define PLED_D4  (1<<4)
#define PLED_E4  (1<<5)
#define PLED_F4  (1<<1)

enum 
{
      TEMPSUB=1, TEMPADD
};

#define  EEP_FLAG 0x55    //EEP写入标志
#define  EEP_FLAG1 0xaa    //EEP写入标志


extern xdata unsigned char segval[4];
extern bit fs_col500ms;
extern code unsigned char TAB_SEG[15];



extern void ledwork();
extern void ShowTmp(unsigned char temp);



extern bit err_sense;
extern bit f_keydown;


extern unsigned char Tmp_Flag;
extern xdata int Settmp;
//extern unsigned char Settmp_H;
extern xdata int Tmp_H;
extern unsigned char btime250us,btime1ms,btime10ms,btime20ms,btime500ms,btime1s;
extern unsigned int cnt0,cnt1,cnt2,cnt3,cnt4,cnt5,cnt6,cnt7,cnt8;
extern unsigned int	Key_Buf;

extern unsigned int ad3_result,ad3_result_sum,ad3_result_ave;

extern unsigned char Delaybuzz;
extern unsigned char xdata Test_Value;
extern bit f_lamp;
extern bit f_onoff;
extern bit f_settemp;
extern bit col_500ms;
extern bit fsg_keynocol;
extern unsigned char xdata rsg_show_H;
extern bit fsg_lowpower;
extern xdata unsigned char rsg_showver;
extern xdata int Tmp_C; 
extern bit fig_adjust_500ms;
extern bit fig_diswork_500ms;
extern bit fsg_keynocolbf;

extern bit err_NTC_short;	
extern bit err_NTC_open;
//extern xdata unsigned char rsg_TMPNTC;

extern void Get_Tmp(void);
extern void ADC_ave(void);

extern void BasicDisplayer(void);
extern void DispTurn(void);
//extern void showtemp(unsigned char ttt);
extern void showtemp(int temp);
extern void BasicDisp(void);
extern void DisWork(void);
extern bit ForceClose_lev1(void);
extern void FanWork(void) ;




extern void Relaywork();
extern void BuzWork(unsigned char temp);
extern void ClearSetTimeCount(void);  //清设置计时
//extern unsigned char TurnToCenti(unsigned char temp);
int TurnToCenti(int temp);
//extern unsigned char TurnToFahren(unsigned char temp);
int TurnToFahren(int temp);
extern void WriteROM(void);
extern unsigned char Output_led();
extern unsigned char IAPRead(unsigned int Addr);
extern void IAP_Init(void);
extern void IAPWrite(unsigned int Addr,unsigned char Data);





#endif