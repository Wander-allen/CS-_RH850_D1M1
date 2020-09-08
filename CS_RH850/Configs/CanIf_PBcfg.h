/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : CanIf_PBcfg.h  CAN Interface Service
Author: Steven
******************************************************************************/
#ifndef CANIF_PBCFG_H
#define CANIF_PBCFG_H
#ifdef __cplusplus
extern "C" {
#endif

#include "Can_Types.h"

typedef struct
{
    void(*TxCallback)(uint8 UPduId);
    uint32 CanId;
    uint8 DataLen;
    uint8 UPduId; /* User layer PduId */
    uint16 TxHthId;
    boolean Dynamic;  /* Dynamic CanId */
} CanIf_TxPduCfgType;

typedef struct
{
    void(*URxCallback)(uint8 UPduId, const uint8* Data, uint8 Length);
    uint32 CanId;
    uint8 DataLen;
    uint8 UPduId; /* User layer PduId */
} CanIf_RxPduCfgType;

typedef struct
{
    const uint16* RxPduTbl;  /* Rx pdu table for HRH */
    uint16 RxPduNum;
} CanIf_RxHrhCfgType;

typedef struct
{
    Can_PduType LPdu;
    uint8 Data[8];
} CanIf_CanTxPduType;

typedef struct
{
    CanIf_CanTxPduType* TxBuffer;
    uint16 TxBufSize;
    uint8 CanHth;
} CanIf_TxHthCfgType;

typedef struct
{
    const CanIf_RxPduCfgType* RxPduCfg;
    const CanIf_TxPduCfgType* TxPduCfg;
    const CanIf_RxHrhCfgType* RxHrhCfg;
    const CanIf_TxHthCfgType* TxHthCfg;
    uint16 RxPduNum;
    uint16 TxPduNum;
    uint16 RxHrhNum;
    uint16 TxHthNum;
    void(*BusoffCallback)(uint8 CanCh);
    void(*ModeCsCallback)(uint8 CanCh, Can_CsModeType Mode);
} CanIf_ConfigType;

#ifdef __cplusplus
}
#endif
#endif

