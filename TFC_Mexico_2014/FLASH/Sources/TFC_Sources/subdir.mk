################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/TFC_Sources/Motor.c" \
"../Sources/TFC_Sources/Servo.c" \
"../Sources/TFC_Sources/TFC.c" \
"../Sources/TFC_Sources/TFC_ADC.c" \
"../Sources/TFC_Sources/TFC_ARM_SysTick.c" \
"../Sources/TFC_Sources/TFC_BoardSupport.c" \
"../Sources/TFC_Sources/TFC_CrystalClock.c" \
"../Sources/TFC_Sources/TFC_LineScanCamera.c" \
"../Sources/TFC_Sources/TFC_Queue.c" \
"../Sources/TFC_Sources/TFC_Terminal.c" \
"../Sources/TFC_Sources/TFC_UART.c" \
"../Sources/TFC_Sources/TFC_arm_cm0.c" \
"../Sources/TFC_Sources/TPM2.c" \
"../Sources/TFC_Sources/i2c.c" \

C_SRCS += \
../Sources/TFC_Sources/Motor.c \
../Sources/TFC_Sources/Servo.c \
../Sources/TFC_Sources/TFC.c \
../Sources/TFC_Sources/TFC_ADC.c \
../Sources/TFC_Sources/TFC_ARM_SysTick.c \
../Sources/TFC_Sources/TFC_BoardSupport.c \
../Sources/TFC_Sources/TFC_CrystalClock.c \
../Sources/TFC_Sources/TFC_LineScanCamera.c \
../Sources/TFC_Sources/TFC_Queue.c \
../Sources/TFC_Sources/TFC_Terminal.c \
../Sources/TFC_Sources/TFC_UART.c \
../Sources/TFC_Sources/TFC_arm_cm0.c \
../Sources/TFC_Sources/TPM2.c \
../Sources/TFC_Sources/i2c.c \

OBJS += \
./Sources/TFC_Sources/Motor.o \
./Sources/TFC_Sources/Servo.o \
./Sources/TFC_Sources/TFC.o \
./Sources/TFC_Sources/TFC_ADC.o \
./Sources/TFC_Sources/TFC_ARM_SysTick.o \
./Sources/TFC_Sources/TFC_BoardSupport.o \
./Sources/TFC_Sources/TFC_CrystalClock.o \
./Sources/TFC_Sources/TFC_LineScanCamera.o \
./Sources/TFC_Sources/TFC_Queue.o \
./Sources/TFC_Sources/TFC_Terminal.o \
./Sources/TFC_Sources/TFC_UART.o \
./Sources/TFC_Sources/TFC_arm_cm0.o \
./Sources/TFC_Sources/TPM2.o \
./Sources/TFC_Sources/i2c.o \

C_DEPS += \
./Sources/TFC_Sources/Motor.d \
./Sources/TFC_Sources/Servo.d \
./Sources/TFC_Sources/TFC.d \
./Sources/TFC_Sources/TFC_ADC.d \
./Sources/TFC_Sources/TFC_ARM_SysTick.d \
./Sources/TFC_Sources/TFC_BoardSupport.d \
./Sources/TFC_Sources/TFC_CrystalClock.d \
./Sources/TFC_Sources/TFC_LineScanCamera.d \
./Sources/TFC_Sources/TFC_Queue.d \
./Sources/TFC_Sources/TFC_Terminal.d \
./Sources/TFC_Sources/TFC_UART.d \
./Sources/TFC_Sources/TFC_arm_cm0.d \
./Sources/TFC_Sources/TPM2.d \
./Sources/TFC_Sources/i2c.d \

OBJS_QUOTED += \
"./Sources/TFC_Sources/Motor.o" \
"./Sources/TFC_Sources/Servo.o" \
"./Sources/TFC_Sources/TFC.o" \
"./Sources/TFC_Sources/TFC_ADC.o" \
"./Sources/TFC_Sources/TFC_ARM_SysTick.o" \
"./Sources/TFC_Sources/TFC_BoardSupport.o" \
"./Sources/TFC_Sources/TFC_CrystalClock.o" \
"./Sources/TFC_Sources/TFC_LineScanCamera.o" \
"./Sources/TFC_Sources/TFC_Queue.o" \
"./Sources/TFC_Sources/TFC_Terminal.o" \
"./Sources/TFC_Sources/TFC_UART.o" \
"./Sources/TFC_Sources/TFC_arm_cm0.o" \
"./Sources/TFC_Sources/TPM2.o" \
"./Sources/TFC_Sources/i2c.o" \

