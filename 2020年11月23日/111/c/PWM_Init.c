#include "H/SC93F843X_C.H"
#include "H/Function_Init.H"
/*****************************************************
*�������ƣ�void PWM_Init(void)
*�������ܣ�PWM��ʼ��
*��ڲ�����void
*���ڲ�����void
*****************************************************/
void PWM_Init(void)
{
	PWMCON = 0x3A;		//PWM�����IO��PWMʱ��ΪFsys/4
	PWMPRD  = 59;			//PWM����=(59+1)*(1/6us)=10us	;
	PWMCFG  = 0x00;		//PWM���������,�����P00/P01/P02
 	PWMDTY0 = 30;			//PWM0��Duty = 30/60 =1/2
	PWMDTY1 = 15;     //PWM0��Duty = 15/60 =1/4
	PWMDTY2 = 10;     //PWM0��Duty = 10/60 =1/6
	PWMDTYA = 0x00;
	PWMCON |= 0x80;   //����PWM
	while(1);
}