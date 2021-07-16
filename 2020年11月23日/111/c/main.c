#include "H/SC93F843X_C.H"
#include "H/Function_Init.H"

/*************************************************************
˵����
1��Options for Target��Target1����BL51 Locate->Code Range:0x100����¼ѡ����ѡ��DISRST����λ����Ϊ��ͨIOʹ�ã�
2���ı�TEST�Ķ��壬���Էֱ���Զ�Ӧ�Ĺ��ܣ�
***************************************************************/

#define  TEST	    		9     // (0:BTM  1:EX  2:LCD 3:Timer  4:PWM  5:Uart0  6:Uart1  7:ADC  8:ADC_TS  9:IAP  10:TWI  11:SPI)

void main(void)
{
	IO_Init();
	while(1)
	{
		WDTCON |= 0x10;		    //�忴�Ź�	
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
			case 8:  ADC_TS_Init();    //�����¶ȴ�������ѹ
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