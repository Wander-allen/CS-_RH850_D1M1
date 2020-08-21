/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Uart_PBcfg.h Nxp S32K14x LPUART driver
Author: Steven
******************************************************************************/
#ifndef UART_PBCFG_H
#define UART_PBCFG_H

#include "Std_Types.h"
#include "Uart_Define.h"

#define RLIN30          (0xFFCE0000UL)
#define RLIN31          (0xFFCE1000UL)
#define RLIN32          (0xFFCE2000UL)
#define RLIN33          (0xFFCE3000UL)

#define UART_ERR_FE     0x08 /* Framing Error */
#define UART_ERR_ORE    0x04 /* Receiver Overrun Error */
#define UART_ERR_PE     0x40 /* Parity Error */
#define UART_ERR_BE     0X01 /* Bit Error */

typedef struct
{
    uint32 UartHw;      /* Hardware register starting address*/
    uint8  LWBR;        /* Select the bit sampling count and prescaler clock */
    uint16 LBRP01;      /* Set the baud rate prescaler */
    uint8  LBFC;        /* UART Configuration Register */
    uint8 Reserve;
    uint8 URxCh;
    uint8 UTxCh;
    void(*URxCallback)(uint8 URxCh, uint16 RxByte);
    void(*UTxCallback)(uint8 UTxCh, boolean TxIdle);
}Uart_ChCfgType;

typedef struct
{
    const Uart_ChCfgType* ChCfg;
    uint8 ChNum;
} Uart_ConfigType;

#endif

