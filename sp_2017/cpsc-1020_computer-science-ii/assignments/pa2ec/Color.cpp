/* Dylan Mumm
 * CPSC 1020 001, Spring 2017
 * dmumm
 */

#include "Color.h"

// Setter

void Color::setRGB(unsigned char r, unsigned char g, unsigned char b)
{

  red = r;
  green = g;
  blue = b;

}

// Getters

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
