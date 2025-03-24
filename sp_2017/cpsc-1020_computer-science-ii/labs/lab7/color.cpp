/*
  Dylan Mumm
  dmumm
  Lab 7, 004
  Nick Glyder
*/

#include "color.h"

using namespace std;


Color::Color(unsigned char r, unsigned char g, unsigned char b)
{
  red = r;
  green = g;
  blue = b;

}

Color::Color()
{
  red = 0;
  green = 0;
  blue = 0;
}

void Color::setRed(unsigned char r)
{
  red = r;
}

void Color::setGreen(unsigned char g)
{
  green = g;
}

void Color::setBlue(unsigned char b)
{
  blue = b;
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
