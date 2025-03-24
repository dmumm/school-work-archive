#include "Pixel.h"


Pixel::Pixel()
{
  clr.setRGB(0,0,0);
}

Pixel::Pixel(unsigned char r, unsigned char g, unsigned char b)
{
  clr.setRGB(r, g, b);
}

void Pixel::setRGB(unsigned char r, unsigned char b, unsigned char g)
{
  clr.setRGB(r, g, b);
}

void Pixel::printRGB(ofstream& output)
{
  output << clr.getRed() << clr.getGreen() << clr.getBlue();
}

double Pixel::getX()
{
    return pnt.getX();
}

double Pixel::getY()
{
    return pnt.getY();
}
