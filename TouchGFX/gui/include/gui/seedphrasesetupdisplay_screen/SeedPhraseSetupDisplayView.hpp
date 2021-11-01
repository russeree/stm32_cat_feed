#ifndef SEEDPHRASESETUPDISPLAYVIEW_HPP
#define SEEDPHRASESETUPDISPLAYVIEW_HPP

#include <gui_generated/seedphrasesetupdisplay_screen/SeedPhraseSetupDisplayViewBase.hpp>
#include <gui/seedphrasesetupdisplay_screen/SeedPhraseSetupDisplayPresenter.hpp>

/*Magic Numbers*/
#define _EMU_BIP39_VERIFCATION_QUESTIONS 3
#define _EMU_BIP39_VERIFCATION_MODAL_WINDOWS 3
#define _EMU_BIP39_UTF8_BUF_SIZE 9
#define _EMU_BIP39_VERIFICION_SELECTION_OPTIONS 4
/*Magic Words*/
#define _EMU_SEED_GUI_ERROR_INCORRECT_STATE "ERROR - SEED GENERATION: THIS INCORRECT SETUP STATE DETERMINED"
#define _EMU_SEED_GUI_ERROR_WALLET_OUT_OF_RANGE "Failed to set an active wallet. the requested wallet is out of range."

typedef enum{
	backupConfirmation, //Has the user backed up their seed phrase question (YES/NO)
	backupVerification, //Multiple Choice Test for the user to complete proving they have backed up their seed phrase
	backupComplete,     //Seed phrase is saved to the eeprom and backed up
	closeAll
} SeedPhraseModalWindow;

class SeedPhraseSetupDisplayView : public SeedPhraseSetupDisplayViewBase{
public:
	/* Nested Class for use with the verification questions window */
	class VerificationQuestions{
	public:
		VerificationQuestions(SeedPhraseSetupDisplayView& curVerificaionScreen);
		virtual ~VerificationQuestions(){}
		uint16_t wrongSelections[_EMU_BIP39_VERIFICION_SELECTION_OPTIONS];
		uint8_t  correctAnswers;
		uint8_t  correctSelectionPosition;
		uint16_t correctSelectionBip39Idx;
		/* Pointer arrays to TouchGFX Elements */
		touchgfx::WildcardTextButtonStyle<touchgfx::ImageButtonStyle<touchgfx::ClickButtonTrigger>>* buttons[4];
		touchgfx::Unicode::UnicodeChar* buttonTextBuffers[4];
	public: //Functions for modifying the screen contents of the seed phrase verificaion
		void displayVerificationQuestion(uint16_t correctSeedWordIndex); //Shows the user a verification question.
		void seedPhraseVerificationAnswerSubmit(uint8_t answerIndex);
	private:
		SeedPhraseSetupDisplayView& curScreenRef;
	};
public:
    SeedPhraseSetupDisplayView();
    virtual ~SeedPhraseSetupDisplayView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    /*Virtual Base Functions used to display the BIP39 SeedPhrase to the screen for the user */
    virtual void SeedPhraseBackupConfirmWindow();
    virtual void seedPhraseBackupVerification();
    virtual void seedPhraseConfirmationCancel();
    virtual void seedWordScrollListUpdateItem(SeedWordCustomContainer& item, int16_t itemIndex);
    /*Helper Functions */
    void setActiveWallet(uint8_t walletNumber);
    void setActiveModalWindow(SeedPhraseModalWindow switchToWindow);
protected:
    uint8_t activeWallet;
    bool    verificaionWordsGenerated;
    touchgfx::ModalWindow* seedPhraseSetupModalWindows[_EMU_BIP39_VERIFCATION_MODAL_WINDOWS];
protected:
    void updateUtf8SeedWord(touchgfx::Unicode::UnicodeChar* _tempSeedWord, uint8_t word);
/* Seed Phrase Verification Variables */
protected:
    VerificationQuestions vqWindow;
    virtual void answerASelected();
    virtual void answerBSelected();
    virtual void answerCSelected();
    virtual void answerDSelected();
    void createSeedPhraseVerificaionQuestionScreen(void); //Call this one time to generate a series of questions for the user to answer
    void createSeedWordsToVerify(void);
    uint8_t seedWordsToVerify[_EMU_BIP39_VERIFCATION_QUESTIONS];
};

#endif // SEEDPHRASESETUPDISPLAYVIEW_HPP
