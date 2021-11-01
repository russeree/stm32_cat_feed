#ifndef PINSETUPCOMPLETENOTESPRESENTER_HPP
#define PINSETUPCOMPLETENOTESPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class PinSetupCompleteNotesView;

class PinSetupCompleteNotesPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    PinSetupCompleteNotesPresenter(PinSetupCompleteNotesView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~PinSetupCompleteNotesPresenter() {};

private:
    PinSetupCompleteNotesPresenter();

    PinSetupCompleteNotesView& view;
};

#endif // PINSETUPCOMPLETENOTESPRESENTER_HPP
