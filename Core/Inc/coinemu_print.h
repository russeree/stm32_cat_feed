/*
 * coinemu_print.h
 *
 *  Created on: May 26, 2021
 *      Author: Reese
 */

#ifndef INC_COINEMU_PRINT_H_
#define INC_COINEMU_PRINT_H_

#include "main.h"
#include "string.h"
#include "stdint.h"
#include "usbd_cdc_if.h"
#include "bip39.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"

void heartBeatPrinter(void *argument);
void cemuPrintWelcome(void);

#endif /* INC_COINEMU_PRINT_H_ */
