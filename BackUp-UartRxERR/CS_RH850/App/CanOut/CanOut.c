/******************************************************************************
Copyright (C) 2019 Steven, mculib.net All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : CanOut.c  CAN报文外发处理
Author: Wander
******************************************************************************/
#include <string.h>
#include "Std_Types.h"
#include "CanOut_Define.h"
#include "CanOut_Server.h"
#include "CanOut_Tx.h"
#include "CanOut.h"

/******************************************************************************
函数名称: void CanOut_Init(void)
函数说明: 
最后修改: Wander
******************************************************************************/
void CanOut_Init(void)
{
    uint8 i;
    
    /* 使能所有帧发送 */
    for (i = 0; i < CANOUT_TXPDU_NUNMBER; i++)
    {
       CanOut_Enable((CanOut_PduID)i, TRUE);
    }
}

/******************************************************************************
函数名称: void CanOut_Init(void)
函数说明: 
最后修改: Wander
******************************************************************************/
void CanOut_TXPDU_45D(void)
{
     uint8 TxTmp[8] = {0};
     uint8 BuffTmp[8] = {0};
     
     CanOut_Tx45D(TxTmp);
     
     CanOut_GetServerDataBuff(CANOUT_TXPDU_45D, BuffTmp);
#if 1
     /* 周期发送处理 */
     if (memcmp(TxTmp, BuffTmp, 8))
     {
         CanOut_UpdateServerDataBuff(CANOUT_TXPDU_45D, TxTmp);
     }
     
     CanOut_Enable(CANOUT_TXPDU_45D, TRUE);
#else
     /* 周期事件发送处理 */
     if (memcmp(TxTmp, BuffTmp, 8))
     {
         CanOut_Active(CANOUT_TXPDU_45D);
         CanOut_UpdateServerDataBuff(CANOUT_TXPDU_45D, TxTmp);
         return;
     }
     
     CanOut_Enable(CANOUT_TXPDU_45D, TRUE);
#endif
}


/******************************************************************************
函数名称: void CanOut_Init(void)
函数说明: 
最后修改: Wander
******************************************************************************/
void CanOut_PollFunction(void)
{
    uint8 i;
    
    CanOut_TXPDU_45D();
    
    CanOut_ServerFunction();
    
}







