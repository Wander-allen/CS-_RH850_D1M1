/******************************************************************************
Copyright (C) 2019 Steven, mculib.net All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : CanOut_Tx.c  CanOut数据解析处理函数
Author: Wander
******************************************************************************/
#include "Std_Types.h"
#include "ComIf.h"
#include "JLRX_IPC.h"
#include "CanIn.h"
//#include "CanOut_Tx.h"

/******************************************************************************
函数名称: void CanOut_TxFrame45D(const uint8* Data)
函数说明: 
最后修改: Wander
******************************************************************************/
void CanOut_Tx45D(uint8* Data)
{
    /* 导航信息显示使能状态 */
    ComIf_SetData(Data, JLRX_IPC.NaviSt, BYTE0, BITS_B01);
    
    /* 蓝牙电话显示使能状态 */
    ComIf_SetData(Data, JLRX_IPC.BlePhoneSw, BYTE0, BITS_B23);
    
    /* 主动安全显示使能状态 */
    ComIf_SetData(Data, JLRX_IPC.ADAS_EnableSwSts, BYTE0, BITS_B45);
    
    /* 主题设置状态 */
    ComIf_SetData(Data, JLRX_IPC.ThemeSet, BYTE0, BITS_B67);
    
    /* 手动亮度调节状态 */
    ComIf_SetData(Data, JLRX_IPC.BacklightVal, BYTE1, BITS_B05);
    
    /* 自动亮度使能状态 */
    ComIf_SetData(Data, JLRX_IPC.BacklightMode, BYTE1, BITS_B67);
    
    /* 高度调节状态 */
    ComIf_SetData(Data, JLRX_IPC.HeightSet, BYTE2, BITS_B05);
    
    /* 测试代码 */
    uint8 Value = CanIn_GetFrameData(CANIN_RXPDU_123, BYTE7, BITS_B07);
    ComIf_SetData(Data, Value, BYTE2, BITS_B07);
}
