/******************************************************************************
* File Name    : Port.h
* Version      : 1.0.0.0
* Device(s)    : R7F701442
* Description  : This file implements SMC pin code generation.
* Creation Date: 2020-08-11
******************************************************************************/
#ifndef UART_H
#define UART_H
#ifdef __cplusplus
extern "C" {
#endif

#include "Std_Types.h"
#include "Mcu_Types.h"

extern void Uart_Init(void);
extern void Uart_transmit_string(char data_string[]);
extern void Uart_transmit_n_size(char data_string[], uint16 size);

#ifdef __cplusplus
}
#endif
#endif