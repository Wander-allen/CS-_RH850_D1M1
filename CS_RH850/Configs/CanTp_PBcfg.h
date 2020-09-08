/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : CanTp_PBcfg.h Can Transport Layer Service
Author: Steven
******************************************************************************/
#ifndef CANTP_PBCFG_H
#define CANTP_PBCFG_H

#include "CanTp.h"

typedef struct
{
    uint8 RxBS;  /* Reserved fixed 0 */
    uint8 RxSTmin; /* ms */
    uint16 NAr;  /* ms */
    uint16 NBr;  /* ms reserved */
    uint16 NCr;  /* ms */
    uint16 NAs;  /* ms */
    uint16 NBs;  /* ms */
    uint16 NCs;  /* ms reserved */
    uint16 WFTmax; /* Max FC.Wait Frame Transmitsion */
    uint8 Padding;    
    uint8 UTxChId;
    uint8 URxChId;
    uint16 LTxChId;
    void(*TpRxCallback)(uint8 URxChId, uint8 Error);
    Std_ReturnType(*TpRxStartCbk)(uint8 URxChId, uint16 Length);
    Std_ReturnType(*TpCopyRxData)(uint8 URxChId, uint16 Offset, const uint8* Data, uint16 Length);
    void(*TpTxCallback)(uint8 UTxChId, uint8 Error);
    Std_ReturnType(*TpCopyTxData)(uint8 UTxChId, uint16 Offset, uint8* Data, uint16 Length);
    Std_ReturnType(*LPduTransmit)(uint16 LTxChId, const uint8* Data, uint8 Length);
} CanTp_ChCfgType;

typedef struct
{
    const CanTp_ChCfgType* ChCfg;
    const uint8* NRxPduChMap;
    const uint8* NTxPduChMap;
    uint8 ChNum;
    uint8 NRxPduNum;
    uint8 NTxPduNum;
} CanTp_ConfigType;

#endif

