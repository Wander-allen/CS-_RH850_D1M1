/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : CanTp_PBcfg.c Can Transport Layer Service
Author: Steven
******************************************************************************/
#include "CanTp_PBcfg.h"
#include "CanIf.h"
// #include "Dcm_Cbk.h"

#if 0
static const CanTp_ChCfgType CanTpChCfg[] = 
{
    /* CanTp Ch0: DCM Physical addressing */
    { 
        0,      /* RxBS */
        1,      /* RxSTmin ms */
        200,    /* NAr ms */
        700,    /* NBr ms */
        1000,   /* NCr ms */
        200,    /* NAs ms */
        1000,   /* NBs ms */
        700,    /* NCs ms */
        5,      /* WFTmax */
        0xAA,   /* Padding */
        DCM_CH_CANTP_PHY, /* TxUPduId */
        DCM_CH_CANTP_PHY, /* RxUPduId */
        CANIF_TXPDU_UDS0, /* TxLPduId */
        Dcm_TpRxCallback, /* TpRxCallback */
        Dcm_TpRxStartCbk, /* TpRxStartCbk */
        Dcm_TpCopyRxData, /* TpCopyRxData */
        Dcm_TpTxCallback, /* TpTxCallback */
        Dcm_TpCopyTxData, /* TpCopyTxData */
        CanIf_Transmit,   /* LPduTransmit */
    },

    /* CanTp Ch1: DCM Function addressing */
    { 
        0,      /* RxBS */
        1,      /* RxSTmin ms */
        200,    /* NAr ms */
        700,    /* NBr ms */
        1000,   /* NCr ms */
        200,    /* NAs ms */
        1000,   /* NBs ms */
        700,    /* NCs ms */
        5,      /* WFTmax */
        0xAA,   /* Padding */
        DCM_CH_CANTP_FUN, /* TxUPduId */
        DCM_CH_CANTP_FUN, /* RxUPduId */
        CANIF_TXPDU_UDS1, /* TxLPduId */
        Dcm_TpRxCallback, /* TpRxCallback */
        Dcm_TpRxStartCbk, /* TpRxStartCbk */
        Dcm_TpCopyRxData, /* TpCopyRxData */
        Dcm_TpTxCallback, /* TpTxCallback */
        Dcm_TpCopyTxData, /* TpCopyTxData */
        CanIf_Transmit,   /* LPduTransmit */
    },
};

static const uint8 CanTpNRxPduChMap[] = {0,1};
static const uint8 CanTpNTxPduChMap[] = {0,1};

static const CanTp_ConfigType CanTpConfig = 
{
    CanTpChCfg,  /* ChCfg */
    CanTpNRxPduChMap,  /* NRxPduChMap */
    CanTpNTxPduChMap,  /* NTxPduChMap */
    sizeof(CanTpChCfg)/sizeof(CanTp_ChCfgType),  /* ChNum */
    sizeof(CanTpNRxPduChMap),  /* NRxPduNum */
    sizeof(CanTpNTxPduChMap),  /* NTxPduNum */
};

const CanTp_ConfigType* const CanTpCfgPtr = &CanTpConfig;

#endif