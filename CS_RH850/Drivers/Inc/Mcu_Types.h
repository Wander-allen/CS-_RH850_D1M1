/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Mcu_Types.h 
Author: Wander 
******************************************************************************/
#ifndef MCU_TYPES_H
#define MCU_TYPES_H
#ifdef __cplusplus
extern "C" {
#endif

#include "Std_Types.h"

typedef enum
{
    DIRECT_BRANCH = 0,
    TABLE_REFERENCE
}Eic_MethodType;

typedef enum
{
    PRIORITY_0 = 0,
    PRIORITY_1,
    PRIORITY_2,
    PRIORITY_3,
    PRIORITY_4,
    PRIORITY_5,
    PRIORITY_6,
    PRIORITY_7,
    PRIORITY_8,
    PRIORITY_9,
    PRIORITY_10,
    PRIORITY_11,
    PRIORITY_12,
    PRIORITY_13,
    PRIORITY_14,
    PRIORITY_15,

}Eic_PriorityType;

#ifdef __cplusplus
}
#endif
#endif