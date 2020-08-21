/******************************************************************************
Copyright (C) 2019 Steven, mculib.net All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : ComIf.c  common interface 通用接口-字节位处理
Author: Wander
******************************************************************************/
#include "ComIf.h"
#include "Std_Types.h"

/******************************************************************************
函数名称: void ComIf_init(void)
函数说明: 
最后修改: Wander
******************************************************************************/
static void ComIf_init(void)
{
    ;
}

/******************************************************************************
函数名称: void ComIf_SetData(uint8_t *Data, uint8_t Value, Byte_t Byte, Bits_t Bit)
函数说明: 
最后修改: Wander
******************************************************************************/
void ComIf_ClrData(uint8_t *Data, Byte_t Byte, Bits_t Bit)
{
    uint8_t LeftOffset = (((uint8_t)Bit & 0xF0) >> 4);
    uint8_t RightOffset = ((uint8_t)Bit & 0x0F);
    uint8_t tmp = 0xFF;
    
    if (Data != NULL)
    {
        tmp <<= (7 - RightOffset);
        tmp >>= (7 - RightOffset + LeftOffset);
        tmp <<= LeftOffset;
        Data[Byte] &= ~tmp;
    }
}

/******************************************************************************
函数名称: void ComIf_SetData(uint8_t *Data, uint8_t Value, Byte_t Byte, Bits_t Bit)
函数说明: 
最后修改: Wander
******************************************************************************/
void ComIf_SetData(uint8_t *Data, uint8_t Value, Byte_t Byte, Bits_t Bit)
{
    uint8_t LeftOffset = (((uint8_t)Bit & 0xF0) >> 4);
    uint8_t RightOffset = ((uint8_t)Bit & 0x0F);
    uint8_t tmp = 0xFF;
    
    if (Data != NULL)
    {
        tmp <<= (7 - RightOffset);
        tmp >>= (7 - RightOffset + LeftOffset);
        tmp <<= LeftOffset;
        Data[Byte] &= ~(tmp);
        Data[Byte] |= (((Value) << LeftOffset) & (tmp));
    }
}

/******************************************************************************
函数名称: uint8_t    ComIf_GetData(uint8_t *Data, Byte_t Byte, Bits_t Bit)
函数说明: 
最后修改: Wander
******************************************************************************/
uint8_t  ComIf_GetData(uint8_t *Data, Byte_t Byte, Bits_t Bit)
{
    uint8_t LeftOffset = (((uint8_t)Bit & 0xF0) >> 4);
    uint8_t RightOffset = ((uint8_t)Bit & 0x0F);
    uint8_t tmp = 0xFF;
    
    if (Data != NULL)
    {
        tmp = Data[Byte];
        tmp <<= (7 - RightOffset);
        tmp >>= (7 - RightOffset + LeftOffset);
    }
    
    return tmp;
}

/******************************************************************************
函数名称: void   ComIf_ClrDataMotorolaLsb(uint8_t *Data, uint8_t Start, uint8_t  Len)
函数说明: 
最后修改: Wander
******************************************************************************/
void  ComIf_ClrDataMotorolaLsb(uint8_t *Data, uint8_t Start, uint8_t  Len)
{
    uint8_t StartByte = Start / 8;                          /* 起始字节      */
    uint8_t StartBit = Start % 8;                           /* 起始字节位    */
    uint8_t Bytes = (Len - (7 - StartByte) + 7) / 8 ;       /* 总字节数      */
    uint8_t EndByte = StartByte - Bytes + 1;                /* 结束字节      */
    uint8_t EndBit = 7 - ((Len - (7 - StartBit + 1)) % 8);  /* 结束字节位    */
    
    /* 参数检查 */
    if (Start > 63 || Len > 63 || Len > Start)
    {
        return ;
    }

    /* 单字节处理 */
    if (StartByte == EndByte)
    {
        ComIf_ClrData(Data, (Byte_t) StartByte, (Bits_t)((EndBit) << 4 | StartByte));
        return ;
    }

    /* 多字节处理 */
    ComIf_ClrData(Data, (Byte_t) StartByte, (Bits_t)((StartBit) << 4 | 7));
    
    for (uint8_t i = StartByte - 1; i > EndByte; i--)
    {
        ComIf_ClrData(Data, (Byte_t) i, BITS_B07);
    }

    ComIf_ClrData(Data, (Byte_t) EndByte, (Bits_t) (EndBit));
    
    return ;
    
}

