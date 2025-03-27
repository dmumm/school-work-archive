#include "Color.h"

void Color::setRGB(unsigned char red, unsigned char green, unsigned char blue)
{
    this->red = red;
    this->green = green;
    this->blue = blue;
}

unsigned char Color::getRed()
{
    return red;
}

unsigned char Color::getGreen()
{
    return green;
}

unsigned char Color::getBlue()
{
    return blue;
}
