#include "H/SC93F843X_C.H"
#include "H/Function_Init.H"

/*************************************************************
说明：
1、Options for Target‘Target1’：BL51 Locate->Code Range:0x100，烧录选项请选择DISRST，复位脚作为普通IO使用；
2、改变TEST的定义，可以分别测试对应的功能；
***************************************************************/

#define  TEST	    		9     // (0:BTM  1:EX  2:LCD 3:Timer  4:PWM  5:Uart0  6:Uart1  7:ADC  8:ADC_TS  9:IAP  10:TWI  11:SPI)

void main(void)
{
	IO_Init();
	while(1)
	{
		WDTCON |= 0x10;		    //清看门狗	
		switch(TEST)
		{
			case 0:  BTM_Init();
			break;
			case 1:  EX_Init();
			break;
			case 2:  LCD_Init();
			break;
			case 3:  Timer_Init();
			break;
			case 4:  PWM_Init();
			break;
			case 5:  Uart0_Init();
			break;
			case 6:  Uart1_Init();
			break;
			case 7:  ADC_Init();
			break;
			case 8:  ADC_TS_Init();    //测量温度传感器电压
			break;
			case 9:  IAP_Init();
			break;
			case 10: TWI_Init();
			break;
			case 11: SPI_Init();
			break;
			default: 
			break;
		}
	}
}