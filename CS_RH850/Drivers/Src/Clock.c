/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Port.c 
Author: Wander 
******************************************************************************/

/******************************************************************************
Pragma directive
******************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/******************************************************************************
Includes
******************************************************************************/
#include "ioDefine.h"
#include "Clock.h"

/******************************************************************************
#Define
******************************************************************************/
/**
  * @brief  Unlock the Protected Rigister 
  * @param  CLUSTER：  protection command register
  * @param  RIGISTER： Write-Protected Registers 
  * @param  VALUE：    The value being written 
  */
#define UNLOCK_REGISTER(CLUSTER, RIGISTER, VALUE)   \
do{                                                 \
    (CLUSTER) = 0x000000A5;                         \
    (RIGISTER) = VALUE;                             \
    (RIGISTER) = ~((uint32)VALUE);                  \
    (RIGISTER) = VALUE;                             \
}while(0);                                          \

/******************************************************************************
Global variables and functions
******************************************************************************/
static void Clock_OscInit(void);
static void Clock_GeneratorInit(void);
static void Clock_DomainInit(void);

/******************************************************************************
* Function Name: Clock_Init
* Description  : 时钟初始化 
* Arguments    : None
* Return Value : None
******************************************************************************/
void Clock_Init(void)
{
    Clock_OscInit();
    Clock_GeneratorInit();
    Clock_DomainInit();
}

/******************************************************************************
* Function Name: Clock_OscInit
* Description  : 
* Arguments    : None
* Return Value : None
******************************************************************************/
static void Clock_OscInit(void)
{
    /* Configure the MainOsc 8Mhz*/
    SYS.MOSCC.BIT.MOSCAMPSEL = 1;                               /* Select the MainOsc frequency 8MHz*/
    SYS.MOSCST.BIT.MOSCCLKST = 0x8000;                          /* Select the correct MainOsc stabilization time */
                                                                /* 0x8000 / frh = 4ms */
    UNLOCK_REGISTER(SYS.PROTCMD0.UINT32, SYS.MOSCE.UINT32, 1);  /* Unlock the Protect Rigister and Start the MainOsc */
    while (SYS.MOSCS.BIT.MOSCCLKACT == 0){}                     /* Wait until MainOsc active*/

    /* Configure the PLL0 clock generators 480MHz */
    SYS.PLL0C.BIT.NI = 0x3B;                                    /* Nr = (0x3B + 1) =  60 */
    SYS.PLL0C.BIT.M = 0;                                        /* mr = 1 */
    SYS.PLL0C.BIT.P = 0;                                        /* Pr = 1 */
                                                                /* fPLL0= 480MHz fout = fin * (Nr + 1) / ((Mr +1) * (Pr + 1)) */
    UNLOCK_REGISTER(SYS.PROTCMD1.UINT32, SYS.PLL0E.UINT32, 1);  /* Unlock the Protect Rigister and Start the PLL0 */
    while (SYS.PLL0S.BIT.PLL0CLKACT == 0){}                     /* Wait until PLL0 active */
    SYS.CKSC_IPLL0S_CTL.BIT.PLL0SSTP = 1;                       /* Enable the PLL0CLK clock*/
    while (SYS.CKSC_IPLL0S_ACT.BIT.PLL0SACT == 0){}             /* Wait until PLL0CLK active */

    /* Configure the PLL1 clock generators 480MKz */
    SYS.PLL1C.BIT.NI = 0x3B;                                    /* Nr = (0x3B + 1) =  60 */
    SYS.PLL1C.BIT.M = 0;                                        /* mr = 1 */
    SYS.PLL1C.BIT.P = 0;                                        /* Pr = 1 */ 
                                                                /* fPLL1= 480MHz fout = fin * (Nr + 1) / ((Mr +1) * (Pr + 1)) */

    UNLOCK_REGISTER(SYS.PROTCMD1.UINT32, SYS.PLL1E.UINT32, 1);  /* Unlock the Protect Rigister and Start the PLL1 */
    while (SYS.PLL1S.BIT.PLL1CLKACT == 0){}                     /* Wait until PLL1 active */
    SYS.CKSC_IPLL1S_CTL.BIT.PLL1SSTP = 1;                       /* Enable the PLL1CLK clock*/
    while (SYS.CKSC_IPLL1S_ACT.BIT.PLL1SACT == 0){}             /* Wait until PLL1CLK active */

    /* Configure the SubOsc */
    SYS.SOSCST.BIT.SOSCCLKST = 0x8000;                          /* Select correct SubOsc stabilization time */
                                                                /* 0x8000 / frh = 4ms */
    UNLOCK_REGISTER(SYS.PROTCMD0.UINT32, SYS.SOSCE.UINT32, 1);  /* Unlock the Protect Rigister and Start the PLL1 */
    while (SYS.SOSCS.BIT.SOSCCLKACT == 0){}                     /* Wait until SubOsc active */
}

