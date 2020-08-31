/******************************************************************************
Copyright (C) 2020 Querda Electronic Technology All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : Pwm.h 
Author: Wander 
******************************************************************************/
#ifndef PWM_H
#define PWM_H
#ifdef __cplusplus
extern "C" {
#endif

#include "Std_Types.h"
#include "Pwm_Define.h"

extern void Pwm_Init(void);
extern void Pwm_DeInit(void);
// extern void Pwm_Start(void);
// extern void PWM_Stop(void);

extern void Pwm_SetDutyCycle(uint8 Ch, uint16 DutyCycle);
extern void Pwm_SetPeriodAndDuty(uint8 Ch, uint16 Period, uint16 DutyCycle);

#ifdef __cplusplus


}
#endif
#endif