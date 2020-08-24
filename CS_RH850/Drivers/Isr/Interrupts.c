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

/******************************************************************************
Includes
******************************************************************************/
#include "Std_Types.h"
#include "ioDefine.h"
#include "Uart_Isr.h"
#include "Taub_Isr.h"

/******************************************************************************
#Define
******************************************************************************/
#define INT1_EICn(n)       (*(volatile uint16*)(0xFFFEEA00UL + (n) * 2))
#define INT2_EICn(n)       (*(volatile uint16*)(0xFFFFB040UL + (n) * 2))
#define PBG_FSGD0BPROT0    (*(volatile uint32*)(FFC4C000UL))


/******************************************************************************
Global variables and functions
******************************************************************************/

/******************************************************************************
* Function Name: Clock_Init
* Description  : 时钟初始化 
* Arguments    : None
* Return Value : None
******************************************************************************/
/*
============================================================================
 Interrupt Service Routines - ISR
============================================================================
*/

/* RLIN3 UART transmission interrupt service routine */
#pragma interrupt INTRLIN30UR0( enable = false, channel = 83, callt = false, fpu = false )
void INTRLIN30UR0(void)
{    
	INTRLIN30UR0_IsrHandle();
}    


/* RLIN3 UART reception interrupt service routine */
#pragma interrupt INTRLIN30UR1( enable = false, channel = 82, callt = false, fpu = false )
void INTRLIN30UR1(void)
{  
    INTRLIN30UR1_IsrHandle();
}    

/* RLIN3 UART status interrupt service routine */
#pragma interrupt INTRLIN30UR2( enable = false, channel = 81, callt = false, fpu = false )
void INTRLIN30UR2(void)
{     
    INTRLIN30UR2_IsrHandle();
}    

/* RLIN3 UART status interrupt service routine */
#pragma interrupt INTTAUB0I0( enable = false, channel = 17, callt = false, fpu = false )
void INTTAUB0I0(void)
{
    INTTAUB0I0_IsrHandle();
}


