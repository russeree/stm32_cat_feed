#include <gui/common/FrontendApplication.hpp>
#include <gui/unlockscreen_screen/unlockScreenView.hpp>
#include <gui/unlockscreen_screen/unlockScreenPresenter.hpp>
#include <touchgfx/transitions/NoTransition.hpp>
#include <touchgfx/transitions/SlideTransition.hpp>
#include <touchgfx/transitions/CoverTransition.hpp>
#include <gui/common/FrontendHeap.hpp>
#include "coinemu.h"

FrontendApplication::FrontendApplication(Model& m, FrontendHeap& heap)
    : FrontendApplicationBase(m, heap){

}

void FrontendApplication::gotoPinPadSetupComplete(){
    unlockTransitionCallback = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::gotoPinPadSetupCompleteImpl);
    pendingScreenTransitionCallback = &unlockTransitionCallback;
    return;
}

void FrontendApplication::gotoPinPadNotesPart2(){
    unlockTransitionCallback = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::gotoPinPadNotesPart2Impl);
    pendingScreenTransitionCallback = &unlockTransitionCallback;
    return;
}

void FrontendApplication::gotoPinPad()
{
    unlockTransitionCallback = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::gotoPinPadImpl);
    pendingScreenTransitionCallback = &unlockTransitionCallback;
    return;
}

void FrontendApplication::gotoMainMenu()
{
    unlockTransitionCallback = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::gotoMainMenuImpl);
    pendingScreenTransitionCallback = &unlockTransitionCallback;
    return;
}

/*--- TRANSITION CALLBACK FUNCTIONS ---*/
void FrontendApplication::gotoPinPadSetupCompleteImpl(){
	touchgfx::makeTransition<PinSetupCompleteNotesView, PinSetupCompleteNotesPresenter, touchgfx::CoverTransition<NORTH>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
	return;
}

void FrontendApplication::gotoPinPadNotesPart2Impl(){
	touchgfx::makeTransition<PinSetupNotesPartTwoView, PinSetupNotesPartTwoPresenter, touchgfx::CoverTransition<NORTH>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
	return;
}

void FrontendApplication::gotoPinPadImpl()
{
	touchgfx::makeTransition<unlockScreenView, unlockScreenPresenter, touchgfx::CoverTransition<NORTH>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
	return;
}

void FrontendApplication::gotoMainMenuImpl()
{
	touchgfx::makeTransition<main_menuView, main_menuPresenter, touchgfx::CoverTransition<NORTH>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
	return;
}
