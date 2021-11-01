/*
 * QRCodeWidget.hpp
 *
 *  Created on: Jun 21, 2021
 *      Author: Reese
 */

#ifndef QR_CODE_WIDGET_HPP
#define QR_CODE_WIDGET_HPP

#include <TouchGFXHAL.hpp>
#include <touchgfx/widgets/Widget.hpp>
#include <gui/model/QRCodeData.hpp>
#include "coinemu_qr.h"

/* QR Code TouchGFX Widget Defintion */
class QRCodeWidget : public touchgfx::Widget{
public:
    QRCodeWidget();

    virtual void draw(const touchgfx::Rect& invalidatedArea) const;
    virtual touchgfx::Rect getSolidRect() const;

    void setQRCodeData(QRCodeData* data);
    void setScale(uint8_t s);
private:
    void updateSize();

    QRCodeData *code;
    uint8_t scale;
};
#endif /* GUI_INCLUDE_GUI_COMMON_QRCODEWIDGET_HPP_ */
