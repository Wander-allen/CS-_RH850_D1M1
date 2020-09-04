/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Can.h 
Author: Wander 
******************************************************************************/
#ifndef CAN_H
#define CAN_H
#ifdef __cplusplus
extern "C" {
#endif

#include "Std_Types.h"

  typedef unsigned char U8;
  typedef signed char S8;
  typedef unsigned short U16;
  typedef signed short S16;
  typedef unsigned long U32;
  typedef signed long S32;
  typedef unsigned char BOOL;
  typedef volatile unsigned char VU8;
  typedef volatile unsigned short VU16;
  typedef volatile unsigned long VU32;

/* ---- CAN frame ----- */
typedef struct
{
    U32 ID :29;
    U32 THLEN :1;
    U32 RTR :1;
    U32 IDE :1;
    
    U32 TS :16;
    U32 LBL :12;
    U32 DLC :4;
    U8 DB[8];
} Can_FrameType;

typedef U8 Can_RtnType;

extern void Can_Init(void);
#if 0
    int RS_CAN_error(void);
#endif

Can_RtnType Can_ReadRxBuffer(Can_FrameType* pFrame);
Can_RtnType Can_C0TrmByTxBuf(U8 TxBufIdx, const Can_FrameType* pFrame);

static void Can_SetRxRule(void);


extern const Can_FrameType CANTraStandData;
extern Can_FrameType CANRecData;

#ifdef __cplusplus
}
#endif
#endif