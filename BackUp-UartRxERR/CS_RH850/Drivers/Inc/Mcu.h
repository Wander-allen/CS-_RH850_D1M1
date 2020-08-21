/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : MCU.h 
Author: Wander 
******************************************************************************/

/******************************************************************************
* File Name    : Port.h
* Version      : 1.0.0.0
* Device(s)    : R7F701442
* Description  : This file implements SMC pin code generation.
* Creation Date: 2020-08-11
******************************************************************************/
#ifndef MCU_H
#define MCU_H
#ifdef __cplusplus
extern "C" {
#endif

#include "Std_Types.h"
#include "Mcu_Types.h"

extern void Mcu_Init(void);

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