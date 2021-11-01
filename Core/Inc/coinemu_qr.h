/*
 * coinemu_qr.h
 *
 *  Created on: Jun 3, 2021
 *      Author: Reese
 */

#ifndef INC_COINEMU_QR_H_
#define INC_COINEMU_QR_H_

#include "stdbool.h"
#include "stdint.h"
#include "coinemu.h"
#include "qrcodegen.h"

extern uint8_t qr0[qrcodegen_BUFFER_LEN_FOR_VERSION(10)];

void qrTestGen(void);

#endif /* INC_COINEMU_QR_H_ */
