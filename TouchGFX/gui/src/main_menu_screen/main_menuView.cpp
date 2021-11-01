#include <gui/main_menu_screen/main_menuView.hpp>

main_menuView::main_menuView()
{
	QRCodeData code;
	recvAddr.setXY(20, 40);
	recvAddr.setQRCodeData(&code);
	recvAddr.setScale(5);
	add(recvAddr);
}

void main_menuView::setupScreen()
{
    main_menuViewBase::setupScreen();
}

void main_menuView::tearDownScreen()
{
    main_menuViewBase::tearDownScreen();
}

void main_menuView::rngStatusUpdate(bool value){
	if(value)
		rngStatusIcon.setAlpha(255);
	else
		rngStatusIcon.setAlpha(63);
	rngStatusIcon.invalidate();
}

void main_menuView::updateRNG(){

}
