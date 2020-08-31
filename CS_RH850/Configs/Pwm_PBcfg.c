/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Pwm_PBcfg.c For Renesas RH850 D1M1 Pwm
Author: Steven
******************************************************************************/
#include "Pwm_PBcfg.h"

/* CLKJIT:80MHz  */
static const Pwm_ClkCfgType PwmClkCfg[] = 
{
    /* PwmBRSmHw     Channel    BRSm*/
    { PWBA0_BRSm(0),    0,      0x0010},  /* PWMCLK0 = PCLK / ( 2 * 16 ) = 2.5MHz , (PCLK = 80MHz) */
};

static const Pwm_ChCfgType PwmChCfg[] = 
{
    /*   PwmHw   CH   CSDR     CRDR    Ctl   IdleSta */
    { PWGAn(22), 22,  0x00FF,  0x0FFF, 0x00,  0 }, /* 610Hz=2.5MHz /4096, PWMCLK0 */
};

static const Pwm_ConfigType PwmConfig = 
{
    PwmClkCfg,
    sizeof(PwmClkCfg)/sizeof(PwmClkCfg[0]),
    PwmChCfg,
    sizeof(PwmChCfg)/sizeof(PwmChCfg[0]),
};

const Pwm_ConfigType* const PwmCfgPtr = &PwmConfig;



