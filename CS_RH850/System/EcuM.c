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
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"  
#include "semphr.h"
#include "event_groups.h"
#include "ioDefine.h"
#include "EcuM.h"
#include "Pin.h"
#include "Mcu.h"
#include "Uart.h"
#include "Clock.h"
#include "Test.h"

/******************************************************************************
                                    局部宏方法
******************************************************************************/
#define BEGIN_OSCREATE(tasks, num)                                          \
static Os_ParaType Os_##tasks##Paramter[num] =                              \
{                                                                           \

#define DECLARE_OSCREATE(TaskCode, StackDepth, Parameters, Priority, CreatedTask)\
{                                                                           \
    TaskCode, #TaskCode, StackDepth, Parameters, Priority, CreatedTask,     \
}                                                                           \

#define END_OSCREATE()                                                      \
};                                                                          \

/******************************************************************************
                                局部常量定义&类型定义
******************************************************************************/

typedef struct
{
    TaskFunction_t pxTaskCode;
    const char * const pcName;
    const uint16_t usStackDepth;
    void * const pvParameters;
    UBaseType_t uxPriority;
    TaskHandle_t * const pxCreatedTask;
    
}Os_ParaType;

/******************************************************************************
                                    局部变量定义
******************************************************************************/
TaskHandle_t AppTaskCreate_Handle = NULL;/* 创建任务句柄 */
TaskHandle_t Task1ms_Handle = NULL;/* LED任务句柄 */
TaskHandle_t Task10ms_Handle = NULL;/* KEY任务句柄 */
TaskHandle_t Task100ms_Handle = NULL;/* KEY任务句柄 */
TaskHandle_t Task1s_Handle = NULL;/* KEY任务句柄 */
TaskHandle_t Test_Handle = NULL;/* KEY任务句柄 */

static void AppTaskCreate(void);
static void vEcu_1ms_Task( void *pvParameters );
static void vEcu_10ms_Task( void *pvParameters );
static void vEcu_100ms_Task( void *pvParameters );
static void vEcu_1s_Task( void *pvParameters );

/******************************************************************************
                                    任务创建
******************************************************************************/
BEGIN_OSCREATE(OS_TASK, 2)
    DECLARE_OSCREATE(Test_Task, 256, NULL, 3, &Test_Handle)
END_OSCREATE()


/******************************************************************************
* Function Name: Ecu_Init
* Description  : Mcu初始化
* Arguments    : None
* Return Value : None
******************************************************************************/
void EcuM_Init(void)
{
    Clock_Init();
    Mcu_Init();
    Port_Init();
    Uart_Init();
    Test_Init();
}

/******************************************************************************
* Function Name: Ecu_Init
* Description  : 开始任务创建
* Arguments    : None
* Return Value : None
******************************************************************************/
void EcuM_Start(void)
{
    BaseType_t xReturn;

    xReturn = xTaskCreate((TaskFunction_t )AppTaskCreate,  
                            (const char*    )"AppTaskCreate",
                            (uint16_t       )512,  
                            (void*          )NULL,
                            (UBaseType_t    )1, 
                            (TaskHandle_t*  )&AppTaskCreate_Handle); 
    if (xReturn < 0)
    {
        //printf("任务创建失败\n");
    }

    vTaskStartScheduler();
}

/******************************************************************************
* Function Name: vApplicationStackOverflowHook
* Description  : 堆栈溢出处理函数
* Arguments    : None
* Return Value : None
******************************************************************************/
void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{
    //暂时未添加，后续添加
}

/******************************************************************************
* Function Name: AppTaskCreate
* Description  : 任务创建
* Arguments    : None
* Return Value : None
******************************************************************************/
static void AppTaskCreate(void)
{
    BaseType_t xReturn;
    int i;

    /* 测试任务， 后续不需要可删除 */
    xReturn = xTaskCreate((TaskFunction_t )vEcu_1ms_Task,  
                        (const char*    )"vEcu_1ms_Task",
                        (uint16_t       )512,  
                        (void*          )NULL,
                        (UBaseType_t    )1, 
                        (TaskHandle_t*  )&Task1ms_Handle); 

    
    xReturn = xTaskCreate((TaskFunction_t )vEcu_10ms_Task,  
                        (const char*    )"vEcu_10ms_Task",
                        (uint16_t       )512,  
                        (void*          )NULL,
                        (UBaseType_t    )5, 
                        (TaskHandle_t*  )&Task10ms_Handle); 
                
    
    xReturn = xTaskCreate((TaskFunction_t )vEcu_100ms_Task,  
                        (const char*    )"vEcu_100ms_Task",
                        (uint16_t       )512,  
                        (void*          )NULL,
                        (UBaseType_t    )6, 
                        (TaskHandle_t*  )&Task100ms_Handle); 

    xReturn = xTaskCreate((TaskFunction_t )vEcu_1s_Task,  
                        (const char*    )"vEcu_1s_Task",
                        (uint16_t       )512,  
                        (void*          )NULL,
                        (UBaseType_t    )6, 
                        (TaskHandle_t*  )&Task1s_Handle); 

    /* 任务创建 */
    for (i = 0; i < TASK_MAX; i++)
    {
            xReturn = xTaskCreate((TaskFunction_t )Os_OS_TASKParamter[i].pxTaskCode,  
                                    (const char*    )Os_OS_TASKParamter[i].pcName,
                                    (uint16_t       )Os_OS_TASKParamter[i].usStackDepth,  
                                    (void*          )Os_OS_TASKParamter[i].pvParameters,
                                    (UBaseType_t    )Os_OS_TASKParamter[i].uxPriority, 
                                    (TaskHandle_t*  )Os_OS_TASKParamter[i].pxCreatedTask); 
    }
    vTaskDelete(AppTaskCreate_Handle);
}

/******************************************************************************
* Function Name: vLED_1_Task
* Description  : 任务1
* Arguments    : None
* Return Value : None
******************************************************************************/
static void  vEcu_1ms_Task(void *pvParameters)
{  
    for( ;; )
    {     
        //Port_FlipPin(PORT_P17, 9);
        
        vTaskDelay(1/portTICK_RATE_MS);
    }
}

/******************************************************************************
* Function Name: vLED_2_Task
* Description  : 任务2
* Arguments    : None
* Return Value : None
******************************************************************************/
static void  vEcu_10ms_Task(void *pvParameters)
{
    for( ;; )
    {     
        Port_FlipPin(PORT_P17, 9);
        
        vTaskDelay(10/portTICK_RATE_MS);
    }

}

/******************************************************************************
* Function Name: vLED_3_Task
* Description  : 任务3
* Arguments    : None
* Return Value : None
******************************************************************************/
static void  vEcu_100ms_Task(void *pvParameters)
{  

    for( ;; )
    {     
        //Port_FlipPin(PORT_P17, 9);
        
        vTaskDelay(100/portTICK_RATE_MS);
    }
}

/******************************************************************************
* Function Name: vLED_3_Task
* Description  : 任务3
* Arguments    : None
* Return Value : None
******************************************************************************/
static void  vEcu_1s_Task(void *pvParameters)
{  

    for( ;; )
    {     
        
        //Port_FlipPin(PORT_P17, 9);
        
        vTaskDelay(1000/portTICK_RATE_MS);
    }
}
