/*
 * random_seed_gen.h
 *
 *  Created on: Jan 16, 2021
 *      Author: Reese
 */

#ifndef INC_COINEMU_RNG_H_
#define INC_COINEMU_RNG_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"              //Includes all of the main components needed
#include "cmsis_os.h"          //Needed for the semaphore object used for the PinPad
#include "coinemu.h"           //CoinEmu Basic Building Blocks

/*--- External Semaphores ***/
extern osSemaphoreId_t pinPadSemaphoreHandle;
extern osSemaphoreId_t randGenSemaphoreHandle;
extern osSemaphoreId_t pinPadGenReqSemaphoreHandle;

typedef struct BlockEmuRNG {
	uint32_t  version;         //Internal Debug-Sanity Check
	CEMU      status;          //Current Status
	uint8_t   rngValid;        //Is the Random Number Generator Currently Valid
	uint32_t  lastRandomGen;   //The last random generation
	uint32_t  totalRandomGens; //The total number of random generations
	uint8_t   pinPadInit;      //Has the pin pad been initialized - Do not increment this unless you want to generate another pin pad
	uint8_t   pinPadGen;       //Currently Generating Numbers for the Pinpad
	uint8_t   pinPad[10];      //The 10 Digits for the PinPad Randomized
	/* Non Pin-Pad RNG Variables FREE-RTOS is needed*/
	uint32_t* entropyArr;      //A pointer to memory where a random number needs to be placed
	uint32_t  entropyArrSize;  //Request a number of generations
	uint32_t  entropyArrGens;  //Number of gens of 32 bits of entropy that have been successful
	bool      entropyValid;    //Is the current entropy set valid?
} BlockEmuRNG;

CEMU getEntropy(int bits);
CEMU pinPadPadRNGReadyCheck(void);
void initBlockEmuRng(BlockEmuRNG *rng);
void pinPadRNG(void);

#endif /* INC_COINEMU_RNG_H_ */
