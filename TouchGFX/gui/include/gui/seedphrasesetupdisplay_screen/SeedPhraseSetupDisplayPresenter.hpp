#ifndef SEEDPHRASESETUPDISPLAYPRESENTER_HPP
#define SEEDPHRASESETUPDISPLAYPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class SeedPhraseSetupDisplayView;

class SeedPhraseSetupDisplayPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    SeedPhraseSetupDisplayPresenter(SeedPhraseSetupDisplayView& v);

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

    virtual ~SeedPhraseSetupDisplayPresenter() {};

private:
    SeedPhraseSetupDisplayPresenter();

    SeedPhraseSetupDisplayView& view;
};

#endif // SEEDPHRASESETUPDISPLAYPRESENTER_HPP
