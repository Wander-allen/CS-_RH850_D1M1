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
// #include "ioDefine.h"
#include "Det.h"
#include "Pwm_PBcfg.h"
#include "Pwm_Define.h"

/******************************************************************************
Rigister Struct
******************************************************************************/

typedef struct 
{                                                   /* Module           */
    uint16 BRS0;                                    /* BRS0             */
    uint8  dummy800[2];                             /* Reserved         */
    uint16 BRS1;                                    /* BRS1             */
    uint8  dummy801[2];                             /* Reserved         */
    uint16 BRS2;                                    /* BRS2             */
    uint8  dummy802[2];                             /* Reserved         */
    uint16 BRS3;                                    /* BRS3             */
    uint8  dummy803[2];                             /* Reserved         */
    uint8 TE;                                       /* TE               */
    uint8  dummy804[3];                             /* Reserved         */
    uint8 TS;                                       /* TS               */
    uint8  dummy805[3];                             /* Reserved         */
    uint8 TT;                                       /* TT               */
    uint8  dummy806[3];                             /* Reserved         */
    uint8 EMU;                                      /* EMU              */
}PWBAn_Type;

typedef struct 
{                                                   /* Module           */
    uint16 CSDR;                                    /* CSDR             */
    uint8 dummy791[2];                              /* Reserved         */
    uint16 CRDR;                                    /* CRDR             */
    uint8 dummy792[2];                              /* Reserved         */
    uint16 CTDR;                                    /* CTDR             */
    uint8 dummy793[2];                              /* Reserved         */
    uint8 RDT;                                      /* RDT              */
    uint8 dummy794[3];                              /* Reserved         */
    uint8 RSF;                                      /* RSF              */
    uint8 dummy795[3];                              /* Reserved         */
    uint16 CNT;                                     /* CNT              */
    uint8 dummy796[10];                             /* Reserved         */
    uint8 CTL;                                      /* CTL              */
    uint8 dummy797[3];                              /* Reserved         */
    uint16 CSBR;                                    /* CSBR             */
    uint8 dummy798[2];                              /* Reserved         */
    uint16 CRBR;                                    /* CRBR             */
    uint8 dummy799[2];                              /* Reserved         */
    uint16 CTBR;                                    /* CTBR             */
}PWGAn_Type;

/******************************************************************************
Define Register
******************************************************************************/
#define PWBA0_BASE          ((uint32)0xFFE45800)
#define PWBA0_BRSm(m)       (*(volatile uint16 *)(PWBA0_BASE + (0x0004 * (m))))
#define PWBA0               (*(volatile PWBAn_Type *)(PWBA0_BASE))

#define PWGAn_BASE(n)       (0xFFE44000 + (0x100 * (n))))
#define PWGAn(n)            (*(volatile PWGAn_Type *)(0xFFE44000 + (0x100 * (n))))

#define SLPWGA0             (*(volatile uint32 *)0xFFE45900)

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
    uint8 i, Channel;
 
    /* Parameter checkout */
    assert_param((PwmCfgPtr != NULL));
    assert_param((PwmCfgPtr->ChCfg != NULL));
    assert_param((PwmCfgPtr->ChNum > 0));
    assert_param((PwmCfgPtr->ClkCfg != NULL));
    assert_param((PwmCfgPtr->ClkNum > 0));

    TemSLPWGA0 = 0;
    TemClkOpt = 0;

    /* Setting of the clock cycle of PWMCLKm. PWMCLKm = PCLK / 2 * 16 */
    for (i = 0; i < PwmCfgPtr->ClkNum; i++)
    {
        Channel = PwmCfgPtr->ClkCfg[i].Channel;
        PWBA0_BRSm(Channel) = PwmCfgPtr->ClkCfg[i].BRSm;

        /* Sets the corresponding clock source for PWBAnTS & PWBAnTT */
        TemClkOpt |= (uint8)0x01 << (PwmCfgPtr->ClkCfg[i].Channel);
    }

    for (i = 0; i < PwmCfgPtr->ChNum; i++)
    {
        /* Hardware register address */
        Channel = PwmCfgPtr->ChCfg[i].Channel;

        /* Sets the setting condition for PWGA_TOUTn output.                                    */
        /* PWM period = ( 1 / PWMCLK0 ) * (4095+1) = 0.0016384s (TRGOUT0) , (PWMCLK0 = 2.5MHz)  */
        /* High Level = (PWGAnCRDR - PWGAnCSDR) * ( 1 / PWMCLK0 )                               */
        PWGAn(Channel).CSDR = PwmCfgPtr->ChCfg[i].CSDR;

        /* Sets the reset condition for PWGA_TOUTn output.*/
        PWGAn(Channel).CRDR = PwmCfgPtr->ChCfg[i].CRDR;

        /* Select the count clock from PWBA.Uses PWMCLK0 as count clock */
        PWGAn(Channel).CTL = PwmCfgPtr->ChCfg[i].CTL;

        /* Sets the corresponding channel for SLPWGA */
        TemSLPWGA0 |= (uint32)0x0001 << (PwmCfgPtr->ChCfg[i].Channel);
    }
    
    /* Start for PWMCLKm. */
    PWBA0.TS = TemClkOpt;
    while( (PWBA0.TE & 0x01U) != TemClkOpt )
    {
        /* Waiting for PWBA0TE to set. */
    }

    /* Start for respective channels simultaneously. */
    SLPWGA0 = TemSLPWGA0;
}

/******************************************************************************
* Function Name: Pwm_Init
* Description  : Pwm初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
void Pwm_DeInit(void)
{
    uint8 i, Channel;

    for (i = 0; i < PwmCfgPtr->ChNum; i++)
    {
        /* Hardware register address */
        Channel = PwmCfgPtr->ChCfg[i].Channel;


        /* The PWM output is fixed to the low level*/
        if (PwmCfgPtr->ChCfg[i].IdleSta == 0)
        {
            PWGAn(Channel).CSDR = 0x00;
            PWGAn(Channel).CRDR = 0x00;
            PWGAn(Channel).RDT = 0x01;
            continue;
        }

        /* The PWM output is fixed to the high level*/
        PWGAn(Channel).CRDR |= 0x1000;
        PWGAn(Channel).RDT = 0x01;
    }

    /* Stop for respective channels simultaneously. */
    SLPWGA0 &= ~TemSLPWGA0;

    /* Stop for PWMCLKm. */
    PWBA0.TT = TemClkOpt;
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
void Pwm_SetDutyCycle(Pwm_ChannelType Ch, uint16 DutyCycle)
{
    uint8  Channel;

    Channel = PwmCfgPtr->ChCfg[Ch].Channel;
    
    if ( (PWGAn(Channel).RSF & 0x01U) == 0x00U )
    {
        /* Sets the setting condition for PWGA_TOUTn output. */
        PWGAn(Channel).CSDR           = 0U;

        /* Sets the reset condition for PWGA_TOUTn output. */
        PWGAn(Channel).CRDR = DutyCycle;

        /* Triggers the simultaneous rewrite request for the compare registers. */
        PWGAn(Channel).RDT = 0x01;
    }
}



