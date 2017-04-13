#include "TFC_Headers\TFC.h"
#include "derivative.h"
uint32_t Cuentas;
uint32_t Temporal;
uint32_t Cuentas2;
uint32_t Temporal2;

void Init_TPM2(void){			  
  SIM_SCGC6 |= SIM_SCGC6_TPM2_MASK;
  //revisar si esta
  
  PORTA_PCR1 = (uint32_t)((PORTA_PCR1 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x04)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x03)
               ));
  PORTA_PCR2 = (uint32_t)((PORTA_PCR2 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x04)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x03)
               ));
			   
  TPM2_SC = (TPM_SC_CMOD(0x00) | TPM_SC_PS(0x00));
  TPM2_C0SC = (TPM_CnSC_CHIE_MASK | TPM_CnSC_ELSA_MASK);
  TPM2_C1SC = (TPM_CnSC_CHIE_MASK | TPM_CnSC_ELSA_MASK);
  TPM2_CONF &= (uint32_t)~(uint32_t)(
                TPM_CONF_CROT_MASK |
                TPM_CONF_CSOO_MASK |
                TPM_CONF_CSOT_MASK |
                TPM_CONF_GTBEEN_MASK |
                TPM_CONF_DBGMODE(0x03) |
                TPM_CONF_DOZEEN_MASK
               );
  TPM2_MOD |= TPM_MOD_MOD(0xFFFF);
  TPM2_C0V &= (uint32_t)~(uint32_t)(0xFFFF0000U);
  TPM2_C1V &= (uint32_t)~(uint32_t)(0xFFFF0000U);
  TPM2_SC = (uint32_t)((TPM2_SC & (uint32_t)~(uint32_t)(
             TPM_SC_DMA_MASK |
             TPM_SC_TOF_MASK |
             TPM_SC_TOIE_MASK |
             TPM_SC_CPWMS_MASK |
             TPM_SC_CMOD(0x02)
            )) | (uint32_t)(
             TPM_SC_CMOD(0x01) |
             TPM_SC_PS(0x07)
            ));
  enable_irq(INT_TPM2-16);
  
}

void FTM2_IRQHandler(void)
{
	if (TPM2_STATUS&TPM_STATUS_CH0F_MASK)
	{
		Cuentas=TPM2_C0V-Temporal;
		Temporal=TPM2_C0V;
		TPM2_C0SC |= (0x80);//reset interrupt flag
	}
	if (TPM2_STATUS&TPM_STATUS_CH1F_MASK){
		Cuentas2=TPM2_C1V-Temporal2;
		Temporal2=TPM2_C1V;		
		TPM2_C1SC |= (0x80);//reset interrupt flag
	}
}
