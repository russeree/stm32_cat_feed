#ifndef PADPADCUSTOMCONTAINER_HPP
#define PADPADCUSTOMCONTAINER_HPP

#include <gui_generated/containers/PinPadCustomContainerBase.hpp>

class PinPadCustomContainer : public PinPadCustomContainerBase
{
public:
    PinPadCustomContainer();
    virtual ~PinPadCustomContainer() {}

    virtual void initialize();
    /**
     * @desc: These functions represent the pin pad presses,
     * since the numbers order is always random on each boot these are refereced to their physical location
     **/
    virtual void pressedButton0();
    virtual void pressedButton1();
    virtual void pressedButton2();
    virtual void pressedButton3();
    virtual void pressedButton4();
    virtual void pressedButton5();
    virtual void pressedButton6();
    virtual void pressedButton7();
    virtual void pressedButton8();
    virtual void pressedButton9();
    virtual void pressedButtonDel();
    virtual void pressedButtonEnter();
public:
    touchgfx::TextButtonStyle<touchgfx::ImageButtonStyle<touchgfx::RepeatButtonTrigger>>* enterButton;
    touchgfx::ImageButtonStyle<touchgfx::RepeatButtonTrigger>* showPasswordButton;
    void updatePinPressesDisplay();
    bool showPin;
private:
    void pinEntryBoundsCheckPress(void); //Checks the zero bound and the upper bound of an entries length
    void updatePinPad(void);
};

#endif // PADPADCUSTOMCONTAINER_HPP
