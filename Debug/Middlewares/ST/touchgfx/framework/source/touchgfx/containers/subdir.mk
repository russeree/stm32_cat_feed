################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Middlewares/ST/touchgfx/framework/source/touchgfx/containers/CacheableContainer.cpp \
../Middlewares/ST/touchgfx/framework/source/touchgfx/containers/Container.cpp \
../Middlewares/ST/touchgfx/framework/source/touchgfx/containers/ListLayout.cpp \
../Middlewares/ST/touchgfx/framework/source/touchgfx/containers/ModalWindow.cpp \
../Middlewares/ST/touchgfx/framework/source/touchgfx/containers/ScrollableContainer.cpp \
../Middlewares/ST/touchgfx/framework/source/touchgfx/containers/SlideMenu.cpp \
../Middlewares/ST/touchgfx/framework/source/touchgfx/containers/Slider.cpp \
../Middlewares/ST/touchgfx/framework/source/touchgfx/containers/SwipeContainer.cpp \
../Middlewares/ST/touchgfx/framework/source/touchgfx/containers/ZoomAnimationImage.cpp 

OBJS += \
./Middlewares/ST/touchgfx/framework/source/touchgfx/containers/CacheableContainer.o \
./Middlewares/ST/touchgfx/framework/source/touchgfx/containers/Container.o \
./Middlewares/ST/touchgfx/framework/source/touchgfx/containers/ListLayout.o \
./Middlewares/ST/touchgfx/framework/source/touchgfx/containers/ModalWindow.o \
./Middlewares/ST/touchgfx/framework/source/touchgfx/containers/ScrollableContainer.o \
./Middlewares/ST/touchgfx/framework/source/touchgfx/containers/SlideMenu.o \
./Middlewares/ST/touchgfx/framework/source/touchgfx/containers/Slider.o \
./Middlewares/ST/touchgfx/framework/source/touchgfx/containers/SwipeContainer.o \
./Middlewares/ST/touchgfx/framework/source/touchgfx/containers/ZoomAnimationImage.o 

CPP_DEPS += \
./Middlewares/ST/touchgfx/framework/source/touchgfx/containers/CacheableContainer.d \
./Middlewares/ST/touchgfx/framework/source/touchgfx/containers/Container.d \
./Middlewares/ST/touchgfx/framework/source/touchgfx/containers/ListLayout.d \
./Middlewares/ST/touchgfx/framework/source/touchgfx/containers/ModalWindow.d \
./Middlewares/ST/touchgfx/framework/source/touchgfx/containers/ScrollableContainer.d \
./Middlewares/ST/touchgfx/framework/source/touchgfx/containers/SlideMenu.d \
./Middlewares/ST/touchgfx/framework/source/touchgfx/containers/Slider.d \
./Middlewares/ST/touchgfx/framework/source/touchgfx/containers/SwipeContainer.d \
./Middlewares/ST/touchgfx/framework/source/touchgfx/containers/ZoomAnimationImage.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/touchgfx/framework/source/touchgfx/containers/%.o: ../Middlewares/ST/touchgfx/framework/source/touchgfx/containers/%.cpp Middlewares/ST/touchgfx/framework/source/touchgfx/containers/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/Components/ft5336 -I../Drivers/BSP/STM32746G-Discovery -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

