/***********************************************************************/
/*                                                                     */
/*  FILE        :Main.c                                                */
/*  DATE        :Mon, Oct 24, 2016                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :                                                      */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
#include "EcuM.h"
#include "Cpu.h"
#include "Pin.h"


void main(void);

void main(void)
{
    EcuM_Init();
    EcuM_Start();

    // while(1)
    // {
    //     // Cpu_Delay1US();
    //     Cpu_DelayUS(10);
    //     //Cpu_DelayMS(10);
    //     Port_FlipPin(PORT_P17, 9);
    // }

    

    for( ;; );
}

