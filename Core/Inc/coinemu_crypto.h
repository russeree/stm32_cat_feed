/*
 * coinemu_crypto.h
 *
 *  Created on: May 17, 2021
 *      Author: Reese Russell
 *  @Desc This Handles all of the Decryption and Encryption of Data within the BlockEmu Device
 */

#ifndef INC_COINEMU_CRYPTO_H_
#define INC_COINEMU_CRYPTO_H_

#include "coinemu.h"
#include "crypto.h"

#define _SHA_HMAC_IPAD_BYTE 0x36
#define _SHA_HMAC_OPAD_BYTE 0x5c

typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
typedef enum {IPAD = 0,OPAD = 1} sha512HmacPadding;

typedef struct EmuSha256{
	TestStatus validator;                    // Validator: This is used to store a state of the validation test result of the sha256 engine
	TestStatus testStatus;
	uint32_t errorStatus;
	int32_t MessageDigestLength;
	uint8_t MessageDigest[CRL_SHA256_SIZE];
} EmuSha256;

typedef struct EmuSha512HMAC{
	TestStatus validator;                    // Validator: This is used to store a state of the validation test result of the sha256 engine
	TestStatus testStatus;
	uint32_t errorStatus;
	int32_t MessageDigestLength;
	uint8_t MessageDigest[CRL_SHA512_SIZE];
} EmuSha512HMAC;

/* Reese Russell Crypto Implemention */
void arrBitwiseXOR(uint8_t* xorArr, uint8_t* input, uint32_t len);
TestStatus Sha256Validator(void);
TestStatus Sha512HMACValidator(void);
TestStatus DigestCmp(const uint8_t* digest, uint8_t* digest1, uint16_t BufferLength);
EmuSha256* STMSha256Hash(char* input, uint32_t inputLen, EmuSha256* es256);
EmuSha512HMAC* STMSha512HmacHash(char* input, uint32_t inputLen, uint8_t* key, uint32_t keyLen, EmuSha512HMAC* es512);
uint8_t* EmuPBKDF2Sha512HMAC(uint8_t* message, uint32_t messageLen, uint8_t* salt, uint32_t saltLen, uint32_t rounds); //Does not support variable key length support as it's not needed for the BIP39
/* DEPREICIATED */
EmuSha512HMAC* Sha512HmacHash(char* input, uint32_t inputLen, uint8_t* key, uint32_t keyLen, EmuSha512HMAC* es512);
void hmacPadCreation(sha512HmacPadding padSelection, uint8_t* padArray, uint32_t paddArraySize);
void hmacAppendMessage(uint32_t blocksize, uint8_t* padArray, uint32_t padArraySize, uint8_t* message, uint32_t messageSize);

extern EmuSha256 emuSha256;
extern EmuSha512HMAC emuSha512HMAC;

#endif /* INC_COINEMU_CRYPTO_H_ */
