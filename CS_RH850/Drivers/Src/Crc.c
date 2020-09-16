/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Crc.c 
Author: Wander 
******************************************************************************/

/******************************************************************************
Includes
******************************************************************************/
#include "Std_Types.h"

/******************************************************************************
#Define Register
******************************************************************************/
#define DCRA_BASE       (0xFFF70000)
#define DCRA_CIN        (*(volatile uint32 *)(DCRA_BASE + 0x00))
#define DCRA_COUT       (*(volatile uint32 *)(DCRA_BASE + 0x04))
#define DCRA_CTL        (*(volatile uint8  *)(DCRA_BASE + 0x20))

/******************************************************************************
Global variables and functions
******************************************************************************/

/******************************************************************************
* Function Name: Crc_Init
* Description  : Crc初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
void Crc_Init(void)
{
    DCRA_CTL = 0x05;
    DCRA_COUT = 0xFFFFFFFF;
    DCRA_CIN = 0x0055;
}

/******************************************************************************
* Function Name: Crc_Init
* Description  : Crc初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
uint16 Crc_GetCalData(void)
{
    return DCRA_COUT;
}