/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : CanIf_PBcfg.c  CAN Interface Service
Author: Steven
******************************************************************************/
#include "CanIf_PBcfg.h"
#include "CanTp_Cbk.h"
// #include "CanIn_Cbk.h"
#include "CanSM_Cbk.h"

#if 0
static const CanIf_RxPduCfgType CanIfRxPduCfg[] = 
{
    /* Cbk             CanId       Dlc UPduId */
	{CanIn_RxCallback, 0x00000123, 8,  0},  /* RxPdu00:ECU */
	{CanIn_RxCallback, 0x00000245, 8,  1},
    {CanIn_RxCallback, 0x0000024A, 8,  2},
    {CanIn_RxCallback, 0x0000024C, 8,  3},
    {CanIn_RxCallback, 0x00000271, 8,  4},
	{CanIn_RxCallback, 0x0000028A, 8,  5},
    {CanIn_RxCallback, 0x000002E5, 8,  6},
	{CanIn_RxCallback, 0x00000314, 8,  7},
    {CanIn_RxCallback, 0x00000331, 8,  8},
	{CanIn_RxCallback, 0x0000034B, 8,  9},
	{CanIn_RxCallback, 0x000003B1, 8,  10},
	{CanIn_RxCallback, 0x000003BA, 8,  11},
    {CanIn_RxCallback, 0x000003BB, 8,  12},
    {CanIn_RxCallback, 0x0000042D, 8,  13},
	{CanIn_RxCallback, 0x0000045D, 8,  14},	
	{CanIn_RxCallback, 0x0000047D, 8,  15},
	
	{CanTp_RxCallback, 0x00000782, 8,  0},
	{CanTp_RxCallback, 0x000007DF, 8,  1},
};

static const CanIf_TxPduCfgType CanIfTxPduCfg[] = 
{
    /* Cbk             CanId       Dlc UId Hth Dynamic */
    {CanTp_TxCallback, 0x00000792, 8,  0,  0,  FALSE},  /* 01:UDS PhyAddressing */
    {CanTp_TxCallback, 0x00000792, 8,  1,  0,  FALSE},  /* 02:UDS FunAddressing */
	{Tx45D_TxCallback, 0x0000045D, 8,  2,  1,  FALSE},  /* 外发CAN报文 */
    {CanTp_TxCallback, 0x000002E6, 8,  3,  0,  FALSE},  /* 与多媒体交互报文*/
};

static const uint16 CanIfHrhTbl0[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,};
static const CanIf_RxHrhCfgType CanIfRxHrhCfg[] = 
{
    /* RxPduTbl      RxPduNum */
    {CanIfHrhTbl0, sizeof(CanIfHrhTbl0)/2},
};

static CanIf_CanTxPduType CanIfTxBuf0[8];
static CanIf_CanTxPduType CanIfTxBuf1[4];
static CanIf_CanTxPduType CanIfTxBuf2[4];
static const CanIf_TxHthCfgType CanIfTxHthCfg[] = 
{
    /* TxBuffer        Size  Hth */
    {CanIfTxBuf0, sizeof(CanIfTxBuf0)/sizeof(CanIf_CanTxPduType), 0},
    {CanIfTxBuf1, sizeof(CanIfTxBuf1)/sizeof(CanIf_CanTxPduType), 1},
    {CanIfTxBuf2, sizeof(CanIfTxBuf2)/sizeof(CanIf_CanTxPduType), 2},
};

static const CanIf_ConfigType CanIfConfig = 
{
    CanIfRxPduCfg,  /* RxPduCfg */
    CanIfTxPduCfg,  /* TxPduCfg */
    CanIfRxHrhCfg,  /* RxHrhCfg */
    CanIfTxHthCfg,  /* TxHthCfg */
    sizeof(CanIfRxPduCfg)/sizeof(CanIf_RxPduCfgType),  /* RxPduNum */
    sizeof(CanIfTxPduCfg)/sizeof(CanIf_TxPduCfgType),  /* TxPduNum */
    sizeof(CanIfRxHrhCfg)/sizeof(CanIf_RxHrhCfgType),  /* RxHrhNum */
    sizeof(CanIfTxHthCfg)/sizeof(CanIf_TxHthCfgType),  /* TxHthNum */
    CanSm_BusoffCallback,  /* BusoffCallback */
    CanSm_ModeCsCallback,  /* ModeCsCallback */
};

const CanIf_ConfigType* const CanIfCfgPtr = &CanIfConfig;

#endif