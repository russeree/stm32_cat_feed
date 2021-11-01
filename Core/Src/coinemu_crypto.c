/*
 * coinemu_crypto.c
 *
 *  Created on: May 17, 2021
 *      Author: Reese
 */

#include "coinemu_crypto.h"

/*** SHA256 Section ***/
const uint8_t validatoSHA256Hash[] = { // SHA256 of '1337'
		0x5D, 0xB1, 0xFE, 0xE4, 0xB5, 0x70, 0x38, 0x08, 0xC4,
		0x80, 0x78, 0xA7, 0x67, 0x68, 0xB1, 0x55, 0xB4, 0x21,
		0xB2, 0x10, 0xC0, 0x76, 0x1C, 0xD6, 0xA5, 0xD2, 0x23,
		0xF4, 0xD9, 0x9F, 0x1E, 0xAA
};

/**
 * @desc: Generates a SHA256 hash an tests the validity against a known hash
 * @returns: [bool] True or Flase
 */
TestStatus Sha256Validator(void){
	/* As a safety | enable the CRC clock, the crypto libs depend on it */
	char testVector[] = "1337";
	STMSha256Hash(&testVector[0], sizeof(testVector), &emuSha256);
	return DigestCmp(&validatoSHA256Hash[0], &emuSha256.MessageDigest[0], sizeof(validatoSHA256Hash));
}

/**
 * @desc: Generates a SHA256 hash an tests the validity against a known hash
 * @returns: [bool] True or Flase
 */
TestStatus Sha512HMACValidator(void){
	/* As a safety | enable the CRC clock, the crypto libs depend on it */
	char testVector[] = "legal winner thank year wave sausage worth useful legal winner thank yellow";
	char testKey[] = "mnemonicTREZOR";
	uint8_t* pbkdf2;
	pbkdf2 = EmuPBKDF2Sha512HMAC((uint8_t*)&testVector[0], sizeof(testVector) - 1, (uint8_t*)&testKey, sizeof(testKey) - 1, 2048);
	free(pbkdf2);
	return emuSha512HMAC.validator;
}

/**
 * @desc: This i the PBKDF2 function using the SHA512 Algorithm. This only supports a 512bit final key length for now.
 * @note: Do not include null termination in the salt or the message;
 * @note: VALID for BIP39
 */
uint8_t* EmuPBKDF2Sha512HMAC(uint8_t* message, uint32_t messageLen, uint8_t* salt, uint32_t saltLen, uint32_t rounds){
	uint8_t* xorOutput = (uint8_t*)calloc(CRL_SHA512_SIZE, sizeof(uint8_t));     //Digest used For XORing Calloc Takes Care of Zeroing out
	uint8_t* pbkdf2Salt = (uint8_t*)calloc(saltLen + 4, sizeof(uint8_t));        //Add 4 bytes to the end for the concatenation of the salt with round numbers
	/*Copy the salt into a temporary array : THIS ASSUMES NO NULL TERMINATORS*/
	for(int i = 0; i < saltLen; i++){
		pbkdf2Salt[i] = salt[i];
	}
	/*Concatenate with the Integer value of the DK*/
	pbkdf2Salt[saltLen + 4 - 1] = 0x01;
	/* Begin the hasing rounds */
	STMSha512HmacHash((char*)&pbkdf2Salt[0], saltLen + 4, (uint8_t*)&message[0], messageLen, &emuSha512HMAC); //Use the modified salt to hash the seed phrase
	arrBitwiseXOR(&xorOutput[0], &emuSha512HMAC.MessageDigest[0], CRL_SHA512_SIZE);
	/* Validated unil here */
	/* The main PKDF2 function */
	for(int i = 1; i < rounds; i++){
		STMSha512HmacHash((char*)&emuSha512HMAC.MessageDigest[0], CRL_SHA512_SIZE, (uint8_t*)&message[0], messageLen, &emuSha512HMAC);
		arrBitwiseXOR(&xorOutput[0], &emuSha512HMAC.MessageDigest[0], CRL_SHA512_SIZE);
	}
	free(pbkdf2Salt);
	return &xorOutput[0];
}

