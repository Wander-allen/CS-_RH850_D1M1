/******************************************************************************
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
#include "Can.h"
#include "Pin.h"
#include "Pwm.h"
#include "Adc.h"
#include "Mcu.h"
#include "CanSm.h"
#include "Crc.h"

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
uint16 CrcRetData;
/******************************************************************************
* Function Name: Test_Init
* Description  : Mcu初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
void Test_Init(void)
{
    Crc_Init();
    CrcRetData = Crc_GetCalData();
    // Uart_transmit_string("hello world\r\n");
    // Uart_transmit_string("Test_Init Success\r\n");
    
}

Can_PduType TmpCanFrameData = {0};
/******************************************************************************
* Function Name: Can_Test
* Description  : Can模块测试
* Arguments    : None
* Return Value : None
******************************************************************************/
void Can_Test(void)
{
    static uint8 InitFlag = 0;
    uint8 i;

    if (InitFlag == 0)
    {
        for (i = 0; i < 8; i++)
        {
            TmpCanFrameData.Data[i] = i * 2;
        }
    }

    /* Can White */
    if(TmpCanFrameData.Id<0xFF)
      TmpCanFrameData.Id++;
    else
      TmpCanFrameData.Id=0x01;
    
    TmpCanFrameData.Length = 8;
    CAN_Transmit(CAN1, &TmpCanFrameData);
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


/******************************************************************************
* Function Name: Can_Test
* Description  : Can模块测试
* Arguments    : None
* Return Value : None
******************************************************************************/
void Adc_Test(void)
{
    uint16 Buffer;

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
        // Adc_Test();
#endif
        vTaskDelay(100);
    }

}
    