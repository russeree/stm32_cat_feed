#include <gui/unlockscreen_screen/unlockScreenView.hpp>
#include <gui/unlockscreen_screen/unlockScreenPresenter.hpp>

unlockScreenPresenter::unlockScreenPresenter(unlockScreenView& v)
    : view(v){

}

void unlockScreenPresenter::activate()
{
	ces.curScreen = scrPinEntry;     //Let Coin EMU status know that the screen is now the pin pad screen
}

void unlockScreenPresenter::deactivate(){

}
