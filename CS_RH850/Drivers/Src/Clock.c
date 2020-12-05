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
#include "Mcu.h"
#include "Clock.h"

/******************************************************************************
#Define
******************************************************************************/
#define protected_write(preg,pstatus,reg,value)\
do{\
    (preg)=0xa5u;\
    (reg)=(value);\
    (reg)=~(value);\
    (reg)=(value);\
}while((pstatus)==1u)

/******************************************************************************
Global variables and functions
******************************************************************************/
static void Clock_OscInit(void);
static void Clock_GeneratorInit(void);
static void Clock_DomainInit(void);

/******************************************************************************
* Function Name: Clock_Init
* Description  : 时钟初始化
                start MainOSC(8 MHz) and PLL
                PLL0 = 480 MHz (PLL0CLK = 480 MHz)
                PLL1 = 480 MHz (PLL1CLK = 480 MHz)
                CLKFIX = 80 MHz
                CLKJIT = 80 MHz
                PLLFIXCLK = 480 MHz (PLL1CLK)
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
    protected_write(SYS.PROTCMD0.UINT32, SYS.PROTS0.UINT32, SYS.MOSCE.UINT32, 1);/* trigger enable (protected write) */
    while (SYS.MOSCS.BIT.MOSCCLKACT == 0) {}                    /* Wait until MainOsc active*/

    /* Configure the PLL0 clock generators 480MHz */
    SYS.PLL0C.BIT.NI = 0x3B;                                    /* Nr = (0x3B + 1) =  60 */
    SYS.PLL0C.BIT.M = 0;                                        /* mr = 1 */
    SYS.PLL0C.BIT.P = 0;                                        /* Pr = 1 */
    /* fPLL0= 480MHz fout = fin * (Nr + 1) / ((Mr +1) * (Pr + 1)) */
    protected_write(SYS.PROTCMD1.UINT32, SYS.PROTS1.UINT32, SYS.PLL0E.UINT32, 1);/* Start the PLL0 (protected write) */
    while (SYS.PLL0S.BIT.PLL0CLKACT == 0) {}                    /* Wait until PLL0 active */
    SYS.CKSC_IPLL0S_CTL.BIT.PLL0SSTP = 1;                       /* Enable the PLL0CLK clock*/
    while (SYS.CKSC_IPLL0S_ACT.BIT.PLL0SACT == 0) {}            /* Wait until PLL0CLK active */

    /* Configure the PLL1 clock generators 480MKz */
    SYS.PLL1C.BIT.NI = 0x3B;                                    /* Nr = (0x3B + 1) =  60 */
    SYS.PLL1C.BIT.M = 0;                                        /* mr = 1 */
    SYS.PLL1C.BIT.P = 0;                                        /* Pr = 1 */
    /* fPLL1= 480MHz fout = fin * (Nr + 1) / ((Mr +1) * (Pr + 1)) */
    protected_write(SYS.PROTCMD1.UINT32, SYS.PROTS1.UINT32, SYS.PLL1E.UINT32, 1);/* Start the PLL1 (protected write) */
    while (SYS.PLL1S.BIT.PLL1CLKACT == 0) {}                    /* Wait until PLL1 active */
    SYS.CKSC_IPLL1S_CTL.BIT.PLL1SSTP = 1;                       /* Enable the PLL1CLK clock*/
    while (SYS.CKSC_IPLL1S_ACT.BIT.PLL1SACT == 0) {}            /* Wait until PLL1CLK active */

    /* Configure the SubOsc */
    SYS.SOSCST.BIT.SOSCCLKST = 0x8000;                          /* Select correct SubOsc stabilization time */
    /* 0x8000 / frh = 4ms */
    protected_write(SYS.PROTCMD0.UINT32, SYS.PROTS0.UINT32, SYS.SOSCE.UINT32, 1);/* Start the SubOsc (protected write) */
    while (SYS.SOSCS.BIT.SOSCCLKACT == 0) {}                    /* Wait until SubOsc active */
}

