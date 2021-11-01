#include <gui/unlockscreen_screen/unlockScreenView.hpp>

extern "C" {
	#include "main.h"
	#include "coinemu.h"
	#include "string.h"
	#include "coinemu_flash.h"
	#include <coinemu_rng.h>
	/* Access to the random number generator */
	extern BlockEmuRNG bemurng;
}

/**
 * @desc: Constructor
 */
unlockScreenView::unlockScreenView(){
	/* Setup Active Screen in CES */
	ces.curScreen = scrPinEntry;
	ces.nxtScreen = scrUndefined;
	this->submitProgress.setVisible(true);
	/* Check if this is first time the device has been powered on */
	if(ces.bootConfigStatus == firstUse){
		ces.nxtScreen = scrFirstUse;
		this->updateCoinEmuSetupConfig();
		this->firstPowerUpDisplay.show();
	}
	else if(ces.bootConfigStatus < configured){
		this->deviceSetupBegin.show();
		ces.nxtScreen = scrUndefined;
	}
}

/**
 * @desc: Setups up the screen for use.
 */
void unlockScreenView::setupScreen(){
	unlockScreenViewBase::setupScreen();
}

/**
 * @desc: Destroys the current screen.
 */
void unlockScreenView::tearDownScreen(){
	unlockScreenViewBase::tearDownScreen();
}

/**
 * @desc: Callback for the continue button used on the 'confirm first use screen'
 **/
void unlockScreenView::confirmFirstUse(){
	this->firstPowerUpDisplay.hide(); //Closes the first power up display window
	/* Check if the device needs to be configured */
	if(ces.bootConfigStatus < configured){
		this->deviceSetupBegin.show();
	}
}

/**
 * @desc: PinPad Next Screen
 **/
void unlockScreenView::nextScreen(void){
	if((bool)cec.setup.setup){
		switch(cec.setup.stage){
			case PinSetupPart1:
				static_cast<FrontendApplication*>(Application::getInstance())->gotoPinPadNotesPart2();
				break;
			case PinSetupPart2:
				writePinsToRom();
				static_cast<FrontendApplication*>(Application::getInstance())->gotoPinPadSetupComplete();
				break;
			default:
				printf("%s", _EMU_PIN_GUI_ERROR_SCREEN_SWITCH_FAILED);
				break;
		}
	}
}

/**
 * @desc: CoinEMU Specific function to move the pin into a memory location for unlocking or hashing
 */
void unlockScreenView::safeMovePinToRam(void){
	/* Write the length of the pin to ram */
	switch(cec.setup.stage){
		case PinSetupPart1:
			cec.pinPart1Len = ppe.cursorPos;
			break;
		case PinSetupPart2:
			cec.pinPart2Len = ppe.cursorPos;
			break;
		default:
			printf("%s", _EMU_PIN_GUI_INCORRECT_STATE_ENTRY);
			break;
	}
	/* Now use that length to write the rest of the pin to memory */
	for(uint8_t digit = 0; digit < _EMU_MAX_PIN_LEN; digit++){
		uint32_t _digitDecoded = 0;
		/* Cast the pin entry into a digit to be wrote to memory */
		switch(ppe.presses[digit]){
			case Zero:
				_digitDecoded = 0; break;
			case One:
				_digitDecoded = 1; break;
			case Two:
				_digitDecoded = 2; break;
			case Three:
				_digitDecoded = 3; break;
			case Four:
				_digitDecoded = 4; break;
			case Five:
				_digitDecoded = 5; break;
			case Six:
				_digitDecoded = 6; break;
			case Seven:
				_digitDecoded = 7; break;
			case Eight:
				_digitDecoded = 8; break;
			case Nine:
				_digitDecoded = 9; break;
			case Unused:
				_digitDecoded = (uint8_t)Unused; break;
			default:
				printf("%s", _EMU_PIN_GUI_ERROR_TRANSLATION_TO_MEMORY);
				break;
		}
		/* Compare the cast value with the original */
		if(ppe.presses[digit] != _digitDecoded){
			printf("%s", _EMU_PIN_GUI_ERROR_TRANSLATION_TO_MEMORY);
		}
		/* Write the temporary variable to memory */
		switch(cec.setup.stage){
			case PinSetupPart1:
				cec.PIN1[digit] = ppe.presses[digit];
				break;
			case PinSetupPart2:
				cec.PIN2[digit] = ppe.presses[digit];
				break;
			default:
				printf("%s", _EMU_PIN_GUI_INCORRECT_STATE_ENTRY);
		}
		/* Clean up the ppe scratch pad */
	}
	/* Pin has been moved. CLEAN UP PIN PAD struct */
	ppe.cursorPos = 0;
	memset(&ppe.presses, Unused, _EMU_MAX_PIN_LEN);
	this->PinPad.updatePinPressesDisplay();
}

/**
 * @desc: This is the enter button 'press' function. This function starts a timer that continues as long as the button is pressed
 * this timer will update a progress bar. This is used to make sure that the user is deliberately pressing enter to submit a pin entry
 **/

void unlockScreenView::handleTickEvent(){
	if(this->PinPad.enterButton->getPressed() == true){
		int submitProgressValue = submitProgress.getValue();
		if(submitProgressValue < _EMU_PIN_ENT_SUBMIT_THRESHOLD){
			submitProgressValue += _EMU_PIN_ENT_PRESS_PROGRESS_SPEED;
			submitProgress.setValue(submitProgressValue);
			submitProgress.invalidate();
		}
		/* This will execute when the button is held to a value of 100 or more, this validates the user input. THIS IS A PIN SUBMSSION TO THE DEVICE */
		else{
			this->safeMovePinToRam();
			this->nextScreen();
		}
	}
	/* If the enter button is not pressed, reset the value of the progress counter to zero */
	else{
		if(submitProgress.getValue() > 0){
			submitProgress.setValue(0);
			submitProgress.invalidate();
		}
	}
}

/**
 * @desc: Updates the cec state variable to determine if a setup is required by the user to continue
 */
void unlockScreenView::updateCoinEmuSetupConfig(void){

	/*1. Determine the state of the CoinEMU Boot Configuration Status */
	switch(ces.bootConfigStatus){
		case firstUse:
		case devReset:
		case unconfigured:
			cec.setup.stage = PinSetupPart1;
			break;
		default:
			cec.setup.stage = Undefined;
			break;
	}
}
