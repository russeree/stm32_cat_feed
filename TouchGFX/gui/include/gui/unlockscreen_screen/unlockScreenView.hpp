#ifndef PIN_PADVIEW_HPP
#define PIN_PADVIEW_HPP

#include <gui_generated/unlockscreen_screen/unlockScreenViewBase.hpp>
#include <gui/unlockscreen_screen/unlockScreenView.hpp>

/*Magic Number Defines*/
#define _EMU_PIN_ENT_PRESS_PROGRESS_SPEED 6
#define _EMU_PIN_ENT_SUBMIT_THRESHOLD 100
/*Magic Text Defines */
#define _EMU_PIN_GUI_INCORRECT_STATE_ENTRY "ERROR: FAILED TO DETERMINE CORRECT STATE OF PIN ENTRY\n\r"
#define _EMU_PIN_GUI_INCORRECT_STATE_NOTES "ERROR: COULD NOT DETERMINE THE CORRECT STATE FOR PIN PAD TEXT\n\r"
#define _EMU_PIN_GUI_ERROR_TRANSLATION_TO_MEMORY "ERROR: PIN NUMBER TRANSLATION TO MEMORY FAILED\n\r"
#define _EMU_PIN_GUI_ERROR_SCREEN_SWITCH_FAILED  "ERROR: CoinEMU can't determine the next screen to switch to.\n\r"

extern "C" {
	#include "coinemu.h"
}


class unlockScreenView : public unlockScreenViewBase
{
public:
	unlockScreenView();
    virtual ~unlockScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void pinEntryBoundsCheckPress(void);              //Checks the zero bound and the upper bound of a entries length
    void updatePinPressesDisplay(void);               //Updates the 'Pin Entry' text field with data.
    void safeMovePinToRam(void);                      //This function is built for the pin pad as such it will safely move the pin data to the cec structure. After which the pin will be authenticated
    void nextScreen(void);                            //Use this function to switch to the next screen
    /*-- Update the tick handler for use on the pin pad --*/
    virtual void handleTickEvent();
    virtual void confirmFirstUse();
    /* Update Global State Machine Functions */
    void updateCoinEmuSetupConfig(void); //Updates the state of the CoinEmu Setup Configuration State:
protected:
};

#endif // PIN_PADVIEW_HPP
