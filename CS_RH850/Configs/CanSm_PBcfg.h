/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : CanSM_PBcfg.h  Can State Manager
Author: Felix
******************************************************************************/
#ifndef CANSM_PBCFG_H
#define CANSM_PBCFG_H

#include "Std_Types.h"

typedef struct
{
    uint8 BorL1Count;  /* Count of L2(short) to L2(long) recovery */
    uint16 BorL1Time;  /* Short recovery time */
    uint16 BorL2Time;  /* Long recovery time */
    uint16 BorEnTime;  /* Busoff recovery ensure time */
} CanSm_ChCfgType;

typedef struct
{
    const CanSm_ChCfgType* ChCfg;
    uint8 ChNum;
} CanSm_ConfigType;


#endif

