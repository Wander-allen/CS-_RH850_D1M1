/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Det.c   Error Detection
Author: Wander 
******************************************************************************/

/******************************************************************************
Pragma directive
******************************************************************************/

/******************************************************************************
Includes
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Std_Types.h"

/******************************************************************************
Define Register
******************************************************************************/

/******************************************************************************
Global variables and functions
******************************************************************************/

/******************************************************************************
* Function Name: assert_failed
* Description  : 断言函数处理
* Arguments    : None
* Return Value : None
******************************************************************************/
assert_failed(uint8* file, uint32 line)
{
    (void) file;
    (void) line;
    // fflush(stdout);
    // fprintf(stderr,"\nAssert failed： %s, line %u\n",file, line);
    // fflush(stderr);
    // abort();
}