/******************************************************************************
Copyright (C) 2019 Steven, mculib.net All Rights Reserved

This software and code can be freely used for study and research. 
For commercial purposes, please contact the owner for permission.

File  : CanIn.c  CAN�������봦��
Author: 
******************************************************************************/
#include <string.h>
#include <stdio.h>
#include "Cpu.h"
#include "CanIn.h"
#include "jlrx_can.h"
//#include "JLRX_IPC.h"
#include "canif.h"
#include "chery_can.h"
#include "chery_uds.h"
#include "DbgIf.h"

typedef void CanIn_RxFunType(const uint8*);

typedef struct
{
    uint8 RxFlag;      /* ���յ��±��ı�־    */
    boolean Valid;     /* ������Ч��־        */
    uint16 RxTimer;    /* ���ݽ��ռ�ʱ��      */
    uint8 RxBuffer[8]; /* ���ݻ�����          */
} CanIn_PduVarType;


typedef struct
{
    uint32           CanID;          /* CANID        */
    uint8            UpdateTimer;    /* ���ݸ���ʱ�� */
    CanIn_RxFunType *Rx_function;    /* ���ݴ���     */
}CanIn_Type;

typedef struct 
{
    boolean RxFlag;    /* ���ĸ��±��    */
    uint8   RxCnt;     /* ���Ľ���֡��    */
    uint32  RxTimer;   /* ���ĵ��߼�ʱ    */
    uint8   Data[8];   /* ���ݻ�����      */
}CanIn_VarType;

static uint16 CanInIdleTimer;
static CanIn_PduVarType CanInPduVars[CANIN_RXPDU_NUMBER];

static const CanIn_Type CanInPduRxFun[CANIN_RXPDU_NUMBER] = {DEFAULT_CANINRXFUN};/* CANIn������Ϣ */
static CanIn_VarType CanInDataBuff[CANIN_RXPDU_NUMBER];        /* һ������ */
static CanIn_VarType CanInDataUser[CANIN_RXPDU_NUMBER];        /* �������� */
static uint32 CanInCanBusRxTimer = 0;/* can���߿��м�ʱ 100ms */

#if 1

/******************************************************************************
��������: void CanIn_Init(void)
����˵��: 
����޸�: Steven
******************************************************************************/
void CanIn_Init(void)
{
    CanInCanBusRxTimer = 0;
    (void)memset(CanInDataBuff, 0x00, (sizeof(CanIn_VarType) * CANIN_RXPDU_NUMBER));
    (void)memset(CanInDataUser, 0x00, (sizeof(CanIn_VarType) * CANIN_RXPDU_NUMBER));
}

/******************************************************************************
��������: void CanIn_ClrFrameData(CanIn_ID RxPduId, Byte_t Byte, Bits_t Bit)
����˵��: �����������
����޸�: Wander
******************************************************************************/
void CanIn_ClrFrameData(CanIn_ID RxPduId, Byte_t Byte, Bits_t Bit)
{
    ComIf_ClrData(CanInDataUser[RxPduId].Data, Byte, Bit);
}

/******************************************************************************
��������: void CanIn_Init(void)
����˵��: �������������������
����޸�: Wander
******************************************************************************/
void CanIn_ClrFrameAllData(CanIn_ID RxPduId)
{
    uint8 j;
    
    for (j = 0; j < 8; j++)
    {
        CanIn_ClrFrameData((CanIn_ID) RxPduId, (Byte_t) j, BITS_B07);
    }
}


/******************************************************************************
��������: void CanIn_SetFrameData(CanIn_ID RxPduId, uint8 Value, Byte_t Byte, Bits_t Bit)
����˵��: ���ñ�������
����޸�: Wander
******************************************************************************/
void CanIn_SetFrameData(CanIn_ID RxPduId, uint8 Value, Byte_t Byte, Bits_t Bit)
{
    ComIf_SetData(CanInDataUser[RxPduId].Data, Value, Byte, Bit);
}

/******************************************************************************
��������: void CanIn_GetFrameData(CanIn_ID RxPduId, Byte_t Byte, Bits_t Bit)
����˵��: ��ȡ��������
����޸�: Wander
******************************************************************************/
uint8 CanIn_GetFrameData(CanIn_ID RxPduId, Byte_t Byte, Bits_t Bit)
{
    return ComIf_GetData(CanInDataUser[RxPduId].Data, Byte, Bit);
}

