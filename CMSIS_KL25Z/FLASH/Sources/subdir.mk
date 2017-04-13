################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/arm_sin_cos_example_f32.c" \
"../Sources/sa_mtb.c" \

C_SRCS += \
../Sources/arm_sin_cos_example_f32.c \
../Sources/sa_mtb.c \

OBJS += \
./Sources/arm_sin_cos_example_f32.o \
./Sources/sa_mtb.o \

C_DEPS += \
./Sources/arm_sin_cos_example_f32.d \
./Sources/sa_mtb.d \

OBJS_QUOTED += \
"./Sources/arm_sin_cos_example_f32.o" \
"./Sources/sa_mtb.o" \

C_DEPS_QUOTED += \
"./Sources/arm_sin_cos_example_f32.d" \
"./Sources/sa_mtb.d" \

OBJS_OS_FORMAT += \
./Sources/arm_sin_cos_example_f32.o \
./Sources/sa_mtb.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/arm_sin_cos_example_f32.o: ../Sources/arm_sin_cos_example_f32.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/arm_sin_cos_example_f32.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/arm_sin_cos_example_f32.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/sa_mtb.o: ../Sources/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/sa_mtb.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '


