/*
 * QRCodeData.hpp
 *
 *  Created on: Jun 21, 2021
 *      Author: Reese
 */

#ifndef QR_CODE_HPP
#define QR_CODE_HPP

#include <touchgfx/hal/Types.hpp>

class QRCodeData{
public:
    /**
     * @fn bool QRCode::at(uint16_t x, uint16_t y);
     *
     * @brief Get the qr code value at a particular coordinate
     *
     * @param x x coordinate
     * @param y y coordinate
     *
     * @return The value of the qr code at the supplied coordinate
     */
    bool at(uint16_t x, uint16_t y) const;
    /**
     * @fn uint16_t QRCode::getWidth();
     *
     * @brief Get the width of the qr code
     *
     * @return The width
     */
    uint16_t getWidth() const;
    /**
     * @fn uint16_t QRCode::getHeight();
     *
     * @brief Get the height of the qr code
     *
     * @return The height
     */
    uint16_t getHeight() const;
};

#endif /* GUI_INCLUDE_GUI_COMMON_QRCODEDATA_HPP_ */
