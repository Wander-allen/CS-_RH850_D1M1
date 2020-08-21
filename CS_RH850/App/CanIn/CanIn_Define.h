/******************************************************************************
Copyright (C) 2019 Steven, mculib.net All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : CanIn_Define.h  CAN报文输入处理
Author: 
******************************************************************************/
#ifndef CANIN_DEFINE_H
#define CANIN_DEFINE_H

#define CNT1MS       (1)
#define CNT10MS      (10)
#define CNT100MS     (100)

#define DEFAULT_CANINRXFUN \
/*   CanId  UpdateTmr  CallBack       */\
    {0X123, CNT1MS,   CanIn_RxFrame123},\
    {0X245, CNT1MS,   CanIn_RxFrame245},\
    {0X24A, CNT1MS,   CanIn_RxFrame24A},\
    {0X24C, CNT1MS,   CanIn_RxFrame24C},\
    {0X271, CNT1MS,   CanIn_RxFrame271},\
    {0X28A, CNT1MS,   CanIn_RxFrame28A},\
    {0X2E5, CNT1MS,   CanIn_RxFrame2E5},\
    {0X314, CNT1MS,   CanIn_RxFrame314},\
    {0X331, CNT1MS,   CanIn_RxFrame331},\
    {0X34B, CNT1MS,   CanIn_RxFrame34B},\
    {0X38F, CNT1MS,   CanIn_RxFrame38F},\
    {0X3B1, CNT1MS,   CanIn_RxFrame3B1},\
    {0X3BA, CNT1MS,   CanIn_RxFrame3BA},\
    {0X42D, CNT1MS,   CanIn_RxFrame42D},\
    {0X45D, CNT1MS,   CanIn_RxFrame45D},\
    {0X47D, CNT1MS,   CanIn_RxFrame47D}\

typedef enum
{
    CANIN_RXPDU_123 = 0,
    CANIN_RXPDU_245,
    CANIN_RXPDU_24A,
    CANIN_RXPDU_24C,
    CANIN_RXPDU_271,
    CANIN_RXPDU_28A,
    CANIN_RXPDU_2E5,
    CANIN_RXPDU_314,
    CANIN_RXPDU_331,
    CANIN_RXPDU_34B,
    CANIN_RXPDU_38F,
    CANIN_RXPDU_3B1,
    CANIN_RXPDU_3BA,
    CANIN_RXPDU_42D,
    CANIN_RXPDU_45D,
    CANIN_RXPDU_47D,
    CANIN_RXPDU_NUMBER
}CanIn_ID;


#endif


