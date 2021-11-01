#ifndef ANTIPHISHINGEMOJIVIEW_HPP
#define ANTIPHISHINGEMOJIVIEW_HPP

#include <gui_generated/antiphishingemoji_screen/AntiPhishingEmojiViewBase.hpp>
#include <gui/antiphishingemoji_screen/AntiPhishingEmojiPresenter.hpp>

#define _EMU_MAX_EMOJI_IDX 140
#define _EMU_MAX_EMOJI_SELECTIONS 6

class AntiPhishingEmojiView : public AntiPhishingEmojiViewBase
{
public:
    AntiPhishingEmojiView();
    virtual ~AntiPhishingEmojiView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void emoji1Select();
    virtual void emoji2Select();
    virtual void emoji3Select();
    virtual void emoji4Select();
    virtual void emoji5Select();
    virtual void emoji6Select();

protected:
    uint8_t emojiSelectionIDX[6]; //Contains a list of emojis that the user can pick from
    touchgfx::ImageButtonStyle<touchgfx::ClickButtonTrigger>* emojiButtons[6];
    bool verificaionEmojisGenerated;
private:
    void userEmojiSelect(uint8_t emojiIdx);
};

#endif // ANTIPHISHINGEMOJIVIEW_HPP
