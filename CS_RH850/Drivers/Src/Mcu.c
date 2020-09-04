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
#include "Pin.h"

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
Rigister Struct
******************************************************************************/
typedef struct 
{                                                        /* Module           */
    uint8 WDTE;                                          /* WDTE             */
    uint8 dummy855[3];                                   /* Reserved         */
    uint8 EVAC;                                          /* EVAC             */
    uint8 dummy856[3];                                   /* Reserved         */
    uint8 REF;                                           /* REF              */
    uint8 dummy857[3];                                   /* Reserved         */
    uint8 MD;                                            /* MD               */
}WDTAn_Type;

/******************************************************************************
#Define Register
******************************************************************************/
/* General reset flags registers */
#define SYS_RESF                        (*(volatile uint32 *)0xFFF80760)
#define SYS_RESFC                       (*(volatile uint32 *)0xFFF80768)
#define SYS_RESFR                       (*(volatile uint32 *)0xFFF80860)
#define SYS_RESFCR                      (*(volatile uint32 *)0xFFF80868)

/* Software reset control registers */
#define SYS_SWRESA                      (*(volatile uint32 *)0xFFF80A04)
#define SYS_MRSTC                       (*(volatile uint32 *)0xFFF8F400)

/* Isolated-Area reset control register*/
#define SYS_PWRGD_CNT                   (*(volatile uint32 *)0xFFF8F500)

/* Write protection registers */
#define SYS_PROTCMD0                    (*(volatile uint32 *)0xFFF80000)
#define SYS_PROTS0                      (*(volatile uint32 *)0xFFF80004)
#define SYS_PROTCMD1                    (*(volatile uint32 *)0xFFF88000)
#define SYS_PROTS1                      (*(volatile uint32 *)0xFFF88004)
#define SYS_PROTCMDD1                   (*(volatile uint32 *)0xFFF87000)
#define SYS_PROTSD1                     (*(volatile uint32 *)0xFFF87004)
#define SYS_PROTCMDMRST                 (*(volatile uint32 *)0xFFF8F480)
#define SYS_PROTSMRST                   (*(volatile uint32 *)0xFFF8F484)
#define SYS_PROTCMDPWRGD                (*(volatile uint32 *)0xFFF8F580)
#define SYS_PROTSPWRGD                  (*(volatile uint32 *)0xFFF8F584)

/* Stand-by Controller Registers */
#define SYS_STBC0PSC                    (*(volatile uint32 *)0xFFF80100)
#define SYS_WUF0                        (*(volatile uint32 *)0xFFF80400)
#define SYS_WUFMSK0                     (*(volatile uint32 *)0xFFF80404)
#define SYS_WUFC0                       (*(volatile uint32 *)0xFFF80408)
#define SYS_IOHOLD                      (*(volatile uint32 *)0xFFF80B00)

/* WDTAn registers */
#define WDTA0_BASE                      ((uint32)0xFFED0000)
#define WDTA1_BASE                      ((uint32)0xFFED1000)
#define WDTA0                           (*(volatile WDTAn_Type *)WDTA0_BASE)

/* EI Level Interrupt Control Registers */
#define INT1_EICn(n)       (*(volatile uint16*)(0xFFFEEA00UL + (n) * 2))
#define INT2_EICn(n)       (*(volatile uint16*)(0xFFFFB040UL + (n - 32) * 2))
#define PBG_FSGD0BPROT0    (*(volatile uint32*)(0xFFC4C000UL))

/******************************************************************************
Global variables and functions
******************************************************************************/
static void Mcu_ModuleReset(void);
static void Mcu_CheckResetFactor( void );
static void Wdta_Init(void);

/******************************************************************************
* Function Name: Mcu_Init
* Description  : Mcu初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
void Mcu_Init(void)
{
    Mcu_CheckResetFactor();
    Mcu_ModuleReset();
    Clock_Init();
    Wdta_Init();
}

/******************************************************************************
* Function Name: Mcu_SoftReset
* Description  : MCU generate a software reset SWRES. 
* Arguments    : None
* Return Value : None
******************************************************************************/
void Mcu_SoftReset(void)
{
    /* Generate software reset SWRES */
    protected_write(SYS_PROTCMD0, SYS_PROTS0, SYS_SWRESA, 1); 
}

