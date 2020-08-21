/******************************************************************************
Copyright (C) 2019 Steven, mculib.net All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : CanIn_Cbk.h  CAN报文输入处理
Author: 
******************************************************************************/
#ifndef CANIN_CBK_H
#define CANIN_CBK_H

#include "Std_Types.h"
#include "CanIn_Define.h"

extern void CanIn_RxCallback(CanIn_ID RxPduId, const uint8* Data, uint8 Length);

#endif

