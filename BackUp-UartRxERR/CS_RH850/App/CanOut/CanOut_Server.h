/******************************************************************************
Copyright (C) 2019 Steven, mculib.net All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : CanOut_Server.c  CanOut外发服务
Author: Wander
******************************************************************************/
#ifndef CANOUT_SERVER_H
#define CANOUT_SERVER_H

extern void CanOut_ServerInit(void);
extern void CanOut_Enable(CanOut_PduID PduId, boolean Status);
extern void CanOut_Active(CanOut_PduID PduId);
extern void CanOut_Disable(CanOut_PduID PduId);
extern void CanOut_GetServerDataBuff(CanOut_PduID PduId, uint8 *data);
extern void CanOut_UpdateServerDataBuff(CanOut_PduID PduId, uint8 *data);
extern void CanOut_ServerFunction(void);

#endif
