/*
 * mma8451.h
 *
 *  Created on: Oct 18, 2012
 *      Author: B34443
 */

#ifndef MMA8451_H_
#define MMA8451_H_

#include "derivative.h" /* include peripheral declarations */
#include "i2c.h"

#define MMA8451_I2C_ADDRESS (0x1d<<1)
#define I2C0_B  I2C0_BASE_PTR

void mma8451_init(void); //prepare I2C port
uint16_t mma8451_read_reg(uint8_t addr);
void mma8451_write_reg(uint8_t addr, uint8_t data);
uint16_t mma8451_test_reg_rw(void);
void mma8451_test_function(void);


#endif /* MMA8451_H_ */
