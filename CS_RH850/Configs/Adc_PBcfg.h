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
    uint32 VirCh;   /* ValidValue:0-20 */
    uint8  PhyCh;   /* ValidValue:0-15 */
}Adc_ChCfgType;

typedef struct 
{
    uint8   SGId;       /* Scan Group Id (0 - 3)*/
    uint32  SGVCSP;     /* Scan Group x Start Virtual Channel */
    uint32  SGVCEP;     /* Scan Group x End Virtual Channel */
    uint32  SGCR;       /* Scan Group x Control */
    void(*EndCallback)(void);  /* A/D conversion for SGx is completed. */
}Adc_GroupCfgType;

typedef struct 
{
    uint32  ADCR;
    uint32  SMPCR;
}Adc_ModuleCfgType;

typedef struct
{
    const Adc_ChCfgType* ChCfg;
    uint8 ChNum;
    const Adc_GroupCfgType* GroupCfg;
    uint8 GroupNum;
    const Adc_ModuleCfgType* ModuleCfg;
} Adc_ConfigType;


#endif

