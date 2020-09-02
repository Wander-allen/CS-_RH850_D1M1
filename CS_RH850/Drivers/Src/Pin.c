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
#include "Pin_PBcfg.h"
#include "Pin.h"

/******************************************************************************
Rigister Struct
******************************************************************************/
/* PCRn 寄存器结构体定义  The small end format */
typedef union 
{
    uint32 Value;
    struct 
    {
        uint32 PFC      :1;
        uint32 PFCE     :1;
        uint32 PFCAE    :1;
        uint32 reserve1 :1;
        uint32 PM       :1;
        uint32 PIPC     :1;
        uint32 PMC      :1;
        uint32 reserve2 :1;

        uint32 PPR      :1;
        uint32 reserve3 :3;
        uint32 P        :1;
        uint32 reserve4 :3;

        uint32 PIBC     :1;
        uint32 PBDC     :1;
        uint32 PD       :1;
        uint32 PU       :1;
        uint32 PIS      :1;
        uint32 reserve5 :1;
        uint32 PISA     :1;
        uint32 reserve6 :1;

        uint32 PDSC     :1;
        uint32 reserve7 :3;
        uint32 PODC     :1;
        uint32 reserve8 :1;
        uint32 PINC     :1;
        uint32 reserve9 :1;
    };
}Port_PCRnType;
/******************************************************************************
Define Register(n : Group  m : Pin)
******************************************************************************/
#define    PORTU0_BASE      (0xFF618000)    /* Group n = 0 */
#define    PORTUn_BASE      (0xFF610000)    /* Group n > 0 */
#define    PORTO0_BASE      (0xFFC18000)    /* Group n = 0 */
#define    PORTOn_BASE      (0xFFC10000)    /* Group n > 0 */
#define    JPORTUn_Base     (0xFF620000)    /* Group JP0 */
#define    JPORTOn_Base     (0xFFC20000)    /* Group JP0 */

/* PCRn_m */
#define PORT_PCR0_m(m)       (*(volatile Port_PCRnType *)(PORTU0_BASE + 0x2000 + (m) * 4))
#define PORT_PCRn_m(n, m)    (*(volatile Port_PCRnType *)(PORTUn_BASE + 0x2000 + (n) * 0x40 + (m) * 4))
#define PORT_JPCR0(m)        (*(volatile Port_PCRnType *)(JPORTUn_Base + 0x2000 + (m) * 4))

/* PMCn */
#define PORT_PMC0            (*(volatile uint16 *)(PORTU0_BASE + 0x0014))
#define PORT_PMCn(n)         (*(volatile uint16 *)(PORTUn_BASE + 0x0014 + (n) * 0x40))
#define PORT_JPMC0           (*(volatile uint8 *)(JPORTUn_Base + 0x0014))

/* PMn */
#define PORT_PM0             (*(volatile uint16 *)(PORTU0_BASE + 0x0010))
#define PORT_PMn(n)          (*(volatile uint16 *)(PORTUn_BASE + 0x0010 + (n) * 0x40))
#define PORT_JPM0            (*(volatile uint16 *)(JPORTUn_Base + 0x0010))

/* PIBCn */
#define PORT_PIBC0           (*(volatile uint16 *)(PORTO0_BASE + 0x4000))
#define PORT_PIBCn(n)        (*(volatile uint16 *)(PORTOn_BASE + 0x4000 + (n) * 0x40))
#define PORT_JPIBC0          (*(volatile uint16 *)(JPORTOn_Base + 0x4000))

/* Pn */
#define PORT_P0              (*(volatile uint16 *)(PORTU0_BASE + 0x0000))
#define PORT_Pn(n)           (*(volatile uint16 *)(PORTUn_BASE + 0x0000 + (n) * 0x40))
#define PORT_JP0             (*(volatile uint16 *)(JPORTUn_Base + 0x0000))

/* PPRn */
#define PORT_PPR0              (*(volatile uint16 *)(PORTU0_BASE + 0x000C))
#define PORT_PPRn(n)           (*(volatile uint16 *)(PORTUn_BASE + 0x000C + (n) * 0x40))
#define PORT_JPPR0             (*(volatile uint16 *)(JPORTUn_Base + 0x000C))

/* PNOTn */
#define PORT_PNOT0             (*(volatile uint16 *)(PORTU0_BASE + 0x0008))
#define PORT_PNOTn(n)          (*(volatile uint16 *)(PORTUn_BASE + 0x0008 + (n) * 0x40))
#define PORT_JPNOT0            (*(volatile uint16 *)(JPORTUn_Base + 0x0008))

/******************************************************************************
Global variables and functions
******************************************************************************/
extern const Port_ConfigType* const PortCfgPtr;

