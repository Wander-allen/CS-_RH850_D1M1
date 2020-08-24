/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Uart_Isr.h  Uart interrupts request header file(RH850_D1M1_V2)
Author: Wander 
******************************************************************************/
#ifndef UART_ISR_H
#define UART_ISR_H
#ifdef __cplusplus
extern "C" {
#endif

#include "Std_Types.h"

extern void INTRLIN30UR0_IsrHandle( void );
extern void INTRLIN30UR1_IsrHandle( void );
extern void INTRLIN30UR2_IsrHandle( void );

#ifdef __cplusplus
}
#endif
#endif