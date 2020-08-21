/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : DbgIf_Cbk.h Debug uart通讯接口
Author: Steven 
******************************************************************************/
#ifndef DBGIF_CBK_H
#define DBGIF_CBK_H

#include "Std_Types.h"

extern void DbgIf_UartTxCallback(uint8 Ch);
extern uint16 DbgIf_UartRxCallback(uint8 Ch, const uint8* Data, uint16 Length);

#endif

