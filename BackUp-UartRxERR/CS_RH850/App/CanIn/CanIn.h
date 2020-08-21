/******************************************************************************
Copyright (C) 2019 Steven, mculib.net All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : CanIn.h  CAN报文输入处理
Author: Steven
******************************************************************************/
#ifndef CANIN_H
#define CANIN_H

#include "Std_Types.h"
#include "CanIn_Define.h"
#include "ComIf.h"


extern void CanIn_Init(void);
extern void CanIn_PollFunction(void);

/* CanIn 数据接口 */
extern void CanIn_ClrFrameData(CanIn_ID RxPduId, Byte_t Byte, Bits_t Bit);
extern void CanIn_ClrFrameAllData(CanIn_ID RxPduId);
extern void CanIn_SetFrameData(CanIn_ID RxPduId, uint8 Value, Byte_t Byte, Bits_t Bit);
extern uint8 CanIn_GetFrameData(CanIn_ID RxPduId, Byte_t Byte, Bits_t Bit);

/* CanIn MotorolaLsb 格式数据接口 */
extern void CanIn_ClrFrameDataMotorolaLsb(CanIn_ID RxPduId, uint8 Start, uint8  Len);
extern void CanIn_SetFrameDataMotorolaLsb(CanIn_ID RxPduId, uint32 value, uint8 Start, uint8  Len);
extern uint32 CanIn_GetFrameDataMotorolaLsb(CanIn_ID RxPduId, uint8 Start, uint8  Len);


/* CanIn 通讯计时接口 */
extern void CanIn_ClrCanFrameRxCnt(CanIn_ID RxPduId);
extern uint8 CanIn_GetCanFrameRxCnt(CanIn_ID RxPduId);
extern void CanIn_ClrCanFrameRxTimer(CanIn_ID RxPduId);
extern uint16 CanIn_GetCanFrameRxTimer(CanIn_ID RxPduId);
extern void CanIn_ClrCanBusRxTimer(void);
extern uint16 CanIn_GetCanBusRxTimer(void);




#endif

