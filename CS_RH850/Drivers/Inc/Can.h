/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Can.h 
Author: Wander 
******************************************************************************/
#ifndef CAN_H
#define CAN_H
#ifdef __cplusplus
extern "C" {
#endif

#include "Std_Types.h"
#include "Can_PBcfg.h"
#include "Can_Types.h"


extern void Can_Init(void);
extern Std_ReturnType CAN_Transmit(Can_ChannelType Channel, const Can_PduType* pFrame);

#ifdef __cplusplus
}
#endif
#endif