/******************************************************************************
* Function Name: Clock_GeneratorInit
* Description  :
* Arguments    : None
* Return Value : None
******************************************************************************/
static void Clock_GeneratorInit(void)
{
    /* Set CPU clock divider to 4 */
    protected_write(SYS.PROTCMD1.UINT32, SYS.PROTS1.UINT32, SYS.CKSC_ICPUCLKD_CTL.UINT32, 3);
    /* divider 2 (protected write) */
    while (SYS.CKSC_ICPUCLKD_ACT.UINT32 != 3) {}                    /* Current active CPUCLKD clock divider */

    /* Set CPU clock to PLL1CLK / 4 (120MHz) */
    protected_write(SYS.PROTCMD1.UINT32, SYS.PROTS1.UINT32, SYS.CKSC_ICPUCLKS_CTL.UINT32, 3);
    /* PLL1CLK / 4 (protected write) */
    while (SYS.CKSC_ICPUCLKS_ACT.UINT32 != 3) {}                    /* Wait until Current active */

    /* Set CLKFIX clock divider to 6 */
    protected_write(SYS.PROTCMDD1.UINT32, SYS.PROTSD1.UINT32, SYS.CKSC_ICLKFIXS_CTL.UINT32, 1);
    /* divider 6 (protected write) */
    while (SYS.CKSC_ICLKFIXS_ACT.UINT32 != 1) {}                    /* Wait unit selected and active clock */

    /* Set CLKFIX clock to PLLFIXCLK/6, (PLLFIXCLK=PLL1CLK(480MHz) / 6 = 80MHz) */
    protected_write(SYS.PROTCMDD1.UINT32, SYS.PROTSD1.UINT32, SYS.CKSC_ICLKFIXS_CTL.UINT32, 1);
    /* PLLFIXCLK / 6 (protected write) */
    while (SYS.CKSC_ICLKFIXS_ACT.UINT32 != 1) {}                    /* Wait unit selected and active clock */


    /* Set CLKJIT clock divider to 6 */
    protected_write(SYS.PROTCMDD1.UINT32, SYS.PROTSD1.UINT32, SYS.CKDV_ICLKJITD_CTL.UINT32, 6);
    /* divider 6 (protected write) */
    while (SYS.CKDV_ICLKJITD_STAT.UINT32 != 3) {}                   /* Wait until CLKJIT active */

    /* Set CLKJIT clock to PLLFIXCLK/6, (PLL0CLK(480MHz) / 6 = 80MHz)  */
    protected_write(SYS.PROTCMDD1.UINT32, SYS.PROTSD1.UINT32, SYS.CKSC_ICLKJITS_CTL.UINT32, 1);
    /* PLLFIXCLK/6 (protected write) */
    while (SYS.CKSC_ICLKJITS_ACT.UINT32 != 1) {}                    /* Wait until Current active */
}

/******************************************************************************
* Function Name: Clock_OscInit
* Description  : 时钟初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
static void Clock_DomainInit(void)
{
    /* Set C_ISO_OSTM clock to C_ISO_CPUCLK / 4 = 30 MHz */
    protected_write(SYS.PROTCMDD1.UINT32, SYS.PROTSD1.UINT32, SYS.CKSC_IOSTMS_CTL.UINT32, 2);
    /* C_ISO_CPUCLK / 4 (protected write) */
    while (SYS.CKSC_IOSTMS_CTL.UINT32 != 2) {}                      /* Wait Until Current active RLINS source clock selection*/

    /* Set C_ISO_IRLINS clock to CLKJIT / 1 = 80 MHz */
    protected_write(SYS.PROTCMDD1.UINT32, SYS.PROTSD1.UINT32, SYS.CKSC_IRLINS_CTL.UINT32, 2);
    /* CLKJIT / 1 (protected write) */
    while (SYS.CKSC_IRLINS_ACT.UINT32 != 2) {}                      /* Wait Until Current active RLINS source clock selection*/

    /* Set C_ISO_TAUB01 clock to CLKFIX /1, (CLKFIX(80MHz) / 1 = 80MHz) */
    protected_write(SYS.PROTCMDD1.UINT32, SYS.PROTSD1.UINT32, SYS.CKSC_ITAUB01S_CTL.UINT32, 1);
    /* CLKJIT / 1 (protected write) */
    while (SYS.CKSC_ITAUB01S_ACT.UINT32 != 1) {}                    /* Wait until Current active C_ISO_TAUB01 */

    /* Set C_ISO_ADCE clock to CKLJIT /2 (40 MHz) */
    protected_write(SYS.PROTCMDD1.UINT32, SYS.PROTSD1.UINT32, SYS.CKSC_IADCED_CTL.UINT32, 1);
    /* CKLJIT /2 (protected write) */
    while (SYS.CKSC_IADCED_ACT.UINT32 != 1) {}                      /* Wait until Current active C_ISO_TAUB01  */

    /* Set C_AWO_WDTA clock to LS IntOsc fRL (240 kHz) / 128 */
    protected_write(SYS.PROTCMD0.UINT32, SYS.PROTS0.UINT32, SYS.CKSC_AWDTA0D_CTL.UINT32, 1);
    while (SYS.CKSC_AWDTA0D_ACT.UINT32 != 1) {}
}

