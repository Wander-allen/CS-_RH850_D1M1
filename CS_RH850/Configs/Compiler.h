/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Compiler.h
Author: Steven
******************************************************************************/
#ifndef COMPILER_H
#define COMPILER_H
#ifdef __cplusplus
extern "C" {
#endif

#ifndef FAR
#define FAR
#endif

#ifndef TRUE
#define TRUE        1
#endif

#ifndef FALSE
#define FALSE       0
#endif

#ifndef NULL
#define NULL        ((void*)0)
#endif

#ifndef INTERRUPT
#define INTERRUPT   __interrupt
#endif

#ifdef __cplusplus
}
#endif
#endif

