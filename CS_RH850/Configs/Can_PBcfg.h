/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Can_PBcfg.hNxp S32K14x FlexCAN Driver(Rx FIFO mode)
Author: Steven
******************************************************************************/
#ifndef CAN_PBCFG_H
#define CAN_PBCFG_H

#include "Std_Types.h"
#include "Can_Define.h"
#include "Can_Types.h"

typedef enum
{
    CAN0,
    CAN1,
    CAN2,
    CAN_MAX
}Can_ChannelType;

/* Receive rule setting */
typedef struct 
{
    uint32 Id;
    uint32 PTR;
    uint32 DF0;
    uint32 DF1;
}Can_RuleCfgType;

/* Can Channel Configure */
typedef struct 
{
    Can_ChannelType CanCh;
    uint32 CmCFG;
    uint8 RNCSm;        /* Rule Array Start */
    uint8 RNCEm;        /* Rule Array End */
}Can_ChCfgType;

typedef struct 
{
    void(*RxCallback)(uint8 Hrh, uint32 Id, uint8 Dlc, const uint8* Data);
    void(*TxCallback)(uint16 TxPduId);
    void(*ModeCsCbk)(uint8 CanCh, Can_CsModeType Mode);
    void(*BusoffCbk)(uint8 Ch);
    const Can_RuleCfgType* Rule_Cfg;
    uint8 RuleNum;
    const Can_ChCfgType* ChCfg;
    uint8 ChNum;
} Can_ConfigType;

#endif
  
