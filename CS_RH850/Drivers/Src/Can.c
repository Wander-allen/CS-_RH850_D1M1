/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Can.c 
Author: Wander 
******************************************************************************/

/******************************************************************************
Pragma directive
******************************************************************************/

/******************************************************************************
Includes
******************************************************************************/
// #include "ioDefine.h"
#include "Std_Types.h"
#include "Can_PBcfg.h"
#include "Can.h"
#include "Det.h"
#include "Mcu.h"
#include <string.h>

/******************************************************************************
#Define
******************************************************************************/
#ifndef CAN_ENABLE
#define CAN_ENABLE                          1U
#endif
#ifndef CAN_DISABLE
#define CAN_DISABLE                         0U
#endif

#define CAN_PAGE_RX_RULE_IDX_MASK           0xfU
#define CAN_RX_RULE_PAGE_IDX_BIT_POS        4U
#define CAN_CHANNEL_MAX_BUFFER              0x0F
#define CAN_RX_FIFO_BUF_MAX                 0x08

/* ---- bit operations ---- */
#define GET_BIT(reg, pos)              (((reg) >> (pos)) & 1U)
#define SET_BIT(reg, pos)              ((reg) |= 1U << (pos))
#define CLR_BIT(reg, pos)              ((reg) &= ~(1UL << (pos)))

/* ---- bit value ---- */
#define CAN_SET                             1U
#define CAN_CLR                             0U

/* ---- CiTBCRj ---- */
#define CAN_TBTR_BIT_POS                    0U
#define CAN_TBAR_BIT_POS                    1U
#define CAN_TBOE_BIT_POS                    2U

/* ---- TX buffer, TX status flag ---- */
#define CAN_TBTST_NOT_TRANSMITTING          0U
#define CAN_TBTST_TRANSMITTING              1U

/* transmission command */
#define CAN_TBCR_TRM                        (CAN_ENABLE << CAN_TBTR_BIT_POS)

/******************************************************************************
#Structures
******************************************************************************/
/* ---- CAN frame ----- */
typedef struct
{
    uint32 ID :29;
    uint32 THLEN :1;
    uint32 RTR :1;
    uint32 IDE :1;
    
    uint32 TS :16;
    uint32 LBL :12;
    uint32 DLC :4;
    uint8  DB[8];
} Can_FrameType;

/******************************************************************************
#Define Register
******************************************************************************/
#define RSCAN0_BASE             ((uint32)0xFFD00000)

#define RSCAN0_GCFG             (*((volatile uint32 *)(RSCAN0_BASE + 0x0084)))
#define RSCAN0_GCTR             (*((volatile uint32 *)(RSCAN0_BASE + 0x0088)))
#define RSCAN0_GSTS             (*((volatile uint32 *)(RSCAN0_BASE + 0x008C)))

#define RSCAN0_CmCFG(m)         (*((volatile uint32 *)(RSCAN0_BASE + 0x0000 +(0x10 * m))))
#define RSCAN0_CmCTR(m)         (*((volatile uint32 *)(RSCAN0_BASE + 0x0004 +(0x10 * m))))
#define RSCAN0_CmSTS(m)         (*((volatile uint32 *)(RSCAN0_BASE + 0x0008 +(0x10 * m))))
#define RSCAN0CmERFL(m)         (*((volatile uint32 *)(RSCAN0_BASE + 0x000C +(0x10 * m))))

/* Receive Rule Register (j = 0 to 15) */
#define RSCAN0_GAFLECTR         (*((volatile uint32 *)(RSCAN0_BASE + 0x0098)))
#define RSCAN0_GAFLCFG0         (*((volatile uint32 *)(RSCAN0_BASE + 0x009C)))
#define RSCAN0_GAFLIDj(j)       (*((volatile uint32 *)(RSCAN0_BASE + 0x0500 +(0x10 * j))))

