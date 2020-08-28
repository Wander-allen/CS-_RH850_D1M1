/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Pwm_PBcfg.c For Renesas RH850 D1M1 Pwm
Author: Steven
******************************************************************************/
#include "Pwm_PBcfg.h"

/* CLKJIT:80MHz  */
static const Pwm_ChCfgType PwmChCfg[] = 
{
    /*   PwmHw   CH   BRS0     CSDR     CRDR    IdleSta*/
    { PWGAn(22), 22,  0x0010,  0x00FF,  0x0FFF, 0}, /* 610Hz=80MHz/2 * 16 * 4096 */
};

static const Pwm_ConfigType PwmConfig = 
{
    PwmChCfg,
    sizeof(PwmChCfg)/sizeof(PwmChCfg[0]),
};

const Pwm_ConfigType* const PwmCfgPtr = &PwmConfig;



