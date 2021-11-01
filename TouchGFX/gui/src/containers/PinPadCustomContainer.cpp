#include <gui/containers/PinPadCustomContainer.hpp>

extern "C" {
	#include "main.h"
	#include "coinemu.h"
	#include "string.h"
	#include "coinemu_rng.h"
	extern BlockEmuRNG bemurng;
}
extern BlockEmuRNG bemurng;

PinPadCustomContainer::PinPadCustomContainer() : showPin(false){
	/* Make some private variables accessible though a pointer */
	enterButton = &this->pin_pad_b_return;
	showPasswordButton = &this->showPassword;
	/* Make sure that the Pin Pad entry buffer is cleared */
	memset(&ppe.presses, Unused, PINENTRY_SIZE);
	/* First generate the random numbers needed for a Pin Pad */
	if(bemurng.rngValid != PASS){
		initBlockEmuRng(&bemurng);
	}
	/* Generate a random pin pad button order*/
	pinPadRNG();
	updatePinPad();
}

/**
 * @desc: determine that this o
 **/
void PinPadCustomContainer::initialize(){
    PinPadCustomContainerBase::initialize();
}

/**** PIN BUTTON PRESSES SECTION ****/
void PinPadCustomContainer::pressedButton0(){
	ppe.presses[ppe.cursorPos] =  (PIN_NUMBERS)bemurng.pinPad[0];
	pinEntryBoundsCheckPress();
}

void PinPadCustomContainer::pressedButton1(){
	ppe.presses[ppe.cursorPos] =  (PIN_NUMBERS)bemurng.pinPad[1];
	pinEntryBoundsCheckPress();
}

void PinPadCustomContainer::pressedButton2(){
	ppe.presses[ppe.cursorPos] =  (PIN_NUMBERS)bemurng.pinPad[2];
	pinEntryBoundsCheckPress();
}

void PinPadCustomContainer::pressedButton3(){
	ppe.presses[ppe.cursorPos] =  (PIN_NUMBERS)bemurng.pinPad[3];
	pinEntryBoundsCheckPress();
}

void PinPadCustomContainer::pressedButton4(){
	ppe.presses[ppe.cursorPos] =  (PIN_NUMBERS)bemurng.pinPad[4];
	pinEntryBoundsCheckPress();
}

void PinPadCustomContainer::pressedButton5(){
	ppe.presses[ppe.cursorPos] =  (PIN_NUMBERS)bemurng.pinPad[5];
	pinEntryBoundsCheckPress();
}

void PinPadCustomContainer::pressedButton6(){
	ppe.presses[ppe.cursorPos] =  (PIN_NUMBERS)bemurng.pinPad[6];
	pinEntryBoundsCheckPress();
}

void PinPadCustomContainer::pressedButton7(){
	ppe.presses[ppe.cursorPos] =  (PIN_NUMBERS)bemurng.pinPad[7];
	pinEntryBoundsCheckPress();
}

void PinPadCustomContainer::pressedButton8(){
	ppe.presses[ppe.cursorPos] =  (PIN_NUMBERS)bemurng.pinPad[8];
	pinEntryBoundsCheckPress();
}

void PinPadCustomContainer::pressedButton9(){
	ppe.presses[ppe.cursorPos] =  (PIN_NUMBERS)bemurng.pinPad[9];
	pinEntryBoundsCheckPress();
}

/**
 * @desc: This is the pin pads delete button.
 * @status: Tested
 */
void PinPadCustomContainer::pressedButtonDel(){
	ppe.presses[ppe.cursorPos] = Unused;
	if(ppe.cursorPos > 0){
		ppe.cursorPos -= 1;
	}
	updatePinPressesDisplay();
}

/**
 * @desc: Updates the wildcard chars on the pinpad to represent their random values generated though the trueRNG
 * @version: 1.0.1
 * @notes: Add a check to make sure that the RNG pin pad generator has indeed generated a pin pad for use
 **/
