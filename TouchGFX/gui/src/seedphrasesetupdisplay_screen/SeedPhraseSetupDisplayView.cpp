#include <gui/seedphrasesetupdisplay_screen/SeedPhraseSetupDisplayView.hpp>
#include <stdlib.h>

extern "C" {
	#include "main.h"
	#include "coinemu.h"
	#include "string.h"
	#include "coinemu_flash.h"
	#include "coinemu_rng.h"
	#include "bip39.h"

	extern BlockEmuRNG bemurng;
}

SeedPhraseSetupDisplayView::SeedPhraseSetupDisplayView(): vqWindow(*this){
	this->verificaionWordsGenerated = false;
	this->activeWallet = 0;
	/* Let ces know the current screen is the seed phrase display */
	ces.curScreen = scrSeedPhraseDisplay;
	ces.nxtScreen = scrUndefined;
	/* Setup the pointers to this screens modal windows */
	this->seedPhraseSetupModalWindows[(uint8_t)backupConfirmation] = &exitConfirmation;
	this->seedPhraseSetupModalWindows[(uint8_t)backupVerification] = &seedPhraseVerification;
	this->seedPhraseSetupModalWindows[(uint8_t)backupComplete]     = &seedPhraseBackupComplete;
	/* Determine if the device is configured or not - The reason for this is to make sure that if the device is configured you are not modifying exitising wallets */
	switch(ces.bootConfigStatus){
		case unconfigured: //The device is unconfigured and this this will be the first wallet generated
		case firstUse:{
			char walletNameStr[] = "default";                                               //Set the name of the default wallet
			cec.walletCount = 1;                                                            //Creating the first wallet for the user
			createWalletInEEPROM(0, 0,(char*)&walletNameStr, words24);                      //Create a wallet within the devices EEPROM as the default wallet.
			this->setActiveWallet(0);                                                       //Set the default wallet to 0 since this is the first wallet on the device
			this->createSeedPhraseVerificaionQuestionScreen();                              //Setup the verification screen to prompt the user to verify the first index of a random seed word
			break;
		}
		default:
			printf("%s", _EMU_SEED_GUI_ERROR_INCORRECT_STATE);
			break;
	}

}

void SeedPhraseSetupDisplayView::setupScreen()
{
    SeedPhraseSetupDisplayViewBase::setupScreen();
}

void SeedPhraseSetupDisplayView::tearDownScreen()
{
    SeedPhraseSetupDisplayViewBase::tearDownScreen();
}

/**
 * @desc: Given the index of a modal window this helper function will hide the others and show the desired window
 **/
void SeedPhraseSetupDisplayView::setActiveModalWindow(SeedPhraseModalWindow switchToWindow){
	/* Start by hiding all of the modal windows */
	for(uint8_t window = 0; window < _EMU_BIP39_VERIFCATION_MODAL_WINDOWS; window++){
		this->seedPhraseSetupModalWindows[window]->hide();
	}
	if(switchToWindow == closeAll){
		return;
	}
	else{
		this->seedPhraseSetupModalWindows[switchToWindow]->show();
	}
}

/*--- Russeree Functions ---*/
void SeedPhraseSetupDisplayView::setActiveWallet(uint8_t walletNumber){
	if(walletNumber < _EMU_MAX_WALLETS){
		/* Set the active wallet number */
		this->activeWallet = walletNumber;
		/* Set the displayed name of the wallet for the user */
		touchgfx::Unicode::UnicodeChar _tempWalletName[_EMU_MAX_WALLET_NAME_LEN];
		touchgfx::Unicode::strncpy(_tempWalletName, (const char*)flashCES.cec.wallets[activeWallet].walletName, _EMU_MAX_WALLET_NAME_LEN);
		Unicode::snprintf(this->walletNameBuffer, WALLETNAME_SIZE, "USING \"%s\" WALLET", _tempWalletName);
		this->walletName.invalidate();
	}
	else{
		printf("%s", _EMU_SEED_GUI_ERROR_WALLET_OUT_OF_RANGE);
	}
}

/* Update Items on the the screen of scrolling items */
void SeedPhraseSetupDisplayView::seedWordScrollListUpdateItem(SeedWordCustomContainer& item, int16_t itemIndex){
	item.setSeedWordText(flashCES.cec.wallets[activeWallet].seedWords[itemIndex], itemIndex, this->activeWallet);
	printf("%s","NOW SHOWING OUTPUT OF SCROLL WIDGET\n\r");
}