/*******************************************cu*********************************
* Function Name: Mcu_ModuleReset
* Description  : Mcug generate separate resets for various modules
* Arguments    : None
* Return Value : None
******************************************************************************/
static void Mcu_ModuleReset(void)
{
    /* deactivate reset for all modules */
    protected_write(SYS_PROTCMDMRST, SYS_PROTSMRST, SYS_MRSTC, (0x00003fff)); 
}

/******************************************************************************
* Function Name: Mcu_EicEnable
* Description  : 中断使能
* Arguments    : Ch      :32-255
                 Method  :0:DIRECT_BRANCH  1:TABLE_REFERENCE
                 priority:0-15
* Return Value : None
******************************************************************************/
void Mcu_EicEnable(uint8 Ch, Eic_MethodType Method, Eic_PriorityType priority)
{
    uint16 TmpEicValue = 0x0000;

    TmpEicValue = (((uint16)Method << 6) & 0x40) | ((uint16)priority & 0x0F);

    /* Interrupt Enable */
    if (Ch >= 32)
    {
        PBG_FSGD0BPROT0 = 0x07FFFFFF;
        INT2_EICn(Ch) = TmpEicValue;
        return;
    }

    INT1_EICn(Ch) = TmpEicValue;
}

/******************************************************************************
* Function Name: Mcu_EicDisable
* Description  : ADC初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
void Mcu_EicDisable(uint8 Ch)
{
    /* Interrupt Disable */
    if (Ch >= 32)
    {
        INT2_EICn(Ch - 32) = 0x008F;
        return;
    }

    INT2_EICn(Ch) = 0x008F;
}

/******************************************************************************
* Function Name: Wdta_Init
* Description  : Wdta初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
static void Wdta_Init(void)
{
    /* Set a mode of WDT */
    WDTA0.MD = 0x3F;

    /* Set interrupt flags */
    INT1_EICn(0) = 0x0047;

    /*WDTA0 start */
    WDTA0.WDTE = 0xAC;
}

/******************************************************************************
* Function Name: Wdta_Init
* Description  : Wdta重新计时
* Arguments    : None
* Return Value : None
******************************************************************************/
void Wdta_Clear(void)
{
    WDTA0.WDTE = 0xAC;                  /* start & clear */
}

/******************************************************************************
* Function Name: INTWDTA0_IsrHandle
* Description  : WDTA0 75 % interrupt service routine
* Arguments    : None
* Return Value : None
******************************************************************************/
void INTWDTA0_IsrHandle(void)
{
    Mcu_FeedDog();
}

