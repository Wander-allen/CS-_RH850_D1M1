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


#define PWGAn_BASE              ((uint32)0xFFE45800)
#define PWGAn(n)                (PWGAn_BASE + (0x100 * (n)))

typedef struct 
{
    uint32  PwmHw;      /* Pwm hardware address*/
    uint8   Channel;    /* PWGAn (n = 0 to 23)  */
    uint16  BRS0;       /* PWBAnBRSm = n        */
    uint16  CSDR;       /* PWGAnCSDR            */
    uint16  CRDR;       /* PWGAnCRDR            */
    uint8   IdleSta;    /* Idle level state     */

}Pwm_ChCfgType;

typedef struct
{
    const Pwm_ChCfgType* ChCfg;
    uint8 ChNum;
} Pwm_ConfigType;

#endif

