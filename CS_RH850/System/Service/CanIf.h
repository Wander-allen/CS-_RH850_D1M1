/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : CanIf.h  CAN Interface Service
Author: Steven
******************************************************************************/
#ifndef CANIF_H
#define CANIF_H
#ifdef __cplusplus
extern "C" {
#endif

#include "Std_Types.h"
#include "CanIf_Define.h"

#define CANIF_MAJOR_VERSION     (0x00)
#define CANIF_MINOR_VERSION     (0x02)
#define CANIF_PATCH_VERSION     (0x00)

#define CANIF_MAX_CANCH_NUM     1
#define CANIF_MAX_RXPDU_NUM     32
#define CANIF_MAX_TXPDU_NUM     16
#define CANIF_MAX_TXHTH_NUM     8

typedef enum
{
    CANIF_PM_BS_OFFLINE,  /* SET&GET:Both Rx&Tx offline. */
    CANIF_PM_RX_ONLINE,   /* SET:Rx online. GET:Rx online, Tx offline */
    CANIF_PM_TX_ONLINE,   /* SET:Tx online. GET:Tx online, Rx offline */
    CANIF_PM_BS_ONLINE,   /* SET&GET:Both Rx&Tx online */
    CANIF_PM_RX_OFFLINE,  /* SET:Rx offline */
    CANIF_PM_TX_OFFLINE,  /* SET:Tx offline */
} CanIf_PduModeType;

typedef enum
{
    CANIF_CS_STOP,
    CANIF_CS_START,
    CANIF_CS_SLEEP,
} CanIf_CsModeType;

extern void CanIf_Init(void);
extern void CanIf_PollFunction(void);

extern void CanIf_SetDynamicTxId(uint16 TxPduId, uint32 CanId);
extern Std_ReturnType CanIf_Transmit(uint16 TxPduId, const uint8* Data, uint8 Length);

extern CanIf_CsModeType CanIf_GetCanMode(uint8 CanCh);
extern Std_ReturnType CanIf_SetCanMode(uint8 CanCh, CanIf_CsModeType CsMode);

extern CanIf_PduModeType CanIf_GetPduMode(uint8 CanCh);
extern void CanIf_SetPduMode(uint8 CanCh, CanIf_PduModeType Mode);

#ifdef __cplusplus
}
#endif
#endif

