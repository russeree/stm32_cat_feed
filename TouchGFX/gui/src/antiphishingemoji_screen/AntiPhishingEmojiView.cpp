#include <gui/antiphishingemoji_screen/AntiPhishingEmojiView.hpp>

#include <stdlib.h>

extern "C" {
	#include "main.h"
	#include "coinemu.h"
	#include "string.h"
	#include "coinemu_rng.h"
	extern BlockEmuRNG bemurng;
}

AntiPhishingEmojiView::AntiPhishingEmojiView(){
	/*First create an array of emoji buttons to use*/
	this->emojiButtons[0] = &this->antiPhishingIcon1;
	this->emojiButtons[1] = &this->antiPhishingIcon2;
	this->emojiButtons[2] = &this->antiPhishingIcon3;
	this->emojiButtons[3] = &this->antiPhishingIcon4;
	this->emojiButtons[4] = &this->antiPhishingIcon5;
	this->emojiButtons[5] = &this->antiPhishingIcon6;
	/*Hide the confirmation button until an emoji is selected */
	this->confirmEmojiSelection.setVisible(false);
	this->verificaionEmojisGenerated = false;
	/* Uses the stm32tRNG  to generate a random number */
	if(bemurng.status == FAIL){
		initBlockEmuRng(&bemurng);
	}
	getEntropy(32);                                   //Generate the entropy for the data
	bool duplicateFound;                              //Has the generated seed word to verify already been requested
	while(!bemurng.entropyValid){                     //This is built to run until the data has been returned
		osDelay(1);
	}
	/* Seed the RNG */
	srand(bemurng.entropyArr[0]);
	for(uint8_t verImg = 0; verImg < _EMU_MAX_EMOJI_SELECTIONS; verImg++){
		duplicateFound = false;
		this->emojiSelectionIDX[verImg] = rand() % _EMU_MAX_EMOJI_IDX;
		for(int duplicateCheckIDX = 0; duplicateCheckIDX < verImg; duplicateCheckIDX++){
			if(this->emojiSelectionIDX[duplicateCheckIDX] == this->emojiSelectionIDX[verImg]){
				duplicateFound = true;
				break;
			}
		}
		if(duplicateFound){
			verImg--;
			continue;
		}
	}
	this->verificaionEmojisGenerated = true;
	/* Now display the emojis to the user */
	for(uint8_t emojiButton = 0; emojiButton < _EMU_MAX_EMOJI_SELECTIONS; emojiButton++){
		this->emojiButtons[emojiButton]->setBitmaps(Bitmap(emojiSelectionIDX[emojiButton]), Bitmap(emojiSelectionIDX[emojiButton]));
		this->emojiButtons[emojiButton]->invalidate();
	}
}

void AntiPhishingEmojiView::setupScreen(){
    AntiPhishingEmojiViewBase::setupScreen();
}

void AntiPhishingEmojiView::tearDownScreen(){
    AntiPhishingEmojiViewBase::tearDownScreen();
}

/*--- USER BUTTONS VIRTUAL FUNCTION OVERRIDES ---*/

void AntiPhishingEmojiView::emoji1Select(){
	userEmojiSelect(0);
};
void AntiPhishingEmojiView::emoji2Select(){
	userEmojiSelect(1);
};
void AntiPhishingEmojiView::emoji3Select(){
	userEmojiSelect(2);
};
void AntiPhishingEmojiView::emoji4Select(){
	userEmojiSelect(3);
};
void AntiPhishingEmojiView::emoji5Select(){
	userEmojiSelect(4);
};
void AntiPhishingEmojiView::emoji6Select(){
	userEmojiSelect(5);
};

/*--- EMOJI SELECTION DISPLAY AND SAVE ---*/
void AntiPhishingEmojiView::userEmojiSelect(uint8_t emojiIdx){
	for(uint8_t emojiButton = 0; emojiButton < _EMU_MAX_EMOJI_SELECTIONS; emojiButton++){
		this->emojiButtons[emojiButton]->setAlpha(50);
		if(emojiButton == emojiIdx){
			this->emojiButtons[emojiButton]->setAlpha(255);
		}
		this->emojiButtons[emojiButton]->invalidate();
	}
	this->confirmEmojiSelection.setVisible(true);
	this->confirmEmojiSelection.invalidate();
}
