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
#include "ioDefine.h"
#include "Std_Types.h"
#include "Det.h"
#include "Adc.h"
#include "Pin.h"


/******************************************************************************
#Define
******************************************************************************/

/******************************************************************************
Global variables and functions
******************************************************************************/

/******************************************************************************
* Function Name: Adc_Init
* Description  : ADC初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
void ADC0_Init(void)
{
  //normal mode
//   ADCE0VCR00 = 0x000000010;/* Bits[5..0]=0 -> Select AP0_0 as Physical Channel
    ADCE0.VCR00.UINT32 = 0x000000014;/* Bits[5..0]=14 -> Select AP0_4 as Physical Channel  
                                Bits[7,6]=00b -> No Upper Limit/Lower Limit  check
                                Bit[8]=0 -> disable A/D Conversion End Interrupt Enable 
                                Bit[9]=0 -> A/D conversion of the hold value is performed during a self-diagnostic
                                Bit[14..12]=0 -> do not set the MPX value to be transferred to an external analog multiplexer.
                                Bit[15]=0 -> do not enable MPX
                            */
  
  
//   ADCE0ADCR=0x00000002;   /* Bits[1,0]=10b -> Asynchronous suspend
    ADCE0.ADCR.UINT32=0x00000002;   /* Bits[1,0]=10b -> Asynchronous suspend
                             Bit[4]=0 -> CRAC: 12-bit mode
                             Bit[5]=0 -> CTYP: PWDDR and ADCAnDRj are set to right align
                             Bit[7]=0 -> The self-diagnostic voltage circuit is turned off
                         */
                             
//   ADCE0SMPCR=0x00000018;  /* Bits[7..0]=00010010b   Set sampling time to 24cycles/40MHz */
    ADCE0.SMPCR.UINT32=0x00000018;  /* Bits[7..0]=00010010b   Set sampling time to 24cycles/40MHz */
 
//   ADCE0SFTCR=0x00000000;  /* Bit[2]=0 -> Overwrite Error Interrupt disabled
  ADCE0.SFTCR.UINT32=0x00000000;  /* Bit[2]=0 -> Overwrite Error Interrupt disabled
                             Bit[3]=0 -> Upper Limit/Lower Limit Error Interrupt disabled
                             Bit[4]=0 -> When the A/D conversion result is read, the A/D conversion result is not cleared by hardware.
                          */
  
//   ADCE0DGCTL0=0x00000000;   /*  No setting for Self-Diagnostic voltage level */
//   ADCE0DGCTL1=0x00000000;   /*  No channels selected for Self-Diagnostic */
    ADCE0.DGCTL0.UINT32=0x00000000;   /*  No setting for Self-Diagnostic voltage level */
    ADCE0.DGCTL0.UINT32=0x00000000;   /*  No channels selected for Self-Diagnostic */
  
//   ADCE0PDCTL1=0x00000000;   /*  Bits[15..0]=0 -> ANIn[00:15] Pull-down enable is off */
//   ADCE0PDCTL2=0x00000000;   /*  Bits[19..0]=0 -> ANI0[16:35], ANI1[16:23] Pull-down enable is off*/
    ADCE0.PDCTL2.UINT32=0x00000000;   /*  Bits[19..0]=0 -> ANIn[00:19] Pull-down enable is off */


//   ADCE0SGTSEL1=0x00000000;  /*  Bits[8..0]=0 ->External input HW trigger is disabled   */
//   ADCE0SGTSEL2=0x00000000;  /*  Bits[8..0]=0 ->External input HW trigger is disabled   */
//   ADCE0SGTSEL3=0x00000000;  /*  Bits[8..0]=0 ->External input HW trigger is disabled   */
    ADCE0.SGTSEL1.UINT32=0x00000000;  /*  Bits[8..0]=0 ->External input HW trigger is disabled   */
    ADCE0.SGTSEL2.UINT32=0x00000000;  /*  Bits[8..0]=0 ->External input HW trigger is disabled   */
    ADCE0.SGTSEL3.UINT32=0x00000000;  /*  Bits[8..0]=0 ->External input HW trigger is disabled   */

//   ADCE0SGVCSP1=0x00000000;  /*  Bits[5..0]=0 -> select the virtual channel 0 from which the scan is to be started */
//   ADCE0SGVCEP1=0x00000000;  /*  Bits[5..0]=0 -> select the virtual channel 0 from which the scan is to be ended */  
//   ADCE0SGMCYCR1=0x00000000; /*  Bits[1,0]=0 -> specify the number  of times for scanning in multicycle scan mode */
  ADCE0.SGVCSP1.UINT32=0x00000000;  /*  Bits[5..0]=0 -> select the virtual channel 0 from which the scan is to be started */
  ADCE0.SGVCEP1.UINT32=0x00000000;  /*  Bits[5..0]=0 -> select the virtual channel 0 from which the scan is to be ended */  
  ADCE0.SGMCYCR1.UINT32=0x00000000; /*  Bits[1,0]=0 -> specify the number  of times for scanning in multicycle scan mode */
  
//   ADCE0SGCR1=0x00000010;    /*  Bit[0]=0 -> SGx_TRG trigger is disabled
    ADCE0.SGCR1.UINT32=0x00000010;    /*  Bit[0]=0 -> SGx_TRG trigger is disabled
                             Bits[3,2]=0 -> Channel repeat times is one
                             Bit[4]=1 -> INT_SGx is output when the scan for SGx ends
                             Bit[5]=0 -> Multicycle scan mode
                             */
                             
//   INTC2EIC66 = 0x004f;       /* enable Scan group 1 interrupt (INTADCE0I1) with reference table jump  */
    INTC2.EIC66.UINT16 = 0x004f;       /* enable Scan group 1 interrupt (INTADCE0I1) with reference table jump  */
    
}

/******************************************************************************
* Function Name: ADC0_Start
* Description  : ADC初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
void ADC0_Start(void)
{
//   ADCE0SGSTCR1=0x1; /* Scan Group 1 Start Trigger */
    ADCE0.SGSTCR1.UINT32 = 0x1; /* Scan Group 1 Start Trigger */
}

/******************************************************************************
* Function Name: ADC0_Stop
* Description  : ADC初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
void ADC0_Stop(void)
{
//   ADCE0SGSTCR1=0x1; /* Scan Group 1 Start Trigger */
    ADCE0.SGSTCR1.UINT32 = 0x0; /* Scan Group 1 End Trigger */
}

uint32 Result[19] = {0};
/******************************************************************************
* Function Name: Adc_Init
* Description  : ADCE0 Scan group 1 interrupt (INTADCE0I1)
* Arguments    : None
* Return Value : None
******************************************************************************/
void INTADCE0I1_IsrHandle(void)
{

    Result[0]=(ADCE0.DIR00.BIT.DR & 0x0fff);

}
