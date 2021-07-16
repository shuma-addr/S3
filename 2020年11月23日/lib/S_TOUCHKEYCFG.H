//*************************************************************************************************
//  Copyright (c) 	深圳市赛元微电子有限公司
//	文件名称	:  S_TouchKeyCFG.h
//	作者		: 
//	模块功能	:  触控键配置文件
// 	版本		:  V0.1
// 	更改记录	:
//************************************************************************************************
#ifndef __S_TOUCHKEYCFG_H__
#define __S_TOUCHKEYCFG_H__
#define		    SOCAPI_SET_TOUCHKEY_TOTAL					  4 	
#define			SOCAPI_SET_TOUCHKEY_CHANNEL					  0x0000000f																																			 
unsigned int  code TKCFG[17] = {0,1,0,7,10,3000,300,200,2,0,0,2,100,10,65535,65535,20}; 
unsigned char code TKChannelCfg[5][8]={
0x02,0x2e,0x04,0x08,0x20,0x05,0x01,0xda,
0x02,0x2e,0x04,0x08,0x1b,0x05,0x01,0xd9,
0x02,0x2e,0x04,0x08,0x15,0x05,0x01,0xce,
0x02,0x2e,0x04,0x08,0x16,0x05,0x01,0xd2,
0x02,0x2e,0x04,0x08,0x1c,0x05,0x01,0xbe,
};
#endif 