/* Receive Buffer Register (y = 0 to 1)(q = 0 to 47) */
#define RSCAN0_RMNB             (*((volatile uint32 *)(RSCAN0_BASE + 0x00A4)))
#define RSCAN0_RMNDy(y)         (*((volatile uint32 *)(RSCAN0_BASE + 0x00A8 +(0x04 * y))))
#define RSCAN0_RMIDq(q)         (*((volatile uint32 *)(RSCAN0_BASE + 0x0600 +(0x10 * q))))

/* Receive FIFO Buffer Register x (x = 0 to 7) */
#define RSCAN0_RFCCx(x)         (*((volatile uint32 *)(RSCAN0_BASE + 0x00B8 +(0x04 * x))))
#define RSCAN0_RFSTSx(x)        (*((volatile uint32 *)(RSCAN0_BASE + 0x00D8 +(0x04 * x))))
#define RSCAN0_RFPCTRx(x)       (*((volatile uint32 *)(RSCAN0_BASE + 0x00F8 +(0x04 * x))))
#define RSCAN0_RFIDx(x)         (*((volatile uint32 *)(RSCAN0_BASE + 0x0E00 +(0x10 * x))))

/* Transmit/receive FIFO Buffer Register k (k = 0 to 8) */
#define RSCAN0_CFCCx(x)         (*((volatile uint32 *)(RSCAN0_BASE + 0x0118 +(0x04 * x))))
#define RSCAN0_CFSTSx(x)        (*((volatile uint32 *)(RSCAN0_BASE + 0x0178 +(0x04 * x))))
#define RSCAN0_CFPCTRx(x)       (*((volatile uint32 *)(RSCAN0_BASE + 0x01D8 +(0x04 * x))))

/* Status Register */
#define RSCAN0_FESTS            (*((volatile uint32 *)(RSCAN0_BASE + 0x0238)))
#define RSCAN0_FFSTS            (*((volatile uint32 *)(RSCAN0_BASE + 0x023C)))
#define RSCAN0_FMSTS            (*((volatile uint32 *)(RSCAN0_BASE + 0x0240)))
#define RSCAN0_RFISTS           (*((volatile uint32 *)(RSCAN0_BASE + 0x0244)))
#define RSCAN0_CFRISTS          (*((volatile uint32 *)(RSCAN0_BASE + 0x0248)))
#define RSCAN0_CFTISTS          (*((volatile uint32 *)(RSCAN0_BASE + 0x024C)))

/* Transmit Buffer Register (p = 0 to 47) (y = 0, 1) */
#define RSCAN0_TMCp(p)          (*((volatile uint8  *)(RSCAN0_BASE + 0x0250 +(0x01 * p))))
#define RSCAN0_TMSTSp(p)        (*((volatile uint8  *)(RSCAN0_BASE + 0x02D0 +(0x01 * p))))
#define RSCAN0_TMTRSTSy(y)      (*((volatile uint32 *)(RSCAN0_BASE + 0x0350 +(0x04 * y))))
#define RSCAN0_TMTARSTSy(y)     (*((volatile uint32 *)(RSCAN0_BASE + 0x0360 +(0x04 * y))))
#define RSCAN0_TMTCSTSy(y)      (*((volatile uint32 *)(RSCAN0_BASE + 0x0370 +(0x04 * y))))
#define RSCAN0_TMTASTSy(y)      (*((volatile uint32 *)(RSCAN0_BASE + 0x0380 +(0x04 * y))))
#define RSCAN0_TMIECy(y)        (*((volatile uint32 *)(RSCAN0_BASE + 0x0390 +(0x04 * y))))
#define RSCAN0_TMIDp(p)         (*((volatile uint32 *)(RSCAN0_BASE + 0x1000 +(0x04 * p))))

/* EI Level Interrupt Control Registers */
#define INT1_EICn(n)       (*(volatile uint16*)(0xFFFEEA00UL + (n) * 2))
#define INT2_EICn(n)       (*(volatile uint16*)(0xFFFFB040UL + (n - 32) * 2))
#define PBG_FSGD0BPROT0    (*(volatile uint32*)(0xFFC4C000UL))

