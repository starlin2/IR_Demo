///////////////////////////////////////////////////
//
//	FILE:       MPC82_IR_Demo.c
//	AUTHOR:     Neo (Hsin-Chih Lin)
//	COPYRIGHT:  (c) Megawin Technology Co., Ltd.
//	CREATED:    2008.9.22
//	PURPOSE:    Demo IR Receiver Function
//	Description:                                       
//              Input:24MHz or 11MHz clock to 8051.    
//           IR Input:P3.2 (Use External Interrupt 0)  
//            Circuit:MPC82_IR_Demo_Circuit.jpg        
//
///////////////////////////////////////////////////
//#include "REG_MPC82L54.H"
#include "REG_MPC82G516.H"

#include "MPC_IR_LIB.h"
//#define DEBUG //For Megawin GNU Debugger
#ifdef DEBUG
#include "debug.h"
#endif
void Init_Uart(void)
{
//  11MHz / 12 / 16 / 9600 => 6
    TMOD|=0x20;                                  //Set Timer1 Mode 2
    SCON=0x50;                                  //Set UART Mode 1
    PCON=0x80;                                  //Set SMOD = 1 (Double Baud rate)
    TH1=0xfa;                                   //Set Timer1 overflow rate
    TL1=0xfa;
    TR1 =1;                                     //Start Timer1
}
///////////////////////////////////////////////////
//
//	Function:Output()
//  Output to RS232
//
///////////////////////////////////////////////////
void Output(unsigned char d)
{
        if(d>9 & d<16)
            SBUF = d + 0x37;
        else if(d<10)
            SBUF = d + 0x30;
        else if(d==0xaa)    //NewLine
            SBUF = 0x0a;
        else if(d==0xdd)    //Return
            SBUF = 0x0d;
        else
            SBUF = d;
        while(TI == 0){}    //Write transmitting has been finished
        TI = 0;
}
///////////////////////////////////////////////////
//
//	Function:OutputHex()
//  Output HEX to Char and a space
//
///////////////////////////////////////////////////
void OutputHex(unsigned char Uart_Data)
{
    unsigned char DataH,DataL;
    EX0 = 0;//disable External Int 0
    DataH = Uart_Data >> 4;
    DataL = Uart_Data & 0x0f;
    Output(DataH);
    Output(DataL);
    Output(0x20);
    EX0 = 1;//enable External Int 0
}
void Initial()
{
    IT0 = 1;//Set falling edge in External 0
    IE0 = 0;//Clean EX0 flag
    TMOD = 0x01;//Mode 1 (16bit timer)
    IE = 0x81;//Enable Timer 0 & External 0
}
void External_0_Interrupt() interrupt 0
{
    Get_IR_code();
    IE = 0x80;
}
///////////////////////////////////////////////////
//
//	MainLoop()
//
///////////////////////////////////////////////////
void main(void)
{
    extern unsigned char key_code;
#ifdef DEBUG
    Debug_clear_LCD();
#endif
    Initial();
    Init_Uart();
    Set_Freq_And_CustomCode(1,0x8213,2);//11Mhz
//    Set_Freq_And_CustomCode(2,0x866B);//24Mhz
    while(1)
    {
        IR_polling();

        if(key_code!=0xff)
        {
#ifdef DEBUG
            Debug_show_msg_to_LCD(key_code);
#endif
            OutputHex(key_code);
            key_code=0xff;
            Clear_para(0);//clear all para
        }
    }
}

