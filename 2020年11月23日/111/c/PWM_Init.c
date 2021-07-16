#include "H/SC93F843X_C.H"
#include "H/Function_Init.H"
/*****************************************************
*函数名称：void PWM_Init(void)
*函数功能：PWM初始化
*入口参数：void
*出口参数：void
*****************************************************/
void PWM_Init(void)
{
	PWMCON = 0x3A;		//PWM输出到IO，PWM时钟为Fsys/4
	PWMPRD  = 59;			//PWM周期=(59+1)*(1/6us)=10us	;
	PWMCFG  = 0x00;		//PWM输出不反向,输出至P00/P01/P02
 	PWMDTY0 = 30;			//PWM0的Duty = 30/60 =1/2
	PWMDTY1 = 15;     //PWM0的Duty = 15/60 =1/4
	PWMDTY2 = 10;     //PWM0的Duty = 10/60 =1/6
	PWMDTYA = 0x00;
	PWMCON |= 0x80;   //开启PWM
	while(1);
}