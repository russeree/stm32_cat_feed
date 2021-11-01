/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef PINPADCUSTOMCONTAINERBASE_HPP
#define PINPADCUSTOMCONTAINERBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/containers/buttons/Buttons.hpp>
#include <touchgfx/widgets/BoxWithBorder.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

class PinPadCustomContainerBase : public touchgfx::Container
{
public:
    PinPadCustomContainerBase();
    virtual ~PinPadCustomContainerBase() {}
    virtual void initialize();

    /*
     * Virtual Action Handlers
     */
    virtual void pressedButton0()
    {
        // Override and implement this function in PinPadCustomContainer
    }

    virtual void pressedButton1()
    {
        // Override and implement this function in PinPadCustomContainer
    }

    virtual void pressedButton2()
    {
        // Override and implement this function in PinPadCustomContainer
    }

    virtual void pressedButton3()
    {
        // Override and implement this function in PinPadCustomContainer
    }

    virtual void pressedButton4()
    {
        // Override and implement this function in PinPadCustomContainer
    }

    virtual void pressedButton5()
    {
        // Override and implement this function in PinPadCustomContainer
    }

    virtual void pressedButton6()
    {
        // Override and implement this function in PinPadCustomContainer
    }

    virtual void pressedButton7()
    {
        // Override and implement this function in PinPadCustomContainer
    }

    virtual void pressedButton8()
    {
        // Override and implement this function in PinPadCustomContainer
    }

    virtual void pressedButton9()
    {
        // Override and implement this function in PinPadCustomContainer
    }

    virtual void pressedButtonDel()
    {
        // Override and implement this function in PinPadCustomContainer
    }

    virtual void pressedButtonEnter()
    {
        // Override and implement this function in PinPadCustomContainer
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::TextButtonStyle< touchgfx::ImageButtonStyle< touchgfx::RepeatButtonTrigger > > pin_pad_b_return;
    touchgfx::TextButtonStyle< touchgfx::ImageButtonStyle< touchgfx::ClickButtonTrigger > > pin_pad_b_del;
    touchgfx::WildcardTextButtonStyle< touchgfx::ImageButtonStyle< touchgfx::ClickButtonTrigger > > pin_pad_b_9;
    touchgfx::WildcardTextButtonStyle< touchgfx::ImageButtonStyle< touchgfx::ClickButtonTrigger > > pin_pad_b_8;
    touchgfx::WildcardTextButtonStyle< touchgfx::ImageButtonStyle< touchgfx::ClickButtonTrigger > > pin_pad_b_7;
    touchgfx::WildcardTextButtonStyle< touchgfx::ImageButtonStyle< touchgfx::ClickButtonTrigger > > pin_pad_b_6;
    touchgfx::WildcardTextButtonStyle< touchgfx::ImageButtonStyle< touchgfx::ClickButtonTrigger > > pin_pad_b_5;
    touchgfx::WildcardTextButtonStyle< touchgfx::ImageButtonStyle< touchgfx::ClickButtonTrigger > > pin_pad_b_4;
    touchgfx::WildcardTextButtonStyle< touchgfx::ImageButtonStyle< touchgfx::ClickButtonTrigger > > pin_pad_b_3;
    touchgfx::WildcardTextButtonStyle< touchgfx::ImageButtonStyle< touchgfx::ClickButtonTrigger > > pin_pad_b_2;
    touchgfx::WildcardTextButtonStyle< touchgfx::ImageButtonStyle< touchgfx::ClickButtonTrigger > > pin_pad_b_1;
    touchgfx::WildcardTextButtonStyle< touchgfx::ImageButtonStyle< touchgfx::ClickButtonTrigger > > pin_pad_b_0;
    touchgfx::BoxWithBorder pin_entry_box;
    touchgfx::TextAreaWithOneWildcard PinEntry;
    touchgfx::ImageButtonStyle< touchgfx::RepeatButtonTrigger > showPassword;

    /*
     * Wildcard Buffers
     */
    static const uint16_t PINENTRY_SIZE = 7;
    touchgfx::Unicode::UnicodeChar PinEntryBuffer[PINENTRY_SIZE];
    static const uint16_t PIN_PAD_B_9_SIZE = 2;
    touchgfx::Unicode::UnicodeChar pin_pad_b_9Buffer[PIN_PAD_B_9_SIZE];
    static const uint16_t PIN_PAD_B_8_SIZE = 2;
    touchgfx::Unicode::UnicodeChar pin_pad_b_8Buffer[PIN_PAD_B_8_SIZE];
    static const uint16_t PIN_PAD_B_7_SIZE = 2;
    touchgfx::Unicode::UnicodeChar pin_pad_b_7Buffer[PIN_PAD_B_7_SIZE];
    static const uint16_t PIN_PAD_B_6_SIZE = 2;
    touchgfx::Unicode::UnicodeChar pin_pad_b_6Buffer[PIN_PAD_B_6_SIZE];
    static const uint16_t PIN_PAD_B_5_SIZE = 2;
    touchgfx::Unicode::UnicodeChar pin_pad_b_5Buffer[PIN_PAD_B_5_SIZE];
    static const uint16_t PIN_PAD_B_4_SIZE = 2;
    touchgfx::Unicode::UnicodeChar pin_pad_b_4Buffer[PIN_PAD_B_4_SIZE];
    static const uint16_t PIN_PAD_B_3_SIZE = 2;
    touchgfx::Unicode::UnicodeChar pin_pad_b_3Buffer[PIN_PAD_B_3_SIZE];
    static const uint16_t PIN_PAD_B_2_SIZE = 2;
    touchgfx::Unicode::UnicodeChar pin_pad_b_2Buffer[PIN_PAD_B_2_SIZE];
    static const uint16_t PIN_PAD_B_1_SIZE = 2;
    touchgfx::Unicode::UnicodeChar pin_pad_b_1Buffer[PIN_PAD_B_1_SIZE];
    static const uint16_t PIN_PAD_B_0_SIZE = 2;
    touchgfx::Unicode::UnicodeChar pin_pad_b_0Buffer[PIN_PAD_B_0_SIZE];

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<PinPadCustomContainerBase, const touchgfx::AbstractButtonContainer&> flexButtonCallback;

    /*
     * Callback Handler Declarations
     */
    void flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src);

};

#endif // PINPADCUSTOMCONTAINERBASE_HPP