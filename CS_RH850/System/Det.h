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

#include <assert.h>

#ifdef RHDEBUG
#define assert_para(paramter)       assert(paramter)
#else
#define assert_para(paramter)
#endif


#ifdef __cplusplus
}
#endif
#endif