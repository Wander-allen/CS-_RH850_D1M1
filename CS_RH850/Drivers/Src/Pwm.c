/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Pwm.c 
Author: Wander 
******************************************************************************/

/******************************************************************************
Pragma directive
******************************************************************************/

/******************************************************************************
Includes
******************************************************************************/
#include "Std_Types.h"
#include "ioDefine.h"
#include "Det.h"
#include "Pwm_PBcfg.h"

/******************************************************************************
Define Register
******************************************************************************/

/******************************************************************************
Global variables and functions
******************************************************************************/
extern const Pwm_ConfigType* const PwmCfgPtr;
uint32 TemSLPWGA0;
uint32 TemClkOpt;

/******************************************************************************
* Function Name: Pwm_Init
* Description  : Pwm初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
void Pwm_Init(void)
{
    volatile struct __tag4839 *PWGAn_Ptr;
    volatile uint16 * PWMBA0BRSm_Ptr;
    uint8 i;
 
    /* Parameter checkout */
    assert_param((PWGAn_Ptr != NULL));
    assert_param((PWMBA0BRSm_Ptr != NULL));
    assert_param((PwmCfgPtr != NULL));

    TemSLPWGA0 = 0;
    TemClkOpt = 0;

    /* Setting of the clock cycle of PWMCLKm. PWMCLKm = PCLK / 2 * 16 */
    for (i = 0; i < PwmCfgPtr->ClkNum; i++)
    {
        PWMBA0BRSm_Ptr = PwmCfgPtr->ClkCfg[i].PwmBRSmHw;
        *PWMBA0BRSm_Ptr = PwmCfgPtr->ClkCfg[i].BRSm;

        /* Sets the corresponding clock source for PWBAnTS & PWBAnTT */
        TemClkOpt |= (uint8)0x01 << (PwmCfgPtr->ClkCfg[i].Channel);
    }

    for (i = 0; i < PwmCfgPtr->ChNum; i++)
    {
        /* Hardware register address */
        PWGAn_Ptr = PwmCfgPtr->ChCfg[i].PwmHw;

        /* Sets the setting condition for PWGA_TOUTn output.                                    */
        /* PWM period = ( 1 / PWMCLK0 ) * (4095+1) = 0.0016384s (TRGOUT0) , (PWMCLK0 = 2.5MHz)  */
        /* High Level = (PWGAnCRDR - PWGAnCSDR) * ( 1 / PWMCLK0 )                               */
        PWGAn_Ptr->CSDR.UINT16 = PwmCfgPtr->ChCfg[i].CSDR;

        /* Sets the reset condition for PWGA_TOUTn output.*/
        PWGAn_Ptr->CRDR.UINT16 = PwmCfgPtr->ChCfg[i].CRDR;

        /* Select the count clock from PWBA.Uses PWMCLK0 as count clock */
        PWGAn_Ptr->CTL.UINT8 = PwmCfgPtr->ChCfg[i].CTL;

        /* Sets the corresponding channel for SLPWGA */
        TemSLPWGA0 |= (uint32)0x0001 << (PwmCfgPtr->ChCfg[i].Channel);
    }
    
    /* Start for PWMCLKm. */
    PWBA0.TS.UINT8  = TemClkOpt;
    while( (PWBA0.TE.UINT8 & 0x01U) != TemClkOpt )
    {
        /* Waiting for PWBA0TE to set. */
    }

    /* Start for respective channels simultaneously. */
    SELB.SLPWGA0.UINT32                   = TemSLPWGA0;
}

/******************************************************************************
* Function Name: Pwm_Init
* Description  : Pwm初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
void Pwm_DeInit(void)
{
    volatile struct __tag4839 *PWGAn_Ptr;
    uint8 i;

    for (i = 0; i < PwmCfgPtr->ChNum; i++)
    {
        /* Hardware register address */
        PWGAn_Ptr = PwmCfgPtr->ChCfg[i].PwmHw;


        /* The PWM output is fixed to the low level*/
        if (PwmCfgPtr->ChCfg[i].IdleSta == 0)
        {
            PWGAn_Ptr->CSDR.UINT16 = 0x00;
            PWGAn_Ptr->CRDR.UINT16 = 0x00;
            PWGAn_Ptr->RDT.UINT8 = 0x01U;
            continue;
        }

        /* The PWM output is fixed to the high level*/
        PWGAn_Ptr->CRDR.UINT16 |= 0x1000;
        PWGAn_Ptr->RDT.UINT8 = 0x01U;
    }

    /* Stop for respective channels simultaneously. */
    SELB.SLPWGA0.UINT32 &= ~TemSLPWGA0;

    /* Stop for PWMCLKm. */
    PWBA0.TT.UINT8 = TemClkOpt;
    //while( (PWBA0.TE.UINT8 & TemClkOpt) == TemClkOpt ) 
    {
        /* Waiting for PWBA0TE to reset. */
    }

}

/******************************************************************************
* Function Name: Pwm_Start
* Description  : Pwm启动
* Arguments    : None
* Return Value : None
******************************************************************************/
void Pwm_SetDutyCycle(uint8 Ch, uint16 DutyCycle)
{
    volatile struct __tag4839 *PWGAn_Ptr = PwmCfgPtr->ChCfg[Ch].PwmHw;

    if ( (PWGAn_Ptr->RSF.UINT8 & 0x01U) == 0x00U )
    {
        /* Sets the setting condition for PWGA_TOUTn output. */
        PWGAn_Ptr->CSDR.UINT16           = 0U;

        /* Sets the reset condition for PWGA_TOUTn output. */
       PWGAn_Ptr->CRDR.UINT16 = DutyCycle;

        /* Triggers the simultaneous rewrite request for the compare registers. */
        PWGAn_Ptr->RDT.UINT8 = 0x01U;
    }
}


