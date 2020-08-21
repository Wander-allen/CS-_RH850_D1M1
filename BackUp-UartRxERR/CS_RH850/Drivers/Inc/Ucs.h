/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Ucs.h Uart Communication Service
Author: Steven
******************************************************************************/
#ifndef UCS_H
#define UCS_H
#ifdef __cplusplus
extern "C" {
#endif

#include "Std_Types.h"
#include "Ucs_Define.h"

#define UCS_MAJOR_VERSION       (0x00)
#define UCS_MINOR_VERSION       (0x01)
#define UCS_PATCH_VERSION       (0x00)

extern void Ucs_Init(void);
extern void Ucs_PollFunction(void);

extern Std_ReturnType Ucs_Write(uint8 Ch, void* Data, uint16 Length);
extern Std_ReturnType Ucs_WriteToHex(uint8 Ch, void* Data, uint16 Length);

extern Std_ReturnType Ucs_SetRxBuffer(uint8 Ch, uint8* Buffer, uint16 Size);
extern Std_ReturnType Ucs_SetTxBuffer(uint8 Ch, uint8* Buffer, uint16 Size);

extern void Ucs_ClearRxBuffer(uint8 Ch);
extern void Ucs_ClearTxBuffer(uint8 Ch);

#ifdef __cplusplus
}
#endif
#endif

