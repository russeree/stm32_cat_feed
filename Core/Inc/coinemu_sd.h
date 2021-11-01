/*
 * coinemu_sd.h
 *
 *  Created on: Jun 5, 2021
 *      Author: Reese
 */

#ifndef INC_COINEMU_SD_H_
#define INC_COINEMU_SD_H_

#include "main.h"
#include "FreeRTOS.h"
#include "fatfs.h"
#include "task.h"
#include "cmsis_os.h"
#include "stdbool.h"
#include "coinemu.h"

/* Different Status Elements of the CoinEmu SD Status */
typedef enum {
	Fail,
	Uninitialized,
	NoSdCard,
	Initialized,
	ReadSuccess,
	WriteSuccess
}SD_Status;

typedef enum {
	SD_Fail,
	SD_Success
}SD_Return;


typedef struct{
	bool rtosInit;     //Make sure that the rtos scheduler is running
	bool sdInserted;   //Modify this with the FreeROTS Daemon.
	bool sdMounted;    //The SD card has been mounted upon the init.
	bool sdCompatible; //Make sure the card is compatible
	FIL curFile;
	FRESULT res;
	SD_Status status;
} CoinemuSdDriver;

extern CoinemuSdDriver cesd;

SD_Return initCoinEmuSDInterface(void);
FRESULT sdMountErrorHandler(FRESULT fres);

#endif /* INC_COINEMU_SD_H_ */
