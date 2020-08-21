/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : DbgIf.c Debug uartͨѶ�ӿ�
Author: Steven 
******************************************************************************/
#include "DbgIf.h"
#include "DbgIf_Cbk.h"
#include "Ucs.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "Uart.h"
/******************************************************************************
* Function Name: DbgIf_UartTxCallback
* Description  : 
* Arguments    : None
* Return Value : None
******************************************************************************/
void DbgIf_UartTxCallback(uint8 Ch)
{
    (void)Ch;
}

/******************************************************************************
* Function Name: DbgIf_UartRxCallback
* Description  : 
* Arguments    : None
* Return Value : None
******************************************************************************/
uint16 DbgIf_UartRxCallback(uint8 Ch, const uint8* Data, uint16 Length)
{
    (void)Ch;
// //    (void)Data;
// //	Ucs_Write(UCS_CH_DEBUG, (uint8*)Data, Length);
// 	for(int i = 0;i<Length;i++)
// 	{
// 		//data_analysis(Data[i]);
// 	}
//     return Length;
	return 0;
}

/******************************************************************************
* Function Name: Dbgif_printf
* Description  : 
* Arguments    : None
* Return Value : None
******************************************************************************/
int Dbgif_printf(const char *format, ...)
{
	char buff[1024] = {0};
	va_list ap;
	//char *pScr = buff;
	int size;
	va_start(ap, format);
	//cs+buzhi
	//size = vsnprintf((char *)buff, sizeof(buff) - 1, format, ap);
	va_end(ap);

    if (size > 0)
    {
		Uart_transmit_n_size(buff, size);
	}
	
	return size;
	
}


