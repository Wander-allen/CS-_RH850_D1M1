/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Mcu.h 
Author: Wander 
******************************************************************************/
#ifndef MCU_H
#define MCU_H
#ifdef __cplusplus
extern "C" {
#endif

#include "Std_Types.h"
#include "Mcu_Types.h"

#define Mcu_FeedDog        Wdta_Clear

extern void Mcu_Init(void);
extern void Mcu_SoftReset(void);
extern void Mcu_GoDeepStop(void);
extern void Mcu_EicEnable(uint8 Ch, Eic_MethodType Method, Eic_PriorityType priority);
extern void MCu_EicDisnable(uint8 Ch);

#if 0
extern void Mcu_Init(const Mcu_ConfigType * ConfigPtr);
extern Std_Return_Type Mcu_InitClock(Mcu_ClockType ClockSetting);
extern Mcu_PllStatusType Mcu_GetPllStatus(void);
extern void Mcu_DistributePllClock(void);
extern Std_Return_Type Mcu_InitRamSection(Mcu_RamSectionType RamSection);
#endif

#ifdef __cplusplus
}
#endif
#endif