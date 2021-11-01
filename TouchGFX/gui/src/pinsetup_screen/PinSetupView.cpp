#include <stdio.h>
#include <string.h>
#include <gui/pinsetup_screen/PinSetupView.hpp>

 PinSetupView::PinSetupView(){
	/* Set the tick counter to 0 so as to avoid overflow issues on class creation */
	tickCounter = 0;
	/* Hide the submit progress indicator */
	this->submitProgress.setVisible(false);
	this->submitProgress.invalidate();
	/*Set the setup text wildcard */
	this->setupYourPinText.setWildcard(createScreenTitleWildcardText());
	this->setupYourPinText.invalidate();

}

void PinSetupView::setupScreen(){
	PinSetupViewBase::setupScreen();
}

void PinSetupView::tearDownScreen(){
	PinSetupViewBase::tearDownScreen();
}

/**
 * @desc: This is the enter button 'press' function. This function starts a timer that continues as long as the button is pressed
 * this timer will update a progress bar. This is used to make sure that the user is deliberately pressing enter to submit a pin entry
 **/
void PinSetupView::handleTickEvent(){
	/*Check the tick counter*/
	if(this->tickCounter == 1000)
		this->tickCounter = 0;
	else
		this->tickCounter++;
	/* Check if the enter button is pressed */
	if(this->PinPad.enterButton->getPressed() == true){
		int submitProgressValue = this->submitProgress.getValue();
		if(submitProgressValue < _EMU_PIN_ENT_SUBMIT_THRESHOLD){
			submitProgressValue += _EMU_PIN_ENT_PRESS_PROGRESS_SPEED;
			this->submitProgress.setValue(submitProgressValue);
			this->submitProgress.setVisible(true);
			this->submitProgress.invalidate();
		}
		/* This will execute when the button is held to a value of 100 or more, this validates the user input. THIS IS A PIN SUBMSSION TO THE DEVICE */
		else{
		}
	}
	/* If the enter button is not pressed, reset the value of the progress counter to zero */
	else{
		if(submitProgress.getValue() > 0){
			this->submitProgress.setVisible(false);
			this->submitProgress.setValue(0);
			this->submitProgress.invalidate();
		}
	}
	/*Check if the show pin button is being pressed */
	if(this->tickCounter % 3 == 0){
		if(this->PinPad.showPasswordButton->getPressed() == true){
			this->PinPad.showPin = true;
		}
		else{
			this->PinPad.showPin = false;
		}
		this->PinPad.updatePinPressesDisplay();
	}
}

/**
 * @desc: Modifies the wildcard text of title ("SETUP PIN PART x")
 */
const Unicode::UnicodeChar* PinSetupView::createScreenTitleWildcardText(void){
	memset(this->setupYourPinTextBuffer, 0, sizeof(setupYourPinTextBuffer));
	char setupStageText[SETUPYOURPINTEXT_SIZE];
	switch(cec.setup.stage){
		case(PinSetupPart1):
			strncpy(setupStageText, "1", SETUPYOURPINTEXT_SIZE);
			break;
		case(PinSetupPart2):
			strncpy(setupStageText, "2", SETUPYOURPINTEXT_SIZE);
			break;
		default:
			strncpy(setupStageText, "-", SETUPYOURPINTEXT_SIZE);
	}
	Unicode::snprintf(this->setupYourPinTextBuffer, SETUPYOURPINTEXT_SIZE, "%s", setupStageText);
	return this->setupYourPinTextBuffer;
}
