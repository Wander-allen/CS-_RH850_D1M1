/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : MCU_Types.h 
Author: Wander
******************************************************************************/

/******************************************************************************
* File Name    : Port.h
* Version      : 1.0.0.0
* Device(s)    : R7F701442
* Description  : This file implements SMC pin code generation.
* Creation Date: 2020-08-11
******************************************************************************/
#ifndef MCU_TYPES_H
#define MCU_TYPES_H
#ifdef __cplusplus
extern "C" {
#endif

#include "Std_Types.h"

 typedef enum{
    MCU_PLL_STATUS_UNDEFINED,
    MCU_PLL_STATUS_LOCKED,
    MCU_PLL_STATUS_UNLOCKED
 }Mcu_PllStatusType;


#ifdef __cplusplus
}
#endif
#endif