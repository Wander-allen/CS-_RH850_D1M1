/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : CanSM_Cbk.h  Can State Manager
Author: Filex
******************************************************************************/
#ifndef CANSM_CBK_H
#define CANSM_CBK_H
#ifdef __cplusplus
extern "C" {
#endif

#include "Can_Types.h"
#include "Can_PBcfg.h"

extern void CanSm_BusoffCallback(Can_ChannelType Channel);
extern void CanSm_ModeCsCallback(Can_ChannelType Channel, Can_CsModeType CsMode);

#ifdef __cplusplus
}
#endif
#endif

