/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Ucs_PBcfg.h Uart Communication Service
Author: Steven
******************************************************************************/
#ifndef UCS_TYPES_H
#define UCS_TYPES_H

#include "Std_Types.h"

typedef struct
{
    uint16(*URxCallback)(uint8 URxCh, const uint8* Data, uint16 Length);
    void(*UTxCallback)(uint8 UTxCh);  /* Tx Idle Callback */
    uint8 UartCh; /* Uart Channel */
    uint8 URxCh;  /* Upper layer Rx Channel */
    uint8 UTxCh;  /* Upper layer Tx Channel */
    uint8 Reserved;
    uint16 MinRecLen;  /* Minimum receive length */
    uint16 RxOverTime; /* Receive data over time */
    uint8* RxBuffer;   /* Default Rx buffer point */
    uint8* TxBuffer;   /* Default Tx buffer point */
    uint16 RxBufSize;  /* Default Rx buffer size */
    uint16 TxBufSize;  /* Default Tx buffer size */
} Ucs_ChCfgType;

typedef struct
{
    const Ucs_ChCfgType* ChCfg;
    uint8 ChNum;
} Ucs_ConfigType;

#endif

