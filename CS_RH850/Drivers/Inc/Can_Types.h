/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Can_Types.h  Nxp S32K14x FlexCAN Driver(Rx FIFO mode)
Author: Steven
******************************************************************************/
#ifndef CAN_TYPES_H
#define CAN_TYPES_H

#include "Std_Types.h"

/* Can procotol data unit type */
typedef struct 
{
    uint8* Data;
    uint32 Id;
    uint16 TxPduId;
    uint8 Length;
} Can_PduType;

/* Can Change State type */
typedef enum
{
    CAN_CS_STOP,
    CAN_CS_START,
    CAN_CS_SLEEP,
} Can_CsModeType;

#endif

