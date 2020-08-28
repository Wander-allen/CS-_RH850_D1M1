/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Port_PBcfg.c For Renesas Rh850 D1M1_V2 Series
Author: Steven
******************************************************************************/
#include "Pin_PBcfg.h"
#include "Pin_Define.h"


static const Port_GpioCfgType PortGpioCfg[] = 
{
    /* Channel   PMC_JPMC  PM_JPM  PIBC_JPIBC P_JP*/
    {  PORT_P0 ,  0x03C0,  0xFEBF,  0x0000,  0x0000  },
    {  PORT_P1 ,  0x0000,  0xFFFE,  0x0000,  0x0000  },
    {  PORT_P3 ,  0x0000,  0xFFFD,  0x0008,  0x0000  },
    {  PORT_P10,  0x0000,  0xF7FF,  0x0000,  0x0800  },
    {  PORT_P11,  0x0000,  0xFFF0,  0x0000,  0x0001  },
    {  PORT_P16,  0x0040,  0xF33F,  0x0008,  0x0000  },
    {  PORT_P17,  0x0000,  0xFDC0,  0x0000,  0x0000  },
    {  PORT_P21,  0x0000,  0xFFFF,  0x0000,  0x0000  },
    {  PORT_P22,  0x0000,  0xFFFF,  0x0000,  0x0000  },
    {  PORT_P42,  0x0000,  0xFFFF,  0x0000,  0x0000  },
    {  PORT_P43,  0x0000,  0xFFFF,  0x0000,  0x0000  },
    {  PORT_P44,  0x0000,  0xFFFF,  0x0000,  0x0000  },
    {  PORT_P45,  0x0000,  0xFFFF,  0x0000,  0x0000  },
    {JPORT_PJP0,  0x0000,  0xFFFF,  0x0000,  0x0000  }
};

static const Port_PpcrCfgType PortPpcrCfg[] = 
{
    /* PID        Pin.  PCRv */
    {  PORT_P0 ,  6,    0x00000003},  /* CAN1TX */
    {  PORT_P0 ,  7,    0x00000003},  /* CAN1RX */
    {  PORT_P0 ,  8,    0x00000000},  /* RLIN30TX */
    {  PORT_P0 ,  9,    0x00000000},  /* RLIN30RX */
    {  PORT_P3 ,  0,    0x00000000},  /* RIIC0SDA */
    {  PORT_P3 ,  1,    0x00000000},  /* RIIC0SCL */
    {  PORT_P16,  6,    0x00000001},  /* PWGA22O */
};

/* Port Configuration */
static const Port_ConfigType PortConfig = 
{
    PortGpioCfg,  /* GpioCfg */
    PortPpcrCfg,  /* PpcrCfg */
    sizeof(PortGpioCfg)/sizeof(PortGpioCfg[0]), /* GpioNum */
    sizeof(PortPpcrCfg)/sizeof(PortPpcrCfg[0]), /* PpcrNum */
};

const Port_ConfigType* const PortCfgPtr = &PortConfig;

