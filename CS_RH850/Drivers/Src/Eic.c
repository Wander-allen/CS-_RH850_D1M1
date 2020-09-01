/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Eic.c EI Level Interrupt Control for RH850 D1M1
Author: Wander 
******************************************************************************/

/******************************************************************************
Pragma directive
******************************************************************************/

/******************************************************************************
Includes
******************************************************************************/
#include "Std_Types.h"
#include "Eic.h"


/******************************************************************************
#Define Register
******************************************************************************/
#define INT1_EICn(n)       (*(volatile uint16*)(0xFFFEEA00UL + (n) * 2))
#define INT2_EICn(n)       (*(volatile uint16*)(0xFFFFB040UL + (n) * 2))
#define PBG_FSGD0BPROT0    (*(volatile uint32*)(0xFFC4C000UL))

/******************************************************************************
Global variables and functions
******************************************************************************/

/******************************************************************************
* Function Name: Eic_Enable
* Description  : 中断使能
* Arguments    : Ch      :32-255
                 Method  :0:DIRECT_BRANCH  1:TABLE_REFERENCE
                 priority:0-15
* Return Value : None
******************************************************************************/
void Eic_Enable(uint8 Ch, Eic_MethodType Method, Eic_PriorityType priority)
{
    uint16 TmpEicValue = 0x0000;

    TmpEicValue = (((uint16)Method << 6) & 0x40) | ((uint16)priority & 0x0F);

    /* Interrupt Enable */
    if (Ch >= 32)
    {
        PBG_FSGD0BPROT0 = 0x07FFFFFF;
        INT2_EICn(Ch - 32) = TmpEicValue;
        return;
    }

    INT1_EICn(Ch) = TmpEicValue;
}

/******************************************************************************
* Function Name: Eic_Enable
* Description  : ADC初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
void Eic_Disable(uint8 Ch)
{
    /* Interrupt Disable */
    if (Ch >= 32)
    {
        INT2_EICn(Ch - 32) = 0x008F;
        return;
    }

    INT2_EICn(Ch) = 0x008F;
}