C_DEPS_QUOTED += \
"./Sources/TFC_Sources/Motor.d" \
"./Sources/TFC_Sources/Servo.d" \
"./Sources/TFC_Sources/TFC.d" \
"./Sources/TFC_Sources/TFC_ADC.d" \
"./Sources/TFC_Sources/TFC_ARM_SysTick.d" \
"./Sources/TFC_Sources/TFC_BoardSupport.d" \
"./Sources/TFC_Sources/TFC_CrystalClock.d" \
"./Sources/TFC_Sources/TFC_LineScanCamera.d" \
"./Sources/TFC_Sources/TFC_Queue.d" \
"./Sources/TFC_Sources/TFC_Terminal.d" \
"./Sources/TFC_Sources/TFC_UART.d" \
"./Sources/TFC_Sources/TFC_arm_cm0.d" \
"./Sources/TFC_Sources/TPM2.d" \
"./Sources/TFC_Sources/i2c.d" \

OBJS_OS_FORMAT += \
./Sources/TFC_Sources/Motor.o \
./Sources/TFC_Sources/Servo.o \
./Sources/TFC_Sources/TFC.o \
./Sources/TFC_Sources/TFC_ADC.o \
./Sources/TFC_Sources/TFC_ARM_SysTick.o \
./Sources/TFC_Sources/TFC_BoardSupport.o \
./Sources/TFC_Sources/TFC_CrystalClock.o \
./Sources/TFC_Sources/TFC_LineScanCamera.o \
./Sources/TFC_Sources/TFC_Queue.o \
./Sources/TFC_Sources/TFC_Terminal.o \
./Sources/TFC_Sources/TFC_UART.o \
./Sources/TFC_Sources/TFC_arm_cm0.o \
./Sources/TFC_Sources/TPM2.o \
./Sources/TFC_Sources/i2c.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/TFC_Sources/Motor.o: ../Sources/TFC_Sources/Motor.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/TFC_Sources/Motor.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/TFC_Sources/Motor.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/TFC_Sources/Servo.o: ../Sources/TFC_Sources/Servo.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/TFC_Sources/Servo.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/TFC_Sources/Servo.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/TFC_Sources/TFC.o: ../Sources/TFC_Sources/TFC.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/TFC_Sources/TFC.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/TFC_Sources/TFC.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/TFC_Sources/TFC_ADC.o: ../Sources/TFC_Sources/TFC_ADC.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/TFC_Sources/TFC_ADC.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/TFC_Sources/TFC_ADC.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/TFC_Sources/TFC_ARM_SysTick.o: ../Sources/TFC_Sources/TFC_ARM_SysTick.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/TFC_Sources/TFC_ARM_SysTick.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/TFC_Sources/TFC_ARM_SysTick.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/TFC_Sources/TFC_BoardSupport.o: ../Sources/TFC_Sources/TFC_BoardSupport.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/TFC_Sources/TFC_BoardSupport.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/TFC_Sources/TFC_BoardSupport.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/TFC_Sources/TFC_CrystalClock.o: ../Sources/TFC_Sources/TFC_CrystalClock.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/TFC_Sources/TFC_CrystalClock.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/TFC_Sources/TFC_CrystalClock.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/TFC_Sources/TFC_LineScanCamera.o: ../Sources/TFC_Sources/TFC_LineScanCamera.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/TFC_Sources/TFC_LineScanCamera.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/TFC_Sources/TFC_LineScanCamera.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/TFC_Sources/TFC_Queue.o: ../Sources/TFC_Sources/TFC_Queue.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/TFC_Sources/TFC_Queue.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/TFC_Sources/TFC_Queue.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/TFC_Sources/TFC_Terminal.o: ../Sources/TFC_Sources/TFC_Terminal.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/TFC_Sources/TFC_Terminal.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/TFC_Sources/TFC_Terminal.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/TFC_Sources/TFC_UART.o: ../Sources/TFC_Sources/TFC_UART.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/TFC_Sources/TFC_UART.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/TFC_Sources/TFC_UART.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/TFC_Sources/TFC_arm_cm0.o: ../Sources/TFC_Sources/TFC_arm_cm0.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/TFC_Sources/TFC_arm_cm0.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/TFC_Sources/TFC_arm_cm0.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/TFC_Sources/TPM2.o: ../Sources/TFC_Sources/TPM2.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/TFC_Sources/TPM2.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/TFC_Sources/TPM2.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/TFC_Sources/i2c.o: ../Sources/TFC_Sources/i2c.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/TFC_Sources/i2c.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/TFC_Sources/i2c.o"
	@echo 'Finished building: $<'
	@echo ' '


