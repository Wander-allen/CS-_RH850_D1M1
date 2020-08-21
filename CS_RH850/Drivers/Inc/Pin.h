/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Port.h 
Author: Wander 
******************************************************************************/

/******************************************************************************
* File Name    : Port.h
* Version      : 1.0.0.0
* Device(s)    : R7F701442
* Description  : This file implements SMC pin code generation.
* Creation Date: 2020-08-11
******************************************************************************/
#ifndef PORT_H
#define PORT_H
#ifdef __cplusplus
extern "C" {
#endif

#include "Std_Types.h"
#include "Pin_PBcfg.h"

extern void Port_Init(void);
extern uint16 Port_Read(Port_ChannelType Channel);
extern void Port_Write(Port_ChannelType Channel, uint32 Levels);

extern Std_StatusType Port_ReadPin(Port_ChannelType Channel, uint8 PinId);
extern void Port_WritePin(Port_ChannelType Channel, uint8 PinId, Std_StatusType Level);
extern Std_StatusType Port_FlipPin(Port_ChannelType Channel, uint8 PinId);

extern void Port_SetPinIO(Port_ChannelType Channel, uint8 PinId, Std_StatusType Status);
extern Std_StatusType Port_GetPinIO(Port_ChannelType Channel, uint8 PinId);

extern void Port_SetPinFun(Port_ChannelType Channel, uint8 PinId, uint32 Ppcr);

#ifdef __cplusplus
}
#endif
#endif