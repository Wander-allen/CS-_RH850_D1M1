/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Uart.PBcfg Nxp S32K14x LPUART driver
Author: Steven
******************************************************************************/
#include "Uart_PBcfg.h"
#include "Ucs_Cbk.h"

static const Uart_ChCfgType UartChCfg[] = 
{
    /* Ch0: DEBUG Buadrate:115200bps */
    {
        RLIN30,         /* UartHw */
        0xF0,           /* Select the bit sampling count and prescaler clock */
        0x42,           /* Set the baud rate prescaler */
        0x00,           /* UART Configuration Register */
        0,              /* Reserved */
        UCS_CH_DEBUG,   /* URxCh */
        UCS_CH_DEBUG,   /* UTxCh */
        Ucs_UartRxCbk,  /* RxCallback */
        Ucs_UartTxCbk,  /* TxCallback */
    },
};

static const Uart_ConfigType UartConfig = 
{
    UartChCfg,  /* ChCfg */
    sizeof(UartChCfg)/sizeof(Uart_ChCfgType),  /* ChNum */
};

const Uart_ConfigType* const UartCfgPtr = &UartConfig;

