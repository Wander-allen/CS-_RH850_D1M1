/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Port.c 
Author: Wander 
******************************************************************************/

/******************************************************************************
Pragma directive
******************************************************************************/

/******************************************************************************
Includes
******************************************************************************/
#include "ioDefine.h"
#include "Det.h"
#include "Ucs.h"

/******************************************************************************
#Define
******************************************************************************/

/******************************************************************************
Global variables and functions
******************************************************************************/

/******************************************************************************
* Function Name: Uart_Init
* Description  : Uart初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
void Ucs_ClearRxBuffer(uint8 Ch)
{
    (void)Ch;
}
void Ucs_ClearTxBuffer(uint8 Ch)
{
    (void)Ch;
}
void Ucs_UartRxCbk(uint8 Ch, uint16 RxByte)
{
    (void)Ch;
    (void)RxByte;
}

void Ucs_UartTxCbk(uint8 Ch, boolean TxIdle)
{
    (void)Ch;
    (void)TxIdle;
}

