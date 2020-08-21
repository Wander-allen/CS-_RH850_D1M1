/******************************************************************************
Copyright (C) 2019 Steven, mculib.net All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : CanIn_Define.h  CAN报文输入处理
Author: 
******************************************************************************/
#ifndef CANOUT_TYPES_H
#define CANOUT_TYPES_H

typedef void CanOut_TxFunType(const uint8*);

typedef struct
{
    uint16    CanId;
    uint16    Cycle;
    uint16    Event;
    uint16    EventCnt;
    CanOut_TxFunType *CallBack; 
}CanOut_InfoType;

#endif
