#include "derivative.h" /* include peripheral declarations */
#include "TFC_Headers/TFC.h"
#include "TFC_Headers/mma8451.h"
#include <math.h>
#include "arm_math.h"
#define kp_servo 	1.6036f//1.4036 con 0.6//1.6036//para 0.5//1.4596//1.5096 1.6036
//6 con 0.6 /*0.65 esta es para LUT de 0.5*/
#define ki_servo    0.01f
#define d_t 		0.011f

//Servo 28 Derecha,0 centro,-28 izquierda y=3.75*x+475
//Motores de 0 hasta 1 van para adelante, y de 0 a -1 van para atras
// 0 es Blanco y 1 es negro

signed short y=0,x=0,z=0;
int32_t i=0,j=0;
float32_t LeftMotor=0.0f,RightMotor=0.0f,Servo=0.0f,Error=0.0f,Prev_Error=0.0f,Derivative=0.0f,Integral=0.0f,kd_servo=0.0f;
float32_t Out[134],Edge[134],limitador[122],LeftHalf[61],RightHalf[61],RawData[128],ImageMeanRight=0.0f,ImageMeanLeft=0.0f;
float32_t LeftMax=0.0f,RightMax=0.0f,MaxMeanRight=0.0f,MaxMeanLeft=0.0f,BinaryData[122],Dilate[122];
float32_t DoG[7]={0.0333f,0.2707f,0.6065f,0.0f,-0.6065f,-0.2707f,-0.0333f};
float32_t buffer[8]={0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
uint32_t RawDataLen=128,DoGLen=7,ConvLen,LeftIndex=0,RightIndex=0,Cont=0,Error2=0,Suma=0,Integracion=0;
	
void Image_Dilate(float Binary_Data[122],float Dilate[122]);
void UART2_send(unsigned char dato);
void Calibracion(void);
void Camera(void);
//void UART2_putString(unsigned char *mystring);
//void UART2_Init(void);
int main(void)
{	
	TFC_Init();	
	//UART2_Init();
	//Init_TPM2();
	/*unsigned char tmp;
	mma8451_init();      //Initialize I2C modules
	tmp = mma8451_read_reg(0x2A);
	mma8451_write_reg(0x2A,tmp|0x35);
	tmp = mma8451_read_reg(0x0E);
	mma8451_write_reg(0x0E,tmp|0x12);*/
	for(;;)
	{	   
		TFC_Task();
		
		/*if((mma8451_read_reg(0x00)&0xf) != 0)
		{
			x=mma8451_read_reg(0x01)<<8;
			x|=mma8451_read_reg(0x02);
			y=mma8451_read_reg(0x03)<<8;
			y|=mma8451_read_reg(0x04);
			z=mma8451_read_reg(0x05)<<8;
			z|=mma8451_read_reg(0x06);
			y>>=11;
			x>>=11;
			z>>=11;
			
		}*/
		switch(Cont)
		{
		default:
		case 0 ://Carro parado
			j=4000;
			TFC_HBRIDGE_DISABLE;
			Move_Motor(0.0f,0.0f);
			Calibracion();
			if(TFC_PUSH_BUTTON_0_PRESSED)
			{
				TFC_Delay_mS(500);
				Cont=1;
			}
			if(TFC_GetDIP_Switch()&0x01)
			{
				kd_servo=0.6f;
				LeftMotor=0.45f;
				RightMotor=0.45f;
			}
			if(TFC_GetDIP_Switch()&0x02)/*LUT para 0.5*/
			{
				kd_servo=0.6f;
				float32_t ML_LUT[51] = {-0.1f,-0.1f,-0.0800f,-0.0800f,-0.0788f,-0.0788f,-0.0168058f,0.0410352f,0.0948142f,0.1446272f,0.190575f,
					0.2327632f,0.2713022f,0.3063072f,0.3378982f,0.3662f,0.3913422f,0.4134592f,0.4326902f,0.4491792f,0.463075f,
					0.4745312f,0.4837062f,0.4907632f,0.4958702f,0.5f,0.4983712f,0.4958702f,0.4958702f,0.495575f,0.4921392f,
					0.4882702f,0.4841792f,0.4800822f,0.4762f,0.4727582f,0.4703872f,0.4700942f,0.4699872f,0.4681222f,0.468075f,
					0.4674032f,0.4664032f,0.4654032f,0.4644032f,0.4634032f,0.4634032f,0.4634032f,0.4634032f,0.4634032f,0.4634032f};
				float32_t MR_LUT[51] = {0.4644032,0.4644032,0.4644032,0.4644032,0.4644032,0.4634032,0.4644032,0.4654032,0.4664032,0.4674032,0.468075,
					0.4681222,0.4699872,0.4700942,0.4703872,0.4727582,0.4762,0.4800822,0.4841792,0.4882702,0.4921392,
					0.495575,0.4958702,0.4958702,0.4983712,0.5,0.4958702,0.4907632,0.4837062,0.4745312,0.463075,
					0.4491792,0.4326902,0.4134592,0.3913422,0.3662,0.3378982,0.3063072,0.2713022,0.2327632,0.190575,
					0.1446272,0.0948142,0.0410352,-0.0168058,-0.0788,-0.0788,-0.0800,-0.0800f,-0.1f,-0.1f};
				LeftMotor=ML_LUT[(int32_t)Error+25];
				RightMotor=MR_LUT[(int32_t)Error+25];
			}
			if(TFC_GetDIP_Switch()&0x04)/*LUT para 0.6*/
			{
				kd_servo=6.0f;
				float32_t ML_LUT[51] = {-0.1992f,-0.1992f,-0.1992f,-0.1992f,-0.1992f,-0.1992f,-0.123f,-0.0506f,0.018f,0.0828f,0.1438f,
					0.201f,0.2544f,0.304f,0.3498f,0.3918f,0.43f,0.4644f,0.495f,0.5218f,0.5448f,
					0.564f,0.5794f,0.591f,0.5988f,0.6f,0.5967f,0.5928f,0.5883f,0.5832f,0.5775f,
					0.5712f,0.5643f,0.5568f,0.5487f,0.54f,0.5307f,0.5208f,0.5103f,0.4992f,0.4875f,
					0.4752f,0.4623f,0.4488f,0.4347f,0.42f,0.42f,0.42f,0.42f,0.42f,0.42f};
				float32_t MR_LUT[51] = {0.42f,0.42f,0.42f,0.42f,0.42f,0.42f,0.4347f,0.4488f,0.4623f,0.4752f,0.4875f,
					0.4992f,0.5103f,0.5208f,0.5307f,0.54f,0.5487f,0.5568f,0.5643f,0.5712f,0.5775f,
					0.5832f,0.5883f,0.5928f,0.5967f,0.6f,0.5988f,0.591f,0.5794f,0.564f,0.5448f,
					0.5218f,0.495f,0.4644f,0.43f,0.3918f,0.3498f,0.304f,0.2544f,0.201f,0.1438f,
					0.0828f,0.018f,-0.0506f,-0.123f,-0.1992f,-0.1992f,-0.1992f,-0.1992f,-0.1992f,-0.1992f};
					LeftMotor=ML_LUT[(int32_t)Error+25];
					RightMotor=MR_LUT[(int32_t)Error+25];
			}
			if(TFC_GetDIP_Switch()&0x08)/*Ecuacion para 0.65*/
			{
				kd_servo=6.0f;
				LeftMotor=-0.0015f*(Error*Error)+0.0158f*Error+0.6497f;
				RightMotor=-0.0015f*(Error*Error)-0.0158f*Error+0.6497f;
				//LeftMotor=-0.0017f*(Error*Error)+0.0161f*Error+0.75f;
				//RightMotor=-0.0017f*(Error*Error)-0.0161f*Error+0.75f;
			}
			if(TFC_GetDIP_Switch()&&0x00)/*Apagados*/
			{
				LeftMotor=0.0f;
				RightMotor=0.0f;
			}
			break;
		case 1 ://Carro recorriendo la pista
			TFC_HBRIDGE_ENABLE;
			if(TFC_PUSH_BUTTON_0_PRESSED)
			{
				TFC_Delay_mS(500);
				Cont=0;
			}
			if(TFC_Ticker[0]>11 && LineScanImageReady==1)
			{
				Error=0.0f;
				Camera();
				TFC_Ticker[0] = 0;
				LineScanImageReady=0;
				TERMINAL_PRINTF("\r");
				TERMINAL_PRINTF("L:");
				//TERMINAL_PRINTF("%d",Suma);
				//TERMINAL_PRINTF("R:");
				//TERMINAL_PRINTF("%d",RightIndex);
				
				if((Servo>=-29.0f)&&(Servo<=29.0f))
				{
					//LeftMotor=-0.0012f*(Error*Error)+0.0078f*Error+0.4897f;
					//RightMotor=-0.0012f*(Error*Error)-0.0078f*Error+0.4897f;
					/*6Mejorado*///LeftMotor=-0.0012f*(Error*Error)+0.008f*Error+0.5797f;
					/*6Mejorado*///RightMotor=-0.0012f*(Error*Error)-0.008f*Error+0.5797f;
					/*7*///LeftMotor=-0.0012f*(Error*Error)+0.0098f*Error+0.6697f;
					/*7*///RightMotor=-0.0012f*(Error*Error)-0.0098f*Error+0.6697f;
					Move_Motor(LeftMotor,RightMotor);
					Integral=Integral+Error*d_t;
					Derivative = (Error-Prev_Error);
					Servo=(Error*kp_servo)+(kd_servo*Derivative)+(ki_servo*Integral);
					Move_Servo(0,Servo);
					Prev_Error=Error;
				}
					if(Servo>20.0f) Servo=29.0f;
					if(Servo<-29.0f) Servo=-29.0f;
			}
			break;
		case 2 ://Carro llego a la meta
			while(--j){
				Move_Motor(-0.3f,-0.3f);
				Move_Servo(0,-0.5f);
				Cont=0;
			}
			Move_Motor(0.0f,0.0f);
			break;
			
		}
	}

}

/*void mma8451_init(void)
{
  i2c0_init(I2C0_B);
}
// this delay is very important, it may cause w-r operation failure.
static void pause(void)
{
    int n;
    for(n=0; n<40; n++)
        asm("nop");
}

uint16_t mma8451_read_reg(uint8_t addr)
{
    uint8_t result;

    i2c_start(I2C0_B);
    i2c_write_byte(I2C0_B, MMA8451_I2C_ADDRESS | I2C_WRITE);
    
    i2c_wait(I2C0_B);
    i2c_get_ack(I2C0_B);

    i2c_write_byte(I2C0_B, addr);
    i2c_wait(I2C0_B);
    i2c_get_ack(I2C0_B);

    i2c_repeated_start(I2C0_B);
    i2c_write_byte(I2C0_B, MMA8451_I2C_ADDRESS | I2C_READ);
    i2c_wait(I2C0_B);
    i2c_get_ack(I2C0_B);

    i2c_set_rx_mode(I2C0_B);

    i2c_give_nack(I2C0_B);
    result = i2c_read_byte(I2C0_B);
    i2c_wait(I2C0_B);

    i2c_stop(I2C0_B);
    result = i2c_read_byte(I2C0_B);
    pause();
    return result;
}

void mma8451_write_reg(uint8_t addr, uint8_t data)
{
    i2c_start(I2C0_B);

    i2c_write_byte(I2C0_B, MMA8451_I2C_ADDRESS|I2C_WRITE);
    i2c_wait(I2C0_B);
    i2c_get_ack(I2C0_B);

    i2c_write_byte(I2C0_B, addr);
    i2c_wait(I2C0_B);
    i2c_get_ack(I2C0_B);

    i2c_write_byte(I2C0_B, data);
    i2c_wait(I2C0_B);
    i2c_get_ack(I2C0_B);

    i2c_stop(I2C0_B);
    pause();
}*/


void Image_Dilate(float32_t Binary_Data[122],float32_t Dilate[122])
{
	float32_t B[2]={1.0,1.0};
	float32_t C[134];
	float32_t aux[2];
	uint32_t i=0,j=0;
	float32_t suma=0;
	C[0]=0;
	C[133]=0;
	for(i=0;i<122;i++)
	{
		C[i+1]=BinaryData[i];
	}
	for(i=0;i<122;i++)
	{
		for(j=0;j<2;j++)
		{
			aux[j]=C[i+j];
			aux[j]=B[j]&&aux[j];
			suma=0;
		}
		for(j=0;j<2;j++)
			suma=suma+aux[j];
		if(suma>=1)
			Dilate[i]=1;
		else
			Dilate[i]=0;
		}
	}

void Calibracion(void)
{
	if(LineScanImageReady==1)
	{
		LineScanImageReady=0;
		for(i=0;i<128;i++)
			Suma=Suma+LineScanImage0[i];
		Suma/=128;
	}
	if(Suma>3000){
		Integracion=Integracion-1;
		TFC_BAT_LED0_OFF;
	}
	else if(Suma<2850)
	{
		Integracion=Integracion+1;
		TFC_BAT_LED0_OFF;
	}
	else
	{
		Integracion=Integracion;
		TFC_BAT_LED0_ON;
	}
	if(Integracion>=50000)
		Integracion=50000;
	if(Integracion<=0)
		Integracion=0;
	TFC_SetLineScanExposureTime(Integracion);
	//TFC_SetLineScanExposureTime((uint32_t)((4000*TFC_ReadPot(0))+14000));
}

void Camera(void)
{
	for(i=0;i<128;i++)
		RawData[i]=(float32_t)LineScanImage0[i];
	arm_conv_f32(RawData,RawDataLen,DoG,DoGLen,Out);
	arm_abs_f32(Out,Edge,134);	
	for(i=0;i<122;i++)
		limitador[i]=Edge[i+6];
	for(i=0;i<61;i++)
	{
		LeftHalf[i]=limitador[i];
		RightHalf[i]=limitador[i+61];
	}
	arm_max_f32(LeftHalf,61,&LeftMax,&LeftIndex);
	arm_max_f32(RightHalf,61,&RightMax,&RightIndex);
	LeftIndex=60;RightIndex=61;
	for(i=0;i<61;i++)
	{
		BinaryData[i]=limitador[i]<LeftMax?0:1;
		BinaryData[i+61]=limitador[i+61]<RightMax?0:1;
	}
	Image_Dilate(BinaryData,Dilate);
	while(Dilate[LeftIndex]!=1)
		LeftIndex--;
	while(Dilate[RightIndex]!=1)
		RightIndex++;
	Error=(61.0f-((LeftIndex+RightIndex)/2.0f));
}

/*
void UART2_Init(void)
{
	SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;
	PORTD_PCR2 = (uint32_t)((PORTD_PCR2 & (uint32_t)~(uint32_t)(PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x04))) | (uint32_t)(PORT_PCR_MUX(0x03)));
	PORTD_PCR3 = (uint32_t)((PORTD_PCR3 & (uint32_t)~(uint32_t)(PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x04))) | (uint32_t)(PORT_PCR_MUX(0x03)));
	UART2_C2 = 0x00U;
	UART2_BDH = UART_BDH_SBR(0x00);
	UART2_BDL = UART_BDL_SBR(0x9C);
	UART2_C1 = 0x00U;
	UART2_S2 = (UART_S2_LBKDIF_MASK | UART_S2_RXEDGIF_MASK);
	(void) UART2_S1;                  //Dummy read of the UART2_S1 register to clear flags 
	(void) UART2_D;                   //Dummy read of the UART2_D register to clear flags 
	UART2_C4 = 0x00U;
	UART2_C3 = 0x00U;
	UART2_C2 = (UART_C2_TE_MASK | UART_C2_RE_MASK);
}

void UART2_send(unsigned char dato){
	while (!((UART2_S1)&(UART_S1_TDRE_MASK)));  //ejecuta lo demas hasta que el buffer este libre
	UART2_D = dato;
}

void UART2_putString(unsigned char *mystring){
	while(*mystring){
		UART2_send(*mystring);
		mystring++;
	}
}

void LCDsendCommand(unsigned char com){
	TERMINAL_PUTC(0xFE);
	TERMINAL_PUTC(com);
}

void LCDclearScreen(void){
	LCDsendCommand(0x01);
}

void LCDgotoPosition(unsigned char pos){
	LCDsendCommand(128+pos);
}

void LCDgotoSecondLine(void){
	LCDsendCommand((unsigned char)(128+64));
}

void LCDgotoxy(char x, char y){
	LCDgotoPosition((unsigned char)(x*64+y));
}*/