/******************************************************************************
* Function Name: Mcu_GoDeepStop
* Description  : McuDeepStop模式
* Arguments    : None
* Return Value : None
******************************************************************************/
void Mcu_GoDeepStop(void)
{
    /* Stop all the peripheral functions to stop clock supply. */
        /* Unused by the sample program. */

    /* set the IO buffer used to hold state*/
    // protected_write(SYSPROTCMD0, SYSPROTS0, SYSIOHOLD, 0x007f);
    protected_write(SYS_PROTCMD0, SYS_PROTS0, SYS_IOHOLD, 0x007f);

    /* Interrupt disable */
    __DI();


    /* Set interrupt flags */
    // INTC1EIC0 &= 0xEF7F; 		/*(ICxxx.RFxxx = 0)*/
    // 							/*Unmask the interrupt of wake-up factor (ICxxx.MKxxx = 0).*/
    INT1_EICn(0) &= 0xEF7F;

    /* Clear all the wakeup factor
    WUFC0     - Wake-Up Factor Registers
    b31:b0      WUFy         - Indicates the generation of a wake-up event.  */
    // SYSWUFC0                    = 0xFFFFFFFFUL;
    SYS_WUF0                    = 0xFFFFFFFFUL;


    /* Masked the interrupt of the unused wakeup factor, and Unmasked the interrupt of the wakeup factor.
    WUFMSK0   - Wake-Up Factor Mask Registers
    b31:b0      WUFMSKy      - Enables/disables a wake-up event. */
    // SYSWUFMSK0                = 0xFFFFEFFFUL;        /* Wakeup factor 12 (Deep STOP   ¨ RUN )   : INTWDTA0  */
    SYS_WUFMSK0                = 0xFFFFEFFFUL;

    /*	PLL unused in this sample, so do not need the processes below*/
    /*
    protected_write(SYSPROTCMD1, SYSPROTS1, SYSPLL0E, 0x00000002);
    protected_write(SYSPROTCMD1, SYSPROTS1, SYSPLL1E, 0x00000002);
    */

    /* clear RESF and RESFR*/
    // SYSRESFC            = SYSRESF;
    // SYSRESFCR           = SYSRESFR;
    SYS_RESFC            = SYS_RESF;
    SYS_RESFCR           = SYS_RESFR;

    /* Shift to DEEPSTOP mode
    STBC0PSC  - Power Save Control Register
    b31:b2                   - Reserved set to 0
    b 1         STBC0DISTRG  - DEEPSTOP mode is entered. Set to 1
    b 0                      - Reserved set to 0 */

    protected_write(SYS_PROTCMD0, SYS_PROTS0, SYS_STBC0PSC, 0x00000002);

    while ( SYS_STBC0PSC != 0x00000002 )
    {
        /* Waiting for shift to DEEPSTOP mode. */
    }

    while ( 1U )
    {
        /* Waiting for shift to DEEPSTOP mode. */
    }
}

/******************************************************************************
* Function Name : static void Mcu_CheckResetFactor(void)
* Description   : This function check the reset factor.
* Argument      : none
* Return Value  : none
******************************************************************************/
static void Mcu_CheckResetFactor(void)
{
    uint32  reg_resf_value;
    uint32  reg_resfr_value;

    /* Read reset factor */
    reg_resf_value        = SYS_RESF;
    reg_resfr_value       = SYS_RESFR;

    /* Clear reset factor */
    SYS_RESFC                 = reg_resf_value;
    SYS_RESFCR                = reg_resfr_value;

    if ( reg_resf_value == reg_resfr_value )
    {
        if ( reg_resf_value & 0x00000400UL )        /* DEEPSTOP reset  (ISORES)  */
        {
            /* Set the port of the ISO domain again. */
                /* Unused by the sample program. */


            /* Set the peripheral function of the ISO domain again. */
                /* Unused by the sample program. */


            /* Release a keeping state of the input and output terminal.
            IOHOLD  - I/O Buffer Hold Control Register
            b31:b1            - Reserved set to 0
            b 0       IOHOLD  - hold state of the I/O buffer in DEEPSTOP mode. Set to 0 */
            protected_write(SYS_PROTCMD0,SYS_PROTS0,SYS_IOHOLD,0x00);/* Protection release the IOHOLD register.    */		

            /* Check wakeup factor 1 (INTWDTA0)    */
            if ( (SYS_WUF0 & (~SYS_WUFMSK0)) == 0x00001000UL )
            {
                INT1_EICn(0) = 0x1047;					/*set the wake-up factor interrupt flag*/
                __EI();                               /* enable interrupts globally */
                /* Disable by the detection of wakeup factor 1.                     */
                SYS_WUFMSK0     = 0xFFFFFFFFUL;           /* Disable wakeup factor 1  */
                SYS_WUFC0         = 0xFFFFFFFFUL;           /* Clear wakeup factor 1    */
            }
            else
            {
                /* Do Nothing */
            }
        }
        if( reg_resf_value & 0x00000002UL )		//WDTA0 RESET
        {
        }
    }
    else
    {
        /* Error */
    }
}


