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

typedef enum
{
	PIN0 	= 0,
	PIN1	=1,
	PIN2	=2,
	PIN3	=3,
	PIN4	=4,
	PIN5	=5,
	PIN6	=6,
	PIN7	=7,
	PIN8	=8,
	PIN9	=9,
	PIN10	=10,
	PIN11	=11,
	PIN12	=12,
	PIN13	=13,
	PIN14	=14,
	PIN15	=15,
}Pin_IdType;

typedef enum
{
	Pin_Out,	
	Pin_In,
}Port_ModType;

typedef enum
{
	Normal_Port,
	Alter_Func1,
	Alter_Func2,
	Alter_Func3,
	Alter_Func4,
	Alter_Func5,
	Alter_Func6,
}Port_FuncType;

typedef enum
{
	Port_IP_SoftCtl,
	Port_IP_DirCtl,	
}Port_IPCtlType;

typedef enum
{
	PuPd_No_Set,
	Port_Pu,
	Port_Pd,
}Port_pUpDType;

typedef enum
{
	Port_IB_Off,
	Port_IB_On,
}Port_IBType;

typedef enum
{
	Port_PBD_Off,
	Port_PBD_On,
}T_Port_PBDType;

typedef enum
{
	Port_Push_Pull,
	Port_Open_Drain,	
}T_Port_OPBFType;

#ifdef __cplusplus
}
#endif
#endif

