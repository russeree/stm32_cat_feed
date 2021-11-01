#ifndef SEEDWORDCUSTOMCONTAINER_HPP
#define SEEDWORDCUSTOMCONTAINER_HPP

#include <gui_generated/containers/SeedWordCustomContainerBase.hpp>

class SeedWordCustomContainer : public SeedWordCustomContainerBase
{
public:
    SeedWordCustomContainer();
    virtual ~SeedWordCustomContainer() {}

    virtual void initialize();
    void setSeedWordText(uint16_t bip39WordIdx, uint8_t seedPhraseWordNumber, uint8_t activeWallet);
protected:
};

#endif // SEEDWORDCUSTOMCONTAINER_HPP
