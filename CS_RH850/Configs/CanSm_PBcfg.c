/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : CanSm_PBcfg.c  Can State Manager
Author: Felix
******************************************************************************/
#include "CanSm_PBcfg.h"

static const CanSm_ChCfgType CanSmChCfg[] = 
{
    /* BorL1Count BorL1Time BorL2Time BorEnTime */
    {5,           100,      1000,     10000},
};

static const CanSm_ConfigType CanSmConifg = 
{
    CanSmChCfg,  /* NmCfg */
    sizeof(CanSmChCfg)/sizeof(CanSmChCfg[0]),  /* NmNum */
};

const CanSm_ConfigType* const CanSmCfgPtr = &CanSmConifg;
