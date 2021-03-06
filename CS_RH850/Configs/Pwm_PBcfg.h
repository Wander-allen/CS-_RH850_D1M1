/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Pwm_PBcfg.h For Renesas RH850 D1M1 Pwm
Author: Steven
******************************************************************************/
#ifndef PWM_PBCFG_H
#define PWM_PBCFG_H

#include "Std_Types.h"

typedef struct 
{
    uint8   Channel;    /* PWGAn (ValidValue:0-23)       */
    uint16  CSDR;       /* PWGAnCSDR                    */
    uint16  CRDR;       /* PWGAnCRDR                    */
    uint8   CTL;        /* PWGAnCTL                     */
    uint8   IdleSta;    /* Idle level state             */
}Pwm_ChCfgType;

typedef struct
{
    uint8   Channel;    /* Clk (ValidValue:0-7)         */
    uint16  BRSm;       /* (ValidBits:0x7FF CLKS&BRSm)  */
}Pwm_ClkCfgType;

typedef struct
{
    const Pwm_ClkCfgType* ClkCfg;
    uint8 ClkNum;
    const Pwm_ChCfgType* ChCfg;
    uint8 ChNum;
} Pwm_ConfigType;

#endif

