/*
============================================================================
 PROJECT: Example project
============================================================================
                           C O P Y R I G H T
============================================================================
 Copyright (c) 2015 by Renesas Electronics GmbH. All rights reserved.
 Arcadiastr. 10
 D-40472 Duesseldorf
 Germany
============================================================================

 Warranty disclaimer:
 Because the product(s) is licensed free of charge, there is no warranty of
 any kind whatsoever and expressly disclaimed and excluded by Renesas, either
 expressed or implied, including but not limited to those for non-
 infringement of intellectual property, merchantability and/or fitness for
 the particular purpose. Renesas shall not have any obligation to maintain,
 service or provide bug fixes for the supplied Product(s) and/or the
 Application.

 Each user is solely responsible for determining the appropriateness of
 using the product(s) and assumes all risks associated with its exercise
 of rights under this agreement, including, but not limited to the risks
 and costs of program errors, compliance with applicable laws, damage to
 or loss of data, programs or equipment, and unavailability or
 interruption of operations.

 Limitation of liability:
 In no event shall Renesas be liable to the user for any incidental,
 consequential, indirect, or punitive damage (including but not limited to
 lost profits) regardless of whether such liability is based on breach of
 contract, tort, strict liability, breach of warranties, failure of
 essential purpose or otherwise and even if advised of the possibility of
 such damages. Renesas shall not be liable for any services or products provided
 by third party vendors, developers or consultants identified or referred
 to the user by Renesas in connection with the product(s) and/or the
 application.

============================================================================
 Enviroment:  Devices:     RH850/D1M2H / R7F701412
              Debugger:    GHS Multi 2000
============================================================================

 GHS Multi example project for use with RH850/D1M2H application board
 (Y-RH850-D1X-MB-T1-V1, Y-RH850-D1M2H-PB-TET-V1) 

============================================================================
*/


//============================================================================
//
// Source code for the RS CAN Functions
//
//============================================================================

//============================================================================
// Includes
//============================================================================
#include "ioDefine.h"
#include "rscan.h"
#include "can_table.h"
#include "Pin.h"

