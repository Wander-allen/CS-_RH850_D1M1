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
#include "Adc_Define.h"

typedef enum
{
    ADC_IDLE,
    ADC_BUSY,
    ADC_COMPLETED,
} Adc_StatusType;

extern void Adc_Init(void);
extern void Adc_DeInit(void);

extern void Adc_StopGroup(ADC_ChannelType ChId);
extern void Adc_StartGroup(ADC_ChannelType ChId, uint16* Buffer);
extern Adc_StatusType Adc_GetStatus(ADC_ChannelType ChId);

#ifdef __cplusplus
}
#endif
#endif