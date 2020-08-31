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

/******************************************************************************
* Function Name: Pwm_Init
* Description  : Pwm初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
void Pwm_Init(void)
{
    /*The INTC2 registers are not accessible per default as these registers are guarded by
        the PBUS Guard PBG0B. Before accessing any of these registers the PBG0B protection
        register FSGD0BPROT0 has to be set to 07FF FFFFH.*/
    // PBGFSGD0BPROT0 = 0x07FFFFFFUL;	
    // INTC2EIC141 |= 0x0080; 		/* demask PWGA0 interrupt and enable reference table jump method */
    PBG.FSGD0APROT0.UINT32 = 0x07FFFFFFUL;
    INTC2.EIC163.UINT16 |= 0x0080; 		/* demask PWGA22 interrupt and enable reference table jump method */

    /* Setting of the ADCA corresponding to each channel.
    PWSAnPVCRx_y - PWSAnPVCRx_y Register
    b31:b29                   - Reserved set to 0
    b28            PWSAnSLADy - ADCTL Select (odd-numbered channel)                  - Unused. Set to 0'b
    b27            PWSAnVRDTy - This bit indicates the setting value of the
                                ADCAnPWDVCR.MPXE bit (oddnumbered channel).           - The use of MPX is prohibited.
    b26:b24        PWSAnVRDTy - This bit indicates the setting value of the
                                ADCAnPWDVCR.MPXV[2:0] bits (oddnumbered channel).     - Unused. Set to 000'b. 
    b23:b22        PWSAnVRDTy - This bit indicates the setting value of the
                                ADCAnPWDVCR.ULS[1:0] bits (oddnumbered channel).      - Unused. Set to 0'b
    b21:b16        PWSAnVRDTy - This bit indicates the setting value of the
                                ADCAnPWDVCR.GCTRL[5:0] bits (odd-numbered channel).   - Unused. Set to 0'b
    b15:b13                   - Reserved set to 0
    b12            PWSAnSLADx - ADCTL Select (even-numbered channel)                  - Unused. Set to 0'b.
    b11            PWSAnVRDTx - This bit indicates the setting value of the 
                                ADCAnPWDVCR.MPXE bit. (evennumbered channel)          - Unused. Set to 0'b.
    b10:b 8        PWSAnVRDTx - These bits indicate the setting value of the
                                ADCAnPWDVCR.MPXV[2:0] bits. (even-numbered channel)   - Unused. Set to 0'b.
    b 7:b 6        PWSAnVRDTx - These bits indicate the setting value of the
                                ADCAnPWDVCR.ULS[1:0] bits. (even-numbered channel)   - Upper limit and lower limit are
                                                                                        checked for ADCAnULLMTBR0.
                                                                                        Set to 01'b.
    b 5:b 0        PWSAnVRDTx - These bits indicate the setting value of the
                                ADCAnPWDVCR.GCTRL[5:0] bits. (even-numbered channel)  - Select ANI000 */
    //PWSA0.PVCR00_01.UINT32           = 0x00000050UL;

    /* Setting of the clock cycle of PWMCLKm.
    PWBAnBRSm    - PWBAnBRSm Register
    b15:b11                   - Reserved set to 0
    b10:b 0        PWBAnBRSm  - Register for setting the clock cycle of PWMCLKm.      - PWMCLKm = PCLK / 2 * 16  */
    PWBA0.BRS0.UINT16                = 0x0010U;         /* PWMCLK0 = PCLK / ( 2 * 16 ) = 2.5MHz , (PCLK = 80MHz) */

    /* Sets the setting condition for PWGA_TOUTn output.
    PWGAnCSDR    - PWM Output Set Condition Register
    b15:b12                   - Reserved set to 0
    b11:b 0        PWGAnCSDR  - Setting condition for PWM output. */
                        /* PWM period = ( 1 / PWMCLK0 ) * (4095+1) = 0.0016384s (TRGOUT0) , (PWMCLK0 = 2.5MHz) */
                        /* High Level = (PWGAnCRDR - PWGAnCSDR) * ( 1 / PWMCLK0 )                              */
    //PWGA22.CSDR.UINT16               = 0x0FFFU / 2U;
    PWGA22.CSDR.UINT16               = 0;

    /* Sets the reset condition for PWGA_TOUTn output.
    PWGAnCRDR    - PWM Output Set Condition Register
    b15:b12                   - Reserved set to 0
    b11:b 0        PWGAnCRDR  - Reset condition for PWM output. */
    PWGA22.CRDR.UINT16               = 0xFFFU;		//0x9c3

    /* Sets the generation condition for PWGA_TRGOUTn.
    PWGAnCTDR    - PWGA_TRGOUTn Generation Condition Register
    b15:b12                   - Reserved set to 0
    b11:b 0        PWGAnCTDR  - A/D conversion trigger generation condition for PWSAn.  */
                            /* A/D trigger position =  PWGA0CTDR * ( 1 / PWMCLK0 )   */
    //PWGA22.CTDR.UINT16               = 0x0FFFU / 2U + 0x400U;


    /* Select the count clock from PWBA.
    PWGAnCTL     - PWGA Control Register
    b 7:b 6                   - Reserved set to 0
    b 0            PWGAnCKS   - Count Clock Enable Input PWMCLK3 to PWMCLK0 Select  - Uses PWMCLK0 as count clock */
    PWGA22.CTL.UINT8                = 0x00U;
}

