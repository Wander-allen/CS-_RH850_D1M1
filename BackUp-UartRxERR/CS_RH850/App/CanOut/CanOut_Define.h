/******************************************************************************
Copyright (C) 2019 Steven, mculib.net All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : CanIn_Define.h  CAN报文输入处理
Author: 
******************************************************************************/
#ifndef CANOUT_DEFINE_H
#define CANOUT_DEFINE_H

#define TISK(x)  (x * 10) /* 10ms单位 */

#define CANOUT_INFO_DEFAULT\
/*   ID     Cycle     Event     Cnt CallBackFun */\
    {0x782, TISK(0),  TISK(0),  0,  NULL        },\
    {0x782, TISK(0),  TISK(0),  0,  NULL        },\
    {0x45D, TISK(50), TISK(0),  0,  CanOut_Tx45D} \
    //{0x45D, TISK(50), TISK(10), 3,  CanOut_Tx45D} \

typedef enum
{
    CANOUT_TXPDU_PHY = 0,
    CANOUT_TXPDU_FUN,
    
    CANOUT_TXPDU_45D,
    CANOUT_TXPDU_NUNMBER
}CanOut_PduID;

#endif