/******************************************************************************
Global variables and functions
******************************************************************************/
extern const Can_ConfigType* const CanCfgPtr;

static void Can_SetRxRule(void);

/******************************************************************************
* Function Name: Can_Init
* Description  : ADC初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
void Can_Init(void)
{
    uint8 i;

    /* Parameter checkout */
    assert_param((CanCfgPtr != NULL));

    /* Wait while CAN RAM initialization is ongoing */
    while (RSCAN0_GSTS & 0x00000008);

    /* Switch to global/channel reset mode */
    RSCAN0_GCTR &= 0xfffffffb;	//set the 3rd bit to 0 -- global stop mdoe
    RSCAN0_CmCTR(1)  &= 0xfffffffb;

    /* Configure clk_xincan as CAN-ClockSource */
    RSCAN0_GCFG = 0x00000010;
    
    for (i = 0; i < CanCfgPtr->ChNum; i++)
    {
        /* When fCAN is 8MHz, 
        Bitrate = fCAN/(BRP+1)/(1+TSEG1+TSEG2) = 8/1/16 = 0.5Mbps(500Kbps) */
        RSCAN0_CmCFG(CanCfgPtr->ChCfg[i].CanCh) = CanCfgPtr->ChCfg[i].CmCFG; 
    }

    /* ==== Rx rule setting ==== */
    Can_SetRxRule();

    /* ==== buffer setting ==== */    
    RSCAN0_RMNB = 0x10;  //Can_SetGlobalBuffer--16
    RSCAN0_RFCCx(0) = 0x00007602;

    /* Set THLEIE disabled, MEIE(FIFO Message Lost Interrupt disabled)  */
    RSCAN0_GCTR &= 0xfffff8ff;
    RSCAN0_CmCTR(1) |= 0x00600800;    //Bus Error Interrupt Enable
    RSCAN0_TMIECy(0) |= 0xFFFF0000;   //Transmit buffer (16- 31) interrupt is enabled.
    Mcu_EicEnable(70, TABLE_REFERENCE, PRIORITY_7); /* Channel 0 to 2 RX FIFO interrupt */
    Mcu_EicEnable(118, TABLE_REFERENCE, PRIORITY_7);/* Channel 1 error interrupt */
    Mcu_EicEnable(120, TABLE_REFERENCE, PRIORITY_7);/* Channel 1 TX interrupt */


    /* If GlobalChannel in halt or reset mode */
    if (RSCAN0_GSTS & 0x03) 
    {
        RSCAN0_GCTR &= 0xfffffffc; //Switch to communication mode
        while ((RSCAN0_GSTS & 0x02) == 2) {
            /* While halt mode */
        }
        while ((RSCAN0_GSTS & 0x01) == 1) {
            /* While reset mode */
        }
    }

    /* If Channel1 in halt or reset mode */
    if (RSCAN0_CmSTS(1) & 0x03) 
    {
        RSCAN0_CmCTR(1) &= 0xfffffffc;    //Switch to communication mode
        while ((RSCAN0_CmSTS(1) & 0x02) == 2) {
            /* While halt mode */
        }
        while ((RSCAN0_CmSTS(1) & 0x01) == 1) {
            /* While reset mode */
        }
    } 

    /* Receive FIFO Buffer Enable */
    RSCAN0_RFCCx(0) |= 0x00000001;
}

