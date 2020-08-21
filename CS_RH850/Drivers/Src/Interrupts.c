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
#include "Std_Types.h"
#include "ioDefine.h"

/******************************************************************************
#Define
******************************************************************************/


/******************************************************************************
Global variables and functions
******************************************************************************/
void INTRLIN30UR0( void );
void INTRLIN30UR1( void );
void INTRLIN30UR2( void );

uint16   dummy;

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
	INTC2.EIC83.UINT16 &= 0xEFFF;
}    

char buff[2048] = {0};
uint8 index = 0;

/* RLIN3 UART reception interrupt service routine */
#pragma interrupt INTRLIN30UR1( enable = false, channel = 82, callt = false, fpu = false )
void INTRLIN30UR1(void)
{  

    char rev;

    //	RLN32LUTDR = RLN32LURDR;
    INTC2.EIC82.UINT16 &= 0xEFFF;

    while ((RLN30.LST.UINT8 & 0x10) == 0x10)
    {
        /* Transmission is operated */
    }

    rev = RLN30.LURDR.BIT.URD;
    buff[index++] = rev;

    /*  the stop bit is being received. */
    if ((RLN30.LST.UINT8 & 0x20) == 0x20)
    {
        RLN30.LUWTDR.BIT.UWTD = rev;
    }
    else
    {
        RLN30.LUTDR.BIT.UTD = rev;
    }
}    

/* RLIN3 UART status interrupt service routine */
#pragma interrupt INTRLIN30UR2( enable = false, channel = 81, callt = false, fpu = false )
void INTRLIN30UR2(void)
{     
	if ( RLN30.LEST.UINT8 & 0x4CU )	/* Overrun error, Framing error, Parity error  */
	{                       
	    dummy            = RLN30.LEST.UINT8;        /* Clear UART reception data register          */
	}
	/* Clear error status
	RLN3nLEST  - UART Error Status Register
	b7                   - Reserved set to 0
	b6           UPER    - Parity Error Flag           - Clear the Parity Error Flag
	b5           IDMT    - ID Matching Flag            - Clear the ID Matching Flag
	b4           EXBT    - Expanded Bit Detection Flag - Clear the Expanded Bit Detection Flag
	b3           FER     - Framing Error Flag          - Clear the Framing Error Flag
	b2           OER     - Overrun Error Flag          - Clear the Overrun Error Flag
	b1                   - Reserved set to 0
	b0           BER     - Bit Error Flag              - Clear the Bit Error Flag */
	RLN30.LEST.UINT8 = 0x00U;

}    


