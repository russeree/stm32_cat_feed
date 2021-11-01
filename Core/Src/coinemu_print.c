/*
 * coinemu_print.c
 *
 *  Created on: May 26, 2021
 *      Author: Reese
 */

/**
 * @desc: This function is a general test of the USB Virtual Com Ports ability to print text
 */
#include "coinemu_print.h"

/**
 * @desc: This is a general print statement to test the USB CDC VCP
 */
void heartBeatPrinter(void *argument){
	for(;;){
		for(int i = 0; i < 2048; i++){
			printf("BIP39 word: %.*s\r\n", 8, &bip39wl[i][0]);
			osDelay(1000);
		}
	}
}

/**
 * @desc: Prints a device welcome text over the USB CDC perhipreal
 */
void cemuPrintWelcome(void){
	  printf("%s","Welcome to BlockEmu 0.1a\r\n");
}
