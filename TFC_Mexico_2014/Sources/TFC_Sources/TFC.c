#include "TFC_Headers/TFC.h"


void TFC_Init()
{
	TFC_InitClock();
	TFC_InitSysTick();
	TFC_InitGPIO();
	Init_Servo();
	TFC_InitMotorPWM();
    TFC_InitADCs();
    TFC_InitLineScanCamera();
    TFC_InitTerminal();
	TFC_InitUARTs();
}


void TFC_Task()
{
	#if defined(TERMINAL_USE_SDA_SERIAL)
		TFC_UART_Process();
	#endif
	 
    TFC_ProcessTerminal();
}
