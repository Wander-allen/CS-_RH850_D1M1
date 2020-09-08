/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : CanIf_Cbk.h  CAN Interface Service
Author: Steven
******************************************************************************/
#ifndef CANIF_CBK_H
#define CANIF_CBK_H
#ifdef __cplusplus
extern "C" {
#endif

#include "Can_Types.h"

extern void CanIf_TxCallback(uint16 TxPduId);
extern void CanIf_RxCallback(uint8 Hrh, uint32 Id, uint8 Dlc, const uint8* Data);
extern void CanIf_ModeCsCallback(uint8 CanCh, Can_CsModeType Mode);
extern void CanIf_BusOffCallback(uint8 CanCh);

#ifdef __cplusplus
}
#endif
#endif

