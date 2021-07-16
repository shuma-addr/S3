#include "H/SC93F843X_C.H"
#include "H/Function_Init.H"
/*****************************************************
*函数名称：void IO_Init(void)
*函数功能：IO初始化
*入口参数：void
*出口参数：void
*****************************************************/
void IO_Init(void)
{
	P0CON = 0xFF;  //设置P0为强推挽IO
	P0PH  = 0x00;
	P1CON = 0x00;  //设置P1为高阻态输入IO
	P1PH  = 0x00;
	P2CON = 0x00;  //设置P2为带上拉输入IO
	P2PH  = 0xFF;
	P5CON = 0xFF;  //设置P5为强推挽IO
	P5PH  = 0xFF;
}