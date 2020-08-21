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
#include "ioDefine.h"
#include "Uart.h"

/******************************************************************************
#Define
******************************************************************************/
#define RLIN3n_
/******************************************************************************
Global variables and functions
******************************************************************************/


/******************************************************************************
* Function Name: Uart_Init
* Description  : Uart初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
void Uart_Init(void)
{
    /* mask the interrupt */
    PBG.FSGD0BPROT0.UINT32 = 0x07FFFFFF; /* INTC2 Protect unlock register */
    INTC2.EIC81.UINT16 = 0x0080; /*  Interrupt processing is disabled */
    INTC2.EIC82.UINT16 = 0x0080; /*  Interrupt processing is disabled */
    INTC2.EIC83.UINT16 = 0x0080; /*  Interrupt processing is disabled */

    /* Choose the shift to a reset mode.
    RLN3nLCUC      - UART Control Register
    b7:b1                      - Reserved set to 0
    b0               OM0       - LIN Reset - LIN reset mode is caused */
    RLN30.LCUC.UINT8 = 0x00U;
    while ( (RLN30.LCUC.UINT8 & 0x01U) != 0x00U ) {
    /* Wait for LIN reset mode. */
    }

    /* Select the UART interface mode.
    RLN3nLMD       - UART Mode Register
    b7:b6                      - Reserved set to 0
    b5               LRDNFS    - LIN Reception Data Noise Filtering Disable - Noise filter is enabled
    b4:b2                      - Reserved set to 0
    b1:b0            LMD       - LIN/UART Mode Select                       - UART mode */
    RLN30.LMD.UINT8 = 0x01U;

    /* Select the bit sampling count and prescaler clock.
    RLN3nLWBR      - LIN Wake-Up Baud Rate Select Register
    b7:b4            NSPB      - Bit Sampling Count Select  - 16 sampling
    b3:b1            LPRS      - Prescaler Clock Select     - 1/1
    b0                         - Reserved set to 0 */
    RLN30.LWBR.UINT8 = 0xF0U;

    /* Set the baud rate prescaler
    RLN3nLBRP01    - UART Baud Rate Prescaler 01 Reg
    b15:b0           BRP       - The formula for baud rate is described below.
                                Baud rate for UART
                                = { Frequency of LIN communication clock source} * (RLN3nLWBR.LPRS[2:0] selection clock)
                                    / (RLN3nLBRP01 + 1) / the number of selected NSPB[3:0] [bps]
                                = 80MHz * ( 1 / 1 ) / ( 42 + 1 ) / 16 = 11,5200(11,6279)  */
    RLN30.LBRP01.UINT16 = 42U;

    /* Enables or disables detection of the framing error , overrun error and bit error.
    RLN3nLEDE      - UART Error Detection Enable Register
    b7:b4                      - Reserved set to 0
    b3               FERE      - Framing Error Detection Enable - Enables framing error detection
    b2               OERE      - Overrun Error Detection Enable - Enables overrun error detection
    b1                         - Reserved set to 0
    b0               BERE      - Bit Error Detection Enable     - Enables bit error detection */
    RLN30.LEDE.UINT8                 = 0x0CU;

    /* Enables or disables detection of the framing error , overrun error and bit error.
    RLN3nLBFC      - UART Configuration Register
    b7                         - Reserved set to 0
    b6               UTPS      - UART Output Polarity Switch       - Transmit data normal output
    b5               URPS      - UART Input Polarity Switch        - Reception data normal output
    b4:b3            UPS       - UART Parity Select                - Even Parity		no parity
    b2               USBLS     - UART Stop Bit length Select       - Stop bit:1 bit
    b1               UBOS      - UART Transfer Format Order Select - LSB First
    b0               UBLS      - UART Character Length Select      - UART 8 bits communication */
    RLN30.LBFC.UINT8                 = 0x00U;

    /*RLN3nLUOR1:	UART Option Register 1
    b7:b5			-Reserved to 0
    b4		UECD	- Expansion Bit Comparison Disable	set to 0, disable	
    b3		UTIGTS	- Transmission Interrupt Generation Timing Select	set to 1,Transmission interrupt is generated at the completion of transmission.
    b2		UEBDCE	- Expansion Bit Data Comparison Enable
    b1		UEBDL	- Expansion Bit Detection Level Select
    b0		UEBE	- Expansion Bit Enable	*/ 
    RLN30.LUOR1.UINT8	= 0x08U;

    /* Choose the cancellation of the reset mode.
    RLN3nLCUC      - UART Control Register
    b7:b1                      - Reserved set to 0
    b0               OM0       - LIN Reset - LIN reset mode is canceled */
    RLN30.LCUC.UINT8 = 0x01U;
    while ( (RLN30.LMST.UINT8 & 0x01U) != 0x01U ) {
    /* Wait for cancellation of the LIN reset mode. */
    }

    /* Set the interrupt flags */
    INTC2.EIC81.UINT16	=	0x0047;
    INTC2.EIC82.UINT16	=	0x0047;
    INTC2.EIC83.UINT16	=	0x0047;

    /* Enables reception and transmission
    RLN3nLUOER     - UART Operation Enable Register
    b7:b2                      - Reserved set to 0
    b1               UROE      - Reception Enable     - Enables reception
    b0               UTOE      - Transmission Enable  - Enables transmission */
    RLN30.LUOER.UINT8 	= 	0x03U;
}

/******************************************************************************
* Function Name: Uart_DeInit
* Description  : Uart取消初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
void Uart_DeInit(void)
{

}

/******************************************************************************
* Function Name: Uart_write
* Description  : Uart写一个字符
* Arguments    : None
* Return Value : None
******************************************************************************/
void Uart_transmit_char(char send)
{
    while ((RLN30.LST.UINT8 & 0x10) == 0x10)
    {
        /* Transmission is operated */
    }

    /*  the stop bit is being received. */
    if ((RLN30.LST.UINT8 & 0x20) == 0x20)
    {
        RLN30.LUWTDR.BIT.UWTD = send;
    }
    else
    {
        RLN30.LUTDR.BIT.UTD = send;
    }
}

/******************************************************************************
* Function Name: Uart_write
* Description  : Uart写一个字符串
* Arguments    : None
* Return Value : None
******************************************************************************/
void Uart_transmit_string(char data_string[])
{
    uint32 i = 0;

    while (data_string[i] != '\0')
    {
        Uart_transmit_char(data_string[i]);
        i++;
    }
}

/******************************************************************************
* Function Name: Uart_write
* Description  : Uart写n个字节
* Arguments    : None
* Return Value : None
******************************************************************************/
void Uart_transmit_n_size(char data_string[], uint16 size)
{
    uint32 i = 0;

    for (i = 0; i < size; i++)
    {
        Uart_transmit_char(data_string[i]);
    }
}

