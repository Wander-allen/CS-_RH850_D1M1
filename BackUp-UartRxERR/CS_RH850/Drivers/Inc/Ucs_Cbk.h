/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Ucs_Cbk.h Uart Communication Service
Author: Steven
******************************************************************************/
#ifndef UCS_CBK_H
#define UCS_CBK_H

#include "Std_Types.h"
#include "Ucs_Define.h"

extern void Ucs_UartRxCbk(uint8 Ch, uint16 RxByte);
extern void Ucs_UartTxCbk(uint8 Ch, boolean TxIdle);

#endif