/******************************************************************************
��������: void CanIn_GetFrameData(CanIn_ID RxPduId, Byte_t Byte, Bits_t Bit)
����˵��: ��ȡ��������
����޸�: Wander
******************************************************************************/
void CanIn_ClrFrameDataMotorolaLsb(CanIn_ID RxPduId, uint8 Start, uint8  Len)
{
    ComIf_ClrDataMotorolaLsb(CanInDataUser[RxPduId].Data, Start, Len);
}

/******************************************************************************
��������: void CanIn_GetFrameData(CanIn_ID RxPduId, Byte_t Byte, Bits_t Bit)
����˵��: ��ȡ��������
����޸�: Wander
******************************************************************************/
void CanIn_SetFrameDataMotorolaLsb(CanIn_ID RxPduId, uint32 value, uint8 Start, uint8  Len)
{
    ComIf_SetDataMotorolaLsb(CanInDataUser[RxPduId].Data, value, Start, Len);
}


/******************************************************************************
��������: void CanIn_GetFrameData(CanIn_ID RxPduId, Byte_t Byte, Bits_t Bit)
����˵��: ��ȡ��������
����޸�: Wander
******************************************************************************/
uint32 CanIn_GetFrameDataMotorolaLsb(CanIn_ID RxPduId, uint8 Start, uint8  Len)
{
    return ComIf_GetDataMotorolaLsb(CanInDataUser[RxPduId].Data, Start, Len);
}

/******************************************************************************
��������: void CanIn_GetFrameData(CanIn_ID RxPduId, Byte_t Byte, Bits_t Bit)
����˵��: ���㱨�Ľ���֡��
����޸�: Wander
******************************************************************************/
void CanIn_ClrCanFrameRxCnt(CanIn_ID RxPduId)
{
    CanInDataUser[RxPduId].RxCnt = 0;
}

/******************************************************************************
��������: void CanIn_GetFrameData(CanIn_ID RxPduId, Byte_t Byte, Bits_t Bit)
����˵��: ��ȡ���Ľ���֡��
����޸�: Wander
******************************************************************************/
uint8 CanIn_GetCanFrameRxCnt(CanIn_ID RxPduId)
{
    return CanInDataUser[RxPduId].RxCnt;
}

/******************************************************************************
��������: void CanIn_GetFrameData(CanIn_ID RxPduId, Byte_t Byte, Bits_t Bit)
����˵��: ���㱨�ĵ���ʱ��(100ms)
����޸�: Wander
******************************************************************************/
void CanIn_ClrCanFrameRxTimer(CanIn_ID RxPduId)
{
    CanInDataUser[RxPduId].RxTimer = 0;
}


/******************************************************************************
��������: void CanIn_GetFrameData(CanIn_ID RxPduId, Byte_t Byte, Bits_t Bit)
����˵��: ��ȡ���ĵ���ʱ��(100ms)
����޸�: Wander
******************************************************************************/
uint16 CanIn_GetCanFrameRxTimer(CanIn_ID RxPduId)
{
    return CanInDataUser[RxPduId].RxTimer;
}

/******************************************************************************
��������: void CanIn_ClrCanBusRxTimer(void)
����˵��: ��ȡ���ĵ���ʱ��(100ms)
����޸�: Wander
******************************************************************************/
void CanIn_ClrCanBusRxTimer(void)
{
    CanInCanBusRxTimer = 0;
}


/******************************************************************************
��������: uint16 CanIn_GetCanBusRxTimer(void)
����˵��: ��ȡ���ĵ���ʱ��(100ms)
����޸�: Wander
******************************************************************************/
uint16 CanIn_GetCanBusRxTimer(void)
{
    return CanInCanBusRxTimer;
}

/******************************************************************************
��������: void CanIn_RxCallback(uint8 RxPduId, const uint8* Data, uint8 Length)
����˵��: 
����޸�: Steven
******************************************************************************/
void CanIn_RxCallback(CanIn_ID RxPduId, const uint8* Data, uint8 Length)
{
    if (RxPduId < CANIN_RXPDU_NUMBER)
    {
        (void)memcpy(&(CanInDataBuff[RxPduId].Data[0]), Data, 8);
        CanInDataBuff[RxPduId].RxCnt++;
        CanInDataBuff[RxPduId].RxTimer = 0;
        CanInDataBuff[RxPduId].RxFlag = TRUE;
    }
}

