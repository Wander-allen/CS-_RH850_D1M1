/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : CanTp_Cbk.h Can Transport Layer Service
Author: Steven
******************************************************************************/
#ifndef CANTP_CBK_H
#define CANTP_CBK_H
#ifdef __cplusplus
}
#endif

#include "Std_Types.h"
#include "CanTp_Define.h"

extern void CanTp_RxCallback(uint8 RxPduId, const uint8* Data, uint8 Length);
extern void CanTp_TxCallback(uint8 TxPduId);

#ifdef __cplusplus
}
#endif
#endif

