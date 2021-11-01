#ifndef PINSETUPPRESENTER_HPP
#define PINSETUPPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class PinSetupView;

class PinSetupPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    PinSetupPresenter(PinSetupView& v);

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

    virtual ~PinSetupPresenter() {};

private:
    PinSetupPresenter();

    PinSetupView& view;
};

#endif // PINSETUPPRESENTER_HPP
