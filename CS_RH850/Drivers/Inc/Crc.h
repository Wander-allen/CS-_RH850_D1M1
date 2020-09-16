/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Crc.h 
Author: Wander 
******************************************************************************/
#ifndef CRC_H
#define CRC_H
#ifdef __cplusplus
extern "C" {
#endif

#include "Std_Types.h"

extern void Crc_Init(void);
extern uint16 Crc_GetCalData(void);

#ifdef __cplusplus
}
#endif
#endif