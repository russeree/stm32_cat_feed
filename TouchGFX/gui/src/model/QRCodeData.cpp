/*
 * QRCodeData.cpp
 *
 *  Created on: Jun 21, 2021
 *      Author: Reese
 */

#include <gui/model/QRCodeData.hpp>
#include <stdlib.h>

//NOTE: in a real application you should override this and utilize a qr code generator
bool QRCodeData::at(uint16_t x, uint16_t y) const
{
    // a deterministic random value for x,y
    srand(x*123456+y*getWidth()*23456789);
    for(int i = 0; i < 100; i++)
    {
        srand(rand());
    }
    return ((rand() / (float)RAND_MAX) > 0.5);
}

uint16_t QRCodeData::getWidth() const
{
    return 37;
}

uint16_t QRCodeData::getHeight() const
{
    return 37;
}





