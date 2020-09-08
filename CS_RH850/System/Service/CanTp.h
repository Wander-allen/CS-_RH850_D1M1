/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : CanTp.h Can Transport Layer Service
Author: Steven
******************************************************************************/
#ifndef CANTP_H
#define CANTP_H
#ifdef __cplusplus
extern "C" {
#endif

#include "Std_Types.h"
#include "CanTp_Define.h"

#define CANTP_MAJOR_VERSION     (0x00)
#define CANTP_MINOR_VERSION     (0x01)
#define CANTP_PATCH_VERSION     (0x00)

#define CANTP_MAX_CH_NUM        4

extern void CanTp_Init(void);
extern void CanTp_PollFunction(void);

extern void CanTp_Shutdown(void);
extern Std_ReturnType CanTp_Transmit(uint8 Ch, const uint8* Data, uint16 Length);

#ifdef __cplusplus
}
#endif
#endif

