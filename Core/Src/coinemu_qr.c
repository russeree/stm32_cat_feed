/*
 * coinemu_qr.c
 *
 *  Created on: Jun 3, 2021
 *      Author: Reese
 */

#include "coinemu_qr.h"

uint8_t qr0[qrcodegen_BUFFER_LEN_FOR_VERSION(10)];

/* Used for QR code library validation */
void qrTestGen(void){
	uint8_t tempBuffer[qrcodegen_BUFFER_LEN_FOR_VERSION(10)];
	qrcodegen_encodeText("https://www.youtube.com/watch?v=dQw4w9WgXcQ", tempBuffer, qr0, qrcodegen_Ecc_HIGH, 5, 5, qrcodegen_Mask_AUTO, true);
}