/******************************************************************************
函数名称: void  ComIf_SetDataMotorolaLsb(uint8_t *Data, uin8_t Value, uint8_t Start, uint8_t  Len)
函数说明: 
最后修改: Wander
******************************************************************************/
void  ComIf_SetDataMotorolaLsb(uint8_t *Data, uint32_t Value, uint8_t Start, uint8_t  Len)
{
    uint8_t StartByte = Start / 8;                          /* 起始字节      */
    uint8_t StartBit = Start % 8;                           /* 起始字节位    */
    uint8_t Bytes = (Len - (7 - StartByte) + 7) / 8 ;       /* 总字节数      */
    uint8_t EndByte = StartByte - Bytes + 1;                /* 结束字节      */
    uint8_t EndBit = 7 - ((Len - (7 - StartBit + 1)) % 8);  /* 结束字节位    */
    
    /* 参数检查 */
    if (Start > 63 || Len > 63 || Len > Start)
    {
        return ;
    }

    /* 单字节处理 */
    if (StartByte == EndByte)
    {
        ComIf_SetData(Data, (uint8_t)Value, (Byte_t) StartByte, (Bits_t)((EndBit) << 4 | StartByte));
        return ;
    }

    /* 多字节处理 */
    ComIf_SetData(Data, (uint8_t)Value, (Byte_t) StartByte,  (Bits_t)((StartBit) << 4 | 7));
    Value >>= 7 - StartBit + 1;
    
    for (uint8_t i = StartByte - 1; i > EndByte; i--)
    {
        ComIf_SetData(Data, (uint8_t)Value, (Byte_t) i, BITS_B07);
        Value >>= 8;
    }

    ComIf_SetData(Data, (uint8_t)Value, (Byte_t) EndByte, (Bits_t) (EndBit));
    
    return ;
    
}


/******************************************************************************
函数名称: uint32_t  ComIf_GetDataMotorolaLsb(uint8_t *Data, uint8_t Start, uint8_t  Len)
函数说明: 
最后修改: Wander
******************************************************************************/
uint32_t  ComIf_GetDataMotorolaLsb(uint8_t *Data, uint8_t Start, uint8_t  Len)
{
    uint8_t StartByte = Start / 8;                          /* 起始字节      */
    uint8_t StartBit = Start % 8;                           /* 起始字节位    */
    uint8_t Bytes = (Len - (7 - StartByte) + 7) / 8 ;       /* 总字节数      */
    uint8_t EndByte = StartByte - Bytes + 1;                /* 结束字节      */
    uint8_t EndBit = 7 - ((Len - (7 - StartBit + 1)) % 8);  /* 结束字节位    */
    
    uint32_t VReturn = 0;
    
    /* 参数检查 */
    if (Start > 63 || Len > 63 || Len > Start)
    {
        return VReturn;
    }

    /* 单字节处理 */
    if (StartByte == EndByte)
    {
        VReturn  = ComIf_GetData(Data, (Byte_t) StartByte, (Bits_t)((EndBit) << 4 | StartByte));
        return VReturn;
    }

    /* 多字节处理 */
    VReturn = ComIf_GetData(Data, (Byte_t) EndByte, (Bits_t) (EndBit));
    VReturn <<= EndBit + 1;

    for (uint8_t i = EndBit + 1; i < StartByte; i++)
    {
        VReturn |= ComIf_GetData(Data, (Byte_t) i, BITS_B07);
        VReturn <<= 8;
    }

    VReturn |= ComIf_GetData(Data, (Byte_t) StartByte, BITS_B07);
    VReturn >>= StartBit;
    
    return VReturn;
    
}


