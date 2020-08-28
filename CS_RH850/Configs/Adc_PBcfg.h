/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Adc_PBcfg.h ADC driver For Nxp S32K14x
Author: Steven
******************************************************************************/
#ifndef ADC_PBCFG_H
#define ADC_PBCFG_H

#include "Std_Types.h"

typedef struct
{
    uint8 CFG1;   /* ValidBits:6F */
    uint8 CFG2;   /* ValidBits:FF */
    uint16 SC2;   /* Reserved */
    uint16 RES;   /* Reserved */
    uint8 SC3;    /* Reserved */
    uint8 ChNum;  /* Channel number of group */
    const uint8* ChList; /* Channel list */
    void(*EndCallback)(void);  /* 完成提示 */
} Adc_GroupCfgType;

typedef struct
{
    const Adc_GroupCfgType* GroupCfg;
    uint8 GroupNum;
} Adc_ConfigType;

#endif

