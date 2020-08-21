/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Std_Types.h
Author: Steven
******************************************************************************/
#ifndef STD_TYPES_H
#define STD_TYPES_H

#include "Compiler.h"

typedef unsigned char   boolean;
typedef unsigned char   uint8;
typedef unsigned char   uint08;
typedef unsigned short  uint16;
typedef unsigned long   uint32;
typedef signed char     sint8;
typedef signed char     sint08;
typedef signed short    sint16;
typedef signed long     sint32;
typedef unsigned char   uint8_least;
typedef unsigned char   uint08_least;
typedef unsigned short  uint16_least;
typedef unsigned long   uint32_least;
typedef signed char     sint08_least;
typedef signed char     sint8_least;
typedef signed short    sint16_least;
typedef signed long     sint32_least;
typedef float           float32;
typedef double          float64;

#define STD_OK          (0x00U)
#define STD_NOT_OK      (0x01U)
#define STD_PENDING     (0x02U)
#define STD_BUSY        (0x02U)
typedef uint8 Std_ReturnType;

#define STD_FALSE       (0x00U)
#define STD_TRUE        (0x01U)
#define STD_LOW         (0x00U)
#define STD_HIGH        (0x01U)
#define STD_IDLE        (0x00U)
#define STD_ACTIVE      (0x01U)
#define STD_OFF         (0x00U)
#define STD_ON          (0x01U)
#define STD_CLOSED      (0x00U)
#define STD_OPENED      (0x01U)
#define STD_IN          (0x00U)
#define STD_OUT         (0x01U)
typedef uint8 Std_StatusType;

typedef struct
{
    uint16 VendorID;
    uint16 ModuleID;
    uint8 MajorVer;
    uint8 MinorVer;
    uint8 PatchVer;
} Std_VersionType;

#endif