/**
 * @desc: Activates the window for the user to confirm that they have infact backed up their seed phrase
 */
void SeedPhraseSetupDisplayView::SeedPhraseBackupConfirmWindow(){
	this->exitConfirmation.show();
}

/**
 * @desc:Allows the user to return to the seed generation display
 **/
void SeedPhraseSetupDisplayView::seedPhraseConfirmationCancel(){
	this->exitConfirmation.hide();
}

/**
 * @desc: Show a screen for a seed phrase confirmation - the user will input portions of their
 * seed phrase to verify that they have likely backed it up correctly ... For this project we will request
 * 3 words from the use to input from their initial 24 seed word wallet.
 */
void SeedPhraseSetupDisplayView::seedPhraseBackupVerification(){
	/*Verify the users seed with _EMU_BIP39_VERIFCATION_QUESTIONS number of tries*/
	this->seedPhraseVerification.show();
}

void SeedPhraseSetupDisplayView::answerASelected(){
	this->vqWindow.seedPhraseVerificationAnswerSubmit(0);
}
void SeedPhraseSetupDisplayView::answerBSelected(){
	this->vqWindow.seedPhraseVerificationAnswerSubmit(1);

}
void SeedPhraseSetupDisplayView::answerCSelected(){
	this->vqWindow.seedPhraseVerificationAnswerSubmit(2);
}
void SeedPhraseSetupDisplayView::answerDSelected(){
	this->vqWindow.seedPhraseVerificationAnswerSubmit(3);
}
/**
 * @desc: Creates the index locations of the seed words to verify.
 */
void SeedPhraseSetupDisplayView::createSeedWordsToVerify(void){
	/* Uses the stm32tRNG  to generate a random number */
	getEntropy(32);                                   //Generate the entropy for the data
	bool duplicateFound;                              //Has the generated seed word to verify already been requested
	while(!bemurng.entropyValid){                     //This is built to run until the data has been returned
		osDelay(1);
	}
	/* Seed the RNG */
	srand(bemurng.entropyArr[0]);
	for(uint8_t verWord = 0; verWord < _EMU_BIP39_VERIFCATION_QUESTIONS; verWord++){
		duplicateFound = false;
		this->seedWordsToVerify[verWord] = rand() % flashCES.cec.wallets[this->activeWallet].seedPhraseLength;
		for(int duplicateCheckIDX = 0; duplicateCheckIDX < verWord; duplicateCheckIDX++){
			if(this->seedWordsToVerify[duplicateCheckIDX] == this->seedWordsToVerify[verWord]){
				duplicateFound = true;
				break;
			}
		}
		if(duplicateFound){
			verWord--;
			continue;
		}
	}
	this->verificaionWordsGenerated = true;
}

/**
 * @desc: Updates the onscreen elements to display a question for the user to verify their seed word
 **/
void SeedPhraseSetupDisplayView::createSeedPhraseVerificaionQuestionScreen(void){
	/* Create a list of seed word backup verification questions for the seed phrase verification screen to use*/
	this->createSeedWordsToVerify();
	/* After you have set the initial wildcard setup the screen with a multiple choice selection */
	this->vqWindow.displayVerificationQuestion(this->seedWordsToVerify[0]);
}

/**
 * @section: Verification Questions Class Object constructor - This handles objects within the modal window
 **/
SeedPhraseSetupDisplayView::VerificationQuestions::VerificationQuestions(SeedPhraseSetupDisplayView& curVerificaionScreen)
	:  curScreenRef(curVerificaionScreen){
	this->correctSelectionBip39Idx = 0;
	this->correctSelectionPosition = 0;
	this->correctAnswers = 0;
	/* Create an array of pointers to buttons */
	this->buttons[0] = &this->curScreenRef.optionAFlx;
	this->buttons[1] = &this->curScreenRef.optionBFlx;
	this->buttons[2] = &this->curScreenRef.optionCFlx;
	this->buttons[3] = &this->curScreenRef.optionDFlx;
	/* Create and array of pointers to the button text buffers */
	this->buttonTextBuffers[0] = &this->curScreenRef.optionAFlxBuffer[0];
	this->buttonTextBuffers[1] = &this->curScreenRef.optionBFlxBuffer[0];
	this->buttonTextBuffers[2] = &this->curScreenRef.optionCFlxBuffer[0];
	this->buttonTextBuffers[3] = &this->curScreenRef.optionDFlxBuffer[0];
}

