#include "H/SC93F843X_C.H"
#include "H/Function_Init.H"
/*****************************************************
*�������ƣ�void IO_Init(void)
*�������ܣ�IO��ʼ��
*��ڲ�����void
*���ڲ�����void
*****************************************************/
void IO_Init(void)
{
	P0CON = 0xFF;  //����P0Ϊǿ����IO
	P0PH  = 0x00;
	P1CON = 0x00;  //����P1Ϊ����̬����IO
	P1PH  = 0x00;
	P2CON = 0x00;  //����P2Ϊ����������IO
	P2PH  = 0xFF;
	P5CON = 0xFF;  //����P5Ϊǿ����IO
	P5PH  = 0xFF;
}