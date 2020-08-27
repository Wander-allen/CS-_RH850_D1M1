/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Adc.h 
Author: Wander 
******************************************************************************/
#ifndef ADC_H
#define ADC_H
#ifdef __cplusplus
extern "C" {
#endif

#include "Std_Types.h"

extern void ADC0_Init(void);
extern void ADC0_Start(void);
extern void ADC0_Stop(void);

#ifdef __cplusplus
}
#endif
#endif