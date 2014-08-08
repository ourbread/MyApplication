################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Sources/main.cpp \

CPP_SRCS_QUOTED += \
"../Sources/main.cpp" \

OBJS += \
./Sources/main.o \

OBJS_QUOTED += \
"./Sources/main.o" \

CPP_DEPS_QUOTED += \
"./Sources/main.d" \

CPP_DEPS += \
./Sources/main.d \

OBJS_OS_FORMAT += \
./Sources/main.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/main.o: ../Sources/main.cpp
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C++ Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-g++" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '


