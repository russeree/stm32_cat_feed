################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Middlewares/ST/touchgfx/framework/source/touchgfx/containers/clock/AbstractClock.cpp \
../Middlewares/ST/touchgfx/framework/source/touchgfx/containers/clock/AnalogClock.cpp \
../Middlewares/ST/touchgfx/framework/source/touchgfx/containers/clock/DigitalClock.cpp 

OBJS += \
./Middlewares/ST/touchgfx/framework/source/touchgfx/containers/clock/AbstractClock.o \
./Middlewares/ST/touchgfx/framework/source/touchgfx/containers/clock/AnalogClock.o \
./Middlewares/ST/touchgfx/framework/source/touchgfx/containers/clock/DigitalClock.o 

CPP_DEPS += \
./Middlewares/ST/touchgfx/framework/source/touchgfx/containers/clock/AbstractClock.d \
./Middlewares/ST/touchgfx/framework/source/touchgfx/containers/clock/AnalogClock.d \
./Middlewares/ST/touchgfx/framework/source/touchgfx/containers/clock/DigitalClock.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/touchgfx/framework/source/touchgfx/containers/clock/%.o: ../Middlewares/ST/touchgfx/framework/source/touchgfx/containers/clock/%.cpp Middlewares/ST/touchgfx/framework/source/touchgfx/containers/clock/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/Components/ft5336 -I../Drivers/BSP/STM32746G-Discovery -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