/******************************************************************************
��������: static void CanIn_AnalyseFrame(void)
����˵��: ��������
����޸�: Steven
******************************************************************************/
static void CanIn_AnalyseFrame(void)
{
    static uint8 CanFrameTimer = 0;
    uint8 i;

    CanFrameTimer++;

    /* ���ĸ��´��� */
    for (i = 0; i < CANIN_RXPDU_NUMBER; i++)
    {
        if ((CanFrameTimer % CanInPduRxFun[i].UpdateTimer) == 0)
        {
            if (CanInDataBuff[i].RxFlag == TRUE)
            {
                CanInDataBuff[i].RxFlag = FALSE;
                CanInDataUser[i].RxCnt = CanInDataBuff[i].RxCnt;
                CanInDataUser[i].RxTimer = CanInDataBuff[i].RxTimer;
            }

            /* ���ݸ��� */
            if (memcmp(&(CanInDataUser[i].Data[0]), &(CanInDataBuff[i].Data[0]), 8))
            {
                (void)memcpy(&(CanInDataUser[i].Data[0]), &(CanInDataBuff[i].Data[0]), 8);
                if (CanInPduRxFun[i].Rx_function != NULL)
                {
                    CanInPduRxFun[i].Rx_function(&(CanInDataUser[i].Data));
                }
            }
        }
    }
}

/******************************************************************************
��������: static void CanIn_CanFrameTimer(void)
����˵��: ���߿���ʱ���ʱ(100ms)
����޸�: Wander
******************************************************************************/
static void CanIn_CanFrameTimer(void)
{
    uint8 i;
    
    for (i = 0; i < CANIN_RXPDU_NUMBER; i++)
    {
        if (CanInDataUser[i].RxTimer < 65535)
        {
            CanInDataUser[i].RxTimer++;
        }
    }

}


/******************************************************************************
��������: static void CanIn_CanBusTimer(void)
����˵��: ���߿���ʱ���ʱ(100ms)
����޸�: Wander
******************************************************************************/
static void CanIn_CanBusTimer(void)
{
    uint8 i;
    
    for (i = 0; i < CANIN_RXPDU_NUMBER; i++)
    {
        if (CanInDataUser[i].RxTimer != 0)
        {
            continue;
        }
        
        CanInCanBusRxTimer = 0;
        break;
    }
    if (i == CANIN_RXPDU_NUMBER)
    {
        if (CanInCanBusRxTimer < 65535)
        {
            CanInCanBusRxTimer++;
        }
    }
    
}


#else

/******************************************************************************
��������: void CanIn_Init(void)
����˵��: 
����޸�: Steven
******************************************************************************/
void CanIn_Init(void)
{
    ;
}

/******************************************************************************
��������: void CanIn_RxCallback(uint8 RxPduId, const uint8* Data, uint8 Length)
����˵��: 
����޸�: Steven
******************************************************************************/
void CanIn_RxCallback(CanIn_ID RxPduId, const uint8* Data, uint8 Length)
{
    CanIn_PduVarType* PduVar = &CanInPduVars[RxPduId];

	if (RxPduId < CANIN_RXPDU_NUMBER)
	{
    (void)memcpy(PduVar->RxBuffer, Data, Length);
    PduVar->RxFlag = 0x01;
    PduVar->RxTimer = 0;
	}
}

/******************************************************************************
��������: CanInPduRxFun
����˵��: 
����޸�: Steven
******************************************************************************/
static void(*const CanInPduRxFun[CANIN_RXPDU_NUMBER])(const uint8*) =
{
    CanIn_RxFrame123,  /* Pdu00 */
	CanIn_RxFrame245,
    CanIn_RxFrame24A,
    CanIn_RxFrame24C,
    CanIn_RxFrame271,
	CanIn_RxFrame28A,
    CanIn_RxFrame2E5,
	CanIn_RxFrame314,
    CanIn_RxFrame331,
	CanIn_RxFrame34B,
	CanIn_RxFrame38F,
	CanIn_RxFrame3B1,
	CanIn_RxFrame3BA,
    CanIn_RxFrame42D,
	CanIn_RxFrame45D,
	CanIn_RxFrame47D,
	
    
    //CanIn_RxFramexxx,  /* Pdu01 */
    //CanIn_RxFramexxx,  /* Pdu02 */
    //CanIn_RxFramexxx,  /* Pdu03 */
    //CanIn_RxFramexxx,  /* Pdu04 */
};

