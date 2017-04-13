#include "TFC/TFC.h"


#define FTM1_CLOCK                                                                  (CORE_CLOCK)
#define FTM1_CLK_PRESCALE                                  						     6// Prescale Selector value - see comments in Status Control (SC) section for more details
#define FTM1_OVERFLOW_FREQUENCY 50  // Desired Frequency of PWM Signal - Here 50Hz => 20ms period
// use these to dial in servo steering to your particular servo
#define SERVO_MIN_DUTY_CYCLE                                          (float)(.0010*FTM1_OVERFLOW_FREQUENCY)  // The number here should be be *pulse width* in seconds to move servo to its left limit
#define SERVO_MAX_DUTY_CYCLE                                         (float)(.0020*FTM1_OVERFLOW_FREQUENCY)  // The number here should be be *pulse width* in seconds to move servo to its Right limit
/**********************************************************************************************/

//Position is -1.0 to 1.0.   Use SERVO_X_MIN_DUTY_CYCLE and SERVO_MAX_DUTY_CYCLE  to calibrate the extremes

/******************************************* Function to control Interrupt ************************************/
volatile unsigned char ServoTickVar;

void FTM1_IRQHandler()
{
               //Clear the overflow mask if set.   According to the reference manual, we clear by writing a logic one!
               if(TPM1_SC & TPM_SC_TOF_MASK)
                              TPM1_SC |= TPM_SC_TOF_MASK;
               
               if (ServoTickVar < 0xff)//if servo tick less than 255 count up... 
                              ServoTickVar++;
  
}

void Init_Servo()
{
               
               //Clock Setup for the TPM requires a couple steps.
               
    
				
               //1st,  set the clock mux
               //See Page 124 of f the KL25 Sub-Family Reference Manual, Rev. 3, September 2012
               SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;// We Want MCGPLLCLK/2 (See Page 196 of the KL25 Sub-Family Reference Manual, Rev. 3, September 2012)
               SIM_SOPT2 &= ~(SIM_SOPT2_TPMSRC_MASK);
               SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1); //We want the MCGPLLCLK/2 (See Page 196 of the KL25 Sub-Family Reference Manual, Rev. 3, September 2012)
  

				//Enable the Clock to the FTM0 Module
				//See Page 207 of f the KL25 Sub-Family Reference Manual, Rev. 3, September 2012
				SIM_SCGC6 |= SIM_SCGC6_TPM1_MASK; 
               
               //The TPM Module has Clock.  Now set up the peripheral
               
               //Blow away the control registers to ensure that the counter is not running
               TPM1_SC = 0;
               TPM1_CONF = 0;
               
               //While the counter is disabled we can setup the prescaler
               
               TPM1_SC = TPM_SC_PS(FTM1_CLK_PRESCALE);
               TPM1_SC |= TPM_SC_TOIE_MASK; //Enable Interrupts for the Timer Overflow
               
               //Setup the mod register to get the correct PWM Period
               
               TPM1_MOD = FTM1_CLOCK/(1<<(FTM1_CLK_PRESCALE+1))/FTM1_OVERFLOW_FREQUENCY;
               
               //Setup Channels 0 and 1
               
               TPM1_C0SC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK;
              
               
               //Enable the TPM COunter
               TPM1_SC |= TPM_SC_CMOD(1);
               
               //Enable TPM1 IRQ on the NVIC
               enable_irq (INT_TPM1-16);
              
               //Enable the FTM functions on the the port
               
               PORTB_PCR0 = PORT_PCR_MUX(3);
                              
}

void Move_Servo(int Posicion)
{
	TPM1_C0V=Posicion;
}
