/*
 * coinemu.h
 *
 *  Created on: Feb 2, 2021
 *      Author: Reese
 */
#ifndef INC_COINEMU_H_
#define INC_COINEMU_H_

#include "stdint.h"
#include "stdbool.h"
#include "stdio.h"

/* Debug Flags */
//#define _EMU_PRINT_DEBUG
#define _EMU_TOUGHGFX_DEBUG

/* Block Emu Complier Defines */
#define _EMU_UART          0
#define _MAX_PIN_PAD_TRIES 10
#define _EMU_VERSION       1337
#define _PIN_ENTRY_CORRECT "DECRYPTION VALID"

/* Block EMU RTOS Settings */
#define _EMU_RTOS_LONG_DELAY      1000
#define _EMU_RTOS_SHORT_DELAY     500
#define _EMU_RTOS_SD_DAEMON_DELAY 100

//BLOCK EMU DEFINES
#define _EMU_MAX_PIN_LEN          6
#define _EMU_INIT_UNINIT          0
#define _EMU_INIT_SUCCESS         1
#define _EMU_MAX_TRIES            10
#define _EMU_MAX_SEED_WORDS       24
#define _EMU_MAX_WALLETS          64
#define _EMU_EEPROM_BYTES_SIZE    32768
#define _EMU_EEPROM_START_ADDR    0x08008000
#define _EMU_MAX_WALLET_NAME_LEN  32
#define _EMU_MAX_SEEDWORD_CHARS   9
#define _EMU_NUMBER_OF_SEEDWORDS  2048


//INITIAL CONFIGURATION STATES FOR BLOCK EMU
#define _EMU_FIRSTUSE     1
#define _EMU_CONFIGURED   2
#define _EMU_RESET        3
#define _EMU_UNCONFIGURED 4

//Magic Phrases
#define _PIN_ENTRY_1           "ENTER YOUR PIN\n-PART 1-\nUSE 0 TO 6 DIGITS"
#define _PIN_ENTRY_CONF_1      "CONFIRM YOUR PIN\n-PART 1-"
#define _PIN_ENTRY_2           "ENTER YOUR PIN\n-PART 2-\nUSE 0 TO 6 DIGITS"
#define _PIN_ENTRY_CONF_2      "CONFIRM YOUR PIN\n-PART 2-"

//Crypto Constants
#define _PBKDF2_SHA512_DIGEST_BYTES 64
#define _PBKDF2_SHA512_DIGEST_BITS 512

/*--- BIP39 ENUMERATIONS ---*/
//The different states a pin pad
typedef enum SeedLen{
	words12 = 12,
	words24 = 24
} SeedLen;


typedef enum CEMU{
	FAIL,
	PASS,
	BUSY,
	READY,
	INVALID_PARAMETERS,
	HARDWARE_NOT_READY,
} CEMU;

/*--- INITIAL CONFIGURATION STATES FOR BLOCK EMU ---*/
typedef enum CEMU_CONFIG_STATUS{
	firstUse,     //This is the first time the device has been configured and used - This state will not be reached again.
	devReset,     //CoinEmu has been reset by the user. NEW KEY - NEW PIN [This is the same as first use except for the fact there will be no first power on screen shown in the GUI - That is a 1 time event]
	unconfigured,  //CoinEmu is not configured, this means that somehow the configuration stage has failed, maybe the user lost power or some other bad event -> This will notify the user of a setup error then move to the reset stage
	configured   //CoinEmu is configured as a wallet including keys and pin - ONLY WHEN ces in this state will access to wallet features be enabled.
}CEMU_CONFIG_STATUS;


//DIFFERENT SCREEN THAT CAN BE USED.
typedef enum SCREEN{
	scrUndefined,
	scrFirstUse,
	scrUnlock,
	scrWelcome,
	scrPinEntry,
	scrBeginSetup,
	scrPinSetupNotesPart2,
	scrSeedPhraseDisplay
} SCREEN;

/*** ENUMS ARE USED TO REPLACE THE DEFINE STRUCTURES ***/
//The Different Values that can be used on the pin pad
typedef enum PIN_NUMBERS{
	Zero,
	One,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Unused
} PIN_NUMBERS;

//The different states a pin pad
typedef enum PIN_READY{
	NotReady,
	Ready
} PIN_READY;

//The different states a pin pad can be in
typedef enum SETUP_STAGES{
	Undefined,               //A null setup state, this means you are not performing anything, this is the default 0 value state.
	PinSetupPart1,           //Actual Pin Number Creation for Part1
	PinSetupPart2,
	SeedPhraseDisplay,
	PinConfirm1,
	PinConfirm2,
	PinCreationComplete
} SETUP_STAGES;