/******************************************************************************
** Function:    Can_SetRxRule
** Description: Set all Rx rules
** Parameter:   None
** Return:      None
******************************************************************************/
static void Can_SetRxRule(void)
{
    uint16 RxRuleIdx;
    uint8 PageRxRuleIdx;
    volatile Can_RuleCfgType* pCRE;
    uint8 i, RuleNum, ShiftBits;

    /* Set Rx rule number per channel */
    for (i = 0; i < CanCfgPtr->ChNum; i++)
    {
        RuleNum = CanCfgPtr->ChCfg[i].RNCEm - CanCfgPtr->ChCfg[i].RNCSm + 1;

        switch (CanCfgPtr->ChCfg[i].CanCh)
        {
            case CAN0: ShiftBits = 24;break;
            case CAN1: ShiftBits = 16;break;
            case CAN2: ShiftBits = 8;break;
            default: break;
        }
        RSCAN0_GAFLCFG0 |= (uint32)(RuleNum << ShiftBits);
    }

    /* Get access base address of Rx rule */
    pCRE = (volatile Can_RuleCfgType*)&(RSCAN0_GAFLIDj(0));
    
    /* Receive Rule Table Write Enable */
    RSCAN0_GAFLECTR |= 0x00000100;	//set bit8 to 1, Receive rule table write is enabled

    /* Copy Rx rule one by one */
    for (RxRuleIdx = 0U; RxRuleIdx < CanCfgPtr->RuleNum; RxRuleIdx++) //CAN_RX_RULE_NUM=12, refer to cab_table.h
    {
        PageRxRuleIdx = (uint8) (RxRuleIdx & CAN_PAGE_RX_RULE_IDX_MASK); //CAN_PAGE_RX_RULE_IDX_MASK= 0xF

        /* Update target Rx rule page if necessary. */
        if (PageRxRuleIdx == 0U) 
        {
            RSCAN0_GAFLECTR|= RxRuleIdx >> CAN_RX_RULE_PAGE_IDX_BIT_POS; //CAN_RX_RULE_PAGE_IDX_BIT_POS= 4U
        }

        /* Set a single Rx rule.*/
        pCRE[PageRxRuleIdx] = CanCfgPtr->Rule_Cfg[RxRuleIdx];
    }

    /* Rx rule write disable */
    RSCAN0_GAFLECTR &= 0xfffffeff;
}

/*****************************************************************************
** Function:    Can_SetMode
** Description: 
** Parameter:   None
** Return:      none
******************************************************************************/
Std_ReturnType Can_SetMode(Can_ChannelType Channel, Can_CsModeType CsMode)
{
    switch (CsMode)
    {
        case CAN_CS_STOP: 
            RSCAN0_GCTR &= 0xfffffffc; 
            RSCAN0_CmCTR(Channel) |= 0x02; 
            break;

        case CAN_CS_START: 
            RSCAN0_GCTR &= 0xfffffffc; 
            RSCAN0_CmCTR(Channel) &= 0xfffffffc; 
            break;

        case CAN_CS_SLEEP: 
            RSCAN0_GCTR |= 0x05;
            RSCAN0_CmCTR(Channel) |= 0x05; 
            break;

        default:break;
    }

    return STD_OK;
}

/*****************************************************************************
** Function:    Can_GetMode
** Description: 
** Parameter:   None
** Return:      none
******************************************************************************/
Can_CsModeType Can_GetMode(Can_ChannelType Channel)
{
    if ((RSCAN0_CmSTS(Channel) & 0x03) == 0)
    {
        return CAN_CS_START;
    }

    if ((RSCAN0_CmSTS(Channel) & 0x02) == 2)
    {
        return CAN_CS_STOP;
    }

    return CAN_CS_SLEEP;
}

/*****************************************************************************
** Function:    Can_SetMode
** Description: 
** Parameter:   None
** Return:      none
******************************************************************************/
uint8 Can_GetCanChNum(void)
{
    return  CanCfgPtr->ChNum;
}

/*****************************************************************************
** Function:    Can_GetHthCanCh
** Description: 
** Parameter:   None
** Return:      none
******************************************************************************/
uint8 Can_GetHthCanCh(uint8 Hth)
{
    (void)Hth;

    return 1;
}

/*****************************************************************************
** Function:    Can_GetHrhCanCh
** Description: 
** Parameter:   None
** Return:      none
******************************************************************************/
uint8 Can_GetHrhCanCh(uint8 Hrh)
{
    (void)Hrh;

    return 1;
}

