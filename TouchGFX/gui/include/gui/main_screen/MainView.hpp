#ifndef MAIN_VIEW_HPP
#define MAIN_VIEW_HPP

#include <gui_generated/main_screen/MainViewBase.hpp>
#include <gui/main_screen/MainPresenter.hpp>

class MainView : public MainViewBase
{
public:
    MainView() = default;
    virtual void setupScreen();
    virtual void increaseValue();
    virtual void decreaseValue();

    void updateGFXElements();
protected:

private:
    uint8_t count = 0;
};

#endif // MAIN_VIEW_HPP
