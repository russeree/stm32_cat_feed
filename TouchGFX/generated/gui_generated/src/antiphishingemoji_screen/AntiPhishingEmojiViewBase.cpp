/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/antiphishingemoji_screen/AntiPhishingEmojiViewBase.hpp>
#include <touchgfx/Color.hpp>
#include "BitmapDatabase.hpp"
#include <texts/TextKeysAndLanguages.hpp>

AntiPhishingEmojiViewBase::AntiPhishingEmojiViewBase() :
    buttonCallback(this, &AntiPhishingEmojiViewBase::buttonCallbackHandler),
    flexButtonCallback(this, &AntiPhishingEmojiViewBase::flexButtonCallbackHandler)
{

    __background.setPosition(0, 0, 272, 480);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    background.setXY(1, 0);
    background.setBitmap(touchgfx::Bitmap(BITMAP_PORTRAIT_SLIDE_TO_UNLOCK_BACKGROUND_ID));

    antiPhishingIcon1.setBitmaps(Bitmap(BITMAP_A16_ID), Bitmap(BITMAP_A16_ID));
    antiPhishingIcon1.setBitmapXY(0, 0);
    antiPhishingIcon1.setPosition(41, 112, 72, 72);
    antiPhishingIcon1.setAction(flexButtonCallback);

    antiPhishingIcon2.setBitmaps(Bitmap(BITMAP_A16_ID), Bitmap(BITMAP_A16_ID));
    antiPhishingIcon2.setBitmapXY(0, 0);
    antiPhishingIcon2.setPosition(157, 198, 72, 72);
    antiPhishingIcon2.setAction(flexButtonCallback);

    antiPhishingIcon3.setBitmaps(Bitmap(BITMAP_A16_ID), Bitmap(BITMAP_A16_ID));
    antiPhishingIcon3.setBitmapXY(0, 0);
    antiPhishingIcon3.setPosition(41, 198, 72, 72);
    antiPhishingIcon3.setAction(flexButtonCallback);

    antiPhishingIcon4.setBitmaps(Bitmap(BITMAP_A16_ID), Bitmap(BITMAP_A16_ID));
    antiPhishingIcon4.setBitmapXY(0, 0);
    antiPhishingIcon4.setPosition(157, 112, 72, 72);
    antiPhishingIcon4.setAction(flexButtonCallback);

    antiPhishingIcon5.setBitmaps(Bitmap(BITMAP_A16_ID), Bitmap(BITMAP_A16_ID));
    antiPhishingIcon5.setBitmapXY(0, 0);
    antiPhishingIcon5.setPosition(157, 289, 72, 72);
    antiPhishingIcon5.setAction(flexButtonCallback);

    antiPhishingIcon6.setBitmaps(Bitmap(BITMAP_A16_ID), Bitmap(BITMAP_A16_ID));
    antiPhishingIcon6.setBitmapXY(0, 0);
    antiPhishingIcon6.setPosition(41, 289, 72, 72);
    antiPhishingIcon6.setAction(flexButtonCallback);

    actionDescription.setXY(28, 22);
    actionDescription.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    actionDescription.setLinespacing(0);
    actionDescription.setTypedText(touchgfx::TypedText(T_SINGLEUSEID395));

    confirmEmojiSelection.setXY(52, 397);
    confirmEmojiSelection.setBitmaps(touchgfx::Bitmap(BITMAP_DARK_BUTTONS_ROUND_EDGE_SMALL_ID), touchgfx::Bitmap(BITMAP_DARK_BUTTONS_ROUND_EDGE_SMALL_PRESSED_ID));
    confirmEmojiSelection.setLabelText(touchgfx::TypedText(T_SINGLEUSEID396));
    confirmEmojiSelection.setLabelColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    confirmEmojiSelection.setLabelColorPressed(touchgfx::Color::getColorFromRGB(255, 255, 255));
    confirmEmojiSelection.setAction(buttonCallback);

    add(__background);
    add(background);
    add(antiPhishingIcon1);
    add(antiPhishingIcon2);
    add(antiPhishingIcon3);
    add(antiPhishingIcon4);
    add(antiPhishingIcon5);
    add(antiPhishingIcon6);
    add(actionDescription);
    add(confirmEmojiSelection);
}

void AntiPhishingEmojiViewBase::setupScreen()
{

}

void AntiPhishingEmojiViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &confirmEmojiSelection)
    {
        //SubmitEmojiSelection
        //When confirmEmojiSelection clicked call virtual function
        //Call submitEmojiSelection
        submitEmojiSelection();
    }
}

void AntiPhishingEmojiViewBase::flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src)
{
    if (&src == &antiPhishingIcon1)
    {
        //SelectEmoji1
        //When antiPhishingIcon1 clicked call virtual function
        //Call emoji1Select
        emoji1Select();
    }
    else if (&src == &antiPhishingIcon2)
    {
        //SelectEmoji2
        //When antiPhishingIcon2 clicked call virtual function
        //Call emoji2Select
        emoji2Select();
    }
    else if (&src == &antiPhishingIcon3)
    {
        //SelectEmoji3
        //When antiPhishingIcon3 clicked call virtual function
        //Call emoji3Select
        emoji3Select();
    }
    else if (&src == &antiPhishingIcon4)
    {
        //SelectEmoji4
        //When antiPhishingIcon4 clicked call virtual function
        //Call emoji4Select
        emoji4Select();
    }
    else if (&src == &antiPhishingIcon5)
    {
        //SelectEmoji5
        //When antiPhishingIcon5 clicked call virtual function
        //Call emoji5Select
        emoji5Select();
    }
    else if (&src == &antiPhishingIcon6)
    {
        //SelectEmoji6
        //When antiPhishingIcon6 clicked call virtual function
        //Call emoji6Select
        emoji6Select();
    }
}