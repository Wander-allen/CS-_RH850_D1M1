/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Adc.c 
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
#include "can_table.h"
#include "rscan.h"
#include "Det.h"
#include "Mcu.h"

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

uint32 *AddressPtr[30];
/******************************************************************************
* Function Name: Can_Init
* Description  : ADC初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
void Can_Init(void)
{
    /* Wait while CAN RAM initialization is ongoing */
    while (RSCAN0_GSTS & 0x00000008);

    /* Switch to global/channel reset mode */
    RSCAN0_GCTR &= 0xfffffffb;	//set the 3rd bit to 0 -- global stop mdoe
    RSCAN0_CmCTR(1)  &= 0xfffffffb;


    /* Configure clk_xincan as CAN-ClockSource */
    RSCAN0_GCFG = 0x00000010;
    
    /* When fCAN is 8MHz, 
    Bitrate = fCAN/(BRP+1)/(1+TSEG1+TSEG2) = 8/1/16 = 0.5Mbps(500Kbps) */
    RSCAN0_CmCFG(1) = 0x023a0000; //SJW =3TQ, TSEG1=1TQ, TSEG2=4TQ, BRP=0

    /* ==== Rx rule setting ==== */
    Can_SetRxRule();

    /* ==== buffer setting ==== */    
    RSCAN0_RMNB = 0x10;  //Can_SetGlobalBuffer--16
    RSCAN0_RFCCx(0) = 0x00007602;

    /* Set THLEIE disabled, MEIE(FIFO Message Lost Interrupt disabled)  */
    RSCAN0_GCTR &= 0xfffff8ff;
    RSCAN0_TMIECy(0) |= 0x00020000;
    Mcu_EicEnable(70, TABLE_REFERENCE, PRIORITY_7);
    Mcu_EicEnable(120, TABLE_REFERENCE, PRIORITY_7);


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
    U16 RxRuleIdx;
    U8 PageRxRuleIdx;
    volatile CAN_RX_RULE_TYPE* pCRE;

    /* Set Rx rule number per channel */
    RSCAN0_GAFLCFG0 |= 0x00060000;   //Channel1 rule number is 6

    /* Get access base address of Rx rule */
    pCRE = (volatile CAN_RX_RULE_TYPE*)&(RSCAN0_GAFLIDj(0));
    
    /* Receive Rule Table Write Enable */
    RSCAN0_GAFLECTR |= 0x00000100;	//set bit8 to 1, Receive rule table write is enabled

    /* Copy Rx rule one by one */
    for (RxRuleIdx = 0U; RxRuleIdx < CAN_RX_RULE_NUM; RxRuleIdx++) //CAN_RX_RULE_NUM=12, refer to cab_table.h
    {
        PageRxRuleIdx = (U8) (RxRuleIdx & CAN_PAGE_RX_RULE_IDX_MASK); //CAN_PAGE_RX_RULE_IDX_MASK= 0xF

        /* Update target Rx rule page if necessary. */
        if (PageRxRuleIdx == 0U) 
        {
            RSCAN0_GAFLECTR|= RxRuleIdx >> CAN_RX_RULE_PAGE_IDX_BIT_POS; //CAN_RX_RULE_PAGE_IDX_BIT_POS= 4U
        }

        /* Set a single Rx rule.*/
        pCRE[PageRxRuleIdx] = CAN_RX_RULE_TABLE[RxRuleIdx];
    }

    /* Rx rule write disable */
    RSCAN0_GAFLECTR &= 0xfffffeff;
}

