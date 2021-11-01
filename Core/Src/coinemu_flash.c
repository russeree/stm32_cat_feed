/*
 * coinemu_flash.c
 *
 *  Created on: Feb 2, 2021
 *      Author: Reese
 */

#include "coinemu_flash.h"
#include "string.h"
#include "main.h"
#include "coinemu.h"
#include "bip39.h"

/*--- EEPROM -> RAM SCRATCH PAD POINTERS ---*/
uint8_t eepromCPY[_EMU_EEPROM_BYTES_SIZE];
CoinEmuEEPROM *coinEmuInRamEEPROM;

/**
 * @desc: Takes the EEPROM and then moves it to RAM -> Perform local manipulations on the EEPROM in RAM
 * Then write back to the eeprom when complete.
 * @note: 100% Validate all functions that pass ram to eeprom, DATA CORRUPTION is the worst case scenerio
 */
void eepromToRam(void){
	memcpy(&eepromCPY[0], (uint8_t*)_EMU_EEPROM_START_ADDR, _EMU_EEPROM_BYTES_SIZE);
	coinEmuInRamEEPROM = (CoinEmuEEPROM*)&eepromCPY;
}


/**
 * @desc: Writes the RAM ScratchPad to the ROM
 **/
void writeRAMtoEEPROM(void){
	HAL_FLASH_Unlock();
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR);
	FLASH_Erase_Sector(FLASH_SECTOR_1, VOLTAGE_RANGE_3);
	/* CORE FUNCTION HERE WILL BURN A NEW VALUE TO THE CES VARIABLE THAT CAN NO BE RE-WROTE */
	for(int i = 0; i < _EMU_EEPROM_BYTES_SIZE; i++){
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, (uint32_t)&flashCES + i,  (uint64_t)((uint64_t)eepromCPY[i] & (uint64_t)0x00000000000000FF));
	}
	//Clear the flash programming bits before unlocking again
	CLEAR_BIT (FLASH->CR, (FLASH_CR_PG));
	HAL_FLASH_Lock();
	eepromToRam();
}

/**
 * @desc:This is the update routine that allows for a permanent write after the first power on of the device
 * */
void writeFirstUseFuse(void){
	eepromToRam();      //Read the eeprom back out to ram
	/*Copy all changes of local ces and cec to the eeprom scratch pad and modify the first use variables */
	coinEmuInRamEEPROM->ces = ces;
	coinEmuInRamEEPROM->cec = cec;
	coinEmuInRamEEPROM->ces.init = (uint32_t)false;
	coinEmuInRamEEPROM->ces.nxtScreen = scrFirstUse;
	coinEmuInRamEEPROM->ces.bootConfigStatus = unconfigured;
	/* Write the data to EEPROM */
	writeRAMtoEEPROM();
	/* Read EEPROM to RAM */
	eepromToRam();      //Read the eeprom back out to ram
}

/**
 * @desc: Write pins into the flash memory
 * @ver: beta
 * @notes: Functions but has not been validated for all use cases.
 **/
void writePinsToRom(void){
	eepromToRam();
	/* Write the Lengths of each pin to the EEPROM */
	coinEmuInRamEEPROM->cec.pinPart1Len = cec.pinPart1Len;
	coinEmuInRamEEPROM->cec.pinPart2Len = cec.pinPart2Len;
	/* Write PIN1 to the devices EEPROM */
	for(int i = 0; i < cec.pinPart1Len; i++){
		coinEmuInRamEEPROM->cec.PIN1[i] = cec.PIN1[i];
	}
	/* Write PIN2 to the devices EEPROM */
	for(int i = 0; i < cec.pinPart2Len; i++){
		coinEmuInRamEEPROM->cec.PIN2[i] = cec.PIN2[i];
	}
	/* Write the data to EEPROM */
	writeRAMtoEEPROM();
	/* Read EEPROM to RAM */
	eepromToRam();      //Read the EEPROM contents back out to ram
}

/**
 * @desc: Creates a wallet but does not generate keys for the wallet
 */
void createWalletInEEPROM(uint8_t walletIdx, uint32_t walletId, char* nameStr, SeedLen seedWordsSize){

	/*--- Do memory writing bounds checking */
	if(walletIdx > _EMU_MAX_WALLETS){
		printf("%s", "ERROR: ATTEMPT TO CREATE A WALLET AT AN INVALID INDEX GREATER THAN THE MAXIMUM WALLETS ALLOWED\n\r");
		return;
	}
	if(strlen(nameStr) > _EMU_MAX_WALLET_NAME_LEN){
		printf("%s","ERROR: WALLET NAME IS LONGER THAN STORAGE ALOWS");
		return;
	}
	/* First move the eeprom back to RAM for modifications to the memory */
	eepromToRam();
	/* Create a Default Wallet */
	BIP39SeedPhrase bip39sp = createBip39Phrase(seedWordsSize);
	/* Write the words and seed length to the EEPROM in ram scratchpad*/
	coinEmuInRamEEPROM->cec.walletCount = 1;
	coinEmuInRamEEPROM->cec.wallets[walletIdx].walletActive = false;
	coinEmuInRamEEPROM->cec.wallets[walletIdx].walletId = walletId;
	coinEmuInRamEEPROM->cec.wallets[walletIdx].seedPhraseLength = bip39sp.seedLength;
	strncpy(coinEmuInRamEEPROM->cec.wallets[walletIdx].walletName, nameStr, _EMU_MAX_WALLET_NAME_LEN); //Safe becuase of above name length check
	for(uint32_t word = 0; word < coinEmuInRamEEPROM->cec.wallets[walletIdx].seedPhraseLength; word++){
		coinEmuInRamEEPROM->cec.wallets[walletIdx].seedWords[word] = bip39sp.wordList[word];
	}
	/* Write the data to EEPROM */
	writeRAMtoEEPROM();
	/* Read EEPROM to RAM */
	eepromToRam();
	return;
}
