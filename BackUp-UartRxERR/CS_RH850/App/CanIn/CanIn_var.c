/******************************************************************************
Copyright (C) 2019 Steven, mculib.net All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : CanIn_Var.c  CanIn数据
Author: Wander
******************************************************************************/
#include "CanIn.h"
#include "Std_Types.h"

typedef struct 
{
    uint16 VehicleSpeed;
    
}CanIn_VarTypes;

CanIn_VarTypes CanIn_Var;

/******************************************************************************
函数名称: void CanIn_Init(void)
函数说明: 
最后修改: Wander
******************************************************************************/
void CanIn_VarInit(void)
{
    uint8 i, j;
    
        /* 初始化 */
    (void) memset (&CanIn_Var, 0x00, sizeof(CanIn_VarTypes));
    
    for (i = 0; i < CANIN_RXPDU_NUMBER; i++)
    {
        CanIn_ClrFrameAllData((CanIn_ID) i);
        CanIn_ClrCanFrameRxCnt((CanIn_ID) i);
        CanIn_ClrCanFrameRxTimer((CanIn_ID) i);
    }
}

/******************************************************************************
函数名称: void CanIn_VarPowerONInit(void)
函数说明: 
最后修改: Wander
******************************************************************************/
void CanIn_VarPowerONInit(void)
{
    uint8 i；
    
    /* 数据清零 */
    CanIn_Var.VehicleSpeed  = 0;
    
    for (i = 0; i < CANIN_RXPDU_NUMBER; i++)
    {
        /* 上电无需清零操作，暂时无，后续可添加 */
        if (i == CANIN_RXPDU_NUMBER)
        {
            continue;
        }
        
        CanIn_ClrFrameAllData((CanIn_ID) i);
        CanIn_ClrCanFrameRxCnt((CanIn_ID) i);
        CanIn_ClrCanFrameRxTimer((CanIn_ID) i);
        
    }
}