/*****************************************************************************
** Function:    Can_ReadRx_buffer
** Description: This code shows how to read message from Rx buffer
** Parameter:   pRxBufIdx - Pointer to Rx buffer that receives frame
** Return:      CAN_RTN_OK           - A frame is successfully read out
**              CAN_RTN_BUFFER_EMPTY - No frame is read out   
******************************************************************************/
Can_RtnType Can_ReadRxBuffer(Can_FrameType* pFrame)
{
    U8 BufIdx;
    U8 CRBRCFiBufIdx;
    U8 OverwrittenFlag;
    U32 TempCRBRCF0;
    U32 TempCRBRCF1;
    Can_FrameType* pRxBuffer;
    VU32* pCRBRCF;
    Can_RtnType RtnValue;

    /* Judge if new messages are available */
    TempCRBRCF0 = RSCAN0_RMNDy(0);	//Receive Buffer New Data Register, if it is true, new data is coming
    TempCRBRCF1 = RSCAN0_RMNDy(1);

    if ((TempCRBRCF0 == CAN_CLR) && (TempCRBRCF1 == CAN_CLR)) //CAN_CLR==0
    {
        RtnValue = CAN_RTN_BUFFER_EMPTY;	// buffer empty, no new data 
    }
    else
    {
        /* Get Rx buffer that has new message */
        if (TempCRBRCF0 != CAN_CLR) 
        {
            pCRBRCF = &(RSCAN0_RMNDy(0));
            for (BufIdx = 0U; BufIdx < CAN_CRBRCF0_RX_BUF_NUM; ++BufIdx) //CAN_CRBRCF0_RX_BUF_NUM=32
            {
                if ((TempCRBRCF0 & CAN_1_BIT_MASK) == CAN_SET) //CAN_1_BIT_MASK==0x1; CAN_SET=0x1
                {
                    break;	//if checked bit is 1, that means there is a new message in corresponding receive buffer 
                }
                TempCRBRCF0 = TempCRBRCF0 >> CAN_B1_BIT_POS; //CAN_B1_BIT_POS=0x1
            }
        }
        else if (TempCRBRCF1 != CAN_CLR)
        {
            pCRBRCF = &(RSCAN0_RMNDy(1));
            for (BufIdx = 0U; BufIdx < CAN_CRBRCF1_RX_BUF_NUM; ++BufIdx) 
            {
                if ((TempCRBRCF1 & CAN_1_BIT_MASK) == CAN_SET) 
                {
                    break;
                }
                TempCRBRCF1 = TempCRBRCF1 >> CAN_B1_BIT_POS;
            }
            BufIdx += CAN_CRBRCF0_RX_BUF_NUM;	//CAN_CRBRCF0_RX_BUF_NUM ==32U
        }
        /* Calculate index value in CRBRCFi */
        CRBRCFiBufIdx = BufIdx & CAN_5_BIT_MASK;	//CAN_5_BIT_MASK  0x1fU  0B11111

        do 
        {
            /* Clear Rx complete flag of corresponding Rx buffer */
            do 
            {
                CLR_BIT(*pCRBRCF, CRBRCFiBufIdx);	//To clear a flag to 0, the program must write 0 to the flag
            } while (GET_BIT(*pCRBRCF, CRBRCFiBufIdx) == CAN_SET);

            /* Read out message from Rx buffer */
            pRxBuffer = (Can_FrameType*) &(RSCAN0_RMIDq(0));
            *pFrame = pRxBuffer[BufIdx];

            /* Judge if current message is overwritten */
            OverwrittenFlag = GET_BIT(*pCRBRCF, CRBRCFiBufIdx);
            /* message is overwritten */
            if (OverwrittenFlag == CAN_SET) 
            {
                /* User process for message overwritten */
                //Usr_HandleRxBufOverwritten(BufIdx);
            }
        } while (OverwrittenFlag == CAN_SET);

        RtnValue = CAN_RTN_OK;
    }

    return RtnValue;
}



Can_RtnType Can_C0TrmByTxBuf(U8 TxBufIdx, const Can_FrameType* pFrame)
{
    VU8* pTBSR;
    Can_FrameType* pTxBuffer;
    VU8* pTBCR;

    pTBSR = &(RSCAN0_TMSTSp(0));
    pTBCR = &(RSCAN0_TMCp(0));

    /* ---- Return if Tx Buffer is transmitting. ---- */    
    if( (pTBSR[TxBufIdx] & (VU8)0x01) == CAN_TBTST_TRANSMITTING )
    {
        return CAN_RTN_ERR;
    }

    /* Clear Tx buffer status */
    do 
    {
        pTBSR[TxBufIdx] = CAN_CLR;
    } while (pTBSR[TxBufIdx] != CAN_CLR);

    /* Store message to tx buffer */
    pTxBuffer = (Can_FrameType*) &(RSCAN0_TMIDp(0));
    pTxBuffer[TxBufIdx] = *pFrame;

    /* Set transmission request */
    pTBCR[TxBufIdx] = CAN_TBCR_TRM;

    return CAN_RTN_OK;
}

Can_FrameType* pRxBuffer;
/******************************************************************************
* Function Name: INTRCANGRECC_IsrHandle
* Description  : RSCAN Channel 0 to 2 RX FIFO interrupt
* Arguments    : None
* Return Value : None
******************************************************************************/
void INTRCANGRECC_IsrHandle(void)
{

    // RSCAN0.RFSTS0.UINT32 &= 0xFFFFFFF7;
    RSCAN0_RFSTSx(0) &= 0xFFFFFFF7;

    pRxBuffer = (Can_FrameType*) &(RSCAN0_RFIDx(0));

    // RSCAN0.RFPCTR0.UINT32 = 0xFF;
    RSCAN0_RFPCTRx(0) = 0xFF;

}

/******************************************************************************
* Function Name: INTRCAN1TRX_IsrHandle
* Description  : RSCAN1 Channel 1 TX interrupt (INTRCAN1TRX)
* Arguments    : None
* Return Value : None
******************************************************************************/
void INTRCAN1TRX_IsrHandle(void)
{
    // RSCAN0.TMSTS17.BIT.TMTRF = 0;
    RSCAN0_TMSTSp(17) &= 0xF9;
}