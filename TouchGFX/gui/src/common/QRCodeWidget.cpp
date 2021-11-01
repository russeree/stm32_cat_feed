/*
 * QRCodeWidget.cpp
 *
 *  Created on: Jun 21, 2021
 *      Author: Reese
 */

#include <gui/common/QRCodeWidget.hpp>
#include <stdio.h>

QRCodeWidget::QRCodeWidget() : code(0), scale(1){
}

void QRCodeWidget::setQRCodeData(QRCodeData *qrCode){
    code = qrCode;
    updateSize();
}

void QRCodeWidget::draw(const touchgfx::Rect& invalidatedArea) const
{
	/* If there is no QrCode just return and do not modify the buffer contents */
    if(!code){
        return;
    }
    touchgfx::Rect absolute = getAbsoluteRect();
    /* Cast the frabebuffer as an 8bit array, 3 8bit colors per pixel. */
    uint8_t *framebuffer = (uint8_t *)touchgfx::HAL::getInstance()->lockFrameBuffer();
    /* Iterate though pixels - then RGB as the sub pixel colors */
    for(int y = invalidatedArea.y; y < invalidatedArea.bottom(); y++){
        for(int x = invalidatedArea.x * 3; x < invalidatedArea.right() * 3; x += 3){
        	bool pixel = qrcodegen_getModule(qr0, (int)(x/(scale*3)), (int)(y/scale));
        	for(int rgb = 0; rgb < 3; rgb++){
        		if (pixel == true)
        			framebuffer[(absolute.x * 3 + x + rgb)  + (absolute.y + y) * (touchgfx::HAL::DISPLAY_WIDTH * 3)] = 0x00;
        		else
        			framebuffer[(absolute.x * 3 + x + rgb)  + (absolute.y + y) * (touchgfx::HAL::DISPLAY_WIDTH * 3)] = 0xFF;
        	}
        }
	asm("nop");
    }
    touchgfx::HAL::getInstance()->unlockFrameBuffer();
}

touchgfx::Rect QRCodeWidget::getSolidRect() const
{
    return touchgfx::Rect(0,0,getWidth(), getHeight());
}

void QRCodeWidget::setScale(uint8_t s)
{
    scale = s;
    updateSize();
}

void QRCodeWidget::updateSize()
{
    if(code)
    {
        setWidth(code->getWidth() * scale);
        setHeight(code->getHeight() * scale);
    }
}
