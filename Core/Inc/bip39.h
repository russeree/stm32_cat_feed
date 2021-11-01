/**
 * bip39.h
 *
 *  Created on: May 25, 2021
 *      Author: Reese
 **/

#ifndef BIP39_H_
#define BIP39_H_

#include "stdlib.h"
#include "stdio.h"
#include "coinemu.h"

/* This is the seed phase structure - Destory after use MUST FREE*/
typedef struct BIP39SeedPhrase{
	uint16_t  wordList[_EMU_MAX_SEED_WORDS];    //This is the list of words as represented by a value from 0-2047
	SeedLen   seedLength;                       //This is the number of words generated to be used as the seed phrase
} BIP39SeedPhrase;

/* This is the BIP39 Word List in an array */
extern const char bip39wl[_EMU_NUMBER_OF_SEEDWORDS][_EMU_MAX_SEEDWORD_CHARS];

/* Create a BIP39 Compliant Seed Phrase */
BIP39SeedPhrase createBip39Phrase(SeedLen words);

#endif /* BIP39_H_ */
