#ifndef PINSETUPCOMPLETENOTESVIEW_HPP
#define PINSETUPCOMPLETENOTESVIEW_HPP

#include <gui_generated/pinsetupcompletenotes_screen/PinSetupCompleteNotesViewBase.hpp>
#include <gui/pinsetupcompletenotes_screen/PinSetupCompleteNotesPresenter.hpp>

class PinSetupCompleteNotesView : public PinSetupCompleteNotesViewBase
{
public:
    PinSetupCompleteNotesView();
    virtual ~PinSetupCompleteNotesView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // PINSETUPCOMPLETENOTESVIEW_HPP
