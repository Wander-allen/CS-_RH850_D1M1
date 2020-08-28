/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Adc_PBcfg.c ADC driver For Nxp S32K14x
Author: Steven
******************************************************************************/
#include "Adc_PBcfg.h"

static const Adc_GroupCfgType AdcGroupCfg[] = 
{
    /* CFG1 CFG2 SC2 RES SC3 ChN ChList  EndCallback */
    {0x48,  80,  0,  0,  0,  1,  "\x0F", NULL},  /* VBAT_DET */
    {0x48,  80,  0,  0,  0,  1,  "\x05", NULL},  /* BL_TMP */
};

static const Adc_ConfigType AdcConfig = 
{
    AdcGroupCfg,  /* GroupCfg */
    sizeof(AdcGroupCfg) / sizeof(Adc_GroupCfgType),  /* GroupNum */
};

const Adc_ConfigType* const AdcCfgPtr = &AdcConfig;