/******************************************************************************
��������: static void CanIn_AnalyseFrame(void)
����˵��: ��������
����޸�: Steven
******************************************************************************/
static void CanIn_AnalyseFrame(void)
{
    CanIn_PduVarType* PduVar;
    uint8 i;

    /* CAN���м�ʱ */
    if (CanInIdleTimer < 65535)
    {
        CanInIdleTimer++;
    }

    /* ���Ľ��մ��� */
    PduVar = &CanInPduVars[0];
	for (i = 0; i < CANIN_RXPDU_NUMBER; i++, PduVar++)
    {
        if (PduVar->RxTimer < 65535)
        {
            PduVar->RxTimer++;
        }
        
        if (!(PduVar->RxFlag & 0x01))
        {
            continue;
        }

        PduVar->RxFlag &= 0xFE;
        PduVar->Valid = TRUE;
        CanInIdleTimer = 0;
        
        if (CanInPduRxFun[i] != NULL)
        {
            CanInPduRxFun[i](PduVar->RxBuffer);
        }
    }
}
#endif

/******************************************************************************
��������: static void CanIn_test(void)
����˵��: CanIn�ӿڲ��Ժ���
����޸�: Wander
******************************************************************************/
static void CanIn_test(void)
{  
    static uint8 LastCanFrameRxcnt[CANIN_RXPDU_NUMBER] = {0};
    uint8 data;
    uint8 i;
    static uint32 TickTimer = 0;

    TickTimer = (TickTimer < 65535) ? TickTimer + 1 : 65535;
    
    for (i = 0; i < CANIN_RXPDU_NUMBER; i++)
    {
        
        /* ͨѶʧ�ܲ��� */
        if (CanIn_GetCanFrameRxTimer((CanIn_ID)0) > 600)
        {
            DG_printf("PduId: %d has been Frame break\r\n");
        }
        
        /* ���ݸ��²��� */
        if (LastCanFrameRxcnt[i] == CanIn_GetCanFrameRxCnt((CanIn_ID)i))
        {
            continue;
        }

        LastCanFrameRxcnt[i] = CanIn_GetCanFrameRxCnt((CanIn_ID)i);

        CanIn_SetFrameData((CanIn_ID) i, 0xff, (Byte_t) BYTE0, BITS_B07);
        CanIn_ClrFrameData((CanIn_ID) i,  (Byte_t) BYTE7, BITS_B07);

        /* ���ݽ��ղ��� */
        for (uint8 j = 0; j < 8; j++)
        {
            data = CanIn_GetFrameData((CanIn_ID) i, (Byte_t) j, BITS_B07);
            DG_printf("pduId: %d data[%d]:%x\r\n", i, j, data);
        }
        DG_printf("\r\n");

        uint32 VehicleSpeed = 0;
        
        VehicleSpeed = CanIn_GetFrameDataMotorolaLsb(CANIN_RXPDU_271, 43, 13);
        DG_printf("VehicleSpeed = %d\r\n", VehicleSpeed);

        CanIn_SetFrameDataMotorolaLsb(CANIN_RXPDU_271, 100, 43, 13);
        VehicleSpeed = CanIn_GetFrameDataMotorolaLsb(CANIN_RXPDU_271, 43, 13);
        DG_printf("VehicleSpeed = %d\r\n", VehicleSpeed);

        CanIn_ClrFrameDataMotorolaLsb(CANIN_RXPDU_271, 43, 13);
        VehicleSpeed = CanIn_GetFrameDataMotorolaLsb(CANIN_RXPDU_271, 43, 13);
        DG_printf("VehicleSpeed = %d\r\n", VehicleSpeed);

        
    }

}

/******************************************************************************
��������: void CanIn_PollFunction(void)
����˵��: (1ms)
����޸�: Steven
******************************************************************************/
void CanIn_PollFunction(void)
{
    static uint32 TickTimer = 0;

    TickTimer++;

    CanIn_test();
    
    /* 10ms �������� */
    if ((TickTimer % 10) == 0 )
    {
        CanIn_AnalyseFrame();
    }

    /* 100ms�������� */
    if ((TickTimer % 100) == 0 )
    {
        CanIn_CanBusTimer();
        CanIn_CanFrameTimer();
    }
}