/*****************************************************************************
** Function:    CAN_Transmit
** Description: This code shows how to read message from Rx buffer
** Parameter:   pRxBufIdx - Pointer to Rx buffer that receives frame
** Return:      CAN_RTN_OK           - A frame is successfully read out
**              CAN_RTN_BUFFER_EMPTY - No frame is read out   
******************************************************************************/
Std_ReturnType CAN_Transmit(Can_ChannelType Channel, const Can_PduType* pFrame)
{
    volatile uint8* pTBSR;
    Can_FrameType* pTxBuffer;
    volatile uint8* pTBCR;
    uint8 TxBufIdx = 0;

    pTBSR = &(RSCAN0_TMSTSp(0));
    pTBCR = &(RSCAN0_TMCp(0));

    TxBufIdx = ((uint8)Channel << 4);

    /* ---- Return if Tx Buffer is transmitting. ---- */
    while((pTBSR[TxBufIdx] & (uint8)0x01) == CAN_TBTST_TRANSMITTING)
    {
        TxBufIdx++;
    }

    if (TxBufIdx >= (CAN_CHANNEL_MAX_BUFFER * (Channel +1)))
    {
        return STD_NOT_OK;
    }

    /* Store message to tx buffer */
    pTxBuffer = (Can_FrameType*) &(RSCAN0_TMIDp(0));
    pTxBuffer[TxBufIdx].ID = pFrame->Id;
    pTxBuffer[TxBufIdx].DLC = pFrame->Length;
    (void) memcpy (pTxBuffer[TxBufIdx].DB, pFrame->Data, 8);

    /* Set transmission request */
    pTBCR[TxBufIdx] = CAN_TBCR_TRM;

    return STD_OK;
}

/******************************************************************************
* Function Name: Can_PollFunction
* Description  : 
* Arguments    : None
* Return Value : None
******************************************************************************/
void Can_PollFunction(void)
{

}

/******************************************************************************
* Function Name: INTRCAN1ERR_IsrHandle
* Description  : Channel 1 error interrupt (INTRCAN1ERR)
* Arguments    : None
* Return Value : None
******************************************************************************/
void INTRCAN1ERR_IsrHandle(void)
{
    RSCAN0CmERFL(1) &= 0x00UL;  //Clear All Error Flag

    if (CanCfgPtr->BusoffCbk != NULL)
    {
        (CanCfgPtr->BusoffCbk)(CAN1);
    }

    Can_SetMode(CAN1, CAN_CS_STOP);

}

/******************************************************************************
* Function Name: INTRCANGRECC_IsrHandle
* Description  : RSCAN Channel 0 to 2 RX FIFO interrupt
* Arguments    : None
* Return Value : None
******************************************************************************/
void INTRCANGRECC_IsrHandle(void)
{
    uint8 i;

    Can_FrameType pRxBuffer;

    for (i = 0; i < CAN_RX_FIFO_BUF_MAX; i++)
    {
        if (RSCAN0_RFSTSx(i) & ~0xFFFFFFF7)
        {
            RSCAN0_RFSTSx(i) &= 0xFFFFFFF7;

            pRxBuffer = *((Can_FrameType*) &(RSCAN0_RFIDx(0)));

            RSCAN0_RFPCTRx(i) = 0xFF;
            break;
        }
    }

    if (CanCfgPtr->RxCallback != NULL)
    {
        (CanCfgPtr->RxCallback)(CAN1, pRxBuffer.ID, pRxBuffer.DLC, pRxBuffer.DB);
    }

}

/******************************************************************************
* Function Name: INTRCAN1TRX_IsrHandle
* Description  : RSCAN1 Channel 1 TX interrupt (INTRCAN1TRX)
* Arguments    : None
* Return Value : None
******************************************************************************/
void INTRCAN1TRX_IsrHandle(void)
{
    uint8 i ;

    for (i = 16; i < 32; i++)
    {
        /* Clear Tx buffer status */
        if (RSCAN0_TMSTSp(i) != 0x00)
        {
            RSCAN0_TMSTSp(i) &= 0x00;
            break;
        }
    }

    if (CanCfgPtr->TxCallback != NULL)
    {
        (CanCfgPtr->TxCallback)(CAN1);
    }
}