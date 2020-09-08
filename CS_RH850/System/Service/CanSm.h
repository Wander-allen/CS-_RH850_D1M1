/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : CanSm.h  Can State Manager
Author: Filex
******************************************************************************/
#ifndef CANSM_H
#define CANSM_H
#ifdef __cplusplus
extern "C" {
#endif

#include "Std_Types.h"
#include "Can_PBcfg.h"

#define CANSM_MAJOR_VERSION     (0x00)
#define CANSM_MINOR_VERSION     (0x01)
#define CANSM_PATCH_VERSION     (0x00)

#define CANSM_MAX_NM_NUM        2

typedef enum
{
    CANSM_MODE_OFF,
    CANSM_MODE_RXONLY,
    CANSM_MODE_TXONLY,
    CANSM_MODE_FULL,
} CanSm_ModeType;

extern void CanSm_Init(void);
extern void CanSm_PollFunction(void);

extern void CanSm_RequestMode(Can_ChannelType Channel, CanSm_ModeType Mode);
extern CanSm_ModeType CanSm_GetCurrentMode(Can_ChannelType Channel);

#ifdef __cplusplus
}
#endif
#endif

