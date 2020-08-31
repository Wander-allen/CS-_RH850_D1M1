/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Adc_PBcfg.c ADC driver For Nxp S32K14x
Author: Steven
******************************************************************************/
#include "Adc_PBcfg.h"

static Adc_ChCfgType AdcChCfg[] = 
{
    {0, 4},/* Virtual Channel:0, physical channel: ADCE0I4 */
};

static const Adc_GroupCfgType AdcGroupCfg[] = 
{
    {
        1,              /* Scan Group  */
        0x00000000,     /* Start Virtual Channel 0 */
        0x00000000,     /* End Virtual Channel 0*/
        0x00000010,     /* Bit[0]=0 -> SGx_TRG trigger is disabled
                           Bits[3,2]=0 -> Channel repeat times is one
                           Bit[4]=1 -> INT_SGx is output when the scan for SGx ends
                           Bit[5]=0 -> Multicycle scan mode */
        NULL            /* None*/
    },
};

static const Adc_ModuleCfgType AdcModuleCfg = 
{
    0x00000002,     /*  Bits[1,0]=10b -> Asynchronous suspend
                        Bit[4]=0 -> CRAC: 12-bit mode
                        Bit[5]=0 -> CTYP: PWDDR and ADCAnDRj are set to right align
                        Bit[7]=0 -> The self-diagnostic voltage circuit is turned off */
    0x00000018,     /*  Bits[7..0]=00010010b   Set sampling time to 24cycles/40MHz */
};

static const Adc_ConfigType AdcConfig = 
{
    AdcChCfg,       /* ChCfg */
    sizeof(AdcConfig) / sizeof(Adc_ConfigType),    /* ChNum */
    AdcGroupCfg,    /* GroupCfg */
    sizeof(AdcGroupCfg) / sizeof(Adc_GroupCfgType),/* GroupNum */
    &AdcModuleCfg,
};

const Adc_ConfigType* const AdcCfgPtr = &AdcConfig;


