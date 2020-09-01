/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Cpu.h 
Author: Wander 
******************************************************************************/
#ifndef CPU_H
#define CPU_H
#ifdef __cplusplus
extern "C" {
#endif

#include "Std_Types.h"

#define CPU_EnableAllInterrupts()   __EI()
#define CPU_DisableAllInterrupts()  __DI()

extern void Cpu_Delay1US(void);
extern void Cpu_DelayUS(uint16 USTime);
extern void Cpu_DelayMS(uint16 MSTime);


#ifdef __cplusplus
}
#endif
#endif