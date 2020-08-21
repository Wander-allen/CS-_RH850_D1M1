/******************************************************************************
Copyright (C) 2019 Steven, mculib.net All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : CanOut_Server.c  CanOut外发处理
Author: Wander
******************************************************************************/
#include <string.h>
#include "Std_Types.h"
#include "CanOut_Define.h"
#include "CanOut_Types.h"
#include "CanOut_Tx.h"
#include "CanOut.h"
#include "CanIf.h"
#include "CanOut_Server.h"

typedef struct
{
    uint16 Cycle;
    uint16 Event;
    uint16 EventCnt;
    uint8 Data[8];
    boolean Enable;
}CanOut_Type;

static const CanOut_InfoType CanOut_InfoDefault[CANOUT_TXPDU_NUNMBER] = {CANOUT_INFO_DEFAULT};
static CanOut_Type CanOut_Data[CANOUT_TXPDU_NUNMBER];

/******************************************************************************
函数名称: void CanOut_ServerInit(void)
函数说明: 
最后修改: Wander
******************************************************************************/
void CanOut_ServerInit(void)
{
    uint8 i;
    
    for (i = 0; i < CANOUT_TXPDU_NUNMBER; i++)
    {
        CanOut_Data[i].Cycle = CanOut_InfoDefault[i].Cycle;
        CanOut_Data[i].Event = 0;
        CanOut_Data[i].EventCnt = 0;
        CanOut_Data[i].Enable = TRUE;
        (void) memset (CanOut_Data[i].Data, 0x00, 8);
    }
}

/******************************************************************************
函数名称: void CanOut_GetServerDataBuff(CanOut_PduID PduId, uint8 *data)
函数说明: 
最后修改: Wander
******************************************************************************/
void CanOut_GetServerDataBuff(CanOut_PduID PduId, uint8 *data)
{
    if (PduId < CANOUT_TXPDU_NUNMBER)
    {
        (void)memcpy(data, CanOut_Data[PduId].Data, 8);
    }
}

/******************************************************************************
函数名称: void CanOut_UpdateServerDataBuff(CanOut_PduID PduId, uint8 *data)
函数说明: 
最后修改: Wander
******************************************************************************/
void CanOut_UpdateServerDataBuff(CanOut_PduID PduId, uint8 *data)
{
    if (PduId < CANOUT_TXPDU_NUNMBER)
    {
        (void)memcpy(CanOut_Data[PduId].Data, data, 8);
    }
}

/******************************************************************************
函数名称: void CanOut_Enable(void)
函数说明: 使能周期发送
最后修改: Wander
******************************************************************************/
void CanOut_Enable(CanOut_PduID PduId, boolean Status)
{    
    if (PduId < CANOUT_TXPDU_NUNMBER)
    {
        if (Status != CanOut_Data[PduId].Enable)
        {
            CanOut_Data[PduId].Enable =  Status;
            CanOut_Data[PduId].Cycle = CanOut_InfoDefault[PduId].Cycle;
        }
    }
}

/******************************************************************************
函数名称: void CanOut_Active(CanOut_PduID PduId)
函数说明: 使能事件发送
最后修改: Wander
******************************************************************************/
void CanOut_Active(CanOut_PduID PduId)
{
    if (PduId < CANOUT_TXPDU_NUNMBER)
    {
        CanOut_Data[PduId].Event = CanOut_InfoDefault[PduId].Event;
        CanOut_Data[PduId].EventCnt = CanOut_InfoDefault[PduId].EventCnt;
        CanOut_Data[PduId].Enable = TRUE;
    }
}

/******************************************************************************
函数名称: void CanOut_Disable(CanOut_PduID PduId)
函数说明: 禁止使能事件发送
最后修改: Wander
******************************************************************************/
void CanOut_Disable(CanOut_PduID PduId)
{
    if (PduId < CANOUT_TXPDU_NUNMBER)
    {
        CanOut_Data[PduId].Enable = FALSE;
    }
}

/******************************************************************************
函数名称: void CanOut_DisableAll(void)
函数说明: 禁止使能所有帧发送
最后修改: Wander
******************************************************************************/
void CanOut_DisableAll(void)
{
    uint8 i;
    
    for (i = 0; i < CANOUT_TXPDU_NUNMBER; i++)
    {
        CanOut_Data[i].Enable = FALSE;
    }
}

/******************************************************************************
函数名称: void CanOut_Init(void)
函数说明: 外发服务主函数
最后修改: Wander
******************************************************************************/
void CanOut_ServerFunction(void)
{
    uint8 i;
    
    for (i = 0; i < CANOUT_TXPDU_NUNMBER; i++)
    {
        if (CanOut_Data[i].Enable == TRUE)
        {
            /* 事件型发送 */
            if (CanOut_Data[i].EventCnt > 0)
            {
                if (CanOut_Data[i].Event > 0)
                {
                    /* 事件型发送，立即发送一帧 */
                    if (CanOut_Data[i].Event == CanOut_InfoDefault[i].Event)
                    {
                        CanIf_Transmit(i, CanOut_Data[i].Data, 8);
                        CanOut_Data[i].EventCnt--;
                    }
                    
                    CanOut_Data[i].Event--;
                    continue;
                }
                else
                {
                    CanOut_Data[i].Event = CanOut_InfoDefault[i].Event;
                    continue;
                }
            }
            
            /* 周期型发送 */
            if (CanOut_Data[i].Cycle > 1) 
            {
                if (CanOut_Data[i].Cycle == CanOut_InfoDefault[i].Cycle)
                {
                    CanIf_Transmit(i, CanOut_Data[i].Data, 8);
                }
                CanOut_Data[i].Cycle--;
            }
            else
            {
                CanOut_Data[i].Cycle = CanOut_InfoDefault[i].Cycle;
            }
            
        }
        
    }
    
}
