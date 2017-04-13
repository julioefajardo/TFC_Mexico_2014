#include "TFC/TFC.h"


void TFC_Init()
{
	TFC_InitClock();
	TFC_InitSysTick();
	TFC_InitGPIO();
	Init_Servo();
	Init_Motor();
    TFC_InitADCs();
    TFC_InitLineScanCamera();
    //TFC_InitTerminal();
	//TFC_InitUARTs();
	//Move_Servo(568);
	//Move_Motor(2400,2400);
	
}

void TFC_Task()
{
	#if defined(TERMINAL_USE_SDA_SERIAL)
		TFC_UART_Process();
	#endif
	 
    TFC_ProcessTerminal();
}
