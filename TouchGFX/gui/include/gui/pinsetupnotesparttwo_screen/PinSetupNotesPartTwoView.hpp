#ifndef PINSETUPNOTESPARTTWOVIEW_HPP
#define PINSETUPNOTESPARTTWOVIEW_HPP

#include <gui_generated/pinsetupnotesparttwo_screen/PinSetupNotesPartTwoViewBase.hpp>
#include <gui/pinsetupnotesparttwo_screen/PinSetupNotesPartTwoPresenter.hpp>

#include "coinemu.h"

class PinSetupNotesPartTwoView : public PinSetupNotesPartTwoViewBase
{
public:
    PinSetupNotesPartTwoView();
    virtual ~PinSetupNotesPartTwoView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // PINSETUPNOTESPARTTWOVIEW_HPP
