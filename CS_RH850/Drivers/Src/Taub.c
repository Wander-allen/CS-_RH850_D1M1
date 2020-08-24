/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Taub.c  Timer Array Unit B
Author: Wander 
******************************************************************************/

/******************************************************************************
Pragma directive
******************************************************************************/

/******************************************************************************
Includes
******************************************************************************/
#include "ioDefine.h"
#include "Taub_PBcfg.h"



/******************************************************************************
#Define
******************************************************************************/

/******************************************************************************
Global variables and functions
******************************************************************************/
extern const Taub_ConfigType* const TaubCfgPtr;

/******************************************************************************
* Function Name: Taub_Init
* Description  : Taub初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
void Taub_Init(void)
{
    TAUB0.TPS.UINT16 = 0x0007;          /* specify clock frequency of CK0...CK3  (CK0 -> 80 MHz / (2 ^ 7) = 62KHz) */
    TAUB0.CMOR0.UINT16 = 0x0000;        /* interval timer mode */
    //TAUB0.CDR0 = 65500;                 /* compare register in interval timer mode (625KHz / 625 = 1K Hz) */
    TAUB0.CDR0 = TaubCfgPtr->TimeCfg->CDRv;
    TAUB0.TS.UINT16 = 0x0001;           /* start channel 0 */
    INTC1.EIC17.UINT16 =0x0046;         /* demask timer TAUB0 chanel 0 interrupt and enable reference table jump */
}

/******************************************************************************
* Function Name: Taub_Init
* Description  : Taub初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
void Taub_Start(void)
{
    TAUB0.TS.UINT16 = 0x0001;           /* start channel 0 */
    INTC1.EIC17.UINT16 =0x0047;         /* demask timer TAUB0 chanel 0 interrupt and enable reference table jump method */
}

/******************************************************************************
* Function Name: Taub_Init
* Description  : Taub初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
void Taub_Stop(void)
{
    TAUB0.TS.UINT16 = 0x0001;           /* stop channel 0 */
    INTC1.EIC17.UINT16 =0xEFFFF;        /* mask timer TAUB0 chanel 0 interrupt and enable reference table jump method */
}

/******************************************************************************
* Function Name: INTRLIN30UR2_IsrHandle
* Description  : RLIN3 UART status interrupt service routine
* Arguments    : None
* Return Value : None
******************************************************************************/
void INTTAUB0I0_IsrHandle(void)
{
    if ((TaubCfgPtr->TimeCfg->TickCallback) != NULL)
    {
        (TaubCfgPtr->TimeCfg->TickCallback)();
    }

}