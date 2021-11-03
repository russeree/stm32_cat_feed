/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @author: Reese Russell (russeree)
  * @version: Alpha 0.0.1
  * @platform: [base : STM32F746 Discovery]
  * @desc: see readme.md
  * @license:
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "cmsis_os.h"
#include "crc.h"
#include "dma.h"
#include "dma2d.h"
#include "fatfs.h"
#include "i2c.h"
#include "ltdc.h"
#include "rng.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fmc.h"
#include "app_touchgfx.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "coinemu.h"
#include "stdio.h"
#include "string.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "coinemu_flash.h"
#include "coinemu_crypto.h"
#include "coinemu_sd.h"
#include "coinemu_rng.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_qspi.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */


/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/**
 * @Desc:ONE TIME PROGRAM MEMORY (STM32F7 SUDO EEPROM) uses the a custom scatter file built by me.
 * This memory is programmed onto the device then overwrote on the first power up. All state variables are
 * deliberately created and documented here
 */
__attribute__((section(".user_eeprom"))) volatile CoinEmuEEPROM flashCES = {
		{
			_EMU_INIT_UNINIT,     //CoinEmu on Boot always is not initialized. CoinEmu Updates this once the it has finished it's initialization sequence. !!!FIXME: CEMU: Switch from #define to ENUM!!!
			firstUse,             //One time program state, this memory location once the device is powered on is flashed forever and can not be overwrote.
			{
				_EMU_MAX_TRIES,   // -1- This is the MAX pin input tries.... It is written 4 times in a row and the data is checked against the others for write errors the last thing anyone would want is a failed or botched wrote to destory your chances at getting your bitcoin back (though you should have a paper wallet backup)
				_EMU_MAX_TRIES,   // -2- Sanity check for pin pad entry
				_EMU_MAX_TRIES,   // -3- Sanity check for pin pad entries
				_EMU_MAX_TRIES    // -4- Sanity check for pin pad entries
			},
			scrUnlock,            //(CURRENT SCREEN)The first screen on any boot is always the unlock screen DO NOT DISABLE
			scrBeginSetup,        //(NEXT SCREEN) The next screen to be displayed this is a hint, not all code will use this variable to determine the next screen.
		},
		{}
};

/* Wallets and pins stored in memory !!!ENCRYPT: AES256!!! - NO INIT ON PROGRAMMING */


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
PinPadEntry     ppe;             //Coinemu pin pad entry driver
CoinemuConfig   cec;             //Coinemu config
CoinemuStatus   ces;             //Coinemu Status Structure - Used to control the state of the coinemu device
CoinemuHardware ceh;             //Coinemu Hardware Stucture - Used to determine active hardware features - Full Init Required for true value
CoinemuSdDriver cesd;            //Coinemu SD Card Driver - !!!FIXME: CEMU: SD CARD Driver does not work correctly with FreeRTOS!!!
/*--- CRYPTO AND RNG DRIVERS ---*/
EmuSha256       emuSha256;       //Coinemu SHA256 - Coinemu SHA256 Engine Driver
EmuSha512HMAC   emuSha512HMAC;   //Coinemu SHA512HMAC - Coinemu SHA256 Engine Driver
BlockEmuRNG     bemurng;         //Coinemu RNG - Random number generator driver
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
#ifdef DEBUG
  DBGMCU->APB1FZ |= DBGMCU_APB1_FZ_DBG_TIM6_STOP; //Stop the debug clock
#endif
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  EMU_QUADSPI_TOUCHGFX_Init(); //User created QSPI function since the BSP version for the STM32F746 Discovery does not work correctly.
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_CRC_Init();
  MX_RNG_Init();
  MX_DMA2D_Init();
  MX_LTDC_Init();
  MX_FMC_Init();
  MX_TIM3_Init();
  MX_I2C3_Init();
  MX_USART6_UART_Init();
  MX_TouchGFX_Init();
  /* USER CODE BEGIN 2 */
  emuEepromLoad();      //Burn the eeprom upon first device boot ever - This will notify the user that their device is new and unmodified
  BSP_LCD_Init();       //Custom LCD init function becuase the STM BSP one does not work properly
  BSP_LCD_DisplayOn();  //Turn on the LCD
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();
  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 400;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC|RCC_PERIPHCLK_USART6
                              |RCC_PERIPHCLK_I2C3|RCC_PERIPHCLK_SDMMC1
                              |RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 384;
  PeriphClkInitStruct.PLLSAI.PLLSAIR = 5;
  PeriphClkInitStruct.PLLSAI.PLLSAIQ = 2;
  PeriphClkInitStruct.PLLSAI.PLLSAIP = RCC_PLLSAIP_DIV8;
  PeriphClkInitStruct.PLLSAIDivQ = 1;
  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_8;
  PeriphClkInitStruct.Usart6ClockSelection = RCC_USART6CLKSOURCE_PCLK2;
  PeriphClkInitStruct.I2c3ClockSelection = RCC_I2C3CLKSOURCE_PCLK1;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLLSAIP;
  PeriphClkInitStruct.Sdmmc1ClockSelection = RCC_SDMMC1CLKSOURCE_CLK48;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/**
 * @desc: First boot burn and variable loading function
 */
void emuEepromLoad(void){
	/* Make a Copy of the EEPROM in RAM for use */
	eepromToRam();
	/* Default Configuration Upon Boot */
	ces = coinEmuInRamEEPROM->ces;   //Get the struct from memory -> Uses the reference from above for a 'pointer'
	ces.init = _EMU_INIT_SUCCESS;    //CoinEMU is active and running - Init complete
	ces.nxtScreen = scrBeginSetup;   //Begin Setup Screen
	cec.setup.setup = true;          //Device is in the process being setup;
	cec.setup.stage = PinSetupPart1; //Config is to request a setup of the device
	/* Now setup the boot menus and stages for the GUI */
	switch(ces.bootConfigStatus){
		case firstUse: //Device first power on after programming
			printf("%s", "Burning EEPROM firstuse fuse \n\r");
			writeFirstUseFuse();           //FIRST USE - BURN THOSE FUSES -
			ces.nxtScreen = scrFirstUse;
			break;
		case configured:
			printf("%s", "Device is configured - Loading the main menu \n\r");
			cec.setup.setup = false;      //The device is not in a setup stage since it has been configured.
			cec.setup.stage = Undefined;  //No Stages to load - Setups etc...
			ces.nxtScreen = scrWelcome;   //Main Menu
			break;
		default:
			break;
	}
}

/**
 * @desc: The LCD has been configured earlier - use this to override the BSP setup
 **/
void BSP_LCD_ClockConfig(LTDC_HandleTypeDef *hltdc, void *Params){
	return;
}

#ifdef _EMU_UART
/**
 * @desc: _write printf function to the USART over DMA
 */
int _write(int file, char *ptr, int len) {
	HAL_UART_Transmit(&huart6, (uint8_t *) ptr, len, HAL_MAX_DELAY);
	return len;
}
#endif


#ifdef _EMU_VCP
/**
 * @desc: This printf _write will output to the Virtual Com Port On the USB(HS) Channel
 */
int _write(int file, char *ptr, int len) {
	if(coinEmuUsbConnected){
		//vTaskSuspendAll(); //Lock context switching before printing to avoid hard fault
		CDC_Transmit_HS((uint8_t*) ptr, len);
		//xTaskResumeAll();
	}
	return len;
}
#endif

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