/**
 * @desc: Displays a multiple choice question for the user to answer
 */
void SeedPhraseSetupDisplayView::VerificationQuestions::displayVerificationQuestion(uint16_t seedWordIndex){
	/* First update the question text for the user to answer */
	Unicode::snprintf(this->curScreenRef.verificationWordNumberBuffer, VERIFICATIONWORDNUMBER_SIZE, "%d", seedWordIndex + 1); //!!!FIXME : VALIDATE PLEASE!!!
	this->curScreenRef.verificationWordNumber.setWildcard(this->curScreenRef.verificationWordNumberBuffer);
	this->curScreenRef.verificationWordNumber.invalidate();
	/* Write a check to make sure a seed word outside the seed word limit has not been requested */
	this->correctSelectionPosition = rand() % _EMU_BIP39_VERIFICION_SELECTION_OPTIONS;
	this->correctSelectionBip39Idx = flashCES.cec.wallets[this->curScreenRef.activeWallet].seedWords[seedWordIndex];
	/* Now get a list of wrong answers */
	for(uint8_t answerNumberIdx = 0; answerNumberIdx < _EMU_BIP39_VERIFICION_SELECTION_OPTIONS; answerNumberIdx++){
		this->wrongSelections[answerNumberIdx] = rand() % 2048;
		/* If the wrong answer matches the correct answer get a new wrong answer for the user */
		if(this->wrongSelections[answerNumberIdx] == this->correctSelectionBip39Idx){
			answerNumberIdx--;
			continue;
		}
	}
	/* Display and Setup the Buttons for the user */
	for(uint8_t userAnswerSelection = 0; userAnswerSelection < _EMU_BIP39_VERIFICION_SELECTION_OPTIONS; userAnswerSelection++){
		if(userAnswerSelection == correctSelectionPosition){
			touchgfx::Unicode::strncpy(this->buttonTextBuffers[userAnswerSelection], &bip39wl[this->correctSelectionBip39Idx][0], _EMU_MAX_SEEDWORD_CHARS);
		}
		else{
			touchgfx::Unicode::strncpy(this->buttonTextBuffers[userAnswerSelection], &bip39wl[this->wrongSelections[userAnswerSelection]][0], _EMU_MAX_SEEDWORD_CHARS);
		}
		Unicode::snprintf(this->buttonTextBuffers[userAnswerSelection], _EMU_MAX_SEEDWORD_CHARS, "%s", this->buttonTextBuffers[userAnswerSelection]);
		this->buttons[userAnswerSelection]->invalidate();
	}
}

/**
 * @desc: Right and Wrong answer logic for users seed phrase validation
 */
void SeedPhraseSetupDisplayView::VerificationQuestions::seedPhraseVerificationAnswerSubmit(uint8_t answerIndex){
	/* If the user selects the correct answer */
	if(answerIndex == correctSelectionPosition){
		this->correctAnswers++;
		if(correctAnswers < _EMU_BIP39_VERIFCATION_QUESTIONS){
			this->displayVerificationQuestion(this->curScreenRef.seedWordsToVerify[correctAnswers]);
		}
		else{
			/* This is the exit from the seed phrase verification */
			this->correctAnswers = 0;
			this->curScreenRef.createSeedWordsToVerify();
			this->displayVerificationQuestion(this->curScreenRef.seedWordsToVerify[correctAnswers]);
			this->curScreenRef.setActiveModalWindow(backupComplete);
		}
	}
	/* If the user selects anything that is not the night answer */
	else{
		this->correctAnswers = 0;                                       //Reset the number of correct guesses
		this->curScreenRef.setActiveModalWindow(closeAll);              //Close all the modal windows and start again;
		this->curScreenRef.createSeedWordsToVerify();                   //Generate a new set of questions for the user.
		this->displayVerificationQuestion(this->curScreenRef.seedWordsToVerify[correctAnswers]); //Setup a new set of verification multiple choice questions
	}
	/* Display another correct answer for the user */
}
