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

void Shape::printRGB(ofstream &outputFile)
{
    outputFile << color.getRed() << color.getGreen() << color.getBlue();
}
