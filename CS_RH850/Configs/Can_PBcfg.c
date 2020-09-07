/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Can_PBcfg.cNxp S32K14x FlexCAN Driver(Rx FIFO mode)
Author: Steven
******************************************************************************/
#include "Can_PBcfg.h"


static const Can_RuleCfgType CanRuleCfg[] =
{
    /* CAN 1 reception rules */
    {0x00000010UL, 0xDFFFF000UL, 0x00000000UL, 0x00000001UL}, /* Receive FIFO Buffer 接收所有帧 0x000 - 0xFFF*/
};

//SJW =3TQ, TSEG1=11TQ, TSEG2=4TQ, BRP=0
static const Can_ChCfgType CanChCfg[] = 
{
    /* Ch, CmCFG        RNCSm RNCEm*/
    {CAN1, 0x023a0000,  0,    0} /* 500kbps SamplePoint:75% Rule Array: CanIfCfg[0] */
};

static const Can_ConfigType CanConfig = 
{
    NULL, /* RxCallback */
    NULL, /* TxCallback */
    NULL, /* ModeCsCbk */
    NULL, /* BusoffCbk */
    CanRuleCfg,  /* IfCfg */
    sizeof(CanRuleCfg)/sizeof(CanRuleCfg[0]),  /* RuleNum */
    CanChCfg,  /* ChCfg */
    sizeof(CanChCfg)/sizeof(CanChCfg[0]),  /* ChNum */
};

const Can_ConfigType* const CanCfgPtr = &CanConfig;


