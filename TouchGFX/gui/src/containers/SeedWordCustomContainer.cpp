#include <gui/containers/SeedWordCustomContainer.hpp>
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


SeedWordCustomContainer::SeedWordCustomContainer()
{

}

void SeedWordCustomContainer::initialize()
{
    SeedWordCustomContainerBase::initialize();
}

/**
 * @desc: Sets the text of a SeedWordCustomContainer given the index of the word on the bip39 Word List
 */
void SeedWordCustomContainer::setSeedWordText(uint16_t bip39WordIdx, uint8_t seedPhraseWordNumber, uint8_t activeWallet){
	printf("%d\n\r", bip39WordIdx);
	touchgfx::Unicode::UnicodeChar _tempSeedWord[_EMU_BIP39_UTF8_BUF_SIZE];
	char _capWord[_EMU_BIP39_UTF8_BUF_SIZE];
	memset (_capWord,'\0', 9);
	for(uint8_t letter = 0; letter < strlen(bip39wl[bip39WordIdx]); letter++){
		_capWord[letter] = bip39wl[bip39WordIdx][letter] - 32;
	}
	touchgfx::Unicode::strncpy(_tempSeedWord, &_capWord[0], 9);
	if(seedPhraseWordNumber < 9)
		Unicode::snprintf(this->SeedWordBuffer, SEEDWORD_SIZE, " %d.%s", seedPhraseWordNumber + 1, _tempSeedWord);
	else
		Unicode::snprintf(this->SeedWordBuffer, SEEDWORD_SIZE, "%d.%s", seedPhraseWordNumber + 1, _tempSeedWord);
	this->SeedWord.invalidate();
}