/******************************************************************************
* Function Name: Clock_OscInit
* Description  : 
* Arguments    : None
* Return Value : None
******************************************************************************/
static void Clock_GeneratorInit(void)
{
    /* Configure the Clock divider for C_ISO_CPUCLK, divider /4 */
    UNLOCK_REGISTER(SYS.PROTCMD1.UINT32, SYS.CKSC_ICPUCLKD_CTL.UINT32, 3);          /* Unlock the Protect Rigister */
                                                                                    /* clock selection for Clock divider setting for C_ISO_CPUCLK */
    while (SYS.CKSC_ICPUCLKD_ACT.UINT32 != 3){}                                     /* Current active CPUCLKD clock divider */

    /* Configure the C_ISO_CPUCLK to PLL0CLK 120MHz*/
    UNLOCK_REGISTER(SYS.PROTCMD1.UINT32, SYS.CKSC_ICPUCLKS_CTL.UINT32, 3);          /* Unlock the Protect Rigister */
                                                                                    /* Source clock selection for C_ISO_CPUCLK  */
    while (SYS.CKSC_ICPUCLKS_ACT.UINT32 != 3){}                                     /* Wait until Current active CPUCLKS source clock selection */


    /* Configure the Clock divider for CLKFIX, divider/6 */
    UNLOCK_REGISTER(SYS.PROTCMDD1.UINT32, SYS.CKSC_ICLKFIXS_CTL.UINT32, 1);         /* Unlock the Protect Rigister */
    while (SYS.CKSC_ICLKFIXS_ACT.UINT32 != 1){}                                     /* Wait unit selected and active clock */

    /* Configure the CLKFIX to PLLFIXCLK/6, (PLLFIXCLK=PLL1CLK(480MHz) / 6 = 80MHz) */
    UNLOCK_REGISTER(SYS.PROTCMDD1.UINT32, SYS.CKSC_ICLKFIXS_CTL.UINT32 , 1);        /* Unlock the Protect Rigister */
    while (SYS.CKSC_ICLKFIXS_ACT.UINT32 != 1){}                                     /* Wait unit selected and active clock */


    /* Configure the Clock divider for CLKJIT, divider/6 */
    UNLOCK_REGISTER(SYS.PROTCMDD1.UINT32, SYS.CKDV_ICLKJITD_CTL.UINT32, 6);         /* Unlock the Protect Rigister */
                                                                                    /* clock selection for Clock divider setting for CLKJIT */
    while (SYS.CKDV_ICLKJITD_STAT.UINT32 != 3){}                                    /* Wait until CLKJIT active */

    /* Configure the CLKFIX to PLLFIXCLK/6, (PLL0CLK(480MHz) / 6 = 80MHz) */
    UNLOCK_REGISTER(SYS.PROTCMDD1.UINT32, SYS.CKSC_ICLKJITS_CTL.UINT32, 1);         /* Unlock the Protect Rigister */
                                                                                    /* Source clock selection for CLKJIT CKDV_ICLKJITD_CTL */
    while (SYS.CKSC_ICLKJITS_ACT.UINT32 != 1){}                                     /* Wait until Current active CLKJITS source clock selection */


}

/******************************************************************************
* Function Name: Clock_OscInit
* Description  : 时钟初始化 
* Arguments    : None
* Return Value : None
******************************************************************************/
static void Clock_DomainInit(void)
{
    /* Configure the C_ISO_OSTM  C_ISO_CPUCLK / 4 = 30 MHz*/
    UNLOCK_REGISTER(SYS.PROTCMDD1.UINT32, SYS.CKSC_IOSTMS_CTL.UINT32, 2);   /* Unlock the Protect Rigister */
                                                                            /* clock selection for Clock divider setting*/
    while (SYS.CKSC_IOSTMS_CTL.UINT32 != 2){}                               /* Wait Until Current active RLINS source clock selection*/


    /* Configure the C_ISO_RLIN  CLKJIT / 1 = 80 MHz*/
    UNLOCK_REGISTER(SYS.PROTCMDD1.UINT32, SYS.CKSC_IRLINS_CTL.UINT32, 2);   /* Unlock the Protect Rigister */
                                                                            /* clock selection for Clock divider setting*/
    while (SYS.CKSC_IRLINS_ACT.UINT32 != 2){}                               /* Wait Until Current active RLINS source clock selection*/
}

