/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : DbgIf.h Debug uart通讯接口
Author: Steven 
******************************************************************************/
#ifndef DBGIF_H
#define DBGIF_H

#include "Std_Types.h"


#ifdef DEBUG
#define DG_printf Dbgif_printf
#else
#define DG_printf 
#endif


extern int Dbgif_printf(const char *format, ...);



#endif

