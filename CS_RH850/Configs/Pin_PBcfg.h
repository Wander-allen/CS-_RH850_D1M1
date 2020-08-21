/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Port_PBcfg.h For Renesas Rh850 D1M1_V2 Series
Author: Steven
******************************************************************************/
#ifndef PIN_PBCFG_H
#define PIN_PBCFG_H
#ifdef __cplusplus
extern "C" {
#endif

#include "Std_Types.h"
#include "Pin_Define.h"

typedef struct 
{
    Port_ChannelType Channel;   /* Port Group*/
    uint16 PMC_JPMC;    /* Port Mode Control Register */
    uint16 PM_JPM;      /* Port Mode Register */
    uint16 PIBC_JPIBC;  /* Port Input Buffer Control Register */
    uint16 P_JP;        /* Port Register */
} Port_GpioCfgType;

/* Pin PCR configuration */
typedef struct
{
    Port_ChannelType Channel;   /* Port Group*/
    uint8 Pin;      /* Pin Id*/
    uint32 PCRv;    /* Port Control Register */
} Port_PpcrCfgType;

typedef struct 
{
    const Port_GpioCfgType* GpioCfg;
    const Port_PpcrCfgType* PpcrCfg;
    uint8 GpioNum;
    uint8 PpcrNum;
} Port_ConfigType;

#ifdef __cplusplus
}
#endif
#endif

