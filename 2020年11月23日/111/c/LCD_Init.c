#include "H/SC93F843X_C.H"
#include "H/Function_Init.H"
/*****************************************************
*函数名称：void LCD_Init(void)
*函数功能：LCD初始化
*入口参数：void
*出口参数：void
*****************************************************/
void LCD_Init(void)
{
	P0VO = 0x1f;       //打开LCD电压输出功能，输出电压为1/2VDD
//	OTCON = 0x00;     //关闭内部分压电阻
//	OTCON = 0x04;     //设定内部分压电阻为25K
//	OTCON = 0x08;     //设定内部分压电阻为50K
	OTCON = 0x0C;     //设定内部分压电阻为100K
}