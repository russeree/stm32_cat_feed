#ifndef PINSETUPVIEW_HPP
#define PINSETUPVIEW_HPP

#define _EMU_PIN_ENT_PRESS_PROGRESS_SPEED 6
#define _EMU_PIN_ENT_SUBMIT_THRESHOLD 100

#include <gui_generated/pinsetup_screen/PinSetupViewBase.hpp>
#include <gui/pinsetup_screen/PinSetupPresenter.hpp>

extern "C" {
	#include "coinemu.h"
}


class PinSetupView : public PinSetupViewBase{
public:
    PinSetupView();
    virtual ~PinSetupView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();
    /* counting ticks */
    uint32_t tickCounter;
private:
    const Unicode::UnicodeChar* createScreenTitleWildcardText(void);
protected:
};

#endif // PINSETUPVIEW_HPP
