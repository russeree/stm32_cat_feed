#ifndef MAIN_MENUVIEW_HPP
#define MAIN_MENUVIEW_HPP

#include <gui_generated/main_menu_screen/main_menuViewBase.hpp>
#include <gui/main_menu_screen/main_menuPresenter.hpp>
#include <gui/common/QRCodeWidget.hpp>

class main_menuView : public main_menuViewBase
{
public:
    main_menuView();
    virtual ~main_menuView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    /* RNG Status Update Variables for the user */
    virtual void updateRNG();
    virtual void rngStatusUpdate(bool value);
    /* QR Code Example Data */

protected:
    QRCodeWidget recvAddr;
};

#endif // MAIN_MENUVIEW_HPP