void PinPadCustomContainer::updatePinPad(void){
	/* Update numeric values on each key 0-9 to represent the random generation of pin numbers */
	memset(&pin_pad_b_0Buffer, 0, sizeof(pin_pad_b_0Buffer));
	Unicode::snprintf(pin_pad_b_0Buffer, PIN_PAD_B_0_SIZE, "%d", bemurng.pinPad[0]);
	pin_pad_b_0.invalidate();
	memset(&pin_pad_b_1Buffer, 0, sizeof(pin_pad_b_1Buffer));
	Unicode::snprintf(pin_pad_b_1Buffer, PIN_PAD_B_1_SIZE, "%d", bemurng.pinPad[1]);
	pin_pad_b_1.invalidate();
	memset(&pin_pad_b_2Buffer, 0, sizeof(pin_pad_b_2Buffer));
	Unicode::snprintf(pin_pad_b_2Buffer, PIN_PAD_B_2_SIZE, "%d", bemurng.pinPad[2]);
	pin_pad_b_2.invalidate();
	memset(&pin_pad_b_3Buffer, 0, sizeof(pin_pad_b_3Buffer));
	Unicode::snprintf(pin_pad_b_3Buffer, PIN_PAD_B_3_SIZE, "%d", bemurng.pinPad[3]);
	pin_pad_b_3.invalidate();
	memset(&pin_pad_b_4Buffer, 0, sizeof(pin_pad_b_4Buffer));
	Unicode::snprintf(pin_pad_b_4Buffer, PIN_PAD_B_4_SIZE, "%d", bemurng.pinPad[4]);
	pin_pad_b_4.invalidate();
	memset(&pin_pad_b_5Buffer, 0, sizeof(pin_pad_b_5Buffer));
	Unicode::snprintf(pin_pad_b_5Buffer, PIN_PAD_B_5_SIZE, "%d", bemurng.pinPad[5]);
	pin_pad_b_5.invalidate();
	memset(&pin_pad_b_6Buffer, 0, sizeof(pin_pad_b_6Buffer));
	Unicode::snprintf(pin_pad_b_6Buffer, PIN_PAD_B_6_SIZE, "%d", bemurng.pinPad[6]);
	pin_pad_b_6.invalidate();
	memset(&pin_pad_b_7Buffer, 0, sizeof(pin_pad_b_7Buffer));
	Unicode::snprintf(pin_pad_b_7Buffer, PIN_PAD_B_7_SIZE, "%d", bemurng.pinPad[7]);
	pin_pad_b_7.invalidate();
	memset(&pin_pad_b_8Buffer, 0, sizeof(pin_pad_b_8Buffer));
	Unicode::snprintf(pin_pad_b_8Buffer, PIN_PAD_B_8_SIZE, "%d", bemurng.pinPad[8]);
	pin_pad_b_8.invalidate();
	memset(&pin_pad_b_9Buffer, 0, sizeof(pin_pad_b_9Buffer));
	Unicode::snprintf(pin_pad_b_9Buffer, PIN_PAD_B_9_SIZE, "%d", bemurng.pinPad[9]);
	pin_pad_b_9.invalidate();
}

/**
 * @desc: Updates the pin pad display with the current set of values
 * @status: works - needs improvement
 * @version: 1.0.0
 **/
void PinPadCustomContainer::updatePinPressesDisplay(){
	/*Convert the Integers to Ascii and write them to a temporary array*/
	char pinString[PINENTRY_SIZE];
	memset(&pinString, '\0', PINENTRY_SIZE);
	for(int cur = 0; cur < ppe.cursorPos; cur++){
		if(this->showPin)
			pinString[cur] = (int)ppe.presses[cur] + 0x30; //Shows the Chars
		else
			pinString[cur] = '*';
	}
	/* Char to UTF8 conversion becuase that is what TouchGFX like to use */
	touchgfx::Unicode::UnicodeChar _tempPinDisplay[7];
	touchgfx::Unicode::strncpy(_tempPinDisplay, pinString, 7);
	memset(&PinEntryBuffer, '\0', sizeof(PinEntryBuffer));
	Unicode::snprintf(PinEntryBuffer, PINENTRY_SIZE, "%s", _tempPinDisplay);
	PinEntry.invalidate();
}

/**
 * @desc: Checks to make sure that the index of the pin entry is not longer than the maximum char
 * @status: Verified
 */
void PinPadCustomContainer::pinEntryBoundsCheckPress(void){
	if(ppe.cursorPos < (_EMU_MAX_PIN_LEN)){
		ppe.cursorPos += 1;
	}
	else{ //Nullifies the last char after press this avoid some smaller issues - this is the padding byte
		ppe.presses[ppe.cursorPos] = Unused;
	}
	updatePinPressesDisplay();
};

/**
 * @desc: Null because the pressing and holding of the enter key is handled though the tick event handler
 **/
void PinPadCustomContainer::pressedButtonEnter(){
}
