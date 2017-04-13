/*
 * main implementation: use this 'C' sample to create your own application
 *
 */
#include "derivative.h" /* include peripheral declarations */
#include "TFC/TFC.h"
#include <math.h>
#include "arm_math.h"
#include "FreeRTOS.h"

/* Red RGB LED is on PTB18 */
#define RED             (18)
#define RED_SHIFT       (1<<RED)

#define RED_OFF()       (GPIOB_PSOR = RED_SHIFT)
#define RED_ON()        (GPIOB_PCOR = RED_SHIFT)
#define RED_TOGGLE()    (GPIOB_PTOR = RED_SHIFT)

/* Green RGB LED is on PTB19 */
#define GREEN           (19)
#define GREEN_SHIFT     (1<<GREEN)

#define GREEN_OFF()     (GPIOB_PSOR = GREEN_SHIFT)
#define GREEN_ON()      (GPIOB_PCOR = GREEN_SHIFT)
#define GREEN_TOGGLE()  (GPIOB_PTOR = GREEN_SHIFT)

/* Blue RGB LED is on PTD1 */
#define BLUE            (1)
#define BLUE_SHIFT      (1<<BLUE)

#define BLUE_OFF()      (GPIOD_PSOR = BLUE_SHIFT)
#define BLUE_ON()       (GPIOD_PCOR = BLUE_SHIFT)
#define BLUE_TOGGLE()   (GPIOD_PTOR = BLUE_SHIFT)

float32_t RawData[128];
float32_t Out[134];
float32_t Edge[134];
float32_t LeftHalf[67];
float32_t RightHalf[67];
float32_t DoG[7]={0.0333f,0.2707f,0.6065f,0.0f,-0.6065f,-0.2707f,-0.0333f};
float32_t LeftMax, RightMax;
uint32_t LeftIndex, RightIndex;
int32_t Error = 0;
uint32_t i = 0;

static void InitLED(void) {
  /* Turn on clock to PortB (red and green led) and PortD (blue led) module */
  SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK|SIM_SCGC5_PORTD_MASK;

  /* Set the PTB18 pin multiplexer to GPIO mode */
  PORTB_PCR18 = PORT_PCR_MUX(1);

  /* Set the PTB19 pin multiplexer to GPIO mode */
  PORTB_PCR19 = PORT_PCR_MUX(1);

  /* Set the PTD1 pin multiplexer to GPIO mode */
  PORTD_PCR1 = PORT_PCR_MUX(1);

  /* Set the initial output state to high */
  GPIOB_PSOR |= RED_SHIFT;
  GPIOB_PSOR |= GREEN_SHIFT;
  GPIOD_PSOR |= BLUE_SHIFT;

  /* Set the pins direction to output */
  GPIOB_PDDR |= RED_SHIFT;
  GPIOB_PDDR |= GREEN_SHIFT;
  GPIOD_PDDR |= BLUE_SHIFT;
}

static portTASK_FUNCTION(MainTask, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    
	if(LineScanImageReady==1)
    {
    	for(i=0;i<128;i++) RawData[i]=(float32_t)LineScanImage0[i];	//Float Parser
    	arm_conv_f32(RawData,128,DoG,7,Out);
    	arm_abs_f32(Out,Edge,134);
    	for(i=0;i<67;i++) LeftHalf[i]=Edge[i];
    	for(i=67;i<134;i++) RightHalf[i]=Edge[i];
    	arm_max_f32(LeftHalf, 67, &LeftMax, &LeftIndex);
    	arm_max_f32(RightHalf, 67, &RightMax, &RightIndex);
    	Error = ((LeftIndex+RightIndex)/2)-67;
    	LineScanImageReady=0;
    }
    
    vTaskDelay(20/portTICK_RATE_MS);
  }
}

static portTASK_FUNCTION(Task2, pvParameters) {
  (void)pvParameters; /* parameter not used */
  for(;;) {
    BLUE_TOGGLE();
    
    vTaskDelay(20/portTICK_RATE_MS);
  }
}


int main(void) {
  InitLED();
  TFC_Init();	
  
  RED_ON();
  RED_OFF();
  RED_TOGGLE();
  RED_OFF();
  
  GREEN_ON();
  GREEN_OFF();
  GREEN_TOGGLE();
  GREEN_OFF();

  BLUE_ON();
  BLUE_OFF();
  BLUE_TOGGLE();
  BLUE_OFF();

  if (xTaskCreate(
        MainTask,  /* pointer to the task */
        "Main", /* task name for kernel awareness debugging */
        configMINIMAL_STACK_SIZE, /* task stack size */
        (void*)NULL, /* optional task startup argument */
        tskIDLE_PRIORITY,  /* initial priority */
        (xTaskHandle*)NULL /* optional task handle to create */
      ) != pdPASS) {
    /*lint -e527 */
    for(;;){}; /* error! probably out of memory */
    /*lint +e527 */
  }
  if (xTaskCreate(
          Task2,  /* pointer to the task */
          "job2", /* task name for kernel awareness debugging */
          configMINIMAL_STACK_SIZE, /* task stack size */
          (void*)NULL, /* optional task startup argument */
          tskIDLE_PRIORITY,  /* initial priority */
          (xTaskHandle*)NULL /* optional task handle to create */
        ) != pdPASS) {
      /*lint -e527 */
      for(;;){}; /* error! probably out of memory */
      /*lint +e527 */
    }
  vTaskStartScheduler(); /* does not return */
	return 0;
}