//============================================================================
// Functions
//============================================================================
/*****************************************************************************
** Function:    RS_CAN_init
** Description: Configures the CAN0/CAN1 macros
** Parameter:   None
** Return:      None
******************************************************************************/
void RS_CAN_init(void)
{
    /* default seting: Main Osc/1 -> CAN */
    //protected_write(SYSPROTCMDD1,SYSPROTS1,SYSCKSC_IRSCANXINS_CTL,0x01);
    //while (SYSCKSC_IRSCANXINS_ACT !=0x01); //wait for clk active                                                   
#if 0
    /* Set CAN0TX as P0_4 and CAN0RX as P0_5 */
    PORT_AWOPMC0 |= 0x0030;
    PORT_AWOPFCE0 |= (0x0030);
    PORT_AWOPFC0 |= (0x0030);
    PORT_AWOPM0 &= ~(1<<4);
    PORT_AWOPM0 |= 1<<5;  
#endif
        
    /* Wait while CAN RAM initialization is ongoing */
    //while((RSCAN0GSTS & 0x00000008)) ;
    while (RSCAN0.GSTS.BIT.GRAMINIT);

    /* Switch to global/channel reset mode */
    // RSCAN0GCTR &= 0xfffffffb;	//set the 3rd bit to 0 -- global stop mdoe  
    // RSCAN0C0CTR &= 0xfffffffb;
    RSCAN0.GCTR.UINT32 &= 0xfffffffb;	//set the 3rd bit to 0 -- global stop mdoe
    RSCAN0.C1CTR.UINT32  &= 0xfffffffb;


    /* Configure clk_xincan as CAN-ClockSource */
    //RSCAN0GCFG = 0x00000010;
    RSCAN0.GCFG.UINT32 = 0x00000010;
    
    /* When fCAN is 8MHz, 
    Bitrate = fCAN/(BRP+1)/(1+TSEG1+TSEG2) = 8/1/16 = 0.5Mbps(500Kbps) */

    //RSCAN0C0CFG = 0x023a0000; //SJW =3TQ, TSEG1=11TQ, TSEG2=4TQ, BRP=0
    RSCAN0.C1CFG.UINT32 = 0x023a0000; //SJW =3TQ, TSEG1=1TQ, TSEG2=4TQ, BRP=0

    /* ==== Rx rule setting ==== */
    Can_SetRxRule();

    /* ==== buffer setting ==== */    
    //RSCAN0RMNB = 0x10;  //Can_SetGlobalBuffer--16
    RSCAN0.RMNB.UINT32 = 0x10;  //Can_SetGlobalBuffer--16
    RSCAN0.RFCC0.UINT32 = 0x00007602;

    /* Set THLEIE disabled, MEIE(FIFO Message Lost Interrupt disabled)  */
    //RSCAN0GCTR &= 0xfffff8ff;
    RSCAN0.GCTR.UINT32 &= 0xfffff8ff;
    INTC2.EIC70.UINT16 = 0x0047;


    /* If GlobalChannel in halt or reset mode */
    if (RSCAN0.GSTS.UINT32 & 0x03) 
    {
        RSCAN0.GCTR.UINT32 &= 0xfffffffc; //Switch to communication mode
        while ((RSCAN0.GSTS.UINT32 & 0x02) == 2) {
            /* While halt mode */
        }
        while ((RSCAN0.GSTS.UINT32 & 0x01) == 1) {
            /* While reset mode */
        }
    }

    /* If Channel1 in halt or reset mode */
    if (RSCAN0.C1STS.UINT32 & 0x03) 
    {
        RSCAN0.C1CTR.UINT32 &= 0xfffffffc;    //Switch to communication mode
        while ((RSCAN0.C1STS.UINT32 & 0x02) == 2) {
            /* While halt mode */
        }
        while ((RSCAN0.C1STS.UINT32 & 0x01) == 1) {
            /* While reset mode */
        }
    } 

    RSCAN0.RFCC0.UINT32 |= 0x00000001;
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
    //RSCAN0GAFLCFG0 |= 0x06000000;   //Channel0 rule number is 6
    RSCAN0.GAFLCFG0.UINT32 |= 0x00060000;   //Channel1 rule number is 6

    /* Get access base address of Rx rule */
    // pCRE = (volatile CAN_RX_RULE_TYPE*)&(RSCAN0GAFLID0);
    pCRE = (volatile CAN_RX_RULE_TYPE*)&(RSCAN0.GAFLID0.UINT32);
    
    /* Receive Rule Table Write Enable */
    //RSCAN0GAFLECTR |= 0x00000100;	//set bit8 to 1, Receive rule table write is enabled
    RSCAN0.GAFLECTR.UINT32 |= 0x00000100;	//set bit8 to 1, Receive rule table write is enabled

    /* Copy Rx rule one by one */
    for (RxRuleIdx = 0U; RxRuleIdx < CAN_RX_RULE_NUM; RxRuleIdx++) //CAN_RX_RULE_NUM=12, refer to cab_table.h
    {
        PageRxRuleIdx = (U8) (RxRuleIdx & CAN_PAGE_RX_RULE_IDX_MASK); //CAN_PAGE_RX_RULE_IDX_MASK= 0xF

        /* Update target Rx rule page if necessary. */
        if (PageRxRuleIdx == 0U) 
        {
            //RSCAN0GAFLECTR |= RxRuleIdx >> CAN_RX_RULE_PAGE_IDX_BIT_POS; //CAN_RX_RULE_PAGE_IDX_BIT_POS= 4U
            RSCAN0.GAFLECTR.UINT32 |= RxRuleIdx >> CAN_RX_RULE_PAGE_IDX_BIT_POS; //CAN_RX_RULE_PAGE_IDX_BIT_POS= 4U
        }

        /* Set a single Rx rule.*/
        pCRE[PageRxRuleIdx] = CAN_RX_RULE_TABLE[RxRuleIdx];
    }

    /* Rx rule write disable */
    RSCAN0.GAFLECTR.UINT32 &= 0xfffffeff;
}
#if 0
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
    // TempCRBRCF0 = RSCAN0RMND0;	//Receive Buffer New Data Register, if it is true, new data is coming
    // TempCRBRCF1 = RSCAN0RMND1;
    TempCRBRCF0 = RSCAN0.RMND0.UINT32;	//Receive Buffer New Data Register, if it is true, new data is coming
    TempCRBRCF1 = RSCAN0.RMND1.UINT32;

    if ((TempCRBRCF0 == CAN_CLR) && (TempCRBRCF1 == CAN_CLR)) //CAN_CLR==0
    {
        RtnValue = CAN_RTN_BUFFER_EMPTY;	// buffer empty, no new data 
    }
    else
    {
        /* Get Rx buffer that has new message */
        if (TempCRBRCF0 != CAN_CLR) 
        {
            pCRBRCF = &(RSCAN0.RMND0.UINT32);
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
            pCRBRCF = &(RSCAN0.RMND0.UINT32);
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
            pRxBuffer = (Can_FrameType*) &(RSCAN0.RMID0.UINT32);
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

    // pTBSR = &(RSCAN0TMSTS0);
    // pTBCR = &(RSCAN0TMC0);
    pTBSR = &(RSCAN0.TMSTS0.UINT8);
    pTBCR = &(RSCAN0.TMC0.UINT8);

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
    // pTxBuffer = (Can_FrameType*) &(RSCAN0TMID0);
    pTxBuffer = (Can_FrameType*) &(RSCAN0.TMID0.UINT32);
    pTxBuffer[TxBufIdx] = *pFrame;

    /* Set transmission request */
    pTBCR[TxBufIdx] = CAN_TBCR_TRM;

    return CAN_RTN_OK;
}
#endif
    /* Create Can_FrameType for send and receive data */
    const Can_FrameType CANTraStandData={
    //CiTBpA
    0x18,
    0,
    0,
    0,        
    
    //CiTBpB
    0x0000,                            
    0x000,                            
    0x8,    
    
    {
    0x12,                            //DB0
    0x34,                            //DB1
    0x56,                            //DB2
    0x78,                            //DB3
    //CiTBpD
    0x87,                            //DB4
    0x65,                            //DB5
    0x43,                            //DB6
    0x21                             //DB7
    }
    };
    
    Can_FrameType CANRecData={
    //CiTBpA
    0x00,
    0,
    0,
    0,
    
    //CiTBpB
    0x0000,                                
    0x000,                            
    0x0,                        

    //CiTBpC
    {
    0x00,                            //DB0
    0x00,                            //DB1
    0x00,                            //DB2
    0x00,                            //DB3
    //CiTBpD
    0x00,                            //DB4
    0x00,                            //DB5
    0x00,                            //DB6
    0x00                             //DB7
    }
    };
void rscan_test(void)
{
    Can_ReadRxBuffer(&CANRecData);
    if(CANRecData.DB[0]==0x01)
    {
        CANRecData.DB[0]=0x0;
        Port_FlipPin(PORT_P17, 9);
    }
}




#if 0
 /*****************************************************************************
** Function:    RS_CAN_error
** Description: This function sends/receives and compares data of the CAN-Channels
** Parameter:   None
** Return:      error 1
**              no error 0  
******************************************************************************/
int RS_CAN_error(void)
{
    int rs_count, error,i;

    if(Can_C3TrmByTxBuf(1,&CANTraStandData)== CAN_RTN_OK)
    {

        //Delay
        for(i=0;i<10000;i++);                 //Wait for CAN receive interrupt
                    
        Can_ReadRxBuffer(&CANRecData);        //Channel4 receive the Messages
    }
    
    /* Compare each sent and received value */
    error=0;
    for(rs_count=0; rs_count<8; rs_count++)
    {
        if(CANTraStandData.DB[rs_count] != CANRecData.DB[rs_count])
        {
            error=1;
        }
    }
    return error;
}
#endif
