/*
 * random_seed_gen.c
 *
 *  Created on: Jan 16, 2021
 *      Author: Reese
 */

#include <coinemu_rng.h> //RNG Functions and Types
#include "stm32f7xx_hal_rng.h" //Random number generator hardware support
#include "stdlib.h"
#include "math.h"              //Math functions, these are useful because they are more proven than anything I will build
/*--- FreeRTOS Intergration ---*/
#include "queue.h"
#include "task.h"

extern RNG_HandleTypeDef hrng;
extern BlockEmuRNG bemurng; //The Block EMU RNG Struct
extern xQueueHandle rngMsq;

/**
 * @desc: This is the initialization function for the HAL RNG Peripheral for the BlockEMU
 * Wallet. There are several methods to enable here and keep track of variables.
 * @state: Beta !!!NEEDS REVIEW!!!
 */
void initBlockEmuRng(BlockEmuRNG *rng){
	//Init the HAL RNG Layer
	if(HAL_RNG_Init(&hrng) != HAL_OK){
		rng->status = FAIL;
		return;
	}
	//Setup the Random Seed Structure
	rng->version = 003;
	rng->status = PASS;
	rng->totalRandomGens = 0;
	rng->pinPadInit = false;
	//Generate some random numbers to start
	ceh.emuRNG = true;
}

/**
 * @desc: This is the data ready handler for the RNGEMU
 **/
void HAL_RNG_ReadyDataCallback(RNG_HandleTypeDef *hrng, uint32_t random32bit){
	bemurng.rngValid = 1;                                                 //The Random Number Generator is valid.
	bemurng.lastRandomGen = random32bit;                                  //This is the 32 bit number that was returned by the random number generator
	bemurng.totalRandomGens += 1;                                         //Increment the the number of times the random number generator has created a number
	/* If there has been a request to generate a pin pad randomly */
	if(osSemaphoreAcquire(pinPadGenReqSemaphoreHandle, 0) == osOK){
		if(bemurng.pinPadGen > 0){                                        //If if there are pin numbers that need to be generated generate them
			uint32_t _pinKey = random32bit%10;                            //Get the value of the key that you are trying to insert into the array
			uint8_t  _pinDuplicate = 0;							          //Has a duplicate key been detected
			if(bemurng.pinPadGen == 10){                                  //If the inital pin pad number is being requested
				bemurng.pinPad[bemurng.pinPadGen-1] = _pinKey;            //Fill it with what ever number has been generated
				bemurng.pinPadGen = 9;                                    //Then request 9 more numbers
			}
			else{                                                         //If the number requested is greater than 0 but not the first number generated
				for(int i = 10; i > bemurng.pinPadGen; i--){              //Start with the original 10 numbers and check to see if the newly generated number has not been used
					if(bemurng.pinPad[i-1] == _pinKey){                   //Check the keys
						_pinDuplicate = 1;                                //If a duplicate has been found mark to the function as so
						break;                                            //Break the for loop
					}
				}
				if(_pinDuplicate == 0){
					bemurng.pinPad[bemurng.pinPadGen-1] = _pinKey;
					bemurng.pinPadGen -= 1;
				}
			}
			osSemaphoreRelease(pinPadGenReqSemaphoreHandle);
		}
		/* Though awkward the completion of the loop requires two conditions */
		if((bemurng.pinPadGen == 0) && (bemurng.pinPadInit == 0)){
			osSemaphoreRelease(pinPadSemaphoreHandle); //Release the Semahore
			ppe.pinPadReady = Ready;
			bemurng.pinPadInit = 1;
		}
		HAL_RNG_GenerateRandomNumber_IT(hrng);
	}
	/* If there is just a request to generate a random number */
	else if(osSemaphoreAcquire(randGenSemaphoreHandle, 0) == osOK){
		if(bemurng.entropyArrGens < bemurng.entropyArrSize){
			bemurng.entropyArr[bemurng.entropyArrGens] = random32bit;
			osSemaphoreRelease(randGenSemaphoreHandle);
			bemurng.entropyArrGens++;
			bemurng.entropyValid = false;
		}
		else{
			bemurng.entropyArr[bemurng.entropyArrGens] = random32bit;
			bemurng.entropyValid = true;
		}
		HAL_RNG_GenerateRandomNumber_IT(hrng);
	}
}

/**
 * @Desc: Generate a Pinpad to use with the Hardware Wallet
 */
void pinPadRNG(void){
	//If the pinpad randomization has not been initialized
	if(bemurng.pinPadInit == 0){
		bemurng.pinPadGen = 10;
		osSemaphoreRelease(pinPadGenReqSemaphoreHandle);
		HAL_RNG_GenerateRandomNumber_IT(&hrng); //Generate the first number for the pinpad
	}
}
/**
 * @desc: Check if the pin pad is ready
 **/
CEMU pinPadPadRNGReadyCheck(void){
	if(ppe.pinPadReady == Ready){
		return PASS;
	}
	else{
		HAL_Delay(1);
		return FAIL;
	}
}

/**
 * @desc: This function takes in a pointer to an array where the random bits of entropy will be stored.
 * @note: DO NOT UNDERALOCATE MEMORY SPACE FOR RNG IT WILL RESULT IN NON-DETERMINISTC BEHAVIOR
 */

CEMU getEntropy(int bits){
	/* Local Vars */
	bemurng.entropyArrGens = 0;                                                       //There have been no generations of any entropy
	double _size = bits / 32.0;
	bemurng.entropyArrSize = (uint32_t)ceil(_size);                                   //Find out how many 32 bit pairs need to be generated
	bemurng.entropyArr = (uint32_t*)malloc(bemurng.entropyArrSize *sizeof(uint32_t)); //Allocate memory for the random numbers
	bemurng.entropyValid = false;
	/* Checks */
	if(bemurng.entropyArrSize == 0){
		return INVALID_PARAMETERS;
	}
	if(bemurng.status == FAIL){
		return HARDWARE_NOT_READY;
	}
	/* Data Processing */
	osSemaphoreRelease(randGenSemaphoreHandle); //Release the semaphore for use within the callback function
	HAL_RNG_GenerateRandomNumber_IT(&hrng);     //Start the HAL_RNG loop
	return PASS;
}