/**
 *
 * @Desc this is the SHA256 hashing algorithm, This is used to hash Pin Pad Entries
 */
EmuSha256* STMSha256Hash(char* input, uint32_t inputLen, EmuSha256* es256){
	/* As a safety | enable the CRC clock, the crypto libs depend on it */
	__CRC_CLK_ENABLE();
	/* SHA 256 Function Inputs */
	es256->MessageDigestLength = 0;
	/* Hashing Function Core */
	es256->errorStatus = HASH_SUCCESS;
	SHA256ctx_stt P_pSHA256ctx;
	/* Set the size of the desired hash digest */
	P_pSHA256ctx.mTagSize = CRL_SHA256_SIZE;
	/* Set flag field to default value */
	P_pSHA256ctx.mFlags = E_HASH_DEFAULT;
	es256->errorStatus = SHA256_Init(&P_pSHA256ctx);
	if (es256->errorStatus == HASH_SUCCESS){
		/* Add data to be hashed */
		es256->errorStatus = SHA256_Append(&P_pSHA256ctx, (uint8_t*)input, inputLen - 1);
		if (es256->errorStatus == HASH_SUCCESS){
		  /* retrieve */
			es256->errorStatus = SHA256_Finish(&P_pSHA256ctx, &es256->MessageDigest[0], &es256->MessageDigestLength);
		}
	}
	return es256;
}

/* SHA512 HMAC IMPLEMNATATION USING STM32 PROVIDED BINARIES */
EmuSha512HMAC* STMSha512HmacHash(char* input, uint32_t inputLen, uint8_t* key, uint32_t keyLen, EmuSha512HMAC* es512){
	__CRC_CLK_ENABLE();
	HMAC_SHA512ctx_stt context_st;
	context_st.mFlags = E_HASH_DEFAULT;
	context_st.mTagSize = CRL_SHA512_SIZE;
	context_st.pmKey = key;
	context_st.mKeySize = keyLen;
	es512->errorStatus = HMAC_SHA512_Init(&context_st);
	if (es512->errorStatus == HASH_SUCCESS){
		/* Add data to be hashed */
		HMAC_SHA512_Append(&context_st, (uint8_t*)&input[0], inputLen);
		if (es512->errorStatus == HASH_SUCCESS){
		  /* retrieve */
			es512->errorStatus = HMAC_SHA512_Finish(&context_st, (uint8_t*)&es512->MessageDigest[0], &es512->MessageDigestLength);
		}
	}
	return es512;
}

/************ HELPERS *************/

/* Bitwise Xor an Array. USE THIS IN THE PBKDF2 */
void arrBitwiseXOR(uint8_t* xorArr, uint8_t* input, uint32_t len){
	for(int i = 0; i < len; i++){
		xorArr[i] = xorArr[i] ^ input[i];
	}
}

/*
 * @desc: Compares to arrays: In this scenerio it is used as a means to compared expected digests to a generated one
 */
TestStatus DigestCmp(const uint8_t* digest, uint8_t* digest1, uint16_t BufferLength){
  while (BufferLength--){
    if (*digest != *digest1){
      return FAILED;
    }
    digest++;
    digest1++;
  }
  return PASSED;
}


