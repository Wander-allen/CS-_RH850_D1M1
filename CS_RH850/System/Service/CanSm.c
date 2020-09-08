/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : CanSm.c Can State Manager
Author: Wander 
******************************************************************************/

/******************************************************************************
Pragma directive
******************************************************************************/

/******************************************************************************
Includes
******************************************************************************/
// #include "ioDefine.h"
#include "Std_Types.h"
#include "CanSm_PBcfg.h"
#include "Can_PBcfg.h"
#include "Can.h"
#include <string.h>

/******************************************************************************
#Define
******************************************************************************/

/******************************************************************************
#Structures
******************************************************************************/
typedef struct 
{
    boolean InitFlag;
    uint8   L1L2Conut;
    uint16  l1L2Timer;
    uint8   BusOffCh;
}CanSm_Type;

/******************************************************************************
#Define Register
******************************************************************************/

/******************************************************************************
Global variables and functions
******************************************************************************/
extern const CanSm_ConfigType* const CanSmCfgPtr;
static CanSm_Type CanSm_Var;

/******************************************************************************
* Function Name: CanSm_Init
* Description  : 
* Arguments    : None
* Return Value : None
******************************************************************************/
void CanSm_Init(void)
{
    (void) memset (&CanSm_Var, 0x00, sizeof(CanSm_Type));

    CanSm_Var.InitFlag = TRUE;
}

/******************************************************************************
* Function Name: CanSm_BusoffCallback
* Description  : 
* Arguments    : None
* Return Value : None
******************************************************************************/
void CanSm_BusoffCallback(Can_ChannelType Channel)
{
    CanSm_Var.BusOffCh = Channel;
}

/******************************************************************************
* Function Name: CanSm_ModeCsCallback
* Description  : 
* Arguments    : None
* Return Value : None
******************************************************************************/
void CanSm_ModeCsCallback(Can_ChannelType Channel, Can_CsModeType CsMode)
{
    (void) Channel;
    (void) CsMode;
}

/******************************************************************************
* Function Name: CanSm_PollFunction
* Description  : 100ms周期
* Arguments    : None
* Return Value : None
******************************************************************************/
void CanSm_PollFunction(void)
{
    if (CanSm_Var.InitFlag != TRUE || !CanSm_Var.BusOffCh)
    {
        return;
    }

    if (Can_GetMode(CAN1) == CAN_CS_START)
    {
        CanSm_Var.BusOffCh = 0;
        return;
    }

    /*Bus Off Recovery */
    CanSm_Var.l1L2Timer++;

    if (   (CanSm_Var.l1L2Timer % CanSmCfgPtr->ChCfg->BorL1Time == 0) 
        && CanSm_Var.L1L2Conut < 5) 
    {
        CanSm_Var.L1L2Conut++;
        CanSm_Var.l1L2Timer = 0;
        Can_SetMode((Can_ChannelType)CanSm_Var.BusOffCh, CAN_CS_START);
        return;
    }

    if (   (CanSm_Var.l1L2Timer % CanSmCfgPtr->ChCfg->BorL2Time == 0) 
        && CanSm_Var.L1L2Conut >= 5) 
    {
        CanSm_Var.L1L2Conut = 5;
        CanSm_Var.l1L2Timer = 0;
        Can_SetMode((Can_ChannelType)CanSm_Var.BusOffCh, CAN_CS_START);
        return;
    }


}