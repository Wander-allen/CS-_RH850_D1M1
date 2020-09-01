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
#include "Adc_PBcfg.h"
#include "Adc_Define.h"
#include "Adc.h"
#include "Eic.h"

/******************************************************************************
#Define Register
******************************************************************************/
#define ADCE0_BASE              ((uint32)0xFFF20000)

#define ADCE0_ADCR              (*(volatile uint32 *)(ADCE0_BASE + 0x304))
#define ADCE0_SGSTR             (*(volatile uint32 *)(ADCE0_BASE + 0x308))
#define ADCE0_SFTCR             (*(volatile uint32 *)(ADCE0_BASE + 0x334))
#define ADCE0_DGCTL0            (*(volatile uint32 *)(ADCE0_BASE + 0x350))
#define ADCE0_DGCTL1            (*(volatile uint32 *)(ADCE0_BASE + 0x354))
#define ADCE0_PDCTL2            (*(volatile uint32 *)(ADCE0_BASE + 0x35C))
#define ADCE0_SMPCR             (*(volatile uint32 *)(ADCE0_BASE + 0x380))

#define ADCE0_VCRj(j)           (*(volatile uint32 *)(ADCE0_BASE + (0x0004 * (j))))
#define ADCE0_DRj(j)            (*(volatile uint32 *)(ADCE0_BASE + (0x0002 * (j)) + 0x100))
#define ADCE0_DIRj(j)           (*(volatile uint32 *)(ADCE0_BASE + (0x0004 * (j)) + 0x200))
#define ADCE0_SGSTCRx(x)        (*(volatile uint32 *)(ADCE0_BASE + (0x0040 * (x)) + 0x400))
#define ADCE0_SGCRx(x)          (*(volatile uint32 *)(ADCE0_BASE + (0x0040 * (x)) + 0x408))
#define ADCE0_SGVCSPx(x)        (*(volatile uint32 *)(ADCE0_BASE + (0x0040 * (x)) + 0x40C))
#define ADCE0_SGVCEPx(x)        (*(volatile uint32 *)(ADCE0_BASE + (0x0040 * (x)) + 0x410))
#define ADCE0_SGMCYCRx(x)       (*(volatile uint32 *)(ADCE0_BASE + (0x0040 * (x)) + 0x414))
#define ADCE0_SGTSELx(x)        (*(volatile uint32 *)(ADCE0_BASE + (0x0040 * (x)) + 0x41C))

/******************************************************************************
Global variables and functions
******************************************************************************/
extern const Adc_ConfigType* const AdcCfgPtr;