/* OpenSource the HMAC Algo !!!DEPREICIATED!!!*/
EmuSha512HMAC* Sha512HmacHash(char* input, uint32_t inputLen, uint8_t* key, uint32_t keyLen, EmuSha512HMAC* es512){
	/*Function Constants and Variables */
	const uint32_t _blockSizeBytes = 128;
	const uint32_t messageLen = _blockSizeBytes + inputLen - 1;
	/* Enable Clocks */
	__CRC_CLK_ENABLE();
	/* Hashing Function Core */
	SHA512ctx_stt context_st;
	/* As a safety | enable the CRC clock, the crypto libs depend on it */
	es512->MessageDigestLength = 0;
	es512->errorStatus = HASH_SUCCESS;
	context_st.mTagSize = CRL_SHA512_SIZE;
	context_st.mFlags = E_HASH_DEFAULT;
	/* Init the context */
	es512->errorStatus = SHA512_Init(&context_st);
	/*Setup the HMAC IPAD KEY*/
	uint8_t* ipad   = (uint8_t*)calloc(messageLen, sizeof(uint8_t));
	uint8_t* keyPad = (uint8_t*)calloc(messageLen, sizeof(uint8_t));
	/* Copy the Key to the padded Keypad */
	for(int i = 0; i < keyLen; i++){
		keyPad[i] = key[i];
	}
	hmacPadCreation(IPAD, &ipad[0], _blockSizeBytes);
	/* XOR THE KEY INTO THE ARRAY; THIS INCLUDES ALL ARRAY CHARS INCLUDING THE NULL CHAR */
	arrBitwiseXOR(&ipad[0], &keyPad[0], _blockSizeBytes);
	/*APPEND THE MESSAGE TO THE END OF THE ARRAY IPAD */
	hmacAppendMessage(_blockSizeBytes, &ipad[0], messageLen, (uint8_t*)&input[0], inputLen - 1);
	/* HASH IPAD */
	if (es512->errorStatus == HASH_SUCCESS){
		/* Add data to be hashed */
		SHA512_Append(&context_st, (uint8_t*)&ipad[0], messageLen);
		if (es512->errorStatus == HASH_SUCCESS){
		  /* retrieve */
			es512->errorStatus = SHA512_Finish(&context_st, &es512->MessageDigest[0], &es512->MessageDigestLength);
		}
	}
	es512->MessageDigestLength = 0;
	context_st.mTagSize = CRL_SHA512_SIZE;
	context_st.mFlags = E_HASH_DEFAULT;
	es512->errorStatus = SHA512_Init(&context_st);
	/* OPAD CREATION */
	const uint32_t opadMessageLen = _blockSizeBytes + CRL_SHA512_SIZE;
	uint8_t* opad = (uint8_t*)calloc(opadMessageLen, sizeof(uint8_t));
	hmacPadCreation(OPAD, &opad[0], _blockSizeBytes);
	arrBitwiseXOR(&opad[0], &key[0], keyLen);
	hmacAppendMessage(_blockSizeBytes, &opad[0], opadMessageLen, (uint8_t*)&emuSha512HMAC.MessageDigest[0], CRL_SHA512_SIZE);
	/* XOR THE KEY INTO THE ARRAY; THIS INCLUDES ALL ARRAY CHARS INCLUDING THE NULL CHAR */
	if (es512->errorStatus == HASH_SUCCESS){
		/* Add data to be hashed */
		SHA512_Append(&context_st, (uint8_t*)&opad[0], opadMessageLen);
		if (es512->errorStatus == HASH_SUCCESS){
		  /* retrieve */
			es512->errorStatus = SHA512_Finish(&context_st, &es512->MessageDigest[0], &es512->MessageDigestLength);
		}
	}
	free(ipad);
	free(opad);
	free(keyPad);
	return es512;
}

/*Generate Key Padding*/
void hmacPadCreation(sha512HmacPadding padSelection, uint8_t* padArray, uint32_t paddArraySize){
	/* Null padding byte */
	uint8_t paddingByte = 0x00; //Set this to 0;
	/* Let the switch statement pad the array with the required values */
	switch(padSelection){
		case IPAD:
			paddingByte = _SHA_HMAC_IPAD_BYTE;
			break;
		case OPAD:
			paddingByte = _SHA_HMAC_OPAD_BYTE;
			break;
		default:
			paddingByte = 0x00;
			break;
	}
	/* Write the values the the array */
	for(uint8_t i = 0; i < paddArraySize; i++){
		padArray[i] = paddingByte;
	}
}

/* Appends the padded message to the key to the processed by the PSR */
void hmacAppendMessage(uint32_t blocksize, uint8_t* padArray, uint32_t padArraySize, uint8_t* message, uint32_t messageSize){
	for(int i = 0; i < messageSize; i++){
		padArray[blocksize + i] = message[i];
	}
}

/*** AES256 Section ***/
