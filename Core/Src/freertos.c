/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "coinemu.h"
#include "string.h"
#include "usart.h"
#include "fatfs.h"
#include "sdmmc.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"
/*--- COINEMU INCLUDES ---*/
#include "coinemu_rng.h"
#include "coinemu_print.h"
#include "coinemu_sd.h"
#include "coinemu_qr.h"
/*--- Additional FreeRTOS Includes ---*/
#include "queue.h"
#include "task.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
/* USER CODE BEGIN PTD */
typedef StaticTask_t osStaticThreadDef_t;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
extern BlockEmuRNG bemurng;
/*--- RNG MessageQ Used to communicate the status of the ---*/
xQueueHandle rngMsq; //The Queue for the state of the RNG Object
/* TouchGFX Graphics Task */
uint32_t TouchGFXTaskBuffer[4096];
osStaticThreadDef_t TouchGFXTaskControlBlock;
osThreadId_t TouchGFXHandle;
const osThreadAttr_t TouchGFXTask_attributes = {
  .name = "TouchGFXTask",
  .stack_mem = &TouchGFXTaskBuffer[0],
  .stack_size = sizeof(TouchGFXTaskBuffer),
  .cb_mem = &TouchGFXTaskControlBlock,
  .cb_size = sizeof(TouchGFXTaskControlBlock),
  .priority = (osPriority_t) osPriorityLow,
};

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for emuSDcardDaemon */
osThreadId_t emuSDcardDaemonHandle;
uint32_t emuSDcardDaemonBuffer[ 4096 ];
osStaticThreadDef_t emuSDcardDaemonControlBlock;
const osThreadAttr_t emuSDcardDaemon_attributes = {
  .name = "emuSDcardDaemon",
  .cb_mem = &emuSDcardDaemonControlBlock,
  .cb_size = sizeof(emuSDcardDaemonControlBlock),
  .stack_mem = &emuSDcardDaemonBuffer[0],
  .stack_size = sizeof(emuSDcardDaemonBuffer),
  .priority = (osPriority_t) osPriorityRealtime7,
};
/* Definitions for pinPadSemaphore */
osSemaphoreId_t pinPadSemaphoreHandle;
const osSemaphoreAttr_t pinPadSemaphore_attributes = {
  .name = "pinPadSemaphore"
};
/* Definitions for randGenSemaphore */
osSemaphoreId_t randGenSemaphoreHandle;
const osSemaphoreAttr_t randGenSemaphore_attributes = {
  .name = "randGenSemaphore"
};
/* Definitions for pinPadGenReqSemaphore */
osSemaphoreId_t pinPadGenReqSemaphoreHandle;
const osSemaphoreAttr_t pinPadGenReqSemaphore_attributes = {
  .name = "pinPadGenReqSemaphore"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
extern void TouchGFX_Task(void *argument);
void RTOS_TouchGFX_Task(void *argument);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void sdDaemon(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationIdleHook(void);
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);
void vApplicationMallocFailedHook(void);

/* USER CODE BEGIN 2 */
void vApplicationIdleHook( void )
{
   /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
   to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
   task. It is essential that code added to this hook function never attempts
   to block in any way (for example, call xQueueReceive() with a block time
   specified, or call vTaskDelay()). If the application makes use of the
   vTaskDelete() API function (as this demo application does) then it is also
   important that vApplicationIdleHook() is permitted to return to its calling
   function, because it is the responsibility of the idle task to clean up
   memory allocated by the kernel to any task that has since been deleted. */
}
/* USER CODE END 2 */

/* USER CODE BEGIN 4 */
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName)
{
   /* Run time stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
   called if a stack overflow is detected. */
}
/* USER CODE END 4 */

/* USER CODE BEGIN 5 */
void vApplicationMallocFailedHook(void)
{
   /* vApplicationMallocFailedHook() will only be called if
   configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h. It is a hook
   function that will get called if a call to pvPortMalloc() fails.
   pvPortMalloc() is called internally by the kernel whenever a task, queue,
   timer or semaphore is created. It is also called by various parts of the
   demo application. If heap_1.c or heap_2.c are used, then the size of the
   heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
   FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
   to query the size of free heap space that remains (although it does not
   provide information on how the remaining heap might be fragmented). */
}
/* USER CODE END 5 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of pinPadSemaphore */
  pinPadSemaphoreHandle = osSemaphoreNew(1, 1, &pinPadSemaphore_attributes);

  /* creation of randGenSemaphore */
  randGenSemaphoreHandle = osSemaphoreNew(1, 1, &randGenSemaphore_attributes);

  /* creation of pinPadGenReqSemaphore */
  pinPadGenReqSemaphoreHandle = osSemaphoreNew(1, 1, &pinPadGenReqSemaphore_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  osSemaphoreAcquire(pinPadSemaphoreHandle, 0);
  osSemaphoreAcquire(randGenSemaphoreHandle, 0);
  osSemaphoreAcquire(pinPadGenReqSemaphoreHandle, 0);
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  rngMsq = xQueueGenericCreate(1, 1, 0); //Create the Message Queue for the RNG status to GUI Commuication
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of emuSDcardDaemon */
  emuSDcardDaemonHandle = osThreadNew(sdDaemon, NULL, &emuSDcardDaemon_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  TouchGFXHandle = osThreadNew(RTOS_TouchGFX_Task, NULL, &TouchGFXTask_attributes);
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
	printf("%s","\r\nWelcome to BlockEmu 0.1a\r\n");
	ceh.emuFreeRtos = true;
	MX_USB_DEVICE_Init();
	ceh.emuUSB_HS = true;
	initBlockEmuRng(&bemurng);
	pinPadRNG();
	qrTestGen();
	/* Infinite loop */
	for(;;)
	{
		printf("%s","BlockEmu Heartbeat\r\n");
		/* Update the status of the RNG Hardware Module */
		xQueueSend(rngMsq, &ceh.emuRNG, 0);
		osDelay(_EMU_RTOS_LONG_DELAY);
	}
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_sdDaemon */
/**
* @brief Function implementing the emuSDcardDaemon thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_sdDaemon */
void sdDaemon(void *argument)
{
  /* USER CODE BEGIN sdDaemon */
	MX_SDMMC1_SD_Init();
	BSP_SD_Init();
	MX_FATFS_Init();
	ceh.emuSD = true;
	/* Infinite loop */
	for(;;){
		/* Let the coinemu SD driver know that a card has been inserted */
		if(!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)){
			if(!cesd.sdInserted){
				cesd.sdInserted = true;
				initCoinEmuSDInterface();
			}
			cesd.sdInserted = true;
			HAL_GPIO_WritePin(GPIOI, GPIO_PIN_1, GPIO_PIN_SET);
		}
		else{
			cesd.sdInserted = false;
			HAL_GPIO_WritePin(GPIOI, GPIO_PIN_1, GPIO_PIN_RESET);
		}
	osDelay(_EMU_RTOS_SD_DAEMON_DELAY);
	}
  /* USER CODE END sdDaemon */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void RTOS_TouchGFX_Task(void *argument)
{
	TouchGFX_Task(NULL);
	/* USER CODE BEGIN StartDefaultTask */
	/* Infinite loop */
	for(;;)
	{
		osDelay(_EMU_RTOS_LONG_DELAY);
	}
	/* USER CODE END StartDefaultTask */
}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
