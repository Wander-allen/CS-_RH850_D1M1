/******************************************************************************
Copyright (C) 2019 Steven, mculib.net All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : ComIf.h  字节位处�?
Author: 
******************************************************************************/
#ifndef COMIF_H
#define COMIF_H

#include "stdint.h"
#include "ComIf_Types.h"

extern void ComIf_ClrData(uint8_t *Data, Byte_t Byte, Bits_t Bit);
extern void ComIf_SetData(uint8_t *Data, uint8_t Value, Byte_t Byte, Bits_t Bit);
extern uint8_t  ComIf_GetData(uint8_t *Data, Byte_t Byte, Bits_t Bit);
extern void  ComIf_ClrDataMotorolaLsb(uint8_t *Data, uint8_t Start, uint8_t  Len);
extern void  ComIf_SetDataMotorolaLsb(uint8_t *Data, uint32_t Value, uint8_t Start, uint8_t  Len);
extern uint32_t  ComIf_GetDataMotorolaLsb(uint8_t *Data, uint8_t Start, uint8_t Len);

#endif
