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

/******************************************************************************
#Define
******************************************************************************/

/******************************************************************************
Global variables and functions
******************************************************************************/

/******************************************************************************
* Function Name: Mcu_Init
* Description  : Mcu初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
void Mcu_Init(void)
{
    //Clock_Init();
}

/******************************************************************************
* Function Name: module_reset_release
* Description  : Mcu初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
void module_reset_release()
{
  /* deactivate reset for all modules */
  protected_write(SYS.PROTCMDMRST.UINT32,SYS.PROTSMRST.UINT32,SYS.MRSTC.UINT32,(0x00003fff)); 
}
