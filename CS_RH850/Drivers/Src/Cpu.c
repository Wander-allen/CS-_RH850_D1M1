/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Cpu.c 
Author: Wander 
******************************************************************************/

/******************************************************************************
Pragma directive
******************************************************************************/

/******************************************************************************
Includes
******************************************************************************/
#include "Std_Types.h"

/******************************************************************************
#Define Register
******************************************************************************/

/******************************************************************************
Global variables and functions
******************************************************************************/
extern void Cpu_Delay1US(void);
extern void Cpu_DelayUS(uint16 USTime);
extern void Cpu_DelayMS(uint16 MSTime);

/******************************************************************************
* Function Name: Cpu_Delay1US
* Description  : 延时1Us(实际测试2Us,10Us以上正常)
* Arguments    : None
* Return Value : None
******************************************************************************/
void Cpu_Delay1US(void)
{
    uint16 USTime = 51;
    
    while (USTime)
    {
        USTime--;
    }
}

/******************************************************************************
* Function Name: Cpu_DelayUS
* Description  : 延时USTime
* Arguments    : None
* Return Value : None
******************************************************************************/
void Cpu_DelayUS(uint16 USTime)
{
    while (USTime)
    {
        USTime--;
        Cpu_Delay1US();
    }
}

/******************************************************************************
* Function Name: Cpu_DelayMS
* Description  : 延时MSTime
* Arguments    : None
* Return Value : None
******************************************************************************/
void Cpu_DelayMS(uint16 MSTime)
{
    while (MSTime)
    {
        MSTime--;
        Cpu_DelayUS(1000);
    }
}