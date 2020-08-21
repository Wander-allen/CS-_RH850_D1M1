/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : EcuM.h      ECU management module
Author: Wander 
******************************************************************************/
#ifndef ECUM_H
#define ECUM_H
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
                                    局部宏方法
******************************************************************************/

/******************************************************************************
                                局部常量定义&类型定义
******************************************************************************/
typedef enum
{
    TEST_TASK,
    TASK_MAX,
}Task_num;
/******************************************************************************
                                    局部变量定义
******************************************************************************/
extern void EcuM_Init(void);
extern void EcuM_Start(void);


#ifdef __cplusplus
}
#endif
#endif