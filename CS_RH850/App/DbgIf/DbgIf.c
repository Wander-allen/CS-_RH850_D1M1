/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : DbgIf.c Debug uart通讯接口
Author: Steven 
******************************************************************************/
#include "DbgIf.h"
#include "DbgIf_Cbk.h"
#include "Ucs.h"
//#include "updata_module.h"
#include "stdarg.h"
#include "string.h"
#include "stdio.h"
#include "lpuart.h"
/******************************************************************************
函数名称: void DbgIf_UartTxCallback(uint8 Ch)
函数说明: 
最后修改: Steven
******************************************************************************/
void DbgIf_UartTxCallback(uint8 Ch)
{
    (void)Ch;
}

/******************************************************************************
函数名称: uint16 DbgIf_UartRxCallback(uint8 Ch, const uint8* Data, uint16 Length)
函数说明: 
最后修改: Steven
******************************************************************************/
uint16 DbgIf_UartRxCallback(uint8 Ch, const uint8* Data, uint16 Length)
{
    (void)Ch;
//    (void)Data;
//	Ucs_Write(UCS_CH_DEBUG, (uint8*)Data, Length);
	for(int i = 0;i<Length;i++)
	{
		//data_analysis(Data[i]);
	}
    return Length;
}

/******************************************************************************
函数名称: int Dbgif_printf(const char *format, ...)
函数说明: 
最后修改: Wander
******************************************************************************/
int Dbgif_printf(const char *format, ...)
{
	char buff[1024] = {0};
	va_list ap;
	//char *pScr = buff;
	int size;

	va_start(ap, format);
	size = vsnprintf((char *)buff, sizeof(buff) - 1, format, ap);
	va_end(ap);

    if (size > 0)
    {
		Lpuart2_transmit_n_size(buff, size);
	}
	
	return size;
	
}