//This is the peak structure. Use this everywhere to adjust the status of CoinEMU
typedef struct CoinemuStatus{
	uint32_t           init;               //Had the device successfully started up
	CEMU_CONFIG_STATUS bootConfigStatus;   //Is this is the first time the device has been used
	uint32_t           pinPadTriesUsed[4]; //4 element array because it is meant to be written to 4 times with each use. If there are any discrepancies then the count is checked against itself
	SCREEN             curScreen;          //Current screen being used - All screens must modify this variable
	SCREEN             nxtScreen;          //The Next Screen to be used - The current screen can write to this but it is not a required read varibale
} CoinemuStatus;

//This Represents the current state of the pin pad.
typedef struct PinPadEntry{
	PIN_NUMBERS presses[_EMU_MAX_PIN_LEN + 1]; //The Current State of the pin entry - The Extra Char is a padding for the cursor, it never should actualy be written to
	uint8_t     cursorPos;                     //The position of the cursor of the pin pad. Cursor Index
	PIN_READY   pinPadReady;                   //Has the pin pad been randomly generated
} PinPadEntry;

/*---Seed Word Large Storage Pool---*/
typedef struct bip39Wallet{
	bool     walletActive;                        //Is this an active Wallet that is shown on the list of wallets
	char     walletName[_EMU_MAX_WALLET_NAME_LEN];//An integer array when cast to uint16_t contains the utf16 name of the wallet
	uint32_t walletId;                            //Integer value index of the wallets storage location
	SeedLen  seedPhraseLength;                    //Number of seed words used in the wallets seed phrase
	uint16_t seedWords [_EMU_MAX_SEED_WORDS];     //These are the seed words as indexed per bip39
	uint32_t metaDataPTR;                         //This is the pointer to the QSPI wallet data - the non secutrity sensitive stuff.
} bip39Wallet;

/*---A struct to keep track of all setup variables ---*/
typedef struct CoinemuSetup{
	bool setup;         //Is a setup active at this time;
	bool pin1Created;   //Has the pin part1 been created
	bool pin2Created;   //Has the pin part2 been created
	bool pin1Confirmed; //Has the pin part1 been confirmed
	bool pin2Confirmed; //Has the pin part2 been confirmed
	bool seedConfirmed; //Had the seed phrase been confirmed
	bool emojiSecure;   //Had an Emoji Secure icon been selected
	SETUP_STAGES stage; //The Stage you are within the setup process;
}CoinemuSetup;

/**
 * @desc: This is the global CoinEMU Config (cec) variable
 * @notes: This section contains extra comments due to the critical nature of each section and communication of clear intent is critical.
 **/
typedef struct CoinemuConfig{
	/* CoinEMU Setup Data */
	CoinemuSetup setup;                          //Setup Stages Variables and Status
	/* CoinEMU Wallet data */
	uint32_t     walletCount;                    //Number of wallets stored in coinEMU Memory
	bip39Wallet  wallets[_EMU_MAX_WALLETS];      //Wallets for CoinEMU to use
	/* CoinEMU Pin data */
	PIN_NUMBERS  PIN1[_EMU_MAX_PIN_LEN];         //PIN PART 1
	PIN_NUMBERS  PIN2[_EMU_MAX_PIN_LEN];         //PIN PART 2
	uint32_t     pinPart1Len;                    //Length of pin part 1
	uint32_t     pinPart2Len;                    //Length of pin part 2


} CoinemuConfig;

/**
 * @desc:State of each hardware component of a coinemu wallet - false = failed - true = success
 **/
typedef struct CoinemuHardware{
	bool emuFreeRtos;
	bool emuUSB_HS;
	bool emuSD;
	bool emuRNG;
} CoinemuHardware;

/**
 * @desc: The ULTIMATE typedef struct for EEPROM use, since all EEPROM is modified within RAM
 **/
typedef struct CoinEmuEEPROM{
	CoinemuStatus ces;
	CoinemuConfig cec;
}CoinEmuEEPROM;

//Needed by anything using this file to use the struct
extern CoinemuStatus   ces;   //CoinEmu Status
extern CoinemuConfig   cec;   //CoinEmu Config
extern CoinemuHardware ceh;   //CoinEmuHardware
extern PinPadEntry     ppe;   //PinPad Entry

/*--- USED FOR THE EEPROM in RAM SCRATCHPAD ---*/
extern          CoinEmuEEPROM *coinEmuInRamEEPROM;
extern volatile CoinEmuEEPROM flashCES;
#endif /* INC_COINEMU_H_ */
