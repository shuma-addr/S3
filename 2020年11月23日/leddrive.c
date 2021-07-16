#include "h\SC93F843X_C.H"	
#include "h\data_type.h"
#include "config.h"

//extern void Leddrivework();

#define COM0  P17
#define COM1  P16
#define COM2  P07
#define COM3  P21



void Leddriveinit()
{
	//com¿Ú£ºP17,P16,P21,P07  SEG¿Ú£ºP27,P25-22,P20,P06
	P0CON |= 0xC0; //1100 0000
	P0PH  &= ~0xC0;
		
	P1CON |= 0xC0;  //1100 0000
	P1PH  &= ~0xC0;

	P2CON |= 0xBF; //1011 1111
	P2PH  &= ~0xBF;	

	IOHCON |= 0xFF;//1111 1100
//	IOHCON |= 0x00;//1111 1100
}
void SetAllcom()
{
	COM0 = 0;
	COM1 = 0;
	COM2 = 0;
	COM3 = 0;	
}

void ClearAllseg()
{
	P2 &= ~0xbd;
	P06 = 0;
}
void ScanEcom()
{
	static unsigned char comcnt;

//	if(!fsg_lowpower)
//	{
//		switch (comcnt)
//		{
//			case 0:
//				comcnt++;
//				COM0 = 1;
//				P2 |= segval[0] & 0xbd;    //1011 1101
//				if(segval[0] & 0x02)	//0000 0010
//					P06 = 1;	
//				break;
//			case 1:
//				comcnt++;
//				COM1 = 1;
//				P2 |= segval[1] & 0xbd;    //1011 1101
//				if(segval[1] & 0x02)	//0000 0010
//					P06 = 1;	
//				break;
//			case 2:
//				comcnt++;
//				COM2 = 1;
//				P2 |= segval[2] & 0xbd;    //1011 1101
//				if(segval[2] & 0x02)	//0000 0010
//					P06 = 1;
//				break;
//			case 3:
//				comcnt=0;
//				COM3 = 1;
//				P2 |= segval[3] & 0xbd;    //1011 1101
//				if(segval[3] & 0x02)	//0000 0010
//					P06 = 1;
//				break;
//			default:
//				comcnt = 0;
//				break;
//		}	
//	}
//	else
//	{
//		switch (comcnt)
//		{
//			case 0:
//				comcnt++;
//				COM0 = 1;
//				P2 |= segval[0] & 0xbd;    //1011 1101
//				if(segval[0] & 0x02)	//0000 0010
//					P06 = 1;	
//				break;
//			case 1:
//				comcnt++;	
//				break;
//			case 2:
//				comcnt++;
//				COM1 = 1;
//				P2 |= segval[1] & 0xbd;    //1011 1101
//				if(segval[1] & 0x02)	//0000 0010
//					P06 = 1;	
//				break;
//			case 3:
//				comcnt++;	
//				break;
//			case 4:
//				comcnt++;
//				COM2 = 1;
//				P2 |= segval[2] & 0xbd;    //1011 1101
//				if(segval[2] & 0x02)	//0000 0010
//					P06 = 1;
//				break;
//			case 5:
//				comcnt++;	
//				break;
//			case 6:
//				comcnt++;
//				COM3 = 1;
//				P2 |= segval[3] & 0xbd;    //1011 1101
//				if(segval[3] & 0x02)	//0000 0010
//					P06 = 1;
//				break;
//			case 7:
//				comcnt=0;	
//				break;
//			default:
//				comcnt = 0;
//				break;
//		}		
//	}
		switch (comcnt)
		{
			case 0:
				comcnt++;
				COM0 = 1;
				P2 |= segval[0] & 0xbd;    //1011 1101
				if(segval[0] & 0x02)	//0000 0010
					P06 = 1;	
				break;
			case 1:
				comcnt++;	
				break;
			case 2:
				comcnt++;	
				break;
			case 3:
				comcnt++;
				COM1 = 1;
				P2 |= segval[1] & 0xbd;    //1011 1101
				if(segval[1] & 0x02)	//0000 0010
					P06 = 1;	
				break;
			case 4:
				comcnt++;	
				break;
			case 5:
				comcnt++;	
				break;
			case 6:
				comcnt++;
				COM2 = 1;
				P2 |= segval[2] & 0xbd;    //1011 1101
				if(segval[2] & 0x02)	//0000 0010
					P06 = 1;
				break;
			case 7:
				comcnt++;	
				break;
			case 8:
				comcnt++;	
				break;
			case 9:
				comcnt++;
				COM3 = 1;
				P2 |= segval[3] & 0xbd;    //1011 1101
				if(segval[3] & 0x02)	//0000 0010
					P06 = 1;
				break;
			case 10:
				comcnt++;	
				break;
			case 11:
				comcnt=0;	
				break;
			default:
				comcnt = 0;
				break;
		}		
}

void Leddrivework()
{
	SetAllcom();
	ClearAllseg();
	ScanEcom();	
}