/******************************************************************************
* Function Name: Pwm_Start
* Description  : Pwm启动
* Arguments    : None
* Return Value : None
******************************************************************************/
void Pwm_Start(void)
{
    /*The INTC2 registers are not accessible per default as these registers are guarded by
    the PBUS Guard PBG0B. Before accessing any of these registers the PBG0B protection
    register FSGD0BPROT0 has to be set to 07FF FFFFH.*/
    // PBGFSGD0BPROT0 = 0x07FFFFFFUL;	
    // INTC2EIC141 = 0x0047; 		/* demask PWGA0 interrupt and enable reference table jump method */
    PBG.FSGD0APROT0.UINT32 = 0x07FFFFFFUL;
    INTC2.EIC163.UINT16 |= 0x0047; 		/* demask PWGA22 interrupt and enable reference table jump method */

    /* Start for PWMCLKm.
    PWBAnTS      - PWBAnTS Register
    b 7:b 4                   - Reserved set to 0
    b 3            PWBAnTS3   - Start trigger bit for PWMCLK3                         - Unused. set to 0'b
    b 2            PWBAnTS2   - Start trigger bit for PWMCLK2                         - Unused. set to 0'b
    b 1            PWBAnTS1   - Start trigger bit for PWMCLK1                         - Unused. set to 0'b
    b 0            PWBAnTS0   - Start trigger bit for PWMCLK0                         - Starts the output of PWMCLK0. */
    PWBA0.TS.UINT8                  = 0x01U;
    while( (PWBA0.TE.UINT8 & 0x01U) != 0x01U )
    {
    /* Waiting for PWBA0TE to set. */
    }

    /* Start for respective channels simultaneously.
    PWBAnTS      - PWBAnTS Register
    b31:b 0        SLPWGA     - Trigger start and stop to multiple channels
                            simultaneously.                                      - Starts the corresponding ch.22 */
    //SELBSLPWGA0                   = 0x00000001UL;
    SELB.SLPWGA0.UINT32                   = 0x00400000UL;

}

