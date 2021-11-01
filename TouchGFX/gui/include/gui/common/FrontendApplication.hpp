#ifndef FRONTENDAPPLICATION_HPP
#define FRONTENDAPPLICATION_HPP

#include <gui_generated/common/FrontendApplicationBase.hpp>
#include "coinemu.h"

class FrontendHeap;

using namespace touchgfx;

class FrontendApplication : public FrontendApplicationBase
{
public:
    FrontendApplication(Model& m, FrontendHeap& heap);
    virtual ~FrontendApplication() { }

    virtual void handleTickEvent()
    {
        model.tick();
        FrontendApplicationBase::handleTickEvent();
    }
    void gotobtcunlock_screenScreenNoTransition();
    void gotoMainMenu();
    void gotoPinPad();
    void gotoFirstUse();
    void gotoPinPadNotes();
    void gotoPinPadNotesPart2();
    void gotoPinPadSetupComplete();

private:
    touchgfx::Callback<FrontendApplication> unlockTransitionCallback;
    void gotobtcunlock_screenScreenNoTransitionImpl();
    void gotoMainMenuImpl();
    void gotoPinPadImpl();
    void gotoFirstUseImpl();
    void gotoPinPadNotesImpl();
    void gotoPinPadNotesPart2Impl();
    void gotoPinPadSetupCompleteImpl();
};

#endif // FRONTENDAPPLICATION_HPP
