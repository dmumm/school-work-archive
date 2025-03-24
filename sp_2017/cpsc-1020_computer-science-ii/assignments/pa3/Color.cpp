#include "Color.h"

void Color::setRGB(unsigned char r, unsigned char g, unsigned char b)
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
