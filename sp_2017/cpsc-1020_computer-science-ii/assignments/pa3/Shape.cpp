#include "Shape.h"

Shape::Shape()
{
    clr.setRGB(0, 0, 0);
}

Shape::Shape(unsigned char r, unsigned char g, unsigned char b)
{
    clr.setRGB(r, g, b);
}

void Shape::setRGB(unsigned char r, unsigned char g, unsigned char b)
{
    clr.setRGB(r, g, b);
}

unsigned char Shape::getRed()
{
    return clr.getRed();
}

unsigned char Shape::getGreen()
{
    return clr.getGreen();
}

unsigned char Shape::getBlue()
{
    return clr.getBlue();
}
