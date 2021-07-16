#include "config.h"


bit fs_col500ms;


bit err_sense;
bit f_keydown;



unsigned char Delaybuzz;
bit f_lamp=0;	
//unsigned char dis_value3;
bit f_onoff=0;
bit f_settemp=0;
bit col_500ms=0;
unsigned char Tmp_Flag;
xdata int Settmp;
//unsigned char Settmp_H;
xdata int Tmp_H;
//bit fsg_keynocol;
bit fsg_keynocolbf;
unsigned char xdata rsg_show_H;
//unsigned char Tmp;
bit fsg_lowpower=0;
unsigned char xdata Test_Value=0;

xdata unsigned char rsg_showver=0;
xdata int Tmp_C; 
bit fig_adjust_500ms=0;
bit fig_diswork_500ms=0;
bit err_NTC_short=0;	
bit err_NTC_open=0;
//xdata unsigned char rsg_TMPNTC;