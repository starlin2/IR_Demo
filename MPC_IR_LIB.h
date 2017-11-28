///////////////////////////////////////////////////
//
//	FILE:       MPC_IR_LIB.lib
//	AUTHOR:     Neo (Hsin-Chih Lin)
//	COPYRIGHT:  (c) Megawin Technology Co., Ltd.
//	CREATED:    2008.9.2
//	PURPOSE:    IR Decoder (NEC protocol) library
//
///////////////////////////////////////////////////

extern void Get_IR_code();
extern void IR_polling();
extern void Clear_para(unsigned char mode);
///////////////////////////////////////////////////
//
//	Function:Set_Freq_And_CustomCode(unsigned char num,unsigned int custom_code,unsigned char speed)
//  Parames:
//          num:1:11.0592Mhz
//              2:24Mhz
//          custom_code is IR transfer's custom code
//          speed:Repeat key speed 0(faster) ~ 10(slow)
//
///////////////////////////////////////////////////
extern void Set_Freq_And_CustomCode(unsigned char num,unsigned int custom_code,unsigned char speed);

