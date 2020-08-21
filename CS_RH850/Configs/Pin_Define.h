/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Port_Define For Renesas Rh850 D1M1_V2 Series
Author: Steven
******************************************************************************/
#ifndef PIN_DEFINE_H
#define PIN_DEFINE_H
#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    PORT_P0     = 0,
    PORT_P1     = 1,
    PORT_P3     = 3,
    PORT_P10    = 10,
    PORT_P11    = 11,
    PORT_P16    = 16,
    PORT_P17    = 17,
    PORT_P21    = 21,
    PORT_P22    = 22,
    PORT_P42    = 42,
    PORT_P43    = 43,
    PORT_P44    = 44,
    PORT_P45    = 45,
    JPORT_PJP0  = 46,
    PORT_NUM
}Port_ChannelType;

#if 0
typedef enum
{
    GPIO_OUT    = 0xF0,
    GPIO_IN     = 0xF1,
    ALT_OUT1    = 0x00,
    ALT_IN1     = 0x01,
    ALT_OUT2    = 0x10,
    ALT_IN2     = 0x11,
    ALT_OUT3    = 0x20,
    ALT_IN3     = 0x21,
    ALT_OUT4    = 0x30,
    ALT_IN4     = 0x31,
    ALT_OUT5    = 0x40,
    ALT_IN5     = 0x41,
    ALT_OUT6    = 0x50,
    ALT_IN6     = 0x51,
    
}Port_FunType;
#endif


#ifdef __cplusplus
}
#endif
#endif

