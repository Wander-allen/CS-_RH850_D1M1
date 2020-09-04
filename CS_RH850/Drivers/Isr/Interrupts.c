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
#include "Adc_Isr.h"
#include "Mcu_Isr.h"

/******************************************************************************
#Define
******************************************************************************/

/******************************************************************************
Global variables and functions
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

/* ADCE0 Scan group 1 interrupt (INTADCE0I1) service routine */
#pragma interrupt INTADCE0I1( enable = false, channel = 66, callt = false, fpu = false )
void INTADCE0I1(void)
{
    INTADCE0I1_IsrHandle();
}

/* WDTA0 75 % interrupt (INTWDTA0) service routine */
#pragma interrupt INTWDTA0( enable = false, channel = 0, callt = false, fpu = false )
void INTWDTA0(void)
{
    INTWDTA0_IsrHandle();
}

/* RSCAN Channel 0 to 2 RX FIFO interrupt(INTRCANGRECC) service routine */
#pragma interrupt INTRCANGRECC( enable = false, channel = 70, callt = false, fpu = false )
void INTRCANGRECC(void)
{
    INTRCANGRECC_IsrHandle();
}

/* RSCAN1 Channel 1 TX interrupt (INTRCAN1TRX) service routine */
#pragma interrupt INTRCAN1TRX( enable = false, channel = 120, callt = false, fpu = false )
void INTRCAN1TRX(void)
{
    INTRCAN1TRX_IsrHandle();
}



