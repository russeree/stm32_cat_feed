################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/AbstractDataGraph.cpp \
../Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphElements.cpp \
../Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphLabels.cpp \
../Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphScroll.cpp \
../Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphWrapAndClear.cpp \
../Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphWrapAndOverwrite.cpp 

OBJS += \
./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/AbstractDataGraph.o \
./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphElements.o \
./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphLabels.o \
./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphScroll.o \
./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphWrapAndClear.o \
./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphWrapAndOverwrite.o 

CPP_DEPS += \
./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/AbstractDataGraph.d \
./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphElements.d \
./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphLabels.d \
./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphScroll.d \
./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphWrapAndClear.d \
./Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/GraphWrapAndOverwrite.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/%.o: ../Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/%.cpp Middlewares/ST/touchgfx/framework/source/touchgfx/widgets/graph/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/Components/ft5336 -I../Drivers/BSP/STM32746G-Discovery -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

