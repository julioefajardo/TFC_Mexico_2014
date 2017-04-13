#ifndef TFC_PWM_SERVO_H_
#define TFC_PWM_SERVO_H_

void Init_Servo();
void Move_Servo(uint8_t ServoNumber, float Position);
void TFC_SetServoDutyCycle(uint8_t ServoNumber, float DutyCycle);

#endif /* TFC_PWM_SERVO_H_ */
