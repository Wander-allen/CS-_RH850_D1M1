/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Uart.h 
Author: Wander 
******************************************************************************/
#ifndef UART_H
#define UART_H
#ifdef __cplusplus
extern "C" {
#endif

#include "Std_Types.h"

extern void Uart_Init(void);
extern void Uart_DeInit(void);

extern Std_ReturnType Uart_Write(uint8 Ch, uint16 TxByte);

extern void Uart_SetRxFun(uint8 ch, Std_ReturnType status); /* 打开或关闭接收功能 */
extern void Uart_SetTxFun(uint8 ch, Std_ReturnType status); /* 打开或关闭发送功能 */

extern void Uart_SetRxIrq(uint8 ch, Std_ReturnType status); /* 打开或关闭接收&错误中断功能 */
extern void Uart_SetTxIrq(uint8 ch, Std_ReturnType status); /* 打开或关闭发送中断功能 */

void Uart_transmit_string(char data_string[]);
#ifdef __cplusplus
}
#endif
#endif