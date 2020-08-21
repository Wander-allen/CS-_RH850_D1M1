/******************************************************************************
Copyright (C) 2019 Steven, mculib.net All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : ComIf.h  CAN报文输入处理
Author: 
******************************************************************************/
#ifndef COMIF_TYPES_H
#define COMIF_TYPES_H

typedef enum
{
    BYTE0 = 0,
    BYTE1,
    BYTE2,
    BYTE3,
    BYTE4,
    BYTE5,
    BYTE6,
    BYTE7,
    
}Byte_t;

typedef enum
{
    BITS_B0 = 0x00,
    BITS_B1 = 0x11,
    BITS_B2 = 0x22,
    BITS_B3 = 0x33,
    BITS_B4 = 0x44,
    BITS_B5 = 0x55,
    BITS_B6 = 0x66,
    BITS_B7 = 0x77,
    
    BITS_B01 = 0x01,
    BITS_B02 = 0x02,
    BITS_B03 = 0x03,
    BITS_B04 = 0x04,
    BITS_B05 = 0x05,
    BITS_B06 = 0x06,
    BITS_B07 = 0x07,
    
    BITS_B12 = 0x12,
    BITS_B13 = 0x13,
    BITS_B14 = 0x14,
    BITS_B15 = 0x15,
    BITS_B16 = 0x16,
    BITS_B17 = 0x17,
    
    BITS_B23 = 0x23,
    BITS_B24 = 0x24,
    BITS_B25 = 0x25,
    BITS_B26 = 0x26,
    BITS_B27 = 0x27,
    
    BITS_B34 = 0x34,
    BITS_B35 = 0x35,
    BITS_B36 = 0x36,
    BITS_B37 = 0x37,
    
    BITS_B45 = 0x45,
    BITS_B46 = 0x46,
    BITS_B47 = 0x47,
    
    BITS_B56 = 0x56,
    BITS_B57 = 0x57,
    
    BITS_B67 = 0x67,

}Bits_t;

#endif
