#ifndef PINSETUPNOTESPARTTWOPRESENTER_HPP
#define PINSETUPNOTESPARTTWOPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class PinSetupNotesPartTwoView;

class PinSetupNotesPartTwoPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    PinSetupNotesPartTwoPresenter(PinSetupNotesPartTwoView& v);

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

    virtual ~PinSetupNotesPartTwoPresenter() {};

private:
    PinSetupNotesPartTwoPresenter();

    PinSetupNotesPartTwoView& view;
};

#endif // PINSETUPNOTESPARTTWOPRESENTER_HPP