/******************************************************************************
* Function Name: Adc_Init
* Description  : ADC初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
void ADC0_Init(void)
{
    uint8 VirChId;
    uint8 GroupId;
    uint8 i;

    /* Parameter checkout */
    assert_param((AdcCfgPtr != NULL));
    assert_param((AdcCfgPtr->ChCfg != NUll));
    assert_param((AdcCfgPtr->ChNum > 0));
    assert_param((AdcCfgPtr->GroupCfg != NUll));
    assert_param((AdcCfgPtr->GroupNum > 0));
    assert_param((AdcCfgPtr->ModuleCfg != NUll));

    /* Physical Channel Select */
    for (i = 0; i < AdcCfgPtr->ChNum; i++)
    {
        VirChId = AdcCfgPtr->ChCfg[i].VirCh;
        ADCE0_VCRj(VirChId) = AdcCfgPtr->ChCfg[i].PhyCh | 0x10;
    }
  
    /* Operation setting */
    ADCE0_ADCR = AdcCfgPtr->ModuleCfg->ADCR;    /* ADC common operation control setting */
    ADCE0_SMPCR = AdcCfgPtr->ModuleCfg->SMPCR;  /* Sampling control setting */

    /* Error check */
    ADCE0_SFTCR = 0x00000000;  /* Bit[2]=0 -> Overwrite Error Interrupt disabled
                             Bit[3]=0 -> Upper Limit/Lower Limit Error Interrupt disabled
                             Bit[4]=0 -> When the A/D conversion result is read, the A/D conversion result is not cleared by hardware.*/

    /* Self-diagnosis */
    ADCE0_DGCTL0 = 0x00000000;   /*  No setting for Self-Diagnostic voltage level */
    ADCE0_DGCTL1 = 0x00000000;   /*  No channels selected for Self-Diagnostic */

    ADCE0_PDCTL2 = 0x00000000;   /*  Bits[19..0]=0 -> ANIn[00:19] Pull-down enable is off */

    /* Hardware trigger */
    ADCE0_SGTSELx(1) = 0x00000000;  /*  Bits[8..0]=0 ->External input HW trigger is disabled   */
    ADCE0_SGTSELx(2) = 0x00000000;  /*  Bits[8..0]=0 ->External input HW trigger is disabled   */
    ADCE0_SGTSELx(3) = 0x00000000;  /*  Bits[8..0]=0 ->External input HW trigger is disabled   */

    /* SG1-3 operation */
    for (i = 0; i < AdcCfgPtr->GroupNum; i++)
    {
        GroupId = AdcCfgPtr->GroupCfg->SGId;
        ADCE0_SGVCSPx(GroupId) = AdcCfgPtr->GroupCfg[i].SGVCSP;
        ADCE0_SGVCEPx(GroupId) = AdcCfgPtr->GroupCfg[i].SGVCEP;
        ADCE0_SGMCYCRx(GroupId)  = 0x00000000;  /*  Bits[1,0]=0 -> specify the number  of times for scanning in multicycle scan mode */
        ADCE0_SGCRx(GroupId) = AdcCfgPtr->GroupCfg[i].SGCR;
    }

    /* enable Scan group 1 interrupt (INTADCE0I1) with reference table jump  */
    Eic_Enable(66, TABLE_REFERENCE, PRIORITY_7);
}

/******************************************************************************
* Function Name: Adc_DeInit
* Description  : ADC初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
void Adc_DeInit(void)
{
    uint8 GroupId;
    uint8 i;

    for (i = 0; i < AdcCfgPtr->GroupNum; i++)
    {
        GroupId = AdcCfgPtr->GroupCfg[i].SGId;
        ADCE0_SGSTCRx(GroupId) = 0x00;/* Scan Group x Stop Trigger */
    }
}

/******************************************************************************
* Function Name: Adc_StopGroup
* Description  : ADC初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
void Adc_StopGroup(ADC_ChannelType ChId)
{
    uint8 GroupId;

    GroupId = AdcCfgPtr->GroupCfg[ChId].SGId;
    ADCE0_SGSTCRx(GroupId) = 0x00;/* Scan Group x Start Trigger */
}

/******************************************************************************
* Function Name: Adc_StartGroup
* Description  : ADC初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
void Adc_StartGroup(ADC_ChannelType ChId, uint16* Buffer)
{
    uint8 GroupId;
    uint8 VirChId;

    GroupId = AdcCfgPtr->GroupCfg[ChId].SGId;
    ADCE0_SGSTCRx(GroupId) = 0x01;/* Scan Group x Start Trigger */

    VirChId = AdcCfgPtr->ChCfg[ChId].VirCh;
    *Buffer = ADCE0_DRj(VirChId);

}

/******************************************************************************
* Function Name: Adc_StopGroup
* Description  : ADC初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
Adc_StatusType Adc_GetStatus(ADC_ChannelType ChId)
{
    uint8 GroupId;
    uint32 Act;

    GroupId = AdcCfgPtr->GroupCfg[ChId].SGId;
    Act = (uint32)1 << GroupId ;

    if (ADCE0_SGSTR & 0x00F0)
    {
        if (ADCE0_SGSTR & Act)
        {
            return ADC_COMPLETED;
        }
        return ADC_BUSY;
    }

    return ADC_IDLE;
}

/******************************************************************************
* Function Name: Adc_Init
* Description  : ADCE0 Scan group 1 interrupt (INTADCE0I1)
* Arguments    : None
* Return Value : None
******************************************************************************/
void INTADCE0I1_IsrHandle(void)
{
    if (AdcCfgPtr->GroupCfg[0].SGId == 1)
    {
        if (AdcCfgPtr->GroupCfg[0].EndCallback != NULL)
        {
            (AdcCfgPtr->GroupCfg[0].EndCallback)();
        }
    }
}
