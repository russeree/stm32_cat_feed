/*
 * coinemu_sd.c
 *
 *  Created on: Jun 5, 2021
 *      Author: Reese
 */
#include "coinemu_sd.h"

CoinemuSdDriver CEMU_SD;

/* Initializes the SDCard Library for CoinEmu */
SD_Return initCoinEmuSDInterface(void){
	osDelay(100); //Give the SD card a moment to debounce;
	/* Check is the FreeRTOS scheduler is running */
	if(xTaskGetSchedulerState() != taskSCHEDULER_RUNNING){
		CEMU_SD.rtosInit = false;
		return SD_Fail; //If the scheduler is not running or suspended at the time of init just fail
	}
	else{
		CEMU_SD.rtosInit = true;
	}
	/* Check if the SD Card is inserted and USB is Enabled */
	if(!cesd.sdInserted){
		return SD_Fail; //Fail is there is no SD Card Inserted #Polled every 250MS by FreeRTOS
	}
	uint8_t buffer[_MAX_SS]; /* a work buffer for the f_mkfs() */
	printf("%s","Now Mounting an SD Card.\n\r");
	FRESULT x = f_mount(&SDFatFS, (TCHAR const*)SDPath, 1);
	  if(x != FR_OK)
	  {
	      /* FatFs Initialization Error */
		  printf("%s","Failed to Mount SD Card");
	  }
	  x = f_mkfs((TCHAR const*)SDPath, FM_ANY, 0, buffer, _MAX_SS);
	  if(x != FR_OK)
	  {
		  printf("%s","Failed to Format SD Card");
	      /* FatFs Format Error */
	  }
	  else{
		  osDelay(1000);
		  x = f_mount(NULL, (TCHAR const*)SDPath, 1);
		  osDelay(1000);

		  x = f_mount(&SDFatFS, (TCHAR const*)SDPath, 1);
	  }
	  if(x != FR_OK)
	  {
		  printf("%s","Failed to open file on SD Card");
	      /* 'STM32.TXT' file Open for write Error */
	  }
	  f_close(&SDFile);

	/* SD Card is inserted time to init the card an verify it is a CoinEMU valid
	if(sdMountErrorHandler(f_mount(&SDFatFS, (TCHAR const*)SDPath, 0)) == FR_OK){
		CEMU_SD.sdMounted = true;
		BYTE work[_MAX_SS]; // Work area (larger is better for processing time)
		FRESULT x;
		uint8_t rtext[_MAX_SS];// File read buffer
		x = f_mkfs("", FM_ANY, 0, work, sizeof(work));
		x = f_mkdir("bitcoin");
		if(x = FR_OK){
			return SD_Success;
		}
	}
	*/
	/* Notify CoinEmu hardware that the SDcard is functioning correctly */
	ceh.emuSD = true;
	/* If the function makes it though everything - Then return to the use that it was a success */
	return SD_Success;
}

/**
 * @desc: Handles Mounting for the SD card
 * @note: The most common being that the SD card is not formatted correctly or has a corrupt file system
 **/
FRESULT sdMountErrorHandler(FRESULT fres){
	switch(fres){
		case FR_OK: //Everything is working as normal and the sd-card was mounted successfuly
			cesd.sdCompatible = FR_OK;
			break;
		case FR_NO_FILESYSTEM: //No filesystem was found
			ceh.emuSD =  FR_NO_FILESYSTEM;
			break;
		default:
			break;
	}
	return fres;
}
