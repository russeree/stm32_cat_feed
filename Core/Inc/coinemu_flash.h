/*
 * coinemu_flash.h
 *
 *  Created on: Feb 2, 2021
 *      Author: Reese
 *  Desc: This file is used to control the access and use of flash memory for the Coinemu Hardware Wallet
 */

#ifndef INC_COINEMU_FLASH_H_
#define INC_COINEMU_FLASH_H_

#include "stm32f7xx_hal.h"
#include "main.h"
#include "coinemu.h"

void eepromToRam(void);       //Copies the EEPROM to Ram for scratchpad use
void writeFirstUseFuse(void); //Burns the EEPROM with a flag that the user
void writeRAMtoEEPROM(void);  //Writes the entire eeprom scratchpad to memory
void createWalletInEEPROM(uint8_t walletIdx, uint32_t walletId, char* nameStr, SeedLen seedWordsSize); //Creats a wallet in memory
void writePinsToRom(void);    //Write the users pin numbers into memory

#endif /* INC_COINEMU_FLASH_H_ */