/******************************************************************************
* Function Name : void PWMD_Stop( void )
* Description   : This function stop the PWM-diag. ch.22.
* Argument      : none
* Return Value  : none
******************************************************************************/
void PWM_Stop( void )
{
	/*The INTC2 registers are not accessible per default as these registers are guarded by
	    the PBUS Guard PBG0B. Before accessing any of these registers the PBG0B protection
	    register FSGD0BPROT0 has to be set to 07FF FFFFH.*/
	PBG.FSGD0APROT0.UINT32 = 0x07FFFFFFUL;	
	INTC2.EIC163.UINT16                  |= 0x0080U;                     /* Disable INTPWGA0                   */


	/* Stop for respective channels simultaneously.
	PWBAnTS      - PWBAnTS Register
	b31:b 0        SLPWGA     - Trigger start and stop to multiple channels
	                            simultaneously.                                 - Stops the corresponding ch.22 */
	SELB.SLPWGA0.UINT32                   &= ~0x00400000UL;


	/* Falling edge of PWGA_TOUTn detected. */
	while(!(INTC2.EIC163.UINT16&0x1000)) 
	{
	    /* Waiting for RFPWGA0 to set. */
	}
	INTC2.EIC163.UINT16                &= 0xEFFFU;                     /* clear INTPWGA0 interrupt request flag */


	/* Stop for PWMCLKm.
	PWBAnTT      - PWBAnTT Register
	b 7:b 4                   - Reserved set to 0
	b 3            PWBAnTT3   - Stop trigger bit for PWMCLK3                          - Unused. set to 0'b
	b 2            PWBAnTT2   - Stop trigger bit for PWMCLK2                          - Unused. set to 0'b
	b 1            PWBAnTT1   - Stop trigger bit for PWMCLK1                          - Unused. set to 0'b
	b 0            PWBAnTT0   - Stop trigger bit for PWMCLK0                          - Stops the output of PWMCLK0. */
	PWBA0.TT.UINT8                  = 0x01U;
	while( (PWBA0.TE.UINT8 & 0x01U) == 0x01U ) 
	{
	    /* Waiting for PWBA0TE to reset. */
	}


	/* Control operations of PWSA.
	PWSAnCTL     - PWSAnCTL Register
	b 7:b 6                   - Reserved set to 0
	b 0            PWSAnENBL  - Operation Permission Control                          - Operation is disabled. */
	PWSA0.CTL.UINT8                 = 0x00U;
}

/******************************************************************************
* Function Name: Pwm_Start
* Description  : Pwm启动
* Arguments    : None
* Return Value : None
******************************************************************************/
void Pwm_SetDuty(uint8 ch, uint32 Duty)
{
    (void)ch; //防止预编译警告

    if ( (PWGA22.RSF.UINT8 & 0x01U) == 0x00U )
    {
        /* Sets the setting condition for PWGA_TOUTn output.
        PWGAnCSDR    - PWM Output Set Condition Register
        b15:b12                   - Reserved set to 0
        b11:b 0        PWGAnCSDR  - Setting condition for PWM output. */
                                    /* PWM period = ( 1 / PWMCLK0 ) * (4095+1) = 0.0016384s (TRGOUT0) , (PWMCLK0 = 2.5MHz) */
                                    /* High Level = (PWGAnCRDR - PWGAnCSDR) * ( 1 /PWMCLK0) */
        PWGA22.CSDR.UINT16           = 0U;



        /* Sets the reset condition for PWGA_TOUTn output.
        PWGAnCRDR    - PWM Output Set Condition Register
        b15:b12                   - Reserved set to 0
        b11:b 0        PWGAnCRDR  - Reset condition for PWM output. */
        PWGA22.CRDR.UINT16 = Duty;

        /* Stop for PWMCLKm.
        PWGAnRDT     - Buffer Register Reload Trigger Register
        b7:b1                     - Reserved set to 0
        b0             PWGAnRDT   - Simultaneous Rewrite Request Trigger              - Triggers the simultaneous
                                                                                        rewrite request for the
                                                                                        compare registers. */
        PWGA22.RDT.UINT8 = 0x01U;
    }
}

/******************************************************************************
* Function Name: INTRLIN30UR2_IsrHandle
* Description  : PWGA22 status interrupt service routine
* Arguments    : None
* Return Value : None
******************************************************************************/
void INTPWGA22_IsrHandle(void)
{     

}    
