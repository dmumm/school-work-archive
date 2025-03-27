#include "Shape.h"

Shape::Shape()
{
    color.setRGB(0, 0, 0);
}

Shape::Shape(unsigned char r, unsigned char g, unsigned char b)
{
    color.setRGB(r, g, b);
}

void Shape::setRGB(unsigned char r, unsigned char g, unsigned char b)
{
    color.setRGB(r, g, b);
}

unsigned char Shape::getRed()
{
    return color.getRed();
}

unsigned char Shape::getGreen()
{
    return color.getGreen();
}

unsigned char Shape::getBlue()
{
    return color.getBlue();
}
