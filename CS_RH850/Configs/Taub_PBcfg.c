/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Tbm_PBcfg.c Timebase Moudle Driver(Nxp S32K14x Series SYSTICK Timer)
Author: Steven
******************************************************************************/
#include "SchM.h"
#include "Taub_PBcfg.h"


static const Taub_TimeCfgType TaubTimeCfg[] = 
{
    /* TickCallback   CSRv */
    {SchM_TaubCallback, 625UL},  /* 625KHz / 625 = 1K Hz*/
};

static const Taub_ConfigType TaubConfig = 
{
    TaubTimeCfg,
    sizeof(TaubTimeCfg)/sizeof(Taub_TimeCfgType),
};

const Taub_ConfigType* const TaubCfgPtr = &TaubConfig;

