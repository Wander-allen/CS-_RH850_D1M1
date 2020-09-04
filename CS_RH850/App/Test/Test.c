﻿/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : EcuM.c      ECU management module
Author: Wander 
******************************************************************************/

/******************************************************************************
                                    头文件
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "Uart.h"
//#include "rscan.h"
#include "Can.h"
#include "Pin.h"
#include "Pwm.h"
#include "Adc.h"
#include "Mcu.h"

/******************************************************************************
                                    局部宏方法
******************************************************************************/

/******************************************************************************
                                局部常量定义&类型定义
******************************************************************************/
#define TEST 1

/******************************************************************************
                                    局部变量定义
******************************************************************************/
unsigned long ul_interrupt_counter;     /* interrupt occurences counter */
/* Create Can_FrameType for send and receive data */
Can_FrameType CAN_Trans_Data={
  //CiTBpA
  0x18,
  0,
  0,
  0,        

  //CiTBpB
  0x0000,                            
  0x000,                            
  0x8,    

  {
    0x12,                            //DB0
    0x34,                            //DB1
    0x56,                            //DB2
    0x78,                            //DB3
    //CiTBpD
    0x87,                            //DB4
    0x65,                            //DB5
    0x43,                            //DB6
    0x21                             //DB7
  }
};

/******************************************************************************
* Function Name: Test_Init
* Description  : Mcu初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
void Test_Init(void)
{
    Uart_transmit_string("hello world\r\n");
    Uart_transmit_string("Test_Init Success\r\n");
    
}


/******************************************************************************
* Function Name: Can_Test
* Description  : Can模块测试
* Arguments    : None
* Return Value : None
******************************************************************************/
void Can_Test(void)
{

    Can_ReadRxBuffer(&CANRecData);
    if(CANRecData.DB[0]==0x01)
    {
        CANRecData.DB[0]=0x0;
    }

  ul_interrupt_counter++;               /* count interrupt occurences */
  if(ul_interrupt_counter == 9)
  {
    ul_interrupt_counter=9;
    //PORT_ISOPNOT16=0x02u;                 /* toggle port P16.1 (LED26 on main board) */
    if(CAN_Trans_Data.ID<0xFF)
      CAN_Trans_Data.ID++;
    else
      CAN_Trans_Data.ID=0x01;

#if 0
    if(CAN_Trans_Data.DB[0]<0xFF)
      CAN_Trans_Data.DB[0]++;       /* change DB0 (first data byte send) */
    else
#else
      CAN_Trans_Data.DB[0]=0x01;    /* always send "0x01" as DB0 (first data byte) */
#endif

    Can_C0TrmByTxBuf(17, &CAN_Trans_Data);
  }
}

static uint32 TickTimer = 0;
/******************************************************************************
* Function Name: Can_Test
* Description  : Can模块测试
* Arguments    : None
* Return Value : None
******************************************************************************/
void Pwm_Test(void)
{
    TickTimer++;

    if (TickTimer == 10)
    {
        Pwm_Init();
    }
    
    if (TickTimer == 150)
    {
        Pwm_DeInit();
    }

    if (TickTimer == 100)
    {
        Pwm_SetDutyCycle(PWM_CH_LED, 0x0FFF / 2);
    }
}

uint16 Buffer;
/******************************************************************************
* Function Name: Can_Test
* Description  : Can模块测试
* Arguments    : None
* Return Value : None
******************************************************************************/
void Adc_Test(void)
{
    Adc_StatusType Adc_Status;
    

    Adc_Status = Adc_GetStatus(ADC_GRP_BL_TMP);

    if (Adc_Status == ADC_IDLE)
    {
        Adc_StartGroup(ADC_GRP_BL_TMP, &Buffer);

        if (Adc_Status == ADC_IDLE)
        {
            printf("read success\n");
        }
    }
}

/******************************************************************************
* Function Name: Test_Task
* Description  : Mcu初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
void Test_Task(void)
{
    while(1)
    {

        // Mcu_GoDeepStop();

#if (TEST == 1)
        //Uart_transmit_string("this is a Uart test task runing\r\n");
        Can_Test();
        // Pwm_Test();
        Adc_Test();
#endif
        vTaskDelay(100);
    }

}
    