/******************************************************************************
* Function Name: Port_Init
* Description  : 端口初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
void Port_Init(void)
{
    const Port_GpioCfgType * const GpioCfg = PortCfgPtr->GpioCfg;
    const uint8 GpioNum = PortCfgPtr->GpioNum;
    const Port_PpcrCfgType * const PpcrCfg = PortCfgPtr->PpcrCfg;
    const uint8 PpcrNum = PortCfgPtr->PpcrNum;
    uint8 i;

    /* 端口配置 */
    for (i = 0; i < GpioNum; i++)
    {
        if (GpioCfg[i].Channel == PORT_P0)
        {
            PORT_PMC0 = GpioCfg[i].PMC_JPMC;
            PORT_PM0  = GpioCfg[i].PM_JPM;
            PORT_PIBC0= GpioCfg[i].PIBC_JPIBC;
            PORT_P0   = GpioCfg[i].P_JP;
            continue;
        } 

        if (GpioCfg[i].Channel == JPORT_PJP0)
        {
            PORT_JPMC0 = (uint8)GpioCfg[i].PMC_JPMC;
            PORT_JPM0  = (uint8)GpioCfg[i].PM_JPM;
            PORT_JPIBC0= (uint8)GpioCfg[i].PIBC_JPIBC;
            PORT_JP0   = (uint8)GpioCfg[i].P_JP;
            continue;
        }

        PORT_PMCn(GpioCfg[i].Channel) = GpioCfg[i].PMC_JPMC;
        PORT_PMn(GpioCfg[i].Channel)  = GpioCfg[i].PM_JPM;
        PORT_PIBCn(GpioCfg[i].Channel)= GpioCfg[i].PIBC_JPIBC;
        PORT_Pn(GpioCfg[i].Channel)   = GpioCfg[i].P_JP;
    }

    /* PCRv 配置 */
    for (i = 0; i < PpcrNum; i++)
    {
        if (PpcrCfg[i].Channel == PORT_P0)
        {
            PORT_PCR0_m(PpcrCfg[i].Pin).Value |= PpcrCfg[i].PCRv;
            continue;
        }

        if (PpcrCfg[i].Channel == JPORT_PJP0)
        {
            PORT_JPCR0(PpcrCfg[i].Pin).Value |= PpcrCfg[i].PCRv;
            continue;
        }

        PORT_PCRn_m(PpcrCfg[i].Channel, PpcrCfg[i].Pin).Value |= PpcrCfg[i].PCRv;
    }
}

/******************************************************************************
* Function Name: Port_Read
* Description  : 
* Arguments    : None
* Return Value : None
******************************************************************************/
uint16 Port_Read(Port_ChannelType Channel)
{
    if (Channel == PORT_P0)
    {
        return PORT_PPR0;
    }

    if (Channel == JPORT_PJP0)
    {
        return PORT_JPPR0;
    }

    return PORT_PPRn(Channel);
}

/******************************************************************************
* Function Name: Port_Write
* Description  : 
* Arguments    : None
* Return Value : None
******************************************************************************/
void Port_Write(Port_ChannelType Channel, uint32 Levels)
{
    if (Channel == PORT_P0)
    {
        PORT_PPR0 = Levels;
    }

    if (Channel == JPORT_PJP0)
    {
        PORT_JPPR0 = Levels;
    }

    PORT_PPRn(Channel) = Levels;
}

/******************************************************************************
* Function Name: Port_ReadPin
* Description  : 
* Arguments    : None
* Return Value : None
******************************************************************************/
Std_StatusType Port_ReadPin(Port_ChannelType Channel, uint8 PinId)
{
    if (Channel == PORT_P0)
    {
        return PORT_PCR0_m(PinId).PPR;
    }

    if (Channel == JPORT_PJP0)
    {
        return PORT_JPCR0(PinId).PPR;
    }

    return PORT_PCRn_m(Channel, PinId).PPR;
}

/******************************************************************************
* Function Name: Port_WritePin
* Description  : 
* Arguments    : None
* Return Value : None
******************************************************************************/
void Port_WritePin(Port_ChannelType Channel, uint8 PinId, Std_StatusType Level)
{
    if (Channel == PORT_P0)
    {
        PORT_PCR0_m(PinId).P = Level;
    }

    if (Channel == JPORT_PJP0)
    {
        PORT_JPCR0(PinId).P = Level;
    }

    PORT_PCRn_m(Channel, PinId).P = Level;
}

/******************************************************************************
* Function Name: Port_FlipPin
* Description  : 
* Arguments    : None
* Return Value : None
******************************************************************************/
Std_StatusType Port_FlipPin(Port_ChannelType Channel, uint8 PinId)
{
    if (Channel == PORT_P0)
    {
        PORT_PNOT0 |= (uint16)1 << PinId;
        return PORT_PCR0_m(PinId).PPR;
    }

    if (Channel == JPORT_PJP0)
    {
        PORT_JPNOT0 |= (uint16)1 << PinId;
        return PORT_JPCR0(PinId).PPR;
    }

    PORT_PNOTn(Channel) |= (uint16)1 << PinId;
    return PORT_PCRn_m(Channel, PinId).PPR;
}

/******************************************************************************
* Function Name: Port_SetPinIO
* Description  : 
* Arguments    : None
* Return Value : None
******************************************************************************/
void Port_SetPinIO(Port_ChannelType Channel, uint8 PinId, Std_StatusType Status)
{
    if (Channel == PORT_P0)
    {
        PORT_PCR0_m(PinId).PM = Status;
    }

    if (Channel == JPORT_PJP0)
    {
        PORT_JPCR0(PinId).PM = Status;
    }

    PORT_PCRn_m(Channel, PinId).PM = Status;
}

/******************************************************************************
* Function Name: Port_GetPinIO
* Description  : 
* Arguments    : None
* Return Value : None
******************************************************************************/
Std_StatusType Port_GetPinIO(Port_ChannelType Channel, uint8 PinId)
{
    if (Channel == PORT_P0)
    {
        return PORT_PCR0_m(PinId).PM;
    }

    if (Channel == JPORT_PJP0)
    {
        return PORT_JPCR0(PinId).PM;
    }

    return PORT_PCRn_m(Channel, PinId).PM;
}

/******************************************************************************
* Function Name: Port_SetPinFun
* Description  : 
* Arguments    : None
* Return Value : None
******************************************************************************/
void Port_SetPinFun(Port_ChannelType Channel, uint8 PinId, uint32 Ppcr)
{
    if (Channel == PORT_P0)
    {
        PORT_PCR0_m(PinId).Value = Ppcr;
    }

    if (Channel == JPORT_PJP0)
    {
        PORT_JPCR0(PinId).Value = Ppcr;
    }

    PORT_PCRn_m(Channel, PinId).Value = Ppcr;
}
